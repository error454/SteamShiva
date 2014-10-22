--------------------------------------------------------------------------------
--  Handler.......... : onAchievementStored
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function SteamworksAI.onAchievementStored ( sAchievementName, nCurProgress, nMaxProgress )
--------------------------------------------------------------------------------
	
    log.message ( "Steamworks: handler onAchievementStored called" )
    if ( nMaxProgress == 0 ) then
        log.warning ( "Steamworks: achievement '"..sAchievementName.."' was stored and achieved." )
    else
        log.warning ( "Steamworks: achievement '"..sAchievementName.."' was stored. Progesss: "..nCurProgress.."/"..nMaxProgress )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
