// This code is to practie creating classes,
// importing, and file architecture
#include "Message.h"

// Construct a custom made class instance
Message greeting("Fadil", "Hello, World");
void setup() {
  Serial.begin(9600);
  
  // Print a message using a class printMessage method
  Serial.print(greeting.getUser());
  Serial.println(" says:");
  Serial.println(greeting.getMessage() + "\n");
  Serial.print("Number of messages is - ");
  Serial.println(Message::getNumOfMessages());
  Message farewell("GurtYo", "Catch ya later");
  Serial.print("Now the number of messages is - ");
  Serial.print(Message::getNumOfMessages());
  
  
}

void loop() {

}
