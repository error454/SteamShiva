--------------------------------------------------------------------------------
--  Handler.......... : onScoreUploaded
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.onScoreUploaded ( bOK )
--------------------------------------------------------------------------------
	
	if bOK then
        log.message ( this.sDebugLabel ( ), "Score was uploaded!" )
        --
        -- Score upload was a success, remove the 4 past entries from the table
        --
        table.removeFirst ( this.tPendingScores ( ) )
        table.removeFirst ( this.tPendingScores ( ) )
        
        -- Grab the AI and callback and send an event to them if they exist
        local sAI, sCallback = table.getRangeAt ( this.tPendingScores ( ), 0, 2 )
        table.removeFirst ( this.tPendingScores ( ) )
        table.removeFirst ( this.tPendingScores ( ) )
        
        if sAI and sCallback then
            user.sendEvent ( this.getUser ( ), sAI, sCallback, bOK )
        end
    else
        log.warning ( this.sDebugLabel ( ), "Could not upload score" )
        local sAI, sCallback = table.getRangeAt ( this.tPendingScores ( ), 2, 2 )
        if sAI and sCallback then
            user.sendEvent ( this.getUser ( ), sAI, sCallback, bOK )
        end
    end
    
    --
    -- Handle the next entries in the table and the clearing of the inUse flag
    --
    if table.getSize ( this.tPendingScores ( ) ) > 1 then
        local sLeaderboardName, nScore = table.getRangeAt ( this.tPendingScores ( ), 0, 2 )
        
        if this.sLeaderboardSelected ( ) ~= sLeaderboardName then
            log.message ( this.sDebugLabel ( ), "Selecting new leaderboard ", sLeaderboardName )
            --
            -- Request the leaderboard and wait for onFoundLeaderboard callback
            --
            Steamworks.FindLeaderboard ( sLeaderboardName )
        else
            log.message ( this.sDebugLabel ( ), "Uploading next score ", nScore )
            --
            -- The desired leaderboard is already selected, upload the score and 
            -- wait for the onScoreUploaded callback
            --
            Steamworks.UploadScore ( nScore )
        end
    else
        this.bLeaderboardsInUse ( false )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
