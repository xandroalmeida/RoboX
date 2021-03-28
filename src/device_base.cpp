#include "device_base.h"
#include <Eventually.h>

extern EvtManager evtManager;

DeviceBase::DeviceBase(Vio *vio) 
: _vio(vio)
{
}

void DeviceBase::begin()
{
    if (getTimeLoop() > 0) {
        auto t = new EvtTimeListener(getTimeLoop(), true, [](EvtListener *l, EvtContext *ctx) {
            static_cast<DeviceBase*>(l->extraData)->loop();
            return false;
        });
        t->extraData = this;
        evtManager.addListener(t);
    }
}