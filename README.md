# SteamWorks Plugin README #

## Details ##
This is a plugin to integrate the Steamworks SDK into the Shiva 3D game engine. Right now this is built with:
* Steamworks 1.35
* Shiva 1.9.2

## Credits ##
This plugin was started as a joint effort between Shaderman and error454. error454 now maintains it and uses it in Rage Runner.
The last error454 version was 1.29, versions 1.34 and 1.35 were compiled by broozar from ShiVaTechnologies SAS.
DLC addition by Tuomas Karmakallio.
Steam Controller addition by Felix Caffier.


# Basic Configuration #
0. Copy the steam_api(64).dll/(dylib/so) to the root of your project directory. This has to be done after exporting your game project as well.
1. Add the file **steam_appid.txt** to the folder where your shiva editor executable is. In the file, put your steam app ID, or **480** if you want to run in test mode. 480 is the appID of "Spacewar", the Steam SDK test project.
2. Add the Steam AI as a user AI.
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


## DLC Stuff ##
1. in the Steam.dlcInit ( ) Lua function, declare your DLC:
```
htAdd ( ht, "MyDlcName", 123456 )  -- where 123456 is the Dlc Id
```

2. check for Dlc by calling :
```
user.sendEventImmediate ( hUser, "Steam", "onDlcItemConfirmation", "123456" )
```

3. optionally, you can pass an environment variable, and the function will save the boolean value to it
```
user.sendEventImmediate ( hUser, "Steam", "onDlcItemConfirmation", "123456", "my_boolean_env_variable" )
```

Note that a user may switch Dlc on and off in their game control panel in Steam, so the status should always be checked on launch.


# Controller Setup #
## Steam pre-config ##
0. Read https://partner.steamgames.com/documentation/steamcontroller
1. Create an In-Game Actions file according to above in-game specifications, or use the game_actions_example.vdf Portal 2 example file. -- Important: If you want to test it first with the default demo game "SpaceWar" (ID 480), do NOT make a game_actions_480.vdf.
2. Steam tells you to make a Steam shortcut with "-forcecontrollerappid <your game's AppID>" (example: "-forcecontrollerappid 480" for the "Spacewar" demo game), but I found that quite pointless, so don't do it.
3. If you want to test with the SpaceWar game, here are the strings you need to know: ActionSets "menu_controls,ship_controls", Analog "analog_controls", Digital "turn_left,turn_right,forward_thrust,backward_thrust,fire_lasers,pause_menu,menu_up,menu_down,menu_left,menu_right,menu_select,menu_cancel"
4. Assigning buttons to your game actions has to be done from Steam Big Picture Mode. There is no other way. Valve says: "Run Steam in Big Picture mode, and navigate to your game's Game Details page. Select Manage Game, and then Configure Controller. If you receive any errors at this point, they'll be identifying issues in your IGA file and you'll need to go fix them."
5. "If you don't receive any errors, you're now looking at an empty controller configuration for your game, and it should be fully aware of your in-game actions. Use the UI to create a default configuration. Make sure you set defaults for all your In-Game Action Sets, not just the first one.""
6. "Once you've got a configuration, save it privately. Don't publish it, because your game is not yet ready to receive IGAs."
7. If you just want to run the SpaceWar test game, run Big Picture Mode, go to the Game Details page, configure your controls there, then close Big Picture Mode again, go to ShiVa and you should be able to use the setup you just configured.

Feel free to use the steamcon_ icons in the project, they are just renamed versions of the "Official Controller Glyphs" from steam/partner/controller/SteamControllerGlyphs_v1.zip

## ShiVa config ##
0. Everything Steam Controller related has the prefix "Scon", short for "Steam Controller", somewhere in the name.
1. Add your digital, analog and action set strings to the Steam.scon_* AIModel member variables, or open the function Steam.initSCon() and add them there if you like text editing better.

## Using the Steam Controller in ShiVa ##
- All connected controllers will be written automatically into the table Steam.tSconIDs. It will be updated every frame and deletes/adds (dis)connected controllers for you.
- Before you can receive any input, you must tell a controller which actionSet you are using, for instance:
```
Steamworks.sconSetActionSet( table.getFirst (this.tSconIDs ( )), "ship_controls" )
```

Only call this one after you can be sure that the controller has been initialized, e.g. at the beginning of your main menu level, NOT in the init() function as the controller needs a couple of frames to register.
	
- You can now receive Digital and Analog actions from the controller. There are 3 new handlers for that:
```
Steam.onSconDigitalActionOn ( sControllerID, sAction, sActionSet, kSource )
Steam.onSconDigitalActionOff ( sControllerID, sAction, sActionSet, kSource )
Steam.onSconAnalogActionContinuous ( sControllerID, sAction, sActionSet, nX, nY, kSource, kSourceMode )
```

- DigitalActionOn and DigitalActionOff behave very much like onJoytickButtonUp/Down - thesy are events that only fire when something happens. sControllerID is the string representation of the UINT64 controller ID that is stored in tSconIDs which can be used to identify controllers. sAction and sActionSet are the action name/actionset name that belong to the event tat fired.
- kSource is a number that can be interpreted by the table tSconActionOrigins, for instance:
```
table.getAt ( this.tSconActionOrigins ( ), kSource )
```

- AnalogActionContinuous fires every frame no matter what, and thus behaves more like a regular function. nX and nY are the numbers that come back from e.g. the right touchpad. However, those numbers are also highly dependent on kSourceMode:
- kSourceMode is a number that tells you where the analog action originated from and how nX and nY have to be handled. kSourceMode can be interpreted by the table this.tSconSourceModes, for instance:
```
table.getAt ( this.tSconSourceModes ( ), kSourceMode )
```

- All buttons and analog inputs furthermore have a constant equivalent, for instance:
```
Steamworks.kSconButtonA
Steamworks.kSconButtonB
Steamworks.kSconButtonX
Steamworks.kSconButtonY
```

- All source modes furthermore have a constant equivalent, for instance:
```
Steamworks.kSconAnalogSourceModeRelativeMouse
Steamworks.kSconAnalogSourceModeJoystickMove
```

###Other useful functions:###
- sconGetConnectedControllers -- returns the number of currently connected controllers
- sconGetAnalogActionOrigin -- returns the kOrigin constant of a given analog action
- sconGetDigitalActionOrigin -- returns the kOrigin constant of a given digital action
- sconGetActionSet -- returns the current action set name for a given controller
- sconShowBindingPanel -- accesses the binding config panel for a given controller, only works in Big Picture Mode
- sconPulse -- sends a haptic feedback pulse to a given controller pad. Durations under 200 are barely noticable, durations over 800 do not seem to make the effect any more pronounced. Try 500, like so:
```
Steamworks.sconPulse( table.getFirst ( this.tSconIDs ( ) ), Steamworks.kSconRightPad, 500 )
```	
	

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
You will need to package the `libsteam_api.so` file that is in `Plugins\com.shaderman.steamworks\Contents\Linux` with your game.
The easiest way to do this is to place the file in a `libs/` folder in your game root and then set the `LD_LIBRARY_PATH` in a bash script before launching:

    #!/bin/bash
    #Set library path to find libsteam_api.so
    export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:./libs

    #Launch our game
    ./mygame
	
This plugin has only be compiled for Linux 64bit, which covers most recent machines, including SteamOS. The plugin will not work with the 32bit version of the ShiVa linux engine.
