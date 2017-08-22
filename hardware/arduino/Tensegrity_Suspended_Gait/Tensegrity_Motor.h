/*
  File name: Tensegrity_Motor.h 
  Author: Erik Jung
  Comments: Library for Tensegrity Motor Control
*/
#ifndef Tensegrity_Motor_h
#define Tensegrity_Motor_h

#include "Tensegrity_Motor.h"
#include "Arduino.h"
#include <Adafruit_MotorShield.h>

#define MAX_MOTOR_SPEED 100
#define FRONT_HIP_MOTOR_NUMBER 1
#define BACK_HIP_MOTOR_NUMBER 2
#define HAMSTRING_MOTOR_NUMBER 3

class Tensegrity_Motor
{
	public:
		Tensegrity_Motor();
		void increase_motor_speed(int motor_number, uint8_t motor_direction, int motor_speed);
		void decrease_motor_speed(int motor_number, uint8_t motor_direction, int motor_speed);
		void hip_flex(int distance, int motor_speed);
		void hip_unflex(int distance, int motor_speed);
		void knee_flex(int distance, int motor_speed);
		void knee_unflex(int distance, int motor_speed);
};

#endif