#include "utilHeaders/TrackingWheel.hpp"
#include "api.h"
#include <math.h>

TrackingWheel::TrackingWheel(pros::Rotation &rotationSensor, Pose2D offset, double wheelDiameter) {
    
    this->encoder = &rotationSensor; // set the encoder to the rotation sensor object passed in
    this->offset = offset; // set the offset to the pose2D object passed in
    this->wheelDiameter = wheelDiameter; // set the wheel diameter to the value passed in

    if (offset.getHeading() == 0) {
        wheelOrientation = 0; // horizontal wheel
    } else if (offset.getHeading() == M_PI / 2.0) {
        wheelOrientation = 1; // vertical wheel
    } else {
        wheelOrientation = 2; // diagonal wheel
    }
}

void TrackingWheel::reset() {
    encoder->set_position(0); // reset the encoder position to 0
    previousPosition = 0; // reset the previous position to 0
}

double TrackingWheel::getWheelRotations() {
    // the tracking wheel getPostion() method returns the distance in centidegrees.
    // 1 rotation = 360 degrees = 36000 centidegrees
    return (encoder->get_position() / 100.0) / 360.0; //in rotations
}

double TrackingWheel::getWheelDistance() {
    return getWheelRotations() * wheelDiameter * M_PI;
}

Distance TrackingWheel::getWheelOffsetX() {
    return offset.getX();
}

Distance TrackingWheel::getWheelOffsetY() {
    return offset.getY();
}

Angle TrackingWheel::getWheelOffsetAngle() {
    return offset.getHeading();
}

void TrackingWheel::updatePreviousDistance(){
    previousPosition = ((encoder->get_position() / 100.0) / 360.0) * wheelDiameter * M_PI;
}

double TrackingWheel::getPreviousDistance() {
    return previousPosition; 
}

