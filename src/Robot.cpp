#include "Robot.h"

int Robot::selectedAuton = -1;
lv_color_t Robot::colorRed = LV_COLOR_MAKE(255, 0, 0);
lv_color_t Robot::colorBlue = LV_COLOR_MAKE(0, 0, 255);
lv_obj_t *Robot::autonColor = lv_obj_create(lv_scr_act(), nullptr);
lv_style_t Robot::styleSelectedAuton = lv_style_t();

Robot::Robot(): master(pros::Controller(pros::E_CONTROLLER_MASTER)) {
	leftWheels = MotorGroup();
	rightWheels = MotorGroup();
}

void Robot::printAutons() {
	textArea = lv_ta_create(lv_scr_act(), nullptr);
	lv_obj_set_pos(textArea, 300, 300);
	lv_obj_set_size(textArea, 100, 100);

	lv_obj_t *btnBlue = createBtn(lv_scr_act(), 0, 0, 100, 35, BLUE, "Blue Auton");
	lv_obj_t *btnRed = createBtn(lv_scr_act(), 150, 0, 100, 35, RED, "Red Auton");

	lv_obj_align(autonColor, nullptr, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_size(autonColor, 50, 50);
	lv_style_copy(&styleSelectedAuton, &lv_style_plain);
	styleSelectedAuton.body.main_color = LV_COLOR_MAKE(255, 255, 255);
	lv_obj_set_style(autonColor, &styleSelectedAuton);
}

void Robot::driveToPos(double target, double p, double i, double d) {
	//Pass the wheel position to the PID
	//PID gives an output for the speed

	//Need to figure out how to get both running at the same time
	// leftWheels.driveToPos(target);
	// rightWheels.driveToPos(target);

	// motors[0].set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
	// motors[0].set_zero_position(motors[0].get_position());
	leftWheels.setZeroPos();
	rightWheels.setZeroPos();
	// pid.changeConstants(0.05, 0.0015, 0.17);
	leftWheels.pid.changeConstants(p, i, d);
	rightWheels.pid.changeConstants(p, i, d);
	// pid.setMaxOut(127); //Use this to change the motor speeds
	leftWheels.pid.setTarget(target);
	rightWheels.pid.setTarget(target);
	// std::cout << "Target: " << pid.getTarget() << std::endl;
	// std::cout << "Current pos: " << motors[0].get_position() << std::endl;
	leftWheels.pid.setEnabled(true);
	rightWheels.pid.setEnabled(true);

	/*****Check to see if the encoders for the drives change by the same amount*****/
	// while (!motors[0].get_zero_position_flag()) {
	while (leftWheels.getPos() != target && rightWheels.getPos() != target) {
		// std::cout << "In loop" << std::endl;
		// std::cout << pid.update(motors.at(0).get_position()) << std::endl;
		leftWheels.setPower(leftWheels.pid.update(leftWheels.getPos()));
		rightWheels.setPower(rightWheels.pid.update(rightWheels.getPos()));
		pros::delay(20);
	}

	leftWheels.pid.setEnabled(false);
	rightWheels.pid.setEnabled(false);
	setArcadePowers(0, 0);
	// std::cout << "End point: " << motors[0].get_position() << std::endl;
}

void Robot::addText(std::string txt) {
	// lv_ta_add_text(textArea, txt.c_str());
}

lv_obj_t* Robot::createBtn(lv_obj_t * parent, lv_coord_t x, lv_coord_t y,
	lv_coord_t width, lv_coord_t height, AUTON_ID id, const char * title) {
	lv_obj_t *btn = lv_btn_create(parent, nullptr);
	lv_obj_set_pos(btn, x, y);
	lv_obj_set_size(btn, width, height);
	lv_obj_set_free_num(btn, id);
	lv_btn_set_action(btn, LV_BTN_ACTION_CLICK, setAuton);

	lv_obj_t *label = lv_label_create(btn, nullptr);
	lv_label_set_text(label, title);
	lv_obj_align(label, nullptr, LV_ALIGN_IN_TOP_MID, 0, 5);

	return btn;
}

void Robot::changeStyleColor(lv_style_t *style, lv_color_t color) {
	style->body.main_color = color;
	style->body.grad_color = color;
}

lv_res_t Robot::setAuton(lv_obj_t *btn) {
	selectedAuton = lv_obj_get_free_num(btn);

	switch (selectedAuton) {
		case (RED):
			changeStyleColor(&styleSelectedAuton, colorRed);
			break;
		case(BLUE):
			changeStyleColor(&styleSelectedAuton, colorBlue);
			break;
	}

	lv_obj_set_style(autonColor, &styleSelectedAuton);

	return LV_RES_OK;
}
