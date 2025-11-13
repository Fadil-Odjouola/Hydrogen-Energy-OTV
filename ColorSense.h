#ifndef COLORSENSE_H
#define COLORSENSE_H
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"
#include <math.h>

class ColorSense{
  private:
    Adafruit_TCS34725 tcs;
    bool isConnected;
    uint16_t r, g, b, c;
  public:
    ColorSense();
    void start();
    void sample();
    String color();
    void printData();
};


#endif // COLORSENSE_H
