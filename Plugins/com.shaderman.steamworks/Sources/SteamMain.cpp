#include "PrecompiledHeader.h"

#include "steam_api.h"
#include "SteamMain.h"

//-----------------------------------------------------------------------------
// Generic API stuff
//-----------------------------------------------------------------------------

CSteamMain::CSteamMain() :
	m_CallbackGameOverlayActivated( this, &CSteamMain::OnGameOverlayActivated )
{
	bInitialised = false;
}

// Initialise Steamworks
bool CSteamMain::Init(const char* sAIModel)
{
	if ( !bInitialised )
	{
		S3DX::log.message("Steamworks: Initialising...");

		bool bInit = SteamAPI_Init();
		
		if ( bInit && SteamUser()->BLoggedOn() )
		{
			m_SteamIDLocalUser = SteamUser()->GetSteamID();
			if ( m_SteamIDLocalUser.IsValid() ) {
				m_pStatsAndAchievements = new CStatsAndAchievements(sAIModel);
				m_pLeaderboards = new CSteamLeaderboards(sAIModel);
				m_pCloudAndWorkshop = new CCloudAndWorkshop(sAIModel);
				m_pDlc = new CSteamDlc(sAIModel);
				m_pSteamCon = new CSteamCon(sAIModel);
				
				m_sAIModel = sAIModel;
				bInitialised = true;
			}
		}
	}
	return bInitialised;
}

// Shutdown Steamworks
void CSteamMain::Shutdown()
{
	if ( !bInitialised ) return;
	S3DX::log.message("Shutting down STEAM connection...");
	SteamAPI_Shutdown();

	if ( m_pStatsAndAchievements )
		delete m_pStatsAndAchievements;

	if ( m_pLeaderboards )
		delete m_pLeaderboards;

	if ( m_pCloudAndWorkshop )
		delete m_pCloudAndWorkshop;

	if ( m_pDlc )
		delete m_pDlc;

	if ( m_pSteamCon )
		delete m_pSteamCon;
}

// Fire callbacks
void CSteamMain::RunCallbacks()
{
	SteamAPI_RunCallbacks();
	m_pStatsAndAchievements->RunFrame();
}

// Steam overlay callback
void CSteamMain::OnGameOverlayActivated( GameOverlayActivated_t *callback )
{
	S3DX::AIVariable hUser = S3DX::application.getCurrentUser();
	S3DX::AIVariable bActivated;
	bActivated.SetBooleanValue ( callback->m_bActive );
	S3DX::user.sendEvent( hUser, m_sAIModel, "onGameOverlayActivated", bActivated );
}

//-----------------------------------------------------------------------------
// Additional functions exposed to ShiVa
//-----------------------------------------------------------------------------
const char* CSteamMain::GetLocalPlayerName()
{
	if ( m_SteamIDLocalUser.IsValid() ) {
		return SteamFriends()->GetFriendPersonaName( m_SteamIDLocalUser );
	} else {
		return "";
	}
}
