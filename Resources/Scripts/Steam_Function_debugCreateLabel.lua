--------------------------------------------------------------------------------
--  Function......... : debugCreateLabel
--  Author........... : 
--  Description...... : Creates labels for the list headers
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.debugCreateLabel ( sText, sTag )
--------------------------------------------------------------------------------
	
	local hLabel = hud.getComponent ( this.getUser ( ), sTag )
    
    if not hLabel then
        hud.newComponent ( this.getUser ( ), hud.kComponentTypeLabel, sTag )
        hLabel = hud.getComponent ( this.getUser ( ), sTag )
        hud.setComponentSize ( hLabel, 100, 100 )
        hud.setComponentBackgroundColor ( hLabel, 0, 255, 80, 0)
        hud.setComponentBorderColor ( hLabel, 0, 255, 0, 255 )
        hud.setDefaultFont ( this.getUser ( ), "Dynamic" )
        hud.setComponentIgnoredByMouse ( hLabel, true )
        hud.setLabelTextAlignment ( hLabel, hud.kAlignCenter, hud.kAlignCenter)
        hud.setLabelTextEncoding ( hLabel, hud.kEncodingUTF8 )
    end
    
    hud.setLabelText ( hLabel, sText )
    
    return hLabel
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
