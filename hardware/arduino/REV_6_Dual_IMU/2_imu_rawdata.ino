#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// The two BNO055 modules, bnoB has the ADR pin wired to 3.3v to change its i2c address
// Both are wired: SCL to analog 5, SDA to analog 4, VIN to 5v, GRN to ground
String input; // keyboard input
char command; // hotkey parsed from input

Adafruit_BNO055 bnoA = Adafruit_BNO055(-1, BNO055_ADDRESS_A);
Adafruit_BNO055 bnoB = Adafruit_BNO055(-1, BNO055_ADDRESS_B);

void setup() {
   Serial.begin(115200);
   if(!bnoA.begin()) {
       Serial.print("Ooops, BNO055(A) not detected");
       while(1);
   }
   bnoA.setExtCrystalUse(true);
   if(!bnoB.begin()) {
       Serial.print("Ooops, BNO055(B) not detected");
       while(1);
   }
   bnoB.setExtCrystalUse(true);
}

void loop() {

   
    if (Serial.available() > 0) { // if serial input is ready to read input
    input = Serial.readString();
    command = input[0];
    switch (command) {
      case 'p':
           imu::Vector<3> euler = bnoA.getVector(Adafruit_BNO055::VECTOR_EULER);
           Serial.print(euler.x()); Serial.print(", ");
           euler = bnoB.getVector(Adafruit_BNO055::VECTOR_EULER);
           Serial.println(euler.x());
 
        break;
      }
    }




   
}
