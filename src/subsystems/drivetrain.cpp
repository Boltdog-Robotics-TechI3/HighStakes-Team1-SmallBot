#include <main.h>

std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder()
	.withMotors({11, 12, 13}, {1, 2, 3})
	.withDimensions(AbstractMotor::gearset::blue, {{3.25_in, 11.5_in}, imev5BlueTPR})
	.build();

std::shared_ptr<ChassisModel> drivetrain = chassis->getModel();

void drivetrainInitialize() {
    drivetrain->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
}

void drivetrainPeriodic() {
    arcadeDrive();
}

void arcadeDrive() {
    // Arcade control scheme
    int leftY = driverController.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
    int rightX = driverController.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick

    // Apply a cubic scaling to the controller values. This makes driving slower require less percision
    int fwdSpeed = pow(leftY / 127, 3) * 127; 
    int rotSpeed = pow(rightX / 127, 3) * 127; 

    // Applies the speeds to the drivetrain
    drivetrain->arcade(fwdSpeed, rotSpeed);
}
