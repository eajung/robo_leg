#include <math.h> // to use exponential function


// the value of the 'other' resistor
#define SERIESRESISTOR 10000    
 
// What pin to connect the sensor to
#define THERMISTORPIN A0 
 
void setup(void) {
  Serial.begin(9600);
}
 
void loop(void) {
  float reading;
 
  reading = analogRead(THERMISTORPIN);
 
  Serial.print("Analog reading "); 
  Serial.println(reading);
 
  // convert the value to resistance
  reading = (1023 / reading)  - 1;
  reading = SERIESRESISTOR / reading;
  //Serial.print("Thermistor resistance ");
  
  Serial.print("Force muscle generates: ");
  float force = ((0.759096*exp(0.00178499*reading)) - 1.26725);
  Serial.println(force); 
  //Serial.println(reading);
 
  delay(1000);
}
