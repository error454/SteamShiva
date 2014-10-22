--------------------------------------------------------------------------------
--  Handler.......... : onDebugToggleAchievement
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.onDebugToggleAchievement (  )
--------------------------------------------------------------------------------
	
	--
	-- Get selected list item and toggle the achivement status
	--
    local hList = hud.getComponent ( this.getUser ( ), "SteamDebug.MenuList" )
    if hList then
        local nItem = hud.getListSelectedItemAt ( hList, 0 )
        if nItem > 0 then
            local sAchievement = table.getAt ( this.tAchievements ( ), nItem - 1 )
            log.message ( this.sDebugLabel ( ), "Toggling achievement ", sAchievement )
            
            local bAchieved = Steamworks.GetAchievement ( sAchievement )
            
            if bAchieved then
                Steamworks.ClearAchievement ( sAchievement )
            else
                Steamworks.SetAchievement ( sAchievement )
            end
            
            Steamworks.StoreStats ( )
        end
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
