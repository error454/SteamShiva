--------------------------------------------------------------------------------
--  Handler.......... : onFoundLeaderboard
--  Author........... : 
--  Description...... : Callback from steam API
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.onFoundLeaderboard ( bOK )
--------------------------------------------------------------------------------
	
    if bOK then
        if table.getSize ( this.tPendingScores ( ) ) > 1 then
            --
            -- Set the selected leaderboard name
            --
            local sLeaderboardName, nScore = table.getRangeAt ( this.tPendingScores ( ), 0, 2 )
            this.sLeaderboardSelected ( sLeaderboardName )
            log.message ( this.sDebugLabel ( ), "Selected leaderboard ", sLeaderboardName )
            log.message ( this.sDebugLabel ( ), "Submitting score ", nScore )
            
            --
            -- Submit the score and wait for onScoreUploaded callback
            --
            Steamworks.UploadScore ( nScore )            
        end
    else
        -- TODO: implement retry?
        log.warning ( this.sDebugLabel ( ), "Could not find leaderboard" )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
