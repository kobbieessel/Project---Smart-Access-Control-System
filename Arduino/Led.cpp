#include "Led.h"
#include <Arduino.h>

Led::Led(byte pin)
{
  this->pin = pin;
}

void Led::init()
{
  pinMode(pin, OUTPUT);
}

void Led::on()
{
  digitalWrite(pin, HIGH);
}

void Led::off()
{
  digitalWrite(pin, LOW);
}

void Led::fade(byte brightness = 255)
{
  analogWrite(pin, brightness);
}