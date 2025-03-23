// #include "main.h"
// using namespace okapi;

// void allianceMogoBlueAuto() {
//     // Limit Speeds for accuracy
//     chassis->setMaxVelocity(0.7*chassis->getMaxVelocity());
//     setDriveMotorCurrentLimits(1300);
//     gyro.set_heading(225);

//     // Grab Alliance Mogo
//     setLadybrownPosition(300, 50);
//     turnToHeading(268);
//     chassis->moveDistance(-5.5_ft);
//     setMogoClamp(true);

//     // Score Preload
//     setLiftSpeed(1);
//     setIntakeSpeed(1);

//     // Intake ring, readying it in the ladybrown
//     turnToHeading(225);
//     setLadybrownPosition(140, 50);
//     chassis->moveDistance(2_ft);

//     // Back up and move to align with alliance stake
//     chassis->moveDistance(-2_ft);
//     setIntakeSpeed(0);
//     setLiftSpeed(0);
//     turnToHeading(270);
//     chassis->moveDistance(2.2_ft);
//     turnToHeading(180);
//     chassis->moveDistance(1_ft);

//     // Score ring on allinace stake
//     setLadybrownPosition(999, 100);
//     pros::delay(1000);

//     // Back off from allinace stake 
//     chassis->moveDistance(-1_ft);
//     chassis->setMaxVelocity(3*chassis->getMaxVelocity());
//     chassis->setGains(       
//         {0.0015, 0, 0.00004},
//         {3.0, 0, 0.00},
//         {0.0005, 0, 0.0000}
//     );
//     setLadybrownPosition(0, 80);

//     // Drive to and intake ring near left corner
//     turnToHeading(270);
//     setLiftSpeed(1);
//     setIntakeSpeed(1);
//     chassis->moveDistance(7.1_ft);

//     // Drop mogo off at left corner
//     turnToHeading(45);
//     setMogoClamp(false);
//     chassis->moveDistanceAsync(-3_ft);
//     pros::delay(1500);
//     setIntakeSpeed(0);
//     setLiftSpeed(0);
//     pros::delay(500);
//     chassis->moveDistance(6_ft);
//     turnToHeading(225);


//     // Drive to ladder and extend ladybrown to contact it
//     // chassis->moveDistance(1_ft);
//     // chassis->moveDistance(6.7_ft);
//     // setLadybrownPosition(999, 100);
//     // pros::delay(2000);
//     // ladybrownGroup.move(0);
//     // pros::delay(1000);
// }    