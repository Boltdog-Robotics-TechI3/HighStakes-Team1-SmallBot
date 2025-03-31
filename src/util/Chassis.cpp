#include "main.h"

Chassis::Chassis(std::vector<std::int8_t>& leftMotorPorts, 
                 std::vector<std::int8_t>& rightMotorPorts, 
                 TrackingWheel leftTrackingWheel, 
                 TrackingWheel rightTrackingWheel, 
                 TrackingWheel backTrackingWheel,
                 double wheelDiameter,
                 double wheelBase,
                 double wheelTrack)
    : leftMotorGroup({leftMotorPorts[0], leftMotorPorts[1], leftMotorPorts[2]}),
      rightMotorGroup({rightMotorPorts[0], rightMotorPorts[1], rightMotorPorts[2]}) {
    this->leftTrackingWheel = leftTrackingWheel;
    this->rightTrackingWheel = rightTrackingWheel;
    this->backTrackingWheel = backTrackingWheel;
}