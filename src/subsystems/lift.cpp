#include "main.h"
#include <string>

double highestHueDetected = 0;
double ejectionCount = 0;

bool isEjecting = false;

/** 
*  Runs once when the codebase is initialized. 
*  Used to set the attributes of objects and other tasks that need to happen at the start.
*/
void liftInitialize() {
    lift.set_brake_mode(pros::MotorBrake::coast);
    intakeGroup.set_brake_mode(pros::MotorBrake::coast);

    lift.set_current_limit(2500);

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
* @param speed The speed to set the lift motor to, from -127 to 127.
*/
void setLiftSpeed(double speed) {
    if (!isEjecting) {
        lift.move(speed);
    }
}

/**
* Sets the speed of the intake.
*
* @param speed The speed to set the intake motors to, from -127 to 127.
*/
void setIntakeSpeed(double speed) {
    intakeGroup.move(speed);
}

/**
 * Method that detects whether or not the hue currently detected by the
 * optical sensor is the hue of the other alliance's ring.
 * 
 * @returns True if the detected color is that of the wrong colored ring; False otherwise
 */
bool detectsBadColor() {
    if (redAlliance) {
        if (opticalSensor.get_hue() >= 170 && opticalSensor.get_hue() <= 230) {
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
    lift.move_voltage(127);
    pros::delay(160);
    lift.move_voltage(-127);
    pros::delay(150);
    // setLadybrownSetpoint(500, 100);
    // pros::delay(20);
    lift.move_voltage(0);
    pros::delay(150);
    // pros::delay(200);
    // setLadybrownSetpoint(0, 100);
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
        pros::delay(5);
    }
    
}

void intakeUntilColor(void* param) {
    pros::Task::notify_take(true, TIMEOUT_MAX);
    while (true) {
        setLiftSpeed(1);
        setIntakeSpeed(1);
        double hue = opticalSensor.get_hue();
        double distance = opticalSensor.get_proximity();
        if (redAlliance && hue >= 1 && hue <= 25 && distance > 100) {
            setLiftSpeed(0);
            setIntakeSpeed(0);
            intakeTask.suspend();
        }
        else if (blueAlliance && hue >= 160 && hue <= 230 && distance > 100) {
            setLiftSpeed(0);
            setIntakeSpeed(0);
            intakeTask.suspend();
        }
        pros::delay(20);
    }
}

void intakeJamHandler(void* param) {
    pros::Task::notify_take(true, TIMEOUT_MAX);
    int stallTime = -1;
    while (true) {
        if (intakeGroup.get_actual_velocity() == 0 && intakeGroup.get_target_velocity() > 0) {
            if (stallTime == -1) {
                stallTime = pros::millis();
            } else if (pros::millis() - stallTime >= 150) {
                print(1, 0, "Intake Jammed");
                setIntakeSpeed(-1);
                pros::delay(50);
                setIntakeSpeed(1);
            }
        } else {
            stallTime = -1;
        }
        pros::delay(20);
    }
}

void liftStallHandler(void* param) {
    pros::Task::notify_take(true, TIMEOUT_MAX);
    int stallTime = -1;
    while (true) {
        bool ladyBrownReadied = ladybrownGroup.get_position() > 100 && ladybrownGroup.get_position() < 200;
        if (lift.get_actual_velocity() == 0 && lift.get_target_velocity() > 0 && !ladyBrownReadied) {
            if (stallTime == -1) {
                stallTime = pros::millis();
            } else if (pros::millis() - stallTime >= 250) {
                print(0, 0, "Lift Stalled");
                setLiftSpeed(-1);
                pros::delay(200);
                setLiftSpeed(1);
            }
        } else {
            stallTime = -1;
        }
        pros::delay(20);
    }
}