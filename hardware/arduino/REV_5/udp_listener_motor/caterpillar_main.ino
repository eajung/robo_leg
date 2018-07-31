#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <Adafruit_ADS1015.h>
//V1

//Wifi Setup
WiFiUDP Udp;
//Define Bot id
int bot_id =1;

//Set wifi
const char *ssid = "TP-Link_Pat";
const char *password = "espbot1234";
unsigned int localUdpPort = 4210;  // local port to listen on
IPAddress ip(192, 168, 0, 110 + bot_id);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
char incomingPacket[255];  // buffer for incoming packets
IPAddress remote_ip;
int remote_port = 8000;
char replyPacket[50];

//Define PIN PCB v4
const int A_IN1 = 14;
const int A_IN2 = 16;
const int B_IN1 = 12;
const int B_IN2 = 13;
const int A_PWM = 15;
const int B_PWM = 2;

//ADC
Adafruit_ADS1015 ads;
int16_t adc_val;
boolean ir_detect[4] = {false, false, false, false};
int ir_threshold[4] = {930, 1050, 925, 1030};
//Timer
unsigned long counter_5hz;
long count = 0;

boolean sensorEnabled = true;

void update_ir_sensor()
{
  for (int i = 0; i < 4; i++)
  {
    // if (i == 0 || i == 1 || i == 2) {
    adc_val = ads.readADC_SingleEnded(i);
    Serial.print("ADC ");
    Serial.print(i);
    Serial.print(":");
    Serial.println(adc_val);
    if (adc_val <= ir_threshold[i]) {
      ir_detect[i] = true;
      drive_motor(1, 0);
      drive_motor(2, 0);
    } else {
      ir_detect[i] = false;
    }
    //}
  }
  //Construct sensor message
  snprintf ( replyPacket, 50, "%d:%d,%d,%d,%d",
             bot_id, ads.readADC_SingleEnded(0), ads.readADC_SingleEnded(1), ads.readADC_SingleEnded(2), ads.readADC_SingleEnded(3)
           );
  //Send data
  Udp.beginPacket(remote_ip, remote_port);
  Udp.write(replyPacket);
  Udp.endPacket();
}
void drive_motor(int motor, int value)
{
  if (motor == 1)
  {
    if (value > 0)
    {
      Serial.println("1 fwd");
      Serial.println(value);
      digitalWrite(A_IN1, LOW);
      digitalWrite(A_IN2, HIGH);
      analogWrite(A_PWM, value);
    }
    else if (value < 0)
    {
      Serial.println("1 bwd");
      digitalWrite(A_IN1, HIGH);
      digitalWrite(A_IN2, LOW);
      analogWrite(A_PWM, -value);
    }
    else
    {
      //Brake
      digitalWrite(A_IN1, LOW);
      digitalWrite(A_IN2, LOW);
      analogWrite(A_PWM, 0);
      Serial.println("1 0");
    }
  }
  else if (motor == 2)
  {
    if (value > 0)
    {
      Serial.println("2 fwd");
      digitalWrite(B_IN1, LOW);
      digitalWrite(B_IN2, HIGH);
      analogWrite(B_PWM, value);
    }
    else if (value < 0)
    {
      Serial.println("2 bwd");
      digitalWrite(B_IN1, HIGH);
      digitalWrite(B_IN2, LOW);
      analogWrite(B_PWM, -value);
    }
    else
    {
      //Brake
      Serial.println("2 0");
      digitalWrite(B_IN1, LOW);
      digitalWrite(B_IN2, LOW);
      analogWrite(B_PWM, 0);
    }
  }
}
void setup()
{
  Serial.begin(115200);
  Serial.println();

  //Set pin mode
  pinMode(A_IN1, OUTPUT);
  pinMode(A_IN2, OUTPUT);
  pinMode(B_IN1, OUTPUT);
  pinMode(B_IN2, OUTPUT);
  pinMode(A_PWM, OUTPUT);
  pinMode(B_PWM, OUTPUT);
  analogWrite(A_PWM, 0);
  analogWrite(B_PWM, 0);
  digitalWrite(A_IN1, LOW);
  digitalWrite(A_IN2, LOW);
  digitalWrite(B_IN1, LOW);
  digitalWrite(B_IN2, LOW);

  //Setup wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  IPAddress myIP = WiFi.localIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);

  ads.begin();
  counter_5hz = millis();
}
void loop()
{
  if (sensorEnabled == true) { 
    //IR sensor update 5 Hz
    if (millis() - counter_5hz >= 200)
    {
      update_ir_sensor();
      //count++;
      //Serial.print(count); Serial.print(":"); Serial.println(WiFi.softAPgetStationNum());
      counter_5hz = millis();
    }
  }
  if (Serial.available() > 0) {
    switch (Serial.read())
    {
      case '1':
        drive_motor(1, 200);
        break;
      case '2':
        drive_motor(2, 200);
        break;
    }
  }
  //Process UDP package
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // receive incoming UDP packets
    //Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    Serial.printf("UDP packet contents: %s\n", incomingPacket);
    remote_ip = Udp.remoteIP();
    //Parse Motor and value
    int motor = atoi(&incomingPacket[0]);
    if (len >= 3 && len <= 9)
    {
      //Convert char* to int
      char buffer[len - 1];
      for (int i = 0; i < len - 2; i++)
      {
        buffer[i] = incomingPacket[i + 2];
      }
      buffer[len - 2] = '\0';
      int value = atoi(buffer);
      Serial.println(len);
      Serial.print(motor);
      Serial.print(":");
      Serial.println(value);
      if (value >= -1024 && value <= 1024)
      {
        if (motor == 1 || motor == 2 ) {
          drive_motor(motor, value);
        }
        else if (motor == 3) {
          drive_motor(1, value);
          drive_motor(2, value);
        }
      }
    }
  }
}
