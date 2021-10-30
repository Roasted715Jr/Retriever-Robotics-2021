#ifndef SMALL_BOT_H
#define SMALL_BOT_H

#include "util/Robot.h"

//This class holds methods and properties unique to the big bot
class SmallBot: public Robot {
	public:
		SmallBot();
		void setArcadePowers(int pwr, int turn);
		void startMatchAuton();
		void startSkillsAuton();
		void runOpControl();

	private:
};

#endif
