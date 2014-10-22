#include "PrecompiledHeader.h"
#include "CloudAndWorkshop.h"
#include "steam_api.h"
#include "Steamworks.h"
#include "ISteamRemoteStorage.h"
#include "ISteamUGC.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/stat.h>

#define _MAX_FNAME 256
#define _MAX_EXT 256
#define _MAX_PATH 260

char CCloudAndWorkshop::mFile[] = {};
AppId_t CCloudAndWorkshop::mAppID = 0;
char CCloudAndWorkshop::mTitle[] = {};
char CCloudAndWorkshop::m_sUGCDownloadLocation[] = {};
char CCloudAndWorkshop::mDescription[] = {};
SteamUGCDetails_t CCloudAndWorkshop::mTempDetails;
char CCloudAndWorkshop::m_sFileID[] = {};
char CCloudAndWorkshop::m_sPublishAICallback[] = {};
char CCloudAndWorkshop::m_sPublishHandlerCallback[] = {};

CCloudAndWorkshop::CCloudAndWorkshop (const char* sAIModel) :
	m_CallbackFileSubscribed( this, &CCloudAndWorkshop::OnFileSubscribed ),
	m_CallbackFileUnsubscribed( this, &CCloudAndWorkshop::OnFileUnsubscribed )
{
	m_pSteamRemoteStorage = SteamRemoteStorage();
	m_pSteamUGC = SteamUGC();
	m_sAIModel = sAIModel;
}

// http://stackoverflow.com/questions/228005/alternative-to-itoa-for-converting-integer-to-string-c
std::string CCloudAndWorkshop::toString(int i)
{
	std::stringstream out;
	out << i;
	return out.str();
}
void CCloudAndWorkshop::SetCallback ( const char* ai, const char* handler)
{
	strcpy(m_sPublishAICallback, ai);
	strcpy(m_sPublishHandlerCallback, handler);
}
void CCloudAndWorkshop::SetUGCDownloadLocation(const char* location)
{
	strcpy( m_sUGCDownloadLocation, location);
}

/* 
 * Called when a user subscribes to a workshop item
 */
void CCloudAndWorkshop::OnFileSubscribed ( RemoteStoragePublishedFileSubscribed_t* pCallback )
{
	char *number = new char [30];
	strcpy ( number, toString(pCallback->m_nPublishedFileId).c_str() );
	S3DX::AIVariable fileID;
	fileID.SetStringValue (number);
	S3DX::user.sendEvent ( S3DX::application.getCurrentUser(), m_sAIModel, "onWorkshopItemSubscribed", fileID );
	delete[] number;
}

/* 
 * Called when a user unsubscribes from a workshop item
 */
void CCloudAndWorkshop::OnFileUnsubscribed ( RemoteStoragePublishedFileUnsubscribed_t * pCallback )
{
	char *number = new char [30];
	strcpy ( number, toString(pCallback->m_nPublishedFileId).c_str() );
	S3DX::AIVariable fileID;
	fileID.SetStringValue (number);
	S3DX::user.sendEvent ( S3DX::application.getCurrentUser(), m_sAIModel, "onWorkshopItemUnsubscribed", fileID );
	delete[] number;
}

bool CCloudAndWorkshop::WriteFile(const char *sFile)
{
	S3DX::log.warning("Steamworks: Write file ", sFile);

	// Open the file
	std::ifstream is (sFile, std::ifstream::binary);
	if (!is)
	{
		S3DX::log.warning("Steamworks: File did not exist: ", sFile);
		return false;
	}

	// Read the contents of the file
	is.seekg(0, is.end);
	int length = is.tellg();
	is.seekg(0, is.beg);
	
	char * fileBuffer = new char [length];
	is.read(fileBuffer, length);
	is.close();

	// Extract the name of the file from the path
	std::string filename(sFile);
	const size_t last_slash_idx = filename.find_last_of("\\/");
	if (std::string::npos != last_slash_idx)
	{
		filename.erase(0, last_slash_idx + 1);
		strcpy ( mFile, filename.c_str());
	}

	// Write file to steam cache
	bool result = m_pSteamRemoteStorage->FileWrite( mFile, fileBuffer, length );
	delete[] fileBuffer;
	return result;
}

/* 
 * Publishes a new file to the workshop
 */
void CCloudAndWorkshop::PublishFile ( const char* sFile, int appID, const char* sTitle, const char* sDesc, const char* sAI, const char* sCallback )
{
	SetCallback ( sAI, sCallback );

	strcpy ( mTitle, sTitle );
	strcpy ( mDescription, sDesc );
	mAppID = appID;

	S3DX::log.warning("Steamworks: PublishFile called with ", sFile, " ", mTitle, " ", mDescription, " ", mAppID);

	bool result = WriteFile(sFile);

	if (!result)
	{
		S3DX::log.warning("Steamworks: File could not be written to steam cloud.\nCloud Enabled for Account: ", m_pSteamRemoteStorage->IsCloudEnabledForAccount(),
			"\nCloud Enabled for App: ", m_pSteamRemoteStorage->IsCloudEnabledForApp());
		S3DX::user.sendEvent(S3DX::application.getCurrentUser(), sAI, sCallback, false);
		return;
	}

	//Initiate the upload immediately 
	SteamAPICall_t hSteamAPICall = m_pSteamRemoteStorage->FileShare( mFile );
	m_callResultWriteFile.Set( hSteamAPICall, this, &CCloudAndWorkshop::OnFileSharePublishToWorkshop );
}

/* 
 * Callback for FileShare
 */
void CCloudAndWorkshop::OnFileSharePublishToWorkshop ( RemoteStorageFileShareResult_t *pResult, bool bIOFailure )
{
	if (bIOFailure)
	{
		S3DX::log.warning("Steamworks: OnFileSharePublishToWorkshop callback failure" );
		S3DX::user.sendEvent(S3DX::application.getCurrentUser(), m_sPublishAICallback, m_sPublishHandlerCallback, false);
		return;
	}

	if ( pResult->m_eResult != k_EResultOK )
	{
		S3DX::log.warning( "Steamworks: Publish File failed with: ", pResult->m_eResult, " see definition for EResult in steamclientpublic.h" );
		S3DX::user.sendEvent(S3DX::application.getCurrentUser(), m_sPublishAICallback, m_sPublishHandlerCallback, false);
		return;
	}

	S3DX::log.warning( "Steamworks: OnFileSharePublishToWorkshop callback: ", pResult->m_eResult );
	S3DX::log.warning("Steamworks: Publishing file with: ", mFile, " ", mTitle, " ", mDescription, " ", mAppID);

	// Publish the file to the workshop
	SteamAPICall_t hSteamAPICall = m_pSteamRemoteStorage->PublishWorkshopFile( mFile, 
		NULL, //const char *pchPreviewFile, 
		mAppID, 
		mTitle, 
		mDescription, 
		k_ERemoteStoragePublishedFileVisibilityPublic, 
		NULL, //SteamParamStringArray_t *pTags, 
		k_EWorkshopFileTypeCommunity );

	m_callResultPublishFile.Set ( hSteamAPICall, this, &CCloudAndWorkshop::OnPublishFileResult );
}

/* 
 * Callback for PublishWorkshopFile
 */
void CCloudAndWorkshop::OnPublishFileResult ( RemoteStoragePublishFileResult_t * pResult, bool bIOFailure )
{
	if (pResult->m_eResult != k_EResultOK || bIOFailure)
	{
		S3DX::log.warning("Steamworks: OnPublishFileResult callback failure" );
		S3DX::user.sendEvent(S3DX::application.getCurrentUser(), m_sPublishAICallback, m_sPublishHandlerCallback, false);
		return;
	}

	S3DX::log.warning("Steamworks: OnPublishFileResult returned: ", pResult->m_eResult );

	// Open a url to the published item
	S3DX::user.sendEvent(S3DX::application.getCurrentUser(), m_sPublishAICallback, m_sPublishHandlerCallback, true);
	OpenItemInBrowser( pResult->m_nPublishedFileId );
}

void CCloudAndWorkshop::PublishFileUpdate( uint64 fileID, const char* sFile, int appID, const char* sTitle, const char* sDesc, const char* sAI, const char* sCallback )
{
	SetCallback ( sAI, sCallback );

	PublishedFileUpdateHandle_t hFileHandle = m_pSteamRemoteStorage->CreatePublishedFileUpdateRequest ( fileID );
	if (hFileHandle != NULL)
	{
		bool result = WriteFile(sFile);

		m_pSteamRemoteStorage->UpdatePublishedFileDescription(hFileHandle, sDesc);
		m_pSteamRemoteStorage->UpdatePublishedFileFile(hFileHandle, mFile);
		m_pSteamRemoteStorage->UpdatePublishedFileTitle(hFileHandle, sTitle);

		SteamAPICall_t hSteamAPICall = m_pSteamRemoteStorage->CommitPublishedFileUpdate( hFileHandle );
		m_callResultPublishFileUpdate.Set( hSteamAPICall, this, &CCloudAndWorkshop::OnPublishedFileUpdateRequest );
	}
	else
	{
		S3DX::user.sendEvent(S3DX::application.getCurrentUser(), m_sPublishAICallback, m_sPublishHandlerCallback, false);
	}
}

void CCloudAndWorkshop::OnPublishedFileUpdateRequest ( RemoteStorageUpdatePublishedFileResult_t  *pResult, bool bIOFailure )
{
	if (pResult->m_eResult != k_EResultOK || bIOFailure)
	{
		S3DX::log.warning("Steamworks: OnPublishedFileUpdateRequest callback failure ", pResult->m_eResult );
		S3DX::user.sendEvent(S3DX::application.getCurrentUser(), m_sPublishAICallback, m_sPublishHandlerCallback, false);
		return;
	}

	S3DX::log.warning("Steamworks: OnPublishedFileUpdateRequest returned: ", pResult->m_eResult );
	S3DX::user.sendEvent(S3DX::application.getCurrentUser(), m_sPublishAICallback, m_sPublishHandlerCallback, true);

	// Open a url to the published item
	OpenItemInBrowser( pResult->m_nPublishedFileId );
}

/*
 * Subscribe and unsubscribe to a file, note that these will trigger the callbacks when they're called
 */
void CCloudAndWorkshop::SubscribeToFile ( uint64 item )
{
	m_pSteamRemoteStorage->SubscribePublishedFile( item );
}

void CCloudAndWorkshop::UnsubscribeFromFile ( uint64 item )
{
	m_pSteamRemoteStorage->UnsubscribePublishedFile( item );
}

/*
 * Set one of the available actions on the item
 */
void CCloudAndWorkshop::SetPublishedFileAction ( uint64 item, EWorkshopFileAction eAction )
{
	m_pSteamRemoteStorage->SetUserPublishedFileAction ( item, eAction );
}

void CCloudAndWorkshop::GetUserPublishedItemVoteDetails ( uint64 item )
{
	SteamAPICall_t hSteamAPICall = m_pSteamRemoteStorage->GetUserPublishedItemVoteDetails( item );
	m_callResultGetUserVoteDetails.Set( hSteamAPICall, this, &CCloudAndWorkshop::OnGetUserPublishedItemVoteDetails );
}

void CCloudAndWorkshop::GetPublishedItemVoteDetails ( uint64 item )
{
	SteamAPICall_t hSteamAPICall = m_pSteamRemoteStorage->GetPublishedItemVoteDetails( item );
	m_callResultGetVoteDetails.Set( hSteamAPICall, this, &CCloudAndWorkshop::OnGetPublishedItemVoteDetails );
	
	//m_pSteamRemoteStorage->GetUserPublishedItemVoteDetails( item );
	//m_pSteamRemoteStorage->UpdateUserPublishedItemVote ( item, true );
}

void CCloudAndWorkshop::UpdateUserPublishedItemVote ( uint64 item, bool vote )
{
	m_pSteamRemoteStorage->UpdateUserPublishedItemVote ( item, vote );
}

// Callback when fetching user vote details
void CCloudAndWorkshop::OnGetUserPublishedItemVoteDetails( RemoteStorageUserVoteDetails_t *pResult, bool bIOFailure )
{
	if (pResult->m_eResult == k_EResultOK)
	{
		char *number = new char [30];
		strcpy ( number, toString(pResult->m_nPublishedFileId).c_str() );
		S3DX::AIVariable fileID;
		fileID.SetStringValue (number);
		
		bool vote = NULL;
		if (pResult->m_eVote == k_EWorkshopVoteFor)
			vote = true;
		else if (pResult->m_eVote == k_EWorkshopVoteAgainst)
			vote = false;

		// score, reports
		S3DX::user.sendEvent ( S3DX::application.getCurrentUser(), m_sAIModel, "onWorkshopUserItemVoteDetails", 
			fileID,
			vote);

		delete[] number;
	}
}

// Callback when fetchign vote details
void CCloudAndWorkshop::OnGetPublishedItemVoteDetails ( RemoteStorageGetPublishedItemVoteDetailsResult_t *pResult, bool bIOFailure )
{
	if (pResult->m_eResult == k_EResultOK)
	{
		char *number = new char [30];
		strcpy ( number, toString(pResult->m_unPublishedFileId).c_str() );
		S3DX::AIVariable fileID;
		fileID.SetStringValue (number);
		
		// score, reports
		S3DX::user.sendEvent ( S3DX::application.getCurrentUser(), m_sAIModel, "onWorkshopItemVoteDetails", 
			fileID,
			pResult->m_fScore,
			pResult->m_nVotesFor,
			pResult->m_nVotesAgainst,
			pResult->m_nReports);

		delete[] number;
	}
}

void CCloudAndWorkshop::OnUGCQueryCompleted( SteamUGCQueryCompleted_t * pResult, bool bIOFailure )
{
	if (pResult->m_eResult != k_EResultOK || bIOFailure)
	{
		S3DX::log.message("Query failed ", pResult->m_eResult, " ", bIOFailure);
		return;
	}

	char *number = new char [30];

	for (int i = 0; i < pResult->m_unNumResultsReturned; i++)
	{
		m_pSteamUGC->GetQueryUGCResult(pResult->m_handle, i, &mTempDetails);

		strcpy ( number, toString(mTempDetails.m_nPublishedFileId).c_str() );
		S3DX::AIVariable fileID;
		fileID.SetStringValue (number);

		//S3DX::log.message(  (int)mTempDetails.m_ulSteamIDOwner, " vs ", (int)SteamUser()->GetSteamID().GetAccountID());
		bool isCreator = (int)mTempDetails.m_ulSteamIDOwner == (int)SteamUser()->GetSteamID().GetAccountID();

		// Send item details to user
		S3DX::user.sendEvent( S3DX::application.getCurrentUser(), 
			"Steam", 
			"onQueryWorkshopUserContent", 
			i, 
			pResult->m_unNumResultsReturned, 
			pResult->m_unTotalMatchingResults,
			fileID,
			mTempDetails.m_rgchTitle,
			mTempDetails.m_rgchDescription,
			mTempDetails.m_rtimeUpdated,
			mTempDetails.m_pchFileName,
			isCreator,
			SteamFriends()->GetFriendPersonaName(mTempDetails.m_ulSteamIDOwner),
			mTempDetails.m_flScore);
	}

	// Release query
	delete[] number;
	m_pSteamUGC->ReleaseQueryUGCRequest(pResult->m_handle);
}

void CCloudAndWorkshop::DownloadUGCContent ( uint64 item )
{
	strcpy ( m_sFileID, toString(item).c_str() );
	SteamAPICall_t hSteamAPICall = m_pSteamRemoteStorage->GetPublishedFileDetails( item, 300 );
	m_CallbackDownloadContent.Set ( hSteamAPICall, this, &CCloudAndWorkshop::OnDownloadUGCContent );
}

void CCloudAndWorkshop::OnDownloadUGCContent ( RemoteStorageGetPublishedFileDetailsResult_t *pResult, bool bIOFailure )
{
	if ( pResult->m_eResult != k_EResultOK || bIOFailure )
	{
		S3DX::log.message("Download init failed ", pResult->m_eResult, " ", bIOFailure);
		S3DX::user.sendEvent ( S3DX::application.getCurrentUser(), m_sAIModel, "onWorkshopDownloadComplete", false );
		return;
	}

	// Only download the file if an update is required
	char *filename = new char[_MAX_PATH];
	
	// Construct path/filename
	strcpy(filename, m_sUGCDownloadLocation );
	strcat(filename, m_sFileID );
	strcat(filename, "-" );
	strcat(filename, pResult->m_pchFileName );

	struct stat fileInfo;
	
	if (stat(filename, &fileInfo) != 0)
	{
		S3DX::log.message("Could not stat workshop file ", filename);

		SteamAPICall_t hSteamAPICall = m_pSteamRemoteStorage->UGCDownload ( pResult->m_hFile, 5 );
		m_CallbackDownloadComplete.Set ( hSteamAPICall, this, &CCloudAndWorkshop::OnDownloadComplete );
	}
	else
	{
		if ( pResult->m_rtimeUpdated > fileInfo.st_mtime )
		{
			S3DX::log.message(filename, " needs update! ", pResult->m_rtimeUpdated, " vs ", (int)fileInfo.st_mtime);
			SteamAPICall_t hSteamAPICall = m_pSteamRemoteStorage->UGCDownload ( pResult->m_hFile, 5 );
			m_CallbackDownloadComplete.Set ( hSteamAPICall, this, &CCloudAndWorkshop::OnDownloadComplete );
		}
		else
		{
			S3DX::log.message(filename, " is up to date, not re-downloading" );
			S3DX::user.sendEvent ( S3DX::application.getCurrentUser(), m_sAIModel, "onWorkshopDownloadComplete", true );
		}
	}
	
	delete[] filename;
}

void CCloudAndWorkshop::OnDownloadComplete ( RemoteStorageDownloadUGCResult_t *pResult, bool bIOFailure )
{
	if ( pResult->m_eResult != k_EResultOK || bIOFailure )
	{
		S3DX::log.message("Download did not complete ", pResult->m_eResult, " ", bIOFailure);
		S3DX::user.sendEvent ( S3DX::application.getCurrentUser(), m_sAIModel, "onWorkshopDownloadComplete", false );
		return;
	}

	char *fileBuffer = new char[pResult->m_nSizeInBytes];
	char *filename = new char[_MAX_PATH];
	
	// Construct path/filename
	strcpy(filename, m_sUGCDownloadLocation );
	strcat(filename, m_sFileID );
	strcat(filename, "-" );
	strcat(filename, pResult->m_pchFileName );

	// Read data into buffer
	m_pSteamRemoteStorage->UGCRead ( pResult->m_hFile, fileBuffer, pResult->m_nSizeInBytes, 0, k_EUGCRead_Close );
		
	// Write buffer to disk
	std::ofstream os (filename, std::ofstream::binary);
	os.write(fileBuffer, pResult->m_nSizeInBytes);

	// Clean up
	os.flush();
	os.close();
	delete[] fileBuffer;
	delete[] filename;

	S3DX::user.sendEvent ( S3DX::application.getCurrentUser(), m_sAIModel, "onWorkshopDownloadComplete", true );
}

void CCloudAndWorkshop::QueryUserUGCContent( EUserUGCList eQueryType, EUserUGCListSortOrder eSortOrder, uint64 nCreatorAppID, uint64 nConsumerAppID, int page )
{
	S3DX::log.message("Starting Query");

	UGCQueryHandle_t userQuery = m_pSteamUGC->CreateQueryUserUGCRequest(
		SteamUser()->GetSteamID().GetAccountID(), 
		eQueryType, 
		k_EUGCMatchingUGCType_Items,
		eSortOrder,
		nCreatorAppID,
		nConsumerAppID,
		page);

	SteamAPICall_t hSteamAPICall = m_pSteamUGC->SendQueryUGCRequest(userQuery);
	m_CallbackUGCQueryCompleted.Set( hSteamAPICall, this, &CCloudAndWorkshop::OnUGCQueryCompleted );
}

/* 
 * Open the specified item number in the steam browser.
 */
void CCloudAndWorkshop::OpenItemInBrowser( uint64 item )
{
	char *url = new char [200];
	strcpy ( url, "http://steamcommunity.com/sharedfiles/filedetails/?id=" );
	strcat ( url, toString(item).c_str() );
	SteamFriends()->ActivateGameOverlayToWebPage( url );
	delete[] url;
}