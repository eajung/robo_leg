#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

/*
This program is an abridged version of Adafruit BNO055 rawdata.ino available after installing the Adafruit BNO055 library
File→Examples→Adafruit BNO055→Raw Data
  Connections on Arduino Uno
  =========================================================================
  SCL to analog 5 | SDA to analog 4 | VDD to 3.3V DC | GND to common ground
*/

#define BNO055_SAMPLERATE_DELAY_MS (100)          // Delay between data requests

Adafruit_BNO055 bno = Adafruit_BNO055();          // Create sensor object bno based on Adafruit_BNO055 library

void setup(void)
{
  Serial.begin(115200);                           // Begin serial port communication
  if(!bno.begin())                                // Initialize sensor communication
  {  
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");  
  }
  delay(1000);
  bno.setExtCrystalUse(true);                     // Use the crystal on the development board
}

void loop(void)
{
  imu::Quaternion quat = bno.getQuat();           // Request quaternion data from BNO055

  Serial.print(quat.w(), 4);  Serial.print("\t"); // Print quaternion w
  Serial.print(quat.x(), 4);  Serial.print("\t"); // Print quaternion x
  Serial.print(quat.y(), 4);  Serial.print("\t"); // Print quaternion y
  Serial.print(quat.z(), 4);  Serial.println();   // Print quaternion z

  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  Serial.print("X: ");
  Serial.print(euler.x());
  Serial.print(" Y: ");
  Serial.print(euler.y());
  Serial.print(" Z: ");
  Serial.print(euler.z());
  Serial.print("\t\t");

  delay(BNO055_SAMPLERATE_DELAY_MS);              // Pause before capturing new data
}