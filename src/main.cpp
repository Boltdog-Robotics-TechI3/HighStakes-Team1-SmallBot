#include "main.h"
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	initializeScreen();

	// Call the subsystems' initialize functions
	drivetrainInitialize();
	liftInitialize();
	clamperInitialize();
	ladybrownInitialize();

	// Initialize the gyro
	gyro.reset(true);
	while (gyro.is_calibrating());
	gyro.set_data_rate(5);

	debug = false;

	// Initialize Tasks
	intakeTask.suspend();
	intakeTask.notify();
	/*if (!pros::competition::is_connected()) {
		intakeJamTask.notify();
		liftStallTask.notify();
		printTask.notify();
	} else {
		printTask.suspend();
	}*/
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	/*chassis->stop();
	drivetrain->stop();
	lift.moveVelocity(0);
	ladybrownGroup.brake();
	intakeGroup.brake();*/
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	// Disable debug mode if connected to the competition switch
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	skillsAuto();
	/*switch (autoSelection) {
		case 0:
			allianceMogoRedAuto();
			break;
		case 1:
			allianceMogoBlueAuto();
			break;
		case 2: 
			goalRushNoWallAuto();
			break;
		case 3:
			goalRushWallStakeAuto();
			break;
		case 4:
			skillsAuto();
			break;
		case 5:
			testAuto();
			break;
		case 6:
			// Do Nothing :)
			break;
	}*/
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	while (true) {
		// Run each subsystem's periodic function
		clamperPeriodic();
		liftPeriodic();
		ladybrownPeriodic();
		drivetrainPeriodic();

		if (driverController.get_digital(DIGITAL_L2) && driverController.get_digital(DIGITAL_Y)) {
			scoreOnRedStake();
		}

		// Debugging code
		/*if (debug) {
			if (driverController.get_digital_new_press(DIGITAL_Y)) {
				skillsAuto();
			}
		}*/

		// Run for 20 ms then update
		pros::delay(20);  
	}
}

