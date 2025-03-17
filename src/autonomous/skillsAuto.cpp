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
    chassis->moveDistance(5.4_ft);

    // get ring from mid
    turnToHeading(45, 0.7);
    setIntakeSpeed(1);
    chassis->moveDistance(3.4_ft);
    setIntakeSpeed(0);
    chassis->moveDistance(-3.7_ft);
    
    //getting mogo
    chassis->setMaxVelocity((6/10.0)*chassis->getMaxVelocity());
    turnToHeading(90, 0.6);
    chassis->moveDistance(-3.2_ft);
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
    // gyro.set_heading(gyro.get_heading()+3.5);
    turnToHeading(70, 0.6);
    toggleMogoClamp();
    chassis->moveDistanceAsync(-16_in);
    pros::delay(1000);

    // Drive to other side of field
    chassis->moveDistance(1.6_ft);
    turnToHeading(0, 0.7);
    intakeTask.resume();
    setIntakeSpeed(1);

    // Ready the ladybrown and pick up ring in stack next to wall stake
    // setLadybrownPosition(200, 50);
    // pros::delay(250);
    // setLadybrownPosition(143, 50);
    // pros::delay(250);
    chassis->setMaxVelocity((6/10.0)*chassis->getMaxVelocity());
    chassis->moveDistanceAsync(10.9_ft);
    pros::delay(4000);
    chassis->stop();
    chassis->setMaxVelocity((10/6.0)*chassis->getMaxVelocity());

    // chassis->moveDistanceAsync(-2_ft);
    // pros::delay(2200);
    // setIntakeSpeed(0);
    // turnToHeading(0, 2);
    // chassis->moveDistanceAsync(2_ft);
    // pros::delay(1500);




    // Place ring on wall stake (all of these lift methods are to push the ring into position)
    // turnToHeading(272, 0.7);
    // chassis->moveDistanceAsync(1.3_ft);
    // pros::delay(500);
    // setLiftSpeed(-0.5);
    // pros::delay(200);
    // setLiftSpeed(1);
    // pros::delay(500);
    // setLiftSpeed(-0.5);
    // pros::delay(200);
    // setLiftSpeed(1);
    // pros::delay(500);
    // setLiftSpeed(-0.5);
    // pros::delay(200);
    // setLiftSpeed(1);
    // pros::delay(500);
    // setLiftSpeed(0);

    // setLadybrownPosition(950, 150);
    // pros::delay(500);
    // chassis->moveDistance(-2.5_ft);
    // setLadybrownPosition(0, 50);

    // Pick up first ring on other side of the field
    // turnToHeading(0, 0.7);
   
    // chassis->moveDistance(3.5_ft);

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
    turnToHeading(0, 0.7);
    chassis->moveDistance(3.6_ft);
    turnToHeading(270, 0.7);
    chassis->moveDistance(4_ft);

    // Place mogo in far corner
    chassis->setMaxVelocity((6/10.0)*chassis->getMaxVelocity());
    turnToHeading(165, 0.6);
    toggleMogoClamp();
    chassis->moveDistanceAsync(-3_ft);
    pros::delay(1000);

    // Drive to ring next to blue stake
    // chassis->moveDistance(3_ft);
    // turnToHeading(68, 0.7);
    // chassis->moveDistance(5_ft);
    
    

    pros::delay(10000);

}