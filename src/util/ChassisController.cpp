#include "utilHeaders/ChassisController.hpp"
#include "globals.hpp"


// ChassisController::arcade

ChassisController::ChassisController(Drivetrain &drivetrain, OdomSensors &odomSensors) {
    this->drivetrain = &drivetrain;
    this->odomSensors = &odomSensors;
    pros::Task task{[=] {
        while (true) {
            calculate();
            pros::delay(10);
        }
    }};
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

    // print to the brain screen for debugging

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
    
    odomSensors->addToTotalChanges(leftChange, backChange);

    //5-6. update the heading
    delTheta = odomSensors->getCurrentHeading() - formerPosition.getHeading();
    
    //7-8. 
    double deltaDl[2]; 
    if(delTheta == 0){
        deltaDl[0] = backChange;
        deltaDl[1] = leftChange;
    } else {
        deltaDl[0] = (2 * sin(delTheta.asRad() / 2)) * ((backChange / delTheta.asRad()) + (odomSensors->getBackWheelOffset()));
        deltaDl[1] = (2 * sin(delTheta.asRad() / 2)) * ((leftChange / delTheta.asRad()) + (odomSensors->getLeftWheelOffset()));
    }
    auto deltaD = Pose2D(deltaDl[0], deltaDl[1], delTheta);
    
    //9. get theta m 
    double thetaM = formerPosition.getHeading().asRad() + (delTheta.asRad() / 2);

    //10. 
    deltaD.rotate(-1 * thetaM);

    //11.
    updatedPosition.setPose(formerPosition.getX() + deltaD.getX(), formerPosition.getY() + deltaD.getY(), delTheta);
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





/**
 * @brief Move the robot forward a specified distance.
 * @param distance The distance to move forward.
*/
void ChassisController::moveForwardRelative(Distance distance) {
    
}

/**
 * @brief Turn the robot to a specified heading.
 * @param heading The heading to turn to.
*/
void ChassisController::turnToHeading(Angle heading/*, double angle, double maxVel, PIDController pid */){
    /*double point = angle + heading;
    double error = angle;
    double previousError = 0;
    double intergral = 0;

    bool targetReached = false;

    while(!targetReached){
        double velocity = pid.getP * error + ((error - previousError) * pid.getD) + (pid.getI * intergral); // this is not yet including the time change
        
        if(velocity > 0){
          velocity = std::clamp(velocity + pid.miniVelocity, 0.0, 600.0 * maxVel);
        } else if(velocity < 0){
         velocity = std::clamp(veloity - pid.miniVelocity, -600.0 * maxVel, 0.0);
         }
    } */
}

/**
 * @brief A simple move to point function that drives the robot
 *   to a specified point in the field by first turning to face the point and then moving forward.
 * @param pose The target pose to move to.
*/
void ChassisController::moveToPoint(Pose2D pose) {
    // Calculate the angle to the target point
    double deltaX = pose.getX().asIN() - currentPosition.getX().asIN();
    double deltaY = pose.getY().asIN() - currentPosition.getY().asIN();
    double targetAngle = atan2(deltaY, deltaX); // Angle to the target point


    
}
