#ifndef _SPEEDOMETER__H_
#define _SPEEDOMETER__H_

#include <stdint.h>

class Speedometer {

public:
    Speedometer(uint8_t inputPin);
    void begin();
    /* void loop(); */

    float getRPM();
    float getRPS();
    void pinChanded(bool pinstate);

    uint32_t getTachometer() { return _partialTachometer;}

    static void pinChanded(Speedometer* _this, bool pinstate) {
        _this->pinChanded(pinstate);
    }

private:
    uint8_t _inputPin;
    uint8_t _lastPinState;
    uint32_t _tachometer;
    uint16_t _partialTachometer;
    unsigned long _lastMillis;
    float _currentRPS;
}; 

#endif