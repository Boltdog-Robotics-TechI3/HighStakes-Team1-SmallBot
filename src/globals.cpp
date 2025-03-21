#include "main.h"
#include <queue>
#include <string>

// Controllers
pros::Controller driverController(pros::E_CONTROLLER_MASTER);

// Motors
    // Drivetrain
    // okapi::Motor leftMotorA(18, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    // okapi::Motor leftMotorB(19, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    // okapi::Motor leftMotorC(20, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    // okapi::Motor rightMotorA(14, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    // okapi::Motor rightMotorB(12, false, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);
    // okapi::Motor rightMotorC(13, true, okapi::AbstractMotor::gearset::blue, okapi::AbstractMotor::encoderUnits::rotations);

    pros::Motor leftMotorA(18);
    pros::Motor leftMotorB(19);
    pros::Motor leftMotorC(20);
    pros::Motor rightMotorA(14);
    pros::Motor rightMotorB(12);
    pros::Motor rightMotorC(13);

    pros::MotorGroup leftMotorGroup({-18, 19, -20});
    pros::MotorGroup rightMotorGroup({14, 12, -13});

    okapi::MotorGroup BADLeftMotorGroup({-18, 19, -20});
    okapi::MotorGroup BADRightMotorGroup({14, 12, -13});

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

pros::Task printTask(printMessages);
pros::Task intakeTask(intakeUntilColor);
pros::Task intakeJamTask(intakeJamHandler);
pros::Task liftStallTask(liftStallHandler);

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

bool debug = true;

struct PrintMessage {
    int line;
    int col;
    std::string text;
};
std::queue<PrintMessage> printQueue;

/**
* Task that prints messages to the controller screen. 
*/
void printMessages(void* param) {
    pros::Task::notify_take(true, TIMEOUT_MAX);
    driverController.clear();
    while (true) {
        if (!printQueue.empty()) {
            PrintMessage message = printQueue.front();
            driverController.set_text(message.line, message.col, message.text);
            printQueue.pop();
        }
        pros::delay(50);
    }
}

/**
* Sends a message to the print queue to be printed on the controller screen.
*
* @param line the line to print the message on
* @param col the column to print the message on
* @param text the message to print 
*/
void print(int line, int col, std::string text) {
    // If the message is the same as the last message, don't print it
    if (!printQueue.empty() && printQueue.back().text.compare(text) == 0) {
        return;
    }

    // If the queue is too long, pop the oldest message
    if (printQueue.size() > 200) {
        printQueue.pop();
    }
    printQueue.push({line, col, text});
}