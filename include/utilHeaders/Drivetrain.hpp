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

        double getLeftIME();
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

        double getGearRatio();
        void setGearRatio(double gearRatio);

        /** Gets the diameter of the wheels in inches
        * @return diameter in inches
        */
        double getWheelDiameter();
        /** Sets the diameter of the wheels in inches
        * @param wheelDiameter diameter in inches
        */
        void setWheelDiameter(double wheelDiameter);
        
        double getWheelBase();
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