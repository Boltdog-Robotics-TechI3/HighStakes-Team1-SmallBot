#include "main.h"

pros::MotorGroup leftMotors({-7, -8, 9, 10});
pros::MotorGroup rightMotors({-1, -2, 3, 4});
double wheelDiameter = 3.25;
double trackWidth = 10.875;
double gearRatio = 1.0; // 1:1

pros::IMU imu(11); // IMU on port 20

pros::Rotation leftRotSensor(18);
pros::Rotation backRotSensor(19);

TrackingWheel backWheel(backRotSensor, Pose2D(), 2.125); // Back wheel on port 19
TrackingWheel leftWheel(leftRotSensor, Pose2D(), 2.125); // Left wheel on ports 18

Drivetrain drivetrain = Drivetrain(leftMotors, rightMotors, wheelDiameter, trackWidth, gearRatio);
OdomSensors odometry = OdomSensors(&leftWheel, NULL, &backWheel, &imu); // OdomSensors with left and back wheels

ChassisController chassisController = ChassisController(drivetrain, odometry);

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::delay(100);
	chassisController.reset(); // Reset the chassis controller

	initializeScreen();
	drivetrain.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

	// Call the subsystems' initialize functions
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	
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
	// switch (autoSelection) {
	// 	default:
	// 		// Do Nothing :)
	// 		break;
	// }
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
		driverController.clear();
		while (true) {
			// Run for 20 ms then update
			chassisController.arcade(driverController.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), 
									driverController.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));

			Pose2D pos = chassisController.getCurrentPosition();

			driverController.set_text(1,0, pos.asString());
			// driverController.set_text(1, 0, "deg: " + std::to_string(odometry.getCurrentHeading().asDeg()));
			// driverController.set_text(2, 0, "vert: " + std::to_string(odometry.getLeftTrackingDistance()));
			// driverController.set_text(3, 0, "horz: " + std::to_string(odometry.getBackTrackingDistance()));
		
			pros::delay(20);  
	}
}

