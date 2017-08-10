/*
 * File name: Knee_motor_program_2
 * Author: Erik Jung
 * Comments: This is a force controlled motion of the flexural knee tensegrity structure.
 * As the hamstring is pulled, the tension grows exponentially to a defined maximum tension.
 * From there once the structure reaches the set tension, it releases back to the original non-flexed state.
 */

/* 
 * Include all libraries needed to properly run program
 * Sketch -> Include Library -> Manage Libraries
 */
// ------------------------------------------------------
#include <math.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <stdio.h>
#include "Timer.h"
#include "utility/Adafruit_MS_PWMServoDriver.h"



// ------------------------------------------------------

/*
 * Define any global or set variables
 */
#define FORCERESISTOR 10000 // value of the resistor in the circuit for calculating force
#define THERMISTORPIN A0 // the pin to connect the sensor 
#define STARTPOSITION 0
#define PEAKFLEXIONSTATE 1
#define UNFLEXSTATE 2
#define HAMSTRING_MOTOR 3


const int button_pin = 2; // the number of the switch pin
int button_state = 0; // this will change based on the state of the push button status
int flexed_state = 0; // tells us if the leg has flexed
uint8_t i; 
unsigned long time; // time might be used by the delay()
//float fact; // dependent on the voltage 
float stretchcord_reading; // analog reading for the stretch sensor
float maximum_tension = 2.7; // software set maximum tension in cables compared to the stretchcord_reading
float fully_flexed_angle_tension = 2.2;
float taut_tension = 1.4; // software set tension for when the leg is back to being taught
float force; // force calcuation based off of the stretchcord_reading

int counter = 0;
//float distance = 3200;
float fact = 1.0; // 6V

//For the timer
Timer t;

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




//=================================================================
/* Helper functions to make the main code look cleaner:
 * increase, decrease, etc.
 */
//=================================================================
void increase_motor_speed(int motor_number, uint8_t motor_direction, int motor_speed) { //( direction, motor)
  switch(motor_number){
    case 1:
      Serial.print("hip flex forward");
      f_hip_motor->run(motor_direction);
      Serial.print("increasing motor speed");
      for(i=0;i<motor_speed;i++){
       f_hip_motor->setSpeed(i);
       delay(5);
       
      }
      break;   
    
    case 2:
      Serial.print("hip flex backwards");
      b_hip_motor->run(motor_direction);
      Serial.print("increasing motor speed");
      for(i=0;i<motor_speed;i++){
       b_hip_motor->setSpeed(i);
       delay(5);
       
      }
      break;
    
    case 3:
      Serial.print("knee flex backwards");
      hamstring_motor->run(motor_direction);
      Serial.print("increasing motor speed");
      for(i=0;i<motor_speed;i++){
       hamstring_motor->setSpeed(i);
       delay(5);
       
      }
      break;
    default:
      break;
     
    
  }//end of switch

  
  
}//end of increase_motor_speed

//=================================================================
//=================================================================
//motor speed ranges from 0-255
void decrease_motor_speed(int motor_number, uint8_t motor_direction) { 
    switch(motor_number){
    case 1:
      f_hip_motor->run(motor_direction);
      Serial.print("decreasing front hip motor speed");
      for(i=100; i!=0; i--){
       f_hip_motor->setSpeed(i);
       delay(5);
       
      }
      break;   
    case 2:
      b_hip_motor->run(motor_direction);
      Serial.print("decreasing back hip motor speed");
      for(i=100; i!=0; i--){
       b_hip_motor->setSpeed(i);
       delay(5);
       
      }
      break;
    case 3:
      hamstring_motor->run(motor_direction);
      Serial.print("decreasing hamstring motor speed");
      for(i=100; i!=0; i--){
       hamstring_motor->setSpeed(i);
       delay(5);
       
      }
      break;
    
  }//end of switch
  
}//end of decrease_motor_speed()


//===FLEX=HIP=========================================================
//distance,direction, motor
//(1=>forward, 2=>backwards)
void hip_flex(int distance, int motor_number, uint8_t motor_direction, int motor_speed){  //40% motorspeed
  Serial.println("Flexing hip");
  increase_motor_speed(motor_number,motor_direction,motor_speed);
  delay(distance*fact);
  decrease_motor_speed(motor_number,motor_direction);
   
}

//Seperate rear motor function for test and running at different motor speeds, this one is at 100%
void hip_flex_b(int distance, int motor_number, uint8_t motor_direction, int motor_speed){  
  Serial.println("Flexing hip");
  increase_motor_speed(motor_number,motor_direction,motor_speed);//run rear motor to maximum capacity
  delay(distance*fact);
  decrease_motor_speed(motor_number,motor_direction);
   
}


//==FLEX=KNEE=========================================================

//flex=only=backwards=======
void knee_flex(int distance, uint8_t motor_direction){
  Serial.println("Flexing knee backwards");
  increase_motor_speed(motor_direction,HAMSTRING_MOTOR,100);
  delay(distance*fact);
 
}

//====SETUP===================================================

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  Serial.println("KNEE Motion Program!");

// initialize control over the keyboard:
//  Keyboard.begin();
  
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  
 
  hamstring_motor->setSpeed(0); // Set the speed to start, from 0 (off) to 255 (max speed)
  hamstring_motor->run(FORWARD);
  hamstring_motor->run(RELEASE); // turn on motor
 
  pinMode(button_pin, INPUT); // initialize the switch pin as an input
  //digitalWrite(button_pin, High); //Turn on Internal pull-up 
}


//==LOOP======================================================
//============================================================
// Put your main code here to run repeatedly:
void loop() {
  
  //Time function
  time = millis(); //print time since started in milliseconds
  delay(10); //refreashing time constant
  
  button_state = digitalRead(button_pin); // read the state of the switch value

  //Algorithm for GAIT
  if (button_state == HIGH) {
  //    Serial.print("Knee Flexion\n");
   // hamstring_motor->run(FORWARD);


    hip_flex_b(7000, 2, BACKWARD,255);//rear cable release
    delay(10);  // need to make both run at the same time
    
    //Start by raising hip forward
    hip_flex(4500, 1, FORWARD,100);  //pull front cable
    delay(10);

    hip_flex(3000, 1, BACKWARD,100); //release front cable

    hip_flex_b(7000, 2, FORWARD,255);//rear cable tigten
    delay(10);  // need to make both run at the same time


    
       
    
  }//end of button_state if



  
}//===================end of loop , END OF PROGRAM=================================







