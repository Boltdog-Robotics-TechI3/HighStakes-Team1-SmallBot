#include "utilHeaders/ChassisController.hpp"

// ChassisController::arcade

ChassisController::ChassisController(Drivetrain &drivetrain, OdomSensors &odomSensors) {
    this->drivetrain = &drivetrain;
    this->odomSensors = &odomSensors;
}


void ChassisController::arcade(int leftY, int rightX) {
    // Calculate the left and right wheel speeds based on the forward and turn inputs
    int leftSpeed = leftY + rightX;
    int rightSpeed = leftY - rightX;

    // Scale the speeds to the range of -127 to 127
    leftSpeed = std::clamp(leftSpeed, -127, 127); 
    rightSpeed = std::clamp(rightSpeed, -127, 127); 

    // Set the motor speeds
    drivetrain->setLeftSideSpeed(leftSpeed);
    drivetrain->setRightSideSpeed(rightSpeed); 
}

void ChassisController::tank(int leftY, int rightY) {
    //clamp the inputs to the range of -127 to 127
    leftY = std::clamp(leftY, -127, 127);    
    rightY = std::clamp(rightY, -127, 127); 

    // Set the motor speeds for tank drive
    drivetrain->setLeftSideSpeed(leftY);
    drivetrain->setRightSideSpeed(rightY); 
}

void ChassisController::stop() {
    // Stop the motors by setting their speeds to 0
    drivetrain->setLeftSideSpeed(0);
    drivetrain->setRightSideSpeed(0); 
}

Angle delTheta;

//https://thepilons.ca/wp-content/uploads/2018/10/Tracking.pdf 
void ChassisController::calculate() {
    Pose2D updatedPosition;

    //this is step one
    double currentLeft = this->getLeftWheelDistance();
    // auto currentRight = this->getRightWheelDistance();
    double currentBack = this->getBackWheelDistance();

    //2. the change in the encoder conveted to wheel travel
    double previousLeft = odomSensors->getPreviousLeftDistance();
    // auto previousRight = odomSensors->getPreviousRightDistance();
    double previousBack = odomSensors->getPreviousBackDistance();

    double leftChange = currentLeft - previousLeft;
    // auto rightChange = currentRight - previousRight;
    double backChange = currentBack - previousBack;
    
    //3. update previous positions
    odomSensors->updatePreviousTrackingDistances();

    //4 this is cumulative so add to that
    auto formerPosition = this->getCurrentPosition();
    
    odomSensors->addToTotalChanges(leftChange, 0, backChange);

    //5-6. update the heading
    delTheta = odomSensors->getCurrentHeading() - formerPosition.getHeading();
    
    //7-8. 
    double deld[2]; 
    if(delTheta == 0){
        deld[0] = backChange;
        deld[1] = leftChange;
    } else {
        deld[0] = (2 * sin(delTheta.asRad() / 2)) * ((backChange / delTheta.asRad()) + (odomSensors->getBackWheelOffset()));
        deld[1] = (2 * sin(delTheta.asRad() / 2)) * ((leftChange / delTheta.asRad()) + (odomSensors->getLeftWheelOffset()));
    }
    
    //9. get theta m 
    double thetaM = formerPosition.getHeading().asRad() + (delTheta.asRad() / 2);

    //10. 


    this->setPose(updatedPosition);
}

void ChassisController::setPose(Pose2D newPos) {
    this->currentPosition = newPos;
}

Pose2D ChassisController::getCurrentPosition() {
    return this->currentPosition;
}

double ChassisController::getLeftWheelDistance() {
    return odomSensors->getLeftTrackingDistance();
}

double ChassisController::getRightWheelDistance(){
    return odomSensors->getRightTrackingDistance();
}

double ChassisController::getBackWheelDistance(){
    return odomSensors->getBackTrackingDistance();
}





/*
void ChassisController::moveForwardRelative(Distance distance) {
    
}

void ChassisController::turnToHeading(Angle heading){

}

void ChassisController::moveToPoint(Pose2D pose) {
    
}
*/