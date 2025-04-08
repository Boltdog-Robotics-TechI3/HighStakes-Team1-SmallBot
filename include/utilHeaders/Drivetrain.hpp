#pragma once
#include "pros/motor_group.hpp"
#include "utilHeaders/Chassis.hpp"

class Drivetrain {
    private:
        friend class Chassis;
        pros::MotorGroup *leftMotors;
        pros::MotorGroup *rightMotors;
        double wheelDiameter;
        double wheelTrack;
        double gearRatio;

    public:
        Drivetrain(pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double wheelDiameter, double wheelTrack, double gearRatio);
};