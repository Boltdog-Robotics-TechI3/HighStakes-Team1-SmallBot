#include "main.h"
using namespace okapi;

/**
* Small bot's skills auto
*/
void skillsAuto() {
    //pros::Task* intakeTask = new pros::Task(intakeUntilColor);


    // putting first ring on wall stake
    driverController.set_text(0, 0, "AHHHHHHHHHHHHHHHHH");
    setIntakeSpeed(127);
    setLiftSpeed(127);
    chassis->moveDistance(15_in);
    pros::delay(500);
    setLiftSpeed(0);
    pros::delay(1000);
    setIntakeSpeed(0);
    turnAngle(180);

    // going for next ring
    chassis->moveDistance(3_in);
    turnAngle(-32);
    setLiftSpeed(-127);
    chassis->moveDistance(3_ft);
    pros::delay(1000);
    setLiftSpeed(0);
    
    //getting mogo
    turnAngle(116);
    chassis->moveDistance(-1.3_ft);
    chassis->waitUntilSettled();
    toggleMogoClamp();
    setLiftSpeed(-127);
    pros::delay(1000);
    setLiftSpeed(0);

    // getting the two next ring
    turnAngle(-90);
    setLiftSpeed(-127);
    chassis->moveDistance(1.3_ft);
    chassis->waitUntilSettled();
    setLiftSpeed(0);
    turnAngle(190);
    setLiftSpeed(-127);
    chassis->moveDistance(2.5_ft);
    chassis->waitUntilSettled();

    // going to the corner (time out)
    turnAngle(20);
    setLiftSpeed(-127);
    chassis->moveDistance(19_in);
    setLiftSpeed(0);
    chassis->moveDistance(-2_in);
    turnAngle(180);
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