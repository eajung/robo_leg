
/*This program is for testing the motors on the tensegrity flexural joint by individually controlling every motor
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

//Print libraries
#include <stdio.h>
//Motor libraries
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
//Gyroscope libraries
#include <Wire.h>
#include "Timer.h"

/*
   macro definitions and global variables
*/
#define RELEASE_TIBIALIS 1
#define CONTRACT_TIBIALIS 2
#define RELEASE_CALF 2
#define CONTRACT_CALF 1

String input;
int    commaIndex;
char   command;
int    desired_speed;
Timer t;

Adafruit_MotorShield AFMS         = Adafruit_MotorShield();
/*
   Select which 'port' M1, M2, M3, or M4. This is M1
*/
//Creating instances of motor
Adafruit_DCMotor *tibialis_hamstring_motor     = AFMS.getMotor(1); //hip flex forward motor
Adafruit_DCMotor *calf_quadricep_motor     = AFMS.getMotor(4); //hip flex rear motor


/*
    HELPER FUNCTIONS
*/
//squat():
//param: int millisec - specifies the amount of time tensegrity structure squats
//       int desired_speed - moves the motors at this desired_speed to move the tensigrity structure
//Description: This function will have both tibialis_hamstring_motor and the calf_quadricep_motor contract but one will contract at a slower rate in that amount of time.
void squat(int millisec, int desired_speed) {
  Serial.print("calf_quadricep_motor and tibialis_hamstring_motor contracts/n ");

  calf_quadricep_motor->run(RELEASE_CALF);
  for (int i = 0; i < desired_speed; i++) {
    calf_quadricep_motor->setSpeed(i);
  }
  delay(millisec);
  for (int i = 0; i < desired_speed; i++) {
    calf_quadricep_motor->setSpeed(0);

  }

  tibialis_hamstring_motor ->run(CONTRACT_TIBIALIS);
  for (int i = 0; i < desired_speed; i++) {
    tibialis_hamstring_motor ->setSpeed(i);
  }
  delay(millisec / 2);
  for (int i = 0; i < desired_speed; i++) {
    tibialis_hamstring_motor ->setSpeed(0);
  }





}


//stand():
//param: int millisec - specifies the amount of time tensegrity structure has to stand up
//       int desired_speed - the motors at this desired_speed make the tensegrity structure stand up
//Description: This function will have both tibialis_hamstring_motor and the calf_quadricep_motor release but one will release at a slower rate in that amount of time.
void stand(int millisec, int desired_speed) {

  tibialis_hamstring_motor ->run(RELEASE_TIBIALIS);
  for (int i = 0; i < desired_speed; i++) {
    tibialis_hamstring_motor ->setSpeed(i);
  }
  delay(millisec / 2);
  for (int i = 0; i < desired_speed; i++) {
    tibialis_hamstring_motor ->setSpeed(0);
  }

  calf_quadricep_motor->run(CONTRACT_CALF);
  for (int i = 0; i < desired_speed; i++) {
    calf_quadricep_motor->setSpeed(i);
  }
  delay(millisec);
  for (int i = 0; i < desired_speed; i++) {
    calf_quadricep_motor->setSpeed(0);
  }




  //



}


void setup() {
  Serial.begin(9600); //Set the baud rate
  Serial.print("Power On. Begin Test.\n"); //Inform user that test is starting
  AFMS.begin(); //begin
}

void loop() {

  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
  //comment this out
  // imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

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
      case 's': //HoTEKEY = s, starts the squat
        squat(4000, 90);
        stand(3000, 90);
        break;




      case 'x': //HOTKEY = x, stop all motor activity
        Serial.print("Stop: ");
        tibialis_hamstring_motor->run(BRAKE);
        tibialis_hamstring_motor->setSpeed(0);
        calf_quadricep_motor->run(BRAKE);
        calf_quadricep_motor->setSpeed(0);
        Serial.println(millis());
        delay(5);
        break;

      case 'p': //HOTKEY = p, print out the time
        Serial.println(millis());

        break;

    }
  }

}

