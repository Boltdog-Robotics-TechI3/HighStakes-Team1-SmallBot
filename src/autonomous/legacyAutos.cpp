// #include "main.h"
// using namespace okapi;

// /**
//  * THESE AUTOS WERE FROM PRE AUBURN.
//  * THEY ARE NOT TO BE USED.
//  * THEY ARE STORED HERE FOR REFERENCE PURPOSES ONLY
//  */

// /* TASKS */
// // Task Function used for plus side mogo auto (ill figure out how to do parameters later)
// void moveTaskFunction(void* param) {
//     chassis->moveDistance(-4.05_ft);
// }

// // Task Function used for plus side mogo auto (ill figure out how to do parameters later)
// void moveTaskFunctionAgain(void* param) {
//     chassis->moveDistance(4.3_ft);
//     pros::delay(5000);
// }

// // Task Function used for skills auto (ill figure out how to do parameters later)
// void moveTaskFunctionAgain2(void* param) {
//     chassis->moveDistance(1.3_ft);
// }

// /**
//  *  Match Auto with the mogo on the left side that drops it after grabbing it.
//  */
// void matchLeftMogoDropAuto() {
//     // Set speed to max
//     chassis->setMaxVelocity((10.0/4.0)*chassis->getMaxVelocity());
//     chassis->setGains(       
//         {0.001, 0, 0.00004},
//         {0.005, 0, 0.00012},
//         {0.0005, 0, 0.0000}
//     );

//     // Lower acceleration to prevent it from hopping onto the red ring and getting stuck
//     setDriveMotorCurrentLimits(1800);
    
//     // Begin moving towards plus-side mogo 
//     pros::Task* moveTask = new pros::Task(moveTaskFunction);

//     // Set up a timer to clamp the mogo. Once clamped, cancel the movement task to make the robot stop.
//     pros::Task task{[=] {
//             pros::delay(1150);
//             toggleMogoClamp();
//             if (moveTask) {
//                 moveTask->remove(); // Stop the task
//                 delete moveTask;
//             }
//     }};

//     // This delay is necessary as tasks are immediately passed.
//     pros::delay(1200);

//     // Set the max velocity and gains to 40 percent max speed.
//     chassis->setMaxVelocity(0.4*chassis->getMaxVelocity());
//     chassis->setGains(
//         {0.005, 0, 0.00012},
//         {0.005, 0, 0.00012},
//         {0.001, 0, 0.0000}
//     );

//     // Move back and drop off plus side mogo
//     chassis->moveDistance(3.7_ft);
//     chassis->waitUntilSettled();
//     chassis->turnAngle(-90_deg);
//     chassis->waitUntilSettled();
//     toggleMogoClamp();
//     setDriveMotorCurrentLimits(2500);

//     // Go grab alliance side mogo
//     chassis->turnAngle(210_deg);
//     chassis->waitUntilSettled();
//     chassis->moveDistance(-2.1_ft);
//     chassis->waitUntilSettled();
//     toggleMogoClamp();

//     // Move back and turn towards the climb's base
//     chassis->moveDistance(2.1_ft);
//     chassis->waitUntilSettled();
//     chassis->turnAngle(125_deg);
//     chassis->waitUntilSettled();

//     // Move onto the climb base, and while doing so score the preload.
//     moveTask = new pros::Task(moveTaskFunctionAgain); 
//     pros::delay(2000);
//     toggleMogoClamp();
//     pros::delay(100);
//     setLiftSpeed(127);
//     pros::delay(500);
// }

// void matchLeftMogoKeepAuto() {
//     // Set speed to max
//     chassis->setMaxVelocity((10.0/4.0)*chassis->getMaxVelocity());
//     chassis->setGains(       
//         {0.00095, 0, 0.00004},
//         {0.005, 0, 0.00012},
//         {0.000, 0, 0.0000}
//     );

//     // Lower acceleration to prevent it from hopping onto the red ring and getting stuck
//     setDriveMotorCurrentLimits(1000);
    
//     // Begin moving towards plus-side mogo 
//     pros::Task* moveTask = new pros::Task(moveTaskFunction);

//     // Set up a timer to clamp the mogo. Once clamped, cancel the movement task to make the robot stop.
//     pros::Task task{[=] {
//             pros::delay(1225);
//             toggleMogoClamp();
//             if (moveTask) {
//                 moveTask->remove(); // Stop the task
//                 delete moveTask;
//             }
//     }};

//     // This delay is necessary as tasks are immediately passed.
//     pros::delay(1250);

//     // Set the max velocity and gains to 40 percent max speed.
//     chassis->setMaxVelocity(0.4*chassis->getMaxVelocity());
//     chassis->setGains(
//         {0.005, 0, 0.00012},
//         {0.005, 0, 0.00012},
//         {0.001, 0, 0.0000}
//     );

//     // reset Current limits back to where they need to be
//    setDriveMotorCurrentLimits(2000);

//     // Move back and turn towards near ring stack
//     setLiftSpeed(1);
//     chassis->moveDistance(2.7_ft);
//     chassis->waitUntilSettled();
//     chassis->turnAngle(90_deg);
//     chassis->waitUntilSettled();
//     setLiftSpeed(0);

//     // Grab ring in stack
//     pros::Task taskIntake(intakeUntilColor);
//     chassis->moveDistance(1.6_ft);
//     chassis->waitUntilSettled();
//     pros::delay(2000);

//     // Turn around and head for climb
//     chassis->turnAngle(180_deg);
//     chassis->waitUntilSettled();
//     setLiftSpeed(1);
//     chassis->moveDistance(3.5_ft);
//     setLadybrownSpeed(40);
//     pros::delay(3000);
//     setLadybrownSpeed(0);
//     pros::delay(3000);
//     setLiftSpeed(0);
// }
