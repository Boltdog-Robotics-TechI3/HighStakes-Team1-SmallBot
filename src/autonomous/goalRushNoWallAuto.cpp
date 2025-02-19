#include "main.h"
using namespace okapi;

//Second goal rush auto that DOESNT score on wall stake
void goalRushNoWallAuto(){
    // Set speed to max
    chassis->setMaxVelocity((10.0/4.0)*chassis->getMaxVelocity());

    // Lower acceleration to prevent it from hopping onto the red ring and getting stuck
    setDriveMotorCurrentLimits(1000);

    //drive to and grab mobile goal

    chassis->setGains(
        {0.001, 0, 0.0000},
        {3.0, 0.00, 0},
        {0.0, 0, 0.0000}
    );
    chassis->moveDistance(7.5_ft);
    chassis->setGains(
        {0.0045, 0, 0.0000},
        {3.0, 0.00, 0},
        {0.0, 0, 0.0000}
    );
    toggleMogoClaw();
    chassis->moveDistance(-1_ft);
    toggleMogoClaw();

    setDriveMotorCurrentLimits(2500);

    //grab mobile goal and turn toward ring
    turnAngle(180);
    toggleMogoClamp();
    turnAngle(180);
    chassis->moveDistance(1_ft);

    //pick up 1st ring
    turnAngle(45);
    setLiftSpeed(127);
    pros::delay(1000);
    setLiftSpeed(0);

    //get second ring
    chassis->moveDistance(2_ft);
    setLiftSpeed(127);
    pros::delay(1000);
    setLiftSpeed(0);

    //get third ring
    turnAngle(45);
    chassis->moveDistance(2_ft);
    setLiftSpeed(127);
    pros::delay(1000);
    setLiftSpeed(0);

    //head toward corner
    turnAngle(45);
    chassis->moveDistance(2.82_ft);

    //grab ring in corner
    setLiftSpeed(127);
    pros::delay(1000);
    setLiftSpeed(0);

    //turn around and drop mogo in corner
    chassis->moveDistance(-2_ft);
    turnAngle(180);
    chassis->moveDistance(2_ft);
    toggleMogoClamp();

    //head toward center ladder
    chassis->moveDistance(7_ft);
}