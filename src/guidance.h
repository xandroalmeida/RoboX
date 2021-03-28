#ifndef __GUIDANCE_H__
#define __GUIDANCE_H__

#include "device_base.h"

class Guidance : DeviceBase {
public:
    Guidance(Vio *vio);
    virtual void begin();
private:
    void update();
};

#endif