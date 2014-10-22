--------------------------------------------------------------------------------
--  Handler.......... : onUserStatsStored
--  Author........... : 
--  Description...... : Will receive a callback onUserStatsStored when stats have been stored.
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.onUserStatsStored ( bOK )
--------------------------------------------------------------------------------
	
    log.message ( this.sDebugLabel ( ), "User stats were stored" )
    
    if bOK then
        if this.bDebug ( ) then
            this.debugPrintStats ( )
        end
    end
        
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
