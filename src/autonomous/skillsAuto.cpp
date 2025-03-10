#include "main.h"
using namespace okapi;

/**
* Small bot's skills auto
*/
void skillsAuto() {
    // putting first ring on wall stake
    chassis->setMaxVelocity(0.7*chassis->getMaxVelocity());
    gyro.set_heading(0);
    //setDriveMotorCurrentLimits(1400);
    setLadybrownPosition(200, 50);
    pros::delay(500);
    setLadybrownPosition(140, 50);
    pros::delay(500);
    setIntakeSpeed(127);
    setLiftSpeed(127);
    chassis->moveDistance(17_in);
    chassis->waitUntilSettled();
    chassis->moveDistance(-1.5_in);
    chassis->waitUntilSettled();
    pros::delay(300);
    turnToHeading(183, 0.6);
    setLiftSpeed(0);
    setIntakeSpeed(0);
    pros::delay(300);
    setLadybrownPosition(950, 150);
    pros::delay(1000);
    chassis->moveDistance(-1.1_ft);
    chassis->waitUntilSettled();
    setLadybrownPosition(0, 50);

    // going for next ring
    turnToHeading(315, 0.7);
    setIntakeSpeed(127);
    pros::Task* intakeTask = new pros::Task(intakeUntilColor);
    chassis->moveDistance(5.5_ft);
    chassis->waitUntilSettled();

    // get ring from mid
    turnToHeading(45, 0.7);
    chassis->moveDistance(3.6_ft);
    chassis->waitUntilSettled();
    chassis->moveDistance(-3.7_ft);
    chassis->waitUntilSettled();
    setIntakeSpeed(0);
    
    //getting mogo
    turnToHeading(90, 0.7);
    chassis->moveDistance(-3.4_ft);
    chassis->waitUntilSettled();
    toggleMogoClamp();
    setIntakeSpeed(127);
    setLiftSpeed(127);

    // getting the ring by corner
    turnToHeading(180, 0.6);
    chassis->moveDistance(4.1_ft);
    chassis->waitUntilSettled();

    // going to the corner (time out)
    turnToHeading(225, 0.7);
    chassis->moveDistanceAsync(2.6_ft);
    pros::delay(2000);
    chassis->moveDistance(-19_in);
    chassis->waitUntilSettled();
    setLiftSpeed(0);
    setIntakeSpeed(0);
    turnToHeading(45, 0.6);
    chassis->moveDistance(-10_in);
    chassis->waitUntilSettled();
    toggleMogoClamp();
    pros::delay(750);

    // Drive to other side of field
    chassis->moveDistance(1_ft);
    chassis->waitUntilSettled();
    turnToHeading(0, 0.7);
    setIntakeSpeed(127);
    pros::Task* intakeTaskTwo = new pros::Task(intakeUntilColor);
    chassis->setMaxVelocity(3*chassis->getMaxVelocity());
    chassis->setGains(       
        {0.0015, 0, 0.00004},
        {3.0, 0, 0.00},
        {0.0005, 0, 0.0000}
    );
    chassis->moveDistance(7_ft);
    chassis->waitUntilSettled();
    chassis->setMaxVelocity((1.0/3.0)*chassis->getMaxVelocity());
    chassis->setGains(       
        {0.0045, 0, 0.0001},
        {3.0, 0.00, 0},
        {0.0, 0, 0.0000}
    );
    chassis->moveDistance(4.2_ft);
    chassis->waitUntilSettled();
    turnToHeading(270, 0.7);
    chassis->moveDistance(-4.2_ft);
    chassis->waitUntilSettled();
    toggleMogoClamp();
    chassis->moveDistance(1_ft);
    chassis->waitUntilSettled();
    setLiftSpeed(127);
 


    // Drive into center
    // turnToHeading(135);
    // pros::Task* intakeTaskAgain = new pros::Task(intakeUntilColor);
    // chassis->moveDistance(3_ft);
    // chassis->waitUntilSettled();
    // chassis->moveDistance(-3_ft);
    // chassis->waitUntilSettled();

    // Drive into Corner
    turnToHeading(140);
    chassis->setMaxVelocity(3*chassis->getMaxVelocity());
    chassis->setGains(       
        {0.0015, 0, 0.00004},
        {3.0, 0, 0.00},
        {0.0005, 0, 0.0000}
    );
    chassis->moveDistanceAsync(-9_ft);
    pros::delay(2000);
    toggleMogoClamp();
    pros::delay(500);
    chassis->moveDistance(3_ft);

    
    

    pros::delay(10000);

}