/*
  Lora32u4_Battery.h - Library for check the status of rechargeable battery.
  Created by Marcelo Maximiano, July 9, 2019.
  Released into the public domain.
*/
#ifndef Lora32u4_Battery_h
#define Lora32u4_Battery_h

#include "Arduino.h"

class Lora32u4_Battery
{
  public:
    // read-only properties
    const float& voltage = _voltage;
    const bool&  isConnected = _isConnected;
    const bool&  isRunningOnBatteries = _isRunningOnBatteries;
    const byte&   percentage = _percentage;

    // methods
    Lora32u4_Battery(byte pinBat, byte pin5V);
    void updateStatus();
    
  private:
    byte _pinBat;
    byte _pin5V;
    float _voltage = 0.0;
    bool  _isConnected = false;
    bool  _isRunningOnBatteries = false;
    byte   _percentage = 0;

    float _batteryValue(); 
    float _extPowerValue(); 
};

#endif
