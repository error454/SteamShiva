--------------------------------------------------------------------------------
--  Function......... : statsInit
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.statsInit ( )
--------------------------------------------------------------------------------
	
	--
	-- Initialize your game's stats here
	--
    local t = this.htStatTypes ( )
    local hAdd = hashtable.add
    hAdd ( t, "NumGames",               Steamworks.kStatTypeInt )
    hAdd ( t, "NumWins",                Steamworks.kStatTypeInt )
    hAdd ( t, "NumLosses",              Steamworks.kStatTypeInt )
    hAdd ( t, "FeetTraveled",           Steamworks.kStatTypeFloat )
    hAdd ( t, "AverageSpeed",           Steamworks.kStatTypeFloat )
    hAdd ( t, "MaxFeetTraveled",        Steamworks.kStatTypeFloat )
   
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
