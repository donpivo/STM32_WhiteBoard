#include <Arduino.h>
#define PIN_ENCA PA0
#define PIN_ENCB PA1

volatile bool aFlag = false;
volatile bool bFlag = false;
volatile int16_t encPos = 0;
volatile int16_t oldEncPos = 0;
volatile uint16_t reading = 0;
HardwareSerial uart2(PA3, PA2);

void isrENCA();
void isrENCB();

void setup() 
{
  pinMode(PIN_ENCA, INPUT_PULLUP);
  pinMode(PIN_ENCB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCA), isrENCA, RISING);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCB), isrENCB, RISING);
  uart2.begin(115200);
  uart2.println("Rotary encoder test");
}


void loop()
{
  if(oldEncPos!=encPos) 
  {
    uart2.println(encPos);
    oldEncPos = encPos;
  }
}


void isrENCA()
{
  noInterrupts();
  reading = GPIOA->IDR & 0x3;
  if(reading == 0b0000000000000011 && aFlag) 
  {
    encPos--;
    bFlag = 0;
    aFlag = 0;
  }
  else if (reading == 0b0000000000000001) bFlag = 1;
  interrupts();
}

void isrENCB()
{
  noInterrupts();
  reading = GPIOA->IDR & 0x3;
  if (reading == 0b0000000000000011 && bFlag) 
  {
    encPos++;
    bFlag = 0;
    aFlag = 0;
  }
  else if (reading == 0b0000000000000010) aFlag = 1;
  interrupts();
}