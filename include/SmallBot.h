#ifndef SMALL_BOT_H
#define SMALL_BOT_H

#include "Robot.h"

#define R1_DRIVE_PORT 1
#define R2_DRIVE_PORT 2
#define R3_DRIVE_PORT 3
#define L1_DRIVE_PORT 4
#define L2_DRIVE_PORT 5
#define L3_DRIVE_PORT 6
#define RIGHT_LIFT_PORT 7
#define LEFT_LIFT_PORT 8

//This class holds methods and properties unique to the big bot
class SmallBot: public Robot {
	public:
		SmallBot();
		void setArcadePowers(int pwr, int turn);
		void startMatchAuton();
		void startSkillsAuton();
		void runOpControl();

	private:
		MotorGroup liftMotors;
};

#endif
