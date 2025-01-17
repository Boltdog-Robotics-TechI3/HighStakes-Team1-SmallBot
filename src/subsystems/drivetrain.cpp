#include "main.h"
#include <iostream>
using namespace std;


// shared_ptr<IterativePosPIDController> pidController = IterativeControllerFactory()


std::shared_ptr<ChassisController> chassis = ChassisControllerBuilder()
	.withMotors(leftMotorGroup, rightMotorGroup)
	.withDimensions({AbstractMotor::gearset::blue, (60.0/36.0)}, {{3.25_in, 11.5_in}, imev5BlueTPR})
    .withGains(
        {0.005, 0, 0.0001},
        {0.005, 0, 0.0001},
        {0.000, 0, 0.0000}
    )
	.build();
    

std::shared_ptr<ChassisModel> drivetrain = chassis->getModel();


/* 
*  Runs once when the codebase is initialized. 
*  Used to set the attributes of objects and other tasks that need to happen at the start.
*/
void drivetrainInitialize() {
    drivetrain->setBrakeMode(okapi::AbstractMotor::brakeMode::brake);
    chassis->setMaxVelocity(0.4*chassis->getMaxVelocity());
    }

/* 
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

/*
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

    // Apply a cubic scaling to the controller values. This makes driving slower require less percision
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

void skillsAuto() {
    //portion to grab first donut
    //setLiftSpeed(1);
	chassis->moveDistance(0.5_ft);
    chassis->waitUntilSettled();
    
    /*grab donut*/
    pros::delay(900);
    //setLiftSpeed(0);

    // Drive to first mogo
	chassis->turnAngle(-192_deg);
    chassis->waitUntilSettled();
	chassis->moveDistance(-2_ft);
    chassis->waitUntilSettled();

    /*put donut on stake*/
    //insert method that grabs scoring stake
	//setLiftSpeed(1);
    pros::delay(100);
    //setLiftSpeed(0);

    // Move to corner
	chassis->moveDistance(1_ft);
    chassis->waitUntilSettled();
    chassis->turnAngle(45_deg);
    chassis->waitUntilSettled();
	chassis->moveDistance(1.55_ft);
    chassis->waitUntilSettled();

    // Drop stake
	//insert method that releases scoring stake
    //wait to seperate movement sections visually
    pros::delay(500);
    chassis->moveDistance(-1_ft);
    chassis->waitUntilSettled();
    chassis->turnAngle(195_deg);
    chassis->waitUntilSettled();

    // Drive to wall stake
    chassis->turnAngle(-45_deg);
    chassis->waitUntilSettled();
    chassis->moveDistance(2_ft);
    chassis->waitUntilSettled();
    chassis->turnAngle(-45_deg);
    chassis->waitUntilSettled();
    chassis->moveDistance(0.7_ft);
    chassis->waitUntilSettled();
    chassis->turnAngle(45_deg);
    chassis->waitUntilSettled();
    chassis->moveDistance(2_ft);
    chassis->waitUntilSettled();
    chassis->turnAngle(-115_deg);

}