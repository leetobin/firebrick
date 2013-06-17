#!/bin/sh
#
# Firebrick 
#

newdate=''
newtime=''
while [ "$key" != "3" ]; do
	lcd c
	lcd g 0 0 ; lcd p "1. Set Date"
	lcd g 0 1 ; lcd p "2. Set Time" 
	lcd g 0 2 ; lcd p "3. Back"
	lcd g 0 3 ; lcd p "$(date +\(%H:%M\)%Y-%m-%d)"
	stty raw; read -n 1 key; stty -raw
	lcd c
	case "$key" in
		1)
			lcd c
			lcd g 0 0 ; lcd p "$(date +\"%Y-%m-%d\")"
			lcd g 0 1 ; lcd p "Input date:"
			lcd g 0 2 ; lcd p "YYYY-MM-DD"
			stty raw; newdate=$(lcd i 0 3 20); stty -raw
                        date -s "$newdate $(date +%H:%M:%S)"
			;;
		2) 	
			lcd c
			lcd g 0 0 ; lcd p "$(date +\"%H:%M:%S\")"
			lcd g 0 1 ; lcd p "Input time:"
			lcd g 0 2 ; lcd p "HH:MM:SS"
			stty raw; newtime=$(lcd i 0 3 20); stty -raw
			date -s "$(date +%Y-%m-%d) $newtime"
			;;
		*)
			
	esac

done