// This code is to practice creating classes,
#include "Message.h"
#include "ColorSense.h"
#include "Enes100.h"
#include <math.h> // Include for PI and abs()

// Define the motor speed
static const int MOTOR_SPEED = 153;
const float OBSTACLE_DISTANCE_CM = 3.0;
const float OBSTACLE_DISTANCE_M = 0.03;
const int MOVE_SPEED = 180;
const int TURN_SPEED = 180;
const int TURN_DURATION = 850;
const int MOVE_46CM_DURATION = 2300;
const float Y_MIDPOINT = 0.89;
const int DISTANCE_SENSOR_ID = 1;
const float EPSILON = 0.89;
const float D_EPSILON = 5;

// Motor A Pin Definitions
int motorA_In1 = 9;
int motorA_In2 = 8;
int motorA_Enable = 10;

// Motor B Pin Definitions
int motorB_In1 = 12;
int motorB_In2 = 13;
int motorB_Enable = 11;

// Function Prototypes (Good practice, but not strictly required if defined before use)
void stopMotors();
void moveForward();
void rotateByTheta(float targetTheta, float OTVTheta);

void stopMotors() {
    analogWrite(motorA_Enable, 0);
    analogWrite(motorB_Enable, 0);
}
void rotateLeft(){
  
}
void rotateRight(int motorSpeed){
  // Motor a is right and motor b is left
    digitalWrite(motorA_In1, LOW);
    digitalWrite(motorA_In2, HIGH);
    analogWrite(motorA_Enable, motorSpeed);

    digitalWrite(motorB_In1, HIGH);
    digitalWrite(motorB_In2, LOW);
    analogWrite(motorB_Enable, motorSpeed);
}
/**
 * @brief Moves the robot forward at a specified speed.
 */
void moveForward(int motorSpeed) {
    digitalWrite(motorA_In1, HIGH);
    digitalWrite(motorA_In2, LOW);
    analogWrite(motorA_Enable, motorSpeed);

    digitalWrite(motorB_In1, HIGH);
    digitalWrite(motorB_In2, LOW);
    analogWrite(motorB_Enable, motorSpeed);
}

/**
 * @brief Moves the robot backward at a specified speed.
 */
void moveBackward() {
    digitalWrite(motorA_In1, LOW);
    digitalWrite(motorA_In2, HIGH);
    analogWrite(motorA_Enable, MOTOR_SPEED);

    digitalWrite(motorB_In1, LOW);
    digitalWrite(motorB_In2, HIGH);
    analogWrite(motorB_Enable, MOTOR_SPEED);
}

 void rotateByTheta(float targetTheta) {
    float angleDifference;

    do {
        float OTVTheta = Enes100.getTheta();
        
        angleDifference = radToDeg(targetTheta - OTVTheta);
        
        while (angleDifference > 180) {
            angleDifference -= 360.0;
        }
        while (angleDifference < -180) {
            angleDifference += 360.0;
        }

        if (abs(angleDifference) < EPSILON) {
            break;
        }
        
        float factor = abs(angleDifference / 180.0);
        
        if (angleDifference > 0) {
          rotateLeft(TURN_SPEED * factor);
        } else {
          rotateRight(TURN_SPEED * factor);
        }

        delay(50); 

    } while (true);

    stopMotors(); 
}

// ------- [IMPORTANT] Returns -1 if object is out of range,  returns a -------
long readDistanceSensor(){
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  return duration / 74 / 2;
}



ColorSense colorOTV;

void setup() {
  // --- ⚠️ CRITICAL CORRECTION: Pin Modes must be set in setup() ---
  pinMode(motorA_In1, OUTPUT);
  pinMode(motorA_In2, OUTPUT);
  pinMode(motorA_Enable, OUTPUT);
  pinMode(motorB_In1, OUTPUT);
  pinMode(motorB_In2, OUTPUT);
  pinMode(motorB_Enable, OUTPUT);
  pinMode(disTrigPin, INPUT);
  pinMode(dis
  // -----------------------------------------------------------------

  // Initialize serial communication
  Serial.begin(9600);
  while (!Serial);

  // Initialize all SubSystem libraries
  Enes100.begin("Hydro-Bombers", MATERIAL, 275, 1120, 50, 51); // teamname, missiontype, Aruco marker ID, classroom number, txpin num, rxpin num
  Enes100.println("[WifiCom] Connected...");
  colorOTV.start();
  
  // Ensure motors are off at start
  stopMotors(); 
}

void loop() {
    // The main Arduino loop already runs infinitely, so while(true) is redundant 
    // and often makes the code harder to debug. We'll remove it.
    
    // Check if an obstacle is detected within 25 cm
     if(Enes100.getX() >= 3.5){
         stopMotors();
        while(true){};
    }

    

    // [IMPORTANT] Make a float method for distance and converting cm to m
    if((readDistanceSensor() < 2) && !(readDistanceSensor() > 20)){
        stopMotors();
        // --- OBSTACLE HANDLING LOGIC ---
            Enes100.print("Obstacle found while at Y = ");
            Enes100.println(Enes100.getY());
            Enes100.print("Obstacle is ");
            Enes100.print(readDistanceSensor());
            Enes100.println(" meters away");
            
            if (Enes100.getY() > Y_MIDPOINT) {
                if (radToDeg(Enes100.getTheta()) < D_EPSILON && radToDeg(Enes100.getTheta()) > 0 - D_EPSILON) {
                    rotateByTheta(3*PI/2);
                }
                else if(Enes100.getTheta() > 0){
                    rotateByTheta(0);
                } else if (Enes100.getTheta() < 0) {
                    rotateByTheta(0);
                } 
            } else {
                if (radToDeg(Enes100.getTheta()) < D_EPSILON && radToDeg(Enes100.getTheta()) > 0 - D_EPSILON) {
                    rotateByTheta(PI/2);
                } else if (Enes100.getTheta() < 0) {
                    rotateByTheta(0);
                } else {
                    rotateByTheta(0);
                }
            }
            
            moveForward(MOTOR_SPEED);
            delay(500);
        
    } else {
        moveForward(MOTOR_SPEED);
    }
   
}
