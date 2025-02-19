#include "main.h"

extern std::shared_ptr<okapi::ChassisControllerPID> chassis;

extern std::shared_ptr<okapi::ChassisModel> drivetrain;

void drivetrainInitialize();

void drivetrainPeriodic();

void arcadeDrive(bool reverse);

void setDriveMotorCurrentLimits(int mAmps);

void turnAngle(float angle, int timeout = 10);

void testAuto();

void matchLeftMogoDropAuto();

void matchLeftMogoKeepAuto();

void lateralPIDTune();

void angularPIDTune();