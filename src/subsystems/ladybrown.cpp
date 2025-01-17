#include "main.h"

int ladybrownReadiedPos = 0;
int ladybrownScoringPos = 0;

// std::shared_ptr<AsyncPositionController<double, double>> ladybrownController = AsyncPosControllerBuilder()
//     .withMotor(ladybrownGroup)
//     .withSensor(1)
//     .withGains(
//         {0, 0, 0}
//     )
//     .build();

void ladybrownInitialize() {
    rotationSensor.reset_position();

    // ladybrownA.setVoltageLimit(7.2);
    // ladybrownB.setVoltageLimit(7.2);

    ladybrownA.set_voltage_limit(7200);
    ladybrownB.set_voltage_limit(7200);

    ladybrownA.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    ladybrownB.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    ladybrownA.set_reversed(true);
    ladybrownA.set_reversed(false);


    // ladybrownA.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);
    // ladybrownB.setBrakeMode(okapi::AbstractMotor::brakeMode::hold);

}

void ladybrownPeriodic() {
    manualControl();
 }

/*
*  Sets the position of the ladybrown to the given position
*
*/
void setPosition(int posValue) {
    // ladybrownController->setTarget(posValue);

}

void manualControl() {
    if (driverController.get_digital(DIGITAL_UP)) {
        ladybrownA.move(20);
        ladybrownB.move(20);

        // ladybrownGroup.controllerSet(0.8);
        // ladybrownA.moveVoltage(6000);
        // ladybrownB.moveVoltage(2000);
        driverController.set_text(0, 0, "Ball");
    }
    else if (driverController.get_digital(DIGITAL_DOWN)) {
        ladybrownA.move(-20);
        ladybrownB.move(-20);
        // ladybrownGroup.controllerSet(-0.8);
        // ladybrownA.moveVoltage(-6000);
        // ladybrownB.moveVoltage(-2000);
        driverController.set_text(0, 0, "Tree");
    }
    else {
        // ladybrownA.move_absolute(ladybrownA.get_position())
        ladybrownB.move(0);
        // ladybrownA.move_absolute(ladybrownA.get_position(), 100);
        // ladybrownB.move_absolute(ladybrownB.get_position(), 100);

        // ladybrownGroup.controllerSet(0);
        // ladybrownA.moveVoltage(0);
        // ladybrownB.moveVoltage(0);
        driverController.set_text(0, 0, "Epic");
    }
}


