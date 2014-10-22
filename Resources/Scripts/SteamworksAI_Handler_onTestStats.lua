--------------------------------------------------------------------------------
--  Handler.......... : onTestStats
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function SteamworksAI.onTestStats (  )
--------------------------------------------------------------------------------
	
    log.message ( "Steamworks: *** Starting stats tests ***" )
    
    local sStatName, kStatType, nStatValue, bOk
    
    -- Reset all stats (use this for testing)
    -- TODO this doesn't reset achievements
    --Steamworks.ResetAllStats ( true )
    
    -- Update average rate
    -- If the player earned 77 points in the last round, which lasted 0.225 hours (13.5 minutes),
    -- that would be SteamUserStats()->UpdateAvgRateStat( "AvgPointsPerHour", 77, 0.225 )
    sStatName = "AverageSpeed"
    bOk = Steamworks.UpdateAvgRateStat ( sStatName, 77, 0.225 )
    if ( bOk ) then
        log.message ( "Steamworks: UpdateAvgRateStat for "..sStatName.." successful." )
    else
        log.warning ( "Steamworks: UpdateAvgRateStat for "..sStatName.." failed!" )
    end
    
    sStatName = "NumLosses"
    bOk = Steamworks.SetStat ( sStatName, 666, Steamworks.kStatTypeInt )
    if ( bOk ) then
        log.message ( "Steamworks: SetStat for "..sStatName.." successful." )
    else
        log.warning ( "Steamworks: SetStat for "..sStatName.." failed!" )
    end
    
    -- define our stats
    hashtable.add ( this.htStats ( ), "NumGames", Steamworks.kStatTypeInt )
    hashtable.add ( this.htStats ( ), "NumWins", Steamworks.kStatTypeInt )
    hashtable.add ( this.htStats ( ), "NumLosses", Steamworks.kStatTypeInt )
    hashtable.add ( this.htStats ( ), "FeetTraveled", Steamworks.kStatTypeFloat )
    hashtable.add ( this.htStats ( ), "MaxFeetTraveled", Steamworks.kStatTypeFloat )
    hashtable.add ( this.htStats ( ), "AverageSpeed", Steamworks.kStatTypeAvgrate )
    
    for i = 0, hashtable.getSize ( this.htStats ( ) ) -1 do
        sStatName = hashtable.getKeyAt ( this.htStats ( ), i )
        kStatType = hashtable.getAt ( this.htStats ( ), i )
        nStatValue = Steamworks.GetStat ( sStatName, kStatType )
        log.message ( "Steamworks: Stat name: "..sStatName.."\t\tvalue: "..nStatValue )
    end
    
    this.bStatsTestRunning ( false )
    log.message ( "Steamworks: *** Stats tests finished***" )
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
