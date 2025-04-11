#include "main.h"

// Controller Setup
extern pros::Controller driverController;

// Comp Specifications

extern bool debug;

extern pros::Task printTask;
extern pros::Task intakeTask;
extern pros::Task intakeJamTask;
extern pros::Task liftStallTask;

void printMessages(void* param);
void print(int line, int col, std::string text);