--------------------------------------------------------------------------------
--  Handler.......... : onQueryWorkshopUserContent
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.onQueryWorkshopUserContent ( nResult, nResultsReturned, nTotalResults, sFileID, sTitle, sDescription, nLastUpdate, sFilename, bIsOwner, sOwner, nScore  )
--------------------------------------------------------------------------------
	
	log.message ( nResult + 1, "/", nResultsReturned, " of ", nTotalResults, " ", sTitle, ": ", sDescription, " ", "Updated: ", nLastUpdate, " Owner: ", bIsOwner, " | ", sFileID, " ", sOwner )
    
    --
    -- Throw result in a table
    --
    local tWorkshopItem = table.newInstance ( )
    table.add ( tWorkshopItem, sTitle )
    table.add ( tWorkshopItem, sDescription )
    table.add ( tWorkshopItem, nLastUpdate )
    table.add ( tWorkshopItem, bIsOwner )
    table.add ( tWorkshopItem, sFilename )
    table.add ( tWorkshopItem, sFileID )
    table.add ( tWorkshopItem, sOwner )
    table.add ( tWorkshopItem, nScore )

    hashtable.add ( this.htWorkshopItems ( ), sFileID .. "-" .. sFilename, tWorkshopItem )

    if nResult == nResultsReturned - 1 then
        if nTotalResults > 50 then
            -- Query the next page of items
            this.nLastQueryPage ( this.nLastQueryPage ( ) + 1 )
            Steamworks.QueryWorkshopUserContent ( this.nLastWorkshopQuery ( ), this.nLastWorkshopSort ( ), this.sAppID ( ), this.sAppID ( ), this.nLastQueryPage ( ) )
        else
            this.bQueryComplete ( true )
            
            if this.bForceDownloadAfterQuery ( ) then
                -- Add all files to be downloaded
                for i = 0, hashtable.getSize ( this.htWorkshopItems ( ) ) - 1 do
                    local t = hashtable.getAt ( this.htWorkshopItems ( ), i )
                    local sID = table.getAt ( t, 5 )
                    table.add ( this.tDownloadQueue ( ), sID )
                end
                
                -- You should probably look at this function before calling it
                --this.deleteInvalidWorkshopFiles ( this.htWorkshopItems ( ) )
                
                if table.getSize ( this.tDownloadQueue ( ) ) > 0 then
                    local sKey = table.getFirst ( this.tDownloadQueue ( ) )
                    this.downloadWorkshopItem ( sKey )
                end
                this.bForceDownloadAfterQuery ( false )
            end
        end
    end
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
