#include "utilHeaders/Drivetrain.hpp"

Drivetrain::Drivetrain(pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double wheelDiameter, double wheelTrack, double gearRatio) {
    this->leftMotors = &leftMotors;
    this->rightMotors = &rightMotors;
    this->wheelDiameter = wheelDiameter;
    this->wheelTrack = wheelTrack;
    this->gearRatio = gearRatio;
}