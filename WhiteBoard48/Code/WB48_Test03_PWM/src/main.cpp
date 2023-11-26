#include <Arduino.h>
#define PIN_PWM0A PB0
#define PIN_PWM1A PB1
#define PIN_PWM2A PB6
#define PIN_PWM3A PB7
#define PIN_PWM4A PB8
#define PIN_PWM5A PB9
#define PIN_PWM6A PA0 
#define PIN_PWM6B PA1
uint8_t pwmValue;
HardwareSerial uart2(PA3, PA2);

void setup() 
{
  uart2.begin(115200);
  uart2.println("PWM Test");
  pinMode(PIN_PWM0A, OUTPUT);
  pinMode(PIN_PWM1A, OUTPUT);
  pinMode(PIN_PWM2A, OUTPUT);
  pinMode(PIN_PWM3A, OUTPUT);
  pinMode(PIN_PWM4A, OUTPUT);
  pinMode(PIN_PWM5A, OUTPUT);
  pinMode(PIN_PWM6A, OUTPUT);
  pinMode(PIN_PWM6B, OUTPUT);
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
  delay(10);
}