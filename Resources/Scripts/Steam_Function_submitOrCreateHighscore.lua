--------------------------------------------------------------------------------
--  Function......... : submitOrCreateHighscore
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.submitOrCreateHighscore ( sLeaderboardName, nScore )
--------------------------------------------------------------------------------
	
    if user.getAIState ( this.getUser ( ), "Steam" ) == "Idle" then return 0 end
    
	Steamworks.SubmitOrCreateScore ( sLeaderboardName, nScore )
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------