#include <Arduino.h>
#define analogPin PA0
HardwareSerial uart2(PA3, PA2);

void setup() 
{
  pinMode(analogPin, INPUT_ANALOG);
  uart2.begin(115200);
}

void loop() 
{
  uint16_t analogValue = analogRead(analogPin);
  uart2.println(analogValue);
  delay(1000);
}

