#pragma once

#include "utilHeaders/TrackingWheel.hpp"
#include "utilHeaders/Pose2D.hpp"
#include "api.h"

/**
    * @brief Class for handling odometry sensors including tracking wheels and IMU
    * 
    * This class provides methods to read distances from tracking wheels, get the current heading from the IMU,
    * and manage the offsets of the tracking wheels.
    * 
    * @note The class assumes that the tracking wheels are mounted in a specific configuration on the robot.
    *       The left and right tracking wheels are vertical tracking wheels.
    *       The back tracking wheel is a horizontal tracking wheel.
*/
class OdomSensors {
    private:
        TrackingWheel *leftWheel;
        TrackingWheel *rightWheel;
        TrackingWheel *backWheel;
        pros::IMU *imu;

        double leftWheelOffset; // The horizontal distance of the left wheel from the center of the bot (in inches)
        double rightWheelOffset; // The horizontal distance of the right wheel from the center of the bot (in inches)
        double backWheelOffset; // The vertical distance of the back wheel from the center of the bot (in inches)

    public:
        /** 
         * @brief Constructor for OdomSensors class with all tracking wheels and gyro
         * @param leftWheel Pointer to the left tracking wheel object
         * @param rightWheel Pointer to the right tracking wheel object
         * @param backWheel Pointer to the back tracking wheel object
         * @param imu Pointer to the IMU object
        */
        OdomSensors(TrackingWheel *leftWheel, TrackingWheel *rightWheel, TrackingWheel *backWheel, pros::IMU *imu);

        /** 
         * @brief Constructor for OdomSensors class with all tracking wheels
         * @param leftWheel Pointer to the left tracking wheel object
         * @param rightWheel Pointer to the right tracking wheel object
         * @param backWheel Pointer to the back tracking wheel object
        */
        OdomSensors(TrackingWheel *leftWheel, TrackingWheel *rightWheel, TrackingWheel *backWheel);

        /** 
         * @brief Constructor for OdomSensors class with the gyro
         * @param imu Pointer to the IMU object
        */
        OdomSensors(pros::IMU *imu);

        /** 
         * @brief Constructor for OdomSensors class with no sensors
        */
        OdomSensors();

        double getLeftTrackingDistance();

        double getRightTrackingDistance();

        double getBackTrackingDistance();
        
        void updatePreviousTrackingDistances();
      
        double getPreviousLeftDistance();
      
        double getPreviousRightDistance();
      
        double getPreviousBackDistance();

        double getLeftWheelOffset();

        double getRightWheelOffset();

        double getBackWheelOffset();

        Angle getCurrentHeading();

        void addToTotalChanges(double leftChange, double backChange);

        
        
};