#pragma once
#include "pros/motor_group.hpp"

class Drivetrain {
    private:
        pros::MotorGroup *leftMotorGroup;
        pros::MotorGroup *rightMotorGroup;
        double wheelDiameter;
        double wheelTrack;
        double wheelBase;
        double gearRatio;

    public:
        Drivetrain(pros::MotorGroup &leftMotors, pros::MotorGroup &rightMotors, double wheelDiameter, double wheelTrack, double gearRatio);

        Drivetrain();

        /**
        * @brief Resets the motor encoders to 0
        * 
        * This function sets the zero position of all motors in the left and right motor groups to 0.
        */
        void reset();

        /**Retuns the current left motor encoder values */
        double getLeftIME();

        /**Retuns the current right motor encoder values */
        double getRightIME();

        /** Returns the current brake mode of the drivetrain */
        pros::v5::MotorBrake getBrakeMode();

        /** Returns the current limit set on the motors
        * @return current limit in mA
        */
        int getCurrentLimit();

        /** Returns the current speed of the left motor group
        * @return Speed of motors in RPM
        */
        int getLeftSideSpeed();

        /** Returns the current speed of the right motor group
        * @return Speed of motors in RPM
        */
        int getRightSideSpeed();

        /** Sets the brake mode of the drivetrain */
        void setBrakeMode(pros::motor_brake_mode_e_t mode);

        /** Sets the current limit of the motors of the drivetrain
        * @param limit limit im mA
        */
        void setCurrentLimits(int limit);
        
        /** Sets the left motors to move at the provided speed
        * @param leftSpeed motor voltage [-127, 127]
        */
        void setLeftSideSpeed(double leftSpeed);

        /** Sets the right motors to move at the provided speed
        * @param leftSpeed motor voltage [-127, 127]
        */
        void setRightSideSpeed(double rightSpeed);

        /** Gets the gear ratio (unitless) */
        double getGearRatio();

        /** Sets the gear ratio (unitless) */
        void setGearRatio(double gearRatio);

        /** Gets the diameter of the wheels in inches
        * @return diameter in inches
        */
        double getWheelDiameter();

        /** Sets the diameter of the wheels in inches
        * @param wheelDiameter diameter in inches
        */
        void setWheelDiameter(double wheelDiameter);
        
        /** Gets the distance between the front and back wheels
        * @return wheel base in inches
        */
        double getWheelBase();

        /** Sets the distance between the front and back wheels
        * @param wheelBase wheel base in inches
        */
        void setWheelBase(double wheelBase);

        /** Gets the distance between the left and right wheels
        * @return wheel track in inches
        */
        double getWheelTrack();

        /** Gets the distance between the left and right wheels
        * @param wheelTrack wheel track in inches
        */
        void setWheelTrack(double wheelTrack);
};