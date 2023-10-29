#include <Arduino.h>
HardwareSerial uart2(PA3, PA2);

void setup() 
{
  uart2.begin(115200);
  uart2.printf("Clock speed: %d Hz", SystemCoreClock);
}

void loop() 
{

}
