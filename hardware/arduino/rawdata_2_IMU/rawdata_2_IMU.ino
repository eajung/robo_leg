#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

/* This driver reads raw data from the BNO055

   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
   Connect GROUND to common ground

   History
   =======
   2015/MAR/03  - First release (KTOWN)
*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)

Adafruit_BNO055 bno = Adafruit_BNO055(55, BNO055_ADDRESS_A);
Adafruit_BNO055 bno2 = Adafruit_BNO055(56, BNO055_ADDRESS_B);

// Adafruit_BNO055 bno = Adafruit_BNO055(55);
// Adafruit_BNO055 bno2 = Adafruit_BNO055(56);

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
    Serial.print("Ooops, no BNO055_1 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);

  /* Display the current temperature */
  int8_t temp = bno.getTemp();
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println("");

  bno.setExtCrystalUse(true);

  Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");


  if(!bno2.begin())
    {
      /* There was a problem detecting the BNO055 ... check your connections */
      Serial.print("Ooops, no BNO055_2 detected ... Check your wiring or I2C ADDR!");
      while(1);
    }

    delay(1000);

    /* Display the current temperature */
    int8_t temp2 = bno2.getTemp();
    Serial.print("Current Temperature_2: ");
    Serial.print(temp2);
    Serial.println(" C_2");
    Serial.println("");

    bno2.setExtCrystalUse(true);

    Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");
  
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
  imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);


  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(euler.x());
  Serial.print(" Y: ");
  Serial.print(euler.y());
  Serial.print(" Z: ");
  Serial.print(euler.z());
  Serial.print("\t\t");


  imu::Vector<3> euler2 = bno2.getVector(Adafruit_BNO055::VECTOR_EULER);
  /* Display the floating point data */
  Serial.print("X2: ");
  Serial.print(euler2.x());
  Serial.print(" Y2: ");
  Serial.print(euler2.y());
  Serial.print(" Z2: ");
  Serial.print(euler2.z());
  Serial.println("\t\t");

  //====Value=to=voltage=conversion==========================

  //x-volts
  // Serial.print("X_volts: ");
  // Serial.print((0 * (1 - (euler.x()/360))) + 3.3*(euler.x()/360));


  // //y-volts
  // Serial.print(" Y_volts: ");
  // Serial.print(  (0 * (1 - ( (euler.y()+ 90 ) / 180))) +   (3.3*((euler.y()+90)/180))  );

  // //z-volts
  // Serial.print(" Z_volts: ");
  // Serial.print(  (0 * (1 - ( (euler.z()+ 180 ) / 360))) +  (3.3*((euler.z()+180)/360)) );
  
  
  
  
  
  // Serial.print("\t\t");

  // Serial.print("X_volts: ");
  // Serial.print((0 * (1 - (euler2.x()/360))) + 3.3*(euler2.x()/360));


  // //y-volts
  // Serial.print(" Y_volts: ");
  // Serial.print(  (0 * (1 - ( (euler2.y()+ 90 ) / 180))) +   (3.3*((euler2.y()+90)/180))  );

  // //z-volts
  // Serial.print(" Z_volts: ");
  // Serial.print(  (0 * (1 - ( (euler2.z()+ 180 ) / 360))) +  (3.3*((euler2.z()+180)/360)) );
  
  
  
  
  
  // Serial.print("\t\t");



//
//  
//  Serial.print(" Y_voltage: ");
//  Serial.print(euler.y());
//  Serial.print(" Z_volatege: ");
//  Serial.print(euler.z());














 //==========================================================


  /* Display calibration status for each sensor. */
  // uint8_t system, gyro, accel, mag = 0;
  // bno.getCalibration(&system, &gyro, &accel, &mag);
  // Serial.print("CALIBRATION: Sys=");
  // Serial.print(system, DEC);
  // Serial.print(" Gyro=");
  // Serial.print(gyro, DEC);
  
  // Serial.print(" Accel=");
  // Serial.print(accel, DEC);
  // Serial.print(" Mag=");
  // Serial.println(mag, DEC);

  // delay(BNO055_SAMPLERATE_DELAY_MS);
}







  /*
  // Quaternion data
  imu::Quaternion quat = bno.getQuat();
  Serial.print("qW: ");
  Serial.print(quat.w(), 4);
  Serial.print(" qX: ");
  Serial.print(quat.y(), 4);
  Serial.print(" qY: ");
  Serial.print(quat.x(), 4);
  Serial.print(" qZ: ");
  Serial.print(quat.z(), 4);
  Serial.print("\t\t");
  */

