#include "BigBot.h"

BigBot::BigBot(): wheelCircumference(WHEEL_DIAMETER * M_PI), pneuNormallyOpen(pros::ADIDigitalOut(PNEUMATIC_NO_PORT)), pneuNormallyClosed(pros::ADIDigitalOut(PNEUMATIC_NC_PORT)) {
	rightWheels.addMotor(pros::Motor(R1_DRIVE_PORT));
	rightWheels.addMotor(pros::Motor(R2_DRIVE_PORT));
	rightWheels.addMotor(pros::Motor(R3_DRIVE_PORT, true));
	rightWheels.addMotor(pros::Motor(R4_DRIVE_PORT));
	rightWheels.addMotor(pros::Motor(R5_DRIVE_PORT, true));
	rightWheels.reverseDirs();

	leftWheels.addMotor(pros::Motor(L1_DRIVE_PORT));
	leftWheels.addMotor(pros::Motor(L2_DRIVE_PORT));
	leftWheels.addMotor(pros::Motor(L3_DRIVE_PORT, true));
	leftWheels.addMotor(pros::Motor(L4_DRIVE_PORT));
	leftWheels.addMotor(pros::Motor(L5_DRIVE_PORT, true));

	initDriveMotors(pros::E_MOTOR_GEARSET_06);
}

void BigBot::startMatchAuton() {
	// setArcadePowers(127, 0);
	// pros::delay(5000);

	// setArcadePowers(0, 0);
	// pros::delay(500);

	// setArcadePowers(-127, 0);
	// pros::delay(5000);
	// setArcadePowers(0, 0);

	driveToPos(720, 0.07, 0.00003, 0.3);
}

void BigBot::startSkillsAuton() {

}

void BigBot::runOpControl() {
	std::cout << "Big bot opcontrol" << std::endl;
	
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
