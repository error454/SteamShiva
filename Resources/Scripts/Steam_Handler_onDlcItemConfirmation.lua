--------------------------------------------------------------------------------
--  Handler.......... : onDlcItemConfirmation
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.onDlcItemConfirmation ( sDlcAppId, sOptionalEnvironmentVariable )
--------------------------------------------------------------------------------
	
    --[[
    if system.getOSType ( ) ~= system.kOSTypeWindows then
        return -- plugin not updated for osx yet
    end
    --]]
    
    local sPlayer = Steamworks.GetLocalPlayerName ( )
    
    if string.getLength ( sPlayer ) > 0 then
    
        local bInstalled = Steamworks.IsDlcInstalled ( sDlcAppId )
        
        -- if an env var has been given and if the value is true we set it
        if bInstalled and sOptionalEnvironmentVariable then
            log.message( "Dlc id: ",sDlcAppId," confirmed and saved as ",sOptionalEnvironmentVariable )
            application.setCurrentUserEnvironmentVariable ( sOptionalEnvironmentVariable, true )
            
        else
            log.message( "Dlc :",sOptionalEnvironmentVariable," not installed" )
            application.setCurrentUserEnvironmentVariable ( sOptionalEnvironmentVariable, false )
        end
        
    else
        log.message( "No Steam Player found" )
    end
    

--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
