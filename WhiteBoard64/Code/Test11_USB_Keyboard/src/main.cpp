
#include <Arduino.h>
#include "Keyboard.h"

const int buttonPin = PD2;          // input pin for pushbutton


int previousButtonState = HIGH;   // for checking the state of a pushButton
int counter = 0;                  // button push counter

void setup() 
{
  // make the pushButton pin an input:
  pinMode(buttonPin, INPUT_PULLUP);
  // initialize control over the keyboard:
  Keyboard.begin();
  delay(1000);
  Keyboard.print("STM32 as keyboard");
}

void loop() 
{
  // read the pushbutton:
  int buttonState = digitalRead(buttonPin);
  // if the button state has changed,
  if ((buttonState != previousButtonState)
      // and it's currently pressed:
      && (buttonState == HIGH)) {
    // increment the button counter
    counter++;
    // type out a message
    Keyboard.print("You pressed the button ");
    Keyboard.print(counter);
    Keyboard.println(" times.");
  }
  // save the current button state for comparison next time:
  previousButtonState = buttonState;
}
