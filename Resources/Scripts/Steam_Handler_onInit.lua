--------------------------------------------------------------------------------
--  Handler.......... : onInit
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.onInit (  )
--------------------------------------------------------------------------------
	
    this.achievementsInit ( )
    this.statsInit ( )
	local bSuccess = Steamworks.Init ( "Steam" )

    if bSuccess then
        if this.bDebug ( ) then
            this.Debug ( )
        else
            this.Running ( )
        end
    end
    
    -- For UGC, you need to make sure that your directories exist
    --[[
    Steamworks.MakeDir ( system.getDocumentsDirectory ( ) .. "/RageRunner" )
    Steamworks.MakeDir ( system.getDocumentsDirectory ( ) .. "/RageRunner/Mine" )
    Steamworks.MakeDir ( system.getDocumentsDirectory ( ) .. "/RageRunner/UGC" )
	]]
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
