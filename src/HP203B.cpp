/* 
 HP203B Pressure & Temperature Sensor Library
 By: Andrew Shelestov
 Date: April 19th, 2017
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
 Get pressure and temperature from the HP203 sensor.
 */

#include <Wire.h>

#include "HP203B.h"

HP203B::HP203B() {}

void HP203B::begin(){
  Wire.begin();
}

int HP203B::getAll(float* p_tempC, float* p_tempF, float* p_pressure) {
  float cTemp, fTemp, pressure;
  unsigned int data[6] = {0};

  if(NULL == p_tempC && NULL == p_tempF && NULL == p_pressure){
    return -1;
  }

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Send OSR and channel setting command
  Wire.write(0x40 |0x04 | 0x00);
  // Stop I2C transmission
  Wire.endTransmission();
  delay(500);

  // Start I2C transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x10);
  // Stop I2C transmission
  Wire.endTransmission();

  // Request 6 bytes of data
  Wire.requestFrom(Addr, 6);

  // Read 6 bytes of data
  // cTemp msb, cTemp csb, cTemp lsb, pressure msb, pressure csb, pressure lsb
  if (Wire.available() == 6) {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
    data[5] = Wire.read();
  }
  if(NULL == data[0] && NULL == data[1] && NULL == data[2] && NULL == data[3] && NULL == data[4] && NULL == data[5]){
    return -1;
  }

  // Convert the data to 20-bits
  cTemp = (((data[0] & 0x0F) * 65536) + (data[1] * 256) + data[2]) / 100.00;
  fTemp = (cTemp * 1.8) + 32;
  pressure = (((data[3] & 0x0F) * 65536) + (data[4] * 256) + data[5]) / 100.00;

  if(NULL != p_tempC){
    *p_tempC = cTemp;
  }
  if(NULL != p_tempF){
    *p_tempF = fTemp;
  }
  if(NULL != p_pressure){
    *p_pressure = pressure;
  }
  return 0;
}
