#include "main.h"

void drivetrainInitialize();

void drivetrainPeriodic();

void arcadeDrive(bool reverse);

void setDriveMotorCurrentLimits(int mAmps);

void turnAngle(float angle, int timeout = 10);

void testAuto();

void matchLeftMogoDropAuto();

void matchLeftMogoKeepAuto();

void skillsAuto();

void lateralPIDTune();

void angularPIDTune();