/*
  MAX30105 Breakout: Output all the raw Red/IR/Green readings
  By: Nathan Seidle @ SparkFun Electronics
  Date: October 2nd, 2016
  https://github.com/sparkfun/MAX30105_Breakout

  Outputs all Red/IR/Green values.

  Hardware Connections (Breakoutboard to Arduino):
  -5V = 5V (3.3V is allowed)
  -GND = GND
  -SDA = A4 (or SDA)
  -SCL = A5 (or SCL)
  -INT = Not connected

  The MAX30105 Breakout can handle 5V or 3.3V I2C logic. We recommend powering the board with 5V
  but it will also run at 3.3V.

  This code is released under the [MIT License](http://opensource.org/licenses/MIT).
*/

#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include <avr/wdt.h>

MAX30105 particleSensor;

unsigned long time;
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;


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
  int pulseWidth = 69; //Options: 69, 118, 215, 411
  int adcRange = 16384; //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
  
  Serial.println("Time_ms\tGreen\tRed\tIR\tBPM\tavgBPM\tlast_beat_time\ttemp");
  
}

void loop()
{

  time = millis();

  if (time < 30001) {
    
    particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0x10); //Turn on IR LED

  }
  
  else if (time >= 30001 && time < 60001) { 

    particleSensor.setPulseAmplitudeGreen(0x10); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0x10); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0x10); //Turn up IR LED
    
  } else if (time >= 60001 && time < 90001) {

    particleSensor.setPulseAmplitudeGreen(0x20); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0x20); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0x20); //Turn up IR LED
    
  } else if (time >= 90001 && time < 120001){

    particleSensor.setPulseAmplitudeGreen(0x30); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0x30); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0x30); //Turn on IR LED
    
  } else if (time >= 120001 && time < 150001){

    particleSensor.setPulseAmplitudeGreen(0x40); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0x40); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0x40); //Turn on IR LED

  } else if (time >= 150001 && time < 180001){

    particleSensor.setPulseAmplitudeGreen(0x50); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0x50); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0x50); //Turn on IR LED

  } else if (time >= 180001 && time < 210001){

    particleSensor.setPulseAmplitudeGreen(0x50); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0x50); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0x50); //Turn on IR LED

  } else if (time >= 210001 && time < 240001){

    particleSensor.setPulseAmplitudeGreen(0x60); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0x60); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0x60); //Turn on IR LED

  } else if (time >= 240001 && time < 270001){

    particleSensor.setPulseAmplitudeGreen(0x70); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0x70); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0x70); //Turn on IR LED

  } else if (time >= 270001 && time < 300001){

    particleSensor.setPulseAmplitudeGreen(0x80); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0x80); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0x80); //Turn on IR LED

  } else if (time >= 300001 && time < 330001){

    particleSensor.setPulseAmplitudeGreen(0x90); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0x90); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0x90); //Turn on IR LED
    
  } else if (time >= 330001 && time < 360001){

    particleSensor.setPulseAmplitudeGreen(0xA0); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0xA0); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0xA0); //Turn on IR LED

  } else if (time >= 360001 && time < 420001){

    particleSensor.setPulseAmplitudeGreen(0xA0); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0xA0); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0xA0); //Turn on IR LED

  } else if (time >= 420001 && time < 450001){

    particleSensor.setPulseAmplitudeGreen(0xB0); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0xB0); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0xB0); //Turn on IR LED

  } else if (time >= 450001 && time < 480001){

    particleSensor.setPulseAmplitudeGreen(0xC0); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0xC0); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0xC0); //Turn on IR LED
      
  } else if (time >= 480001 && time < 510001){

    particleSensor.setPulseAmplitudeGreen(0xD0); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0xD0); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0xD0); //Turn on IR LED

  } else if (time >= 510001 && time < 540001){

    particleSensor.setPulseAmplitudeGreen(0xE0); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0xE0); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0xE0); //Turn on IR LED


   } else if (time >= 540001 && time < 570001){

    particleSensor.setPulseAmplitudeGreen(0xF0); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0xF0); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0xF0); //Turn on IR LED

  } else if (time >= 570001 && time < 600001){

    particleSensor.setPulseAmplitudeGreen(0xFF); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0xFF); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0xFF); //Turn on IR LED
      
  } else if (time >= 600001 && time < 630001) {

    particleSensor.setPulseAmplitudeGreen(0x0); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0x0); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0x0); //Turn on IR LED
    
  } else if (time >= 630001) {

    wdt_reset();
    // time = 0;
    particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
    particleSensor.setPulseAmplitudeRed(0); //Turn off Red LED
    particleSensor.setPulseAmplitudeIR(0x10); //Turn on IR LED

  }
     
  long irValue = particleSensor.getIR();
  if (checkForBeat(irValue) == true)
  
  {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable

      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

  float temperature = particleSensor.readTemperature();
  
  Serial.print(time);
  Serial.print("\t");
  Serial.print(particleSensor.getGreen());
  Serial.print("\t");
  Serial.print(particleSensor.getRed());
  Serial.print("\t");
  Serial.print(particleSensor.getIR());
  Serial.print("\t");
  Serial.print(beatsPerMinute);
  Serial.print("\t");
  Serial.print(beatAvg);
  Serial.print("\t");
  Serial.print(lastBeat);
  Serial.print("\t");
  Serial.print(temperature);

  Serial.println();

}
