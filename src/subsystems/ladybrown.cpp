#include "main.h"
using namespace std;

int setpoint = ladybrownStartingAngle;

bool manualOverride = false;

// std::shared_ptr<AsyncPositionController<double, double>> ladybrownController = AsyncPosControllerBuilder()
//     .withMotor(ladybrownGroup)
//     .withSensor(1)
//     .withGains(
//         {0, 0, 0}
//     )
//     .build();


/**
*  Runs once when the codebase is initialized. 
*  Used to set the attributes of objects and other tasks that need to happen at the start.
*/
void ladybrownInitialize() {
    rotationSensor.reset_position();

    // ladybrownA.setVoltageLimit(7.2);
    // ladybrownB.setVoltageLimit(7.2);

    ladybrownB.set_voltage_limit(7200);
    ladybrownA.set_voltage_limit(7200);
    
    ladybrownA.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    ladybrownB.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    ladybrownA.set_reversed(false);
    ladybrownB.set_reversed(true);

    ladybrownGroup.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    ladybrownGroup.set_voltage_limit(7200);

    // ladybrownGroup.set_current_limit(1250);

    
}

/**
*  Runs every opcontrol cycle. 
*  This method is used for robot control and printing, as well as anything else
*  that needs to happen every update cycle in driver control.
*
*  Note: This method is not run during autonomous. Any prints you put here
*  will not work unless the robot is in manual control mode.
*/
void ladybrownPeriodic() {
    // driverController.set_text(0, 0, to_string(ladybrownA.get_position()));
    // driverController.set_text(0, 0, "Ladybrown" + std::to_string(getLadybrownAngle()));
    // driverController.set_text(0, 0, "Analog" + std::to_string(driverController.get_analog(ANALOG_LEFT_Y))); 


    setLadybrownPosition(setpoint, 50);

    if (driverController.get_digital_new_press(DIGITAL_LEFT)) {
        setManualOverride(!manualOverride);
    }
    if (manualOverride) {
        manualControl();
    }
    else {
        if (driverController.get_digital(DIGITAL_DOWN)) {
            setLadybrownSetpoint(0);
        }
        else if (driverController.get_digital(DIGITAL_RIGHT)) {
            setLadybrownSetpoint(100);
        }
        else if (driverController.get_digital_new_press(DIGITAL_UP)) {
            setLadybrownSetpoint(700);
        }
    }
 }

double getLadybrownAngleDegrees() {
    return (rotationSensor.get_position() / 100) + ladybrownStartingAngle;
}

double getLadybrownAngleRadians() {
    return getLadybrownAngleDegrees() * 3.14159 / 180;
}

/**
*  Sets the position of the ladybrown to the given position
*
* @param posValue The target position the ladybrown should go to, in [INSERT UNITS HERE]
*/
void setLadybrownPosition(int posValue, int velocity) {
    if (posValue < 0 || posValue > 1500) {
        ladybrownGroup.move_absolute(ladybrownGroup.get_position(), velocity);
    }
    else {
        ladybrownGroup.move_absolute(posValue, velocity);
    }

    // double error = posValue - getLadybrownAngleDegrees();

    // double nominalOutput = (error * ladybrownKP);

    // if (error > 1 &&  nominalOutput < 3) {
    //     nominalOutput = 10;
    // }
    // if (error < 1 &&  nominalOutput > -3) {
    //     nominalOutput = -10;
    // }
    
    // double output = nominalOutput + (std::cos(getLadybrownAngleRadians()) * ladybrownBaseFeedForward); 

    // driverController.set_text(0, 0, "Ladybrown: " + std::to_string(output));

    // driverController.clear();

    // driverController.set_text(0, 0, "Ladybrown: " + std::to_string(output));

   

    // setLadybrownSpeed(output);
}

/**
 * Sets the target position of the ladybrown.
 * 
 * @param point the target position in encoder units.
 */
void setLadybrownSetpoint(int point) {
    setpoint = point;
}

/**
 * Set the state of the manual override.
 * 
 * @param isOverride whether or not the manual override should be active
 */
void setManualOverride(bool isOverride) {
    manualOverride = isOverride;
}

/**
*  Lets the ladybrown be controlled manually. 
*
*  This control scheme should only be used if the position control breaks midmatch,
*  in which case the driver will press the manual override button and be able to control
*  the lady brown with direct voltage inputs.
*/
void manualControl() {
    if (driverController.get_digital(DIGITAL_UP)) {
        setLadybrownSpeed(60 + (std::cos(getLadybrownAngleDegrees()) * ladybrownBaseFeedForward));
    }
    else if (driverController.get_digital(DIGITAL_DOWN)) {
        setLadybrownSpeed(-40 + (std::cos(getLadybrownAngleDegrees()) * ladybrownBaseFeedForward));
    }
    else {
        setLadybrownSetpoint(ladybrownA.get_position());
        setLadybrownPosition(setpoint, 50);
    }
    // if (driverController.get_analog(ANALOG_LEFT_Y) > 5 || driverController.get_analog(ANALOG_LEFT_Y) < -5) {
    //     setLadybrownSpeed(driverController.get_analog(ANALOG_LEFT_Y) + ((std::cos(getLadybrownAngle()) * ladybrownBaseFeedForward)));
    // }
    // else {
    //     driverController.clear();
    //     setLadybrownSpeed(0);
    // }

}

/**
 * Directly sets the speed of the lady brown. 
 * Prevents the ladybrown from moving past its limits.
 * 
 * @param speed speed to set the ladybrown to, from -127 to 127
 */
void setLadybrownSpeed(int speed) {
    if (getLadybrownAngleDegrees() > ladybrownScoringAngle && speed > 0) {
        ladybrownGroup.move(0);
    }
    else if (getLadybrownAngleDegrees() <= ladybrownStartingAngle  && speed < 0) {
        ladybrownGroup.move(0);
    }
    else {
        ladybrownGroup.move(speed);
    }
}


