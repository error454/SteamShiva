--------------------------------------------------------------------------------
--  Function......... : submitHighscore
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.submitHighscore ( sLeaderboardName, nScore, sAI, sCallback )
--------------------------------------------------------------------------------
	
    if user.getAIState ( this.getUser ( ), "Steam" ) == "Idle" then return 0 end
    
	log.message ( this.sDebugLabel ( ), "Submiting highscore" )
	table.add ( this.tPendingScores ( ), sLeaderboardName )
	table.add ( this.tPendingScores ( ), nScore )
	table.add ( this.tPendingScores ( ), sAI )
	table.add ( this.tPendingScores ( ), sCallback )
	
    if not this.bLeaderboardsInUse ( ) then
        this.bLeaderboardsInUse ( true )
        
        if this.sLeaderboardSelected ( ) ~= sLeaderboardName then
            --
            -- Request the leaderboard and wait for onFoundLeaderboard callback
            --
            Steamworks.FindLeaderboard ( sLeaderboardName )
        else
            --
            -- The desired leaderboard is already selected, upload the score and 
            -- wait for the onScoreUploaded callback
            --
            Steamworks.UploadScore ( nScore )
        end
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
