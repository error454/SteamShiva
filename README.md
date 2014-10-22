# Details and Stuff#
## Details ##
This is a plugin to integrate the Steamworks SDK into the Shiva 3D game engine. Right now this is built with:
* Steamworks 1.29a
* Shiva 1.9.2

## Linux Support ##
The Linux version of the plugin builds, but the binaries are out of date. The reason I haven't updated the binaries is due to linux builds having several issues when combined with the Steam client. These issues have been reported.

## Credits ##
This plugin was started as a joint effort between Shaderman and error454. error454 now maintains it and uses it in Rage Runner.

# Get the stuff #
If you don't need to modify the C++ portion of the plugin in any way, then download the **SteamShivaPrebuilt.zip**.

# Basic Configuration #
1. Add the file **steam_appid.txt** to the folder where your shiva editor executable is.
    1. In the file, put your steam app ID, or **480** if you want to run in test mode. (480 is the appid of Spacewar, the Steam SDK test project)
2. Add the Steam AI as a user AI
3. Add the Steam plugin to your project.
4. Edit the `statsInit` function and insert all of the stat names/types for your game.
5. Edit the `achievementsInit` function and add all your achievement identifiers.

# Debug Mode #
If you want to run in debug mode, set the `bDebug` variable to true.

# Usage #
When the Steam SDK initializes, it automatically grabs the stats and achievements for the current user. When those are available, `onUserStatsReceived` will be called. This callback will only be called once, after which you can interact with Stats and Achievements.
## Stats ##
### Reading ###
Use `Steamworks.GetStat` to get stat details. See `debugPrintStats` for an example of how to use these.

### Writing ###
Use the handlers:

    onStatIncrement ( sStatID, nDelta, nTime )
    onStatSetMax ( sStatID, nValue )

## Achievements ##
### Reading ###
Use the `Steamworks.GetAchievement*` to get achievement information. See `debugPrintStats` for an example of how to use these.

### Writing ###
Use the handler:

    onAchievementUnlock ( sAchievementID )

## Committing ##
When you increment stats and unlock achievements, the changes aren't committed to the Steam servers until you call the handler:

    onStatStore ( )

It's recommended to call this handler periodically. For instance, if you want users to immediately see when an achievement has been unlocked you should call `onStatStore` after unlocking the achievement.

## Leaderboards ##
### Read ###
To get leaderboard entries, call:

    onDownloadScores ( sAI, sHandler, sLeaderboardName, kLeaderboardRequest, start, nEnd )

You'll receive a callback to `sAI`, `sHandler` when the scores are available. The parameters passed to the callback are:

    nResult, nTotalResults, nGlobalRank, nScore, sUser


### Write ###
To submit a highscore to a leaderboard, call:

    onSubmitHighscore ( sLeaderboardName, nScore )

## Workshop Stuff ##
If you are implementing Steam Workshop, you'll need to do some additional configuration:
1. Create any required folders in `onInit` for example:

    Steamworks.MakeDir ( system.getDocumentsDirectory ( ) .. "/RageRunner" )
    Steamworks.MakeDir ( system.getDocumentsDirectory ( ) .. "/RageRunner/Mine" )
    Steamworks.MakeDir ( system.getDocumentsDirectory ( ) .. "/RageRunner/UGC" )

2. In `Running->onEnter` set your UGC download location and initiate the first workshop query.

    -- Where the UGC downloads too, note that this was created in onInit
    Steamworks.SetUGCDownloadLocation ( system.getDocumentsDirectory ( ) .. "/RageRunner/UGC/" )
    
    -- Init the Workshop Query variables
    this.nLastWorkshopQuery ( Steamworks.kWorkshopQuerySubscribed )
    this.nLastWorkshopSort ( Steamworks.kWorkshopListSortSubscriptionDateDesc )
    this.nLastQueryPage ( 1 )
    this.bForceDownloadAfterQuery ( true )
    
    -- Query the workshop content, this will download any subscribed workshop items
    Steamworks.QueryWorkshopUserContent ( this.nLastWorkshopQuery ( ), this.nLastWorkshopSort ( ), this.sAppID ( ), this.sAppID ( ), this.nLastQueryPage ( ) )

The remaining workshop stuff, well, I'm too lazy to document it right now, it works similarly to the leaderboards and is fully implemented.

# Misc Functions and Callbacks #

    onGameOverlayActivated ( bActivated )
    
Called when the steam overlay is activated/deactivated.  It's a good idea to pause/unpause your game here.

    onOpenItemInBrowser ( sItem )
Will open a steam item ID in the built-in steam browser.

If you need to know whether the Steam overlay is active you can call:

    Steam.overlayActive ( )

Platform Packaging Caveats
=====

Linux
----
You will need to package the `libsteam_api.so` file that is in `Plugins\com.shaderman.steamworks\Contents\Linux` with your game. The easiest way to do this is to place the file in a `libs/` folder in your game root and then set the `LD_LIBRARY_PATH` in a bash file before launching:

    #!/bin/bash
    #Set library path to find libsteam_api.so
    export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:./libs

    #Launch our game
    ./mygame