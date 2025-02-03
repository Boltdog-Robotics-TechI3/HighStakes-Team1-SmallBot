#include "main.h"
using namespace std;

int ladybrownReadiedPos = 170;
int ladybrownScoringPos = 770;

int setpoint = 0;

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

    ladybrownA.set_voltage_limit(7200);
    ladybrownB.set_voltage_limit(7200);

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

    setLadybrownPosition(setpoint);

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
            setLadybrownSetpoint(ladybrownReadiedPos);
        }
        else if (driverController.get_digital_new_press(DIGITAL_UP)) {
            setLadybrownSetpoint(ladybrownScoringPos);
        }
    }
 }

/**
*  Sets the position of the ladybrown to the given position
*
* @param posValue The target position the ladybrown should go to, in [INSERT UNITS HERE]
*/
void setLadybrownPosition(int posValue) {
    if (posValue < 0 || posValue > 800) {
        ladybrownGroup.move_absolute(ladybrownGroup.get_position(), 100);
    }
    else {
        ladybrownGroup.move_absolute(posValue, 100);

    }
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
        setLadybrownSpeed(60);
    }
    else if (driverController.get_digital(DIGITAL_DOWN)) {
        setLadybrownSpeed(-40);
    }
    else {
        setLadybrownSetpoint(ladybrownA.get_position());
        setLadybrownPosition(setpoint);
    }
}

/**
 * Directly sets the speed of the lady brown. 
 * Prevents the ladybrown from moving past its limits.
 * 
 * @param speed speed to set the ladybrown to, from -127 to 127
 */
void setLadybrownSpeed(int speed) {
    if (ladybrownA.get_position() > 770 && speed > 0) {
        ladybrownGroup.move(0);
    }
    else if (ladybrownA.get_position() <= 0  && speed < 0) {
        ladybrownGroup.move(0);
    }
    else {
        ladybrownGroup.move(speed);
    }
}


