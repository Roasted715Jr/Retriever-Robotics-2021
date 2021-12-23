#ifndef _ROBOTSTATE_H_
#define _ROBOTSTATE_H_

// RobotSTate class with all the state info you could want
class RobotState{
  public:
  RobotState();
  void reset();

  // state data
  double t;
  double x;
  double y;
  double theta;
  double vel;
  double accel;
};

#endif