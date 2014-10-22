--------------------------------------------------------------------------------
--  Handler.......... : onReceiveLeaderboardEntry
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.onReceiveLeaderboardEntry ( nResult, nTotalResults, nGlobalRank, nScore, sUser )
--------------------------------------------------------------------------------
	
	log.message ( nResult + 1, "/", nTotalResults, " Rank: ", nGlobalRank, " Score: ", nScore, " User: ", sUser )
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
