--------------------------------------------------------------------------------
--  Handler.......... : onInit
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function SteamworksAI.onInit (  )
--------------------------------------------------------------------------------
	
    local hUser = application.getCurrentUser ( )
    hud.newTemplateInstance ( hUser, "SteamworksHUD", "SteamworksHUD" )
    
    -- Initialise Steamworks and pass the calling AI model, we need it for callbacks
	local bOk = Steamworks.Init ( "SteamworksAI" )
    this.bInitialised ( bOk )
    
    if ( not bOk ) then
        -- Steam API initialisation problem
        log.warning ( "Steamworks: Initialisation problem. Is the Steam client running?" )
    else
        -- just print out some info
        local sPlayerName = Steamworks.GetLocalPlayerName ( )
        log.message ( "Steamworks: Local player name: "..sPlayerName )
        local hComponent = hud.getComponent ( hUser, "SteamworksHUD.lblPlayerName" )
        hud.setLabelText ( hComponent, sPlayerName )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
