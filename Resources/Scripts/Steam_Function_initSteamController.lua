--------------------------------------------------------------------------------
--  Function......... : initSteamController
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.initSteamController ( )
--------------------------------------------------------------------------------

    ----------------------------------------------------------------------------
    -- modify this to match your actions and action sets!
    ----------------------------------------------------------------------------

    -- script override for actions if member variables are empty
    
    if string.isEmpty ( this.scon_sDigitalActions ( ) ) then
        this.scon_sDigitalActions ( "" ) -- fill me if necessary!

        -- SPACEWAR ID480 example: 
        -- this.scon_sDigitalActions ( "turn_left,turn_right,forward_thrust,backward_thrust,fire_lasers,pause_menu,menu_up,menu_down,menu_left,menu_right,menu_select,menu_cancel" )
    end
    
    
    if string.isEmpty ( this.scon_sAnalogActions ( ) ) then
        this.scon_sAnalogActions ( "" ) -- fill me if necessary!
        
        -- SPACEWAR ID480 example: 
        -- this.scon_sAnalogActions ( "analog_controls" )
    end
    
    
    if string.isEmpty ( this.scon_sActionSets ( ) ) then
        this.scon_sActionSets ( "" ) -- fill me if necessary!
        
        -- SPACEWAR ID480 example: 
        -- this.scon_sActionSets ( "menu_controls,ship_controls" )
    end


    ----------------------------------------------------------------------------
    -- leave those bits down here alone!
    ----------------------------------------------------------------------------	
    
    -- find controllers
    local connum = Steamworks.sconGetConnectedControllers( )
    -- logging makes no sense here, as the controller needs 1-2 frames to initalize,
    -- so the output would be 0 anyway
    
	if connum >= 0 then
        --assign actions
        if not Steamworks.sconSetDigitalActions( this.scon_sDigitalActions ( ) ) then log.warning ( "FAILED: Digital Actions" ) end
        if not Steamworks.sconSetAnalogActions( this.scon_sAnalogActions ( ) ) then log.warning ( "FAILED: Analog Actions" ) end
        if not Steamworks.sconSetActionSets( this.scon_sActionSets ( ) ) then log.warning ( "FAILED: Action Sets" ) end
        
        this.bSconRequested ( true )
    else
        -- no controller connected
        log.warning ( "STEAM Controller connection problem" )
    end
    
    -- fill table with strings equivalent to constants for easier debugging
    local hT = this.tSconActionOrigins ( )
    table.empty ( hT )
    table.add ( hT, "kSconButtonNone" )
    table.add ( hT, "kSconButtonA" )
    table.add ( hT, "kSconButtonB" )
    table.add ( hT, "kSconButtonX" )
    table.add ( hT, "kSconButtonY" )
    table.add ( hT, "kSconButtonLeftBumper" )
    table.add ( hT, "kSconButtonRightBumper" )
    table.add ( hT, "kSconLeftGrip" )
    table.add ( hT, "kSconRightGrip" )
    table.add ( hT, "kSconButtonStart" )
    table.add ( hT, "kSconButtonBack" )
    table.add ( hT, "kSconLeftPadTouch" )
    table.add ( hT, "kSconLeftPadSwipe" )
    table.add ( hT, "kSconLeftPadClick" )
    table.add ( hT, "kSconLeftPadDPadUp" )
    table.add ( hT, "kSconLeftPadDPadDown" )
    table.add ( hT, "kSconLeftPadDPadLeft" )
    table.add ( hT, "kSconLeftPadDPadRight" )
    table.add ( hT, "kSconRightPadTouch" )
    table.add ( hT, "kSconRightPadSwipe" )
    table.add ( hT, "kSconRightPadClick" )
    table.add ( hT, "kSconRightPadDPadUp" )
    table.add ( hT, "kSconRightPadDPadDown" )
    table.add ( hT, "kSconRightPadDPadLeft" )
    table.add ( hT, "kSconRightPadDPadRight" )
    table.add ( hT, "kSconLeftTriggerPull" )
    table.add ( hT, "kSconLeftTriggerClick" )
    table.add ( hT, "kSconRightTriggerPull" )
    table.add ( hT, "kSconRightTriggerClick" )
    table.add ( hT, "kSconLeftStickMove" )
    table.add ( hT, "kSconLeftStickClick" )
    table.add ( hT, "kSconLeftStickUp" )
    table.add ( hT, "kSconLeftStickDown" )
    table.add ( hT, "kSconLeftStickLeft" )
    table.add ( hT, "kSconLeftStickRight" )
    table.add ( hT, "kSconGyroMove" )
    table.add ( hT, "kSconGyroPitch" )
    table.add ( hT, "kSconGyroYaw" )
    table.add ( hT, "kSconGyroRoll" )
    
    -- fill table with strings equivalent to analog source modes for easier debugging
    local ht = this.tSconSourceModes ( )
    table.empty ( ht )
    table.add ( ht, "kSconAnalogSourceModeNone" )
    table.add ( ht, "kSconAnalogSourceModeButtons" )
    table.add ( ht, "kSconAnalogSourceModeFourButtons" )
    table.add ( ht, "kSconAnalogSourceModeAbsoluteMouse" )
    table.add ( ht, "kSconAnalogSourceModeRelativeMouse" )
    table.add ( ht, "kSconAnalogSourceModeJoystickMove" )
    table.add ( ht, "kSconAnalogSourceModeJoystickCamera" )
    table.add ( ht, "kSconAnalogSourceModeScrollwheel" )
    table.add ( ht, "kSconAnalogSourceModeTrigger" )
    table.add ( ht, "kSconAnalogSourceModeTouchmenu" )
    
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
