/* 
 * Include all libraries needed to properly run program
 * Sketch -> Include Library -> Manage Libraries
 */
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
Adafruit_DCMotor *hamstring_motor = AFMS.getMotor(3); // knee flex backwards motor


char input_String[20];     //String to contain characters
char input_Character = -1; //Where to store the character read
byte index           = 0;  //Index into array, where to store the caracter

void setup() {
  Serial.begin(9600);
  Serial.print("Power On. Begin Test.\n");
  AFMS.begin();
}

void loop() {

  char input;
  if (Serial.available() > 0) {
    input = Serial.read();
    Serial.println(input);
    if (input == 'f') {
      Serial.print("Move front hip forward\n");
      f_hip_motor->run(FORWARD);
      for(int i = 0; i < 100; i++) {
        f_hip_motor->setSpeed(i);
      }
      delay(10);
    }

    if (input == 'b') {
      Serial.print("Move front hip backward\n");
      f_hip_motor->run(BACKWARD);
      for(int i = 0; i < 100; i++) {
        f_hip_motor->setSpeed(i);
      }
      delay(10);
    }

    if (input == 'g') {
      Serial.print("Move back hip forward\n");
      b_hip_motor->run(FORWARD);
      for(int i = 0; i < 100; i++) {
        b_hip_motor->setSpeed(i);
      }
      delay(10);
    }

    if (input == 'n') {
      Serial.print("Move back hip backward\n");
      b_hip_motor->run(BACKWARD);
      for(int i = 0; i < 100; i++) {
        b_hip_motor->setSpeed(i);
      }
      delay(10);
    }

    if (input == 'h') {
      Serial.print("Move hamstring forward\n");
      hamstring_motor->run(FORWARD);
      for(int i = 0; i < 100; i++) {
        hamstring_motor->setSpeed(i);
      }
      delay(10);
    }

    if (input == 'm') {
      Serial.print("Move hamstring backward\n");
      hamstring_motor->run(BACKWARD);
      for(int i = 0; i < 100; i++) {
        hamstring_motor->setSpeed(i);
      }
      delay(10);
    }

    if (input == 's') {
      Serial.print("Stop\n");
      f_hip_motor->run(BRAKE);
      f_hip_motor->setSpeed(0);
      b_hip_motor->run(BRAKE);
      b_hip_motor->setSpeed(0);
      hamstring_motor->run(BRAKE);
      hamstring_motor->setSpeed(0);
      delay(10);
    }

    delay(10);
  }
}
