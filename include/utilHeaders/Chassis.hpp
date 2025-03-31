#include "main.h"

class Chassis {
    private: 
        pros::MotorGroup leftMotorGroup;
        pros::MotorGroup rightMotorGroup;

        // Vertical Tracking Wheels
        TrackingWheel leftTrackingWheel;
        TrackingWheel rightTrackingWheel;

        // Horizontal Tracking Wheel
        TrackingWheel backTrackingWheel;

        double wheelDiameter = 4.0; // inches
        double wheelBase = 11.5; // inches
        double wheelTrack;

    public:
        Chassis(std::vector<std::int8_t>& leftMotorPorts, 
                std::vector<std::int8_t>& rightMotorPorts, 
                TrackingWheel leftTrackingWheel, 
                TrackingWheel rightTrackingWheel, 
                TrackingWheel backTrackingWheel,
                double wheelDiameter,
                double wheelBase,
                double wheelTrack); 
         
            
        

        //get motor encoders
        double getLeftMotorEncoder();
        double getRightMotorEncoder();
        

};