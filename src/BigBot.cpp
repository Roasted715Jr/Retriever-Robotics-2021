#include "BigBot.h"
#include "pros/adi.hpp"

#define R1_DRIVE_PORT 1
#define R2_DRIVE_PORT 2
#define R3_DRIVE_PORT 3
#define R4_DRIVE_PORT 4
#define L1_DRIVE_PORT 5
#define L2_DRIVE_PORT 6
#define L3_DRIVE_PORT 7
#define L4_DRIVE_PORT 8

#define PNEUMATIC_NO_PORT 'A'
#define PNEUMATIC_NC_PORT 'B'

BigBot::BigBot(): pneuNormallyOpen(pros::ADIDigitalOut(PNEUMATIC_NO_PORT)), pneuNormallyClosed(pros::ADIDigitalOut(PNEUMATIC_NC_PORT)) {
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
	setArcadePowers(127, 0);
	pros::delay(5000);

	setArcadePowers(0, 0);
	pros::delay(500);

	setArcadePowers(-127, 0);
	pros::delay(5000);
	setArcadePowers(0, 0);
}

void BigBot::startSkillsAuton() {

}

void BigBot::runOpControl() {
	bool pneumaticState = true;

	// addText("Hello there loser");
	// lv_ta_add_text(textArea, "Hello");
	// lv_ta_add_char(textArea, 'A');

	while (true) {
		int pwr = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
		int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		setArcadePowers(pwr, turn);

		if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A))
			pneumaticState = !pneumaticState;
		
		pneuNormallyOpen.set_value(pneumaticState);
		pneuNormallyClosed.set_value(!pneumaticState);

		pros::delay(20);
	}
}

void BigBot::setArcadePowers(int pwr, int turn) {
	leftWheels = (pwr + turn) / 2;
	rightWheels = (pwr + turn) / 2;
}
