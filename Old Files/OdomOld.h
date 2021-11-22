#ifndef _ODOM_H_
#define _ODOM_H_

#include "RobotState.h"
// #include "vex.h"
// #include "robot-config.h"

class Odom{
public:
  double gyro_calibrameter;

  Odom();
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

private:
  friend void autonMotorControlLoop(void*);
  friend class ZController;
  friend class HoloController;

  RobotState currentState;
  RobotState oldState;
  bool enabled;

  double oldLEncoder;
  double oldREncoder;

  double gyro_last = 90.;
  uint32_t time_last = 0;
};

#endif
