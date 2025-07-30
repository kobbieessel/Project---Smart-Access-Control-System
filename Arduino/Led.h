#ifndef LED_H
#define LED_H

#include <Arduino.h>

class Led
{
private:
  byte pin;
  byte brightness;

public:
  Led() {}; // do not use
  Led(byte pin);

  void init();
  void on();
  void off();
  void fade(byte brightness = 255);
};

#endif
