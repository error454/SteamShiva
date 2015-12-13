--------------------------------------------------------------------------------
--  Handler.......... : onGameOverlayActivated
--  Author........... : 
--  Description...... : This gets called when the steam overlay is toggled
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function Steam.onGameOverlayActivated ( bActivated )
--------------------------------------------------------------------------------
	
    log.message ( this.sDebugLabel ( ), "GAME OVERLAY ACTIVATED ", bActivated )
    this.bIsOverlayActive ( bActivated )
    
    local hScene = application.getCurrentUserScene ( )
    local bIsPaused = scene.isPaused ( hScene )
    
    if bActivated then
        if bIsPaused then
            this.bWasAlreadyPaused ( true )
        end
        
        music.pause ( hScene, 1000 )
        scene.setPaused ( hScene, true )
    else
        if not this.bWasAlreadyPaused ( ) then
            scene.setPaused ( hScene, false )
            music.resume ( hScene, 1000 )
        end
        
        this.bWasAlreadyPaused ( false )
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
