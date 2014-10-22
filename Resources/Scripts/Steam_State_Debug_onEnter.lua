--------------------------------------------------------------------------------
--  State............ : Debug
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.Debug_onEnter ( )
--------------------------------------------------------------------------------
	
    log.message ( this.sDebugLabel ( ), "Debug++" )
    --Steamworks.ResetAllStats ( true )
    
    --
    -- Setup the Achievement HUD
    --
	hud.newTemplateInstance ( this.getUser ( ), "SteamDebug", "SteamDebug" )
    local hList = hud.getComponent ( this.getUser ( ), "SteamDebug.MenuList" )
    hud.addListColumn ( hList )
    hud.addListColumn ( hList )
    hud.addListColumn ( hList )
    hud.addListColumn ( hList )
    hud.addListColumn ( hList )
    hud.addListItem ( hList, "" )
    
    -- ID
    hud.setListColumnTextAlignmentAt ( hList, 0, hud.kAlignLeft, hud.kAlignCenter )
    hud.setListColumnWidthAt ( hList, 0, 20 )
    
    -- Name
    hud.setListColumnTextAlignmentAt ( hList, 1, hud.kAlignLeft, hud.kAlignCenter )
    hud.setListColumnWidthAt ( hList, 1, 20 )
    
    -- Description
    hud.setListColumnTextAlignmentAt ( hList, 2, hud.kAlignLeft, hud.kAlignCenter )
    hud.setListColumnWidthAt ( hList, 2, 40 )
    
    -- Percent
    hud.setListColumnTextAlignmentAt ( hList, 3, hud.kAlignCenter, hud.kAlignCenter )
    hud.setListColumnWidthAt ( hList, 3, 10 )
    
    -- Achieved
    hud.setListColumnTextAlignmentAt ( hList, 4, hud.kAlignCenter, hud.kAlignCenter )
    hud.setListColumnWidthAt ( hList, 4, 10 )
    
    -- Create the labels
    local hID = this.debugCreateLabel ( "ID", "SteamDebug.ID" )
    local hName = this.debugCreateLabel ( "Name", "SteamDebug.Name" )
    local hDescription = this.debugCreateLabel ( "Desc.", "SteamDebug.Desc" )
    local hPercent = this.debugCreateLabel ( "%", "SteamDebug.Percent" )
    local hAchieved = this.debugCreateLabel ( "Achieved", "SteamDebug.Achieved" )
    
    -- Set the labels as the content
    hud.setListItemChildAt ( hList, 0, 0, hID )
    hud.setListItemChildAt ( hList, 0, 1, hName )
    hud.setListItemChildAt ( hList, 0, 2, hDescription )
    hud.setListItemChildAt ( hList, 0, 3, hPercent )
    hud.setListItemChildAt ( hList, 0, 4, hAchieved )
    
    --
    -- Setup the Stats HUD
    --
    local hStatsList = hud.getComponent ( this.getUser ( ), "SteamDebug.StatList" )
    hud.addListColumn ( hStatsList )
    hud.addListColumn ( hStatsList )
    hud.addListColumn ( hStatsList )
    hud.addListColumn ( hStatsList )
    hud.addListItem ( hStatsList, "" )
    
    -- Name
    hud.setListColumnTextAlignmentAt ( hStatsList, 0, hud.kAlignLeft, hud.kAlignCenter )
    hud.setListColumnWidthAt ( hStatsList, 0, 33 )
    
    -- Type
    hud.setListColumnTextAlignmentAt ( hStatsList, 1, hud.kAlignLeft, hud.kAlignCenter )
    hud.setListColumnWidthAt ( hStatsList, 1, 33 )
    
    -- Value
    hud.setListColumnTextAlignmentAt ( hStatsList, 2, hud.kAlignLeft, hud.kAlignCenter )
    hud.setListColumnWidthAt ( hStatsList, 2, 33 )
    
    local hStatName = this.debugCreateLabel ( "Name", "SteamDebug.StatName" )
    local hStatType = this.debugCreateLabel ( "Type", "SteamDebug.StatType" )
    local hStatValue = this.debugCreateLabel ( "Value", "SteamDebug.StatValueH" )
    hud.setListItemChildAt ( hStatsList, 0, 0, hStatName )
    hud.setListItemChildAt ( hStatsList, 0, 1, hStatType )
    hud.setListItemChildAt ( hStatsList, 0, 2, hStatValue )
    
    --
    -- Show the player name
    --
    local hPlayerName = hud.getComponent ( this.getUser ( ), "SteamDebug.PlayerName" )
    local sPlayerName = Steamworks.GetLocalPlayerName ( )
    hud.setLabelText ( hPlayerName, "Player: "..sPlayerName )
        
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
