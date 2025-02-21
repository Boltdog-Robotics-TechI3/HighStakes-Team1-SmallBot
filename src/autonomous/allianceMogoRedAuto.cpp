#include "main.h"
using namespace okapi;

void allianceMogoRedAuto() {
    // Limit Speeds for accuracy
    chassis->setMaxVelocity(0.6*chassis->getMaxVelocity());
    setDriveMotorCurrentLimits(1300);
    gyro.set_heading(225);

    // Grab Alliance Mogo
    turnToHeading(268);
    chassis->moveDistance(-5.5_ft);
    setMogoClamp(true);

    // Score Preload
    setLiftSpeed(1);
    setIntakeSpeed(1);
    pros::delay(500);

    // Ready Ladybrown
    setLadybrownPosition(200, 50);
    pros::delay(1000);
    setLadybrownPosition(140, 50);

    // Intake ring, readying it in the ladybrown
    turnToHeading(225);
    chassis->moveDistance(2.3_ft);

    // Back up and move to align with alliance stake
    chassis->moveDistance(-2.3_ft);
    setIntakeSpeed(0);
    setLiftSpeed(0);
    pros::delay(300);
    turnToHeading(270);
    chassis->moveDistance(2_ft);
    turnToHeading(180);
    chassis->moveDistance(1_ft);

    // Score ring on allinace stake
    setLadybrownPosition(999, 100);
    pros::delay(1000);

    // Back off from allinace stake 
    chassis->setMaxVelocity(1.667*chassis->getMaxVelocity());
    chassis->moveDistance(-1.1_ft);
    setLadybrownPosition(0, 80);

    // Drive to and intake ring near left corner
    turnToHeading(270);
    setLiftSpeed(1);
    setIntakeSpeed(1);
    chassis->moveDistance(7.1_ft);

    // Back up and turn towards ladder
    setIntakeSpeed(0);
    chassis->moveDistance(-2.3_ft);
    setLiftSpeed(0);
    turnToHeading(45);

    // Drive to ladder and extend ladybrown to contact it
    chassis->moveDistance(3.8_ft);
    setLadybrownPosition(999, 100);
    pros::delay(2000);
    ladybrownGroup.move(0);
    pros::delay(10000);
}    