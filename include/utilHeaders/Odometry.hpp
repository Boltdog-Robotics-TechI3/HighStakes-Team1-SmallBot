#pragma once

#include "utilHeaders/Chassis.hpp"
#include "utilHeaders/TrackingWheel.hpp"

class Odometry {
    private:
        friend class Chassis;
        TrackingWheel *leftWheel;
        TrackingWheel *rightWheel;
        TrackingWheel *backWheel;
        pros::IMU *imu;

    public:
        Odometry(TrackingWheel *leftWheel, TrackingWheel *rightWheel, TrackingWheel *backWheel, pros::IMU *imu);
    
};