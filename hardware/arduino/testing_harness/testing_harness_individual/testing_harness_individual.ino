
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


Adafruit_MotorShield AFMS         = Adafruit_MotorShield();
/*
   Select which 'port' M1, M2, M3, or M4. This is M1
*/
//Creating instances of motor
Adafruit_DCMotor *tibialis_hamstring_motor     = AFMS.getMotor(1); //hip flex forward motor
Adafruit_DCMotor *calf_quadricep_motor     = AFMS.getMotor(4); //hip flex rear motor

void setup() {
  Serial.begin(9600); //Set the baud rate
  Serial.print("Power On. Begin Test.\n"); //Inform user that test is starting
  AFMS.begin(); //begin
}

String input;
int    commaIndex;
char   command;
int    desired_Speed;
Timer t;

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
    desired_Speed      = secondValue.toInt();

    /*switch statement covering all hotkey cases */
    switch (command) {

      case 't': //HOTKEY = t, move tibialis_hamstring_motor backward and contracts
        Serial.print("Move tibialis_hamstring_motor contracts: ");
        Serial.println(millis());
        //Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(BACKWARD);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i);
        }
        delay(5);
        break;

      case 'h': //HOTKEY = h, move tibialis_hamstring_motor forward and releases
        Serial.print("Move tibialis_hamstring_motor releases: ");
        Serial.println(millis());
       // Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(FORWARD);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i);
        }
        delay(5);
        break;

      case 'c': //HOTKEY = c, move calf_quadricep_motor forward (contract)
        Serial.print("Move calf_quadricep_motor contracts: ");
        Serial.println(millis());
        //Serial.println(desired_Speed);
        calf_quadricep_motor->run(FORWARD);
        for (int i = 0; i < desired_Speed; i++) {
          calf_quadricep_motor->setSpeed(i);
        }
        delay(5);
        break;

      case 'q': //HOTKEY = q, move calf_quadricep_motor backward (releases)
        Serial.print("Move calf_quadricep_motor releases: ");
         Serial.println(millis());
       // Serial.println(desired_Speed);
        calf_quadricep_motor->run(BACKWARD);
        for (int i = 0; i < desired_Speed; i++) {
          calf_quadricep_motor->setSpeed(i);
        }
        delay(5);
        break;

      case 'f': //HOTKEY = f, move tibialis_hamstring_motor forward and calf_quadricep_motor forward - contracts
        Serial.print("both tibialis_hamstring_motor and calf_quadricep_motor contracts: ");
         Serial.println(millis());
        //Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(FORWARD);
        calf_quadricep_motor->run(FORWARD);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i);
          calf_quadricep_motor->setSpeed(i / 2);
        }
        delay(5);
        break;
      case 'b': //HOTKEY = b, move tibialis_hamstring_motor backward and calf_quadricep_motor backward - releases
        Serial.print("Both tibialis_hamstring_motor and calf_quadricep_motor releases: ");
         Serial.println(millis());
        //Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(BACKWARD);
        calf_quadricep_motor->run(BACKWARD);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i / 2);
          calf_quadricep_motor->setSpeed(i);
        }
        delay(5);
        break;

      case 'a': //HOTKEY = i, move tibialis_hamstring_motor forward (contract) and calf_quadricep_motor backward (release)
        Serial.print(" tibialis_hamstring_motor contracts and calf_quadricep_motor releases: ");
        Serial.println(millis());
       // Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(FORWARD);
        calf_quadricep_motor->run(BACKWARD);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i);
          calf_quadricep_motor->setSpeed(i);
        }
        delay(5);
        break;
      case 'o': //HOTKEY = o, move tibialis_hamstring_motor backward (release) and calf_quadricep_motor forward (contract)
        Serial.print("tibialis_hamstring_motor releases and calf_quadricep_motor contracts: ");
        Serial.println(millis());
        //Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(BACKWARD);
        calf_quadricep_motor->run(FORWARD);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i);
          calf_quadricep_motor->setSpeed(i);
        }
        delay(5);
        break;

      //motors move forward at different speeds

      case 's': //HOTKEY = s, stop all motor activity
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

