#include "utilHeaders/Odometry.hpp"
#include "Odometry.hpp"

Odometry::Odometry(TrackingWheel *leftWheel, TrackingWheel *rightWheel, TrackingWheel *backWheel, pros::IMU *imu) {
    this->leftWheel = leftWheel;
    this->rightWheel = rightWheel;
    this->backWheel = backWheel;
    this->imu = imu;
}

Odometry::Odometry(pros::IMU *imu) {
    this->leftWheel = NULL;
    this->rightWheel = NULL;
    this->backWheel = NULL;
    this->imu = imu;
}

Odometry::Odometry() {
    this->leftWheel = NULL;
    this->rightWheel = NULL;
    this->backWheel = NULL;
    this->imu = NULL;
}