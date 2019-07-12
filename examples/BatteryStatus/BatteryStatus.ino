/* 
   BatteryStatus.ino
   by Marcelo Maximiano - 2019

   This example demonstrates the use of the library Lora32u4_Battery.
   The library use two pins: 
   - one to monitor the voltage on battery 
   - and other to monitor the voltage on 5V pin
   
   The Feather 32u4 and Lora32u4 boards already have resistors dividers 
   on BAT pin connected to A9. So you don't need to do anything.

   But to use pin A10 (or other analog pin) to monitor the 5V pin, you
   need to do the following:

   1) connect a 100K resistor to the 5V pin and the other side to the pin A10  
   2) connect a 100K resistor to the GND pin and the other side to the pin A10   

   GND <---[100K]---(A10)---[100K]--> 5V pin

   This example code is in the public domain.               
*/  

#include "Lora32u4_Battery.h"

#define pinMeasureBat A9   
#define pinMeasure5V  A10

Lora32u4_Battery lora32u4_Battery(pinMeasureBat, pinMeasure5V);

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);

  // read the battery's status
  lora32u4_Battery.updateStatus();

  // voltage of battery
  Serial.print("Voltage: ");              
  Serial.print(lora32u4_Battery.voltage);
  Serial.println("V");
  
  // check if there is a battery connected to the charger header
  Serial.print("Connected: ");            
  if (lora32u4_Battery.isConnected) {
    Serial.println("yes");
  } else {
    Serial.println("no");
  }
  
  // check if the board is running on batteries (no USB plugged)
  Serial.print("Running on batteries: "); 
  if (lora32u4_Battery.isRunningOnBatteries) {
    Serial.println("yes");
  } else {
    Serial.println("no");
  }
  
  // check the estimate battery level
  Serial.print("Percentage: ");           
  Serial.print(lora32u4_Battery.percentage);
  Serial.println("%");
  
  Serial.println();

  digitalWrite(LED_BUILTIN, LOW);

  delay(5000);
}


