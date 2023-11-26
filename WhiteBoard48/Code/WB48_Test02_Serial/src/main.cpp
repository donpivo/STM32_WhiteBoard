#include <Arduino.h>
HardwareSerial uart2(PA3, PA2);

void setup() 
{
  uart2.begin(115200);
}

void loop() 
{
  delay(1000);
  uart2.printf("Clock speed: %d Hz\n", SystemCoreClock);
}
