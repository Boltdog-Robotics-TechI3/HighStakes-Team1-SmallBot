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

    // Ladybrown
    //     extern okapi::Motor ladybrownA;
    //     extern okapi::Motor ladybrownB;

    //     extern okapi::MotorGroup ladybrownGroup;
        
        extern pros::Motor ladybrownA;
        extern pros::Motor ladybrownB;

        extern pros::MotorGroup ladybrownGroup;

// Pneumatics
extern pros::adi::Pneumatics mogoClamp;

// Sensor Initialization
extern pros::IMU gyro;

extern pros::Optical opticalSensor;

extern pros::Rotation rotationSensor;

// Comp Specifications
extern bool skills;
extern bool elim;
extern bool qual;
extern bool redAlliance;
extern bool blueAlliance;
extern bool match;
extern int autoSelection;