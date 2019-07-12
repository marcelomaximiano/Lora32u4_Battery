/*
  Lora32u4_Battery.cpp - Library for check the status of rechargeable battery.
  Created by Marcelo Maximiano, July 9, 2019.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Lora32u4_Battery.h"

#define batMin 3.20
#define batMax 4.10

Lora32u4_Battery::Lora32u4_Battery(byte pinBat, byte pin5V) {
  pinMode(pinBat, INPUT);
  pinMode(pin5V, INPUT);
  _pinBat = pinBat;
  _pin5V = pin5V;
}

void Lora32u4_Battery::updateStatus() {
  float value = 0.0;
  float maxValue = 0.0;
  float minValue = 99.9;
  float avgValue = 0.0;
  float diff = 0.0;

  for (byte i = 0; i < 10; i++) {
    value = _batteryValue();
    if (value > maxValue) maxValue = value;
    if (value < minValue) minValue = value;
    avgValue = avgValue + value;
    delay(5);
  }

  diff = maxValue - minValue;  
  avgValue = avgValue / 10;

  // update properties
  _isConnected = (diff > 0.2) ? false : true;
  _isRunningOnBatteries = (_extPowerValue() > 4.5) ? false : true;
  _voltage = _isConnected ? avgValue : 0.00;
  _percentage = isConnected ? map(_voltage*100,batMin*100.0,batMax*100.0,0,100) : 0;
  if (_percentage < 0) _percentage = 0;
  if (_percentage > 100) _percentage = 100;
}

float Lora32u4_Battery::_batteryValue() {
  float value = analogRead(_pinBat);

  value *= 2;    
  value *= 3.3;  
  value /= 1024;
  value = floorf(value * 100) / 100;  

  return value;
}

float Lora32u4_Battery::_extPowerValue() {
  float value = analogRead(_pin5V);

  value *= 2;    
  value *= 3.3;  
  value /= 1024;
  value = floorf(value * 100) / 100;  

  return value;
}
