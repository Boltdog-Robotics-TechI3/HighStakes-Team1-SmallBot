#include "main.h"

/**
*  Runs once when the codebase is initialized. 
*  Used to set the attributes of objects and other tasks that need to happen at the start.
*/
void clamperInitialize() {

}

/** 
*  Runs every opcontrol cycle. 
*  This method is used for robot control and printing, as well as anything else
*  that needs to happen every update cycle in driver control.
*
*  Note: This method is not run during autonomous. Any prints you put here
*  will not work unless the robot is in manual control mode.
*/
void clamperPeriodic() {
    if (driverController.get_digital_new_press(DIGITAL_B)) {
        toggleMogoClamp();
    }
}

void toggleMogoClamp() {
    mogoClamp.toggle();
}