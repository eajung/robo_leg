
 
//Print libraries
#include <stdio.h>
//Motor libraries
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
//Gyroscope libraries 
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

Adafruit_MotorShield AFMS         = Adafruit_MotorShield(); 

//Creating instances of motor
Adafruit_DCMotor *tibialis_hamstring_motor     = AFMS.getMotor(1); //hip flex forward motor
Adafruit_DCMotor *calf_quadriceps_motor     = AFMS.getMotor(4); //hip flex rear motor


void setup() {
  Serial.begin(9600); //Set the baud rate
  Serial.print("Power On. Begin Test.\n"); //Inform user that test is starting
  AFMS.begin(); //begin

  Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");

}

  String input;
  int    commaIndex;
  char   command;
  int    desired_Speed;
  int second_desired_Speed;

void loop() {

  
  /*if there is data in the serial transmit side, read and process it */
  if (Serial.available() > 0) {

    /*parse through the transmit side string */
    input              = Serial.readString();
    commaIndex         = input.indexOf(',');
    String firstValue  = input.substring(0, commaIndex);
    String secondValue = input.substring(commaIndex+1);
    
    /*set the desired motor and the desired speed */
    command      = firstValue[0];
    desired_Speed      = secondValue.toInt();
  

    /*switch statement covering all hotkey cases */
    switch (command) {
// Downward phase - squatting motion
//tibialis_hamstring_motor is contracting  at half speed while calf_quadriceps_motor is releasing at full speed
//d stands for downward phase
      case 'd':
        Serial.print("Downward Phase: Tibialis_hamstring_motor contracting while calf_quadriceps_motor releasing") ;
        Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(FORWARD);
        calf_quadriceps_motor->run(BACKWARD);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i);
           calf_quadriceps_motor->setSpeed(i/2);

          
        }

        
        delay(5);
        break;

// Upward phase - squatting motion
//tibialis_hamstring_motor is releasing  at half speed while calf_quadriceps_motor is contracting at full speed
//u stands for upward phase
        case 'u':
        Serial.print("Upward Phase: Tibialis_hamstring_motor releasing while calf_quadriceps_motor contracting") ;
        Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(BACKWARD);
        calf_quadriceps_motor->run(FORWARD);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i/2);
           calf_quadriceps_motor->setSpeed(i);

          
        }

        
        delay(5);
        break;

 
 //Both tibialis_hamstring_motor and calf_quadriceps_motor contract
//c stands for contract
        case 'c':
        Serial.print(" Both tibialis_hamstring_motor and calf_quadriceps_motor contract") ;
        Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(FORWARD);
        calf_quadriceps_motor->run(FORWARD);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i/4);
           calf_quadriceps_motor->setSpeed(i);

          
        }

        
        delay(5);
        break;

   case 'r':
        Serial.print(" Both tibialis_hamstring_motor and calf_quadriceps_motor contract") ;
        Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(BACKWARD);
        calf_quadriceps_motor->run(BACKWARD);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i/2);
           calf_quadriceps_motor->setSpeed(i);

          
        }

        
        delay(5);
        break;     
    
    

    case 's': //HOTKEY = s, stop all motor activity
        Serial.print("Stop\n");
        tibialis_hamstring_motor->run(BRAKE);
       tibialis_hamstring_motor->setSpeed(0);
        calf_quadriceps_motor->run(BRAKE);
        calf_quadriceps_motor->setSpeed(0);
      
        delay(5);
        break;
    }

    
  
  //delay(BNO055_SAMPLERATE_DELAY_MS);
}

}
