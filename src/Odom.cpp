// Odometry class
#include "Odom.h"

Odom::Odom(Robot& robot): robot(robot), currentState(robot.robotState) {
	currentState.reset();
	currentState.theta = 90.0;
	gyro_last = 90;
	oldState = currentState;

	oldLEncoder = getLEncoder();
	oldREncoder = getREncoder();
}

double Odom::getLVelocity(){
	// return lDrive_mtr1.get_actual_velocity();
	// return mDriveBL.velocity(velocityUnits::rpm);
	return robot.leftWheels.getVel();
}

double Odom::getRVelocity(){
	// return rDrive_mtr6.get_actual_velocity();
	// return mDriveBR.velocity(velocityUnits::rpm);
	return robot.rightWheels.getVel();
}

double Odom::getLEncoder(){
	// return lDrive_mtr1.get_position();
	// return (mDriveBL.position(rotationUnits::rev) + mDriveFR.position(rotationUnits::rev))/2;
	return robot.leftWheels.getPos();
}

double Odom::getREncoder(){
	// return rDrive_mtr6.get_position();
	// return (mDriveBR.position(rotationUnits::rev) + mDriveFL.position(rotationUnits::rev))/2;
	return robot.rightWheels.getPos();
}
RobotState Odom::getCurrentState(){
  	return currentState;
}

// odometry update function
// updates global x, y, theta, velocity states
void Odom::updateCurrentState(){
	// uint32_t Dt = vex::timer::system() - time_last;
	clock_t Dt = clock() * CLOCKS_PER_SEC - time_last;
	// time_last = vex::timer::system();
	time_last = clock() * CLOCKS_PER_SEC;
	double newX;
	double newY;

	double lEncoder = getLEncoder();
	double rEncoder = getREncoder();

	// convert to standard trig degrees with 0 pointing in positive x
	// double gyro_val1 = -gyro1.value(rotationUnits::deg) + 90;
	double gyro_val1 = -robot.gyroL.get_value() * 10 + 90;
	// double gyro_val2 = gyro2.value(rotationUnits::deg) + 90;
	double gyro_val2 = robot.gyroR.get_value() * 10 + 90;
	
	double gyro_val = (gyro_val1 + gyro_val2) / 2;
	// double dTheta = gyro_val - gyro_last;
	Angle dTheta = gyro_val - gyro_last;
	gyro_last = gyro_val;
	
	// account for the ungodly amounts of drift present in a vex gyro
	// dTheta += gyro_calibrameter/10 * Dt;

	// if(dTheta > 180.0){
	// 	dTheta -= 360.0;
	// }
	// else if(dTheta < -180.0){
	// 	dTheta += 360.0;
	// }
	//* update current theta with dtheta
	currentState.theta += dTheta;

	//average both sides for velocity
	currentState.vel = (getLVelocity() + getRVelocity()) / 2;

	// rotate robot encoder coodinates into field coordinates
	double delta_lEnc = lEncoder - oldLEncoder;
	double delta_rEnc = rEncoder - oldREncoder;
	// rotateAxes(newX, newY, delta_rEnc, delta_lEnc, (-currentState.theta + 90 - 45)*DEGREES_TO_RADIANS);
	rotateAxes(newX, newY, delta_rEnc, delta_lEnc, (-currentState.theta + (double) 45) / DEGREES_PER_RADIAN);
	// currentState.x += newX * DWHEEL_CIRCUM;
	currentState.x += newX * 1;
	// currentState.y += newY * DWHEEL_CIRCUM;
	currentState.y += newY * 1;

	// // integrate new x and y values assuming circular paths

	// if(delta_rEnc == delta_lEnc){
	//   dist = delta_lEnc;
	// }
	// // avoid nan and divide by zero
	// else if(dTheta == 0){
	//   // just average the encoders if we havent turned
	//   dist = (delta_lEnc + delta_rEnc) / 2;
	// }
	// else{
	//   // radians version of the odometry equation
	//   dTheta *= DEGREES_TO_RADIANS/2;
	//   dist = ( ((delta_lEnc+delta_rEnc)/2) / dTheta ) * sin(dTheta);
	// }

	// amount travelled in the x direction is equal to total distance travelled times the cosine of the angle
	// double angleRad = currentState.theta * DEGREES_TO_RADIANS;
	// currentState.x += cos(angleRad) * dist * DWHEEL_CIRCUM;
	// currentState.y += sin(angleRad) * dist * DWHEEL_CIRCUM;

	// std::cout << "x: " << currentState.x << "\ty: " << currentState.y<< "\trot:" << currentState.theta<<std::endl;
	// rotateAxes(newX, newY, 1, 0, -45*DEGREES_TO_RADIANS);
	// std::cout << "x: " << newX << "\ty: " << newY << std::endl;


	oldLEncoder = lEncoder;
	oldREncoder = rEncoder;

	// std::cout
	//   << "x: " << currentState.x
	//   << "\ty: " << currentState.y
	//   << "\tdeltalEnc: " << delta_lEnc
	//   << "\tdeltarEnc: " << delta_rEnc
	//   << "\tlEncoder: " << lEncoder
	//   << "\trEncoder: " << rEncoder

	//   << "\ttheta: " << currentState.theta
	//   << "\tvel: " << currentState.vel
	//   << std::endl;
}

void Odom::tareY(double y){
	currentState.y = y;
	oldLEncoder = getLEncoder();
	oldREncoder = getREncoder();
}

void Odom::tareX(double x){
	currentState.x = x;
	oldLEncoder = getLEncoder();
	oldREncoder = getREncoder();
}

void Odom::tareXY(double x, double y){
	// cout << "taring... " << endl;
	tareX(x);
	tareY(y);
	// cout << "x: " << currentState.x << "y: " << currentState.y << endl;
}

void Odom::tareTheta(double theta){
  	currentState.theta = theta;
}

// perform rotation of axes into new coordinates
//theta is radians
void Odom::rotateAxes(double &xPrime, double &yPrime, const double &x, const double &y, const double &theta){
	xPrime =  x*cos(theta) + y*sin(theta);
	yPrime = -x*sin(theta) + y*cos(theta);
}
