#include "main.h"
using namespace okapi;

extern std::shared_ptr<okapi::ChassisControllerPID> chassis;

extern std::shared_ptr<okapi::ChassisModel> drivetrain;
struct PID {
    double kP;
    double kI;
    double kD;
    double smallErrorRange;
    double smallErrorTimeout;
    double largeErrorRange;
    double largeErrorTimeout;
    double minVelocity;
};

enum class TurnBehavior {
    DEFAULT,
    LEFT,
    RIGHT
};

void drivetrainInitialize();

void drivetrainPeriodic();

void arcadeDrive(bool reverse);

void setDriveMotorCurrentLimits(int mAmps);

void turnToHeading(double heading, double maxVelocity=1.0, int timeout=5000, enum TurnBehavior behavior=TurnBehavior::DEFAULT);

void turnAngle(double angle, double maxVelocity=1.0, int timeout=5000);

void moveDistanceWithTimeout(QLength itarget, int timeout);