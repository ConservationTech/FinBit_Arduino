//  MAX30105: Output all the raw Red/IR readings
//  By: Nathan Seidle @ SparkFun Electronics
//  Date: October 2nd, 2016
//  https://github.com/sparkfun/MAX30105_Breakout
//  
//
//  Hardware Connections (Breakoutboard to Arduino):
//  -5V = 5V (3.3V is allowed),
//  -GND = GND
//  -SDA = A4 (or SDA)
//  -SCL = A5 (or SCL)
//  -INT = Not connected
//
//  The MAX30105 Breakout can handle 5V or 3.3V I2C logic. We recommend powering the board with 5V
//  but it will also run at 3.3V.
//
//  This code is released under the [MIT License](http://opensource.org/licenses/MIT).
//

#include <Wire.h>
#include "MAX30105.h"
#include <avr/wdt.h>

MAX30105 particleSensor;

unsigned long time;

void setup()
{
  Serial.begin(115200);
  Serial.println("Initializing...");

  // Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }

  // particleSensor.setup(); //Configure sensor. Use 6.4mA for LED drive // <--- WAS THE DEFAULT

  byte ledBrightness = 128; //Options: 0=Off to 255=50mA
  byte sampleAverage = 1; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 3; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; //Options: 69, 118, 215, 411
  int adcRange = 16384; //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
  
  Serial.println("Time_ms\tRed\tIR");
  
}

void loop()
{

  time = millis();

  if (time <= 240001){

    particleSensor.setPulseAmplitudeRed(0xFF); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0xFF); //Turn on IR LED

  } else if (time>240001){
    wdt_reset();
    particleSensor.setPulseAmplitudeRed(0x0); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0x0); //Turn on IR LED
    Serial.end();
 } 
     
Serial.print(time);
Serial.print("\t");
Serial.print(particleSensor.getRed());
Serial.print("\t");
Serial.print(particleSensor.getIR());
Serial.println();

}
