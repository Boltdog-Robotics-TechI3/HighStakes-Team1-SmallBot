#include "main.h"

extern std::shared_ptr<okapi::ChassisControllerPID> chassis;

extern std::shared_ptr<okapi::ChassisModel> drivetrain;

void drivetrainInitialize();

void drivetrainPeriodic();

void arcadeDrive(bool reverse);

void setDriveMotorCurrentLimits(int mAmps);

void turnToHeading(float heading, int timeout = 10);
//void turnToHeading(double heading, int timeout=10, double maxVelocity=127);

void turnAngle(float angle, int timeout = 10);
//void turnAngle(float angle, int timeout=10, double maxVelocity=127);

void lateralPIDTune();

void angularPIDTune();