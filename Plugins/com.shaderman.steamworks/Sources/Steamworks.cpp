//-----------------------------------------------------------------------------
#include "PrecompiledHeader.h"
#include "Steamworks.h"
#include "steam_api.h"
#include "SteamMain.h"
#include <string> // used for string persistence voodoo
#include <time.h>
#if defined(_WIN32)
#include <direct.h>
#else
#include <sys/stat.h> //mkdir
#endif

//-----------------------------------------------------------------------------


#ifdef S3DX_DLL
	SteamworksAPI Steamworks ;
#endif

CSteamMain* SM;

//-----------------------------------------------------------------------------
//  Callbacks
//-----------------------------------------------------------------------------

int Callback_Steamworks_GetServerTime ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.GetServerTime" ) ;

    // Output Parameters 
    S3DX::AIVariable nDay ;
	S3DX::AIVariable nMonth ;
	S3DX::AIVariable nYear ;
	S3DX::AIVariable nHour ;
	S3DX::AIVariable nMinute ;
	S3DX::AIVariable nSecond ;

	if (SM->bInitialised){
		int32 time = SteamUtils()->GetServerRealTime() - 28800; // set to PST by subtracting 8 hours (GMT - 8)
		time_t timestamp = time;
		struct tm *ptm;
		ptm = gmtime(&timestamp);

		nDay = ptm->tm_mday;
		nMonth = ptm->tm_mon + 1;
		nYear = ptm->tm_year + 1900;
		nHour = ptm->tm_hour;
		nMinute = ptm->tm_min;
		nSecond = ptm->tm_sec;
	}
	else{
		nDay = 0;
		nMonth = 0;
		nYear = 0;
		nHour = 0;
		nMinute = 0;
		nSecond = 0;
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nDay ;
	_pOut[iReturnCount++] = nMonth ;
	_pOut[iReturnCount++] = nYear ;
	_pOut[iReturnCount++] = nHour ;
	_pOut[iReturnCount++] = nMinute ;
	_pOut[iReturnCount++] = nSecond ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_SubmitOrCreateScore ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.SubmitOrCreateScore" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sLeaderboard = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nScore       = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	SM->m_pLeaderboards->CreateOrSubmitScore(sLeaderboard.GetStringValue(), nScore);
    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_OpenItemInBrowser ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.OpenItemInBrowser" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sWorkshopItemID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
	
	SM->m_pCloudAndWorkshop->OpenItemInBrowser( atoi(sWorkshopItemID.GetStringValue()) );

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_MakeDir ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.MakeDir" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sFullPath = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	#if defined(_WIN32)
	_mkdir(sFullPath.GetStringValue());
	#else 
	mkdir(sFullPath.GetStringValue(), 0777);
	#endif

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_DownloadScores ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.DownloadScores" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
	S3DX::AIVariable sCallbackAI		 = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
	S3DX::AIVariable sCallbackHandler	 = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sLeaderboardName	 = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
	S3DX::AIVariable kLeaderboardRequest = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nStart              = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nEnd                = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	//Convert enums
	ELeaderboardDataRequest eRequest;

	/*
	ELeaderboardDataRequest
{
	k_ELeaderboardDataRequestGlobal = 0,
	k_ELeaderboardDataRequestGlobalAroundUser = 1,
	k_ELeaderboardDataRequestFriends = 2,
	k_ELeaderboardDataRequestUsers = 3
	*/

	switch ( (int)kLeaderboardRequest.GetNumberValue() )
	{
	case 0: eRequest = k_ELeaderboardDataRequestGlobal; break;
		case 1: eRequest = k_ELeaderboardDataRequestGlobalAroundUser; break;
		case 2: eRequest = k_ELeaderboardDataRequestFriends; break;
		case 3: eRequest = k_ELeaderboardDataRequestUsers; break;
		default: S3DX::log.warning("Invalid value for kLeaderboardRequest"); return 0;
	}

	SM->m_pLeaderboards->DownloadScores(sCallbackAI.GetStringValue(), sCallbackHandler.GetStringValue(), sLeaderboardName.GetStringValue(), eRequest, nStart, nEnd);

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_DeleteLocalWorkshopFile ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.DeleteLocalWorkshopFile" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sFullPathToFilename = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	std::remove( sFullPathToFilename.GetStringValue() );

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_PublishWorkshopFileUpdate ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.PublishWorkshopFileUpdate" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sWorkshopItemID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sFilePath       = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nAppID          = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sTitle          = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sDescription    = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
	S3DX::AIVariable sAI			  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
	S3DX::AIVariable sCallback		  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	SM->m_pCloudAndWorkshop->PublishFileUpdate ( atoi(sWorkshopItemID.GetStringValue()), sFilePath.GetStringValue(), nAppID.GetNumberValue(), sTitle.GetStringValue(), sDescription.GetStringValue(), sAI.GetStringValue(), sCallback.GetStringValue());

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_DownloadWorkshopFile ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.DownloadWorkshopFile" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sWorkshopItemID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	SM->m_pCloudAndWorkshop->DownloadUGCContent ( atoi(sWorkshopItemID.GetStringValue()) );

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_SetUGCDownloadLocation ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.SetUGCDownloadLocation" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sPath = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	SM->m_pCloudAndWorkshop->SetUGCDownloadLocation(sPath.GetStringValue());

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_QueryWorkshopUserContent ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.QueryWorkshopUserContent" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable kWorkshopQueryType = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable kWorkshopListSort  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nCreatorAppID      = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nConsumerAppID     = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nPage              = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	//Convert enums
	EUserUGCList eType;
	EUserUGCListSortOrder eSortOrder;

	switch ( (int)kWorkshopQueryType.GetNumberValue() )
	{
		case 0: eType = k_EUserUGCList_Published; break;
		case 1: eType = k_EUserUGCList_VotedOn; break;
		case 2: eType = k_EUserUGCList_VotedUp; break;
		case 3: eType = k_EUserUGCList_VotedDown; break;
		case 4: eType = k_EUserUGCList_WillVoteLater; break;
		case 5: eType = k_EUserUGCList_Favorited; break;
		case 6: eType = k_EUserUGCList_Subscribed; break;
		case 7: eType = k_EUserUGCList_UsedOrPlayed; break;
		case 8: eType = k_EUserUGCList_Followed; break;
		default: S3DX::log.warning("Invalid value for kWorkshopQueryType"); return 0;
	}

	switch ( (int)kWorkshopListSort.GetNumberValue() )
	{
		case 0: eSortOrder = k_EUserUGCListSortOrder_CreationOrderDesc; break;
		case 1: eSortOrder = k_EUserUGCListSortOrder_CreationOrderAsc; break;
		case 2: eSortOrder = k_EUserUGCListSortOrder_TitleAsc; break;
		case 3: eSortOrder = k_EUserUGCListSortOrder_LastUpdatedDesc; break;
		case 4: eSortOrder = k_EUserUGCListSortOrder_SubscriptionDateDesc; break;
		case 5: eSortOrder = k_EUserUGCListSortOrder_VoteScoreDesc; break;
		case 6: eSortOrder = k_EUserUGCListSortOrder_ForModeration; break;
		default: S3DX::log.warning("Invalid value for kWorkshopListSort"); return 0;
	}

	SM->m_pCloudAndWorkshop->QueryUserUGCContent( eType, eSortOrder, nCreatorAppID.GetNumberValue(), nConsumerAppID.GetNumberValue(), nPage.GetNumberValue() );

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_GetWorkshopUserVoteDetails ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.GetWorkshopUserVoteDetails" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sWorkshopItemID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	SM->m_pCloudAndWorkshop->GetUserPublishedItemVoteDetails( atoi(sWorkshopItemID.GetStringValue()) );
	
    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_SetWorkshopUserVote ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.SetWorkshopUserVote" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sWorkshopItemID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable bVotePositive   = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	SM->m_pCloudAndWorkshop->UpdateUserPublishedItemVote ( atoi(sWorkshopItemID.GetStringValue()), bVotePositive.GetBooleanValue() );

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_GetWorkshopVoteDetails ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.GetWorkshopVoteDetails" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sWorkshopItemID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	SM->m_pCloudAndWorkshop->GetPublishedItemVoteDetails( atoi(sWorkshopItemID.GetStringValue()) );

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_SetWorkshopFileAction ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.SetWorkshopFileAction" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sWorkshopItemID     = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable kWorkshopFileAction = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	EWorkshopFileAction action;

	// Presumably this enum will grow larger as steam sdk is updated
	if (kWorkshopFileAction == 0)
		action = k_EWorkshopFileActionPlayed;
	else if (kWorkshopFileAction == 1)
		action = k_EWorkshopFileActionCompleted;
	else
	{
		S3DX::log.warning ( "Unknown kWorkshopFileAction constant: ", kWorkshopFileAction );
		return 0;
	}
 
	SM->m_pCloudAndWorkshop->SetPublishedFileAction ( atoi(sWorkshopItemID.GetStringValue()), action );

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_SubscribeToWorkshopFile ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.SubscribeToWorkshopFile" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sWorkshopItemID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	SM->m_pCloudAndWorkshop->SubscribeToFile ( atoi(sWorkshopItemID.GetStringValue()) );

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_UnSubscribeFromWorkshopFile ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.UnSubscribeFromWorkshopFile" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sWorkshopItemID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	SM->m_pCloudAndWorkshop->UnsubscribeFromFile ( atoi(sWorkshopItemID.GetStringValue()) );

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_PublishWorkshopFile ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.PublishWorkshopFile" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sFilePath        = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nAppID           = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sTitle           = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sDescription     = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
	S3DX::AIVariable sAI			  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
	S3DX::AIVariable sCallback		  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	S3DX::log.warning("Steamworks: Publishing workshop file ", sFilePath );

	SM->m_pCloudAndWorkshop->PublishFile ( sFilePath.GetStringValue(), nAppID.GetNumberValue(), sTitle.GetStringValue(), sDescription.GetStringValue(), sAI.GetStringValue(), sCallback.GetStringValue());

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_UploadScore ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.UploadScore" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nScore = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOk ;

	bOk = SM->m_pLeaderboards->UploadScore(nScore.GetNumberValue());

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOk ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_FindLeaderboard ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.FindLeaderboard" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sLeaderboardName = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

	SM->m_pLeaderboards->FindLeaderboard(sLeaderboardName.GetStringValue());

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_ResetAllStats ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.ResetAllStats" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable bAchievementsToo = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOk ;

	bOk = SM->m_pStatsAndAchievements->ResetAllStats(bAchievementsToo);

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOk ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_SetStat ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.SetStat" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sStatName  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nStatValue = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable kStatType  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOk ;

	bOk = SM->m_pStatsAndAchievements->SetStat(sStatName.GetStringValue(), nStatValue, kStatType);

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOk ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_UpdateAvgRateStat ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.UpdateAvgRateStat" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sStatName         = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nCountThisSession = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable nSessionLength    = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOk ;

	bOk = SM->m_pStatsAndAchievements->UpdateAvgRateStat(sStatName.GetStringValue(), nCountThisSession, nSessionLength);

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOk ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_GetStat ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.GetStat" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sStatName = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable kStatType = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nStatValue ;

	if ( kStatType == Steamworks.kStatTypeInt || kStatType == Steamworks.kStatTypeFloat || kStatType == Steamworks.kStatTypeAvgrate ) {
		nStatValue.SetNumberValue(SM->m_pStatsAndAchievements->GetStat(sStatName.GetStringValue(), kStatType));
	} else {
		S3DX::log.warning("Steamworks: Unknown stat kStatType, please check your code");
		nStatValue = 0;
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nStatValue ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_Init ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.Init" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sAIModel = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOk ;

	SM = new CSteamMain();
	bOk = SM->Init(sAIModel.GetStringValue());

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOk ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_GetNumAchievements ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.GetNumAchievements" ) ;

    // Output Parameters 
    S3DX::AIVariable nAchievements ;

	nAchievements = SM->m_pStatsAndAchievements->GetNumAchievements();

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nAchievements ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_GetNextMostAchievedAchievementInfo ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.GetNextMostAchievedAchievementInfo" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable nIndex = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nNewIndex ;
    S3DX::AIVariable sAchievementID ;
    S3DX::AIVariable nPercent ;
    S3DX::AIVariable bAchieved ;

	MostAchievedAchievementInfo* MAAI = SM->m_pStatsAndAchievements->GetNextMostAchievedAchievementInfo(nIndex);

	nNewIndex = MAAI->m_index;

	// persistence voodoo
	static char tmp [128];
	S3DX_MEMCPY( tmp, MAAI->m_name.c_str(), MAAI->m_name.size() + 1 ); // copy the string into a char array
	sAchievementID.SetStringValue(tmp);

	nPercent = MAAI->m_percent;
	bAchieved = MAAI->m_achieved;

	delete MAAI;

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nNewIndex ;
    _pOut[iReturnCount++] = sAchievementID ;
    _pOut[iReturnCount++] = nPercent ;
    _pOut[iReturnCount++] = bAchieved ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_GetMostAchievedAchievementInfo ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.GetMostAchievedAchievementInfo" ) ;

    // Output Parameters 
    S3DX::AIVariable nIndex ;
    S3DX::AIVariable sAchievementID ;
    S3DX::AIVariable nPercent ;
    S3DX::AIVariable bAchieved ;

	MostAchievedAchievementInfo* MAAI = SM->m_pStatsAndAchievements->GetMostAchievedAchievementInfo();

	nIndex = MAAI->m_index;

	// persistence voodoo
	static char tmp [128];
	S3DX_MEMCPY( tmp, MAAI->m_name.c_str(), MAAI->m_name.size() + 1 ); // copy the string into a char array
	sAchievementID.SetStringValue(tmp);

	nPercent = MAAI->m_percent;
	bAchieved = MAAI->m_achieved;

	delete MAAI;

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nIndex ;
    _pOut[iReturnCount++] = sAchievementID ;
    _pOut[iReturnCount++] = nPercent ;
    _pOut[iReturnCount++] = bAchieved ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_GetAchievementAndUnlockTime ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.GetAchievementAndUnlockTime" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sAchievementID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bAchieved ;
    S3DX::AIVariable nUnlockTime ;

	std::pair<bool, uint32> pair = SM->m_pStatsAndAchievements->GetAchievementAndUnlockTime(sAchievementID.GetStringValue());
	bAchieved = pair.first;
	nUnlockTime = pair.second;

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bAchieved ;
    _pOut[iReturnCount++] = nUnlockTime ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_GetAchievementAchievedPercent ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.GetAchievementAchievedPercent" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sAchievementID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nPercent ;

	nPercent = SM->m_pStatsAndAchievements->GetAchievementAchievedPercent(sAchievementID.GetStringValue());

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nPercent ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_ClearAchievement ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.ClearAchievement" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sAchievementID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOk ;

	S3DX::log.message("Steamworks: Clearing achievement ", sAchievementID);
	bOk = SM->m_pStatsAndAchievements->ClearAchievement(sAchievementID.GetStringValue());

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOk ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_StoreStats ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.StoreStats" ) ;

    // Output Parameters 
    S3DX::AIVariable bOk ;

	bOk = SM->m_pStatsAndAchievements->StoreStats();

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOk ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_SetAchievement ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.SetAchievement" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sAchievementID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOk ;

	S3DX::log.message("Steamworks: Setting achievement ", sAchievementID);
	bOk = SM->m_pStatsAndAchievements->SetAchievement(sAchievementID.GetStringValue());

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOk ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_GetAchievementIcon ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.GetAchievementIcon" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sAchievementID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable nIcon ;

	nIcon = (float)SM->m_pStatsAndAchievements->GetAchievementIcon(sAchievementID.GetStringValue());

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = nIcon ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_GetAchievementDescription ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.GetAchievementDescription" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sAchievementID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable sDescription ;

	sDescription.SetStringValue(SM->m_pStatsAndAchievements->GetAchievementDescription(sAchievementID.GetStringValue()));

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = sDescription ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_GetAchievementName ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.GetAchievementName" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sAchievementID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable sName ;

	if ( NULL != SM->m_pStatsAndAchievements ) {
		sName.SetStringValue(SM->m_pStatsAndAchievements->GetAchievementName(sAchievementID.GetStringValue()));
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = sName ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_GetAchievement ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.GetAchievement" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sAchievementName = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bAchieved ;

	if ( NULL != SM->m_pStatsAndAchievements ) {
		bAchieved = SM->m_pStatsAndAchievements->GetAchievement(sAchievementName.GetStringValue());
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bAchieved ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_GetLocalPlayerName ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.GetLocalPlayerName" ) ;

    // Output Parameters 
    S3DX::AIVariable sPlayerName ;

	sPlayerName.SetStringValue(SM->GetLocalPlayerName());

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = sPlayerName ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_Steamworks_RunCallbacks ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "Steamworks.RunCallbacks" ) ;

	SM->RunCallbacks();

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------
//  Constructor / Destructor
//-----------------------------------------------------------------------------

SteamworksPackage::SteamworksPackage ( )
{
#ifdef S3DX_DLL
    Steamworks.pfn_Steamworks_GetServerTime                      = Callback_Steamworks_GetServerTime                      ;
    Steamworks.pfn_Steamworks_SubmitOrCreateScore                = Callback_Steamworks_SubmitOrCreateScore                ;
    Steamworks.pfn_Steamworks_OpenItemInBrowser                  = Callback_Steamworks_OpenItemInBrowser                  ;
    Steamworks.pfn_Steamworks_MakeDir                            = Callback_Steamworks_MakeDir                            ;
    Steamworks.pfn_Steamworks_DownloadScores                     = Callback_Steamworks_DownloadScores                     ;
    Steamworks.kLeaderboardRequestGlobal             = 0 ; 
    Steamworks.kLeaderboardRequestGlobalAroundUser   = 1 ; 
    Steamworks.kLeaderboardRequestFriends            = 2 ; 
    Steamworks.kLeaderboardRequestUsers              = 3 ; 
    Steamworks.pfn_Steamworks_DeleteLocalWorkshopFile            = Callback_Steamworks_DeleteLocalWorkshopFile            ;
    Steamworks.pfn_Steamworks_PublishWorkshopFileUpdate          = Callback_Steamworks_PublishWorkshopFileUpdate          ;
    Steamworks.pfn_Steamworks_DownloadWorkshopFile               = Callback_Steamworks_DownloadWorkshopFile               ;
    Steamworks.pfn_Steamworks_SetUGCDownloadLocation             = Callback_Steamworks_SetUGCDownloadLocation             ;
    Steamworks.pfn_Steamworks_QueryWorkshopUserContent           = Callback_Steamworks_QueryWorkshopUserContent           ;
    Steamworks.kWorkshopListSortCreationDesc         = 0 ; 
    Steamworks.kWorkshopListSortCreationAsc          = 1 ; 
    Steamworks.kWorkshopListSortTitleAsc             = 2 ; 
    Steamworks.kWorkshopListSortLastUpdatedDesc      = 3 ; 
    Steamworks.kWorkshopListSortSubscriptionDateDesc = 4 ; 
    Steamworks.kWorkshopListSortVoteScoreDesc        = 5 ; 
    Steamworks.kWorkshopListSortForModeration        = 6 ; 
    Steamworks.kWorkshopQueryPublished      = 0 ; 
    Steamworks.kWorkshopQueryVotedOn        = 1 ; 
    Steamworks.kWorkshopQueryVotedUp        = 2 ; 
    Steamworks.kWorkshopQueryVotedDown      = 3 ; 
    Steamworks.kWorkshopQueryVoteLater      = 4 ; 
    Steamworks.kWorkshopQueryFavorited      = 5 ; 
    Steamworks.kWorkshopQuerySubscribed     = 6 ; 
    Steamworks.kWorkshopQueryUsedOrPlayed   = 7 ; 
    Steamworks.kWorkshopQueryFollowed       = 8 ; 
    Steamworks.pfn_Steamworks_GetWorkshopUserVoteDetails         = Callback_Steamworks_GetWorkshopUserVoteDetails         ;
    Steamworks.pfn_Steamworks_SetWorkshopUserVote                = Callback_Steamworks_SetWorkshopUserVote                ;
    Steamworks.pfn_Steamworks_GetWorkshopVoteDetails             = Callback_Steamworks_GetWorkshopVoteDetails             ;
    Steamworks.pfn_Steamworks_SetWorkshopFileAction              = Callback_Steamworks_SetWorkshopFileAction              ;
    Steamworks.kWorkshopFileActionPlayed    = 0 ; 
    Steamworks.kWorkshopFileActionCompleted = 1 ; 
    Steamworks.pfn_Steamworks_SubscribeToWorkshopFile            = Callback_Steamworks_SubscribeToWorkshopFile            ;
    Steamworks.pfn_Steamworks_UnSubscribeFromWorkshopFile        = Callback_Steamworks_UnSubscribeFromWorkshopFile        ;
    Steamworks.pfn_Steamworks_PublishWorkshopFile                = Callback_Steamworks_PublishWorkshopFile                ;
    Steamworks.pfn_Steamworks_UploadScore                        = Callback_Steamworks_UploadScore                        ;
    Steamworks.pfn_Steamworks_FindLeaderboard                    = Callback_Steamworks_FindLeaderboard                    ;
    Steamworks.pfn_Steamworks_ResetAllStats                      = Callback_Steamworks_ResetAllStats                      ;
    Steamworks.pfn_Steamworks_SetStat                            = Callback_Steamworks_SetStat                            ;
    Steamworks.pfn_Steamworks_UpdateAvgRateStat                  = Callback_Steamworks_UpdateAvgRateStat                  ;
    Steamworks.pfn_Steamworks_GetStat                            = Callback_Steamworks_GetStat                            ;
    Steamworks.kStatTypeInt   = 0 ; 
    Steamworks.kStatTypeFloat = 1 ; 
    Steamworks.kStatTypeAvgrate = 2 ; 
    Steamworks.pfn_Steamworks_Init                               = Callback_Steamworks_Init                               ;
    Steamworks.pfn_Steamworks_GetNumAchievements                 = Callback_Steamworks_GetNumAchievements                 ;
    Steamworks.pfn_Steamworks_GetNextMostAchievedAchievementInfo  = Callback_Steamworks_GetNextMostAchievedAchievementInfo  ;
    Steamworks.pfn_Steamworks_GetMostAchievedAchievementInfo  = Callback_Steamworks_GetMostAchievedAchievementInfo  ;
    Steamworks.pfn_Steamworks_GetAchievementAndUnlockTime   = Callback_Steamworks_GetAchievementAndUnlockTime   ;
    Steamworks.pfn_Steamworks_GetAchievementAchievedPercent = Callback_Steamworks_GetAchievementAchievedPercent ;
    Steamworks.pfn_Steamworks_ClearAchievement          = Callback_Steamworks_ClearAchievement          ;
    Steamworks.pfn_Steamworks_StoreStats                = Callback_Steamworks_StoreStats                ;
    Steamworks.pfn_Steamworks_SetAchievement            = Callback_Steamworks_SetAchievement            ;
    Steamworks.pfn_Steamworks_GetAchievementIcon        = Callback_Steamworks_GetAchievementIcon        ;
    Steamworks.pfn_Steamworks_GetAchievementDescription = Callback_Steamworks_GetAchievementDescription ;
    Steamworks.pfn_Steamworks_GetAchievementName = Callback_Steamworks_GetAchievementName ;
    Steamworks.pfn_Steamworks_GetAchievement     = Callback_Steamworks_GetAchievement     ;
    Steamworks.pfn_Steamworks_GetLocalPlayerName = Callback_Steamworks_GetLocalPlayerName ;
    Steamworks.pfn_Steamworks_RunCallbacks = Callback_Steamworks_RunCallbacks ;
	
#endif
}

//-----------------------------------------------------------------------------

SteamworksPackage::~SteamworksPackage ( )
{

}

//-----------------------------------------------------------------------------
//  Functions table
//-----------------------------------------------------------------------------

static S3DX::AIFunction aMyFunctions [ ] =
{
    { "GetServerTime"                     , Callback_Steamworks_GetServerTime                     , "nDay, nMonth, nYear, nHour, nMinute, nSecond"                                         , ""                                                                           , "Steam server time - in PST, number of seconds since January 1, 1970 (i.e unix time)"                                                                                                                                                                                                                                 , 0 }, 
    { "SubmitOrCreateScore"               , Callback_Steamworks_SubmitOrCreateScore               , ""                                              , "sLeaderboard, nScore"                                                       , "Submits a new score, creating the leaderboard if it doesn't exist."                                                                                                                                                                                                                                                  , 0 }, 
    { "OpenItemInBrowser"                 , Callback_Steamworks_OpenItemInBrowser                 , ""                                              , "sWorkshopItemID"                                                            , "Opens a workshop item in the steam overlay."                                                                                                                                                                                                                                                                         , 0 }, 
    { "MakeDir"                           , Callback_Steamworks_MakeDir                           , ""                                              , "sFullPath"                                                                  , "Makes the specified directory if it doesn't exist."                                                                                                                                                                                                                                                                  , 0 }, 
    { "DownloadScores"                    , Callback_Steamworks_DownloadScores                    , ""                                              , "sAI, sHandler, sLeaderboardName, kLeaderboardRequest, nStart, nEnd"                                          , "Downloads scores from the specified leaderboard. When querying global entries, start and end provide a range of [1, TotalEntries]. For GlobalAroundUser, start/end specify how many entries around the user to get. For friends, the parameters are not used. Calls back to the specified user AI and handler"                                              , 0 }, 
    { "DeleteLocalWorkshopFile"           , Callback_Steamworks_DeleteLocalWorkshopFile           , ""                                              , "sFullPathToFilename"                                                        , "Deletes the local file."                                                                                                                                                                                                                                                                                             , 0 }, 
    { "PublishWorkshopFileUpdate"         , Callback_Steamworks_PublishWorkshopFileUpdate         , ""                                              , "sWorkshopItemID, sFilePath, nAppID, sTitle, sDescription, sAI, sCallback"                   , "Updates the specified workshop ID with the necessary data. Calls back to the supplied AI and handler."                                                                                                                                                                                                                                                          , 0 }, 
    { "DownloadWorkshopFile"              , Callback_Steamworks_DownloadWorkshopFile              , ""                                              , "sWorkshopItemID"                                                            , "Initiates a download for a workshop item."                                                                                                                                                                                                                                                                           , 0 }, 
    { "SetUGCDownloadLocation"            , Callback_Steamworks_SetUGCDownloadLocation            , ""                                              , "sPath"                                                                      , "Sets the location where UGC should be downloaded to."                                                                                                                                                                                                                                                                , 0 }, 
    { "QueryWorkshopUserContent"          , Callback_Steamworks_QueryWorkshopUserContent          , ""                                              , "kWorkshopQueryType, kWorkshopListSort, nCreatorAppID, nConsumerAppID, nPage", "Submit a query for workshop content by specifying content type, sorting, the creator/consumer app ID and the page number. Results are returned in onQueryWorkshopUserContent."                                                                                                                                       , 0 }, 
    { "GetWorkshopUserVoteDetails"        , Callback_Steamworks_GetWorkshopUserVoteDetails        , ""                                              , "sWorkshopItemID"                             , "Request user voting information for the specified workshop item. The onWorkshopUserItemVoteDetails handler will be called with the results."                                                                                                                                                                         , 0 }, 
    { "SetWorkshopUserVote"               , Callback_Steamworks_SetWorkshopUserVote               , ""                                              , "sWorkshopItemID, bVotePositive"              , "Vote a workshop item up or down."                                                                                                                                                                                                                                                                                    , 0 }, 
    { "GetWorkshopVoteDetails"            , Callback_Steamworks_GetWorkshopVoteDetails            , ""                                              , "sWorkshopItemID"                             , "Request voting information for the specified workshop item. The onWorkshopItemVoteDetails handler will be called with the results."                                                                                                                                                                                  , 0 }, 
    { "SetWorkshopFileAction"             , Callback_Steamworks_SetWorkshopFileAction             , ""                                              , "sWorkshopItemID, kWorkshopFileAction"        , "Sets the specified action on the workshop item"                                                                                                                                                                                                                                                                      , 0 }, 
    { "SubscribeToWorkshopFile"           , Callback_Steamworks_SubscribeToWorkshopFile           , ""                                              , "sWorkshopItemID"                             , "Subscribes to the given workshop file ID"                                                                                                                                                                                                                                                                            , 0 }, 
    { "UnSubscribeFromWorkshopFile"       , Callback_Steamworks_UnSubscribeFromWorkshopFile       , ""                                              , "sWorkshopItemID"                             , "Unsubscribes from the given workshop file ID"                                                                                                                                                                                                                                                                        , 0 }, 
    { "PublishWorkshopFile"               , Callback_Steamworks_PublishWorkshopFile               , ""                                              , "sFilePath, nAppID, sTitle, sDescription, sAI, sCallback", "Uploads the specified file to the steam workshop. Calls back to the supplied AI and handler."                                                                                                                                                                                                                                                                   , 0 }, 
    { "UploadScore"                       , Callback_Steamworks_UploadScore                       , "bOk"                                           , "nScore"                                      , "Uploads the specified score to the currently selected leaderboard."                                                                                                                                                                                                                                                  , 0 }, 
    { "FindLeaderboard"                   , Callback_Steamworks_FindLeaderboard                   , ""                                              , "sLeaderboardName"                            , "This call needs to be made before you can retrieve or set leaderboard entries. The handler onLeaderboardFound will be called with the results."                                                                                                                                                                      , 0 }, 
    { "ResetAllStats"                     , Callback_Steamworks_ResetAllStats                     , "bOk"                                           , "bAchievementsToo"                            , "Call this function to wipe stats for an account, with bAchievementsToo set to true to wipe achievements as well."                                                                                                                                                                                                    , 0 }, 
    { "SetStat"                           , Callback_Steamworks_SetStat                           , "bOk"                                           , "sStatName, nStatValue, kStatType"            , "Use this function to set a stat."                                                                                                                                                                                                                                                                                    , 0 }, 
    { "UpdateAvgRateStat"                 , Callback_Steamworks_UpdateAvgRateStat                 , "bOk"                                           , "sStatName, nCountThisSession, nSessionLength", "Call this function at appropriate points during your game passing the name of the stat, the number of points the player earned since the last call to UpdateAvgRateStat and the amount of game time since the last call to UpdateAvgRateStat. The unit should be the same as the unit on the stat's Window property.", 0 }, 
    { "GetStat"                           , Callback_Steamworks_GetStat                           , "nStatValue"                                    , "sStatName, kStatType", "Use this function to get a stat."                                                                                                                                                                      , 0 }, 
    { "Init"                              , Callback_Steamworks_Init                              , "bOk"                                           , "sAIModel"      , "Initialise Steamworks. Requires the calling AI model name as parameter. Returns true on success, false on failure."                                                                                    , 0 }, 
    { "GetNumAchievements"                , Callback_Steamworks_GetNumAchievements                , "nAchievements"                                 , ""              , "Returns the number of achievements."                                                                                                                                                                   , 0 }, 
    { "GetNextMostAchievedAchievementInfo" , Callback_Steamworks_GetNextMostAchievedAchievementInfo , "nNewIndex, sAchievementID, nPercent, bAchieved", "nIndex"        , "Get the info for the next most achieved achievement."                                                                                                                                                  , 0 }, 
    { "GetMostAchievedAchievementInfo" , Callback_Steamworks_GetMostAchievedAchievementInfo , "nIndex, sAchievementID, nPercent, bAchieved", ""              , "Returns an index for a following function call, the achievement ID of the most achieved achievement, the percentage and true as last value if the player got the achievement already, otherwise false.", 0 }, 
    { "GetAchievementAndUnlockTime"  , Callback_Steamworks_GetAchievementAndUnlockTime  , "bAchieved, nUnlockTime", "sAchievementID", "Return true as first value if the player got the achievement already, otherwise false. The second return value contains the unlock time.", 0 }, 
    { "GetAchievementAchievedPercent", Callback_Steamworks_GetAchievementAchievedPercent, "nPercent"    , "sAchievementID", "Get the achieved percent for an achievement."                           , 0 }, 
    { "ClearAchievement"         , Callback_Steamworks_ClearAchievement         , "bOk"         , "sAchievementID", "Clear an achievement."                                                  , 0 }, 
    { "StoreStats"               , Callback_Steamworks_StoreStats               , "bOk"         , ""              , "At appropriate points within your game (i.e. checkpoints, level transitions), call this function to upload the changes. The handler onUserStatsStored ( ) will be called when that is done."                                          , 0 }, 
    { "SetAchievement"           , Callback_Steamworks_SetAchievement           , "bOk"         , "sAchievementID", "Set an achievement."                                                    , 0 }, 
    { "GetAchievementIcon"       , Callback_Steamworks_GetAchievementIcon       , "nIcon"       , "sAchievementID", "Returns the number of the achievement icon."                            , 0 }, 
    { "GetAchievementDescription", Callback_Steamworks_GetAchievementDescription, "sDescription", "sAchievementID", "Returns the description of the achievement."                            , 0 }, 
    { "GetAchievementName", Callback_Steamworks_GetAchievementName, "sName"      , "sAchievementID", "Returns the human-readable name of the achievement."                    , 0 }, 
    { "GetAchievement"    , Callback_Steamworks_GetAchievement    , "bAchieved"  , "sAchievementID", "Return true if the player got the achievement already, otherwise false.", 0 }, 
    { "GetLocalPlayerName", Callback_Steamworks_GetLocalPlayerName, "sPlayerName", "", "Returns the local player name."                                   , 0 }, 
    { "RunCallbacks", Callback_Steamworks_RunCallbacks, ""   , "", "Call this function every frame to dispatch callbacks."            , 0 }
    //{ NULL, NULL, NULL, NULL, NULL, 0}
} ;

//-----------------------------------------------------------------------------
//  Constants table
//-----------------------------------------------------------------------------

static S3DX::AIConstant aMyConstants [ ] =
{
    { "kLeaderboardRequestGlobal"            , 0, "Global scores"                                                                                       , 0 }, 
    { "kLeaderboardRequestGlobalAroundUser"  , 1, "Global scores around the user (used with min/max)"                                                   , 0 }, 
    { "kLeaderboardRequestFriends"           , 2, "Scores of friends only"                                                                              , 0 }, 
    { "kLeaderboardRequestUsers"             , 3, "No clue what this is for, the steamdocs don't know either but it's in the enum so I'm putting it in.", 0 }, 
    { "kWorkshopListSortCreationDesc"        , 0, "Sort by creation order desc"                                              , 0 }, 
    { "kWorkshopListSortCreationAsc"         , 1, "Sort by creation order asc"                                               , 0 }, 
    { "kWorkshopListSortTitleAsc"            , 2, "Sort by title asc"                                                        , 0 }, 
    { "kWorkshopListSortLastUpdatedDesc"     , 3, "Sort by last updated desc"                                                , 0 }, 
    { "kWorkshopListSortSubscriptionDateDesc", 4, "Sort by subscription date desc"                                            , 0 }, 
    { "kWorkshopListSortVoteScoreDesc"       , 5, "Sort by voting score desc"                                                 , 0 }, 
    { "kWorkshopListSortForModeration"       , 6, "Sort by moderation flag"                                                   , 0 }, 
    { "kWorkshopQueryPublished"     , 0, "Content that is published"                                                 , 0 }, 
    { "kWorkshopQueryVotedOn"       , 1, "Content that has been voted on"                                            , 0 }, 
    { "kWorkshopQueryVotedUp"       , 2, "Content that has been voted up"                                            , 0 }, 
    { "kWorkshopQueryVotedDown"     , 3, "Content that has been voted down"                                          , 0 }, 
    { "kWorkshopQueryVoteLater"     , 4, "Content that has been marked to vote on later"                             , 0 }, 
    { "kWorkshopQueryFavorited"     , 5, "Content that has been favorited"                                           , 0 }, 
    { "kWorkshopQuerySubscribed"    , 6, "Content that has been subscribed to"                                       , 0 }, 
    { "kWorkshopQueryUsedOrPlayed"  , 7, "Content that has been used/played"                                         , 0 }, 
    { "kWorkshopQueryFollowed"      , 8, "Content that has been followed"                                            , 0 }, 
    { "kWorkshopFileActionPlayed"   , 0, "Used to indicate if a piece of workshop content has been played or not."   , 0 }, 
    { "kWorkshopFileActionCompleted", 1, "Used to indicate if a piece of workshop content has been completed or not.", 0 }, 
    { "kStatTypeInt"  , 0, "Use this constant to request a integer stat.", 0 }, 
    { "kStatTypeFloat", 1, "Use this constant to request a float stat."  , 0 },	
	{ "kStatTypeAvgrate", 2, "Use this constant to request a avgrate stat.", 0 }
    //{ NULL, 0, NULL, 0}
} ;

//-----------------------------------------------------------------------------
//  Accessors
//-----------------------------------------------------------------------------

const char *SteamworksPackage::GetName ( ) const
{
    return "Steamworks" ;
}

//-----------------------------------------------------------------------------

S3DX::uint32 SteamworksPackage::GetFunctionCount ( ) const
{
	if ( aMyFunctions[0].pName == NULL )
	{
		return 0 ;
	}
	else
	{
		return sizeof( aMyFunctions ) / sizeof( S3DX::AIFunction ) ;
	}
}

//-----------------------------------------------------------------------------

S3DX::uint32 SteamworksPackage::GetConstantCount ( ) const
{
	if ( aMyConstants[0].pName == NULL )
	{
		return 0 ;
	}
	else
	{
		return sizeof( aMyConstants ) / sizeof( S3DX::AIConstant ) ;
	}
}

//-----------------------------------------------------------------------------

const S3DX::AIFunction *SteamworksPackage::GetFunctionAt ( S3DX::uint32 _iIndex ) const
{
    return &aMyFunctions[ _iIndex ] ;
}

//-----------------------------------------------------------------------------

const S3DX::AIConstant *SteamworksPackage::GetConstantAt ( S3DX::uint32 _iIndex ) const
{
    return &aMyConstants[ _iIndex ] ;
}
