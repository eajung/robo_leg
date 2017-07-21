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


const int button_pin = 2; // the number of the switch pin
int button_state = 0; // this will change based on the state of the push button status
int flexed_state = 0; // tells us if the leg has flexed
uint8_t i; 
unsigned long time; // time might be used by the delay()
float fact; // dependent on the voltage 
float stretchcord_reading; // analog reading for the stretch sensor
float maximum_tension = 2.7; // software set maximum tension in cables compared to the stretchcord_reading
float fully_flexed_angle_tension = 2.2;
float taut_tension = 1.4; // software set tension for when the leg is back to being taught
float force; // force calcuation based off of the stretchcord_reading

int counter = 0;

/* 
 * Create the motor shield object with the default I2C address
 * Or, create it with a different I2C address (say for stacking) 
 * Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);
 */
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
/*
 * Select which 'port' M1, M2, M3, or M4. This is M1
 */
Adafruit_DCMotor *my_motor = AFMS.getMotor(1); // Knee Flexion motor

/*
 * Helper functions to make the main code look cleaner:
 * increase, decrease, etc.
 */
void increase_motor_speed() {
  Serial.println("Increasing motor speed\n");
  for (i=0; i<100; i++) {
    my_motor->setSpeed(i);
    delay(5);
  }
}

void decrease_motor_speed() {
  Serial.println("Decreaseing motor speed\n");
  for (i=100; i!=0; i--) {
    my_motor->setSpeed(i);
    delay(5);
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  Serial.println("KNEE Motion Program!");

// initialize control over the keyboard:
//  Keyboard.begin();
  
  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  
 
  my_motor->setSpeed(0); // Set the speed to start, from 0 (off) to 255 (max speed)
  my_motor->run(FORWARD);
  my_motor->run(RELEASE); // turn on motor
 
  pinMode(button_pin, INPUT); // initialize the switch pin as an input
  //digitalWrite(button_pin, High); //Turn on Internal pull-up 
}

// Put your main code here to run repeatedly:
void loop() {
  
  //Time function
  time = millis(); //print time since started in milliseconds
  delay(10); //refreashing time constant
  
  button_state = digitalRead(button_pin); // read the state of the switch value
  //  Serial.println(button_state);
  
  if (button_state == HIGH) {
  //    Serial.print("Knee Flexion\n");
    my_motor->run(FORWARD);
    increase_motor_speed();
  }
  
  stretchcord_reading = analogRead(THERMISTORPIN); // reads the A0 pin for the voltage values of the stretch cord sensor
  //  Serial.print("Analog reading:");
  //  Serial.println(stretchcord_reading);
 
  // convert the value to resistance
  stretchcord_reading = (1023 / stretchcord_reading)  - 1;
  stretchcord_reading = FORCERESISTOR / stretchcord_reading;
  
  force = ((0.759096*exp(0.00178499*stretchcord_reading)) - 1.26725); // formula found from sensor calibration tests
  //  Serial.print("Force: ");
  //  Serial.println(force);

  /*
   * This allows us to mark when we have reached a specific angle.
  char inChar;
  //user hits enter 
  if(Serial.available()){
    inChar = Serial.read(); // Read the input from the send on the serial monitr
    if(inChar == '\n'){
      counter += 10;
      Serial.print("angle is: ");
      Serial.println(counter); // Tells us which angle we're at
      Serial.println(force); // Tell us the force at the specified angle
    }
  }
  */
  
  if (force > maximum_tension) { // Let us know we've reached about 60-70 degree knee flexion
    flexed_state = 1; 
  }

  if ((force < fully_flexed_angle_tension) && (flexed_state == 1)){ // Approaching maximum degree for knee flexion
    decrease_motor_speed();
    delay(1000);
    my_motor->run(BACKWARD);
    increase_motor_speed();
    flexed_state = 2;
  }

  if ((force < taut_tension) && (flexed_state == 2)) { // Stop motors once at rest length.
    decrease_motor_speed();
    Serial.println("Finished.");
    my_motor->run(RELEASE);
    delay(500);
    flexed_state = STARTPOSITION;
  }
}


