--------------------------------------------------------------------------------
--  Function......... : publishFileUpdate
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.publishFileUpdate ( sWorkshopItemID, sFilePath, sTitle, sDescription, sAI, sCallback )
--------------------------------------------------------------------------------
	
	if user.getAIState ( this.getUser ( ), "Steam" ) == "Idle" then 
        return 0 
    end
    
    Steamworks.PublishWorkshopFileUpdate ( sWorkshopItemID, sFilePath, this.sAppID ( ), sTitle, sDescription, sAI, sCallback )
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
