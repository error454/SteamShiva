//-----------------------------------------------------------------------------
#ifndef __Steamworks_h__
#define __Steamworks_h__
//-----------------------------------------------------------------------------
#include "S3DXAIPackage.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Package declaration
//-----------------------------------------------------------------------------
class SteamworksPackage : public S3DX::AIPackage
{
public :

    //-------------------------------------------------------------------------
    //  Constructor / Destructor
	//-------------------------------------------------------------------------

	SteamworksPackage         ( ) ;
                               ~SteamworksPackage         ( ) ;

	//-------------------------------------------------------------------------
    //  Accessors
	//-------------------------------------------------------------------------

    const   char               *GetName             ( ) const ;
            S3DX::uint32        GetFunctionCount    ( ) const ;
            S3DX::uint32        GetConstantCount    ( ) const ;
    const   S3DX::AIFunction   *GetFunctionAt       ( S3DX::uint32 _iIndex ) const ;
    const   S3DX::AIConstant   *GetConstantAt       ( S3DX::uint32 _iIndex ) const ;

} ;

//-----------------------------------------------------------------------------
// Package API declaration
//-----------------------------------------------------------------------------
class SteamworksAPI
{
public :

    //-------------------------------------------------------------------------
    //  API Constructor
	//-------------------------------------------------------------------------
                                SteamworksAPI       ( ) 
                                {
                                    pfn_Steamworks_sconPulse                          = NULL ;
                                    pfn_Steamworks_sconShowBindingPanel               = NULL ;
                                    pfn_Steamworks_sconSetActionSet                   = NULL ;
                                    pfn_Steamworks_sconGetActionSet                   = NULL ;
                                    pfn_Steamworks_sconGetDigitalActionOrigin         = NULL ;
                                    pfn_Steamworks_sconGetAnalogActionOrigin          = NULL ;
                                    pfn_Steamworks_sconLoop                           = NULL ;
                                    pfn_Steamworks_sconSetAnalogActions               = NULL ;
                                    pfn_Steamworks_sconSetDigitalActions              = NULL ;
                                    pfn_Steamworks_sconSetActionSets                  = NULL ;
                                    pfn_Steamworks_sconGetConnectedControllers        = NULL ;
									pfn_Steamworks_IsDlcInstalled                     = NULL ;
                                    pfn_Steamworks_GetServerTime                      = NULL ;
                                    pfn_Steamworks_SubmitOrCreateScore                = NULL ;
                                    pfn_Steamworks_OpenItemInBrowser                  = NULL ;
                                    pfn_Steamworks_MakeDir                            = NULL ;
                                    pfn_Steamworks_DownloadScores                     = NULL ;
                                    pfn_Steamworks_DeleteLocalWorkshopFile            = NULL ;
                                    pfn_Steamworks_PublishWorkshopFileUpdate          = NULL ;
                                    pfn_Steamworks_DownloadWorkshopFile               = NULL ;
                                    pfn_Steamworks_SetUGCDownloadLocation             = NULL ;
                                    pfn_Steamworks_QueryWorkshopUserContent           = NULL ;
                                    pfn_Steamworks_GetWorkshopUserVoteDetails         = NULL ;
                                    pfn_Steamworks_SetWorkshopUserVote                = NULL ;
                                    pfn_Steamworks_GetWorkshopVoteDetails             = NULL ;
                                    pfn_Steamworks_SetWorkshopFileAction              = NULL ;
                                    pfn_Steamworks_SubscribeToWorkshopFile            = NULL ;
                                    pfn_Steamworks_UnSubscribeFromWorkshopFile        = NULL ;
                                    pfn_Steamworks_PublishWorkshopFile                = NULL ;
                                    pfn_Steamworks_UploadScore                        = NULL ;
                                    pfn_Steamworks_FindLeaderboard                    = NULL ;
                                    pfn_Steamworks_ResetAllStats                      = NULL ;
                                    pfn_Steamworks_SetStat                            = NULL ;
                                    pfn_Steamworks_UpdateAvgRateStat                  = NULL ;
                                    pfn_Steamworks_GetStat                            = NULL ;
                                    pfn_Steamworks_Init                               = NULL ;
                                    pfn_Steamworks_GetNumAchievements                 = NULL ;
                                    pfn_Steamworks_GetNextMostAchievedAchievementInfo  = NULL ;
                                    pfn_Steamworks_GetMostAchievedAchievementInfo  = NULL ;
                                    pfn_Steamworks_GetAchievementAndUnlockTime   = NULL ;
                                    pfn_Steamworks_GetAchievementAchievedPercent = NULL ;
                                    pfn_Steamworks_ClearAchievement          = NULL ;
                                    pfn_Steamworks_StoreStats                = NULL ;
                                    pfn_Steamworks_SetAchievement            = NULL ;
                                    pfn_Steamworks_GetAchievementIcon        = NULL ;
                                    pfn_Steamworks_GetAchievementDescription = NULL ;
                                    pfn_Steamworks_GetAchievementName = NULL ;
                                    pfn_Steamworks_GetAchievement     = NULL ;
                                    pfn_Steamworks_GetLocalPlayerName = NULL ;
                                    pfn_Steamworks_RunCallbacks = NULL ;

                                }

	//-------------------------------------------------------------------------
	//  API Callbacks 
	//-------------------------------------------------------------------------

    S3DX::AICallback        pfn_Steamworks_sconPulse ;
    S3DX::AICallback        pfn_Steamworks_sconShowBindingPanel ;
    S3DX::AICallback        pfn_Steamworks_sconSetActionSet ;
    S3DX::AICallback        pfn_Steamworks_sconGetActionSet ;
    S3DX::AICallback        pfn_Steamworks_sconGetDigitalActionOrigin ;
    S3DX::AICallback        pfn_Steamworks_sconGetAnalogActionOrigin ;
    S3DX::AICallback        pfn_Steamworks_sconLoop ;
    S3DX::AICallback        pfn_Steamworks_sconSetAnalogActions ;
    S3DX::AICallback        pfn_Steamworks_sconSetDigitalActions ;
    S3DX::AICallback        pfn_Steamworks_sconSetActionSets ;
    S3DX::AICallback        pfn_Steamworks_sconGetConnectedControllers ;
	S3DX::AICallback        pfn_Steamworks_IsDlcInstalled ;
    S3DX::AICallback        pfn_Steamworks_GetServerTime ;
    S3DX::AICallback        pfn_Steamworks_SubmitOrCreateScore ;
    S3DX::AICallback        pfn_Steamworks_OpenItemInBrowser ;
    S3DX::AICallback        pfn_Steamworks_MakeDir ;
    S3DX::AICallback        pfn_Steamworks_DownloadScores ;
    S3DX::AICallback        pfn_Steamworks_DeleteLocalWorkshopFile ;
    S3DX::AICallback        pfn_Steamworks_PublishWorkshopFileUpdate ;
    S3DX::AICallback        pfn_Steamworks_DownloadWorkshopFile ;
    S3DX::AICallback        pfn_Steamworks_SetUGCDownloadLocation ;
    S3DX::AICallback        pfn_Steamworks_QueryWorkshopUserContent ;
    S3DX::AICallback        pfn_Steamworks_GetWorkshopUserVoteDetails ;
    S3DX::AICallback        pfn_Steamworks_SetWorkshopUserVote ;
    S3DX::AICallback        pfn_Steamworks_GetWorkshopVoteDetails ;
    S3DX::AICallback        pfn_Steamworks_SetWorkshopFileAction ;
    S3DX::AICallback        pfn_Steamworks_SubscribeToWorkshopFile ;
    S3DX::AICallback        pfn_Steamworks_UnSubscribeFromWorkshopFile ;
    S3DX::AICallback        pfn_Steamworks_PublishWorkshopFile ;
    S3DX::AICallback        pfn_Steamworks_UploadScore ;
    S3DX::AICallback        pfn_Steamworks_FindLeaderboard ;
    S3DX::AICallback        pfn_Steamworks_ResetAllStats ;
    S3DX::AICallback        pfn_Steamworks_SetStat ;
    S3DX::AICallback        pfn_Steamworks_UpdateAvgRateStat ;
    S3DX::AICallback        pfn_Steamworks_GetStat ;
    S3DX::AICallback        pfn_Steamworks_Init ;
    S3DX::AICallback        pfn_Steamworks_GetNumAchievements ;
    S3DX::AICallback        pfn_Steamworks_GetNextMostAchievedAchievementInfo ;
    S3DX::AICallback        pfn_Steamworks_GetMostAchievedAchievementInfo ;
    S3DX::AICallback        pfn_Steamworks_GetAchievementAndUnlockTime ;
    S3DX::AICallback        pfn_Steamworks_GetAchievementAchievedPercent ;
    S3DX::AICallback        pfn_Steamworks_ClearAchievement ;
    S3DX::AICallback        pfn_Steamworks_StoreStats ;
    S3DX::AICallback        pfn_Steamworks_SetAchievement ;
    S3DX::AICallback        pfn_Steamworks_GetAchievementIcon ;
    S3DX::AICallback        pfn_Steamworks_GetAchievementDescription ;
    S3DX::AICallback        pfn_Steamworks_GetAchievementName ;
    S3DX::AICallback        pfn_Steamworks_GetAchievement ;
    S3DX::AICallback        pfn_Steamworks_GetLocalPlayerName ;
    S3DX::AICallback        pfn_Steamworks_RunCallbacks ;

	//-------------------------------------------------------------------------
	//  API Functions 
	//-------------------------------------------------------------------------

    inline void                 sconPulse                          ( const S3DX::AIVariable& sControllerID, const S3DX::AIVariable& SteamworkskPad, const S3DX::AIVariable& nDurationMicroSecs ) { S3DX_DECLARE_VIN_03( sControllerID, SteamworkskPad, nDurationMicroSecs ) ; if ( pfn_Steamworks_sconPulse ) pfn_Steamworks_sconPulse ( 3, vIn, NULL );  }
    inline S3DX::AIVariable     sconShowBindingPanel               ( const S3DX::AIVariable& sControntrollerID ) { S3DX_DECLARE_VIN_01( sControntrollerID ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_sconShowBindingPanel ) pfn_Steamworks_sconShowBindingPanel ( 1, vIn, &vOut ); return vOut ; }
    inline void                 sconSetActionSet                   ( const S3DX::AIVariable& sControllerID, const S3DX::AIVariable& sActionSetName ) { S3DX_DECLARE_VIN_02( sControllerID, sActionSetName ) ; if ( pfn_Steamworks_sconSetActionSet ) pfn_Steamworks_sconSetActionSet ( 2, vIn, NULL );  }
    inline S3DX::AIVariable     sconGetActionSet                   ( const S3DX::AIVariable& sControllerID ) { S3DX_DECLARE_VIN_01( sControllerID ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_sconGetActionSet ) pfn_Steamworks_sconGetActionSet ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     sconGetDigitalActionOrigin         ( const S3DX::AIVariable& sControllerID, const S3DX::AIVariable& sActionSetName, const S3DX::AIVariable& sAction ) { S3DX_DECLARE_VIN_03( sControllerID, sActionSetName, sAction ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_sconGetDigitalActionOrigin ) pfn_Steamworks_sconGetDigitalActionOrigin ( 3, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     sconGetAnalogActionOrigin          ( const S3DX::AIVariable& sControllerID, const S3DX::AIVariable& sActionSetName, const S3DX::AIVariable& sAction ) { S3DX_DECLARE_VIN_03( sControllerID, sActionSetName, sAction ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_sconGetAnalogActionOrigin ) pfn_Steamworks_sconGetAnalogActionOrigin ( 3, vIn, &vOut ); return vOut ; }
    inline void                 sconLoop                           (  ) { if ( pfn_Steamworks_sconLoop ) pfn_Steamworks_sconLoop ( 0, NULL, NULL );  }
    inline S3DX::AIVariable     sconSetAnalogActions               ( const S3DX::AIVariable& sActionCSV ) { S3DX_DECLARE_VIN_01( sActionCSV ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_sconSetAnalogActions ) pfn_Steamworks_sconSetAnalogActions ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     sconSetDigitalActions              ( const S3DX::AIVariable& sActionCSV ) { S3DX_DECLARE_VIN_01( sActionCSV ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_sconSetDigitalActions ) pfn_Steamworks_sconSetDigitalActions ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     sconSetActionSets                  ( const S3DX::AIVariable& sActionCSV ) { S3DX_DECLARE_VIN_01( sActionCSV ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_sconSetActionSets ) pfn_Steamworks_sconSetActionSets ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     sconGetConnectedControllers        (  ) { S3DX::AIVariable vOut ; if ( pfn_Steamworks_sconGetConnectedControllers ) pfn_Steamworks_sconGetConnectedControllers ( 0, NULL, &vOut ); return vOut ; }
    inline S3DX::AIVariable     IsDlcInstalled                     ( const S3DX::AIVariable& sAppId ) { S3DX_DECLARE_VIN_01( sAppId ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_IsDlcInstalled ) pfn_Steamworks_IsDlcInstalled ( 1, vIn, &vOut ); return vOut ; }
	inline S3DX::AIVariable     GetServerTime                      (  ) { S3DX::AIVariable vOut ; if ( pfn_Steamworks_GetServerTime ) pfn_Steamworks_GetServerTime ( 0, NULL, &vOut ); return vOut ; }
    inline void                 SubmitOrCreateScore                ( const S3DX::AIVariable& sLeaderboard, const S3DX::AIVariable& nScore ) { S3DX_DECLARE_VIN_02( sLeaderboard, nScore ) ; if ( pfn_Steamworks_SubmitOrCreateScore ) pfn_Steamworks_SubmitOrCreateScore ( 2, vIn, NULL );  }
    inline void                 OpenItemInBrowser                  ( const S3DX::AIVariable& sWorkshopItemID ) { S3DX_DECLARE_VIN_01( sWorkshopItemID ) ; if ( pfn_Steamworks_OpenItemInBrowser ) pfn_Steamworks_OpenItemInBrowser ( 1, vIn, NULL );  }
    inline void                 MakeDir                            ( const S3DX::AIVariable& sFullPath ) { S3DX_DECLARE_VIN_01( sFullPath ) ; if ( pfn_Steamworks_MakeDir ) pfn_Steamworks_MakeDir ( 1, vIn, NULL );  }
    inline void                 DownloadScores                     ( const S3DX::AIVariable& sCallbackAI, const S3DX::AIVariable& sCallbackHandler, const S3DX::AIVariable& sLeaderboardName, const S3DX::AIVariable& kLeaderboardRequest, const S3DX::AIVariable& nStart, const S3DX::AIVariable& nEnd ) { S3DX_DECLARE_VIN_06( sCallbackAI, sCallbackHandler, sLeaderboardName, kLeaderboardRequest, nStart, nEnd ) ; if ( pfn_Steamworks_DownloadScores ) pfn_Steamworks_DownloadScores ( 6, vIn, NULL );  }
    inline void                 DeleteLocalWorkshopFile            ( const S3DX::AIVariable& sFullPathToFilename ) { S3DX_DECLARE_VIN_01( sFullPathToFilename ) ; if ( pfn_Steamworks_DeleteLocalWorkshopFile ) pfn_Steamworks_DeleteLocalWorkshopFile ( 1, vIn, NULL );  }
    inline void                 PublishWorkshopFileUpdate          ( const S3DX::AIVariable& sWorkshopItemID, const S3DX::AIVariable& sFilePath, const S3DX::AIVariable& nAppID, const S3DX::AIVariable& sTitle, const S3DX::AIVariable& sDescription, const S3DX::AIVariable& sAI, const S3DX::AIVariable& sCallback ) { S3DX_DECLARE_VIN_07( sWorkshopItemID, sFilePath, nAppID, sTitle, sDescription, sAI, sCallback ) ; if ( pfn_Steamworks_PublishWorkshopFileUpdate ) pfn_Steamworks_PublishWorkshopFileUpdate ( 7, vIn, NULL );  }
    inline void                 DownloadWorkshopFile               ( const S3DX::AIVariable& sWorkshopItemID ) { S3DX_DECLARE_VIN_01( sWorkshopItemID ) ; if ( pfn_Steamworks_DownloadWorkshopFile ) pfn_Steamworks_DownloadWorkshopFile ( 1, vIn, NULL );  }
    inline void                 SetUGCDownloadLocation             ( const S3DX::AIVariable& sPath ) { S3DX_DECLARE_VIN_01( sPath ) ; if ( pfn_Steamworks_SetUGCDownloadLocation ) pfn_Steamworks_SetUGCDownloadLocation ( 1, vIn, NULL );  }
    inline void                 QueryWorkshopUserContent           ( const S3DX::AIVariable& kWorkshopQueryType, const S3DX::AIVariable& kWorkshopListSort, const S3DX::AIVariable& nCreatorAppID, const S3DX::AIVariable& nConsumerAppID, const S3DX::AIVariable& nPage ) { S3DX_DECLARE_VIN_05( kWorkshopQueryType, kWorkshopListSort, nCreatorAppID, nConsumerAppID, nPage ) ; if ( pfn_Steamworks_QueryWorkshopUserContent ) pfn_Steamworks_QueryWorkshopUserContent ( 5, vIn, NULL );  }
    inline void                 GetWorkshopUserVoteDetails         ( const S3DX::AIVariable& sWorkshopItemID ) { S3DX_DECLARE_VIN_01( sWorkshopItemID ) ; if ( pfn_Steamworks_GetWorkshopUserVoteDetails ) pfn_Steamworks_GetWorkshopUserVoteDetails ( 1, vIn, NULL );  }
    inline void                 SetWorkshopUserVote                ( const S3DX::AIVariable& sWorkshopItemID, const S3DX::AIVariable& bVotePositive ) { S3DX_DECLARE_VIN_02( sWorkshopItemID, bVotePositive ) ; if ( pfn_Steamworks_SetWorkshopUserVote ) pfn_Steamworks_SetWorkshopUserVote ( 2, vIn, NULL );  }
    inline void                 GetWorkshopVoteDetails             ( const S3DX::AIVariable& sWorkshopItemID ) { S3DX_DECLARE_VIN_01( sWorkshopItemID ) ; if ( pfn_Steamworks_GetWorkshopVoteDetails ) pfn_Steamworks_GetWorkshopVoteDetails ( 1, vIn, NULL );  }
    inline void                 SetWorkshopFileAction              ( const S3DX::AIVariable& sWorkshopItemID, const S3DX::AIVariable& kWorkshopFileAction ) { S3DX_DECLARE_VIN_02( sWorkshopItemID, kWorkshopFileAction ) ; if ( pfn_Steamworks_SetWorkshopFileAction ) pfn_Steamworks_SetWorkshopFileAction ( 2, vIn, NULL );  }
    inline void                 SubscribeToWorkshopFile            ( const S3DX::AIVariable& sWorkshopItemID ) { S3DX_DECLARE_VIN_01( sWorkshopItemID ) ; if ( pfn_Steamworks_SubscribeToWorkshopFile ) pfn_Steamworks_SubscribeToWorkshopFile ( 1, vIn, NULL );  }
    inline void                 UnSubscribeFromWorkshopFile        ( const S3DX::AIVariable& sWorkshopItemID ) { S3DX_DECLARE_VIN_01( sWorkshopItemID ) ; if ( pfn_Steamworks_UnSubscribeFromWorkshopFile ) pfn_Steamworks_UnSubscribeFromWorkshopFile ( 1, vIn, NULL );  }
    inline void                 PublishWorkshopFile                ( const S3DX::AIVariable& sFilePath, const S3DX::AIVariable& nAppID, const S3DX::AIVariable& sTitle, const S3DX::AIVariable& sDescription, const S3DX::AIVariable& sAI, const S3DX::AIVariable& sCallback) { S3DX_DECLARE_VIN_06( sFilePath, nAppID, sTitle, sDescription, sAI, sCallback) ; if ( pfn_Steamworks_PublishWorkshopFile ) pfn_Steamworks_PublishWorkshopFile ( 6, vIn, NULL );  }
    inline S3DX::AIVariable     UploadScore                        ( const S3DX::AIVariable& nScore ) { S3DX_DECLARE_VIN_01( nScore ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_UploadScore ) pfn_Steamworks_UploadScore ( 1, vIn, &vOut ); return vOut ; }
    inline void                 FindLeaderboard                    ( const S3DX::AIVariable& sLeaderboardName ) { S3DX_DECLARE_VIN_01( sLeaderboardName ) ; if ( pfn_Steamworks_FindLeaderboard ) pfn_Steamworks_FindLeaderboard ( 1, vIn, NULL );  }
    inline S3DX::AIVariable     ResetAllStats                      ( const S3DX::AIVariable& bAchievementsToo ) { S3DX_DECLARE_VIN_01( bAchievementsToo ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_ResetAllStats ) pfn_Steamworks_ResetAllStats ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     SetStat                            ( const S3DX::AIVariable& sStatName, const S3DX::AIVariable& nStatValue, const S3DX::AIVariable& kStatType ) { S3DX_DECLARE_VIN_03( sStatName, nStatValue, kStatType ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_SetStat ) pfn_Steamworks_SetStat ( 3, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     UpdateAvgRateStat                  ( const S3DX::AIVariable& sStatName, const S3DX::AIVariable& nCountThisSession, const S3DX::AIVariable& nSessionLength ) { S3DX_DECLARE_VIN_03( sStatName, nCountThisSession, nSessionLength ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_UpdateAvgRateStat ) pfn_Steamworks_UpdateAvgRateStat ( 3, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     GetStat                            ( const S3DX::AIVariable& sStatName, const S3DX::AIVariable& kStatType ) { S3DX_DECLARE_VIN_02( sStatName, kStatType ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_GetStat ) pfn_Steamworks_GetStat ( 2, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     Init                               ( const S3DX::AIVariable& sAIModel ) { S3DX_DECLARE_VIN_01( sAIModel ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_Init ) pfn_Steamworks_Init ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     GetNumAchievements                 (  ) { S3DX::AIVariable vOut ; if ( pfn_Steamworks_GetNumAchievements ) pfn_Steamworks_GetNumAchievements ( 0, NULL, &vOut ); return vOut ; }
    inline S3DX::AIVariables<4> GetNextMostAchievedAchievementInfo  ( const S3DX::AIVariable& nIndex ) { S3DX_DECLARE_VIN_01( nIndex ) ; S3DX::AIVariables<4> vOut ; if ( pfn_Steamworks_GetNextMostAchievedAchievementInfo ) pfn_Steamworks_GetNextMostAchievedAchievementInfo ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariables<4> GetMostAchievedAchievementInfo  (  ) { S3DX::AIVariables<4> vOut ; if ( pfn_Steamworks_GetMostAchievedAchievementInfo ) pfn_Steamworks_GetMostAchievedAchievementInfo ( 0, NULL, vOut ); return vOut ; }
    inline S3DX::AIVariables<2> GetAchievementAndUnlockTime   ( const S3DX::AIVariable& sAchievementID ) { S3DX_DECLARE_VIN_01( sAchievementID ) ; S3DX::AIVariables<2> vOut ; if ( pfn_Steamworks_GetAchievementAndUnlockTime ) pfn_Steamworks_GetAchievementAndUnlockTime ( 1, vIn, vOut ); return vOut ; }
    inline S3DX::AIVariable     GetAchievementAchievedPercent ( const S3DX::AIVariable& sAchievementID ) { S3DX_DECLARE_VIN_01( sAchievementID ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_GetAchievementAchievedPercent ) pfn_Steamworks_GetAchievementAchievedPercent ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     ClearAchievement          ( const S3DX::AIVariable& sAchievementID ) { S3DX_DECLARE_VIN_01( sAchievementID ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_ClearAchievement ) pfn_Steamworks_ClearAchievement ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     StoreStats                (  ) { S3DX::AIVariable vOut ; if ( pfn_Steamworks_StoreStats ) pfn_Steamworks_StoreStats ( 0, NULL, &vOut ); return vOut ; }
    inline S3DX::AIVariable     SetAchievement            ( const S3DX::AIVariable& sAchievementID ) { S3DX_DECLARE_VIN_01( sAchievementID ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_SetAchievement ) pfn_Steamworks_SetAchievement ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     GetAchievementIcon        ( const S3DX::AIVariable& sAchievementID ) { S3DX_DECLARE_VIN_01( sAchievementID ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_GetAchievementIcon ) pfn_Steamworks_GetAchievementIcon ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     GetAchievementDescription ( const S3DX::AIVariable& sAchievementID ) { S3DX_DECLARE_VIN_01( sAchievementID ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_GetAchievementDescription ) pfn_Steamworks_GetAchievementDescription ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     GetAchievementName ( const S3DX::AIVariable& sAchievementName ) { S3DX_DECLARE_VIN_01( sAchievementName ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_GetAchievementName ) pfn_Steamworks_GetAchievementName ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     GetAchievement     ( const S3DX::AIVariable& sAchievementName ) { S3DX_DECLARE_VIN_01( sAchievementName ) ; S3DX::AIVariable vOut ; if ( pfn_Steamworks_GetAchievement ) pfn_Steamworks_GetAchievement ( 1, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     GetLocalPlayerName (  ) { S3DX::AIVariable vOut ; if ( pfn_Steamworks_GetLocalPlayerName ) pfn_Steamworks_GetLocalPlayerName ( 0, NULL, &vOut ); return vOut ; }
    inline void                 RunCallbacks (  ) { if ( pfn_Steamworks_RunCallbacks ) pfn_Steamworks_RunCallbacks ( 0, NULL, NULL );  }

 	//-------------------------------------------------------------------------
	//  API Constants 
	//-------------------------------------------------------------------------

    S3DX::AIVariable kSconLeftPad ; 
    S3DX::AIVariable kSconRightPad ; 
    S3DX::AIVariable kSconAnalogSourceModeNone ; 
    S3DX::AIVariable kSconAnalogSourceModeDpad ; 
    S3DX::AIVariable kSconAnalogSourceModeButtons ; 
    S3DX::AIVariable kSconAnalogSourceModeFourButtons ; 
    S3DX::AIVariable kSconAnalogSourceModeAbsoluteMouse ; 
    S3DX::AIVariable kSconAnalogSourceModeRelativeMouse ; 
    S3DX::AIVariable kSconAnalogSourceModeJoystickMove ; 
    S3DX::AIVariable kSconAnalogSourceModeJoystickCamera ; 
    S3DX::AIVariable kSconAnalogSourceModeScrollWheel ; 
    S3DX::AIVariable kSconAnalogSourceModeTrigger ; 
    S3DX::AIVariable kSconAnalogSourceModeTouchMenu ; 
    S3DX::AIVariable kSconButtonNone ; 
    S3DX::AIVariable kSconButtonA ; 
    S3DX::AIVariable kSconButtonB ; 
    S3DX::AIVariable kSconButtonX ; 
    S3DX::AIVariable kSconButtonY ; 
    S3DX::AIVariable kSconBumperLeft ; 
    S3DX::AIVariable kSconBumperRight ; 
    S3DX::AIVariable kSconGripLeft ; 
    S3DX::AIVariable kSconGripRight ; 
    S3DX::AIVariable kSconButtonStart ; 
    S3DX::AIVariable kSconButtonBack ; 
    S3DX::AIVariable kSconPadLeftTouch ; 
    S3DX::AIVariable kSconPadLeftSwipe ; 
    S3DX::AIVariable kSconPadLeftClick ; 
    S3DX::AIVariable kSconPadLeftDPadUp ; 
    S3DX::AIVariable kSconPadLeftDPadDown ; 
    S3DX::AIVariable kSconPadLeftDPadLeft ; 
    S3DX::AIVariable kSconPadLeftDPadRight ; 
    S3DX::AIVariable kSconPadRightTouch ; 
    S3DX::AIVariable kSconPadRightSwipe ; 
    S3DX::AIVariable kSconPadRightClick ; 
    S3DX::AIVariable kSconPadRightDPadUp ; 
    S3DX::AIVariable kSconPadRightDPadDown ; 
    S3DX::AIVariable kSconPadRightDPadLeft ; 
    S3DX::AIVariable kSconPadRightDPadRight ; 
    S3DX::AIVariable kSconTriggerLeftPull ; 
    S3DX::AIVariable kSconTriggerLeftClick ; 
    S3DX::AIVariable kSconTriggerRightPull ; 
    S3DX::AIVariable kSconTriggerRightClick ; 
    S3DX::AIVariable kSconStickLeftMove ; 
    S3DX::AIVariable kSconStickLeftClick ; 
    S3DX::AIVariable kSconStickLeftUp ; 
    S3DX::AIVariable kSconStickLeftDown ; 
    S3DX::AIVariable kSconStickLeftLeft ; 
    S3DX::AIVariable kSconStickLeftRight ; 
    S3DX::AIVariable kSconGyroMove ; 
    S3DX::AIVariable kSconGyroPitch ; 
    S3DX::AIVariable kSconGyroYaw ; 
    S3DX::AIVariable kSconGyroRoll ; 
    S3DX::AIVariable kLeaderboardRequestGlobal ; 
    S3DX::AIVariable kLeaderboardRequestGlobalAroundUser ; 
    S3DX::AIVariable kLeaderboardRequestFriends ; 
    S3DX::AIVariable kLeaderboardRequestUsers ; 
    S3DX::AIVariable kWorkshopListSortCreationDesc ; 
    S3DX::AIVariable kWorkshopListSortCreationAsc ; 
    S3DX::AIVariable kWorkshopListSortTitleAsc ; 
    S3DX::AIVariable kWorkshopListSortLastUpdatedDesc ; 
    S3DX::AIVariable kWorkshopListSortSubscriptionDateDesc ; 
    S3DX::AIVariable kWorkshopListSortVoteScoreDesc ; 
    S3DX::AIVariable kWorkshopListSortForModeration ; 
    S3DX::AIVariable kWorkshopQueryPublished ; 
    S3DX::AIVariable kWorkshopQueryVotedOn ; 
    S3DX::AIVariable kWorkshopQueryVotedUp ; 
    S3DX::AIVariable kWorkshopQueryVotedDown ; 
    S3DX::AIVariable kWorkshopQueryVoteLater ; 
    S3DX::AIVariable kWorkshopQueryFavorited ; 
    S3DX::AIVariable kWorkshopQuerySubscribed ; 
    S3DX::AIVariable kWorkshopQueryUsedOrPlayed ; 
    S3DX::AIVariable kWorkshopQueryFollowed ; 
    S3DX::AIVariable kWorkshopFileActionPlayed ; 
    S3DX::AIVariable kWorkshopFileActionCompleted ; 
    S3DX::AIVariable kStatTypeAvgrate ; 
    S3DX::AIVariable kStatTypeInt ; 
    S3DX::AIVariable kStatTypeFloat ; 

} ;

extern SteamworksAPI Steamworks;

//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
