#ifndef _SPEEDOMETER__H_
#define _SPEEDOMETER__H_

#include <stdint.h>
#include <Eventually.h>
#include "device_base.h"
#include "vio.h"

class Speedometer : public DeviceBase {

public:
    Speedometer(Vio *vio, ChassiSide side, uint8_t inputPin);
    virtual void begin();
    friend bool Speedometer_onTimer(EvtListener *l, EvtContext *ctx);

private:
    void onTimer();
    void pinChanged(bool pinstate);
    static void pinChanged(Speedometer* _this, bool pinstate) {
        _this->pinChanged(pinstate);
    }
    
    static const uint16_t _timeout;
    ChassiSide _side;
    uint8_t _inputPin;
    unsigned long _lastChange;
    Speed _speeds[4];
    uint8_t _ptSpeeds;
}; 

#endif