#include "utilHeaders/Drivetrain.hpp"

Drivetrain::Drivetrain(pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double wheelDiameter, double wheelTrack, double gearRatio) {
    this->leftMotorGroup = &leftMotors;
    this->rightMotorGroup = &rightMotors;
    this->wheelDiameter = wheelDiameter;
    this->wheelTrack = wheelTrack;
    this->gearRatio = gearRatio;
}

Drivetrain::Drivetrain() {
    this->leftMotorGroup = NULL;
    this->rightMotorGroup = NULL;
    this->wheelDiameter = 4.0;
    this->wheelTrack = 10.0;
    this->gearRatio = 1.0;
}

/**
 * @brief Resets the motor encoders to 0
 * 
 * This function sets the zero position of all motors in the left and right motor groups to 0.
 */
void Drivetrain::reset() {
  leftMotorGroup->set_zero_position_all(0);
  rightMotorGroup->set_zero_position_all(0);
}

double Drivetrain::getLeftIME() {
    return leftMotorGroup->get_position(); 
  };
  
double Drivetrain::getRightIME() {
  return rightMotorGroup->get_position(); 
};

pros::v5::MotorBrake Drivetrain::getBrakeMode() {
  return leftMotorGroup->get_brake_mode();
}

int Drivetrain::getCurrentLimit() {
  return leftMotorGroup->get_current_limit();
};

int Drivetrain::getLeftSideSpeed(){
  return leftMotorGroup->get_actual_velocity();
};

int Drivetrain::getRightSideSpeed() {
  return rightMotorGroup->get_actual_velocity();
};

void Drivetrain::setBrakeMode(pros::motor_brake_mode_e_t mode) {
  leftMotorGroup->set_brake_mode(mode);
  rightMotorGroup->set_brake_mode(mode);
};

void Drivetrain::setCurrentLimits(int limit) {
  leftMotorGroup->set_current_limit(limit);
  rightMotorGroup->set_current_limit(limit);
};

void Drivetrain::setLeftSideSpeed(double leftSpeed) {
  leftMotorGroup->move(leftSpeed);
};

void Drivetrain::setRightSideSpeed(double rightSpeed) {
  rightMotorGroup->move(rightSpeed);
};
