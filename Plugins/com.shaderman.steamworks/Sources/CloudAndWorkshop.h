#ifndef __CloudAndWorkshop_h__
#define __CloudAndWorkshop_h__

#include "ISteamRemoteStorage.h"
#include "steam_api.h"
#include "ISteamUGC.h"
#include <string>

class CCloudAndWorkshop
{
public:
	CCloudAndWorkshop (const char* sAIModel);
	
	std::string toString(int i);
	void SetUGCDownloadLocation( const char *);
	void OpenItemInBrowser(uint64 item );
	void SubscribeToFile ( uint64 item );
	void UnsubscribeFromFile ( uint64 item );
	void SetPublishedFileAction ( uint64 item, EWorkshopFileAction eAction);
	
	//
	// Querying
	//
	void QueryUserUGCContent ( EUserUGCList eQueryType, EUserUGCListSortOrder eSortOrder, uint64 nCreatorAppID, uint64 nConsumerAppID, int page );
	void OnUGCQueryCompleted ( SteamUGCQueryCompleted_t * pResult, bool bIOFailure );
	CCallResult<CCloudAndWorkshop, SteamUGCQueryCompleted_t> m_CallbackUGCQueryCompleted;

	// 
	// Downloading
	//
	void DownloadUGCContent ( uint64 item );
	void OnDownloadUGCContent ( RemoteStorageGetPublishedFileDetailsResult_t *pResult, bool bIOFailure );
	void OnDownloadComplete ( RemoteStorageDownloadUGCResult_t *pResult, bool bIOFailure );
	CCallResult<CCloudAndWorkshop, RemoteStorageGetPublishedFileDetailsResult_t> m_CallbackDownloadContent;
	CCallResult<CCloudAndWorkshop, RemoteStorageDownloadUGCResult_t> m_CallbackDownloadComplete;

	//
	// Voting
	//
	void GetPublishedItemVoteDetails ( uint64 item );
	void GetUserPublishedItemVoteDetails ( uint64 item );
	void UpdateUserPublishedItemVote ( uint64 item, bool vote );

	void OnGetPublishedItemVoteDetails ( RemoteStorageGetPublishedItemVoteDetailsResult_t *pResult, bool bIOFailure );
	CCallResult<CCloudAndWorkshop, RemoteStorageGetPublishedItemVoteDetailsResult_t> m_callResultGetVoteDetails;

	void OnGetUserPublishedItemVoteDetails ( RemoteStorageUserVoteDetails_t *pResult, bool bIOFailure );
	CCallResult<CCloudAndWorkshop, RemoteStorageUserVoteDetails_t> m_callResultGetUserVoteDetails;

	//
	// Publishing
	//
	void SetCallback ( const char *ai, const char *handler);
	void PublishFile ( const char* sFile, int appID, const char* sTitle, const char* sDesc, const char* sAI, const char* sCallback );
	void PublishFileUpdate ( uint64 itemID, const char* sFile, int appID, const char* sTitle, const char* sDesc, const char* sAI, const char* sCallback );
	void OnFileSharePublishToWorkshop( RemoteStorageFileShareResult_t *pResult, bool bIOFailure );
	CCallResult<CCloudAndWorkshop, RemoteStorageFileShareResult_t> m_callResultWriteFile;

	void OnPublishFileResult( RemoteStoragePublishFileResult_t *pResult, bool bIOFailure );
	CCallResult<CCloudAndWorkshop, RemoteStoragePublishFileResult_t > m_callResultPublishFile;

	void OnPublishedFileUpdateRequest ( RemoteStorageUpdatePublishedFileResult_t  *pResult, bool bIOFailure );
	CCallResult<CCloudAndWorkshop, RemoteStorageUpdatePublishedFileResult_t  > m_callResultPublishFileUpdate;

	STEAM_CALLBACK( CCloudAndWorkshop, OnFileSubscribed, RemoteStoragePublishedFileSubscribed_t, m_CallbackFileSubscribed );
	STEAM_CALLBACK( CCloudAndWorkshop, OnFileUnsubscribed, RemoteStoragePublishedFileUnsubscribed_t , m_CallbackFileUnsubscribed );

private:
	const char* m_sAIModel;
	static char m_sUGCDownloadLocation[255];
	static char m_sFileID [30];
	static char mFile [100];
	static char m_sPublishAICallback [100];
	static char m_sPublishHandlerCallback [100];
	static AppId_t mAppID;
	static char mTitle [90];
	static char mDescription [8000];
	static SteamUGCDetails_t mTempDetails;

	bool WriteFile(const char *);

	ISteamRemoteStorage *m_pSteamRemoteStorage;
	ISteamUGC *m_pSteamUGC;
};

//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------