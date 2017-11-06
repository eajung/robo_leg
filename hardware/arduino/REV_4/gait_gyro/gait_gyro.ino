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
// Motor libraries
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
// Gyroscope libraries 
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
//-----------------------------------------------------

/*
 * Define any global or set variables
 */
#define ILIOPSOAS_MOTOR_NUMBER 1
#define GLUTE_MOTOR_NUMBER 2
#define HAMSTRING_MOTOR_NUMBER 3
#define BNO055_SAMPLERATE_DELAY_MS (100) /* Set the delay between fresh samples */

int button_state = 0;
int target_theta = 40;
int i;
String input;
char command;
//-----------------------------------------------------
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
Adafruit_DCMotor *iliopsoas_motor = AFMS.getMotor(ILIOPSOAS_MOTOR_NUMBER);  //hip flex forward motor
Adafruit_DCMotor *gluteus_motor = AFMS.getMotor(GLUTE_MOTOR_NUMBER);  //hip flex rear motor
Adafruit_DCMotor *hamstring_motor = AFMS.getMotor(HAMSTRING_MOTOR_NUMBER); // knee flex backwards motor

// Creating instances of BNO055
Adafruit_BNO055 lower_leg_tracker = Adafruit_BNO055(55);

//=====BEGIN HELPER FUNCTIONS=======================================================
/* Helper functions to make the main code look cleaner:
 * increase_motor_speed, decrease_motor_speed, etc.
 */
//====INCREASE MOTOR SPEED==========================================================
void increase_motor_speed(int motor_number, uint8_t motor_direction_f,
                          uint8_t motor_direction_b, int motor_speed) { //( direction, motor)
  switch(motor_number){
    case ILIOPSOAS_MOTOR_NUMBER:
//      Serial.print("hip flex forward");
      iliopsoas_motor->run(motor_direction_f); //FORWARD, then backward 
      gluteus_motor->run(motor_direction_b);//BACKWARD, then forward  <------------SAME DIRECTION NOW
      hamstring_motor->run(motor_direction_f); // mimic the back to slowly release hamstring
      
//      Serial.print("increasing motor speed");
      for(i=0;i<motor_speed;i++){
       iliopsoas_motor->setSpeed(i*1.2); //front hip motor pulls forward. 
       //IF YOU CALL FORWARD FLEXION, REDUCE SPEED OF REAR
       gluteus_motor->setSpeed(i*.30); //rear hip motor releases simultaneously with front x2 to increase speed
       //run to is slowly enxtend knee forward will flexing hip
       hamstring_motor->setSpeed(i*.70);
       
       //delay(5);  
      }
      break;   
    
    case GLUTE_MOTOR_NUMBER:
//      Serial.print("hip flex backwards");
      gluteus_motor->run(motor_direction_b);  //fix later
      iliopsoas_motor->run(motor_direction_f);  //fix later

      //slowly run hip motor to lightly tight cable
      hamstring_motor->run(motor_direction_f);//same as front hip
//      Serial.print("increasing motor speed");
      for(i=0;i<motor_speed;i++){
        //IF YOU CALL FORWARD FLEXION, REDUCE SPEED OF FRONT
       iliopsoas_motor->setSpeed(i*.40);//new
       hamstring_motor->setSpeed(i*.65);
       gluteus_motor->setSpeed(i);
       
      // delay(5);
       
      }
      break;
    
    case HAMSTRING_MOTOR_NUMBER:
//      Serial.print("knee flex backwards");
      hamstring_motor->run(motor_direction_f); //fix later
//      Serial.print("increasing motor speed");
      for(i=0;i<motor_speed;i++){
       hamstring_motor->setSpeed(i*.80); //new just need to be i, 255 is max value and it will reach there afterwards
       delay(5);
      }
      break;
      
    default:
      break;
    
  }//end of switch
}//end of increase_motor_speed------------------------------------------


//====DECREASE MOTOR SPEED==============================================
//motor speed ranges from 0-255
void decrease_motor_speed(int motor_number, uint8_t motor_direction) { 
    switch(motor_number){
    case ILIOPSOAS_MOTOR_NUMBER:
    //CHECK TO SEE IF MOTOR DIRECTION HERE MATTERS
      iliopsoas_motor->run(motor_direction);
//      Serial.print("decreasing front hip motor speed");
      for(i=10; i!=0; i--){
      	iliopsoas_motor->setSpeed(i);
      	gluteus_motor->setSpeed(i); //IF YOU CALL FORWARD FLEXION, REDUCE SPEED OF REAR
      	delay(5);
      }
      break;
    
    case GLUTE_MOTOR_NUMBER:
      gluteus_motor->run(motor_direction);
//      Serial.print("decreasing back hip motor speed");
      for(i=10; i!=0; i--) {
      	//new addition
      	iliopsoas_motor->setSpeed(i); // IF YOU CALL BACKWARD FLEXION, REDUCE SPEED OF FRONT MOTOR   
      	gluteus_motor->setSpeed(i);
      	hamstring_motor->setSpeed(i);      
      	delay(5);
      }
      break;
    case HAMSTRING_MOTOR_NUMBER:
      hamstring_motor->run(motor_direction);
//      Serial.print("decreasing hamstring motor speed");
      for(i=10; i!=0; i--) {
      	iliopsoas_motor->setSpeed(i); // IF YOU CALL BACKWARD FLEXION, REDUCE SPEED OF FRONT MOTOR   
      	gluteus_motor->setSpeed(i); 
      	hamstring_motor->setSpeed(i);
      	delay(5);
      }
      break;
  }//end of switch
}//end of decrease_motor_speed()--------------------------------------

//==FLEX=KNEE============================================================================
void knee_flex(uint8_t motor_direction_f, uint8_t motor_direction_b, int speed){
  Serial.println("Flexing knee backwards");
  increase_motor_speed(HAMSTRING_MOTOR_NUMBER, motor_direction_f, motor_direction_b, speed);
//  decrease_motor_speed(HAMSTRING_MOTOR_NUMBER, motor_direction_f);
}//end of knee_flex----------------------------------------------------------------------

//==STOP MOTION==========================================================================
void stop_motion() {
	iliopsoas_motor->run(BRAKE);
	iliopsoas_motor->setSpeed(0);
	gluteus_motor->run(BRAKE);
	gluteus_motor->setSpeed(0);
	hamstring_motor->run(BRAKE);
	hamstring_motor->setSpeed(0);
}

//====END OF HELPER FUNCTIONS==============================================

//====SETUP===================================================
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  if(!lower_leg_tracker.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  lower_leg_tracker.setExtCrystalUse(true);
  
//  pinMode(BUTTON, INPUT); // initialize the switch pin as an input
  //digitalWrite(button_pin, High); //Turn on Internal pull-up 

  Serial.println("Setup complete.");
}

void loop() {
	if (Serial.available() > 0) {
		input = Serial.readString();
    command = input[0];
		switch (command) {
			case 's': //s for start
				Serial.print("Starting leg motion.");
				knee_flex(FORWARD, BACKWARD, 120);
				break;
			case 'x': // x for exit
				Serial.println("Stopping all motion.");
				stop_motion();
				break;
		}
	}

	/* Get a new sensor event */
    sensors_event_t event;
    lower_leg_tracker.getEvent(&event);
    if (event.orientation.x >= target_theta) {
    	stop_motion();
    }
   Serial.print(event.orientation.x, 4);
   Serial.print("\tY: ");
   Serial.print(event.orientation.y, 4);
   Serial.print("\tZ: ");
   Serial.println(event.orientation.z, 4); 
   delay(BNO055_SAMPLERATE_DELAY_MS);

}




