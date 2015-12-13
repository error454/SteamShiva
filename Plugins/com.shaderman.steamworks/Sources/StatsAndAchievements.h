//-----------------------------------------------------------------------------
#ifndef __StatsAndAchievements_h__
#define __StatsAndAchievements_h__
//-----------------------------------------------------------------------------

#include <utility> // std::pair
#include <string>

// used to store info about "most achieved achievements"
struct MostAchievedAchievementInfo
{
	std::string m_name;	// achievement ID
	float m_percent;	// percent
	bool m_achieved;	// achieved?
	int m_index;		// index used to iterate over "most achieved achievements"
};

// Stats and achievements class
// See https://partner.steamgames.com/documentation/ugs
class CStatsAndAchievements
{
public:
	CStatsAndAchievements(const char* sAIModel);
	~CStatsAndAchievements() { };

	// Run a frame
	void RunFrame();

	// achievements
	uint32							GetNumAchievements();
	bool							GetAchievement(const char* sAchievementID);
	std::pair<bool, uint32>			GetAchievementAndUnlockTime(const char* sAchievementID); // TODO unlock time is always 0. Test with a real game.
	bool							SetAchievement(const char* sAchievementID);
	bool							ClearAchievement(const char* sAchievementID);
	const char*						GetAchievementName(const char* sAchievementID);
	const char*						GetAchievementDescription(const char* sAchievementID);
	float							GetAchievementAchievedPercent(const char* sAchievementID);
	int								GetAchievementIcon(const char* sAchievementID);
	MostAchievedAchievementInfo*	GetMostAchievedAchievementInfo();
	MostAchievedAchievementInfo*	GetNextMostAchievedAchievementInfo(int nIndex);

	// stats
	S3DX::float32					GetStat(const char* sStatName, int kStatType);
	bool							SetStat(const char* sStatName, S3DX::float32 nStatValue, int kStatType);
	bool							UpdateAvgRateStat(const char* sStatName, S3DX::float32 nCountThisSession, S3DX::float32 nSessionLength);
	bool							ResetAllStats(bool bAchievementsToo);

	// store stats and achievements
	bool StoreStats();

	// callbacks
	STEAM_CALLBACK( CStatsAndAchievements, OnUserStatsStored, UserStatsStored_t, m_CallbackUserStatsStored );
	STEAM_CALLBACK( CStatsAndAchievements, OnAchievementStored, UserAchievementStored_t, m_CallbackAchievementStored );
	STEAM_CALLBACK( CStatsAndAchievements, OnUserStatsReceived, UserStatsReceived_t, m_CallbackUserStatsReceived );

private:
	// our GameID
	CGameID m_GameID;

	// Steam User interface
	ISteamUser *m_pSteamUser;

	// Steam UserStats interface
	ISteamUserStats *m_pSteamUserStats;

	// the calling user AI model name, we need it for callbacks
	const char* m_sAIModel;

	// stats requested / valid flags
	bool m_bRequestedStats;
	bool m_bStatsValid;
};

//-----------------------------------------------------------------------------
#endif // __StatsAndAchievements_h__
//-----------------------------------------------------------------------------