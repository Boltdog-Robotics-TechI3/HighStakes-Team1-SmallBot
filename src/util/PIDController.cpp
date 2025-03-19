#include "main.h"

class PIDController {
public:
    // PID Controller Settings
    // These values' respective functions will be disabled if they are 0
    double kP = 0.0;
    double kI = 0.0;
    double kD = 0.0;
    double smallErrorRange = 0.0;
    double largeErrorRange = 0.0;
    double minOutput = 0.0;
    double maxOutput = 0.0;

    // Other variables
    double setpoint;
    double measurement;
    int currentTime = pros::millis();
    int previousTime = pros::millis();
    double error = 0.0;
    double previousError = 0.0;
    double accumulatedError = 0.0;

    PIDController(double kP, double kI, double kD) {
        this->kP = kP;
        this->kI = kI;
        this->kD = kD;
    }

    PIDController() {
        PIDController(0, 0, 0);
    }

    double reset() {
        accumulatedError = 0.0;
        error = 0.0;
        previousError = 0.0;
    }

    double calculate(double measurement, double setpoint) {
        error = setpoint - measurement;
        int elapsedTime = currentTime - previousTime;

        double output = kP * error +                                  // P term
                        (kI * accumulatedError * elapsedTime) +       // I term
                        ((error - previousError) * kD / elapsedTime); // D term

        previousError = error;
        accumulatedError += error;
        previousTime = currentTime;
        currentTime = pros::millis();

        return output;
    }
};