/* 
This is a time controlled motion of 1 Motor for Flexion of Knee
Model. Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2 
---->  http://www.adafruit.com/products/1438
*/

//Need to make the time controlled Void and make sure it works.
//Voltage setting to 5V


#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61); 

// set pin numbers:
const int buttonPin = 2;     // the number of the swtich pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
 
unsigned long time;          //time might be used by delay() should work
float fact; //dependent of voltage
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *myMotor = AFMS.getMotor(1); //Knee Flexion

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("KNEE Motion Program!");

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(0);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
 
  //Setup Pins being used

  // initialize the switch pin as an input:
  pinMode(buttonPin, INPUT);
 //digitalWrite(buttonPin, High); //Turn on Internal pull-up

}

void loop() {
  uint8_t i; 
 //Time function
 time = millis();
 distance = 3200; 
 fact = 1.0; //for 6V
 
 //print time since started in milliseconds
 delay(10); //refreashing time constant

 // read the state of the switch value:
 buttonState = digitalRead(buttonPin);
  Serial.print(buttonState);
 if (buttonState == HIGH) {
  
   //Knee Flexion
   
     Serial.print("Shoulder Flexion\n");
     myMotor->run(FORWARD);
     Serial.print("    increase\n");
     for (i=0; i<100; i++) {
        myMotor->setSpeed(i);
        delay(5);
     }
     delay(distance*fact); //distance initial too long 2000, 3750 for 1st REV2, 2nd REV 2 = 3500
     
     Serial.print("    decrease\n");
     for (i=100; i!=0; i--) {
      myMotor->setSpeed(i);
      delay(5);
    }

    Serial.print("HOLD TIME\n");
    delay(1000);
    
   //Knee Extension
  
    Serial.print("Shoulder Extension\n");
    myMotor->run(BACKWARD);
     Serial.print("    increase\n");
     for (i=0; i<100; i++) {
        myMotor->setSpeed(i);
        delay(5);
     }
     
    delay(distance*fact); //distance
     
     Serial.print("    decrease\n");
     for (i=100; i!=0; i--) {
      myMotor->setSpeed(i);
      delay(5);
    }
   
    //Cooldown for next motion
    Serial.print("Shouldrer Cooldown\n");    
    myMotor->run(RELEASE);
    delay(500);
    
   
 }
    
}


/*This Void is used for simple test of DC Motors
 * 
 */

