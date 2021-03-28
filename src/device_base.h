#ifndef __DEVICEBASE_H__
#define __DEVICEBASE_H__

#include "vio.h"

class DeviceBase {
public:
    DeviceBase(Vio *vio);
    virtual void begin();
protected:
    virtual void loop() {};
    virtual uint16_t getTimeLoop() = 0;

    Vio *_vio;
};

#endif