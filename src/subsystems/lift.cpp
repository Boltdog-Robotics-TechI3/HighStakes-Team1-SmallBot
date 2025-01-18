#include "main.h"

/** 
*  Runs once when the codebase is initialized. 
*  Used to set the attributes of objects and other tasks that need to happen at the start.
*/
void liftInitialize() {
    lift.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);

    lift.setCurrentLimit(2500);
}

/**
*  Runs every opcontrol cycle. 
*  This method is used for robot control and printing, as well as anything else
*  that needs to happen every update cycle in driver control.
*
*  Note: This method is not run during autonomous. Any prints you put here
*  will not work unless the robot is in manual control mode.
*/
void liftPeriodic() {
    if (driverController.get_digital(DIGITAL_R1)) {
        setLiftSpeed(1);
    } 
    else if (driverController.get_digital(DIGITAL_R2)) {
        setLiftSpeed(-1);
    }    
    else {
        setLiftSpeed(0);
    }
}

/**
* Sets the speed of the lift motor
*
* @param speed The speed to set the lift motor to, from -1 to 1.
*/
void setLiftSpeed(double speed){
    lift.controllerSet(speed);
}

void eject() {
    setLiftSpeed(1);
    pros::delay(500);
    setLiftSpeed(0);
}