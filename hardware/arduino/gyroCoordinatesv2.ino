/* rawdata provided by adafruit
 * modifies 10/26/17
 * Mai Linh Ngo (malngo@ucsc.edu)
 * 
 */

//For Gryoscope
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

//For Motors
#include <math.h>
#include <Adafruit_MotorShield.h>
#include <stdio.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055();

//
const int button_pin = 2; // the number of the switch pin
int button_state = 0; // this will change based on the state of the push button status
int counter = 0;
double x,y,z,x2,y2,z2;
uint8_t i; 
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


/**************************************************************************/
/*
    FUNCTION DECLARATION!!!
*/
/**************************************************************************/


  //====INCREASE MOTOR SPEED==========================================================
  void increase_motor_speed(int motor_number, uint8_t motor_direction_f, int motor_speed) { //( direction, motor)
        Serial.println("\nknee flex backwards");
        hamstring_motor->run(motor_direction_f); //fix later
        Serial.println("increasing motor speed");
        for(i=0;i<motor_speed;i++){
          hamstring_motor->setSpeed(i*.80); //new just need to be i, 255 is max value and it will reach there afterwards
          delay(5); 
        }
  }//end of increase_motor_speed------------------------------------------

  //====DECREASE MOTOR SPEED==============================================
  //motor speed ranges from 0-255
  void decrease_motor_speed(int motor_number, uint8_t motor_direction) { 
        hamstring_motor->run(motor_direction);
        Serial.println("decreasing hamstring motor speed");
        for(i=10; i!=0; i--){
         f_hip_motor->setSpeed(i); // IF YOU CALL BACKWARD FLEXION, REDUCE SPEED OF FRONT MOTOR   
         b_hip_motor->setSpeed(i); 
         hamstring_motor->setSpeed(i);
         //delay(5);//commentout 
        }
  }//
  //-------------end of decrease_motor_speed()-------------------------
  //--------------------------------------------------------------------

  /**************************************************************************/
  /*
      Arduino setup function (automatically called at startup)
  */
  /**************************************************************************/
  void setup(void)
  {
    Serial.begin(9600);
    Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");
    /* Initialise the sensor */
    if(!bno.begin())
    {
      /* There was a problem detecting the BNO055 ... check your connections */
      Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
      while(1);
    }
    delay(1000);
    bno.setExtCrystalUse(true);
  }

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{

  //Time function
  delay(10); //refreashing time constant
  button_state = digitalRead(button_pin); // read the state of the switch value


  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

  
  Serial.print("\t\t"); //Spaced out columnse
  //WRITE TO SERIAL
  delay(500);
  Serial.println(" ");
  //Serial.println("hi");
  char inChar;
  //user hits enter 
  if(Serial.available()){
    inChar = Serial.read(); // Read the input from the send on the serial monitr
    switch (inChar) {
      case 's':
          Serial.println("Starting Position!");
          Serial.println(" ");
          x = euler.x();
          y = euler.y();
          z = euler.z();
          Serial.println(x);
          Serial.println(y);
          Serial.println(z); 
          delay(5);
          break;
      case 'e':
          Serial.println("Desired Position!");
          Serial.println(" ");
          x2 = euler.x();
          y2 = euler.y();
          z2 = euler.z();
          Serial.println(x2);
          Serial.println(y2);
          Serial.println(z2);  
          delay(5);
          //Starting & Ending Positions saved--------------------
          if((x != NULL) &&  (x2 != NULL)){
            Serial.println("\nCoordinates saved");
          }//======================================================================
          break;
      case 'h':
         while(true){
            imu::Vector<3> new_euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);
            delay(400);
            //increase_motor_speed(3, FORWARD,120);
            //Serial.println("\nFlexing knee backwards");
            Serial.println("Goal to reach: ");
            Serial.print(x2);
            
            Serial.println("\nCurrent x-value: ");
            Serial.print(new_euler.x());

            delay(10);

            if( (new_euler.x() <= (x2 + 4.0) ) && (new_euler.x() >= (x2 - 4.0)) ){ 
                Serial.println("\nStopping Leg now");
                Serial.println("Current x-value: ");
                Serial.print(new_euler.x());
                Serial.println(" ");
                decrease_motor_speed(3, FORWARD); //slow down motor and stop leg
                break;
                
               //delay(distance*fact);    
            } //end of if statement   
           
        }//end of while       

          

            delay(10);
        
            
    }                

    
       
  //=========================================================================================  
  }//end of if serial.available =============================================================
  //=========================================================================================


  
}// END of void loop---END OF PROGRAM






