#include "main.h"
using namespace std;
using namespace okapi;

bool isFrontReversed = false;

std::shared_ptr<okapi::ChassisControllerPID> chassis = std::dynamic_pointer_cast<ChassisControllerPID>(ChassisControllerBuilder()
	.withMotors(BADLeftMotorGroup, BADRightMotorGroup)
	.withDimensions({AbstractMotor::gearset::blue, (3.0/4.0)}, {{2.75_in, 11.5_in}, imev5BlueTPR})
    .withGains(
        {0.00045, 0.0005, 0.00000},
        {2.5, 0, 0},
        {0.0, 0, 0.0000}
    )
    .build());

// Turn gains: 3.0, 0.00, 1.5
std::shared_ptr<ChassisModel> drivetrain = chassis->getModel();

// PID constants for turning
PID turnPID = {
    .kP = 2.5,
    .kI = 0.0,
    .kD = 0.0,
    .smallErrorRange = 0.4, // degrees
    .smallErrorTimeout = 100.0, // milliseconds
    .largeErrorRange = 0.75, // degrees
    .largeErrorTimeout = 500.0, // milliseconds
    .minVelocity = 3.0
};

PIDController testPIDController = PIDController(2500, 0.0, 0.0);

/**
*  Runs once when the codebase is initialized. 
*  Used to set the attributes of objects and other tasks that need to happen at the start.
*/
void drivetrainInitialize() {
    //driverController.set_text(0, 0, "");
    drivetrain->setBrakeMode(okapi::AbstractMotor::brakeMode::coast);
    //chassis->setMaxVelocity(0.4*chassis->getMaxVelocity());
    setDriveMotorCurrentLimits(2000);

    testPIDController.setOutputLimits(3.0, 127);
    testPIDController.setSmallErrorRange(0.4);
    testPIDController.setLargeErrorRange(0.75);


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

    /*if (driverController.get_digital_new_press(DIGITAL_L2)) {
        isFrontReversed = !isFrontReversed;
    }*/

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
}

/** 
 * Sets the current limits on the drive train
 * 
 * @param mAmps the max amount of current the drivetrain should attain in milliamperes.
 */
void setDriveMotorCurrentLimits(int mAmps) {
    BADLeftMotorGroup.setCurrentLimit(mAmps);
    BADRightMotorGroup.setCurrentLimit(mAmps);
}

/**
* @brief Turn the robot to an absolute heading using PID control
* @param heading The heading to turn to in degrees: [0,360)
* @param maxVelocity The maximum velocity of the robot in the range [0,1], default to 1
* @param timeout Timeout before the robot gives up in milliseconds, default to 5000
* @param behavior The behavior of the turn, LEFT, RIGHT, or DEFAULT (closest direction), default to DEFAULT
*/
void turnToHeading(double heading, double maxVelocity, int timeout, enum TurnBehavior behavior) {
    // Get the current heading
	double currentHeading = gyro.get_heading();
	double error = heading - currentHeading;
	
    if (behavior == TurnBehavior::DEFAULT) {
        // Normalize the error
        if (error > 180) {
            error = error - 360;
        } else if (error < -180) {
            error = 360 + error;
        }
    } else if (behavior == TurnBehavior::LEFT) {
        if (error > 0) {
            error = -360 + error;
        }
    } else if (behavior == TurnBehavior::RIGHT) {
        if (error < 0) {
            error = 360 + error;
        }
    }

	turnAngle(error, maxVelocity, timeout);
}

/** 
* @brief Turn the robot by the specified angle using PID control
* @param angle angle in degrees
* @param maxVelocity maximum velocity of the robot in the range [0,1], default to 1
* @param timeout timeout before the robot gives up in milliseconds, default to 5000
*/
void turnAngle(double angle, double maxVelocity, int timeout) {
    testPIDController.setOutputLimits(0, maxVelocity);

    // Calculate the target angle
    double target = angle + gyro.get_rotation();

    // Set the start time and exit time
	int startTime = pros::millis();
	int exitTime = pros::millis() + timeout;

    int smallErrorEntryTime = -1; // Time when the robot entered the small error range
    int largeErrorEntryTime = -1; // Time when the robot entered the large error range

    // Loop until the target is reached or the timeout is reached
    bool targetReached = false;
    int currentTime = pros::millis();
    int previousTime = currentTime;
	while (!targetReached && currentTime < exitTime) {
        int timeChange = currentTime - previousTime;

        // Calculate the velocity
		double velocity = testPIDController.calculate(gyro.get_rotation(), target);

        driverController.set_text(0, 0, to_string(velocity));

        // Set the motor velocities
		BADRightMotorGroup.moveVoltage(-velocity);
		BADLeftMotorGroup.moveVoltage(velocity);
		pros::delay(5);

        // Determine if within small error range
        if (testPIDController.isInSmallErrorRange()) {
            // Set the entry time if not already set
            if (smallErrorEntryTime == -1) {
                smallErrorEntryTime = pros::millis();
            }
            // Check if the timeout has been reached
            if (smallErrorEntryTime + turnPID.smallErrorTimeout < pros::millis()) {
                targetReached = true;
                break;
            }
        } else {
            // Reset the entry time
            smallErrorEntryTime = -1;
        }
        // Determine if within large error range
        if (testPIDController.isInLargeErrorRange()) {
            // Set the entry time if not already set
            if (largeErrorEntryTime == -1) {
                largeErrorEntryTime = pros::millis();
            }
            // Check if the timeout has been reached
            if (largeErrorEntryTime + turnPID.largeErrorTimeout < pros::millis()) {
                targetReached = true;
                break;
            }
        } else {
            // Reset the entry time
            largeErrorEntryTime = -1;
        }

        // Update the time values
        previousTime = currentTime;
        currentTime = pros::millis();
	}
    drivetrain->stop();
    pros::delay(50);
}

void moveDistanceWithTimeout(QLength itarget, int timeout) {
    chassis->moveDistanceAsync(itarget);

    auto exitTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(timeout);

    while (!chassis->isSettled() && std::chrono::high_resolution_clock::now() < exitTime) {};
}