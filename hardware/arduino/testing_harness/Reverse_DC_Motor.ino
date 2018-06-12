#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

String input; // keyboard input
char command; // hotkey parsed from input

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  AFMS.begin();  // create with the default frequency 1.6KHz
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(150);
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);

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
  // turn on motor
  myMotor->run(RELEASE);

  uint8_t i;
  myMotor->run(FORWARD);
  for (i=0; i<255; i++) {
    myMotor->setSpeed(i);  
    delay(10);
  }
  
  for (i=255; i!=0; i--) {
    myMotor->setSpeed(i);  
    delay(10);
  }
  

  myMotor->run(BACKWARD);
  for (i=0; i<255; i++) {
    myMotor->setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor->setSpeed(i);  
    delay(10);
  }

  myMotor->run(RELEASE);
  delay(1000);

  break;
      
  case 'x' : // x for exit
  Serial.print("Exiting leg motion");
  myMotor -> setSpeed(0);
    
  break;
      

  case 'r' : // r for reverse  
  Serial.print("Reversing leg motion");
  myMotor->setSpeed(150);
  myMotor->run(BACKWARD);
  // turn on motor
  myMotor->run(RELEASE);

  while (true) {
  myMotor->run(BACKWARD);
  for (i=0; i<255; i--) {
    myMotor->setSpeed(i);  
    delay(10);
  }
  
  for (i=255; i!=0; i++) {
    myMotor->setSpeed(i);  
    delay(10);
  }
  

  myMotor->run(FORWARD);
  for (i=0; i<255; i++) {
    myMotor->setSpeed(i);  
    delay(10);
  }
  for (i=255; i!=0; i--) {
    myMotor->setSpeed(i);  
    delay(10);
  }

  myMotor->run(RELEASE);
  delay(1000);
  
  
  }

  break;
      
    default:
      break;
      
  } 
}

}


