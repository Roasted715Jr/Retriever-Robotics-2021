#ifndef ROBOT_H
#define ROBOT_H

#include "MotorGroup.h"
#include "pros/apix.h"
#include <string>
#include <iostream>

//This class holds methods and properties that the big bot and
// small bot have in common
class Robot {
	public:
		Robot();
		virtual void startMatchAuton() = 0;
		virtual void startSkillsAuton() = 0;
		virtual void setArcadePowers(int pwr, int turn) = 0;
		virtual void runOpControl() = 0;
		void printAutons();

		void driveToPos(double target, double p, double i, double d);

	protected:
		void addText(std::string txt);

		pros::Controller master;
		MotorGroup leftWheels, rightWheels;
		enum AUTON_ID {
			RED,
			BLUE
		};
		static int selectedAuton;
		lv_obj_t *textArea;

	private:
		lv_obj_t* createBtn(lv_obj_t * parent, lv_coord_t x, lv_coord_t y, lv_coord_t width, lv_coord_t height, AUTON_ID id, const char * title);
		static void changeStyleColor(lv_style_t *style, lv_color_t color);
		static lv_res_t setAuton(lv_obj_t *btn);

		static lv_color_t colorRed, colorBlue;
		static lv_obj_t *autonColor;
		static lv_style_t styleSelectedAuton;
};

#endif
