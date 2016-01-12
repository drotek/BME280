#include <Wire.h>
#include <SPI.h>
#include <Sensor_Master.h>
#include <BME280.h>

/*******************************************************************************************
This is an exemple for the BMP280 library 
Drotek BMP280 breakout board can be found here:
http://www.drotek.com/shop/en/home/751-bmp280-breakout-board.html
Please follow the 3 step configuration below.
*******************************************************************************************/

//////////////////////////////////Configuration//////////////////////////////////////////////
                                                                                           //
//First step, select your arduino board type by incomment the right line//                 //
//#define Arduino_UNO                                                                      //
#define Arduino_MEGA2560                                                                   //                                                                
/////////////////////////////////////////////////////////////////////////////////////////////                                                            
                                                                                           //
//Second step, select your wiring by incomment the right line//                            //
#define I2C                                                                                //
//#define Hardware_SPI                                                                     //
//#define Software_SPI                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////////
                                                                                           //
//Last step(only for software SPI), write the Pin used for software SPI//                  //
#define BME_SCK 39                                                                         //
#define BME_MISO 36                                                                        //
#define BME_MOSI 38                                                                        //
#define BME_CS 37                                                                          //
/////////////////////////////////////////////////////////////////////////////////////////////

#define SEALEVELPRESSURE_HPA (1013.25)

#ifdef I2C
  Adafruit_BME280 bme;
#endif

#ifdef Hardware_SPI
  #ifdef Arduino_UNO
    #define BME_CS 10
  #endif //Arduino_UNO
  
  #ifdef Arduino_MEGA2560
    #define BME_CS 53
  #endif //Arduino_MEGA2560
  
  Adafruit_BME280 bme(BME_CS);
#endif //Hardware_SPI
  
#ifdef Software_SPI
  Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO,  BME_SCK);
#endif //Software_SPI

void setup() {
  Serial.begin(9600);
  Serial.println(F("BME280 test"));

  if (!bme.begin()) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }
}

void loop() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" *C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
    delay(2000);
}
