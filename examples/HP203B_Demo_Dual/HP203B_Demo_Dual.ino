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
HP203B HP203_1(0x76);
HP203B HP203_2(0x77);
float tempC;
float pressure;
uint32_t i;

void setup() {
  Serial.begin(115200);
  Serial.println("HP203B Example!");

  HP203_1.begin();
  HP203_2.begin();
  pressure = 0;
  tempC = 0;
  i = 0;
}

void loop() {
  if(0 == HP203_1.getAll(&tempC, NULL, &pressure)){
    Serial.print(i);
    Serial.print(" 1 T:");
    Serial.print(tempC, 1);
    Serial.print("C");
    Serial.print(" \tP:");
    Serial.print(pressure, 1);
    Serial.print(" hPA\t");
  }else{
    Serial.print("Something went wrong... with 1");
  }
  if(0 == HP203_2.getAll(&tempC, NULL, &pressure)){
    Serial.print(i);
    Serial.print(" 2 T:");
    Serial.print(tempC, 1);
    Serial.print("C");
    Serial.print(" \tP:");
    Serial.print(pressure, 1);
    Serial.print(" hPA");
  }else{
    Serial.print("Something went wrong... with 2");
  }
  Serial.println();
  ++i;
  delay(1000);
}
