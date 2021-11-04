#ifndef BIG_BOT_H
#define BIG_BOT_H

#include "Robot.h"
#include "pros/adi.hpp"
#include "pros/misc.h"

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
