#include <Arduino.h>
#define LED_PIN PA15

void setup() 
{
  pinMode(LED_PIN, OUTPUT);
}

void loop() 
{
  digitalWrite(LED_PIN, HIGH);
  delay(100);
  digitalWrite(LED_PIN, LOW);
  delay(1000);
}

