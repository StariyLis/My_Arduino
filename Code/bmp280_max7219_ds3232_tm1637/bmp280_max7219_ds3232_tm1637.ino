#include "LedControl.h"
#include <Wire.h>
#include <SPI.h>

#include "TM1637.h"
#define CLK 3       
#define DIO 2
TM1637 tm1637(CLK,DIO);

#include <iarduino_RTC.h>
iarduino_RTC time(RTC_DS3231);  

#include <Adafruit_BMP280.h>
Adafruit_BMP280 bme; // I2C
LedControl disp =LedControl(12,11,10,1);

void setup() {
	tm1637.init();
	tm1637.set(BRIGHTEST);
	time.begin();
	pinMode(4, INPUT_PULLUP);

	bme.begin();

	disp.shutdown(0,false);
	disp.setIntensity(0,1);
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



	int8_t ListDisp[4];
	time.gettime();

	ListDisp[0] = time.Hours /10;
	ListDisp[1] = time.Hours %10;
	ListDisp[2] = time.minutes /10;
	ListDisp[3] = time.minutes %10;

	tm1637.display(0,ListDisp[0]);
	tm1637.display(1,ListDisp[1]); 
	tm1637.display(2,ListDisp[2]);
	tm1637.display(3,ListDisp[3]);
	(digitalRead(4)== 1) ? tm1637.point(0) : tm1637.point(1);

}


