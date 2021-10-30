#include "MotorGroup.h"

void MotorGroup::addMotor(pros::Motor motor) {
	motors.push_back(motor);
}

void MotorGroup::setPower(int pwr) {
	for (std::vector<pros::Motor>::iterator it = motors.begin(); it != motors.end(); it++)
		*it = pwr;
}

void MotorGroup::setDir(bool reverse) {
	for (std::vector<pros::Motor>::iterator it = motors.begin(); it != motors.end(); it++)
		it->set_reversed(reverse);
}

void MotorGroup::reverseDirs() {
	for (std::vector<pros::Motor>::iterator it = motors.begin(); it != motors.end(); it++)
		it->set_reversed(!it->is_reversed());
}