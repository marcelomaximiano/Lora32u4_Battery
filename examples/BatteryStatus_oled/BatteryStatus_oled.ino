/* 
   BatteryStatus_oled.ino
   by Marcelo Maximiano - 2019
   Requires U8glib: https://github.com/olikraus/u8glib

   This example demonstrates the use of the library Lora32u4_Battery,
   using an Oled display:
   
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
#include "U8glib.h"
#include "Lora32u4_Battery.h"

// Oled I2C display, can be easily changed to other display
U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NONE);  // I2C 

#define pinMeasureBat A9   
#define pinMeasure5V  A10

Lora32u4_Battery lora32u4_Battery(pinMeasureBat, pinMeasure5V);

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // turn led 13 on
  digitalWrite(LED_BUILTIN, HIGH);

  // read the battery's status
  lora32u4_Battery.updateStatus();

  // show information in the Monitor Serial
  display_monitorSerial();

  // show information in the oled display
  display_oled();
  
  // turn led 13 off
  digitalWrite(LED_BUILTIN, LOW);

  delay(5000);
}

void display_monitorSerial() {
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
  Serial.print("Running on battery: "); 
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
}

void display_oled() {
  u8g.firstPage();
  u8g.setFont(u8g_font_8x13B);
  do
  {
    draw();
  } while ( u8g.nextPage() );
}

void draw() {
  char buf[100];

  u8g.setFont(u8g_font_6x12);

  // battery voltage
  char str_temp[7];
  dtostrf(lora32u4_Battery.voltage, 3, 2, str_temp);
  sprintf(buf, "Voltage: %sV", str_temp);
  u8g.drawStr(0, 15, buf);

  // battery connected
  sprintf(buf, "Connected: %s", lora32u4_Battery.isConnected?"yes":"no");
  u8g.drawStr(0, 27, buf);

  // running on batteries
  sprintf(buf, "Run. on battery: %s", lora32u4_Battery.isRunningOnBatteries?"yes":"no");
  u8g.drawStr(0, 39, buf);

  // battery percentage
  sprintf(buf, "Percentage: %d%%", lora32u4_Battery.percentage);
  u8g.drawStr(0, 51, buf);
}


