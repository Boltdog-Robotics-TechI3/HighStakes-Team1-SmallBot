#include "main.h"

// Controller Setup
extern pros::Controller driverController;

// Motor Initialization
    // Drivetrain
        extern okapi::Motor leftMotorA;
        extern okapi::Motor leftMotorB;
        extern okapi::Motor leftMotorC;
        extern okapi::Motor rightMotorA;
        extern okapi::Motor rightMotorB;
        extern okapi::Motor rightMotorC;

        extern okapi::MotorGroup leftMotorGroup;
        extern okapi::MotorGroup rightMotorGroup;

    // Lift
        extern okapi::Motor lift;

// Pneumatics
extern pros::adi::Pneumatics clamp;

// Sensor Initialization
extern pros::IMU gyro;

extern pros::Optical optical_sensor;