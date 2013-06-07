#!/bin/sh
#
# Firebrick Main menu
# 

while [ "$key" != "4" ]; do
	lcd c
	lcd g 0 0 ; lcd p "1.Set Date/Time"
	lcd g 0 1 ; lcd p "2.Storage"
	lcd g 0 2 ; lcd p "3.Imaging/Writeblock" 
	lcd g 0 3 ; lcd p "4.Power Down" 

	stty raw; read -n 1 key; stty -raw
	lcd c
	case "$key" in
		1)
			sh datetime.sh 
			;;
		2) 	
			sh storage.sh 
			;;
		3)
			sh writeblock.sh 
			;;
		4)
			poweroff
			sleep 10
			;;
		s)
			exit 0;
			;;
		*)
	esac
done