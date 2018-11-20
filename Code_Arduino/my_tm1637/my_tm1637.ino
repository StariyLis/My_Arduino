#include "TM1637.h"

#define CLK 3//pins definitions for TM1637 and can be changed to other ports       
#define DIO 2
TM1637 tm1637(CLK,DIO);

#include <iarduino_RTC.h>
//iarduino_RTC time(RTC_DS1307);          // подключаем RTC модуль на базе чипа DS1307, используется аппаратная шина I2C
iarduino_RTC time(RTC_DS3231);          // подключаем RTC модуль на базе чипа DS3231, используется аппаратная шина I2C

void setup()
{
    tm1637.init();
    tm1637.set(BRIGHTEST);//   BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
    time.begin();
    pinMode(4, INPUT_PULLUP);
}

void loop() {
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
