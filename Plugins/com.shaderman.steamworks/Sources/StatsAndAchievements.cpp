#include "PrecompiledHeader.h"

#include "steam_api.h"
#include "StatsAndAchievements.h"


// The constructor :o
CStatsAndAchievements::CStatsAndAchievements(const char* sAIModel) :
	m_pSteamUser( NULL ),
	m_pSteamUserStats( NULL ),
	m_GameID( SteamUtils()->GetAppID() ),
	m_CallbackUserStatsStored( this, &CStatsAndAchievements::OnUserStatsStored ),
	m_CallbackAchievementStored( this, &CStatsAndAchievements::OnAchievementStored ),
	m_CallbackUserStatsReceived( this, &CStatsAndAchievements::OnUserStatsReceived )
{
	m_pSteamUser = SteamUser();
	m_pSteamUserStats = SteamUserStats();
	m_bRequestedStats = false;
	m_bStatsValid = false;
	m_sAIModel = sAIModel;
}

// run every frame until we received valid stats
void CStatsAndAchievements::RunFrame()
{
	if ( !m_bRequestedStats )
	{
		// Is Steam Loaded? if no, can't get stats, done
		if ( NULL == m_pSteamUserStats || NULL == m_pSteamUser )
		{
			m_bRequestedStats = true;
			return;
		}

		// If yes, request our stats
		m_bRequestedStats = m_pSteamUserStats->RequestCurrentStats();
	}

	if ( !m_bStatsValid )
		return;
}

//-----------------------------------------------------------------------------
//  Callbacks
//-----------------------------------------------------------------------------
void CStatsAndAchievements::OnUserStatsReceived( UserStatsReceived_t *pCallback )
{
	if ( !m_pSteamUserStats )
		return;

	// we may get callbacks for other games' stats arriving, ignore them
	if ( m_GameID.ToUint64() == pCallback->m_nGameID )
	{
		S3DX::AIVariable hUser = S3DX::application.getCurrentUser();

		if ( k_EResultOK == pCallback->m_eResult )
		{
			S3DX::log.message("Steamworks: Received stats and achievements from Steam");
			m_bStatsValid = true;
		} else {
			S3DX::log.warning("Steamworks: RequestStats failed: ", pCallback->m_eResult);
		}

		S3DX::user.sendEvent(hUser, m_sAIModel, "onUserStatsReceived", m_bStatsValid);
	}
}

void CStatsAndAchievements::OnUserStatsStored( UserStatsStored_t *pCallback )
{
	// we may get callbacks for other games' stats arriving, ignore them
	if ( m_GameID.ToUint64() == pCallback->m_nGameID )
	{
		S3DX::AIVariable hUser = S3DX::application.getCurrentUser();

		if ( k_EResultOK == pCallback->m_eResult )
		{
			S3DX::log.message("Steamworks: Stats stored successfully");
			S3DX::user.sendEvent(hUser, m_sAIModel, "onUserStatsStored", true);
		}
		else if ( k_EResultInvalidParam == pCallback->m_eResult )
		{
			// One or more stats we set broke a constraint. They've been reverted,
			// and we should re-iterate the values now to keep in sync.
			S3DX::log.warning("Steamworks: Failed to store stats");
			S3DX::user.sendEvent(hUser, m_sAIModel, "onUserStatsStored", false);
		}
		else
		{
			S3DX::log.warning("Steamworks: Failed to store stats, result: ", pCallback->m_eResult);
		}
	}
}

void CStatsAndAchievements::OnAchievementStored( UserAchievementStored_t *pCallback )
{
	// we may get callbacks for other games' stats arriving, ignore them
	if ( m_GameID.ToUint64() == pCallback->m_nGameID )
	{
		if ( 0 == pCallback->m_nMaxProgress )
		{
			S3DX::log.message("Steamworks: Achievement '", pCallback->m_rgchAchievementName, "' unlocked!");
		}
		else
		{
			S3DX::log.message("Steamworks: Achievement '", pCallback->m_rgchAchievementName, "' progress (", pCallback->m_nCurProgress, "/", pCallback->m_nMaxProgress, ")");
		}

		S3DX::AIVariable hUser = S3DX::application.getCurrentUser();
		S3DX::user.sendEvent(hUser, m_sAIModel, "onAchievementStored", pCallback->m_rgchAchievementName, pCallback->m_nCurProgress, pCallback->m_nMaxProgress);
	}
}

//-----------------------------------------------------------------------------
//  Achievement Functions
//-----------------------------------------------------------------------------
bool CStatsAndAchievements::GetAchievement(const char* sAchievementID)
{
	bool bAchieved = false;
	if ( m_bStatsValid ) {
		m_pSteamUserStats->GetAchievement(sAchievementID, &bAchieved);
	}
	return bAchieved;
}

bool CStatsAndAchievements::SetAchievement(const char* sAchievementID)
{
	return m_pSteamUserStats->SetAchievement( sAchievementID );
}

bool CStatsAndAchievements::ClearAchievement(const char* sAchievementID)
{
	return m_pSteamUserStats->ClearAchievement( sAchievementID );
}

const char* CStatsAndAchievements::GetAchievementName(const char* sAchievementID)
{
	if ( m_bStatsValid ) {
		return m_pSteamUserStats->GetAchievementDisplayAttribute( sAchievementID, "name" );
	} else {
		return "";
	}
}

const char* CStatsAndAchievements::GetAchievementDescription(const char* sAchievementID)
{
	if ( m_bStatsValid ) {
		return m_pSteamUserStats->GetAchievementDisplayAttribute( sAchievementID, "desc" );
	} else {
		return "";
	}
}

float CStatsAndAchievements::GetAchievementAchievedPercent(const char* sAchievementID)
{
	float percent = .0f;
	if ( m_bStatsValid ) {
		m_pSteamUserStats->GetAchievementAchievedPercent(sAchievementID, &percent);
	}
	return percent;
}

std::pair<bool, uint32> CStatsAndAchievements::GetAchievementAndUnlockTime(const char* sAchievementID)
{
	bool bAchieved = false;
	uint32 nUnlockTime = 0;
	if ( m_bStatsValid ) {
		m_pSteamUserStats->GetAchievementAndUnlockTime(sAchievementID, &bAchieved, &nUnlockTime);
	}
	return std::make_pair(bAchieved, nUnlockTime);
}

int CStatsAndAchievements::GetAchievementIcon(const char* sAchievementID)
{
	if ( m_bStatsValid ) {
		return m_pSteamUserStats->GetAchievementIcon( sAchievementID );
	} else {
		return 0;
	}
}

MostAchievedAchievementInfo* CStatsAndAchievements::GetMostAchievedAchievementInfo()
{
	MostAchievedAchievementInfo* MAAI = new MostAchievedAchievementInfo();
	char name[128];
	MAAI->m_index = m_pSteamUserStats->GetMostAchievedAchievementInfo(name, 128, &MAAI->m_percent, &MAAI->m_achieved);
	MAAI->m_name = name;
	return MAAI;
}

MostAchievedAchievementInfo* CStatsAndAchievements::GetNextMostAchievedAchievementInfo(int nIndex)
{
	MostAchievedAchievementInfo* MAAI = new MostAchievedAchievementInfo();
	char name[128];
	MAAI->m_index = m_pSteamUserStats->GetNextMostAchievedAchievementInfo(nIndex, name, 128, &MAAI->m_percent, &MAAI->m_achieved);
	MAAI->m_name = name;
	return MAAI;
}

uint32 CStatsAndAchievements::GetNumAchievements()
{
	return m_pSteamUserStats->GetNumAchievements();
}

bool CStatsAndAchievements::StoreStats()
{
	return m_pSteamUserStats->StoreStats();
}

//-----------------------------------------------------------------------------
//  Stats Functions
//-----------------------------------------------------------------------------
S3DX::float32 CStatsAndAchievements::GetStat(const char* sStatName, int kStatType)
{
	int32 statValueInt = 0;
	S3DX::float32 statValueFloat = .0f;

	switch (kStatType)
	{
		case 0: // Steamworks.kStatTypeInt
			m_pSteamUserStats->GetStat(sStatName, &statValueInt);
			return (S3DX::float32)statValueInt;
		case 1: // Steamworks.kStatTypeFloat
			m_pSteamUserStats->GetStat(sStatName, &statValueFloat);
			return statValueFloat;
		case 2: // Steamworks.kStatTypeAvgrate
			// The averaged result is calculated for us
			m_pSteamUserStats->GetStat(sStatName, &statValueFloat);
			return statValueFloat;
		default:
			return 0;
	}
}

bool CStatsAndAchievements::UpdateAvgRateStat(const char* sStatName, S3DX::float32 nCountThisSession, S3DX::float32 nSessionLength)
{
	return m_pSteamUserStats->UpdateAvgRateStat(sStatName, nCountThisSession, nSessionLength);
}

bool CStatsAndAchievements::SetStat(const char* sStatName, S3DX::float32 nStatValue, int kStatType)
{
	switch (kStatType)
	{
		case 0: // Steamworks.kStatTypeInt
			return m_pSteamUserStats->SetStat(sStatName, (int)nStatValue);
		case 1: // Steamworks.kStatTypeFloat
			return m_pSteamUserStats->SetStat(sStatName, nStatValue);
		default:
			return false;
	}
}

bool CStatsAndAchievements::ResetAllStats(bool bAchievementsToo)
{
	return m_pSteamUserStats->ResetAllStats(bAchievementsToo);
}
