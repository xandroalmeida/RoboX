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

protected:
    virtual void loop();
    virtual uint16_t getTimeLoop();
private:
    void pinChanged(bool pinstate);
    static void pinChanged(Speedometer* _this, bool pinstate) {
        _this->pinChanged(pinstate);
    }
    
    ChassiSide _side;
    uint8_t _inputPin;
    unsigned long _lastChange;
    Speed _speeds[4];
    uint8_t _ptSpeeds;
}; 

#endif