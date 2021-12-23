#include "MotorGroup.h"
#include <iostream>

MotorGroup::MotorGroup(): MotorGroup(1, 1, 1) {}

MotorGroup::MotorGroup(int p, int i, int d): pid(p, i, d), motors(std::vector<pros::Motor>()) {}

void MotorGroup::driveToPos(double target) {
	// motors[0].set_encoder_units(const motor_encoder_units_e_t units);
	// motors[0].set_zero_position(const double position);
	// motors[0].move_relative(const double position, const std::int32_t velocity);
	// motors[0].get_actual_velocity(); //Actual velocity in RPM
	// motors[0].get_position(); //Absolute position in encoder units
	// motors[0].get_raw_position(std::uint32_t *const timestamp); //Get position of motor from any point in time
	// motors[0].get_torque(); //Nm
	// motors[0].set_gearing(const motor_gearset_e_t gearset);

	motors[0].set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
	// motors[0].set_zero_position(target);
	motors[0].set_zero_position(motors[0].get_position());
	// pid.changeConstants(0.05, 0.0015, 0.17);
	pid.changeConstants(0.07, 0.00003, 0.3);
	// pid.setMaxOut(127); //Use this to change the motor speeds
	pid.setTarget(target);
	std::cout << "Target: " << pid.getTarget() << std::endl;
	std::cout << "Current pos: " << motors[0].get_position() << std::endl;
	pid.setEnabled(true);

	/*****Check to see if the encoders for the drives change by the same amount*****/
	// while (!motors[0].get_zero_position_flag()) {
	while (motors[0].get_position() != target) {
		// std::cout << "In loop" << std::endl;
		// std::cout << pid.update(motors.at(0).get_position()) << std::endl;
		setPower(pid.update(motors[0].get_position()));
		pros::delay(20);
	}

	pid.setEnabled(false);
	setPower(0);
	std::cout << "End point: " << motors[0].get_position() << std::endl;
}

void MotorGroup::addMotor(pros::Motor motor) {
	motors.push_back(motor);
}

void MotorGroup::setPower(int pwr) {
	for (std::vector<pros::Motor>::iterator it = motors.begin(); it != motors.end(); it++)
		*it = pwr;
}

void MotorGroup::operator=(int pwr) {
	this->setPower(pwr);
}

void MotorGroup::setDir(bool reverse) {
	for (std::vector<pros::Motor>::iterator it = motors.begin(); it != motors.end(); it++)
		it->set_reversed(reverse);
}

void MotorGroup::reverseDirs() {
	for (std::vector<pros::Motor>::iterator it = motors.begin(); it != motors.end(); it++)
		it->set_reversed(!it->is_reversed());
}

double MotorGroup::getPos() {
	return motors[0].get_position();
}

void MotorGroup::setZeroPos() {
	motors[0].set_zero_position(motors[1].get_position());
}

void MotorGroup::setGearbox(pros::motor_gearset_e_t gearset) {
	for (std::vector<pros::Motor>::iterator it = motors.begin(); it != motors.end(); it++)
		it->set_gearing(gearset);
}

void MotorGroup::setEncoderUnits(pros::motor_encoder_units_e_t units) {
	for (std::vector<pros::Motor>::iterator it = motors.begin(); it != motors.end(); it++)
		it->set_encoder_units(units);
}

double MotorGroup::getVel() {
	return motors[0].get_actual_velocity();
}
