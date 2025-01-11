#include <main.h>

void liftInitialize() {
    lift.setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
}

void liftPeriodic() {
    if (driverController.get_digital(DIGITAL_A)) {
        lift.controllerSet(1);
    } else {
        lift.controllerSet(0);
    }
    
}