#include "main.h"
using namespace std;
using namespace okapi;

bool isFrontReversed = false;

std::shared_ptr<okapi::ChassisControllerPID> chassis = std::dynamic_pointer_cast<ChassisControllerPID>(ChassisControllerBuilder()
	.withMotors(leftMotorGroup, rightMotorGroup)
	.withDimensions({AbstractMotor::gearset::blue, (3.0/4.0)}, {{2.75_in, 11.5_in}, imev5BlueTPR})
    .withGains(
        {0.0045, 0, 0.0000},
        {3.0, 0.00, 0},
        {0.0, 0, 0.0000}
    )
    .build());

std::shared_ptr<ChassisModel> drivetrain = chassis->getModel();

/**
*  Runs once when the codebase is initialized. 
*  Used to set the attributes of objects and other tasks that need to happen at the start.
*/
void drivetrainInitialize() {
    //driverController.set_text(0, 0, "");
    drivetrain->setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
    chassis->setMaxVelocity(0.4*chassis->getMaxVelocity());
    setDriveMotorCurrentLimits(2000);
}

/**
*  Runs every opcontrol cycle. 
*  This method is used for robot control and printing, as well as anything else
*  that needs to happen every update cycle in driver control.
*
*  Note: This method is not run during autonomous. Any prints you put here
*  will not work unless the robot is in manual control mode.
*/
void drivetrainPeriodic() {
    if (driverController.get_digital_new_press(DIGITAL_L2)) {
        isFrontReversed = !isFrontReversed;
    }

    arcadeDrive(isFrontReversed);
}

/**
*  Arcade drive control.
*  Reads controller stick inputs and converts those into motor
*  outputs in the style of arcade control.
*
*  Up and Down on the left stick make the bot move forwards and backwards.
*  Left and Right on the right stick make the bot rotate left and right.
*
*  @param reverse Whether or not the front of the robot should be reversed
*/
void arcadeDrive(bool reverse) {
    // Arcade control scheme
    double leftY = driverController.get_analog(ANALOG_LEFT_Y) / 127.0;    // Gets amount forward/backward from left joystick
    double rightX = driverController.get_analog(ANALOG_RIGHT_X) / 127.0;  // Gets the turn left/right from right joystick

    // Apply a squared scaling to the controller values. This makes driving slower require less percision
    double fwdSpeed = pow(leftY, 2); 
    double rotSpeed = pow(rightX, 2);

    // Account for negatives
    if (leftY < 0) {
        fwdSpeed *= -1;
    } 
    if (rightX < 0) {
        rotSpeed *= -1;
    }

    if (reverse) {
        fwdSpeed *= -1;
    }

    // Applies the speeds to the drivetrain
    drivetrain->arcade(fwdSpeed, rotSpeed);
    // drivetrain->arcade(leftY, rightX);
}

/** 
 * Sets the current limits on the drive train
 * 
 * @param mAmps the max amount of current the drivetrain should attain in milliamperes.
 */
void setDriveMotorCurrentLimits(int mAmps) {
    leftMotorGroup.setCurrentLimit(mAmps);
    rightMotorGroup.setCurrentLimit(mAmps);
}

/** 
* @brief Custom Turnangle Function
* @param angle angle in degrees
* @param timeout timeout before the robot gives up in seconds
*/
void turnAngle(float angle, int timeout) {
    auto gains = get<1>(chassis->getGains());

    float target = angle + gyro.get_rotation();
    float error = angle;
	float previousError = 0;
	float integral = 0;
	float errorCounter = 0;
	float precision = 1;
	
	auto exitTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(timeout);
	while (errorCounter < 50 && std::chrono::high_resolution_clock::now() < exitTime) {
		integral += error;
		float velocity = setMinAbs((gains.kP * error + (error - previousError) * gains.kD + gains.kI * integral), 1);
		rightMotorGroup.moveVelocity(-velocity);
		leftMotorGroup.moveVelocity(velocity);
		pros::delay(10);
		//driverController.print(0,0,"%f", velocity);
		previousError = error;
		error = target - gyro.get_rotation();
		if (abs(error) < precision) {
			errorCounter++;
		}
		else {
			errorCounter = 0;
		}
	}
	rightMotorGroup.moveVelocity(0);
	leftMotorGroup.moveVelocity(0);
}

void lateralPIDTune(){
    auto gains = get<1>(chassis->getGains());
    chassis->setGains(
        {0.001, 0, 0.0000},
        {3.0, 0.00, 0},
        {0.0, 0, 0.0000}
    );
    chassis->setGains(
        gains,
        {3.0, 0.00, 0},
        {0.0, 0, 0.0000}
    );

}

void angularPIDTune(){
    turnAngle(90);
}



