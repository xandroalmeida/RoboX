#include "guidance.h"

#include <Eventually.h>

Guidance::Guidance(Vio *vio) :
    DeviceBase(vio)    
{
}

void Guidance::begin()
{
    DeviceBase::begin();
}

uint16_t Guidance::getTimeLoop()
{
    return 100;
}

void Guidance::loop()
{
    Serial.println(_vio->getRadarDist(Front));
    if (_vio->getRadarDist(Front) > 0 && _vio->getRadarDist(Front) < 500) {
        if (_vio->getRadarDist(Right) == 0 && _vio->getRadarDist(Left) == 0) {
            _vio->setSetPointSpeed(Right, -300);
            _vio->setSetPointSpeed(Left, 300);
            return;
        }
        if (_vio->getRadarDist(Right) > _vio->getRadarDist(Left)) {
            _vio->setSetPointSpeed(Right, -300);
            _vio->setSetPointSpeed(Left, 300);
            return;
        } else {
            _vio->setSetPointSpeed(Right, 300);
            _vio->setSetPointSpeed(Left, -300);
            return;
        }
        return;
    }
    
    if (_vio->getRadarDist(Right) > 0 && _vio->getRadarDist(Right) < 500) {
        _vio->setSetPointSpeed(Right, -300);
        _vio->setSetPointSpeed(Left, 300);
        return;
    }

    if (_vio->getRadarDist(Left) > 0 && _vio->getRadarDist(Left) < 500) {
        _vio->setSetPointSpeed(Right, 300);
        _vio->setSetPointSpeed(Left, -300);
        return;
    }

    _vio->setSetPointSpeed(Right, 400);
    _vio->setSetPointSpeed(Left, 400);
}
