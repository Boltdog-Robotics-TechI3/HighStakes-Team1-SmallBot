#include "main.h"
#include <iostream>
using namespace std;
using namespace okapi;

bool isFrontReversed = false;

auto chassis = std::dynamic_pointer_cast<ChassisControllerPID>(ChassisControllerBuilder()
	.withMotors(leftMotorGroup, rightMotorGroup)
	.withDimensions({AbstractMotor::gearset::blue, (60.0/36.0)}, {{2.96_in, 11.5_in}, imev5BlueTPR})
    .withGains(
        {0.005, 0, 0.00012},
        {0.004, 0.0003, 0.00004},
        {0.0001, 0, 0.0000}
    )
    .build());

std::shared_ptr<ChassisModel> drivetrain = chassis->getModel();

/**
*  Runs once when the codebase is initialized. 
*  Used to set the attributes of objects and other tasks that need to happen at the start.
*/
void drivetrainInitialize() {
    driverController.set_text(0, 0, "");
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



/* AUTONOMOUS */

/* TASKS */
// Task Function used for plus side mogo auto (ill figure out how to do parameters later)
void moveTaskFunction(void* param) {
    chassis->moveDistance(-3.75_ft);
}

// Task Function used for plus side mogo auto (ill figure out how to do parameters later)
void moveTaskFunctionAgain(void* param) {
    chassis->moveDistance(4.3_ft);
    pros::delay(5000);
}

// Task Function used for skills auto (ill figure out how to do parameters later)
void moveTaskFunctionAgain2(void* param) {
    chassis->moveDistance(1.3_ft);
}

/* ROUTINES */

void testAuto() {
    // chassis->moveDistance(2_ft);
    chassis->setMaxVelocity((10.0/4.0)*chassis->getMaxVelocity());
    chassis->setGains(       
        {0.001, 0, 0.00004},
        {0.0012, 0, 0.00002},
        {0.0005, 0, 0.0000}
    );

    chassis->turnAngle(90_deg);

    chassis->setMaxVelocity(0.4*chassis->getMaxVelocity());
    chassis->setGains(
        {0.005, 0, 0.00012},
        {0.005, 0, 0.00012},
        {0.001, 0, 0.0000}
    );
}

/**
 *  Match Auto with the mogo on the left side that drops it after grabbing it.
 */
void matchLeftMogoDropAuto() {
    // Set speed to max
    chassis->setMaxVelocity((10.0/4.0)*chassis->getMaxVelocity());
    chassis->setGains(       
        {0.001, 0, 0.00004},
        {0.005, 0, 0.00012},
        {0.0005, 0, 0.0000}
    );

    // Lower acceleration to prevent it from hopping onto the red ring and getting stuck
    setDriveMotorCurrentLimits(1800);
    
    // Begin moving towards plus-side mogo 
    pros::Task* moveTask = new pros::Task(moveTaskFunction);

    // Set up a timer to clamp the mogo. Once clamped, cancel the movement task to make the robot stop.
    pros::Task task{[=] {
            pros::delay(1150);
            toggleMogoClamp();
            if (moveTask) {
                moveTask->remove(); // Stop the task
                delete moveTask;
            }
    }};

    // This delay is necessary as tasks are immediately passed.
    pros::delay(1200);

    // Set the max velocity and gains to 40 percent max speed.
    chassis->setMaxVelocity(0.4*chassis->getMaxVelocity());
    chassis->setGains(
        {0.005, 0, 0.00012},
        {0.005, 0, 0.00012},
        {0.001, 0, 0.0000}
    );

    // Move back and drop off plus side mogo
    chassis->moveDistance(3.7_ft);
    chassis->waitUntilSettled();
    chassis->turnAngle(-90_deg);
    chassis->waitUntilSettled();
    toggleMogoClamp();
    setDriveMotorCurrentLimits(2500);

    // Go grab alliance side mogo
    chassis->turnAngle(210_deg);
    chassis->waitUntilSettled();
    chassis->moveDistance(-2.1_ft);
    chassis->waitUntilSettled();
    toggleMogoClamp();

    // Move back and turn towards the climb's base
    chassis->moveDistance(2.1_ft);
    chassis->waitUntilSettled();
    chassis->turnAngle(125_deg);
    chassis->waitUntilSettled();

    // Move onto the climb base, and while doing so score the preload.
    moveTask = new pros::Task(moveTaskFunctionAgain); 
    pros::delay(2000);
    toggleMogoClamp();
    pros::delay(100);
    setLiftSpeed(127);
    pros::delay(500);
}

void matchLeftMogoKeepAuto() {
    // Set speed to max
    chassis->setMaxVelocity((10.0/4.0)*chassis->getMaxVelocity());
    chassis->setGains(       
        {0.0009, 0, 0.00004},
        {0.005, 0, 0.00012},
        {0.000, 0, 0.0000}
    );

    // Lower acceleration to prevent it from hopping onto the red ring and getting stuck
    setDriveMotorCurrentLimits(1000);
    
    // Begin moving towards plus-side mogo 
    pros::Task* moveTask = new pros::Task(moveTaskFunction);

    // Set up a timer to clamp the mogo. Once clamped, cancel the movement task to make the robot stop.
    pros::Task task{[=] {
            pros::delay(1275);
            toggleMogoClamp();
            if (moveTask) {
                moveTask->remove(); // Stop the task
                delete moveTask;
            }
    }};

    // This delay is necessary as tasks are immediately passed.
    pros::delay(1300);

    // Set the max velocity and gains to 40 percent max speed.
    chassis->setMaxVelocity(0.4*chassis->getMaxVelocity());
    chassis->setGains(
        {0.005, 0, 0.00012},
        {0.005, 0, 0.00012},
        {0.001, 0, 0.0000}
    );

    // reset Current limits back to where they need to be
   setDriveMotorCurrentLimits(2000);

    // Move back and turn towards near ring stack
    setLiftSpeed(1);
    chassis->moveDistance(2.7_ft);
    chassis->waitUntilSettled();
    chassis->turnAngle(90_deg);
    chassis->waitUntilSettled();
    setLiftSpeed(0);
    pros::Task taskIntake(intakeUntilColor);
    chassis->moveDistance(1.6_ft);
    chassis->waitUntilSettled();
    pros::delay(2000);
    chassis->turnAngle(180_deg);
    chassis->waitUntilSettled();
    setLiftSpeed(1);
    chassis->moveDistance(3.5_ft);
    setLadybrownSpeed(40);
    pros::delay(3000);
    setLadybrownSpeed(0);
    pros::delay(3000);
    setLiftSpeed(0);
}

/**
* Small bot's skills auto
*/
void skillsAuto() {
    //portion to grab first donut
    pros::Task* intakeTask = new pros::Task(intakeUntilColor);
	chassis->moveDistance(3.4_ft);
    chassis->waitUntilSettled();
    pros::delay(700);
	chassis->moveDistance(-0.35_ft);
    chassis->waitUntilSettled();
    

    // Drive to and grab first mogo
    chassis->turnAngle(90_deg);
    chassis->waitUntilSettled();
    chassis->moveDistance(-1.7_ft);
    chassis->waitUntilSettled();
    toggleMogoClamp();
    pros::delay(200);
    setLiftSpeed(1);
    pros::delay(500);
    setLiftSpeed(1);

    // Grab autoline ring.
    chassis->turnAngle(-90_deg);
    chassis->waitUntilSettled();
    setLiftSpeed(1);
    chassis->moveDistance(2.4_ft);
    chassis->waitUntilSettled();
    setLiftSpeed(1);
    pros::delay(500);

    // Grab ring that is close to corner
    chassis->turnAngle(180_deg);
    chassis->waitUntilSettled();
    setLiftSpeed(1);
    chassis->moveDistance(4.7_ft);
    chassis->waitUntilSettled();
    setLiftSpeed(1);
    pros::delay(1000);
    chassis->moveDistance(-.4_ft);
    chassis->waitUntilSettled();


    // Grab corner ring
    // chassis->turnAngle(45_deg);
    // chassis->waitUntilSettled();
    // pros::Task* driveTask = new pros::Task(moveTaskFunctionAgain2);
    // pros::delay(2000);
    // driveTask->remove();

    // Back off from corner and place goal
    // chassis->moveDistance(-1.2_ft);
    // chassis->waitUntilSettled();
    chassis->turnAngle(-135_deg);
    chassis->waitUntilSettled();
    setLiftSpeed(0);
    // chassis->turnAngle(180_deg);
    // chassis->waitUntilSettled();
    chassis->moveDistance(-0.8_ft);
    chassis->waitUntilSettled();
    toggleMogoClamp();
    pros::delay(500);

    // Drive to the mogo on the other side of the field on auto line close to 
    chassis->moveDistance(1.1_ft);
    chassis->waitUntilSettled();
    chassis->turnAngle(-45_deg);
    chassis->waitUntilSettled();
    chassis->moveDistance(4_ft);
    chassis->waitUntilSettled();
    chassis->turnAngle(-135_deg);
    chassis->waitUntilSettled();  
    chassis->moveDistance(-1.5_ft);
    chassis->waitUntilSettled();  
    toggleMogoClamp();
    pros::delay(500);

    // Bring mogo to corner
    chassis->turnAngle(90_deg);
    chassis->waitUntilSettled();
    setLiftSpeed(1);
    chassis->moveDistanceAsync(4_ft);
    chassis->waitUntilSettled();
    pros::delay(3000);
    chassis->moveDistance(1.5_ft);
    chassis->waitUntilSettled();
    chassis->turnAngle(180_deg);
    chassis->waitUntilSettled();  
    chassis->moveDistance(5_ft);
    chassis->waitUntilSettled();




}