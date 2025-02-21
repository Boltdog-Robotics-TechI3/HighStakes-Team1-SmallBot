#include "main.h"

/**
*  Runs once when the codebase is initialized. 
*  Used to set the attributes of objects and other tasks that need to happen at the start.
*/
void clamperInitialize() {}

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
    if (driverController.get_digital_new_press(DIGITAL_X)) {
        toggleMogoClaw();
    }
    if (driverController.get_digital_new_press(DIGITAL_A)) {
        toggleMogoClawArm();
    }
}

/**
 * Toggles the state of the mogo clamper
 */
void toggleMogoClamp() {
    mogoClamp.toggle();
}

/**
 * Sets the state of the mogo clamper
 * 
 * @param state the state of the clamp: True for grab, False for release.
 */
void setMogoClamp(bool state) {
    if (state) {
        mogoClamp.extend();
    }
    else {
        mogoClamp.retract();
    }
}

void toggleMogoClawArm(){
    mogoClawArm.toggle();
}

void toggleMogoClaw() {
    mogoClaw.toggle();
}

/**
 * Sets the state of the mogo claw
 * 
 * @param state the state of the claw: True for down, False for up.
 */
void setMogoClaw(bool state) {
    if (state) {
        mogoClaw.extend();
    }
    else {
        mogoClaw.retract();
    }
}

/**
 * Sets the state of the mogo claw
 * 
 * @param state the state of the claw: True for down, False for up.
 */
void setMogoClawArm(bool state) {
    if (state) {
        mogoClawArm.extend();
    }
    else {
        mogoClawArm.retract();
    }
}