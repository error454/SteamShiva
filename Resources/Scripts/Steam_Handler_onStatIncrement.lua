--------------------------------------------------------------------------------
--  Handler.......... : onStatIncrement
--  Author........... : 
--  Description...... : Increment the specified stat, but don't store it
--                      sStatID - The id of the stat
--                      nDelta  - The amount to increment the value
--                      nTime   - The time value to use for kStatTypeAvgrate
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.onStatIncrement ( sStatID, nDelta, nTime )
--------------------------------------------------------------------------------
    
    this.statIncrement ( sStatID, nDelta, nTime )
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
