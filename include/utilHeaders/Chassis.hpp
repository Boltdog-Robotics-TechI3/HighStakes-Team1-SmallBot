#include "main.h"

class Chassis {
    private: 
        pros::MotorGroup leftMotorGroup;
        pros::MotorGroup rightMotorGroup;
        double wheelDiameter = 4.0; // inches
        double wheelBase = 11.5; // inches
        double wheelTrack;
    public:
        Chassis(pros::MotorGroup leftMotorGroup, pros::MotorGroup rightMotorGroup);

        //get motor encoders
        double getLeftMotorEncoder();
        double getRightMotorEncoder();
        

};