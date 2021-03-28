#ifndef __DEVICEBASE_H__
#define __DEVICEBASE_H__

#include "vio.h"

class DeviceBase {
public:
    DeviceBase(Vio *vio);
    virtual void begin() = 0;
protected:
    Vio *_vio;
};

#endif