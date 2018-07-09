/*
  REV_5_open_loop.ino
  
  Description:
  This program is for testing the motors on the tensegrity flexural joint by individually controlling every motor
  With different hotkeys. Moreover, each motor can be set at a particular speed. Note that there is a small delay
  with pressing return in the Serial TX side and the motors following through.

  The format for the transmission is as follows:
  desired_Motor,speed with NO spaces!

  The hotkeys for the motors are as follows:
  t: tibialis_hamstring_motor forward
  h: tibialis_hamstring_
  c: calf_quadricep_motor forward

  The speeds for the motors can range from 0 to 255.

  Lastly, the s hotkey at any point will cease all motor activity
  and the a hotkey will print out the current gyro reading.
*/

/*
  Required Libraries
*/

//Print libraries
#include <stdio.h>
//Motor libraries
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
//Gyroscope libraries
#include <Wire.h>

/*
  Macro Definitions & Global Variables
*/
#define RELEASE_TIBIALIS 1
#define CONTRACT_TIBIALIS 2
#define RELEASE_CALF 2
#define CONTRACT_CALF 1

String input;
int commaIndex;
char command;
int desired_speed;

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); // create an instance variable of motor shield
Adafruit_DCMotor *tibialis_hamstring_motor = AFMS.getMotor(1); // tibialis & hamstring motor
Adafruit_DCMotor *calf_quadricep_motor = AFMS.getMotor(4); // calf & quadricep motor

// ================== HELPER FUNCTIONS ===========================
/*
  squat():
  param: int millisec - specifies the amount of time tensegrity structure squats
       int desired_speed - moves the motors at this desired_speed to move the tensigrity structure
  Description: This function will have both tibialis_hamstring_motor and the calf_quadricep_motor contract but one will contract at a slower rate in that amount of time.
*/
void squat(int millisec, int desired_speed) {
  Serial.print("calf_quadricep_motor and tibialis_hamstring_motor contracts/n ");
  calf_quadricep_motor->run(CONTRACT_CALF); // set motor direction to contract the calf muscles
  for (int i = 0; i < desired_speed; i++) calf_quadricep_motor->setSpeed(i); // contract the muscles at desired speed
  delay(millisec); // motion limited by amount of time
  for (int i = 0; i < desired_speed; i++) calf_quadricep_motor->setSpeed(0); // stops the contraction of the muscles at desired speed

  tibialis_hamstring_motor ->run(CONTRACT_TIBIALIS); // set motor direction to contract the tibialis muscles
  for (int i = 0; i < desired_speed; i++) tibialis_hamstring_motor ->setSpeed(i); // contract the muscles at desired speed
  delay(millisec / 2); // motion limited by amount of time
  for (int i = 0; i < desired_speed; i++) tibialis_hamstring_motor ->setSpeed(0); // stops the contraction of the muscles at desired speed
}

/*
  stand():
  param: int millisec - specifies the amount of time tensegrity structure has to stand up
         int desired_speed - the motors at this desired_speed make the tensegrity structure stand up
  Description: This function will have both tibialis_hamstring_motor and the calf_quadricep_motor release but one will release at a slower rate in that amount of time.
*/
void stand(int millisec, int desired_speed) {
  Serial.print("calf_quadricep_motor and tibialis_hamstring_motor releasing/n ");
  // Step 1: Releasing tibialis and hamstring motors
  tibialis_hamstring_motor ->run(RELEASE_TIBIALIS); // set motor direction to contract the calf muscles
  for (int i = 0; i < desired_speed; i++) tibialis_hamstring_motor ->setSpeed(i); // contract the muscles at desired speed
  delay(millisec / 2); // motion limited by amount of time
  for (int i = 0; i < desired_speed; i++) tibialis_hamstring_motor ->setSpeed(0); // stops the contractions of the muscles at desired speed
  // Step 2: Releasing calf and quadricep motors
  calf_quadricep_motor->run(RELEASE_CALF); // set motor direction to contract the tibialis muscles
  for (int i = 0; i < desired_speed; i++) calf_quadricep_motor->setSpeed(i); // contract the muscles at desired speed
  delay(millisec); // motion limited by amount of time
  for (int i = 0; i < desired_speed; i++) calf_quadricep_motor->setSpeed(0); // stops the contractions of the muscles at desired speed
}

// ================== SETUP FUNCTION ===========================
/* setup()
   Description: This function turns on or activates any necessary libraries for the main part
                of the code to properly compile and run.
*/
void setup() {
  Serial.begin(9600); //Set the baud rate for serial communication
  Serial.print("REV 5 Open Loop\n"); //Inform user that program has been loaded
  AFMS.begin(); // Start up motorshield
}

// ================== MAIN LOOP FUNCTIONS ===========================
void loop() {
  /*if there is data in the serial transmit side, read and process it */
  if (Serial.available() > 0) {
    /*parse through the transmit side string */
    input              = Serial.readString();
    commaIndex         = input.indexOf(',');
    String firstValue  = input.substring(0, commaIndex);
    String secondValue = input.substring(commaIndex + 1);

    /*set the desired motor and the desired speed */
    command      = firstValue[0];
    desired_speed      = secondValue.toInt();

    /*switch statement covering all hotkey cases */
    switch (command) {
      case 's': //HOTKEY = s, starts the squat
        squat(4000, 90); // calls squat(int millisec, int desired_speed)
        stand(3000, 90); // calls stand(int millisec, int desired_speed)
        break;
      case 'x': //HOTKEY = x, stop all motor activity
        Serial.print("Stop: ");
        tibialis_hamstring_motor->run(BRAKE);
        tibialis_hamstring_motor->setSpeed(0);
        calf_quadricep_motor->run(BRAKE);
        calf_quadricep_motor->setSpeed(0);
        delay(5);
        break;
      default:
        break;
    }
  }

}

