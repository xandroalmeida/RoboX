#ifndef __VIO_H__
#define __VIO_H__

#include <stdint.h>

enum ChassiSide {
    Left    = 0,
    Right   = 1,
    Front   = 2,
    Rear    = 3,
};

typedef int16_t Speed;

/**
 * Vehicle Integration Object
 */
class Vio {
public:
    Vio();

    //void setSpeed(ChassiSide side, Speed value) { _speed[side] = value; }  
    void setSpeed(ChassiSide side, Speed value) { _speed[side] += value; _speed[side] /= 2; }  
    Speed getSpeed(ChassiSide side) { return _speed[side]; }  

    void setSetPointSpeed(ChassiSide side, Speed value) { _setPointSpeed[side] = value; }  
    Speed getSetPointSpeed(ChassiSide side) { return _setPointSpeed[side]; }  

    void incTachometer(ChassiSide side) { _tachometer[side]++; }  
    uint32_t getTachometer(ChassiSide side) { return _tachometer[side]; }  

    void setEnginePower(ChassiSide side, uint16_t value) { _enginePower[side] = value; }  
    uint16_t getEnginePower(ChassiSide side) { return _enginePower[side]; }  

    void setRadarDist(ChassiSide side, uint16_t value) { _radarDist[side] = value; }  
    uint16_t getRadarDist(ChassiSide side) { return _radarDist[side]; }  

private:
    Speed _speed[2];
    Speed _setPointSpeed[2];
    uint32_t _tachometer[2];
    uint16_t _enginePower[2];
    uint16_t _radarDist[3];
};

#endif