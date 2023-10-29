#include <Arduino.h>
#include <IWatchdog.h>
HardwareSerial uart2(PA3, PA2);
uint32_t delayTime=100;


void setup() 
{
  uart2.begin(115200);
  uart2.println("\nStarting\n");
  IWatchdog.begin(1000000);
}

void loop() 
{
  uart2.printf("Uptime: %i ms. \n", millis());
  uart2.printf("Delay time: %i ms. \n", delayTime);
  delay(delayTime);
  IWatchdog.reload();
  delayTime+=100;
}

