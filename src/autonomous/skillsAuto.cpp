#include "main.h"
using namespace okapi;

/**
* Scores the first ring on the red alliance stake
*/
void scoreOnRedStake() {
    // putting first ring on alliance stake
    gyro.set_heading(0);
    setLadybrownPosition(200, 50);
    pros::delay(250);
    setLadybrownPosition(138, 50);
    pros::delay(250);
    setIntakeSpeed(127);
    setLiftSpeed(127);
    chassis->moveDistance(24_in);
    chassis->moveDistance(-8.5_in);
    turnToHeading(183, 0.8);
    setLiftSpeed(0);
    setIntakeSpeed(0);
    pros::delay(100);
    setLadybrownPosition(950, 150);
    pros::delay(500);
    chassis->moveDistance(-1.1_ft);
}

/***************************
* Small bot's skills auto
****************************/
void skillsAuto() {
    scoreOnRedStake();
    setLadybrownPosition(0, 50);

    // going for next ring
    turnToHeading(315, 0.7);
    intakeTask.resume();
    chassis->moveDistance(5.6_ft);

    // get ring from mid
    turnToHeading(45, 0.7);
    setIntakeSpeed(1);
    chassis->moveDistance(3.4_ft);
    setIntakeSpeed(0);
    chassis->moveDistance(-3.7_ft);
    
    //getting mogo
    chassis->setMaxVelocity((6/10.0)*chassis->getMaxVelocity());
    turnToHeading(90, 0.6);
    chassis->moveDistance(-3.4_ft);
    chassis->setMaxVelocity((10/6.0)*chassis->getMaxVelocity());
    toggleMogoClamp();
    pros::delay(250);
    setIntakeSpeed(127);
    setLiftSpeed(127);

    // getting the ring by corner
    turnToHeading(180, 0.6);
    chassis->moveDistance(4.1_ft);

    // going to the corner (time out)
    turnToHeading(225, 0.7);
    chassis->moveDistanceAsync(2.8_ft);
    pros::delay(1500);
    chassis->moveDistance(-19_in);
    setLiftSpeed(0);
    setIntakeSpeed(0);

    // Turn around and place goal in corner
    gyro.set_heading(gyro.get_heading()+3.5);
    turnToHeading(45, 0.6);
    toggleMogoClamp();
    chassis->moveDistanceAsync(-12_in);
    pros::delay(1000);

    // Drive to other side of field
    chassis->moveDistance(1.5_ft);
    turnToHeading(345, 0.7);

    setIntakeSpeed(1);
    setLiftSpeed(1);

    // Ready the ladybrown and pick up ring in stack next to wall stake
    setLadybrownPosition(200, 50);
    pros::delay(250);
    setLadybrownPosition(143, 50);
    pros::delay(250);
    chassis->moveDistanceAsync(7.8_ft);
    pros::delay(2200);
    chassis->stop();

    // Place ring on wall stake
    turnToHeading(272, 0.7);

    chassis->moveDistanceAsync(1.3_ft);
    pros::delay(500);

    setLiftSpeed(0);
    setIntakeSpeed(0);
    pros::delay(100);

    setLadybrownPosition(950, 150);
    pros::delay(500);
    chassis->moveDistance(-2.5_ft);
    setLadybrownPosition(0, 50);

    // Pick up first ring on other side of the field
    turnToHeading(0, 0.7);
    intakeTask.resume();
    chassis->moveDistance(3.7_ft);

    // Pick up next mogo
    chassis->setMaxVelocity((6/10.0)*chassis->getMaxVelocity());
    turnToHeading(270, 0.7);
    chassis->moveDistance(-3.9_ft);
    chassis->setMaxVelocity((10/6.0)*chassis->getMaxVelocity());
    toggleMogoClamp();
    pros::delay(250);

    // Score ring on mogo and pickup next two rings by far corner
    setLiftSpeed(1);
    setIntakeSpeed(1);
    turnToHeading(358, 0.7);
    chassis->moveDistance(3.6_ft);
    turnToHeading(270, 0.7);
    chassis->moveDistance(4_ft);

    // Place mogo in far corner
    turnToHeading(150, 0.6);
    toggleMogoClamp();
    chassis->moveDistanceAsync(-2_ft);
    pros::delay(1000);

    // Drive to ring next to blue stake
    chassis->moveDistance(3_ft);
    turnToHeading(68, 0.7);
    chassis->moveDistance(5_ft);
    
    

    pros::delay(10000);

}