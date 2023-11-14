//Lib: https://github.com/stm32duino/STM32RTC
//
#include <Arduino.h>
#include <STM32RTC.h>
HardwareSerial uart2(PA3, PA2);

STM32RTC& rtc = STM32RTC::getInstance();

const byte seconds = 0;
const byte minutes = 33;
const byte hours = 12;
const byte weekDay = 6;
const byte day = 11;
const byte month = 11;
const byte year = 23;

void setup()
{
  uart2.begin(115200);

  rtc.setClockSource(STM32RTC::LSE_CLOCK); //LSI_CLOCK, LSE_CLOCK or HSE_CLOCK.

  rtc.begin(); 

  rtc.setTime(hours, minutes, seconds);
  rtc.setDate(weekDay, day, month, year);
}

void loop()
{
  uart2.printf("%02d/%02d/%02d ", rtc.getDay(), rtc.getMonth(), rtc.getYear());
  uart2.printf("%02d:%02d:%02d.%03d\n", rtc.getHours(), rtc.getMinutes(), rtc.getSeconds(), rtc.getSubSeconds());

  delay(1000);
}