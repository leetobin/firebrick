#!/bin/sh
#
# Firebrick Initialise Storage script
# last edit 17/06/2013 - Lee Tobin

disk1=$(ls -la /sys/block | grep ata. | grep host2 | grep -o sd. | tail -1)
disk2=$(ls -la /sys/block | grep ata. | grep host3 | grep -o sd. | tail -1)

# check if /dev/sda and /dev/sdb are present and the same size
if ( test -d "/sys/block/$disk1" ) && ( test -d "/sys/block/$disk2" ) ; then
	read sdaSize < "/sys/block/$disk1/size"
	read sdbSize < "/sys/block/$disk2/size"
	if [ "$sdaSize" == "$sdbSize" ] ; then

		# initialise it
		lcd c
		lcd g 0 0 ; lcd p "Are you sure?"
		lcd g 0 1 ; lcd p "Input YES"

		stty raw ; ans=$(lcd i 0 2 20); stty -raw
		if [ "$ans" == "YES" ] ; then 

			lcd c
			lcd g 0 1; lcd p "Initialising RAID..." 
			yes | mdadm --create /dev/md0 --level=0 --raid-devices=2 /dev/$disk1 /dev/$disk2
			#create a new partition
			(echo o; echo n; echo p; echo 1; echo 1; echo; echo t; echo b; echo w) | fdisk /dev/md0
			mkfs.vfat /dev/md0p1
			#mount /dev/md0p1 /md0p1 
		fi
	else
		lcd c
		lcd g 0 0; lcd p "  RAID Problem:"
		lcd g 0 1; lcd p "  drives are"
		lcd g 0 2; lcd p "  different sizes"      
		sleep 2
	fi 

	else
	lcd c
	lcd g 0 0; lcd p "  RAID Problem:"
	lcd g 0 1; lcd p "  one of the drives"
	lcd g 0 2; lcd p "  not present" 
	sleep 2
fi
