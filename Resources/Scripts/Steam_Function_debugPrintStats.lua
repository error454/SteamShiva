--------------------------------------------------------------------------------
--  Function......... : debugPrintStats
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.debugPrintStats ( )
--------------------------------------------------------------------------------
	
    local tAchievements = this.tAchievements ( )
    local hUser = this.getUser ( )
    local hListAchievements = hud.getComponent ( hUser, "SteamDebug.MenuList" )
    local hListStats = hud.getComponent ( hUser, "SteamDebug.StatList" )
    
    local nAchievements = Steamworks.GetNumAchievements ( )
    
    --
    -- Warn if the # of hard-coded achievements differs from the # queried from the server. This is bound to happen if you ever add
    -- achievements to an existing game.
    --
    if nAchievements ~= table.getSize ( tAchievements ) then
        log.warning ( this.sDebugLabel ( ), "Received ", nAchievements, " stats but only have ", table.getSize ( tAchievements ), " stats defined" )
    end
    
    --
    -- Remove everything but the list headers
    --
    for listI = hud.getListItemCount ( hListAchievements ) - 1, 1, -1 do
        hud.removeListItemAt ( hListAchievements, listI )
    end
    
    for listI = hud.getListItemCount ( hListStats ) - 1, 1, -1 do
        hud.removeListItemAt ( hListStats, listI )
    end 
    
    --
    -- Display achievement info in the HUD
    -- 
    for achievementI = 0, table.getSize ( this.tAchievements ( ) ) - 1 do
        local sAchievementID = table.getAt ( this.tAchievements ( ), achievementI )
        
        local bAchieved     = Steamworks.GetAchievement ( sAchievementID )
        local nPercent      = Steamworks.GetAchievementAchievedPercent ( sAchievementID )
        local sDescription  = Steamworks.GetAchievementDescription ( sAchievementID )
        local sName         = Steamworks.GetAchievementName ( sAchievementID )
        
        if hListAchievements then
            hud.addListItem ( hListAchievements, "" )
            local nListItem = hud.getListItemCount ( hListAchievements ) - 1
            
            -- Set the content
            hud.setListItemTextAt ( hListAchievements, nListItem, 0, sAchievementID )
            hud.setListItemTextAt ( hListAchievements, nListItem, 1, sName )
            hud.setListItemTextAt ( hListAchievements, nListItem, 2, sDescription )
            hud.setListItemTextAt ( hListAchievements, nListItem, 3, "" .. nPercent )
            hud.setListItemTextAt ( hListAchievements, nListItem, 4, bAchieved and "Y" or "N" )
        end
    end
	
    --
    -- Display stat info in the HUD
    --
    for statI = 0, hashtable.getSize ( this.htStatTypes ( ) ) - 1 do
        local sStatName = hashtable.getKeyAt ( this.htStatTypes ( ), statI )
        local kType = hashtable.get ( this.htStatTypes ( ), sStatName )
        local sType
        
            if kType == Steamworks.kStatTypeInt     then sType = "INT"
        elseif kType == Steamworks.kStatTypeFloat   then sType = "FLOAT"
        elseif kType == Steamworks.kStatTypeAvgrate then sType = "AVG" 
        end
        
        local nValue = Steamworks.GetStat ( sStatName, kType )
        
        if hListStats then
            hud.addListItem ( hListStats, "" )
            local nListItem = hud.getListItemCount ( hListStats ) - 1
            
            -- Set the content
            hud.setListItemTextAt ( hListStats, nListItem, 0, sStatName )
            hud.setListItemTextAt ( hListStats, nListItem, 1, sType)
            hud.setListItemTextAt ( hListStats, nListItem, 2, "" .. nValue )
        end
    end
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
