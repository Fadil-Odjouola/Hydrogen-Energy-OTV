# Hydrogen-Energy-OTV

# ColorSense
Class of methods for the TCS34725
## Private Adafruit_TCS34725 tcs; 
The sensor itself
## Private bool isConnected; 
Connection status
## Private uint16_t r, g, b, c;
Red, Green, Blue, Lumen Data
## ColorSense(); 
Initializes TCS34725 sensor 
## void start(); 
Tries connecting to the TCS34725
## void sample(); 
Calculates the average of 5 rgbc readings
## void printData(); 
Prints current RGB sample to serial

