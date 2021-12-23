#ifndef ODOM_H
#define ODOM_H

#include "RobotState.h"
#include "Robot.h"

#define DEGREES_PER_RADIAN 180/M_PI

class Odom{
public:
	double gyro_calibrameter;

	Odom(Robot& robot);
	double getLVelocity();
	double getRVelocity();
	double getLEncoder();
	double getREncoder();
	RobotState getCurrentState();
	// tare x, y position with the given args
	void tareY(double y);
	void tareX(double x);
	void tareXY(double x = 0, double y = 0);
	void tareTheta(double theta = 90);

	void updateCurrentState();
	void rotateAxes(double &xPrime, double &yPrime, const double &x, const double &y, const double &theta);

private:
	friend void autonMotorControlLoop(void*);
	friend class ZController;
	friend class HoloController;

	RobotState currentState;
	RobotState oldState;
	bool enabled;

	double oldLEncoder;
	double oldREncoder;

	double gyro_last = 90;
	clock_t time_last = 0;

	Robot& robot;
};

#endif
