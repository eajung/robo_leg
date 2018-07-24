

/*
  REV_5_wireless_open_loop.ino

  Description:
  This code uses a wireless module to control the tensegrity leg with two main functions: squat and stand.
*/

// Libraries
#include <stdio.h>
#include <Adafruit_MotorShield.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>

// Macro Definitions & Global Variables
#define RELEASE_TIBIALIS 1
#define CONTRACT_TIBIALIS 2
#define RELEASE_CALF 2
#define CONTRACT_CALF 1
#define TIBIALIS_POSITIVE 14
#define TIBIALIS_NEGATIVE 16
#define TIBIALIS_PWM 15
#define CALF_POSITIVE 12
#define CALF_NEGATIVE 13
#define CALF_PWM 23

WiFiUDP udp; // make a variable instance of the WiFiUDP
const char *ssid = "REV 5 Tensegrity"; // WiFi network
const char *password = "";
unsigned int local_udp_port = 4210; // local port to listen on
boolean serial_ready = false;
char incoming_packet[255]; // buffer for incoming packets
String input;
int commaIndex, desired_speed;
char command;
unsigned long counter_5hz;
long count = 0;

// ================== HELPER FUNCTIONS ===========================
/*
  squat():
  param: int millisec - specifies the amount of time tensegrity structure squats
       int desired_speed - moves the motors at this desired_speed to move the tensigrity structure
  Description: This function will have both tibialis_hamstring_motor and the calf_quadricep_motor contract but one will contract at a slower rate in that amount of time.
*/
void squat(int millisec, int desired_speed) {
  Serial.println("SQUAT: calf_quadricep_motor and tibialis_hamstring_motor contracts");
  Serial.println("Step 1: Contracting calf and quadricep motors");
  // set motor direction to contract the calf muscles
  digitalWrite(CALF_POSITIVE, LOW);
  digitalWrite(CALF_NEGATIVE, HIGH);
  for (int i = 0; i < desired_speed; i++) analogWrite(CALF_PWM, i);  // contract the muscles at desired speed
  delay(millisec); // motion limited by amount of time
  for (int i = 0; i < desired_speed; i++) analogWrite(CALF_PWM, 0); // stops the contraction of the muscles at desired speed
  Serial.println("Step 2: Contracting tibialis and hamstring motors");
  // set motor direction to contract the tibialis muscles
  digitalWrite(TIBIALIS_POSITIVE, HIGH);
  digitalWrite(TIBIALIS_NEGATIVE, LOW);
  for (int i = 0; i < desired_speed; i++) analogWrite(TIBIALIS_PWM, i); // contract the muscles at desired speed
  delay(millisec / 3); // motion limited by amount of time
  for (int i = 0; i < desired_speed; i++) analogWrite(TIBIALIS_PWM, 0); // stops the contraction of the muscles at desired speed 
}

/*
  stand():
  param: int millisec - specifies the amount of time tensegrity structure has to stand up
         int desired_speed - the motors at this desired_speed make the tensegrity structure stand up
  Description: This function will have both tibialis_hamstring_motor and the calf_quadricep_motor release but one will release at a slower rate in that amount of time.
*/
void stand(int millisec, int desired_speed) {
  Serial.println("STAND: calf_quadricep_motor and tibialis_hamstring_motor releasing");
  Serial.println("Step 1: Releasing calf and quadricep motors");
  // set motor direction to contract the tibialis muscles
  digitalWrite(CALF_POSITIVE, HIGH);
  digitalWrite(CALF_NEGATIVE, LOW);
  for (int i = 0; i < desired_speed; i++) analogWrite(CALF_PWM, i); // contract the muscles at desired speed
  delay(millisec/2); // motion limited by amount of time
  for (int i = 0; i < desired_speed; i++) analogWrite(CALF_PWM, 0); // stops the contractions of the muscles at desired speed
  Serial.println("Step 2: Releasing tibialis and hamstring motors");
  // set motor direction to contract the calf muscles
  digitalWrite(TIBIALIS_POSITIVE, LOW);
  digitalWrite(TIBIALIS_NEGATIVE, HIGH);
  for (int i = 0; i < desired_speed; i++) analogWrite(TIBIALIS_PWM, i); // contract the muscles at desired speed
  delay(millisec / 3); // motion limited by amount of time
  for (int i = 0; i < desired_speed; i++) analogWrite(TIBIALIS_PWM, 0); // stops the contractions of the muscles at desired speed
  Serial.println("Finished Squat.");
}

/*
  stop():
  Description: This function will have both tibialis_hamstring_motor and the calf_quadricep_motor stop any motion.
*/
void stop() {
  Serial.print("STOP: calf_quadricep_motor and tibialis_hamstring_motor stop moving\n ");
  // Stop calf and quadricep motors
  analogWrite(TIBIALIS_PWM, 0);
  analogWrite(CALF_PWM, 0);
  digitalWrite(TIBIALIS_POSITIVE, LOW);
  digitalWrite(TIBIALIS_NEGATIVE, LOW);
  digitalWrite(CALF_POSITIVE, LOW);
  digitalWrite(CALF_NEGATIVE, LOW);
}

// ================== SETUP FUNCTION ===========================
/* setup()
   Description: This function turns on or activates any necessary libraries for the main part
                of the code to properly compile and run.
*/
void setup() {
  Serial.begin(115200); //Set the baud rate for serial communication
  Serial.print("REV 5 Open Loop Wireless Protocol\n"); //Inform user that program has been loaded
  WiFi.softAP(ssid, password, 11); // Broadcast WiFi: SSID and password
  
  // Set pins to output for the DC Motors
  pinMode(TIBIALIS_POSITIVE, OUTPUT);
  pinMode(TIBIALIS_NEGATIVE, OUTPUT);
  pinMode(CALF_POSITIVE, OUTPUT);
  pinMode(CALF_NEGATIVE, OUTPUT);
  pinMode(TIBIALIS_PWM, OUTPUT);
  pinMode(CALF_PWM, OUTPUT);

  // Set the DC motor pins to low/off
  analogWrite(TIBIALIS_PWM, 0);
  analogWrite(CALF_PWM, 0);
  digitalWrite(TIBIALIS_POSITIVE, LOW);
  digitalWrite(TIBIALIS_NEGATIVE, LOW);
  digitalWrite(CALF_POSITIVE, LOW);
  digitalWrite(CALF_NEGATIVE, LOW);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  udp.begin(local_udp_port);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), local_udp_port);

  counter_5hz = millis();
}

// ================== MAIN LOOP FUNCTIONS ===========================
void loop() {
  /*if there is data in the serial transmit side, read and process it */
  if (serial_ready) {
    command = incoming_packet[0];
    Serial.println(command);
    /*switch statement covering all hotkey cases */
    switch (command) {
      case 's': //HOTKEY = s, starts the squat
        squat(4200, 90); // calls squat(int millisec, int desired_speed)
        stand(3500, 90); // calls stand(int millisec, int desired_speed)
        stop();
        // incoming_packet[0] = NULL; // reset
        serial_ready = false;
        break;
      case 'x': //HOTKEY = x, stop all motor activity
        stop();
        delay(5);
        serial_ready = false;
        break;
      default:
        break;

   

      case 't': //HOTKEY = t, move tibialis_hamstring_motor backward and contracts
        Serial.print("Move tibialis_hamstring_motor contracts: ");
        Serial.println(millis());
        //Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(CONTRACT_TIBIALIS);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i);
        }
        delay(5);
        break;

      case 'h': //HOTKEY = h, move tibialis_hamstring_motor forward and releases
        Serial.print("Move tibialis_hamstring_motor releases: ");
        Serial.println(millis());
       // Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(RELEASE_TIBIALIS);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i);
        }
        delay(5);
        break;

      case 'c': //HOTKEY = c, move calf_quadricep_motor forward (contract)
        Serial.print("Move calf_quadricep_motor contracts: ");
        Serial.println(millis());
        //Serial.println(desired_Speed);
        calf_quadricep_motor->run(CONTRACT_CALF);
        for (int i = 0; i < desired_Speed; i++) {
          calf_quadricep_motor->setSpeed(i);
        }
        delay(5);
        break;

      case 'q': //HOTKEY = q, move calf_quadricep_motor backward (releases)
        Serial.print("Move calf_quadricep_motor releases: ");
         Serial.println(millis());
       // Serial.println(desired_Speed);
        calf_quadricep_motor->run(RELEASE_CALF);
        for (int i = 0; i < desired_Speed; i++) {
          calf_quadricep_motor->setSpeed(i);
        }
        delay(5);
        break;

      case 'f': //HOTKEY = f, move tibialis_hamstring_motor backward and calf_quadricep_motor forward - contracts
        Serial.print("both tibialis_hamstring_motor and calf_quadricep_motor contracts: ");
         Serial.println(millis());
        //Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(CONTRACT_TIBIALIS);
        calf_quadricep_motor->run(CONTRACT_CALF);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i);
          calf_quadricep_motor->setSpeed(i / 2);
        }
        delay(5);
        break;
      case 'b': //HOTKEY = b, move tibialis_hamstring_motor forward and calf_quadricep_motor backward - releases
        Serial.print("Both tibialis_hamstring_motor and calf_quadricep_motor releases: ");
         Serial.println(millis());
        //Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(RELEASE_TIBIALIS);
        calf_quadricep_motor->run(RELEASE_CALF);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i / 2);
          calf_quadricep_motor->setSpeed(i);
        }
        delay(5);
        break;

      case 'a': //HOTKEY = i, move tibialis_hamstring_motor backward (contract) and calf_quadricep_motor backward (release)
        Serial.print(" tibialis_hamstring_motor contracts and calf_quadricep_motor releases: ");
        Serial.println(millis());
       // Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(CONTRACT_TIBIALIS);
        calf_quadricep_motor->run(RELEASE_CALF);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i);
          calf_quadricep_motor->setSpeed(i);
        }
        delay(5);
        break;
      case 'o': //HOTKEY = o, move tibialis_hamstring_motor forward (release) and calf_quadricep_motor forward (contract)
        Serial.print("tibialis_hamstring_motor releases and calf_quadricep_motor contracts: ");
        Serial.println(millis());
        //Serial.println(desired_Speed);
        tibialis_hamstring_motor->run(RELEASE_TIBIALIS);
        calf_quadricep_motor->run(CONTRACT_CALF);
        for (int i = 0; i < desired_Speed; i++) {
          tibialis_hamstring_motor->setSpeed(i);
          calf_quadricep_motor->setSpeed(i);
        }
        delay(5);
        break;

      //motors move forward at different speeds

      case 'e': //HOTKEY = e, stop(exit) all motor activity
        Serial.print("Stop: ");
        tibialis_hamstring_motor->run(BRAKE);
        tibialis_hamstring_motor->setSpeed(0);
        calf_quadricep_motor->run(BRAKE);
        calf_quadricep_motor->setSpeed(0);
        Serial.println(millis());
        delay(5);
        break;

      case 'p': //HOTKEY = p, print out the time
       Serial.println(millis());

        break;

    }
    

    
  }
  //Process UDP package
  int packetSize = udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = udp.read(incoming_packet, 255);
    if (len > 0)
    {
      incoming_packet[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incoming_packet);
    serial_ready = true;
  }

  
}













