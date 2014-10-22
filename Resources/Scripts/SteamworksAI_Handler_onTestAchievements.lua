--------------------------------------------------------------------------------
--  Handler.......... : onTestAchievements
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function SteamworksAI.onTestAchievements (  )
--------------------------------------------------------------------------------
	
	log.message ( "Steamworks: *** Starting achievement tests ***" )
    
    local sAchievementID = "ACH_WIN_ONE_GAME"
    --local sAchievementID = "ACH_WIN_100_GAMES"
    --local sAchievementID = "ACH_TRAVEL_FAR_ACCUM"
    --local sAchievementID = "ACH_TRAVEL_FAR_SINGLE"
    
    -------------------------------------------------------------------
    -- Set an achievement
    -------------------------------------------------------------------
    local bOk = Steamworks.SetAchievement ( sAchievementID )
    if ( bOk ) then
        log.message ( "Steamworks: Achievement '"..sAchievementID.."' was set" )
    else
        log.warning ( "Steamworks: Achievement '"..sAchievementID.."' wasn't set" )
    end
    
    -------------------------------------------------------------------
    -- Get the number of achievements
    -------------------------------------------------------------------
    local nNumAchievements = Steamworks.GetNumAchievements ( )
    log.message ( "Steamworks: Number of achievements: "..nNumAchievements )
    
    -------------------------------------------------------------------
    -- Iterate over all achievements and show their status ordered by completion
    -------------------------------------------------------------------
    if ( nNumAchievements > 0 ) then
        local nIndex, sName, nPercent, bAchieved, nOldIndex, sAchieved
        
        for i = 0, nNumAchievements -1 do
            if ( i == 0 ) then -- get the first achievement
                nIndex, sName, nPercent, bAchieved = Steamworks.GetMostAchievedAchievementInfo ( )
            else
                nOldIndex = nIndex
                nIndex, sName, nPercent, bAchieved = Steamworks.GetNextMostAchievedAchievementInfo ( nOldIndex )
            end
            
            if ( bAchieved ) then
                sAchieved = "\t\tstatus: achieved"
            else
                sAchieved = "\t\tstatus: not yet achieved"
            end
            
            log.message ( "Steamworks: Achievement index: "..i.."\t\tname: "..sName.."\t\t\tperecent completed: "..nPercent..sAchieved )
        end
    end
    
    -------------------------------------------------------------------
    -- Let's see if a single achievement was achieved already
    -------------------------------------------------------------------
    local bAchieved = Steamworks.GetAchievement ( sAchievementID )
    if ( bAchieved ) then
        log.message ( "Steamworks: Achievement '"..sAchievementID.."' was achieved." )
    else
        log.message ( "Steamworks: Achievement '"..sAchievementID.."' was not yet achieved." )
    end
    
    -------------------------------------------------------------------
    -- Get some info about an achievement
    -------------------------------------------------------------------
    local sName         = Steamworks.GetAchievementName ( sAchievementID )
    local sDescription  = Steamworks.GetAchievementDescription ( sAchievementID )
    local sIcon         = Steamworks.GetAchievementIcon ( sAchievementID )
    local nPercent      = Steamworks.GetAchievementAchievedPercent ( sAchievementID )
    log.message ( "Steamworks: Getting info for achievement ID '"..sAchievementID
            .."\t\tname: "..sName
            .."\t\tdescription: "..sDescription
            .."\t\ticon: "..sIcon
            .."\t\tpercent achieved: "..nPercent )
    
    -------------------------------------------------------------------
    -- Clear an achievement
    -------------------------------------------------------------------
    local bOk = Steamworks.ClearAchievement ( sAchievementID )
    if ( bOk ) then
        log.message ( "Steamworks: Achievement '"..sAchievementID.."' was cleared" )
    else
        log.warning ( "Steamworks: Achievement '"..sAchievementID.."' wasn't cleared" )
    end
    
    -------------------------------------------------------------------
    -- Store our stats and achievements
    -------------------------------------------------------------------
    bOk = Steamworks.StoreStats ( )
    if ( bOk ) then
        log.message ( "Steamworks: Stats and achievements were stored" )
    else
        log.warning ( "Steamworks: Stats and achievements weren't stored" )
    end
    
    this.bAchievementTestRunning ( false )
    log.message ( "Steamworks: *** Achievement tests finished***" )
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
