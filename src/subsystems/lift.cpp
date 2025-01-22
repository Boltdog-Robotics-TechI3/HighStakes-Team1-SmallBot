#include "main.h"

double highestHueDetected = 0;
double poopCount = 0;

/** 
*  Runs once when the codebase is initialized. 
*  Used to set the attributes of objects and other tasks that need to happen at the start.
*/
void liftInitialize() {
    lift.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);

    lift.setCurrentLimit(2500);

    opticalSensor.set_led_pwm(50);
    opticalSensor.set_integration_time(5);
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
    driverController.set_text(0, 0, std::to_string(poopCount));
    if (detectsBadColor()) {
        poopCount++;
        eject();
    }
    else {
        // driverController.clear_line(0);
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

    if (highestHueDetected < opticalSensor.get_hue()) {
        highestHueDetected = opticalSensor.get_hue();
    }

    driverController.set_text(1, 1, std::to_string(highestHueDetected));

}

/**
* Sets the speed of the lift motor
*
* @param speed The speed to set the lift motor to, from -1 to 1.
*/
void setLiftSpeed(double speed){
    lift.controllerSet(speed);
}

bool detectsBadColor() {
    if (redAlliance) {
        if (opticalSensor.get_hue() >= 130 && opticalSensor.get_hue() <= 230) {
            return true;
        }
    }
    else if (blueAlliance) {
        if (opticalSensor.get_hue() >= 1 && opticalSensor.get_hue() <= 35) {
            return true;
        }
    }
    return false;
}

void eject() {
    setLiftSpeed(1);
    pros::delay(150);
    setLiftSpeed(0);
    pros::delay(250);
}