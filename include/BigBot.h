#ifndef BIG_BOT_H
#define BIG_BOT_H

#include "util/Robot.h"

//This class holds methods and properties unique to the big bot
class BigBot: public Robot {
	public:
		BigBot();
		void setArcadePowers(int pwr, int turn);
		void startMatchAuton();
		void startSkillsAuton();
		void runOpControl();

	private:
};

#endif
