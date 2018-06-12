#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

String input; // keyboard input
char command; // hotkey parsed from input

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  AFMS.begin();  // create with the default frequency 1.6KHz

  myMotor->run(RELEASE); // turn on motor
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) { // if serial input is ready to read input
  input = Serial.readString();  //input is user input
  command = input[0]; //index is to take the first letter of user input in serial 
  
  //depending on whether the user put 's' 'x' or 'r', the code switches between the three cases
  switch(command) {
    case 's': // s for start
      Serial.print("Starting leg motion");
      myMotor->setSpeed(150);  //set Speed to 150
     

      uint8_t i;
      myMotor->run(FORWARD); //set myMotor to move forward

      for (i=0; i<255; i++) {
        myMotor->setSpeed(i);  //incrementing the speed from 0-254
        delay(10);    //after each increment, the motor is delayed by 10 milliseconds
      }
      break;
        
    case 'x' : // x for exit
      Serial.print("Exiting leg motion");
      myMotor -> setSpeed(0);  //Setting speed to 0 to make the motor stop
      break;
        

    case 'r' : // r for reverse  
      Serial.print("Reversing leg motion");
      myMotor->run(BACKWARD); //just change direction of the motor spinning
      break;

  //nothing should change if user doesn't input anything      
    default:
      break;
      
  } 
}

}


