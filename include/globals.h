#include "main.h"
#define setMinAbs(num, bound) ((num > -(bound) && num < bound) ? ((num >= 0) ? bound : -(bound)) : num)

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

    // Intake 
        extern pros::Motor intakeA;
        extern pros::Motor intakeB;
        
        extern pros::MotorGroup intakeGroup;

    // Lift
        extern okapi::Motor lift;

    // Ladybrown
        extern pros::Motor ladybrownA;
        extern pros::Motor ladybrownB;

        extern pros::MotorGroup ladybrownGroup;

// Pneumatics
extern pros::adi::Pneumatics mogoClamp;
extern pros::adi::Pneumatics mogoClaw;
extern pros::adi::Pneumatics mogoClawArm;

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

// Constants
extern int ladybrownStartingAngle;
extern int ladybrownReadiedAngle;
extern int ladybrownScoringAngle;
extern int ladybrownBaseFeedForward;
extern int ladybrownKP;