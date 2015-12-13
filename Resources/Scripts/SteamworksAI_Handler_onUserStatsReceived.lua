--------------------------------------------------------------------------------
--  Handler.......... : onUserStatsReceived
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function SteamworksAI.onUserStatsReceived ( bOk )
--------------------------------------------------------------------------------
	
    if ( bOk ) then
        log.message ( "Steamworks: handler onUserStatsReceived called - OK" )
        if ( not this.bAchievementTestRunning ( ) ) then
            this.bAchievementTestRunning ( true )
            this.sendEvent ( "onTestAchievements" )
        end
        if ( not this.bStatsTestRunning ( ) ) then
            this.bStatsTestRunning ( true )
            this.sendEvent ( "onTestStats" )
        end
    else
        log.warning ( "Steamworks: handler onUserStatsReceived called - ERROR" )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
