#ifndef PID_H
#define PID_H

#include <math.h>
#include <stdint.h>
#include <string>
#include <time.h>

//Maybe make this a bit less than 127 in case the motors are worn out enough to not speed up past a value of, for example, 125
#define MOTOR_MAX_SPEED 127

class PID {
    public:
        PID(double p, double i, double d, double maxOut, std::string name);
        void setTarget(double target);
        double getTarget();
        void setEnabled(bool enabled);
        bool getEnabled();
        void setMaxOut(double maxOut);
        double update(double input);
        void idle(double input); //Idle when disabled to update timings
        double getError();
        void setClearDerivative(); //Used for large setpoint changes

    private:
        double kP, kI, kD; //Tunable constants
        // double iLimit, maxOut; //0 means no limit
        double maxOut;
        // double iActiveZone; //0 means maxOut first, then infinite active zone if maxOut is 0
        double proportion = 0, integrator = 0, derivative = 0;
        bool integrating;

        double error = 0;
        double target = 0;
        double output = 0;

        double inputLast = 0;
        uint64_t timeLast = 0;
        double outputLast = 0;
        uint64_t dT = 0;

        bool enabled;

        std::string name;
        bool clearDerivative = true;
        time_t timer;
};

#endif
