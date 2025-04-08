#pragma once
#include "api.h"
#include "utilHeaders/TrackingWheel.hpp"

class Chassis {
    private: 
        pros::MotorGroup* leftMotorGroup;
        pros::MotorGroup* rightMotorGroup;

        // Vertical Tracking Wheels
        TrackingWheel* leftTrackingWheel;
        TrackingWheel* rightTrackingWheel;

        // Horizontal Tracking Wheel
        TrackingWheel* backTrackingWheel;

        double wheelDiameter = 4.0; // inches
        double wheelBase = 11.5; // inches
        double wheelTrack;
        double gearRatio;

    public:
        Chassis(pros::MotorGroup* leftMotorGroup,
                pros::MotorGroup* rightMotorGroup, 
                TrackingWheel* leftTrackingWheel, 
                TrackingWheel* rightTrackingWheel, 
                TrackingWheel* backTrackingWheel,
                double wheelDiameter,
                double wheelBase,
                double wheelTrack,
                double gearRatio); 

        Chassis(pros::MotorGroup* leftMotorGroup,
                pros::MotorGroup* rightMotorGroup, 
                double wheelDiameter,
                double wheelBase,
                double wheelTrack,
                double gearRatio);    

        Chassis();

        //get motor encoders
        double getLeftMotorEncoder();
        double getRightMotorEncoder();

        pros::v5::MotorBrake getBrakeMode();
        double getCurrentLimit();

        double getLeftSideSpeed();
        double getRightSideSpeed();

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