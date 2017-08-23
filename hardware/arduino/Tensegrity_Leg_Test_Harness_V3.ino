#include <Adafruit_MotorShield.h>
#include <stdio.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

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

void setup() {
  Serial.begin(9600);
  Serial.print("Power On. Begin Test.\n");
  AFMS.begin();
}

  String input;
  int    commaIndex;
  char   desired_Motor;
  int    desired_Speed;

void loop() {
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
    }                                 //end of switch
  }                                   //end of if
  
}

