#include "main.h"

// Controller Setup
extern pros::Controller driverController;

// Motor Initialization
    // Drivetrain
        extern pros::Motor leftMotorA;
        extern pros::Motor leftMotorB;
        extern pros::Motor leftMotorC;
        extern pros::Motor rightMotorA;
        extern pros::Motor rightMotorB;
        extern pros::Motor rightMotorC;

        extern okapi::MotorGroup BADLeftMotorGroup;
        extern okapi::MotorGroup BADRightMotorGroup;

        extern pros::MotorGroup leftMotorGroup;
        extern pros::MotorGroup rightMotorGroup;

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
extern double ladybrownKP;

extern bool debug;

extern pros::Task printTask;
extern pros::Task intakeTask;
extern pros::Task intakeJamTask;
extern pros::Task liftStallTask;

void printMessages(void* param);
void print(int line, int col, std::string text);