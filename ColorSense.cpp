#include "ColorSense.h"


ColorSense::ColorSense(){
  this->r = 0;
  this->g = 0;
  this->b = 0;
  this->c = 0;
  this->isConnected = false;
  this->tcs = NULL;
}
void ColorSense::start(){
  this->tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_24MS, TCS34725_GAIN_1X);
  if (this->tcs.begin()) {
    this->isConnected = true;
    Serial.println("[ColorSense] Found sensor"); // Ready to get readings
  } else {
    this->isConnected = false;
    Serial.println("[ColorSense] No TCS34725 found ... check your connections");
  }
}

void ColorSense::sample(){  
  if(!isConnected){
    Serial.println("[ColorSense] No TCS34725 found ... check your connection");
    Serial.println("[ColorSense] Check your SDA and SCL. Also, VIN goes to 5v");
    return;
  }
  
  // Temp raw value variables
  uint16_t r_raw, g_raw, b_raw, c_raw;
  
  // Accumulation variables
  unsigned long r_sum = 0;
  unsigned long g_sum = 0;
  unsigned long b_sum = 0;
  unsigned long c_sum = 0;
  const int num_samples = 5;
  
  // An Average of 5 samples
  for(int i = 0; i < num_samples; i++){
    this->tcs.getRawData(&r_raw, &g_raw, &b_raw, &c_raw);
    r_sum += r_raw;
    g_sum += g_raw;
    b_sum += b_raw;
    c_sum += c_raw;
    
  }
  
  this->r = (int)r_sum / num_samples;
  this->g = (int)g_sum / num_samples;
  this->b = (int)b_sum / num_samples;
  this->c = (int)c_sum / num_samples;
  
}

String ColorSense::color(){
  // ColorSense::sample();
  if(!isConnected){
    Serial.println("[ColorSense] No TCS34725 connected");
    return "N/A";
  }
  
  int threshold = 150;
  if (this->r > this->g && this->r > this->b) {
    if (this->g > this->b && this->r - this->g < 50) return "yellow"; // Red + green ≈ yellow
    return "red";
  } else if (this->g > this->r && this->g > this->b) {
    return "green";
  } else if (this->b > this->r && this->b > this->g) {
    return "blue";
  } else if (this->r > threshold && this->g > threshold && this->b > threshold) {
    return "white";
  }
  return "none";
}

void ColorSense::printData(){
  if(!isConnected){
    Serial.println("[ColorSense] No TCS34725 found ... check your connection");
    Serial.println("[ColorSense] Check your SDA and SCL. Also, VIN goes to 5v");
    return;
  }
  
  Serial.println("[ColorSense]");
  Serial.print("R - ");
  Serial.println(this->r);
  Serial.print("G - ");
  Serial.println(this->g);
  Serial.print("B - ");
  Serial.println(this->b);
  Serial.print("C - ");
  Serial.println(this->c);
}
