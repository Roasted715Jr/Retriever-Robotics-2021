#include "Robot.h"
#include "pros/misc.h"

int Robot::selectedAuton = -1;
lv_color_t Robot::colorRed = LV_COLOR_MAKE(255, 0, 0);
lv_color_t Robot::colorBlue = LV_COLOR_MAKE(0, 0, 255);
lv_obj_t *Robot::autonColor = lv_obj_create(lv_scr_act(), nullptr);
lv_style_t Robot::styleSelectedAuton = lv_style_t();

Robot::Robot(): leftWheels(MotorGroup()), rightWheels(MotorGroup()), master(pros::E_CONTROLLER_MASTER) {}

void Robot::printAutons() {
	lv_obj_t *btnBlue = createBtn(lv_scr_act(), 0, 0, 100, 35, BLUE, "Blue Auton");
	lv_obj_t *btnRed = createBtn(lv_scr_act(), 150, 0, 100, 35, RED, "Red Auton");

	lv_obj_align(autonColor, nullptr, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_size(autonColor, 50, 50);
	lv_style_copy(&styleSelectedAuton, &lv_style_plain);
	styleSelectedAuton.body.main_color = LV_COLOR_MAKE(255, 255, 255);
	lv_obj_set_style(autonColor, &styleSelectedAuton);
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
