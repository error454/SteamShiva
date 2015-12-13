--------------------------------------------------------------------------------
--  Function......... : statSetMax
--  Author........... : 
--  Description...... : Set the stat with nValue if it's > current value
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.statSetMax ( sStatID, nValue )
--------------------------------------------------------------------------------
    
    if user.getAIState ( this.getUser ( ), "Steam" ) == "Idle" then return 0 end
    
    local kType = hashtable.get ( this.htStatTypes ( ), sStatID )
	local nCurrentValue = Steamworks.GetStat ( sStatID, kType )
    
    if kType == Steamworks.kStatTypeInt or kType == Steamworks.kStatTypeFloat then
        if nValue > nCurrentValue then
            Steamworks.SetStat ( sStatID, nValue, kType )
        end
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
