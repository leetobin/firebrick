#!/bin/sh
#
# Firebrick main script
# 
lcd o 190
#lcd c
#lcd g 0 1; lcd p "FIRE Brick v1.0"
#lcd g 0 2; lcd p "http://dfire.ucd.ie/"
	
hpa=$(hdparm -N /dev/sdc | grep "HPA is enabled")
if [ "$hpa" != "" ] 
then
   lcd c
   lcd g 0 0; lcd p "Detected HPA "
   lcd g 0 1; lcd p "on target drive " 
   lcd g 0 3; lcd p "Disable? (y/n) "
   stty raw; read -n 1 key ; stty -raw
fi

#try to assemble raid
mdadm --assemble /dev/md0 /dev/sda /dev/sdb
fdisk -l
sleep 1
fdisk -l
sh main.sh 