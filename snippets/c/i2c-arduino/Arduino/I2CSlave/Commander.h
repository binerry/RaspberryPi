/*
=================================================================================
 Name        : Commander.h
 Version     : 0.1

 Copyright (C) 2012 by Andre Wussow, 2012, desk@binerry.de

 Description :
     Commander library for Arduino as i2c-slave for processing commands/actions.

 References  :
 http://binerry.de/post/27128825416/raspberry-pi-with-i2c-arduino-slave
 
================================================================================
This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
================================================================================
*/
#include "Arduino.h"

// ensure this library description is only included once:
#ifndef Commander_h
#define Commander_h

// constants:
#define MAX_COMMANDS 8     // max supported commands

// structs:
// Command-Struct:
typedef struct {
  String execCommand;                  // command for execution
  void (*callback)(String);            // callback function 
  uint8_t isActive   :1;               // true if this command is enabled 
} Command_t;

// Commander library interface description:
class Commander {
  public:
    // constructor:
    Commander();
    
    // methods:
    void addCommand(Command_t command);
    void processCommand(String command);
  private:
    // properties
    Command_t commands[MAX_COMMANDS];
};
#endif