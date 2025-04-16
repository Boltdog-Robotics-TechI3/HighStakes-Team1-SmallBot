#pragma once

#include "utilHeaders/TrackingWheel.hpp"
#include "utilHeaders/Pose2D.hpp"
#include "api.h"

class OdomSensors {
    private:
        TrackingWheel *leftWheel;
        TrackingWheel *rightWheel;
        TrackingWheel *backWheel;
        pros::IMU *imu;

        double leftWheelOffset; // The horizontal distance of the left wheel from the center of the bot (in inches)
        double rightWheelOffset; // The horizontal distance of the right wheel from the center of the bot (in inches)

    public:
        OdomSensors(TrackingWheel *leftWheel, TrackingWheel *rightWheel, TrackingWheel *backWheel, pros::IMU *imu);

        OdomSensors(TrackingWheel *leftWheel, TrackingWheel *rightWheel, TrackingWheel *backWheel);

        OdomSensors(pros::IMU *imu);

        OdomSensors();

        double getLeftTrackingDistance() {
            return leftWheel->getWheelDistance();
        };

        double getRightTrackingDistance() {
            return rightWheel->getWheelDistance();
        };

        double getBackTrackingDistance() {
            return backWheel->getWheelDistance();
        };
        

};