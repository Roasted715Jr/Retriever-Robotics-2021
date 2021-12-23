#include "PID.h"
#include <chrono>
#include <iostream>

PID::PID(double p, double i, double d, double maxOut, std::string name) {
	this->kP = p;
	this->kI = i;
	this->kD = d;
	this->maxOut = maxOut;
	this->name = name;

	integrating = true;
	enabled = false;
	
	// time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	time = clock();
	// timeLast = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	timeLast = clock();
}

void PID::setTarget(double target) {
	this->target = target;
}

double PID::getTarget() {
	return target;
}

void PID::setEnabled(bool enabled) {
	this->enabled = enabled;
}

bool PID::getEnabled() {
	return enabled;
}

void PID::setMaxOut(double maxOut) {
	this->maxOut = maxOut;
}

double PID::update(double input) {
	bool debugEnabled = true;

	if (enabled) {
		//Update the times
		dT = time - timeLast;
		timeLast = time;
		dT = 20;

		//P
		//Proportional to the error
		error = target - input;
		proportion = error * kP;

		//I
		//Clamping for the integrator
		//No limit if equal to 0
		// std::cout << (abs(outputLast) > maxOut) << std::endl;
		// std::cout << copysign(1, outputLast) << copysign(1, error) << std::endl;
		// integrating = !(abs(outputLast) > maxOut && copysign(1, output) == copysign(1, error));
		integrating = !(abs(outputLast) > maxOut && copysign(1, output) == copysign(1, error));
		//Prevents a steady error state
		// (even if we are giving input, the error may not be changing much if at all)
		if (integrating)
			integrator += error * dT * kI;

		//D
		//Can prematurely slow down the motors if the error is massively decreasing
		// so we don't overshoot
		if (clearDerivative) {
			derivative = 0;
			clearDerivative = false;
		} else
			//Change in error = errorCur - errorLast = (target - input) - (target - inputLast) = inputLast - input
			derivative = ((inputLast - input) / dT) * kD;

		output = (proportion + integrator + derivative);
		//Clamping for the integrator
		//No limit if equal to 0
		// if (maxOut) {
		// 	//Check to see if we need to clamp our output
		// 	if (abs(output) > maxOut) {
		// 		output = copysign(maxOut, output);
				
		// 		//Since we are clamped, if the output and the error have the same sign, we have to disable the integrator
		// 		// because it will become too large and cause windup
		// 		integrating = copysign(1, output) != copysign(1, error);
		// 	} else
		// 		//Continue integrating because we are not clamped
		// 		integrating = true;
		// }
		// if (abs(output) > maxOut)
		// 	output = copysign(maxOut, output);

		inputLast = input;
		outputLast = output;

		if(debugEnabled){
			std::cout << name << ": "
			<< "  input: " << input
			<< "  E: " << error
			<< "  Integrating: " << integrating
			<< "  P: " << proportion
			<< "  I: " << integrator
			<< "  D: " << derivative
			// << "  Time: " << time
			// << "  TimeL: " << timeLast
			<< "  dT: " << dT
			<< "  output: " << output
			<< std::endl;
		}
	} else {
		timeLast = time;
		inputLast = input;
		output = 0;
	}

	return output;
}

// void PID::idle(double input) {
// 	timeLast = time(&timer);
// }

double PID::getError() {
	return error;
}

void PID::setClearDerivative() {
	clearDerivative = true;
	timeLast = time;
}
void PID::changeConstants(double p, double i, double d) {
	kP = p;
	kI = i;
	kD = d;
}
