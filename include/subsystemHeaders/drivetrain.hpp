#include "main.h"
using namespace okapi;

extern std::shared_ptr<okapi::ChassisControllerPID> chassis;

extern std::shared_ptr<okapi::ChassisModel> drivetrain;

void drivetrainInitialize();

void drivetrainPeriodic();

void arcadeDrive(bool reverse);

void setDriveMotorCurrentLimits(int mAmps);

void turnToHeading(double heading, double maxVelocity=1.0, int timeout=5);

void turnAngle(double angle, double maxVelocity=1.0, int timeout=5);

void moveDistanceWithTimeout(QLength itarget, int timeout);

void lateralPIDTune();

void angularPIDTune();