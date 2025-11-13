// This code is to practie creating classes,
#include "Message.h"
#include "ColorSense.h"
#include "Enes100.h"

ColorSense colorOTV;
void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial);
  // Initialize all SubSystem libraries
  Enes100.begin("Hydro-Bombers", MATERIAL, 566, 1120, 51, 50); // teamname, missiontype, Aruco marker ID, classroom number, txpin num, rxpin num
  Enes100.println("[WifiCom] Connected...");
  colorOTV.start();
}


void loop() {
  while(Enes100.isConnected());
  Serial.print("X - ");
  Serial.println(Enes100.getX());
  Serial.print("Y - ");
  Serial.println(Enes100.getY());
  Serial.print("Theta - ");
  Serial.println(Enes100.getTheta());
  Serial.print("Visible? - ");
  Serial.println(Enes100.isVisible() ? "Yes" : "No");
}



// BELOW IS SIMULATION CODE
/*
#include "Arduino.h"
#include "Enes100.h"
#include "Tank.h"



void setup() {
    Enes100.begin("Simulator", FIRE, 566, 1120, 8, 9);
    Tank.begin();
    
    Enes100.println("Starting driving");
    Tank.setLeftMotorPWM(255);
    Tank.setRightMotorPWM(255);
}

void moveForward(int milliseconds){
    Tank.setLeftMotorPWM(255);
    Tank.setRightMotorPWM(255);
    delay(milliseconds);
    Tank.setLeftMotorPWM(0);
    Tank.setRightMotorPWM(0);
}
void moveBackward(int milliseconds){
    Tank.setLeftMotorPWM(-255);
    Tank.setRightMotorPWM(-255);
    delay(milliseconds);
    Tank.setLeftMotorPWM(0);
    Tank.setRightMotorPWM(0);
}
void rotateRight(int milliseconds){
    Tank.setLeftMotorPWM(255);
    Tank.setRightMotorPWM(-255);
    delay(milliseconds);
    Tank.setLeftMotorPWM(0);
    Tank.setRightMotorPWM(0);
}
void rotateLeft(int milliseconds){
    Tank.setLeftMotorPWM(-255);
    Tank.setRightMotorPWM(255);
    delay(milliseconds);
    Tank.setLeftMotorPWM(0);
    Tank.setRightMotorPWM(0);
}

void loop() {
    rotateRight(1000);
    rotateLeft(1000);
    moveForward(5000);
    moveBackward(3000);
    Enes100.print("X = "); Enes100.println(Enes100.getX());
    Enes100.print("Y = "); Enes100.println(Enes100.getY());
    Enes100.print("Theta = "); Enes100.println(Enes100.getTheta());
}
*/
