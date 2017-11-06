// Print libraries
#include <stdio.h>
// Motor libraries
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
// Gyroscope libraries 
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
  Serial.begin(9600);
  Serial.print("Power On. Begin Test.\n");
  AFMS.begin();

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

  if (Serial.available() > 0) {

    input              = Serial.readString();
    commaIndex         = input.indexOf(',');
    String firstValue  = input.substring(0, commaIndex);
    String secondValue = input.substring(commaIndex+1);

    desired_Motor      = firstValue[0];
    desired_Speed      = secondValue.toInt();

    switch (desired_Motor) {
      case 'f':
        Serial.print("Move front hip forward, ");
        Serial.println(desired_Speed);
        f_hip_motor->run(BACKWARD);
        for (int i = 0; i < desired_Speed; i++) {
          f_hip_motor->setSpeed(i);
        }
        delay(5);
        break;
      case 'b':
        Serial.print("Move front hip backward, ");
        Serial.println(desired_Speed);
        f_hip_motor->run(FORWARD);
        for(int i = 0; i < desired_Speed; i++) {
          f_hip_motor->setSpeed(i);
        }
        delay(5);
        break;
      case 'g':
        Serial.print("Move back hip forward, ");
        Serial.println(desired_Speed);
        b_hip_motor->run(FORWARD);
        for(int i = 0; i < desired_Speed; i++) {
          b_hip_motor->setSpeed(i);
        }
        delay(5);
        break;
      case 'n':
        Serial.print("Move back hip backward, ");
        Serial.println(desired_Speed);
        b_hip_motor->run(BACKWARD);
        for(int i = 0; i < desired_Speed; i++) {
          b_hip_motor->setSpeed(i);
        }
        delay(5);
        break;
      case 'h':
        Serial.print("Move hamstring forward, ");
        Serial.println(desired_Speed);
        hamstring_motor->run(FORWARD);
        for(int i = 0; i < desired_Speed; i++) {
          hamstring_motor->setSpeed(i);
        }
        delay(5);
        break;
      case 'm':
        Serial.print("Move hamstring backward, ");
        Serial.println(desired_Speed);
        hamstring_motor->run(BACKWARD);
        for(int i = 0; i < desired_Speed; i++) {
          hamstring_motor->setSpeed(i);
        }
        delay(5);
        break;
      case 's':
        Serial.print("Stop\n");
        f_hip_motor->run(BRAKE);
        f_hip_motor->setSpeed(0);
        b_hip_motor->run(BRAKE);
        b_hip_motor->setSpeed(0);
        hamstring_motor->run(BRAKE);
        hamstring_motor->setSpeed(0);
        delay(5);
        break;
      case 'a': //for angle
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

