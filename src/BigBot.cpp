#include "BigBot.h"
#include "pros/misc.h"

#define R1_DRIVE_PORT 1
#define R2_DRIVE_PORT 2
#define R3_DRIVE_PORT 3
#define R4_DRIVE_PORT 4
#define L1_DRIVE_PORT 5
#define L2_DRIVE_PORT 6
#define L3_DRIVE_PORT 7
#define L4_DRIVE_PORT 8

BigBot::BigBot() {
	rightWheels.addMotor(pros::Motor(R1_DRIVE_PORT));
	rightWheels.addMotor(pros::Motor(R2_DRIVE_PORT));
	rightWheels.addMotor(pros::Motor(R3_DRIVE_PORT, true));
	rightWheels.addMotor(pros::Motor(R4_DRIVE_PORT));
	rightWheels.reverseDirs();

	leftWheels.addMotor(pros::Motor(L1_DRIVE_PORT));
	leftWheels.addMotor(pros::Motor(L2_DRIVE_PORT, true));
	leftWheels.addMotor(pros::Motor(L3_DRIVE_PORT));
	leftWheels.addMotor(pros::Motor(L4_DRIVE_PORT));
}

void BigBot::startMatchAuton() {

}

void BigBot::startSkillsAuton() {

}

void BigBot::runOpControl() {
	while (true) {
		int pwr = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		setArcadePowers(pwr, turn);

		pros::delay(20);
	}
}

void BigBot::setArcadePowers(int pwr, int turn) {
	leftWheels.setPower((pwr + turn) / 2);
	rightWheels.setPower((pwr - turn) / 2);
}
