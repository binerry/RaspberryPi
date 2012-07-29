/*
=================================================================================
 Name        : wdt_test.c
 Version     : 0.1

 Copyright (C) 2012 by Andre Wussow, 2012, desk@binerry.de

 Description :
     A simple test for working with the Raspberry Pi BCM2835 Watchdog.
	 
 References  :
 http://binerry.de/post/28263824530/raspberry-pi-watchdog-timer

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
#include <linux/watchdog.h> 
 
int main (int argc, char *argv[])
{
	// print infos
	printf("Raspberry Pi BCM2835 Watchdog Sample\n");
	printf("========================================\n");
  
	int deviceHandle;
	int disableWatchdog = 1;
	
	// test watchdog reset via t-param
	if (argc > 1) {
		if (!strncasecmp(argv[1], "-t", 2)) {
			disableWatchdog = 0;
		}
	}
	
	printf("Disabling watchdog before closing device: %d\n", disableWatchdog);

	// open watchdog device on /dev/watchdog
	if ((deviceHandle = open("/dev/watchdog", O_RDWR | O_NOCTTY)) < 0) {
		printf("Error: Couldn't open watchdog device! %d\n", deviceHandle);
		return 1;
	} 
	
	// get timeout info of watchdog (try to set it to 15s before)
	int timeout = 15;
	ioctl(deviceHandle, WDIOC_SETTIMEOUT, &timeout);
	ioctl(deviceHandle, WDIOC_GETTIMEOUT, &timeout);
	printf("The watchdog timeout is %d seconds.\n\n", timeout);
  
	// feed watchdog 3 times with heartbeats
	int i;
	for (i = 0; i < 3; i++) {
		printf("Feeding the dog with a heartbeat.\n");
		ioctl(deviceHandle, WDIOC_KEEPALIVE, 0);
		sleep(10);
	}
	
	if (disableWatchdog)
	{
		printf("Disable watchdog.\n");
		write(deviceHandle, "V", 1);
	}
	
	// close connection and return
	close(deviceHandle);
	return 0;
}