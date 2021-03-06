/*
* File name: gait_gyro.ino
* Author: Erik Jung
* Comments: This code will provide the basis for a closed-loop feedback system
* where the gyroscope acts as a sensor for positional feedback. Active tensile 
* components will adjust to achieve specific angles.
*/

//----------------------------------------------------- 
// Include all libraries needed to properly run program
// Sketch -> Include Library -> Manage Libraries

// Standard libraries
#include <stdio.h>
#include <stdbool.h>
// Motor libraries
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
// Gyroscope libraries 
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//-----------------------------------------------------

//Define any global or set variables
#define ILIOPSOAS_MOTOR_NUMBER 1
#define GLUTE_MOTOR_NUMBER 2
#define HAMSTRING_MOTOR_NUMBER 3
#define EQUILIBRIUM_STATE 0
#define HEEL_LIFT_STATE 1
#define EXTENSION_FORWARD_STATE 2
#define EXTENSION_FORWARD_STATE_PART_2 3
#define FOLLOW_THROUGH_STATE 4
#define RETURN_TO_EQUILIBRIUM_STATE 5
#define BNO055_SAMPLERATE_DELAY_MS 100 // Set the delay between fresh samples
sensors_event_t old_event;
int i, current_state, theta_direction;
float target_theta_x_low, target_theta_y_low, target_theta_z_low, target_theta_x_high, target_theta_y_high, target_theta_z_high;  
String input; // keyboard input
char command; // hotkey parsed from input
//-----------------------------------------------------

/* 
 * Create the motor shield object with the default I2C address
 * Or, create it with a different I2C address (say for stacking) 
 * Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);
 */
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

// Select which 'port' M1, M2, M3, or M4. This is M1
// Creating instances of motor
Adafruit_DCMotor *iliopsoas_motor = AFMS.getMotor(ILIOPSOAS_MOTOR_NUMBER); //hip flex forward motor
Adafruit_DCMotor *gluteus_motor = AFMS.getMotor(GLUTE_MOTOR_NUMBER); //hip flex rear motor
Adafruit_DCMotor *hamstring_motor = AFMS.getMotor(HAMSTRING_MOTOR_NUMBER); // knee flex backwards motor

// Creating instances of BNO055
Adafruit_BNO055 lower_leg_tracker = Adafruit_BNO055(55);

//=====BEGIN HELPER FUNCTIONS=======================================================
// Helper functions to make the main code look cleaner:
// increase_motor_speed, decrease_motor_speed, etc.

// range():
// Simple function that tells us if we're within the boundaries of what we expect our value to be within.
bool range(float min,float max,float i) {
  return min <= i  && i < max; 
}


// targeted_bounds():
// Returns true if the gyroscope is within the designated bounds set for the next stage
bool targeted_bounds(sensors_event_t event) {
  return ((range(target_theta_x_low, target_theta_x_high, event.orientation.x)) && 
          (range(target_theta_y_low, target_theta_x_high, event.orientation.y)) && 
          (range(target_theta_z_low, target_theta_z_high, event.orientation.z)));
}

// point_reached():
// By taking the readings from the gyroscope and the given current_state of our system, we return 
// true if the orientation of the gyroscope has reached the specified angles. 
bool point_reached(sensors_event_t event) {
  switch (current_state) {
    case HEEL_LIFT_STATE: // if we are in the heel lift state
      target_theta_x_low = 43.75; target_theta_x_high = 45;
      target_theta_y_low = -39.75; target_theta_y_high = -37.75;
      target_theta_z_low = 68.75; target_theta_z_high = 70;
      if (targeted_bounds(event)) {
        current_state = EXTENSION_FORWARD_STATE; // current state is now a different range
        return true;
      }
      break;
    case EXTENSION_FORWARD_STATE:
      target_theta_x_low = 30; target_theta_x_high = 32;
      target_theta_y_low = -78.1; target_theta_y_high = -77.75;
      target_theta_z_low = -77.8; target_theta_z_high = -77;
      if (targeted_bounds(event)) {
        current_state = EXTENSION_FORWARD_STATE_PART_2; // current state is now a different range
        return true;
      }
      break;
    case EXTENSION_FORWARD_STATE_PART_2:
      target_theta_x_low = 331.35; target_theta_x_high = 331.75;
      target_theta_y_low = -78.75; target_theta_y_high = -78.2;
      target_theta_z_low = -75.75; target_theta_z_high = -75.25;
      if (targeted_bounds(event)) {
        current_state = FOLLOW_THROUGH_STATE; // current state is now a different range
        return true;
      }
      break;
    case FOLLOW_THROUGH_STATE:
      target_theta_x_low = 18; target_theta_x_high = 20;
      target_theta_y_low = -58.5; target_theta_y_high = -56.5;
      target_theta_z_low = 86; target_theta_z_high = 88.5;
      if (targeted_bounds(event)) {
        current_state = EQUILIBRIUM_STATE; // current state is now a different range
        return true;
      }
      break;
    case RETURN_TO_EQUILIBRIUM_STATE:
      target_theta_x_low = 36; target_theta_x_high = 38;
      target_theta_y_low = -38; target_theta_y_high = -36;
      target_theta_z_low = 89; target_theta_z_high = 91;
      if (targeted_bounds(event)) {
        current_state = EQUILIBRIUM_STATE; // current state is now a different range
        return true;
      }
      break;
  }
  return false;
}

// direction_of_movement():
// This function takes the old event and compares it to the current event to dictate orientation 
int direction_of_movement(sensors_event_t event, sensors_event_t old_event) {
  if ((range(359,360, old_event.orientation.x)) || (range(0, 1, old_event.orientation.x))) { // if the range loops from 360 to 0 or 0 to 360 it's an odd case
    if (old_event.orientation.x - event.orientation.x > 0) return 1;
    else return -1;
  }
  else if (old_event.orientation.x - event.orientation.x < 0) return 1;
  else return -1;
}

// increase_motor_speed():
// Takes the specified active tensile element and the antagonistic pair will loosen as one contracts. 
void increase_motor_speed(int motor_number, uint8_t motor_direction_f,
                          uint8_t motor_direction_b, int motor_speed) {
  switch(motor_number) { // Specifies which motor we are actuating
    case ILIOPSOAS_MOTOR_NUMBER:
      iliopsoas_motor->run(motor_direction_f); //FORWARD, then backward 
      gluteus_motor->run(motor_direction_b);//BACKWARD, then forward
      hamstring_motor->run(motor_direction_f); // mimic the back to slowly release hamstring
      for (i = 0; i < motor_speed; i++) {
        iliopsoas_motor->setSpeed(i * 1.2); //front hip motor pulls forward. 
        gluteus_motor->setSpeed(i * .30); //rear hip motor releases simultaneously with front x2 to increase speed
        hamstring_motor->setSpeed(i * .70); //run to is slowly enxtend knee forward will flexing hip
        delay(5);
      }
      break;   
    
    case GLUTE_MOTOR_NUMBER:
      gluteus_motor->run(motor_direction_b);
      iliopsoas_motor->run(motor_direction_f); //slowly run hip motor to lightly tight cable
      hamstring_motor->run(motor_direction_f); //same as front hip
      for (i = 0; i < motor_speed; i++) {
        iliopsoas_motor->setSpeed(i * .40); //IF YOU CALL FORWARD FLEXION, REDUCE SPEED OF FRONT
        hamstring_motor->setSpeed(i * .65);
        gluteus_motor->setSpeed(i);
        delay(5);
      }
      break;
    
    case HAMSTRING_MOTOR_NUMBER:
      hamstring_motor->run(motor_direction_f);
      for (i = 0; i < motor_speed; i++) {
        hamstring_motor->setSpeed(i * .80);
        delay(5);
      }
      break;
      
    default:
      break;
    
  }
}

// decrease_motor_speed():
// Takes the specified active tensile element and decreases the current applied slowly to an eventual halt. 
void decrease_motor_speed(int motor_number, uint8_t motor_direction) { 
  iliopsoas_motor->run(motor_direction);
  gluteus_motor->run(motor_direction);
  hamstring_motor->run(motor_direction);
  for(i = 10; i != 0; i--) { // slowly discharge motors to stop
  	iliopsoas_motor->setSpeed(i);
  	gluteus_motor->setSpeed(i);
  	hamstring_motor->setSpeed(i);      
  	delay(5);
  }
}


// knee_flex():
// Flexes the knee backwards at a specified speed. 
void knee_flex(uint8_t motor_direction_f, uint8_t motor_direction_b, int speed) {
  Serial.println("Heel lift up.");
  increase_motor_speed(HAMSTRING_MOTOR_NUMBER, motor_direction_f, motor_direction_b, speed); // specifies the speed/direction pattern of active tensile elements
}

// extend_forward():
// Flexes the knee backwards at a specified speed. 
void extend_forward(uint8_t motor_direction_f, uint8_t motor_direction_b, int speed) {
  Serial.println("Extending leg forwards.");
  increase_motor_speed(ILIOPSOAS_MOTOR_NUMBER, motor_direction_f, motor_direction_b, speed); // specifies the speed/direction pattern of active tensile elements
}

// extend_forward_release():
// Flexes the knee backwards at a specified speed. 
void extend_forward_release(uint8_t motor_direction_f, uint8_t motor_direction_b, int speed) {
  Serial.println("Release hamstring.");
  increase_motor_speed(ILIOPSOAS_MOTOR_NUMBER, motor_direction_f, motor_direction_b, speed); // specifies the speed/direction pattern of active tensile elements
}

// follow_through():
// Flexes the knee backwards at a specified speed. 
void follow_through(uint8_t motor_direction_f, uint8_t motor_direction_b, int speed) {
  Serial.println("Stepping through.");
  increase_motor_speed(ILIOPSOAS_MOTOR_NUMBER, motor_direction_f, motor_direction_b, speed); // specifies the speed/direction pattern of active tensile elements
}

// return_equilibrium():
// Flexes the knee backwards at a specified speed. 
void return_equilibrium(uint8_t motor_direction_f, uint8_t motor_direction_b, int speed) {
  Serial.println("Return to beginning.");
  increase_motor_speed(ILIOPSOAS_MOTOR_NUMBER, motor_direction_f, motor_direction_b, speed); // specifies the speed/direction pattern of active tensile elements
}

// stop_motion():
// Stops all active tensile elements. 
void stop_motion() {
	iliopsoas_motor->run(BRAKE); // Halt the Iliopsoas active tensile element
	iliopsoas_motor->setSpeed(0);
	gluteus_motor->run(BRAKE); // Halt the Gluteus active tensile element
	gluteus_motor->setSpeed(0);
	hamstring_motor->run(BRAKE); // Halt the Hamstring active tensile element
	hamstring_motor->setSpeed(0);
  delay(100); // discharge all current through motors
}

//====END OF HELPER FUNCTIONS==============================================

//====SETUP===================================================
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  if(!lower_leg_tracker.begin()) {
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!"); // There was a problem detecting the BNO055 ... check your connections
    while(1);
  }
  
  lower_leg_tracker.setExtCrystalUse(true);
  
  current_state = EQUILIBRIUM_STATE; // Starting from equilibrium

  Serial.println("Setup complete.");
}

void loop() {
  /* Get a new sensor event */
  sensors_event_t event;
  lower_leg_tracker.getEvent(&event);

	if (Serial.available() > 0) { // if serial input is ready to read input
		input = Serial.readString();
    command = input[0];
		switch (command) {
			case 's': //s for start
				Serial.print("Starting leg motion.");
        current_state = HEEL_LIFT_STATE;
				knee_flex(FORWARD, BACKWARD, 120);
				break;
			case 'x': // x for exit
				Serial.println("Stopping all motion.");
				stop_motion();
				break;
      case 'p':
        Serial.print(event.orientation.x, 4);
        Serial.print("\tY: ");
        Serial.print(event.orientation.y, 4);
        Serial.print("\tZ: ");
        Serial.println(event.orientation.z, 4); 
        break;
		}
	}

  switch (current_state) {
    case HEEL_LIFT_STATE:
      if (point_reached(event)) {
        stop_motion();
        extend_forward(BACKWARD, FORWARD, 200);
      }
      break;
    case EXTENSION_FORWARD_STATE:
      if (point_reached(event)) {
        stop_motion();
        // extend_forward_release(BACKWARD, FORWARD, 200);
      }
      break;
    case EXTENSION_FORWARD_STATE_PART_2:
      if (point_reached(event)) {
        stop_motion();
        follow_through(BACKWARD, FORWARD, 200);
      }
      break;
    case FOLLOW_THROUGH_STATE:
      if (point_reached(event)) {
        stop_motion();
        return_equilibrium(BACKWARD, FORWARD, 200);
      }
      break;
    case RETURN_TO_EQUILIBRIUM_STATE:
      if (point_reached(event)) {
        stop_motion();
      }
      break;
  }

//   Constantly print out the gyroscopic readings from the BNO055
//   Serial.print(event.orientation.x, 4);
//   Serial.print("\tY: ");
//   Serial.print(event.orientation.y, 4);
//   Serial.print("\tZ: ");
//   Serial.println(event.orientation.z, 4); 
  old_event = event;
  delay(BNO055_SAMPLERATE_DELAY_MS);
}




