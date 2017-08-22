/*
  File name: Tensegrity_Motor.cpp
  Author: Erik Jung
  Comments: Library for Tensegrity Motor Control
*/


#include "Tensegrity_Motor.h"
#include "Arduino.h"
#include <Adafruit_MotorShield.h>
#include <math.h>
#include <Wire.h>
#include <stdio.h>

Tensegrity_Motor::Tensegrity_Motor() {
	 /* 
	 * Create the motor shield object with the default I2C address
	 * Or, create it with a different I2C address (say for stacking) 
	 * Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);
	 */
	Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
	/*
	 * Select which 'port' M1, M2, M3, or M4. This is M1
	 */
	//Creating instances of motor
  Adafruit_DCMotor *f_hip_motor = AFMS.getMotor(1);  //hip flex forward
  Adafruit_DCMotor *b_hip_motor = AFMS.getMotor(2);  //hip flex back
  Adafruit_DCMotor *hamstring_motor = AFMS.getMotor(3); // Knee Flexion motor, was (1)
}

void increase_motor_speed(int motor_number, uint8_t motor_direction, int motor_speed) {
  switch(motor_number) {
    case 1:
      f_hip_motor->run(motor_direction);

      // Increase the motor speed from 0% --> MAX_MOTOR_SPEED
      for (i=0; i<motor_speed; i++) {
        f_hip_motor->setSpeed(i);
        delay(5);
      }
      break;
    case 2:
      b_hip_motor->run(motor_direction);

      // Increase the motor speed from 0% --> MAX_MOTOR_SPEED
      for (i=0; i<motor_speed; i++) {
        b_hip_motor->setSpeed(i);
        delay(5);
      }
      break;
    case 3:
      hamstring_motor->run(motor_direction);

      // Increase the motor speed from 0% --> MAX_MOTOR_SPEED
      for (i=0; i<motor_speed; i++) {
        hamstring_motor->setSpeed(i);
        delay(5);
      }
      break;
    default:
      break;
  }
}

void decrease_motor_speed(int motor_number, uint8_t motor_direction, int motor_speed) {
  switch(motor_number) {
    case 1:
      f_hip_motor->run(motor_direction);

      // Increase the motor speed from 0% --> MAX_MOTOR_SPEED
      for (i=motor_speed; i!=0; i--) {
        f_hip_motor->setSpeed(i);
        delay(5);
      }
      break;
    case 2:
      b_hip_motor->run(motor_direction);

      // Increase the motor speed from 0% --> MAX_MOTOR_SPEED
      for (i=motor_speed; i!=0; i--) {
        b_hip_motor->setSpeed(i);
        delay(5);
      }
      break;
    case 3:
      hamstring_motor->run(motor_direction);

      // Increase the motor speed from 0% --> MAX_MOTOR_SPEED
      for (i=motor_speed; i!=0; i--) {
        hamstring_motor->setSpeed(i);
        delay(5);
      }
      break;
    default:
      break;
  }
}

void hip_flex(int distance, int motor_speed) {
  Serial.println("Flexing hip");

  increase_motor_speed(FRONT_HIP_MOTOR_NUMBER, FORWARD, motor_speed);
  delay(10);
  increase_motor_speed(BACK_HIP_MOTOR_NUMBER, BACKWARD, motor_speed*2.5);
  delay(distance);

  decrease_motor_speed(FRONT_HIP_MOTOR_NUMBER, FORWARD, motor_speed);
  delay(10);
  decrease_motor_speed(BACK_HIP_MOTOR_NUMBER, BACKWARD, motor_speed*2.5);
}

void hip_unflex(int distance, int motor_speed) {
  Serial.println("Unflexing hip");

  increase_motor_speed(FRONT_HIP_MOTOR_NUMBER, BACKWARD, motor_speed);
  delay(10);
  increase_motor_speed(BACK_HIP_MOTOR_NUMBER, FORWARD, motor_speed*2.5);
  delay(distance);

  decrease_motor_speed(FRONT_HIP_MOTOR_NUMBER, BACKWARD, motor_speed);
  delay(10);
  decrease_motor_speed(BACK_HIP_MOTOR_NUMBER, FORWARD, motor_speed*2.5);
}

void knee_flex(int distance, int motor_speed) {
  Serial.println("Flexing knee");

  increase_motor_speed(HAMSTRING_MOTOR_NUMBER, FORWARD, motor_speed);
  delay(10);
  increase_motor_speed(FRONT_HIP_MOTOR_NUMBER, FORWARD, motor_speed*0.5);
  delay(distance);

  decrease_motor_speed(HAMSTRING_MOTOR_NUMBER, FORWARD, motor_speed);
  delay(10);
  decrease_motor_speed(FRONT_HIP_MOTOR_NUMBER, FORWARD, motor_speed*0.5);
}

void knee_unflex(int distance, int motor_speed) {
  Serial.println("Unflexing knee");

  increase_motor_speed(HAMSTRING_MOTOR_NUMBER, BACKWARD, motor_speed);
  delay(10);
  increase_motor_speed(FRONT_HIP_MOTOR_NUMBER, BACKWARD, motor_speed*0.5);
  delay(distance);

  decrease_motor_speed(HAMSTRING_MOTOR_NUMBER, BACKWARD, motor_speed);
  delay(10);
  decrease_motor_speed(FRONT_HIP_MOTOR_NUMBER, BACKWARD, motor_speed*0.5);
}
