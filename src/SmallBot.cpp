#include "SmallBot.h"

#define R1_DRIVE_PORT 1
#define R2_DRIVE_PORT 2
#define L1_DRIVE_PORT 3
#define L2_DRIVE_PORT 4

SmallBot::SmallBot() {
	rightWheels.addMotor(pros::Motor(R1_DRIVE_PORT));
	rightWheels.addMotor(pros::Motor(R2_DRIVE_PORT));
	rightWheels.reverseDirs();

	leftWheels.addMotor(pros::Motor(L1_DRIVE_PORT));
	leftWheels.addMotor(pros::Motor(L2_DRIVE_PORT, true));
}

void SmallBot::startMatchAuton() {

}

void SmallBot::startSkillsAuton() {

}

void SmallBot::runOpControl() {
	while (true) {
		int pwr = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		setArcadePowers(pwr, turn);

		pros::delay(20);
	}
}

void SmallBot::setArcadePowers(int pwr, int turn) {
	leftWheels.setPower((pwr + turn) / 2);
	rightWheels.setPower((pwr - turn) / 2);
}
