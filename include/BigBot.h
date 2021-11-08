#ifndef BIG_BOT_H
#define BIG_BOT_H

#include "Robot.h"
#include "pros/adi.hpp"
#include "pros/misc.h"

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

//This class holds methods and properties unique to the big bot
class BigBot: public Robot {
	public:
		BigBot();
		void setArcadePowers(int pwr, int turn);
		void startMatchAuton();
		void startSkillsAuton();
		void runOpControl();

	private:
		pros::ADIDigitalOut pneuNormallyOpen, pneuNormallyClosed;
};

#endif
