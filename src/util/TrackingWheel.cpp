#include "main.h"

TrackingWheel::TrackingWheel(int rotationSensorPort, Pose2D offset, double wheelDiameter)
    : encoder(rotationSensorPort), offset(offset), wheelDiameter(wheelDiameter) {
    
    if (offset.getHeading() == 0) {
        wheelOrientation = 0; // horizontal wheel
    } else if (offset.getHeading() == M_PI / 2.0) {
        wheelOrientation = 1; // vertical wheel
    } else {
        wheelOrientation = 2; // diagonal wheel
    }
}

double TrackingWheel::getWheelRotations() {
    // the tracking wheel getPostion() method returns the distance in centidegrees.
    // 1 rotation = 360 degrees = 36000 centidegrees
    return encoder.get_position() / 100.0 / 360.0;
}

double TrackingWheel::getWheelDistance() {
    return getWheelRotations() * wheelDiameter * M_PI;
}

double TrackingWheel::getWheelOffsetX() {
    return offset.getX();
}

double TrackingWheel::getWheelOffsetY() {
    return offset.getY();
}

double TrackingWheel::getWheelOffsetAngle() {
    return offset.getHeading();
}