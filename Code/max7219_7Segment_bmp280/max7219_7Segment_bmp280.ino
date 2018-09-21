//We always have to include the library
#include "LedControl.h"
#include <Wire.h>
#include <SPI.h>
//#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bme; // I2C
LedControl disp =LedControl(12,11,10,1);

void setup() {
//  Serial.begin(9600);
//  Serial.println(F("BMP280 test"));  
  if (!bme.begin()) {  
    Serial.println("Could not find a valid BMP280 sensor, check wiring!");
    while (1);
  }
  
  disp.shutdown(0,false);
  /* Set the brightness to a medium values */
  disp.setIntensity(0,1);
  /* and clear the display */
  disp.clearDisplay(0);
}
void loop() { 
    int t = bme.readTemperature();
    int h = bme.readPressure()*0.0075;   
    
    disp.setDigit(0,7,(t*10)/100,false);
    disp.setDigit(0,6,((t*10)/10)%10,false);
    disp.setRow(0,5,0x63);
    disp.setRow(0,4,B01001110);
    disp.setDigit(0,2,h/100,false);
    disp.setDigit(0,1,(h/10)%10,false);
    disp.setDigit(0,0,h%10,false);

//    Serial.print("Temperature = ");
//    Serial.print(t);
//    Serial.println(" *C");
//    
//    Serial.print("Pressure = ");
//    Serial.print(h);
//    Serial.println(" mm Hg");
    


    delay(2000);
}
