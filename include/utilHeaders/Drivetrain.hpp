#pragma once
#include "pros/motor_group.hpp"

class Drivetrain {
    private:
        pros::MotorGroup *leftMotorGroup;
        pros::MotorGroup *rightMotorGroup;
        double wheelDiameter;
        double wheelTrack;
        double wheelBase;
        double gearRatio;

    public:
        Drivetrain(pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double wheelDiameter, double wheelTrack, double gearRatio);

        Drivetrain();

        double getLeftMotorEncoder();
        double getRightMotorEncoder();

        pros::v5::MotorBrake getBrakeMode();
        int getCurrentLimit();

        int getLeftSideSpeed();
        int getRightSideSpeed();

        void setBrakeMode(pros::motor_brake_mode_e_t mode);
        void setCurrentLimits(int limit);
        
        void setLeftSideSpeed(double leftSpeed);
        void setRightSideSpeed(double rightSpeed);

        double getGearRatio();
        void setGearRatio(double gearRatio);

        double getWheelDiameter();
        void setWheelDiameter(double wheelDiameter);
        
        double getWheelBase();
        void setWheelBase(double wheelBase);

        double getWheelTrack();
        void setWheelTrack(double wheelTrack);
};