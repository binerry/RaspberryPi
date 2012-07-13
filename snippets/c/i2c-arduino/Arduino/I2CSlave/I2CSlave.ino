/*
=================================================================================
 Name        : I2CSlave.ino
 Version     : 0.1

 Copyright (C) 2012 by Andre Wussow, 2012, desk@binerry.de

 Description :
     Sample of controlling an Arduino connected to Raspberry Pi via I2C.

	 Recommended connection (http://www.raspberrypi.org/archives/384):
	 Arduino pins      I2C-Shifter      Raspberry Pi
	 GND                                P06  - GND
	 5V                5V
	 SDA               SDA2
	 SCL               SCL2
	                   3V3              P01 - 3.3V
	                   SDA1             P03 - SDA
	                   SCL1             P05 - SCL
	 D2                                               LED1 with 1k resistor to GND
	 D3                                               LED2 with 1k resistor to GND
	 D4                                               LED3 with 1k resistor to GND
	 D5                                               Relay with transistor driver

 
 References  :
 http://binerry.de/post/27128825416/raspberry-pi-with-i2c-arduino-slave
 
================================================================================
This sample is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This sample is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
================================================================================
*/
 
#include "Commander.h"
#include "Wire.h"

/*
  General Setup
*/
// define i2c commands
#define LED1_ON_COMMAND    "L11"
#define LED1_OFF_COMMAND   "L10"
#define LED2_ON_COMMAND    "L21"
#define LED2_OFF_COMMAND   "L20"
#define LED3_ON_COMMAND    "L31"
#define LED3_OFF_COMMAND   "L30"
#define RELAY_ON_COMMAND   "R11"
#define RELAY_OFF_COMMAND  "R10"

// define slave address (0x2A = 42 [the answer to the ultimate question of life, the universe, and everything ;)] )
#define SLAVE_ADDRESS 0x2A 

// instantiate i2cCommander
Commander commander = Commander();

// pin setup
int led1pin = 2;
int led2pin = 3;
int led3pin = 4;
int relaypin = 5;

// other vars
int answer = 0;

void setup() {                
  // initialize the digital pins for leds and relay as an output
  pinMode(led1pin, OUTPUT);
  pinMode(led2pin, OUTPUT);  
  pinMode(led3pin, OUTPUT);  
  pinMode(relaypin, OUTPUT);  
  
  // create commands for i2cCommander
  // led 1:
  Command_t cmdLed1On;
  cmdLed1On.execCommand = LED1_ON_COMMAND;
  cmdLed1On.callback = led1On;
  
  Command_t cmdLed1Off;
  cmdLed1Off.execCommand = LED1_OFF_COMMAND;
  cmdLed1Off.callback = led1Off;
  
  // led 2:
  Command_t cmdLed2On;
  cmdLed2On.execCommand = LED2_ON_COMMAND;
  cmdLed2On.callback = led2On;
  
  Command_t cmdLed2Off;
  cmdLed2Off.execCommand = LED2_OFF_COMMAND;
  cmdLed2Off.callback = led2Off;
  
  // led 3:
  Command_t cmdLed3On;
  cmdLed3On.execCommand = LED3_ON_COMMAND;
  cmdLed3On.callback = led3On;
  
  Command_t cmdLed3Off;
  cmdLed3Off.execCommand = LED3_OFF_COMMAND;
  cmdLed3Off.callback = led3Off;
  
  // relay:
  Command_t cmdRelayOn;
  cmdRelayOn.execCommand = RELAY_ON_COMMAND;
  cmdRelayOn.callback = relayOn;
  
  Command_t cmdRelayOff;
  cmdRelayOff.execCommand = RELAY_OFF_COMMAND;
  cmdRelayOff.callback = relayOff;
  
  // add commands to i2cCommander
  commander.addCommand(cmdLed1On);
  commander.addCommand(cmdLed1Off);
  commander.addCommand(cmdLed2On);
  commander.addCommand(cmdLed2Off);
  commander.addCommand(cmdLed3On);
  commander.addCommand(cmdLed3Off);
  commander.addCommand(cmdRelayOn);
  commander.addCommand(cmdRelayOff);
  
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
   
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
}

void loop() {
  
}

// callback for received data
void receiveData(int byteCount) 
{  
  String requestCommand = "";
  while(Wire.available())
  { 
     requestCommand = requestCommand + (char)Wire.read();
  }
  commander.processCommand(requestCommand);
}

// callback for sending data
void sendData()
{ 
  Wire.write(answer);  
  answer = 0;
}

void led1On(String command)
{
  // switch led 1 on
  digitalWrite(led1pin, HIGH);
  
  // reply with command and success info
  answer = 1; 
}

void led1Off(String command)
{
  // switch led 1 off
  digitalWrite(led1pin, LOW);
  
  // reply with command and success info
  answer = 1; 
}

void led2On(String command)
{
  // switch led 2 on
  digitalWrite(led2pin, HIGH);
  
  // reply with command and success info
  answer = 1; 
}

void led2Off(String command)
{
  // switch led 2 off
  digitalWrite(led2pin, LOW);
  
  // reply with command and success info
  answer = 1; 
}

void led3On(String command)
{
  // switch led 3 on
  digitalWrite(led3pin, HIGH);
  
  // reply with command and success info
  answer = 1; 
}

void led3Off(String command)
{
  // switch led 3 off
  digitalWrite(led3pin, LOW);
  
  // reply with command and success info
  answer = 1; 
}

void relayOn(String command)
{
  // switch relay 3 on
  digitalWrite(relaypin, HIGH);
  
  // reply with command and success info
  answer = 1; 
}

void relayOff(String command)
{
  // switch relay off
  digitalWrite(relaypin, LOW);
  
  // reply with command and success info
  answer = 1; 
}