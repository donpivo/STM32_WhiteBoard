/*
Test the board with and without Watchdog jumper connected, 
and with and without the blinkPC13() function being called each loop, to see the difference.
*/

#include <Arduino.h>
HardwareSerial uart2(PA3, PA2);

void blinkPC13();

void setup() 
{
  uart2.begin(115200);
  uart2.println("Starting");
  pinMode(PC13, OUTPUT);
}

void loop() 
{
  uart2.printf("Uptime: %i ms. \n", millis());
  // blinkPC13();
  delay(100);
}

void blinkPC13()
{
  digitalWrite(PC13, HIGH);
  delay(5);
  digitalWrite(PC13, LOW);
}
