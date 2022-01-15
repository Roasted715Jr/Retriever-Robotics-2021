#ifndef MOTOR_GROUP_H
#define MOTOR_GROUP_H

#include "PID.h"
#include "pros/motors.h"
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
	void setGearbox(pros::motor_gearset_e_t gearset);
	void setEncoderUnits(pros::motor_encoder_units_e_t units);
	void setBrakeMode(pros::motor_brake_mode_e_t mode);
	double getVel();

	PID pid;
private:
	std::vector<pros::Motor> motors;
};

#endif
