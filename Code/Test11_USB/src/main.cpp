#include <Arduino.h>
#define PIN_BTN PD2
#define PIN_LED PC13


void setup() 
{
  pinMode(PIN_BTN, INPUT_PULLUP);
  pinMode(PIN_LED, OUTPUT);
}

void loop() 
{
  bool btnPressed=digitalRead(PIN_BTN);
  digitalWrite(PIN_LED, btnPressed);
  delay(1000);
}

