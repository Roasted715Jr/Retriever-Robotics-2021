#include "SmallBot.h"

SmallBot::SmallBot() {
	rightWheels.addMotor(pros::Motor(R1_DRIVE_PORT));
	rightWheels.addMotor(pros::Motor(R2_DRIVE_PORT, true));
	rightWheels.addMotor(pros::Motor(R3_DRIVE_PORT));
	rightWheels.reverseDirs();

	leftWheels.addMotor(pros::Motor(L1_DRIVE_PORT));
	leftWheels.addMotor(pros::Motor(L2_DRIVE_PORT, true));
	leftWheels.addMotor(pros::Motor(L3_DRIVE_PORT));
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

		pros::delay(20);
	}
}

void SmallBot::setArcadePowers(int pwr, int turn) {
	leftWheels = (pwr + turn) * 3 / 4;
	rightWheels = (pwr - turn) * 3 / 4;
}
