/*
=================================================================================
 Name        : Commander.cpp
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
#include "Commander.h"

// constructor:
Commander::Commander()
{
  for (int i = 0; i < MAX_COMMANDS; i++) {
    this->commands[i].isActive = false;
  } 
}

// add command method:
void Commander::addCommand(Command_t command)
{
  for (int i = 0; i < MAX_COMMANDS; i++) {
    if (!this->commands[i].isActive)
    {
      this->commands[i] = command;
      this->commands[i].isActive = true;
      break;
    }
  }
}

// process command method:
void Commander::processCommand(String command)
{
  for (int i = 0; i < MAX_COMMANDS; i++) 
  {
    if (this->commands[i].isActive)
    { 
      if (this->commands[i].execCommand == command)
      {
        // call callback-function
        this->commands[i].callback(command);
        break;
      }
    }
  }
}