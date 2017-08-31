/*
 * File name: tensegrity_leg_gait_6.ino
 * Authors: Erik Jung and Lawrence Ngo
 * Comments: This a tensegrity knee with newly add hip joint. The purpose of this design is to mimic
 *           human gait. At the moment, the design relies soley on timers for movement.
 */

 
///==========================================================================================================
//Current Version 6: Right now the front motor will pull up the leg, while it's doing to the rear 
// motor will release the cable simultaneously. After that, the front motor releases the leg, and
// the rear cable tightens up
//      1)Trying to get hip to flex back. The rear motor will pull counter clockwise (BACKWARDS)
//        The front motor will release (FORWARDS). And then return to stationary positon.
//       2)Tighten front hip motor (BACKWARDS), stop, run hamstring motor (FORWARD) til 90 degrees of flexion.
//        Then run hamstring motor (Backwards) until neutral, and then loosen up front motor (FORWARDS).           
//
//Work in progress: --------------------------------------------------------------------------------------
//    Getting the robotic leg to simulate gait
//
//--------------------------------------------------------------------------------------------------------

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




//=================================================================
/* Helper functions to make the main code look cleaner:
 * increase, decrease, etc.
 */
//====INCREASE MOTOR SPEED==========================================================
void increase_motor_speed(int motor_number, uint8_t motor_direction_f,
                          uint8_t motor_direction_b, int motor_speed) { //( direction, motor)
  switch(motor_number){
    case 1:
      Serial.print("hip flex forward");
      f_hip_motor->run(motor_direction_f); //FORWARD, then backward 
      b_hip_motor->run(motor_direction_b);//BACKWARD, then forward  <------------SAME DIRECTION NOW
      hamstring_motor->run(motor_direction_f); // mimic the back to slowly release hamstring
      
      Serial.print("increasing motor speed");
      for(i=0;i<motor_speed;i++){
       f_hip_motor->setSpeed(i*1.2); //front hip motor pulls forward. 
       //IF YOU CALL FORWARD FLEXION, REDUCE SPEED OF REAR
       b_hip_motor->setSpeed(i*.30); //rear hip motor releases simultaneously with front x2 to increase speed
       //run to is slowly enxtend knee forward will flexing hip
       hamstring_motor->setSpeed(i*.70);
       
       //delay(5);  
      }
      break;   
    
    case 2:
      Serial.print("hip flex backwards");
      b_hip_motor->run(motor_direction_b);  //fix later
      f_hip_motor->run(motor_direction_f);  //fix later

      //slowly run hip motor to lightly tight cable
      hamstring_motor->run(motor_direction_f);//same as front hip
      Serial.print("increasing motor speed");
      for(i=0;i<motor_speed;i++){
        //IF YOU CALL FORWARD FLEXION, REDUCE SPEED OF FRONT
       f_hip_motor->setSpeed(i*.40);//new
       hamstring_motor->setSpeed(i*.65);
       b_hip_motor->setSpeed(i);
       
      // delay(5);
       
      }
      break;
    
    case 3:
      Serial.print("knee flex backwards");
      hamstring_motor->run(motor_direction_f); //fix later
      Serial.print("increasing motor speed");
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
    case 1:
    //CHECK TO SEE IF MOTOR DIRECTION HERE MATTERS
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
//distance,direction, motor
//(1=>forward, 2=>backwards)
void hip_flex(int distance, int motor_number, uint8_t motor_direction_f, uint8_t motor_direction_b, int motor_speed){  //40% motorspeed
  Serial.println("Flexing hip");
  increase_motor_speed(motor_number,motor_direction_f, motor_direction_b,motor_speed); //calls this fuctions and passes parameters
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


  
//---WALKING-GAIT-ALGORITHM-----------------------------------------------------------------
 if (button_state == HIGH) {
  
    //====FIRST_STEP=====//
    //flex hamstring to bring knee slightly up
    knee_flex(4500, FORWARD, BACKWARD);
    delay(10);
    //bring hip forward
    //pull front cable  (distance, motor number, f_motor_direction, b_motor_direct, speed)
    hip_flex(4000, 1, BACKWARD, FORWARD,200);  //ORGINALLY 4000 AND 4500 3:26PM
    delay(10);

    //====FOLLOW-THROUGH===//
//    //bring leg back to neutral then past continue swinging back 
    hip_flex(6000, 2, FORWARD, BACKWARD, 120);  
    delay(10);
  //-------Calling separate file hip_flex_knee in place

   // void knee_inplace(int distance, uint8_t motor_direction_f, uint8_t motor_direction_b, int motor_speed){
    knee_inplace(40, BACKWARD,FORWARD,170);
    
  //RETURN KNEE BACK TO NEUTRAL    
    knee_flex(2700, BACKWARD, FORWARD);
    delay(10);


    
  }//-----------END OF button_state if statement--------!!


}//===================end of loop , END OF PROGRAM=================================







