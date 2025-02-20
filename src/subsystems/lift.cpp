#include "main.h"

double highestHueDetected = 0;
double ejectionCount = 0;

bool isEjecting = false;

/** 
*  Runs once when the codebase is initialized. 
*  Used to set the attributes of objects and other tasks that need to happen at the start.
*/
void liftInitialize() {
    lift.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);

    lift.setCurrentLimit(2500);

    intakeA.set_voltage_limit(7200);
    intakeB.set_voltage_limit(7200);
    intakeGroup.set_voltage_limit(7200);

    intakeA.set_reversed(false);
    intakeB.set_reversed(true);

    intakeGroup.set_brake_mode(MOTOR_BRAKE_BRAKE);

    opticalSensor.set_led_pwm(50);
    opticalSensor.set_integration_time(10);

    pros::Task task(colorDetectionTask);
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
    // //driverController.set_text(0, 0,std::to_string(ejectionCount));

    if (driverController.get_digital(DIGITAL_R1)) {
        setLiftSpeed(1);
        setIntakeSpeed(1);
    } 
    else if (driverController.get_digital(DIGITAL_R2)) {
        setLiftSpeed(-1);
        setIntakeSpeed(-1);
    }    
    else if (driverController.get_digital(DIGITAL_L1)) {
        setLiftSpeed(0);
        setIntakeSpeed(1);
    }
    else {
        setLiftSpeed(0);
        setIntakeSpeed(0);
    }
    

    if (highestHueDetected < opticalSensor.get_hue()) {
        highestHueDetected = opticalSensor.get_hue();
    }

    // driverController.set_text(1, 1, std::to_string(highestHueDetected));

}

/**
* Sets the speed of the lift motor.
* This method will only work if the lift is not currently ejecting. This is
* to ensure that the ejection isnt interrupted by some other method calling the 
* setLiftSpeed() function.
*
* @param speed The speed to set the lift motor to, from -1 to 1.
*/
void setLiftSpeed(double speed) {
    if (!isEjecting) {
        lift.controllerSet(speed);
    }
}

/**
* Sets the speed of the intake.
*
* @param speed The speed to set the intake motors to, from -1 to 1.
*/
void setIntakeSpeed(double speed) {
    intakeGroup.move(speed * 127.0);
}

/**
 * Method that detects whether or not the hue currently detected by the
 * optical sensor is the hue of the other alliance's ring.
 * 
 * @returns True if the detected color is that of the wrong colored ring; False otherwise
 */
bool detectsBadColor() {
    if (redAlliance) {
        if (opticalSensor.get_hue() >= 130 && opticalSensor.get_hue() <= 230) {
            return true;
        }
    }
    else if (blueAlliance) {
        if (opticalSensor.get_hue() >= 1 && opticalSensor.get_hue() <= 25) {
            return true;
        }
    }
    return false;
}

/**
 * Function that will eject a ring from the lift. It is timed specifically
 * where a ring of the wrong color moving into the sight of the optical sensor
 * will be shot out of the lift by inertia.
 * Uses the direct motor control functions to bypass the ejecting barrier
 * of the setLiftSpeed() function.
 */
void eject() {
    lift.controllerSet(1);
    pros::delay(160);
    lift.controllerSet(-1);
    pros::delay(150);
    lift.controllerSet(0);

}


/**
 *  Task that will run in the background of the project to
 *  constantly check for bad rings. This will be started in
 *  the initialization phase.
 */
void colorDetectionTask(void* param) {
    while (true) {
        if (detectsBadColor()) {
            isEjecting = true;
            eject();
            isEjecting = false;
        }
        pros::delay(20);
    }
    
}

void intakeUntilColor(void* param) {
    while (true) {
        setLiftSpeed(1);
        if (redAlliance && opticalSensor.get_hue() >= 1 && opticalSensor.get_hue() <= 25) {
            setLiftSpeed(0);
            break;
        }
        else if (blueAlliance && opticalSensor.get_hue() >= 130 && opticalSensor.get_hue() <= 230) {
            setLiftSpeed(0);
            break;
        }
        pros::delay(20);
    }
}