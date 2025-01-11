#include <main.h>

// Controllers
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Motors

    // Drivetrain
    okapi::Motor leftMotorA(11, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    okapi::Motor leftMotorB(12, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    okapi::Motor leftMotorC(13, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    okapi::Motor rightMotorA(1, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    okapi::Motor rightMotorB(2, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    okapi::Motor rightMotorC(3, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);

    okapi::MotorGroup leftMotorGroup({11, 12, 13});
    okapi::MotorGroup rightMotorGroup({1, 2, 3});

    // Lift
    okapi::Motor lift(10, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::rotations);

// Pneumatics
pros::adi::Pneumatics clamp = pros::adi::Pneumatics('H', false);

// Sensors
pros::IMU gyro(6);

pros::Optical optical_sensor(1);
