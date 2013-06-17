#!/bin/sh
#
# Firebrick 
# last edit 17/06/2013 - Lee Tobin

#check storage
if ls -la /sys/block | grep ata. | grep host2 | grep -q sd. && ls -la /sys/block | grep ata. | grep host3 | grep -q sd. 
then
	
	#
	lcd c
	lcd g 0 0 ; lcd p "1. Export"
	lcd g 0 1 ; lcd p "2. Initialise"
	lcd g 0 2 ; lcd p "3. Back" 
	  
	stty raw; read -n 1 key; stty -raw
	lcd c
	case "$key" in
		1)
			sh storageExport.sh 
			;;
		2) 	
			sh storageInit.sh 
			;;
		*)
			
	esac
else
	lcd c
	lcd g 0 0; lcd p "Storage Problem:"
	lcd g 0 1; lcd p "Missing a drive"
	sleep 2
fi