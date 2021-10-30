#ifndef MOTOR_GROUP_H
#define MOTOR_GROUP_H

#include "pros/motors.hpp"
#include <vector>

class MotorGroup {
	public:
		MotorGroup(): motors(std::vector<pros::Motor>()) {}
		void addMotor(pros::Motor motor) {
			motors.push_back(motor);
		}
		
		void setPower(int pwr) {
			for (std::vector<pros::Motor>::iterator it = motors.begin(); it != motors.end(); it++)
				*it = pwr;
		}

		void setDir(bool reverse) {
			for (std::vector<pros::Motor>::iterator it = motors.begin(); it != motors.end(); it++)
				it->set_reversed(reverse);
		}
		
		void reverseDir() {
			for (std::vector<pros::Motor>::iterator it = motors.begin(); it != motors.end(); it++)
				it->set_reversed(!it->is_reversed());
		}

	private:
		std::vector<pros::Motor> motors;
};

#endif
