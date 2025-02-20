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

    // Intake 
    pros::Motor intakeA(15);
    pros::Motor intakeB(16); 

    pros::MotorGroup intakeGroup({15, -16});
    
    // Lift
    okapi::Motor lift(11, true, okapi::AbstractMotor::gearset::green, okapi::AbstractMotor::encoderUnits::rotations);

    // LadyBrown
    pros::Motor ladybrownA(5);
    pros::Motor ladybrownB(6); 

    pros::MotorGroup ladybrownGroup({5, -6});

// Pneumatics
pros::adi::Pneumatics mogoClamp = pros::adi::Pneumatics('H', false);
pros::adi::Pneumatics mogoClaw = pros::adi::Pneumatics('F', false);
pros::adi::Pneumatics mogoClawArm = pros::adi::Pneumatics('G', false);

// Sensors
pros::IMU gyro(7);

pros::Optical opticalSensor(17);

pros::Rotation rotationSensor(10);

// Comp Specifications
bool skills = false;
bool match = true;
bool elim = false;
bool qual = true;
bool redAlliance = true;
bool blueAlliance = false;
int autoSelection = 0; 

// Constants
int ladybrownStartingAngle = -15;
int ladybrownReadiedAngle = 0;
int ladybrownScoringAngle = 130;
int ladybrownBaseFeedForward = 12;
double ladybrownKP = 1;