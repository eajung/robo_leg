/*
 * File name: Knee_motor_program_2
 * Author: Erik Jung
 * Comments: This is a force controlled motion of the flexural knee tensegrity structure.
 * As the hamstring is pulled, the tension grows exponentially to a defined maximum tension.
 * From there once the structure reaches the set tension, it releases back to the original non-flexed state.
 */

/* 
 * Include all libraries needed to properly run program
 * Sketch -> Include Library -> Manage Libraries
 */
// ------------------------------------------------------
#include <math.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <stdio.h>
#include <Tensegrity_Motor.h>

// ------------------------------------------------------
/*
 * Define any global or set variables
 */
const int button_pin = 2; // the number of the switch pin
int button_state = 0; // this will change based on the state of the push button status
unsigned long time; // time might be used by the delay()
Tensegrity_Motor tensegrity_motor;

//====SETUP===================================================

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button_pin, INPUT); // initialize the switch pin as an input
}

//==LOOP======================================================
//============================================================
// Put your main code here to run repeatedly:
void loop() {
  
  //Time function
  time = millis(); //print time since started in milliseconds
  delay(10); //refreshing time constant
  
  button_state = digitalRead(button_pin); // read the state of the switch value

  //Algorithm for GAIT
  if (button_state == HIGH) {
    Serial.println("Entering knee_flex");
    tensegrity_motor.hip_flex(2000, 100);    
  }//end of button_state if
  
} //===================end of loop , END OF PROGRAM=================================








