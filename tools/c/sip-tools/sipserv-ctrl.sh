#!/bin/bash
#
#=================================================================================
# Name        : sipserv-ctrl.sh
# Version     : 0.1
#
# Copyright (C) 2012 by Andre Wussow, 2012, desk@binerry.de
#
# Description :
#     Sample Script for controlling sipserv.
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

# define config-file
serv_cfg="sipserv.cfg";

if [ $1 = "start" ]; then 
	# start sipserv in background
	$(./sipserv -s 1 --config-file $serv_cfg > /dev/null &);
	echo "sipserv started.";
fi

if [ $1 = "stop" ]; then 
	# stop sipserv 
	pid="$(ps aux | awk '/[s]ipserv/ {print $2}' | head -1)";
	$(kill $pid  > /dev/null);
	echo "sipserv stopped.";
fi