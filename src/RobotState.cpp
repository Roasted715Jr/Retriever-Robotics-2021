// RobotState class with all the state info you could want
#include "RobotState.h"

RobotState::RobotState(){
	reset();
}

void RobotState::reset(){
	t = 0;
	x = 0;
	y = 0;
	theta = 0;
	vel = 0;
	accel = 0;
}
