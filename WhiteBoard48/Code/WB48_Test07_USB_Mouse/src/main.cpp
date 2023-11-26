#include <Arduino.h>

#include "Mouse.h"

// set pin numbers for the five buttons:
const int upButton = PB3;
const int downButton = PB4;
const int leftButton = PB5;
const int rightButton = PB6;
const int mouseButton = PB7;

int range = 5;           // output range of X or Y movement; affects movement speed
int responseDelay = 10;  // response delay of the mouse, in ms


void setup() {
  // initialize the buttons' inputs:
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
  pinMode(mouseButton, INPUT_PULLUP);
  // initialize mouse control:
  Mouse.begin();
}

void loop() {
  // read the buttons:
  int upState = !digitalRead(upButton);
  int downState = !digitalRead(downButton);
  int rightState = !digitalRead(rightButton);
  int leftState = !digitalRead(leftButton);
  int clickState = !digitalRead(mouseButton);

  // calculate the movement distance based on the button states:
  int xDistance = (rightState-leftState) * range;
  int yDistance = (downState-upState) * range;

  // if X or Y is non-zero, move:
  if ((xDistance != 0) || (yDistance != 0)) {
    Mouse.move(xDistance, yDistance, 0);
  }

  // if the mouse button is pressed:
  if (clickState == HIGH) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  }
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }

  // a delay so the mouse doesn't move too fast:
  delay(responseDelay);
}