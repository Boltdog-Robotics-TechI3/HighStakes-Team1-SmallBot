#include "utilHeaders/Odometry.hpp"

Odometry::Odometry(TrackingWheel *leftWheel, TrackingWheel *rightWheel, TrackingWheel *backWheel, pros::IMU *imu) {
    this->leftWheel = leftWheel;
    this->rightWheel = rightWheel;
    this->backWheel = backWheel;
    this->imu = imu;
}