#include "engine.h"

Engine::Engine(Vio *vio, ChassiSide side, uint8_t motor1, uint8_t motor2) : 
    DeviceBase(vio),
    _side(side),
    _motor1(motor1),
    _motor2(motor2),
    //_speedometer(encoderPin),
    _Kp(0.2),
    _Ki(0.3),
    _Kd(0.01),
    _setpoint(0.0),
    _input(0.0),
    _output(0.0),
    _pid(&_input, &_output, &_setpoint, _Kp, _Ki, _Kd, DIRECT)
{
}

void Engine::begin()
{
    DeviceBase::begin();
    _pid.SetMode(AUTOMATIC);
    _motorDrive.motor(_motor1, RELEASE, 0);
    _motorDrive.motor(_motor2, RELEASE, 0);
}

uint16_t Engine::getTimeLoop()
{
    return 25;
}

void Engine::loop()
{
    _setpoint = abs(_vio->getSetPointSpeed(_side));
    _input = _vio->getSpeed(_side);
    _pid.Compute();
    _vio->setEnginePower(_side, _output);

    auto command = _vio->getSetPointSpeed(_side) > 0 ? FORWARD : BACKWARD;
    _motorDrive.motor(_motor1, command, _output);
    _motorDrive.motor(_motor2, command, _output);
}
