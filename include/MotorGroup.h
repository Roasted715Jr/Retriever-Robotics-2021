#ifndef MOTOR_GROUP_H
#define MOTOR_GROUP_H

#include "PID.h"
#include "pros/motors.hpp"
#include "pros/apix.h"
#include <vector>

class MotorGroup {
	public:
		MotorGroup();
		MotorGroup(int p, int i, int d);
		void addMotor(pros::Motor motor);		
		void setPower(int pwr);
		void operator=(int voltage);
		void setDir(bool reverse);
		void reverseDirs();
		void driveToPos(double target);
		double getPos();
		void setZeroPos();

		PID pid;
	private:
		std::vector<pros::Motor> motors;
};

#endif
