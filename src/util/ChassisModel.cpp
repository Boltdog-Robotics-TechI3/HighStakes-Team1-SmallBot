#include "utilHeaders/ChassisController.hpp"

// ChassisController::arcade

ChassisController::ChassisController(Chassis &chassis){
    this->chassis = &chassis;
}


void ChassisController::arcade(int leftY, int rightX) {
    // Calculate the left and right wheel speeds based on the forward and turn inputs
    int leftSpeed = leftY + rightX;
    int rightSpeed = leftY - rightX;

    // Scale the speeds to the range of -127 to 127
    leftSpeed = std::clamp(leftSpeed, -127, 127); 
    rightSpeed = std::clamp(rightSpeed, -127, 127); 

    // Set the motor speeds
    chassis->setLeftSideSpeed(leftSpeed);
    chassis->setRightSideSpeed(rightSpeed); 
}

void ChassisController::tank(int leftY, int rightY) {
    //clamp the inputs to the range of -127 to 127
    leftY = std::clamp(leftY, -127, 127);    
    rightY = std::clamp(rightY, -127, 127); 

    // Set the motor speeds for tank drive
    chassis->setLeftSideSpeed(leftY);
    chassis->setRightSideSpeed(rightY); 
}

void ChassisController::stop() {
    // Stop the motors by setting their speeds to 0
    chassis->setLeftSideSpeed(0);
    chassis->setRightSideSpeed(0); 
}

void ChassisController::moveForwardRelative(Distance distance) {
    
}

void ChassisController::turnToHeading(Angle heading){

}