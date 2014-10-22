--------------------------------------------------------------------------------
--  Function......... : deleteInvalidWorkshopFiles
--  Author........... : 
--  Description...... : To be called when onQueryWorkshopUserContent has completed.
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.deleteInvalidWorkshopFiles ( ht )
--------------------------------------------------------------------------------
	
    local tResult = table.newInstance ( )
	system.findFiles ( tResult, system.getDocumentsDirectory ( ) .. "/RageRunner/UGC", "*" )
    
    -- Loop through all files
    for i = table.getSize ( tResult ) - 1, 0, -1 do
        local sFile = table.getAt ( tResult, i )
        
        -- If the file is in the hash, don't delete it
        if hashtable.contains ( ht, sFile ) then
            table.removeAt ( tResult, i )
        end
    end
    
    log.message ( "Delete the following files: " )
    for i = 0, table.getSize ( tResult ) - 1 do
        local sFile = table.getAt ( tResult, i )
        Steamworks.DeleteLocalWorkshopFile ( system.getDocumentsDirectory ( ) .. "/RageRunner/UGC/" .. sFile )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
