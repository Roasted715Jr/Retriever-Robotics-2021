
#ifndef _PID_H_
#define _PID_H_

//PID class
#include <string>
#include <time.h>
#include <math.h>

class Pid{
public:
	// tunable constants
	double Kp;
	double Ki;
	double Kd;
	// 0 means no limit
	double iLimit;
	// 0 means no limit
	double maxOut;
	// 0 means maxOut first, then infinite active zone if maxOut is 0
	double IactiveZone;
	double integrator = 0;
	bool integrating = false;

	Pid(double p, double i, double d);
	Pid(double p, double i, double d, double iLimit_, double maxOut_ = 0, std::string name = "");
	Pid(double p, double i, double d, double iLimit_, double IactiveZone_, double maxOut_ = 0, std::string name = "");
	void setTarget(double target);
	double getTarget();
	void disable();
	void enable();
	bool getEnabled();
	void setMaxOut(double maxOut_);
	double update(double input);
	void idle(double input);
	double getError();
	// used for large setpoint changes
	void setClearDerivative();

	// #ifdef DEBUG
	bool debugEnabled;
	// #endif
private:
	double error = 0;
	double setpoint = 0;
	double output = 0;

	double inputLast = 0;
	uint64_t timeLast = 0;
	double outputLast = 0;
	uint64_t Dt = 0;

	bool enabled = true;

	std::string name;

	bool clearDerivative = true;

	time_t timer;
};

#endif
