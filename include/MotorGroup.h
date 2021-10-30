#ifndef MOTOR_GROUP_H
#define MOTOR_GROUP_H

#include "pros/motors.hpp"
#include <vector>

class MotorGroup {
	public:
		MotorGroup(): motors(std::vector<pros::Motor>()) {}
		void addMotor(pros::Motor motor);		
		void setPower(int pwr);
		void setDir(bool reverse);
		void reverseDirs();

	private:
		std::vector<pros::Motor> motors;
};

#endif
