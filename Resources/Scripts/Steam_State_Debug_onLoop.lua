--------------------------------------------------------------------------------
--  State............ : Debug
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.Debug_onLoop ( )
--------------------------------------------------------------------------------
	
	Steamworks.RunCallbacks ( )
    
    if this.bSconRequested ( ) == true then
        Steamworks.sconLoop ( )
    end
    
    local hBreadcrumb = hud.getComponent ( this.getUser ( ), "SteamDebug.Breadcrumb" )
    hud.setLabelText ( hBreadcrumb, "MEM: " .. math.trunc(debug.getTotalMemoryUsed ( ) / 10548576, 5) .. " Mb" )
	
    
    --[[
    -- crude controller ID logging
    local tab = this.tSconIDs ( )
    log.message ( "-------------------------" )
    for i=0, table.getSize ( tab ) - 1 do
        log.message ( "Controller #" .. i .. ": " .. table.getAt ( tab, i ) )
    end
    ]]--
    
    -- crude action set activation for SpaceWar testing
    -- Steamworks.sconSetActionSet( table.getFirst (this.tSconIDs ( )), "menu_controls" )
    -- Steamworks.sconSetActionSet( table.getFirst (this.tSconIDs ( )), "ship_controls" )
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
