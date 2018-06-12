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
  input = Serial.readString();
  command = input[0];
  switch(command) {
    case 's': // s for start
      Serial.print("Starting leg motion");
      myMotor->setSpeed(150);
      myMotor->run(FORWARD);

      uint8_t i;
      myMotor->run(FORWARD);

      for (i=0; i<255; i++) {
        myMotor->setSpeed(i);  
        delay(10);
      }
      break;
        
    case 'x' : // x for exit
      Serial.print("Exiting leg motion");
      myMotor -> setSpeed(0);  
      break;
        

    case 'r' : // r for reverse  
      Serial.print("Reversing leg motion");
      myMotor->setSpeed(150);
      myMotor->run(BACKWARD);
      break;
        
    default:
      break;
      
  } 
}

}


