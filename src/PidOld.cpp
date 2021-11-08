//PID class
#include "PidOld.h"
// #include "vex.h"
#include <iomanip>
#include <iostream>

// default to no limits on output, integral, or integral zone
Pid::Pid(double p, double i, double d){
	Kp = p;
	Ki = i;
	Kd = d;
	iLimit = 0;
	maxOut = 0;
	IactiveZone = 0;

	name = "";
}

//default IactiveZone to maxOut_
Pid::Pid(double p, double i, double d, double iLimit_, double maxOut_, std::string name){
	Kp = p;
	Ki = i;
	Kd = d;
	iLimit = iLimit_;

	IactiveZone = maxOut_;

	maxOut = maxOut_;

	this->name = name;
}

// full send
Pid::Pid(double p, double i, double d, double iLimit_, double IactiveZone_, double maxOut_, std::string name){
	Kp = p;
	Ki = i;
	Kd = d;
	iLimit = iLimit_;

	IactiveZone = IactiveZone_;

	maxOut = maxOut_;

	this->name = name;
}

void Pid::setTarget(double target){
	//TODO: remove this?
	// reset timing and stuff?
	setpoint = target;
	// integrator = 0;
}
double Pid::getTarget(){
	return setpoint;
}
void Pid::disable(){
	enabled = false;
}
void Pid::enable(){
	enabled = true;
}
bool Pid::getEnabled(){
	return enabled;
}
void Pid::setMaxOut(double maxOut_){
	maxOut = maxOut_;
}
double Pid::update(double input){
	double derivative;
	if(enabled){
		// todo timelast initiliaze on first run
		// Dt = vex::timer::system()-timeLast;
		Dt = time(&timer) - timeLast;
		// timeLast = vex::timer::system();
		timeLast = time(&timer);

		// P
		error = setpoint - input;
		double P = error * Kp;

		// I
		// integral active zone. 0 means no limit
		if(IactiveZone == 0 || fabs(P) < IactiveZone){
			integrating = true;
			integrator += error*Dt*Ki;
		}
		else{
			integrating = false;
			// integrator = 0;
		}


		// limit integral
		// 0 means no limit set
		if(iLimit == 0) {}
		else if(integrator > iLimit)
			{ integrator = iLimit; }
		else if(integrator < -iLimit)
			{ integrator = -iLimit; }


		if(clearDerivative){
			derivative = 0;
			clearDerivative = false;
		}
		else{
			derivative = ((inputLast-input)/Dt)*Kd;
		}

		output = (P + integrator + derivative);

		// limit output
		// no limit if equal 0
		if(maxOut == 0){}
		else if(output > maxOut)
			{output = maxOut;}
		else if (output < -maxOut)
			{output = -maxOut;}

			// DEBUGGING
			// #ifdef DEBUG
			if(debugEnabled){
			std::cout << name << ": "
			<< "E: " << std::setw(7) << error
			<< "  input: " << std::setw(7) << input
			<< "  P: " << std::setw(7) << P
			<< "  I: " << std::setw(7) << integrator
			<< "  D: " << std::setw(7) << derivative
			<< "  Dt: " << std::setw(7) << Dt
			<< "  output: " << std::setw(7) << output
			<< std::endl;
			}
			// #endif

		inputLast = input;
		outputLast = output;
	}
	else{
	// timeLast = vex::timer::system();
	timeLast = time(&timer);
	inputLast = input;
	output = 0;
	}
	return output;
}
// idle when disabled to update timings
void Pid::idle(double input){
	// timeLast = vex::timer::system();
	timeLast = time(&timer);
	inputLast = input;
}

double Pid::getError(){
	return error;
}

void Pid::setClearDerivative(){
	clearDerivative = true;
	// timeLast = vex::timer::system();
	timeLast = time(&timer);
}
