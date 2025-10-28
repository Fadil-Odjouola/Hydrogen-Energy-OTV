#ifndef MESSAGE_H
#define MESSAGE_H
#include <Arduino.h>
// Note: In Arduino/C++, 'String' often implies the Arduino String class.
// For standard C++ projects, you would use '#include <string>' and 'std::string'.

class Message{
  private:
    String user_t;
    String message_t;
    static int numOfMessages;
  public:
    Message(String user, String message);
    String getMessage();
    String getUser();
    static int getNumOfMessages();
};

// If you are compiling this in a non-Arduino environment and need to keep it in a single header
// or if your environment is stricter, you must initialize the static member outside the class.
// Since you are not using a Message.cpp file, you may have to put the static definition
// in the .ino file or accept a compiler warning/error about non-standard initialization.

#endif // MESSAGE_H