#ifndef LEADERBOARDS_H
#define LEADERBOARDS_H

#include "steam_api.h"

// From https://partner.steamgames.com/documentation/bootstrap_leaderboards
class CSteamLeaderboards
{
private:
	SteamLeaderboard_t m_CurrentLeaderboard; // Handle to leaderboard
	const char* m_sAIModel;
	ELeaderboardDataRequest meDownloadRequestType;
	int mDownloadStart;
	int mDownloadEnd;
	static char m_sDownloadAICallback [100];
	static char m_sDownloadHandlerCallback [100];

public:
	int m_nLeaderboardEntries;
	int m_nFindOrCreateScore;
	LeaderboardEntry_t m_leaderboardEntries[10]; // Holds downloaded score entries in DownloadScores

	CSteamLeaderboards(const char* sAIModel);
	~CSteamLeaderboards(){};

	void CreateOrSubmitScore( const char *pchLeaderboardName, int score );
	void FindLeaderboard( const char *pchLeaderboardName );
	bool UploadScore( int score );
	void DownloadScores(const char* ai, const char* handler, const char * leaderboardName, ELeaderboardDataRequest eRequestType, int start, int end);

	void OnFindOrCreateLeaderboard( LeaderboardFindResult_t *pResult, bool bIOFailure);
	CCallResult<CSteamLeaderboards, LeaderboardFindResult_t> m_callResultFindOrCreateLeaderboard;

	void OnFindLeaderboard( LeaderboardFindResult_t *pResult, bool bIOFailure);
	CCallResult<CSteamLeaderboards, LeaderboardFindResult_t> m_callResultFindLeaderboard;

	void OnFindLeaderboardForScoreDownload( LeaderboardFindResult_t *pResult, bool bIOFailure);
	CCallResult<CSteamLeaderboards, LeaderboardFindResult_t> m_callResultFindLeaderboardForScoreDownload;

	void OnUploadScore( LeaderboardScoreUploaded_t *pResult, bool bIOFailure);
	CCallResult<CSteamLeaderboards, LeaderboardScoreUploaded_t> m_callResultUploadScore;

	void OnDownloadScore( LeaderboardScoresDownloaded_t *pResult, bool bIOFailure);
	CCallResult<CSteamLeaderboards, LeaderboardScoresDownloaded_t> m_callResultDownloadScore;
};

#endif