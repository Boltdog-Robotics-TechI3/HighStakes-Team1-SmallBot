#include "main.h"
#include <iostream>
using namespace std;


// shared_ptr<IterativePosPIDController> pidController = IterativeControllerFactory()


std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder()
	.withMotors(leftMotorGroup, rightMotorGroup)
	.withDimensions({AbstractMotor::gearset::blue, (60.0/36.0)}, {{3.25_in, 11.5_in}, imev5BlueTPR})
    .withGains(
        {0.005, 0, 0.00012},
        {0.005, 0, 0.00012},
        {0.000, 0, 0.0000}
    )
	.build();
    

std::shared_ptr<ChassisModel> drivetrain = chassis->getModel();


/**
*  Runs once when the codebase is initialized. 
*  Used to set the attributes of objects and other tasks that need to happen at the start.
*/
void drivetrainInitialize() {
    drivetrain->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
    chassis->setMaxVelocity(0.4*chassis->getMaxVelocity());

    leftMotorGroup.setCurrentLimit(2500);
    rightMotorGroup.setCurrentLimit(2500);

    chass

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
    arcadeDrive();
    
}

/**
*  Arcade drive control.
*  Reads controller stick inputs and converts those into motor
*  outputs in the style of arcade control.
*
*  Up and Down on the left stick make the bot move forwards and backwards.
*  Left and Right on the right stick make the bot rotate left and right.
*/
void arcadeDrive() {
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

    // Applies the speeds to the drivetrain
    drivetrain->arcade(fwdSpeed, rotSpeed);
    // drivetrain->arcade(leftY, rightX);
}

/**
 *  Small bot's match auto that goes for the mogo furthest to the left first
 * 
 */
void matchPlusSideAuto() {
    // chassis->setMaxVelocity((10.0/4.0)*chassis->getMaxVelocity());
    // chassis->moveDistance(-4_ft);
    leftMotorA.move
    // leftMotorGroup.moveVoltage(-127);
    // rightMotorGroup.moveVoltage(-127);
    pros::delay(1250);
    leftMotorGroup.moveVoltage(0);
    rightMotorGroup.moveVoltage(0);
    toggleMogoClamp();
    chassis->moveDistance(1_ft);
    //  chassis->setMaxVelocity(0.4*chassis->getMaxVelocity());
}

/**
* Small bot's skills auto
*/
void skillsAuto() {
    //portion to grab first donut
    //setLiftSpeed(1);
	chassis->moveDistance(3.15_ft);
    chassis->waitUntilSettled();
    pros::delay(1000);

    // Drive to and grab first mogo
    chassis->turnAngle(98_deg);
    chassis->waitUntilSettled();
    chassis->moveDistance(-1.9_ft);
    chassis->waitUntilSettled();
    toggleMogoClamp();
    pros::delay(500);

    // Grab autoline ring.
    chassis->turnAngle(-100_deg);
    chassis->waitUntilSettled();
    chassis->moveDistance(2_ft);
    chassis->waitUntilSettled();
    pros::delay(500);

    // Grab ring that is close to corner
    chassis->turnAngle(195_deg);
    chassis->waitUntilSettled();
    chassis->moveDistance(3.9_ft);
    chassis->waitUntilSettled();
    pros::delay(500);

    // Grab corner ring
    chassis->turnAngle(47_deg);
    chassis->waitUntilSettled();
    chassis->moveDistance(1.6_ft);
    chassis->waitUntilSettled();
    pros::delay(500);

    // Back off from corner and place goal
    chassis->moveDistance(-1_ft);
    chassis->waitUntilSettled();
    chassis->turnAngle(194_deg);
    chassis->waitUntilSettled();
    toggleMogoClamp();

    // Drive to the mogo on the other side of the field on auto line close to 
    chassis->moveDistance(0.8_ft);
    chassis->waitUntilSettled();
    chassis->turnAngle(-45_deg);
    chassis->waitUntilSettled();
    chassis->moveDistance(4.15_ft);
    chassis->waitUntilSettled();
    chassis->turnAngle(-140_deg);
    chassis->waitUntilSettled();  
    chassis->moveDistance(-2.6_ft);
    chassis->waitUntilSettled();  
    toggleMogoClamp();
    pros::delay(500);

    // Grab center rings
    chassis->turnAngle(-105_deg);
    chassis->waitUntilSettled();  
    chassis->moveDistance(2.2_ft);
    chassis->waitUntilSettled();
    chassis->turnAngle(30_deg);
    chassis->waitUntilSettled();
    chassis->moveDistance(0.7_ft);
    chassis->waitUntilSettled();
}