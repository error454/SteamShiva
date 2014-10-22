--------------------------------------------------------------------------------
--  Handler.......... : onWorkshopDownloadComplete
--  Author........... : 
--  Description...... : Called when a workshop download has completed or failed
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.onWorkshopDownloadComplete ( bSuccess )
--------------------------------------------------------------------------------
    
    --
    -- If the download queue is not empty then download the next item in line
    --
	log.message ( "Download completed: ", bSuccess )
    this.bDownloading ( false )
    if table.getSize ( this.tDownloadQueue ( ) ) > 0 then
        local sID = table.getFirst ( this.tDownloadQueue ( ) )
        table.removeFirst ( this.tDownloadQueue ( ) )
        this.downloadWorkshopItem ( sID )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
