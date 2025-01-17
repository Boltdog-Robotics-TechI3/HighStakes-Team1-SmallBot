#include "main.h"

// Controllers
pros::Controller driverController(pros::E_CONTROLLER_MASTER);

// Motors

    // Drivetrain
    okapi::Motor leftMotorA(18, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    okapi::Motor leftMotorB(19, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    okapi::Motor leftMotorC(20, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    okapi::Motor rightMotorA(14, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    okapi::Motor rightMotorB(12, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    okapi::Motor rightMotorC(13, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);

    okapi::MotorGroup leftMotorGroup({-18, 19, -20});
    okapi::MotorGroup rightMotorGroup({14, 12, -13});

    // Lift
    okapi::Motor lift(11, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::rotations);

    // LadyBrown
    // okapi::Motor ladybrownA(5, false, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::rotations);
    // okapi::Motor ladybrownB(6, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::rotations);

    // okapi::MotorGroup ladybrownGroup({5, -6});

    pros::Motor ladybrownA(5);
    pros::Motor ladybrownB(6); 

    // pros::MotorGroup ladybrownGroup ({ladybrownA, ladybrownB});

// Pneumatics
pros::adi::Pneumatics mogoClamp = pros::adi::Pneumatics('A', false);

// Sensors
pros::IMU gyro(6);

pros::Optical opticalSensor(2);

pros::Rotation rotationSensor(1);