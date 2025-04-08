#include "main.h"

Chassis::Chassis(pros::MotorGroup* leftMotorGroup,
                 pros::MotorGroup* rightMotorGroup, 
                 TrackingWheel* leftTrackingWheel, 
                 TrackingWheel* rightTrackingWheel, 
                 TrackingWheel* backTrackingWheel,
                 double wheelDiameter,
                 double wheelBase,
                 double wheelTrack,
                 double gearRatio)
    : wheelDiameter(wheelDiameter),
      wheelBase(wheelBase),
      wheelTrack(wheelTrack),
      gearRatio(gearRatio) {
        this->leftMotorGroup = leftMotorGroup;
        this->rightMotorGroup = rightMotorGroup;
        this->leftTrackingWheel = leftTrackingWheel;
        this->rightTrackingWheel = rightTrackingWheel;
        this->backTrackingWheel = backTrackingWheel;
      }

Chassis::Chassis(pros::MotorGroup* leftMotorGroup,
                 pros::MotorGroup* rightMotorGroup, 
                 double wheelDiameter,
                 double wheelBase,
                 double wheelTrack,
                 double gearRatio) 
    : wheelDiameter(wheelDiameter),
      wheelBase(wheelBase),
      wheelTrack(wheelTrack),
      gearRatio(gearRatio) {
    leftMotorGroup = leftMotorGroup;
    rightMotorGroup = rightMotorGroup;
      }

Chassis::Chassis()
    : leftMotorGroup(NULL),
      rightMotorGroup(NULL),
      wheelDiameter(4.0),
      wheelBase(11.5),
      wheelTrack(0.0) {}

double Chassis::getLeftMotorEncoder() {

};

double Chassis::getRightMotorEncoder() {

};

pros::v5::MotorBrake getBrakeMode() {
  return leftMotorGroup.get_brake_mode();
}

double getCurrentLimit();

double getLeftSideSpeed();
double getRightSideSpeed();

void setBrakeMode(pros::motor_brake_mode_e_t mode);
void setCurrentLimits(int limit);

void setLeftSideSpeed(double leftSpeed) {
  leftMotorGroup.move(leftSpeed);
};

void setRightSideSpeed(double rightSpeed) {
  rightMotorGroup.move(rightSpeed);
};


