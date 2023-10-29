#include <Arduino.h>
#define PIN_PWM0A PB7
#define PIN_PWM1A PB6
#define PIN_PWM2A PB5
#define PIN_PWM3A PB4
#define PIN_PWM4A PA15
#define PIN_PWM5A PA11
#define PIN_PWM6A PA10 
#define PIN_PWM6B PC8
#define PIN_PWM7A PB10 
#define PIN_PWM7B PB14

uint8_t pwmValue;

void setup() 
{
  Serial.begin(115200);
  Serial.println("PWM Test");
  pinMode(PIN_PWM0A, OUTPUT);
  pinMode(PIN_PWM1A, OUTPUT);
  pinMode(PIN_PWM2A, OUTPUT);
  pinMode(PIN_PWM3A, OUTPUT);
  pinMode(PIN_PWM4A, OUTPUT);
  pinMode(PIN_PWM5A, OUTPUT);
  pinMode(PIN_PWM6A, OUTPUT);
  pinMode(PIN_PWM6B, OUTPUT);
  pinMode(PIN_PWM7A, OUTPUT);
  pinMode(PIN_PWM7B, OUTPUT);
  analogWriteFrequency(20000);

}

void loop() 
{
  pwmValue++;
  if(pwmValue>=255) pwmValue=0;
  analogWrite(PIN_PWM0A,pwmValue);
  analogWrite(PIN_PWM1A,pwmValue);
  analogWrite(PIN_PWM2A,pwmValue);
  analogWrite(PIN_PWM3A,pwmValue);
  analogWrite(PIN_PWM4A,pwmValue);
  analogWrite(PIN_PWM5A,pwmValue);
  analogWrite(PIN_PWM6A,pwmValue);
  analogWrite(PIN_PWM6B,pwmValue);
  analogWrite(PIN_PWM7A,pwmValue);
  analogWrite(PIN_PWM7B,pwmValue);
  delay(10);
}