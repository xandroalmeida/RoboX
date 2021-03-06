#ifndef _ENGINE__H_
#define _ENGINE__H_

#include <stdint.h>
#include <PID_v1.h>
#include "device_base.h"

#include "MotorDriver.h"
#include "vio.h"

class Engine : public DeviceBase {
public:
    Engine(Vio *vio, ChassiSide side, uint8_t motor1, uint8_t motor2);
    virtual void begin();
protected:
    virtual void loop();
    virtual uint16_t getTimeLoop();
private:
    ChassiSide _side;
    uint8_t _motor1;
    uint8_t _motor2;
    double _Kp;
    double _Ki;
    double _Kd;
    double _setpoint;
    double _input; 
    double _output;
    PID _pid;
    MotorDriver _motorDrive;
};

#endif
