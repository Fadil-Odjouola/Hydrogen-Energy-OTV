// This code is to practie creating classes,
#include "Message.h"
#include "ColorSense.h"

void setup() {
  Serial.begin(9600);
  
  ColorSense colorOTV;
  colorOTV.sample();
  colorOTV.printData();
  // For now, color values are low
  // Test for sensitivity with LEDs
  // Increase intergration time if sensitivity to the LEDs is too low
  
}

void loop() {

}
