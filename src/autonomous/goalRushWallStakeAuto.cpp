#include "main.h"
using namespace okapi;

void goalRushWallStakeAuto() {

    // Set speed to max
    chassis->setMaxVelocity((1.5)*chassis->getMaxVelocity());

    // Lower acceleration to prevent it from hopping onto the red ring and getting stuck
    setDriveMotorCurrentLimits(1000);

    //drive to and grab mobile goal
    chassis->moveDistance(5_ft);
    toggleMogoClaw();

    //move mobile goal
    chassis->moveDistance(1_ft);

    //pick up 1st ring
    setDriveMotorCurrentLimits(2500);

    turnAngle(45);
    setLiftSpeed(-127);
    pros::delay(1000);
    setLiftSpeed(0);

    //get second ring
    chassis->moveDistance(2_ft);
    setLiftSpeed(-127);
    pros::delay(1000);
    setLiftSpeed(0);

    //get third ring
    turnAngle(-90);
    chassis->moveDistance(4_ft);
    setLiftSpeed(-127);
    pros::delay(1000);
    setLiftSpeed(0);

    //score on wall stake
    turnAngle(180);
    chassis->moveDistance(0.5_ft);
    setLiftSpeed(-127);
    pros::delay(1000);
    setLiftSpeed(0);

    //go elsewhere
    turnAngle(30);
    chassis->moveDistance(4.5_ft);
}
