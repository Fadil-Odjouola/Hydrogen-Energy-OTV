#include "Message.h"

int Message::numOfMessages = 0;

Message::Message(String user, String message){
  numOfMessages += 1;
  user_t = user;
  message_t = message;
}
String Message::getMessage(){
  return message_t;
}
String Message::getUser(){
    return user_t;
}
int Message::getNumOfMessages(){
  return numOfMessages;
}
