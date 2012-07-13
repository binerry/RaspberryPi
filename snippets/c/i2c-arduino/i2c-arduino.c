/*
=================================================================================
 Name        : i2c-arduino.c
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

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <stdio.h>
#include <unistd.h>

int deviceHandle;
int readBytes;
char buffer[7];

void testCommand(char command[3], char identifier[5]);
	
int main (void)
{
	// print infos
	printf("Raspberry Pi I2C Arduino Sample\n");
	printf("========================================\n");
	
	// initialize buffer
	buffer[0] = 0x00;
  
	// address of i2c Arduino device
	int deviceI2CAddress = 0x2A;  // (0x2A = 42)
	
	// open device on /dev/i2c-0
	if ((deviceHandle = open("/dev/i2c-0", O_RDWR)) < 0) {
		printf("Error: Couldn't open device! %d\n", deviceHandle);
		return 1;
	}
	
	// connect to arduino as i2c slave
	if (ioctl(deviceHandle, I2C_SLAVE, deviceI2CAddress) < 0) {
		printf("Error: Couldn't find arduino on address!\n");
		return 1;
	}  
	
	// begin transmission and request acknowledgement
	readBytes = write(deviceHandle, buffer, 1);
	if (readBytes != 1)
	{
		printf("Error: Received no ACK-Bit, couldn't established connection!");
	}
	else
	{
		// drive some tests
		testCommand("L11", "LED1 on");
		usleep(2000000); // 2s
		testCommand("L10", "LED1 off");
		usleep(2000000); // 2s
		testCommand("L21", "LED2 on");
		usleep(2000000); // 2s
		testCommand("L20", "LED2 off");
		usleep(2000000); // 2s
		testCommand("L31", "LED3 on");
		usleep(2000000); // 2s
		testCommand("L30", "LED3 off");
		usleep(2000000); // 2s
		testCommand("R11", "Relay on");
		usleep(2000000); // 2s
		testCommand("R10", "Relay off");
	}
	
	// close connection and return
	close(deviceHandle);
	return 0;
}

// function for testing command
void testCommand(char command[3], char action[10])
{
	// switch on
	printf("Switching %s ... ", action);		
	readBytes = write(deviceHandle, command, 3);
		
	// give arduino some reaction time
	usleep(100000); // 100ms
		
	// read success
	readBytes = read(deviceHandle, buffer, 1);
	if (readBytes != 1)
	{
		printf("Error: Received no data!");
	}
	else
	{
		// check response: 0 = error / 1 = success
		if (buffer[0] == 1)
		{
			printf("OK!\n");
		}
	}
}