#ifndef BIG_BOT_H
#define BIG_BOT_H

#include "Robot.h"

#define R1_DRIVE_PORT 6
#define R2_DRIVE_PORT 7
#define R3_DRIVE_PORT 8
#define R4_DRIVE_PORT 9
#define R5_DRIVE_PORT 10
#define L1_DRIVE_PORT 1
#define L2_DRIVE_PORT 2
#define L3_DRIVE_PORT 3
#define L4_DRIVE_PORT 4
#define L5_DRIVE_PORT 5

#define PNEUMATIC_NO_PORT 'A'
#define PNEUMATIC_NC_PORT 'B'

#define WHEEL_DIAMETER 1

//This class holds methods and properties unique to the big bot
class BigBot: public Robot {
	public:
		BigBot();
		void startMatchAuton();
		void startSkillsAuton();
		void runOpControl();

	private:
		pros::ADIDigitalOut pneuNormallyOpen, pneuNormallyClosed;
		const double wheelCircumference;
};

#endif
