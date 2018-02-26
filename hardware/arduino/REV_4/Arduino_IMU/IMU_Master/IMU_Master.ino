#include <SPI.h>
#include <DW1000.h>

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 2; // irq pin
const uint8_t PIN_SS = SS; // spi select pin

// messages used in the IMU Network protocol
#define DATA_REPORT 3
#define DATA_REQ 2
#define DATA_FAILED 255

// message flow state
volatile byte expectedMsgId = DATA_REPORT;
// message sent/received state
volatile boolean sentAck = false;
volatile boolean receivedAck = false;

// data buffer
#define LEN_DATA 16
byte data[LEN_DATA];

const int addr = 255;
const int dev_number = 4;

// watchdog and reset period
unsigned long lastActivity;
unsigned long resetPeriod = 500;
// reply times (same on both sides for symm. ranging)
unsigned int replyDelayTimeUS = 3000;

int count = 1;
void setup() {
  // DEBUG monitoring
  Serial.begin(115200);
  Serial.println(F("### IMU Network-Maser ###"));
  // initialize the driver
  DW1000.begin(PIN_IRQ, PIN_RST);
  DW1000.select(PIN_SS);
  Serial.println("DW1000 initialized ...");
  // general configuration
  DW1000.newConfiguration();
  DW1000.setDefaults();
  DW1000.setDeviceAddress(3);
  DW1000.setNetworkId(10);
  DW1000.enableMode(DW1000.MODE_SHORTDATA_FAST_LOWPOWER);
  DW1000.commitConfiguration();
  Serial.println(F("Committed configuration ..."));
  // DEBUG chip info and registers pretty printed
  char msg[128];
  DW1000.getPrintableDeviceIdentifier(msg);
  Serial.print("Device ID: "); Serial.println(msg);
  DW1000.getPrintableExtendedUniqueIdentifier(msg);
  Serial.print("Unique ID: "); Serial.println(msg);
  DW1000.getPrintableNetworkIdAndShortAddress(msg);
  Serial.print("Network ID & Device Address: "); Serial.println(msg);
  DW1000.getPrintableDeviceMode(msg);
  Serial.print("Device mode: "); Serial.println(msg);
  // attach callback for (successfully) sent and received messages
  DW1000.attachSentHandler(handleSent);
  DW1000.attachReceivedHandler(handleReceived);
  
  receiver();
  transmitNext();
  noteActivity();
}

void noteActivity() {
  // update activity timestamp, so that we do not reach "resetPeriod"
  lastActivity = millis();
}

void resetInactive() {
  // tag sends POLL and listens for POLL_ACK
  expectedMsgId = DATA_REPORT;
  //transmitPoll();
  transmitNext();
  noteActivity();
}

void handleSent() {
  // status change on sent success
  sentAck = true;
}

void handleReceived() {
  // status change on received success
  receivedAck = true;
}
void transmitData_Req(int target) {
  DW1000.newTransmit();
  DW1000.setDefaults();
  data[0] = target;
  data[1] = addr;
  data[2] = DATA_REQ;
  
  DW1000.setData(data, LEN_DATA);
  DW1000.startTransmit();
  //Serial.print("Range ");   Serial.print(target);  
}

void transmitNext()
{
  // Serial.println(count);
  transmitData_Req(count);
  count = count + 1;
  if(count>dev_number)
  {
    count = 1;
  }
}

void receiver() {
  DW1000.newReceive();
  DW1000.setDefaults();
  // so we don't need to restart the receiver manually
  DW1000.receivePermanently(true);
  DW1000.startReceive();
}

void loop() {
  if (!sentAck && !receivedAck) {
    // check if inactive
    if (millis() - lastActivity > resetPeriod) {
      resetInactive();
    }
    return;
  }
  // continue on any success confirmation
  if (sentAck) {
    sentAck = false;
    byte msgId = data[0];
    if (msgId == DATA_REQ) {
      
      noteActivity();
    }
  }
  if (receivedAck) {
    receivedAck = false;
    // get message and parse
    DW1000.getData(data, LEN_DATA);
    byte msgId = data[2];
    byte target = data[0];
    byte source = data[1];
    //Serial.print(source); Serial.print(":"); Serial.print(target); Serial.print(":"); Serial.println(msgId);
    if (msgId == DATA_REPORT) {
        expectedMsgId = DATA_REPORT;
        float x,y,z;
        memcpy(&x, data + 3, 4);
        memcpy(&y, data + 7, 4);
        memcpy(&z, data + 11, 4);
        
        //Serial.print(target);
        Serial.print("IMU# ");
        Serial.print(source);
        Serial.print("  X: ");
        Serial.print(x);
        Serial.print("  Y: ");
        Serial.print(y);
        Serial.print("  Z: ");
        Serial.println(z);
        noteActivity();
        transmitNext();
      }
  }
}

