#include "main.h"
using namespace okapi;

void allianceMogoAuto() {
    chassis->setMaxVelocity(0.6*chassis->getMaxVelocity());
    setDriveMotorCurrentLimits(1300);
    turnAngle(45);
    chassis->moveDistance(-5.5_ft);
    setMogoClamp(true);
    setLiftSpeed(1);
    setIntakeSpeed(1);
    pros::delay(500);
    setLadybrownPosition(200, 50);
    pros::delay(1000);
    setLadybrownPosition(140, 50);
    turnAngle(-45);
    chassis->moveDistance(2_ft);
    chassis->moveDistance(-2_ft);
    setIntakeSpeed(0);
    setLiftSpeed(0);
    pros::delay(300);
    turnAngle(47);
    chassis->moveDistance(2_ft);
    turnAngle(-90);
    chassis->moveDistance(1.1_ft);
    setLadybrownPosition(999, 100);
    pros::delay(1000);
    chassis->setMaxVelocity(1.667*chassis->getMaxVelocity());
    chassis->moveDistance(-1.2_ft);
    setLadybrownPosition(0, 80);
    turnAngle(90);
    setLiftSpeed(1);
    setIntakeSpeed(1);
    chassis->moveDistance(6.5_ft);
    setIntakeSpeed(0);
    chassis->moveDistance(-2_ft);
    setLiftSpeed(0);
    turnAngle(135);
    chassis->moveDistance(3.8_ft);
    setLadybrownPosition(999, 100);
    pros::delay(2000);
    ladybrownGroup.move(0);
    pros::delay(10000);
}    