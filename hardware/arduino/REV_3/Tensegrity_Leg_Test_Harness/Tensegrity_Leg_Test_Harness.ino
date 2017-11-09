/*This program is for testing the motors on the tensegrity flexural joint by individually controlling every motor
 * With different hotkeys. Moreover, each motor can be set at a particular speed. Note that there is a small delay
 * with pressing return in the Serial TX side and the motors following through.
 * 
 * The format for the transmission is as follows:
 * desired_Motor,speed with NO spaces!
 * 
 * The hotkeys for the motors are as follows:
 * f: hip motor forward
 * b: hip motor backward
 * g: rear hip motor forward
 * n: rear hip motor backward
 * h: hamstring motor forward
 * m: hamstring motor backward
 * 
 * The speeds for the motors can range from 0 to 255.
 * 
 * Lastly, the s hotkey at any point will cease all motor activity
 * and the a hotkey will print out the current gyro reading.
 */
 
//Print libraries
#include <stdio.h>
//Motor libraries
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
//Gyroscope libraries 
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
/* 
 * Create the motor shield object with the default I2C address
 * Or, create it with a different I2C address (say for stacking) 
 * Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);
 */
Adafruit_MotorShield AFMS         = Adafruit_MotorShield(); 
/*
 * Select which 'port' M1, M2, M3, or M4. This is M1
 */
//Creating instances of motor
Adafruit_DCMotor *f_hip_motor     = AFMS.getMotor(1); //hip flex forward motor
Adafruit_DCMotor *b_hip_motor     = AFMS.getMotor(2); //hip flex rear motor
Adafruit_DCMotor *hamstring_motor = AFMS.getMotor(3); //knee flex backwards motor

// Set delay between fresh samples
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055();

void setup() {
  Serial.begin(9600); //Set the baud rate
  Serial.print("Power On. Begin Test.\n"); //Inform user that test is starting
  AFMS.begin(); //begin

  Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  /* Display the current temperature */
  int8_t temp = bno.getTemp();
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println("");

  bno.setExtCrystalUse(true);

  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");
}

  String input;
  int    commaIndex;
  char   desired_Motor;
  int    desired_Speed;

void loop() {
  
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
  
  /*if there is data in the serial transmit side, read and process it */
  if (Serial.available() > 0) {

    /*parse through the transmit side string */
    input              = Serial.readString();
    commaIndex         = input.indexOf(',');
    String firstValue  = input.substring(0, commaIndex);
    String secondValue = input.substring(commaIndex+1);

    /*set the desired motor and the desired speed */
    desired_Motor      = firstValue[0];
    desired_Speed      = secondValue.toInt();

    /*switch statement covering all hotkey cases */
    switch (desired_Motor) {
      case 'f': //HOTKEY = f, move front hip forward
        Serial.print("Move front hip forward, ");
        Serial.println(desired_Speed);
        f_hip_motor->run(BACKWARD);
        for (int i = 0; i < desired_Speed; i++) {
          f_hip_motor->setSpeed(i);
        }
        delay(5);
        break;
      case 'b': //HOTKEY = b, move front hip backward
        Serial.print("Move front hip backward, ");
        Serial.println(desired_Speed);
        f_hip_motor->run(FORWARD);
        for(int i = 0; i < desired_Speed; i++) {
          f_hip_motor->setSpeed(i);
        }
        delay(5);
        break;
      case 'g': //HOTKEY = g, move rear hip forward
        Serial.print("Move back hip forward, ");
        Serial.println(desired_Speed);
        b_hip_motor->run(FORWARD);
        for(int i = 0; i < desired_Speed; i++) {
          b_hip_motor->setSpeed(i);
        }
        delay(5);
        break;
      case 'n': //HOTKEY = n, move rear hip backward
        Serial.print("Move back hip backward, ");
        Serial.println(desired_Speed);
        b_hip_motor->run(BACKWARD);
        for(int i = 0; i < desired_Speed; i++) {
          b_hip_motor->setSpeed(i);
        }
        delay(5);
        break;
      case 'h': //HOTKEY = h, move hamstring forward
        Serial.print("Move hamstring forward, ");
        Serial.println(desired_Speed);
        hamstring_motor->run(FORWARD);
        for(int i = 0; i < desired_Speed; i++) {
          hamstring_motor->setSpeed(i);
        }
        delay(5);
        break;
      case 'm': //HOTKEY = m, move hamstring backward
        Serial.print("Move hamstring backward, ");
        Serial.println(desired_Speed);
        hamstring_motor->run(BACKWARD);
        for(int i = 0; i < desired_Speed; i++) {
          hamstring_motor->setSpeed(i);
        }
        delay(5);
        break;
      case 's': //HOTKEY = s, stop all motor activity
        Serial.print("Stop\n");
        f_hip_motor->run(BRAKE);
        f_hip_motor->setSpeed(0);
        b_hip_motor->run(BRAKE);
        b_hip_motor->setSpeed(0);
        hamstring_motor->run(BRAKE);
        hamstring_motor->setSpeed(0);
        delay(5);
        break;
      case 'a': //HOTKEY = a, print gyro information
        /* Display the floating point data */
        Serial.print("X: ");
        Serial.print(euler.x());
        Serial.print(" Y: ");
        Serial.print(euler.y());
        Serial.print(" Z: ");
        Serial.print(euler.z());
        Serial.print("\t\t");
    }                                 //end of switch
  }                                   //end of if
  
  delay(BNO055_SAMPLERATE_DELAY_MS);
}

