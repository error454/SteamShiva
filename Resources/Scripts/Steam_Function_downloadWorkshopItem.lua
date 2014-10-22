--------------------------------------------------------------------------------
--  Function......... : downloadWorkshopItem
--  Author........... : 
--  Description...... : Download a workshop item if it doesn't exist already
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.downloadWorkshopItem ( sKey )
--------------------------------------------------------------------------------
    
    --
    -- If there are no downloads, download this file. Otherwise add file to the queue.
    --
    if not this.bDownloading ( ) then
        this.bDownloading ( true )
        Steamworks.DownloadWorkshopFile ( sKey )
    else
        table.add ( this.tDownloadQueue ( ), sKey )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
