#include "PrecompiledHeader.h"
#include "Leaderboards.h"
#include "minmax.h" // min

char CSteamLeaderboards::m_sDownloadAICallback[] = {};
char CSteamLeaderboards::m_sDownloadHandlerCallback[] = {};

CSteamLeaderboards::CSteamLeaderboards(const char* sAIModel): 				
m_CurrentLeaderboard( NULL ),
	m_nLeaderboardEntries( 0 )
{
	m_sAIModel = sAIModel;
}

void CSteamLeaderboards::CreateOrSubmitScore( const char *pchLeaderboardName, int score )
{
	m_CurrentLeaderboard = NULL;
	m_nFindOrCreateScore = score;

	SteamAPICall_t hSteamAPICall = SteamUserStats()->FindOrCreateLeaderboard(pchLeaderboardName, k_ELeaderboardSortMethodAscending, k_ELeaderboardDisplayTypeNumeric);
	m_callResultFindOrCreateLeaderboard.Set(hSteamAPICall, this, &CSteamLeaderboards::OnFindOrCreateLeaderboard);
}

void CSteamLeaderboards::OnFindOrCreateLeaderboard( LeaderboardFindResult_t *pResult, bool bIOFailure)
{
	if ( !pResult->m_bLeaderboardFound || bIOFailure )
	{
		S3DX::log.message("Steamworks: Leaderboard could not be created or found");
		return;
	}

	m_CurrentLeaderboard = pResult->m_hSteamLeaderboard;
	SteamUserStats()->UploadLeaderboardScore( m_CurrentLeaderboard, k_ELeaderboardUploadScoreMethodKeepBest, m_nFindOrCreateScore, NULL, 0 );
}

void CSteamLeaderboards::FindLeaderboard( const char *pchLeaderboardName )
{
	m_CurrentLeaderboard = NULL;

	SteamAPICall_t hSteamAPICall = SteamUserStats()->FindLeaderboard(pchLeaderboardName);
	m_callResultFindLeaderboard.Set(hSteamAPICall, this, &CSteamLeaderboards::OnFindLeaderboard);
}

void CSteamLeaderboards::OnFindLeaderboard( LeaderboardFindResult_t *pCallback,	bool bIOFailure )
{
	S3DX::AIVariable hUser = S3DX::application.getCurrentUser();
	S3DX::user.sendEvent(hUser, m_sAIModel, "onFoundLeaderboard", pCallback->m_bLeaderboardFound);

	// see if we encountered an error during the call
	if ( !pCallback->m_bLeaderboardFound || bIOFailure )
	{
		S3DX::log.message("Steamworks: Leaderboard could not be found");
		return;
	}

	m_CurrentLeaderboard = pCallback->m_hSteamLeaderboard;
}

bool CSteamLeaderboards::UploadScore( int score )
{
	if (!m_CurrentLeaderboard)
		return false;

	SteamAPICall_t hSteamAPICall = SteamUserStats()->UploadLeaderboardScore( m_CurrentLeaderboard, k_ELeaderboardUploadScoreMethodKeepBest, score, NULL, 0 );

	m_callResultUploadScore.Set(hSteamAPICall, this, &CSteamLeaderboards::OnUploadScore);

	return true;
}

void CSteamLeaderboards::OnUploadScore(LeaderboardScoreUploaded_t *pCallback, bool bIOFailure)
{

	S3DX::AIVariable hUser = S3DX::application.getCurrentUser();
	S3DX::user.sendEvent(hUser, m_sAIModel, "onScoreUploaded", pCallback->m_bSuccess );

	if ( !pCallback->m_bSuccess || bIOFailure )
	{
		S3DX::log.message("Steamworks: Score could not be uploaded to Steam!");
	}
}

void CSteamLeaderboards::DownloadScores(const char* ai, const char* handler, const char *leaderboardName, ELeaderboardDataRequest eRequestType, int start, int end)
{
	strcpy(m_sDownloadAICallback, ai);
	strcpy(m_sDownloadHandlerCallback, handler);

	meDownloadRequestType = eRequestType;
	mDownloadStart = start;
	mDownloadEnd = end;

	SteamAPICall_t hSteamAPICall = SteamUserStats()->FindLeaderboard(leaderboardName);
	m_callResultFindLeaderboardForScoreDownload.Set(hSteamAPICall, this, &CSteamLeaderboards::OnFindLeaderboardForScoreDownload);
}

void CSteamLeaderboards::OnFindLeaderboardForScoreDownload( LeaderboardFindResult_t *pCallback,	bool bIOFailure )
{
	// see if we encountered an error during the call
	if ( !pCallback->m_bLeaderboardFound || bIOFailure )
	{
		S3DX::log.message("Steamworks: Leaderboard could not be found");
		S3DX::user.sendEvent ( S3DX::application.getCurrentUser(), 
				m_sDownloadAICallback, 
				m_sDownloadHandlerCallback, 
				0, 0, 0, 0 );
		return;
	}

	// load the specified leaderboard data around the current user
	SteamAPICall_t hSteamAPICall = SteamUserStats()->DownloadLeaderboardEntries( pCallback->m_hSteamLeaderboard, meDownloadRequestType, mDownloadStart, mDownloadEnd );
	m_callResultDownloadScore.Set(hSteamAPICall, this, &CSteamLeaderboards::OnDownloadScore);
}

void CSteamLeaderboards::OnDownloadScore(LeaderboardScoresDownloaded_t *pCallback, bool bIOFailure)
{
	if (!bIOFailure)
	{
		if ( pCallback->m_cEntryCount == 0 )
		{
			S3DX::user.sendEvent ( S3DX::application.getCurrentUser(), 
				m_sDownloadAICallback, 
				m_sDownloadHandlerCallback, 
				0, 0, 0, 0 );

			return;
		}

		for (int index = 0; index < pCallback->m_cEntryCount; index++)
		{
			LeaderboardEntry_t leaderboardEntry;
			int32 details[3];
			SteamUserStats()->GetDownloadedLeaderboardEntry( pCallback->m_hSteamLeaderboardEntries, index, &leaderboardEntry, details, 3 );
			S3DX::user.sendEvent ( S3DX::application.getCurrentUser(), 
				m_sDownloadAICallback, 
				m_sDownloadHandlerCallback, 
				index, 
				pCallback->m_cEntryCount,
				leaderboardEntry.m_nGlobalRank,
				leaderboardEntry.m_nScore,
				SteamFriends()->GetFriendPersonaName(leaderboardEntry.m_steamIDUser));
			//SteamFriends()->GetSmallFriendAvatar()
		}
	}
	else
	{
		S3DX::user.sendEvent ( S3DX::application.getCurrentUser(), 
				m_sDownloadAICallback, 
				m_sDownloadHandlerCallback, 
				0, 0, 0, 0 );
	}
}