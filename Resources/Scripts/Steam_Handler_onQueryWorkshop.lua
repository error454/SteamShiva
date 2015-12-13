--------------------------------------------------------------------------------
--  Handler.......... : onQueryWorkshop
--  Author........... : 
--  Description...... : Results will be posted in onQueryWorkshopUserContent
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.onQueryWorkshop ( kQueryType, kSortOrder )
--------------------------------------------------------------------------------
	
    if user.getAIState ( this.getUser ( ), "Steam" ) == "Idle" then return 0 end
    
    this.bQueryComplete ( false )
    hashtable.empty ( this.htWorkshopItems ( ) )
    
	this.nLastWorkshopQuery ( kQueryType )
    this.nLastWorkshopSort ( kSortOrder )
    this.nLastQueryPage ( 1 )
    Steamworks.QueryWorkshopUserContent ( this.nLastWorkshopQuery ( ), this.nLastWorkshopSort ( ), this.sAppID ( ), this.sAppID ( ), this.nLastQueryPage ( ) )
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
