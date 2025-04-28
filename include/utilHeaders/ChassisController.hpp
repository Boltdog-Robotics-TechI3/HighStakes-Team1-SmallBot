#pragma once

#include "utilHeaders/Distance.hpp"
#include "utilHeaders/Angle.hpp"
#include "utilHeaders/Drivetrain.hpp"
#include "utilHeaders/OdomSensors.hpp"

class ChassisController{

    private:
        Drivetrain *drivetrain;
        OdomSensors *odomSensors;

        int leftY;
        int rightX;

        Pose2D currentPosition;

    public:

        /**
         */
        ChassisController(Drivetrain &drivetrain, OdomSensors &odomSensors);

        ChassisController(Drivetrain &drivetrain);

        /**
         * @brief Move the robot in arcade mode. The left joystick controls the forward/backward movement, and the right joystick controls the rotation.
         * @param leftY The value of the left joystick (forward/backward movement).
         * @param rightX The value of the right joystick (rotation).
         */
        void arcade(int leftY, int rightX);

        /**
         * @brief Move the robot in tank mode. The left joystick controls the left side motors, and the right joystick controls the right side motors.
         * @param leftY The value of the left joystick (left side motors).
         * @param rightY The value of the right joystick (right side motors).
         */
        void tank(int leftY, int rightY);

        /**
        * @brief Forcefully stop the robot's motors.
        */
        void stop();

        /**
        *  @brief Calculate the robot's current position based on the odometry sensors.
        */
        void calculate();

        /**
         * @brief Set the robot's pose to a new position.
         * @param newPose The new pose to set as a Pose2D.
         */
        void setPose(Pose2D newPose);

        /**
         * @brief Get the robot's current position.
         * @return The current position of the robot as a Pose2D. 
         */
        Pose2D getCurrentPosition();

        /**
         * @brief Get the distance traveled by the left tracking wheel.
         * @return The distance traveled by the left tracking wheel.
         */
        double getLeftWheelDistance();

        /**
         * @brief Get the distance traveled by the right tracking wheel.
         * @return The distance traveled by the right tracking wheel.
         */
        double getRightWheelDistance();

        /**
         * @brief Get the distance traveled by the horizontal tracking wheel.
         * @return The distance traveled by the horizontal tracking wheel.
         */
        double getBackWheelDistance();

        /**
         * @brief Move the robot forward a specified distance.
         * @param distance The distance to move forward.
         */
        void moveForwardRelative(Distance distance);

        /**
         * @brief Turn the robot to a specified heading.
         * @param heading The heading to turn to.
         */
        void turnToHeading(Angle heading);

        /**
         * @brief A simple move to point function that drives the robot
         *   to a specified point in the field by first turning to face the point and then moving forward.
         * @param pose The target pose to move to.
        */
        void moveToPoint(Pose2D pose);

};