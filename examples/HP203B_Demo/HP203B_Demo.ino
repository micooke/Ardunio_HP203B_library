/* 
 HP203B Pressure & Temperature Sensor Library
 By: Andrew Shelestov
 Date: April 19th, 2017
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 Get pressure and temperature from the HP203 sensor.
 */

#include <Wire.h>
#include "HP203B.h"

//Create an instance of the object
HP203B myHP203;
float tempC;
float pressure;
uint32_t i;

void setup() {
  Serial.begin(115200);
  Serial.println("HP203B Example!");

  myHP203.begin();
  pressure = 0;
  tempC = 0;
  i = 0;
}

void loop() {
  if(0 == myHP203.getAll(&tempC, NULL, &pressure)){
    Serial.print(i++);
    Serial.print(" Temperature:");
    Serial.print(tempC, 1);
    Serial.print("C");
    Serial.print(" \tpressure:");
    Serial.print(pressure, 1);
    Serial.print(" hPA");
    Serial.println();
  }else{
    Serial.println("Something went wrong...");
  }

  delay(1000);
}
