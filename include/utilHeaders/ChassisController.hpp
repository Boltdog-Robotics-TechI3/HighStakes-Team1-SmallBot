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
        *@brief Forcefully stop the robot's motors.
        */
        void stop();

        void calculate();

        void update(Pose2D newPose);

        Pose2D getCurrentPosition();

        double getLeftWheelDistance();
        double getRightWheelDistance();
        double getBackWheelDistance();

        // /**
        //  * @brief Move the robot forward a specified distance.
        //  * @param distance The distance to move forward.
        //  */
        // void moveForwardRelative(Distance distance);

        // /**
        //  * @brief Turn the robot to a specified heading.
        //  * @param heading The heading to turn to.
        //  */
        // void turnToHeading(Angle heading);

        // /** Basic Move function (Turn towards the desired position and drive there) */
        // void moveToPoint(Pose2d pose);

};