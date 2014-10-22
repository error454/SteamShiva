//-----------------------------------------------------------------------------
#ifndef __SteamMain_h__
#define __SteamMain_h__
//-----------------------------------------------------------------------------

#include "StatsAndAchievements.h"
#include "Leaderboards.h"
#include "steam_api.h"
#include "CloudAndWorkshop.h"

// Main class for initialisation, shutdown, error handling/logging and so on
class CSteamMain
{
public:
	CSteamMain();
	~CSteamMain() {};

	bool Init(const char* sAIModel);
	void Shutdown();

	bool bInitialised;
	void RunCallbacks();

	// Exposed to ShiVa
	const char* GetLocalPlayerName();

	CStatsAndAchievements *m_pStatsAndAchievements;
	CSteamLeaderboards *m_pLeaderboards;
	CCloudAndWorkshop *m_pCloudAndWorkshop;

private:
	// The AI model where callbacks are sent
	const char* m_sAIModel;

	// SteamID for the local user on this client
	CSteamID m_SteamIDLocalUser;

	// Callback to alert us when the game overlay is activated
	STEAM_CALLBACK( CSteamMain, OnGameOverlayActivated, GameOverlayActivated_t, m_CallbackGameOverlayActivated );
};

//-----------------------------------------------------------------------------
#endif // __SteamMain_h__
//-----------------------------------------------------------------------------