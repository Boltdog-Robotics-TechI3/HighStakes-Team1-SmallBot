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

/**
 * @brief Resets the odometry sensors to their initial state.
 * This function resets the tracking wheels and IMU to their initial positions.
 */
void OdomSensors::reset() {
    if (leftWheel != NULL) {
        leftWheel->reset();
    }
    if (rightWheel != NULL) {
        rightWheel->reset();
    }
    if (backWheel != NULL) {
        backWheel->reset();
    }
    if (imu != NULL) {
        imu->reset();
        while (imu->is_calibrating()); // Wait for the IMU to calibrate
    }
}

double OdomSensors::getLeftTrackingDistance() {
    if (leftWheel != NULL) {
        return leftWheel->getWheelDistance();
    } else {
        return -1;
    }
};

double OdomSensors::getRightTrackingDistance() {
    if (rightWheel != NULL) {
        return rightWheel->getWheelDistance();
    } else {
        return -1;
    }
};

double OdomSensors::getBackTrackingDistance() {
    if (backWheel != NULL) {
        return backWheel->getWheelDistance();
    } else {
        return -1;
    }
};

void OdomSensors::updatePreviousTrackingDistances() {
    if (leftWheel != NULL) {
        leftWheel->updatePreviousDistance();
    }
    if (rightWheel != NULL) {
        rightWheel->updatePreviousDistance();
    }
    if (backWheel != NULL) {
        backWheel->updatePreviousDistance();
    }
}

double OdomSensors::getPreviousLeftDistance() {
    if (leftWheel != NULL) {
        return leftWheel->getPreviousDistance();
    } else {
        return INT_MIN;
    }
}

double OdomSensors::getPreviousRightDistance() {
    if (leftWheel != NULL) {
        return rightWheel->getPreviousDistance();
    } else {
        return INT_MIN;
    }
}

double OdomSensors::getPreviousBackDistance() {
    if (leftWheel != NULL) {
        return backWheel->getPreviousDistance();
    } else {
        return INT_MIN;
    }
}

double OdomSensors::getLeftWheelOffset() {
    return leftWheelOffset;
}

double OdomSensors::getRightWheelOffset() {
    return rightWheelOffset;
}

double OdomSensors::getBackWheelOffset() {
    return backWheelOffset;
}

Angle OdomSensors::getCurrentHeading() {
    // return Angle::fromDeg(imu->get_heading());
    return 0;
}

Angle OdomSensors::getCurrentRotation() {
    // return imu->get_rotation();
    return 0;
}

void OdomSensors::addToTotalChanges(double leftChange, double backChange) {
    leftWheel->addToTotalChange(leftChange);
    // rightWheel->addToTotalChange(rightChange);
    backWheel->addToTotalChange(backChange);
};