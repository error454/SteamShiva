--------------------------------------------------------------------------------
--  Handler.......... : onEnterFrame
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function SteamworksAI.onEnterFrame (  )
--------------------------------------------------------------------------------
	
    if ( this.bInitialised ( ) ) then
        Steamworks.RunCallbacks ( )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
