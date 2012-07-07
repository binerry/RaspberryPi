/*
=================================================================================
 Name        : rtc_ds1307.c
 Version     : 0.1

 Copyright (C) 2012 by Andre Wussow, 2012, desk@binerry.de

 Description :
     A simple test for querying the RTC DS1307.

	 Connection (http://www.raspberrypi.org/archives/384):
	 DS1307 pins   Raspberry Pi    Other
	 1 - X1                        Clock oscillator X1
	 2 - X2                        Clock oscillator X2
	 3 - VBat                      Coin cell battery CR2032 3V
	 4 - GND       P05 - GND
	 5 - Vcc       P01 - 5V
	 6 - SQW/OUT   
	 7 - SCL       P04 - SCL0
	 8 - SDA       P02 - SDA0 
	 
 References  :
 http://binerry.de/post/26685647322/raspberry-pi-and-i2c
 http://pdfserv.maxim-ic.com/en/ds/DS1307.pdf

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
#include <stdio.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
 
int main (void)
{
	// print infos
	printf("Raspberry Pi RTC DS1307 Sample\n");
	printf("========================================\n");
  
	int deviceHandle;
	int readBytes;
	char buffer[7];
  
	// initialize buffer
	buffer[0] = 0x00;
  
	// address of DS1307 RTC device
	int deviceI2CAddress = 0x68;

	// open device on /dev/i2c-0
	if ((deviceHandle = open("/dev/i2c-0", O_RDWR)) < 0) {
		printf("Error: Couldn't open device! %d\n", deviceHandle);
		return 1;
	}

	// connect to DS1307 as i2c slave
	if (ioctl(deviceHandle, I2C_SLAVE, deviceI2CAddress) < 0) {
		printf("Error: Couldn't find device on address!\n");
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
		// read response
		readBytes = read(deviceHandle, buffer, 7);
		if (readBytes != 7)
		{
			printf("Error: Received no data!");
		}
		else
		{
			// get data
			int seconds = buffer[0];	// 0-59
			int minutes = buffer[1];	// 0-59
			int hours = buffer[2];		// 1-23
			int dayOfWeek = buffer[3];	// 1-7
			int day = buffer[4];		// 1-28/29/30/31
			int month = buffer[5];		// 1-12
			int year = buffer[6];		// 0-99;
			
			// and print results
			printf("Actual RTC-time:\n");
			printf("Date: %x-%x-%x\n", year, month, day);
			printf("Time: %x:%x:%x\n", hours, minutes, seconds);
		}
	}	

	// close connection and return
	close(deviceHandle);
	return 0;
}