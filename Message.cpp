#include "Message.h"

int Message::numOfMessages = 0;

Message::Message(String user, String message){
  numOfMessages += 1;
  this->user = user;
  this->message = message;
}
String Message::getMessage(){
  return this->message;
}
String Message::getUser(){
    return this->user;
}
void Message::setMessage(String newMessage){
  this->message == newMessage;
}
void Message::setUser(String newUser){
  this->user = newUser;
}
int Message::getNumOfMessages(){
  return numOfMessages;
}
void Message::serialPrintMessage(){
  Serial.print(this->user);
  Serial.println("says: ");
  Serial.print("\"");
  Serial.print(this->message);
  Serial.print("\"\n");
}
