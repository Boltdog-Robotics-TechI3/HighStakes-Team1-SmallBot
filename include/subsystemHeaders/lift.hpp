#include "main.h"

void liftInitialize();

void liftPeriodic();

void setLiftSpeed(double speed);

void setIntakeSpeed(double speed);

bool detectsBadColor();

void eject();

void colorDetectionTask(void* param);

void intakeUntilColor(void* param);

void intakeJamHandler(void* param);

void liftStallHandler(void* param);