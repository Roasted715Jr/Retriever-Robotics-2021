#include "SmallBot.h"
#include "pros/misc.h"
#include "pros/motors.h"

SmallBot::SmallBot() {
	rightWheels.addMotor(pros::Motor(R1_DRIVE_PORT));
	rightWheels.addMotor(pros::Motor(R2_DRIVE_PORT, true));
	rightWheels.addMotor(pros::Motor(R3_DRIVE_PORT));
	rightWheels.reverseDirs();

	leftWheels.addMotor(pros::Motor(L1_DRIVE_PORT));
	leftWheels.addMotor(pros::Motor(L2_DRIVE_PORT, true));
	leftWheels.addMotor(pros::Motor(L3_DRIVE_PORT));

	liftMotors.addMotor(pros::Motor(RIGHT_LIFT_PORT, true));
	liftMotors.addMotor(pros::Motor(LEFT_LIFT_PORT));

	initDriveMotors();

	//Set the gearboxes
	leftWheels.setGearbox(pros::E_MOTOR_GEARSET_18);
	rightWheels.setGearbox(pros::E_MOTOR_GEARSET_18);
	liftMotors.setGearbox(pros::E_MOTOR_GEARSET_36);
}

void SmallBot::startMatchAuton() {
	driveToPos(1440, 0.07, 0.00003, 0.4);
}

void SmallBot::startSkillsAuton() {

}

void SmallBot::runOpControl() {
	std::cout << "Small bot opcontrol" << std::endl;

	while (true) {
		int pwr = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		setArcadePowers(pwr, turn);

		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A))
			liftMotors.setPower(32);
		else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B))
			liftMotors.setPower(-32);
		else
			liftMotors.setPower(0);

		pros::delay(20);
	}
}

void SmallBot::setArcadePowers(int pwr, int turn) {
	leftWheels = (pwr + turn) * 3 / 4;
	rightWheels = (pwr - turn) * 3 / 4;
}
