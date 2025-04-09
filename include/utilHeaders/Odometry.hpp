#pragma once

#include "utilHeaders/TrackingWheel.hpp"
#include "utilHeaders/Pose2D.hpp"
#include "api.h"

class Odometry {
    private:
        TrackingWheel *leftWheel;
        TrackingWheel *rightWheel;
        TrackingWheel *backWheel;
        pros::IMU *imu;

        Pose2D pose; // The current pose of the robot (x, y, heading)
        double leftWheelOffset; // The horizontal distance of the left wheel from the center of the bot (in inches)
        double rightWheelOffset; // The horizontal distance of the right wheel from the center of the bot (in inches)

    public:
        Odometry(TrackingWheel *leftWheel, TrackingWheel *rightWheel, TrackingWheel *backWheel, pros::IMU *imu);

        Odometry(pros::IMU *imu);

        Odometry();

        void setPose(Pose2D pose);

        Pose2D getPose();

        

};