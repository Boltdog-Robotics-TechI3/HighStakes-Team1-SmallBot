#include "api.h"
#include "utilHeaders/motionProfileController.hpp"
#include "globals.hpp"

MotionProfileController::MotionProfileController(double maxAcceleration, double maxVelocity){
this->maxAcceleration = maxAcceleration;
this->maxVelocity = maxVelocity;
this->PIDcontroller = PIDController(10, 0, 0);
} 
void MotionProfileController::reset(double setpoint){
this->PIDcontroller.reset(); 
this->setpoint = setpoint;
this->startTime = pros::millis();
this->timeAcceleration = maxVelocity / maxAcceleration;
this->distanceTraveledAcceleration = 1/2 * timeAcceleration * maxVelocity;
this->distanceTraveledMaxVelocity = setpoint - distanceTraveledAcceleration * 2;
this->timeAtMaxVelocity = distanceTraveledMaxVelocity / maxVelocity;
this->totalTime = 2 * timeAcceleration + timeAtMaxVelocity;
}
double MotionProfileController::calculate(int currentTime, double currentVelocity){
    double velocity;
    double localTime = currentTime - startTime;
    if(localTime < timeAcceleration){
        velocity = (localTime/timeAcceleration) * maxVelocity;
    }
     else if(localTime < timeAcceleration + timeAtMaxVelocity){
        velocity = maxVelocity;
    }
    else if(localTime < totalTime){
        velocity = maxVelocity * (1 - (localTime - (timeAcceleration + timeAtMaxVelocity)) / timeAcceleration);
    }
driverController.set_text(0,0, std::to_string(velocity));
velocity = this->PIDcontroller.calculate(currentVelocity, velocity);
pros::delay(50);
driverController.set_text(1,0, std::to_string(velocity));
return velocity;
}

double MotionProfileController::getTotalTime(){
    return totalTime;
}
