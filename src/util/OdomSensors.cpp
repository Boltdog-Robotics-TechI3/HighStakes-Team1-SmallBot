#include "utilHeaders/OdomSensors.hpp"
// #include "OdomSensors.hpp"

OdomSensors::OdomSensors(TrackingWheel *leftWheel, TrackingWheel *rightWheel, TrackingWheel *backWheel, pros::IMU *imu) {
    this->leftWheel = leftWheel;
    this->rightWheel = rightWheel;
    this->backWheel = backWheel;
    this->imu = imu;

    if (leftWheel != NULL) {
        leftWheelOffset = leftWheel->getWheelOffsetX().asIN();
    } else {
        leftWheelOffset = 0.0;
    }

    if (rightWheel != NULL) {
        rightWheelOffset = rightWheel->getWheelOffsetX().asIN();
    } else {
        rightWheelOffset = 0.0;
    }
}

OdomSensors::OdomSensors(TrackingWheel *leftWheel, TrackingWheel *rightWheel, TrackingWheel *backWheel) {
    this->leftWheel = leftWheel;
    this->rightWheel = rightWheel;
    this->backWheel = backWheel;
    this->imu = NULL;

    if (leftWheel != NULL) {
        leftWheelOffset = leftWheel->getWheelOffsetX().asIN();
    } else {
        leftWheelOffset = 0.0;
    }

    if (rightWheel != NULL) {
        rightWheelOffset = rightWheel->getWheelOffsetX().asIN();
    } else {
        rightWheelOffset = 0.0;
    }
}

OdomSensors::OdomSensors(pros::IMU *imu) {
    this->leftWheel = NULL;
    this->rightWheel = NULL;
    this->backWheel = NULL;
    this->imu = imu;
}

OdomSensors::OdomSensors() {
    this->leftWheel = NULL;
    this->rightWheel = NULL;
    this->backWheel = NULL;
    this->imu = NULL;
}