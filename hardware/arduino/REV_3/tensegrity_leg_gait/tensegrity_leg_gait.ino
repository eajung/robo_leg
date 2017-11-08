/*
 * File name: tensegrity_leg_gait.ino
 * Authors: Erik Jung and Lawrence Ngo
 * Comments: This a tensegrity knee with newly add hip joint. The purpose of this design is to mimic
 *           human gait. At the moment, the design relies soley on timers for movement.
 */

 
///==========================================================================================================
//Current Version 8: 1 cycle of gait is completed once the button is pressed



/* 
 * Include all libraries needed to properly run program
 * Sketch -> Include Library -> Manage Libraries
 */
// ------------------------------------------------------
#include <math.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <stdio.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
// ------------------------------------------------------

/*
 * Define any global or set variables
 */
#define FORCERESISTOR 10000 // value of the resistor in the circuit for calculating force
#define THERMISTORPIN A0 // the pin to connect the sensor 
#define STARTPOSITION 0
#define PEAKFLEXIONSTATE 1
#define STATE1 1
#define STATE2 2
#define STATE3 3
#define STATE4 4
#define STATE5 5
#define STATE_FINISHED 6
#define UNFLEXSTATE 2
#define HAMSTRING_MOTOR 3
#define BNO055_SAMPLERATE_DELAY_MS (100) /* Set the delay between fresh samples */


int leg_state;
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
Adafruit_DCMotor *f_hip_motor = AFMS.getMotor(1);  //hip flex forward motor
Adafruit_DCMotor *b_hip_motor = AFMS.getMotor(2);  //hip flex rear motor
Adafruit_DCMotor *hamstring_motor = AFMS.getMotor(3); // knee flex backwards motor

Adafruit_BNO055 bno = Adafruit_BNO055(55);

//=================================================================
/* Helper functions to make the main code look cleaner:
 * increase, decrease, etc.
 */
//====INCREASE MOTOR SPEED==========================================================
/*
 * NOTE to user: When you see i*(some arbitrary value) just  know that the purpose of
 * that is to slow down the rate at which the motor increases its speed, but the 
 * motor will eventually reach it's maximum (the desired speed that the user passed to the 
 * increase_motor_speed(...)'s arguments.
*/
void increase_motor_speed(int motor_number, uint8_t motor_direction_f,
                          uint8_t motor_direction_b, int motor_speed) { //( direction, motor)
  switch(motor_number){

    //Flex Hip Forward
    //  Make sure to adjust the rear hip motor accordingly to match the speed of the front motor
    //  to avoid straining the motor
    case 1:
      Serial.print("hip flex forward");
      //The direction of spin depends on the orientation of the motors, either change
      // it here or manually change motor (at your discretion)
      f_hip_motor->run(motor_direction_f); //FORWARD, then backward 
      b_hip_motor->run(motor_direction_b); //BACKWARD, then forward  
      hamstring_motor->run(motor_direction_f); // mimic the Rear motor, by slowly releasing hamstring
      
      Serial.print("increasing motor speed");
      for(i=0;i<motor_speed;i++){
       f_hip_motor->setSpeed(i*1.2); //front hip motor pulls forward, adjust speed according to preference 
       b_hip_motor->setSpeed(i*.30); //rear hip motor releases simultaneously with front at 30% of the speed inputted
       hamstring_motor->setSpeed(i*.70);//run to slowly enxtend knee forward will flexing hip
       
       //delay(5);  
      }
      break;   
    
    //Flex Hip Backward
    //  Make sure to adjust the front hip motor accordingly to match the speed of the reart motor
    //  to avoid straining the motor
    case 2:
      Serial.print("hip flex backwards");
      b_hip_motor->run(motor_direction_b); //Adjust hip motor if it doesn't release properly
      f_hip_motor->run(motor_direction_f); // Rear motor should always be the opposite of the ront
      hamstring_motor->run(motor_direction_f);// Should be same direction as the front hip,
                                              // if not, then use the rear motors direction
                                              //NOTE: it just depends how the motor are set up.
                                              
      Serial.print("increasing motor speed");
      //IF YOU CALL BACKWARD FLEXION, REDUCE SPEED OF FRONT
      //to prevent from tangling messy cable release
        for(i=0;i<motor_speed;i++){
         f_hip_motor->setSpeed(i*.40);//new
         hamstring_motor->setSpeed(i*.65);
         b_hip_motor->setSpeed(i);
      }
      break;
    
    case 3:
    //Flex Just the Hamstring, Backwards
    //  Make sure to adjust the rear hip motor accordingly to match the speed of the front motor
    //  Make that front hip cable is taught, so just the hamstring will flex.
      Serial.print("knee flex backwards");
      hamstring_motor->run(motor_direction_f); 
      Serial.print("increasing motor speed");
      for(i=0;i<motor_speed;i++){
       hamstring_motor->setSpeed(i*.80);
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
    case 1:
    //CHECK TO SEE IF MOTOR DIRECTION HERE MATTERS
    //The direction to slow the motor down is the same as the 
    // direction passed in for the increase_motor_speed()
    // just refer to that.
      f_hip_motor->run(motor_direction);
      Serial.print("decreasing front hip motor speed");
      for(i=10; i!=0; i--){
       f_hip_motor->setSpeed(i);
       b_hip_motor->setSpeed(i); //IF YOU CALL FORWARD FLEXION, REDUCE SPEED OF REAR
       delay(5);
      }
      break;
    
    case 2:
      b_hip_motor->run(motor_direction);
      Serial.print("decreasing back hip motor speed");
      for(i=10; i!=0; i--){
       //new addition
       f_hip_motor->setSpeed(i); // IF YOU CALL BACKWARD FLEXION, REDUCE SPEED OF FRONT MOTOR   
       b_hip_motor->setSpeed(i);
       hamstring_motor->setSpeed(i);
       
       delay(5);
      }
      break;
    case 3:
      hamstring_motor->run(motor_direction);
      Serial.print("decreasing hamstring motor speed");
      for(i=10; i!=0; i--){
       f_hip_motor->setSpeed(i); // IF YOU CALL BACKWARD FLEXION, REDUCE SPEED OF FRONT MOTOR   
       b_hip_motor->setSpeed(i); 
       hamstring_motor->setSpeed(i);
       delay(5);
      }
      break;
  }//end of switch
}//end of decrease_motor_speed()--------------------------------------


//===FLEX=HIP=========================================================
//Enter Distance(duraction of motor run), desired motor, front motor direction,back motor direction, 0-255)
//(1=>forward, 2=>backwards)
void hip_flex(int distance, int motor_number, uint8_t motor_direction_f, uint8_t motor_direction_b, int motor_speed){ 
  
  Serial.println("Flexing hip");
  increase_motor_speed(motor_number,motor_direction_f, motor_direction_b,motor_speed); 
  delay(distance*fact);
  decrease_motor_speed(motor_number,motor_direction_f);
  decrease_motor_speed(3, motor_direction_b);
}
//==FLEX=KNEE============================================================================
void knee_flex(int distance, uint8_t motor_direction_f, uint8_t motor_direction_b){
  Serial.println("Flexing knee backwards");
//(int motor_number, uint8_t motor_direction_f, uint8_t motor_direction_b, int motor_speed)
  increase_motor_speed(3, motor_direction_f,motor_direction_b,120);
  delay(distance*fact);
  decrease_motor_speed(3, motor_direction_f);
}//end of knee_flex----------------------------------------------------------------------


//========HIP-Flex-forward-knee-in-place===============//
void knee_inplace(int distance, uint8_t motor_direction_f, uint8_t motor_direction_b, int motor_speed){
      f_hip_motor->run(motor_direction_f); 
      b_hip_motor->run(motor_direction_b); 
      for(i=0;i<motor_speed;i++){
       f_hip_motor->setSpeed(i*.70); //front hip motor pulls forward. 
       b_hip_motor->setSpeed(i*.25); //rear hip motor releases simultaneously with front x2 to increase speed
       //delay(5);
      }
      delay(5000); ///DELAY TO KEEP LEG KNEEING FORWARD 3:26PM
      for(i=100; i!=0; i--){
       //new addition
       f_hip_motor->setSpeed(i*.90); // IF YOU CALL BACKWARD FLEXION, REDUCE SPEED OF FRONT MOTOR   
       b_hip_motor->setSpeed(i*.85);
      // delay(5);
      }  
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
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  bno.setExtCrystalUse(true);
 
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
  sensors_event_t event;
  bno.getEvent(&event);
//---WALKING-GAIT-ALGORITHM-----------------------------------------------------------------
  if (button_state == HIGH) {
    leg_state = STATE1;
  }
    //====FIRST_STEP=====//
    //flex hamstring to bring knee slightly up
  //RETURN KNEE BACK TO NEUTRAL    
  if (leg_state == STATE5) {
    knee_flex(2700, BACKWARD, FORWARD);
    /* Get a new sensor event */
    Serial.print("X: ");
    Serial.print(event.orientation.x, 4);
    Serial.print("\tY: ");
    Serial.print(event.orientation.y, 4);
    Serial.print("\tZ: ");
    Serial.println(event.orientation.z, 4); 
    delay(BNO055_SAMPLERATE_DELAY_MS);
    leg_state = STATE_FINISHED;
  }

   // void knee_inplace(int distance, uint8_t motor_direction_f, uint8_t motor_direction_b, int motor_speed){
  if (leg_state == STATE4) {
    knee_inplace(40, BACKWARD,FORWARD,170);
    /* Get a new sensor event */
    Serial.print("X: ");
    Serial.print(event.orientation.x, 4);
    Serial.print("\tY: ");
    Serial.print(event.orientation.y, 4);
    Serial.print("\tZ: ");
    Serial.println(event.orientation.z, 4); 
    delay(BNO055_SAMPLERATE_DELAY_MS);
    leg_state = STATE5;
  }
  //====FOLLOW-THROUGH===//
  //    //bring leg back to neutral then past continue swinging back 
  if (leg_state == STATE3) {
    hip_flex(6000, 2, FORWARD, BACKWARD, 120); 
    /* Get a new sensor event */
    Serial.print("X: ");
    Serial.print(event.orientation.x, 4);
    Serial.print("\tY: ");
    Serial.print(event.orientation.y, 4);
    Serial.print("\tZ: ");
    Serial.println(event.orientation.z, 4); 
    delay(BNO055_SAMPLERATE_DELAY_MS); 
    leg_state = STATE4;
  }
  //bring hip forward
  //pull front cable  (distance, motor number, f_motor_direction, b_motor_direct, speed)
  if (leg_state == STATE2) {
    hip_flex(4000, 1, BACKWARD, FORWARD,200);  //ORGINALLY 4000 AND 4500 3:26PM
    /* Get a new sensor event */
    bno.getEvent(&event);
    Serial.print("X: ");
    Serial.print(event.orientation.x, 4);
    Serial.print("\tY: ");
    Serial.print(event.orientation.y, 4);
    Serial.print("\tZ: ");
    Serial.println(event.orientation.z, 4); 
    delay(BNO055_SAMPLERATE_DELAY_MS);
    leg_state = STATE3;
  }

  if (leg_state == STATE1) {
    knee_flex(4500, FORWARD, BACKWARD);
    /* Get a new sensor event */
  
    Serial.print("X: ");
    Serial.print(event.orientation.x, 4);
    Serial.print("\tY: ");
    Serial.print(event.orientation.y, 4);
    Serial.print("\tZ: ");
    Serial.println(event.orientation.z, 4); 
    delay(BNO055_SAMPLERATE_DELAY_MS);
    delay(10);
    leg_state = STATE2;
  }

  //-------Calling separate file hip_flex_knee in place



    
//  }//-----------END OF button_state if statement--------!!


}//===================end of loop , END OF PROGRAM=================================







