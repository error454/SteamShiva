--------------------------------------------------------------------------------
--  State............ : Debug
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.Debug_onLoop ( )
--------------------------------------------------------------------------------
	
	Steamworks.RunCallbacks ( )
    
    local hBreadcrumb = hud.getComponent ( this.getUser ( ), "SteamDebug.Breadcrumb" )
    hud.setLabelText ( hBreadcrumb, "MEM: " .. math.trunc(debug.getTotalMemoryUsed ( ) / 1024, 2) .. " kb" )
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
