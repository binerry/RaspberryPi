/*
=================================================================================
 Name        : pcd8544_test2.c
 Version     : 0.1

 Copyright (C) 2010 Limor Fried, Adafruit Industries
 Raspberry Pi version by Andre Wussow, 2012, desk@binerry.de

 Description :
     A simple PCD8544 LCD (Nokia3310/5110) test for Raspberry PI PCD8544 Library. 
	 Based on Limor Fried's PCD8544 Arduino samples 
	 (https://github.com/adafruit/Adafruit-PCD8544-Nokia-5110-LCD-library/blob/master/examples/pcdtest/pcdtest.pde)
	 Makes use of WiringPI-library of Gordon Henderson (https://projects.drogon.net/raspberry-pi/wiringpi/)

	 Recommended connection (http://www.raspberrypi.org/archives/384):
	 LCD pins      Raspberry Pi
	 LCD1 - GND    P06  - GND
	 LCD2 - VCC    P01 - 3.3V
	 LCD3 - CLK    P11 - GPIO0
	 LCD4 - Din    P12 - GPIO1
	 LCD5 - D/C    P13 - GPIO2
	 LCD6 - CS     P15 - GPIO3
	 LCD7 - RST    P16 - GPIO4
	 LCD8 - LED    P01 - 3.3V 

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
 
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include "PCD8544.h"

// animation setup
#define NUMFLAKES 8
#define XPOS 0
#define YPOS 1
#define DELTAY 2

// pin setup
int _din = 1;
int _sclk = 0;
int _dc = 2;
int _rst = 4;
int _cs = 3;

// lcd contrast  
int contrast = 50;

// a bitmap of a 16x16 smiley icon
// get the bitmap assistance here! : http://en.radzio.dxp.pl/bitmap_converter/
// or here! : http://www.henningkarlsen.com/electronics/t_imageconverter_mono.php
const uint8_t smiley[]={
0x00, 0xE0, 0x30, 0x18, 0x0C, 0x66, 0x62, 0x02, 0x02, 0x62, 0x66, 0x0C, 0x18, 0x30, 0xE0, 0x00,   // 0x0010 (16) pixels
0x00, 0x07, 0x0C, 0x18, 0x30, 0x62, 0x44, 0x4C, 0x4C, 0x44, 0x62, 0x30, 0x18, 0x0C, 0x07, 0x00,   // 0x0020 (32) pixels
};
#define SMILEY_HEIGHT 16 
#define SMILEY_WIDTH  16 
  
int main (void)
{
  // print infos
  printf("Raspberry Pi PCD8544 animation test\n");
  printf("========================================\n");
  
  printf("CLK on Port %i \n", _sclk);
  printf("DIN on Port %i \n", _din);
  printf("DC on Port %i \n", _dc);
  printf("CS on Port %i \n", _cs);
  printf("RST on Port %i \n", _rst);  
  printf("========================================\n");
  
  // check wiringPi setup
  if (wiringPiSetup() == -1)
  {
	printf("wiringPi-Error\n");
    exit(1);
  }
  
  // init and clear lcd
  LCDInit(_sclk, _din, _dc, _cs, _rst, contrast);
  LCDclear();

  // turn all the pixels on (a handy test)
  uint8_t icons[NUMFLAKES][3];
  srandom(666);     // whatever seed
 
  // initialize
  int f;
  for (f=0; f< NUMFLAKES; f++) {
    icons[f][XPOS] = random() % LCDWIDTH;
    icons[f][YPOS] = 0;
    icons[f][DELTAY] = random() % 5 + 1;
  }
  
  while (1) {
    // draw each icon
    for (f=0; f< NUMFLAKES; f++) {
      LCDdrawbitmap(icons[f][XPOS], icons[f][YPOS], smiley, SMILEY_WIDTH, SMILEY_HEIGHT, BLACK);
    }
    LCDdisplay();
    delay(500);
    
    // then erase it + move it
    for (f=0; f< NUMFLAKES; f++) {
      LCDdrawbitmap(icons[f][XPOS], icons[f][YPOS],  smiley, SMILEY_WIDTH, SMILEY_HEIGHT, 0);
      // move it
      icons[f][YPOS] += icons[f][DELTAY];
      // if its gone, reinit
      if (icons[f][YPOS] > LCDHEIGHT) {
		icons[f][XPOS] = random() % LCDWIDTH;
		icons[f][YPOS] = 0;
		icons[f][DELTAY] = random() % 5 + 1;
      }
    }
  }
  
  return 0;
}