--------------------------------------------------------------------------------
--  State............ : Running
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.Running_onEnter ( )
--------------------------------------------------------------------------------
	
    -- This commented out portion would initialize User Generated Content (Workshop) and initiate download of it.
    --[[
    -- Where the UGC downloads too, note that this was created in onInit
	Steamworks.SetUGCDownloadLocation ( system.getDocumentsDirectory ( ) .. "/RageRunner/UGC/" )
    
    -- Init the Workshop Query variables
	this.nLastWorkshopQuery ( Steamworks.kWorkshopQuerySubscribed )
    this.nLastWorkshopSort ( Steamworks.kWorkshopListSortSubscriptionDateDesc )
    this.nLastQueryPage ( 1 )
    this.bForceDownloadAfterQuery ( true )
    
    -- Query the workshop content, this will download any subscribed workshop items
    Steamworks.QueryWorkshopUserContent ( this.nLastWorkshopQuery ( ), this.nLastWorkshopSort ( ), this.sAppID ( ), this.sAppID ( ), this.nLastQueryPage ( ) )
    ]]
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
