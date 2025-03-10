#include "main.h"
#include "okapi/api/chassis/controller/chassisControllerPid.hpp"
#include "okapi/api/device/motor/abstractMotor.hpp"
#include <string>
using namespace std;
using namespace okapi;

bool isFrontReversed = false;

std::shared_ptr<okapi::ChassisControllerPID> chassis = std::dynamic_pointer_cast<ChassisControllerPID>(ChassisControllerBuilder()
	.withMotors(leftMotorGroup, rightMotorGroup)
	.withDimensions({AbstractMotor::gearset::blue, (3.0/4.0)}, {{2.75_in, 11.5_in}, imev5BlueTPR})
    .withGains(
        {0.004, 0, 0.0001},
        {2.5, 0, 0},
        {0.0, 0, 0.0000}
    )
    .build());
// Turn gains: 3.0, 0.00, 1.5
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

    // if (driverController.get_digital_new_press(DIGITAL_RIGHT)) {
    //     turnToHeading(90);
    // }
    // if (driverController.get_digital_new_press(DIGITAL_LEFT)) {
    //     turnToHeading(270);
    // }
    // if (driverController.get_digital_new_press(DIGITAL_UP)) {
    //     turnToHeading(0);
    // }
    // if (driverController.get_digital_new_press(DIGITAL_DOWN)) {
    //     turnToHeading(180);
    // }
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
    //drivetrain->arcade(fwdSpeed, rotSpeed);
    drivetrain->arcade(leftY, rightX);
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
* @brief Turns the robot to an absolute heading using PID control
* @param heading The heading to turn to in degrees: [0,360)
* @param timeout Timeout before the robot gives up in seconds, default to 10
* @param maxVelocity The maximum velocity of the robot in the range [0,1], default to 1
*/
void turnToHeading(double heading, double maxVelocity, int timeout) {
	double currentHeading = gyro.get_heading();
	double error = heading - currentHeading;
	
	if (error > 180) {
		error = error - 360;
	} else if (error < -180) {
		error = 360 + error;
	}
	turnAngle(error, maxVelocity, timeout);
}

/** 
* @brief Custom Turnangle Function
* @param angle angle in degrees
* @param timeout timeout before the robot gives up in seconds
*/

void turnAngle(double angle, double maxVelocity, int timeout) {
    auto gains = get<1>(chassis->getGains());
    double target = angle + gyro.get_rotation();
    double error = angle;
	double previousError = 0;
	double integral = 0;
    double smallErrorRange = 0.4;
    double smallErrorTimeout = 100;
    double largeErrorRange = 0.75;
    double largeErrorTimeout = 500;
    double minVelocity = 3.0;
	int startTime = pros::millis();
	auto exitTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(timeout);
    bool targetReached = false;
    double smallErrorEntryTime = 0;
    double largeErrorEntryTime = 0;
	while (!targetReached && std::chrono::high_resolution_clock::now() < exitTime) {
		integral = integral * 0.8 + error;
		double velocity = gains.kP * error + (error - previousError) * gains.kD + gains.kI * integral;
        if (velocity > 0) {
            velocity = std::clamp(velocity+minVelocity, 0.0, 600.0*maxVelocity);
        } else if (velocity < 0) {
            velocity = std::clamp(velocity-minVelocity, -600.0*maxVelocity, 0.0);
        }
		rightMotorGroup.moveVelocity(-velocity);
		leftMotorGroup.moveVelocity(velocity);
		pros::delay(5);
        if (abs(error) < smallErrorRange) {
            if (smallErrorEntryTime == 0) {
                smallErrorEntryTime = pros::millis();
            }
            if (smallErrorEntryTime + smallErrorTimeout < pros::millis()) {
                print(2, 0, "Small Error");
                targetReached = true;
                break;
            }
        } else {
            smallErrorEntryTime = 0;
        }
        if (abs(error) < largeErrorRange) {
            if (largeErrorEntryTime == 0) {
                largeErrorEntryTime = pros::millis();
            }
            if (largeErrorEntryTime + largeErrorTimeout < pros::millis()) {
                print(2, 0, "Large Error");
                targetReached = true;
                break;
            }
        } else {
            largeErrorEntryTime = 0;
        }
		previousError = error;
		error = target - gyro.get_rotation();
	}
    drivetrain->stop();
    print(0, 0, "Heading: " + std::to_string(gyro.get_heading()));
    if (!targetReached) {
        print(2, 0, "Timeout");
    }
    pros::delay(5000);
}

void moveDistanceWithTimeout(QLength itarget, int timeout) {
    chassis->moveDistanceAsync(itarget);

    auto exitTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(timeout);

    while (!chassis->isSettled() && std::chrono::high_resolution_clock::now() < exitTime) {};
}