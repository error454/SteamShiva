--------------------------------------------------------------------------------
--  Handler.......... : onDebugUpdateStat
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.onDebugUpdateStat (  )
--------------------------------------------------------------------------------
	
	--
	-- Get selected list item and update the stat with the value in the edit text
	--
    local hList = hud.getComponent ( this.getUser ( ), "SteamDebug.StatList" )
    local hValue = hud.getComponent ( this.getUser ( ), "SteamDebug.StatValue" )
    
    local nValue = hud.getEditText ( hValue )
    
    local bIsNumber = true
    for i = 0, string.getLength ( nValue ) - 1 do
        local nByte = string.getByte ( nValue, i )
        if nByte < 48 or nByte > 57 then
            bIsNumber = false
            break
        end
    end
    
    if bIsNumber and string.getLength ( nValue ) > 0 then
        nValue = nValue + 0

        if hList then
            local nItem = hud.getListSelectedItemAt ( hList, 0 )
            if nItem > 0 then
                local sName = hashtable.getKeyAt ( this.htStatTypes ( ), nItem - 1 )
                this.statIncrement ( sName, nValue, application.getTotalFrameTime ( ) )
                log.message ( this.sDebugLabel ( ), "Incrementing stat ", sName, " by ", nValue )
                
                Steamworks.StoreStats ( )
                hud.setEditText ( hValue, "" )
            end
        end
    end
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
