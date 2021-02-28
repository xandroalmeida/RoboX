#include "engine.h"

Engine::Engine(uint8_t motor1, uint8_t motor2, uint8_t encoderPin) : 
    _motor1(motor1),
    _motor2(motor2),
    _speedometer(encoderPin),
    _rps(0),
    _Kp(10.0),
    _Ki(30.0),
    _Kd(5.0),
    _setpoint(0.0),
    _input(0.0),
    _output(0.0),
    _pid(&_input, &_output, &_setpoint, _Kp, _Ki, _Kd, DIRECT)
{
}

void Engine::begin()
{
    _speedometer.begin();
    _pid.SetMode(AUTOMATIC);
    _motorDrive.motor(_motor1, BRAKE, 0);
    _motorDrive.motor(_motor2, BRAKE, 0);
}

void Engine::loop()
{
    _speedometer.loop();
    _input = _speedometer.getRPS();
    _pid.Compute();
    _motorDrive.motor(_motor1, FORWARD, _output);
    _motorDrive.motor(_motor2, FORWARD, _output);
}

void Engine::setRPS(double rps) {
    _setpoint = rps;
}