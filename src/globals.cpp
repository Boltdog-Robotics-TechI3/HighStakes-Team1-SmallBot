#include "main.h"

// Controllers
pros::Controller driverController(pros::E_CONTROLLER_MASTER);

// Motors

    // Drivetrain
    okapi::Motor leftMotorA(9, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    okapi::Motor leftMotorB(10, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    okapi::Motor leftMotorC(20, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    okapi::Motor rightMotorA(11, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    okapi::Motor rightMotorB(12, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    okapi::Motor rightMotorC(13, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);

    okapi::MotorGroup leftMotorGroup({9, -10, -20});
    okapi::MotorGroup rightMotorGroup({11, 12, -13});

    // Lift
    okapi::Motor lift(3, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::rotations);

// Pneumatics
pros::adi::Pneumatics clamp = pros::adi::Pneumatics('H', false);

// Sensors
pros::IMU gyro(6);

pros::Optical optical_sensor(1);
