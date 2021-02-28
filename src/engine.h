#ifndef _ENGINE__H_
#define _ENGINE__H_

#include <stdint.h>
#include <speedometer.h>
#include "MotorDriver.h"
#include <PID_v1.h>


class Engine {
public:
    Engine(uint8_t motor1, uint8_t motor2, uint8_t encoderPin);
    void begin();
    void loop();
    void setRPS(double rps);

private:
    uint8_t _motor1;
    uint8_t _motor2;
    Speedometer _speedometer;
    uint8_t _rps;
    double _Kp;
    double _Ki;
    double _Kd;
    double _setpoint;
    double _input; 
    double _output;
    PID _pid;
    MotorDriver _motorDrive;

};

#endif
