#!/bin/bash
#
#=================================================================================
# Name        : sipcall-sample.sh
# Version     : 0.1
#
# Copyright (C) 2012 by Andre Wussow, 2012, desk@binerry.de
#
# Description :
#     Sample Script for checking average load and making call with sipcall.
#
# Dependencies:
#	- sipcall
# 
# References  :
# http://binerry.de/post/29180946733/raspberry-pi-caller-and-answering-machine
# 
#================================================================================
#This script is free software; you can redistribute it and/or
#modify it under the terms of the GNU Lesser General Public
#License as published by the Free Software Foundation; either
#version 2.1 of the License, or (at your option) any later version.
#
#This script is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#Lesser General Public License for more details.
#================================================================================

# define sip-settings
sip_domain="samplesip.com";
sip_user="12345678";
sip_password="XXXXXX";
play_file="play.wav";

# define number to call
phone_number="0123456789";

# define allowed load limit
maxload=0;

# read actual load values
avgload1="$(uptime |awk -F'average: ' '{print $2}' |awk -F', ' '{print $1}')";
avgload5="$(uptime |awk -F'average: ' '{print $2}' |awk -F', ' '{print $2}')";
avgload15="$(uptime |awk -F'average: ' '{print $2}' |awk -F', ' '{print $3}')";

# check average load within last 5 minutes
avgload="$(echo $avgload5 | awk -F',' '{print $1}')";

check="$(($avgload >= $maxload))";

# creating text to speak
tts="$(echo This is raspberry pi and the load is high. The average load within the last 5 minutes was $avgload5)";

if [ $check = 1 ]; then 
	# make call with sipcall
	$(./sipcall -sd $sip_domain -su $sip_user -sp $sip_password -pn $phone_number -s 1 -mr 2 -tts "$tts" -ttsf $play_file > /dev/null);
fi