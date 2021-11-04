#include "PID.h"

PID::PID(double p, double i, double d, double maxOut = MOTOR_MAX_SPEED, std::string name = "") {
	this->kP = p;
	this->kI = i;
	this->kD = d;
	this->maxOut = maxOut;
	this->name = name;

	integrating = true;
	enabled = false;
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
	if (enabled) {
		//Update the times
		dT = time(&timer) - timeLast;
		timeLast = time(&timer);

		//P
		error = target - input;
		proportion = error * kP;

		//I
		if (integrating)
			integrator += error * dT * kI;

		//D
		if (clearDerivative) {
			derivative = 0;
			clearDerivative = false;
		} else
			//Change in error = errorCur - errorLast = (target - input) - (target - inputLast) = inputLast - input
			derivative = ((inputLast - input) / dT) * kD;

		output = (proportion + integrator + derivative);

		//Clamping for the integrator
		//No limit if equal to 0
		if (maxOut) {
			//Check to see if we need to clamp our output
			if (abs(output) > maxOut) {
				output = copysign(maxOut, output);
				
				//Since we are clamped, if the output and the error have the same sign, we have to disable the integrator
				// because it will become too large and cause windup
				integrating = copysign(1, output) != copysign(1, error);
			} else
				//Continue integrating because we are not clamped
				integrating = true;
		}

		inputLast = input;
		outputLast = output;
	} else {
		timeLast = time(&timer);
		inputLast = input;
		output = 0;
	}

	return output;
}

void PID::idle(double input) {
	timeLast = time(&timer);
}

double PID::getError() {
	return error;
}

void PID::setClearDerivative() {
	clearDerivative = true;
	timeLast = time(&timer);
}
