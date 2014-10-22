--------------------------------------------------------------------------------
--  Handler.......... : onDownloadScores
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.onDownloadScores ( sAI, sHandler, sLeaderboardName, kLeaderboardRequest, start, nEnd )
--------------------------------------------------------------------------------
	
    if user.getAIState ( this.getUser ( ), "Steam" ) == "Idle" then return 0 end
    
	Steamworks.DownloadScores ( sAI, sHandler, sLeaderboardName, kLeaderboardRequest, start, nEnd )
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
