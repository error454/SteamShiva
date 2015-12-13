--------------------------------------------------------------------------------
--  Function......... : statIncrement
--  Author........... : 
--  Description...... : Increment a stat by a delta
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.statIncrement ( sStatID, nDelta, nTime )
--------------------------------------------------------------------------------
    
    if user.getAIState ( this.getUser ( ), "Steam" ) == "Idle" then return 0 end
    
    local kType = hashtable.get ( this.htStatTypes ( ), sStatID )
	local nValue = Steamworks.GetStat ( sStatID, kType )
    
    if kType == Steamworks.kStatTypeAvgrate then
        Steamworks.UpdateAvgRateStat ( sStatID, nDelta, nTime )
    elseif kType == Steamworks.kStatTypeInt or kType == Steamworks.kStatTypeFloat then
        Steamworks.SetStat ( sStatID, nValue + nDelta, kType )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
