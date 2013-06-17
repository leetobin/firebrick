#!/bin/sh
#
# Firebrick 
# last edit 17/06/2013 - Lee Tobin

#Check for storage
if ls -la /sys/block | grep ata. | grep host0 | grep -qo sd. 
then
	evidenceDisk=$(ls -la /sys/block | grep ata. | grep host0 | grep -o sd. | tail -1)
	#create the iblock backstore
		echo "Creating /sys/kernel/config/target/core/iblock_0/sbpStore"
	mkdir -p /sys/kernel/config/target/core/iblock_0/sbpStore
		echo "Adding udev_path=/dev/$evidenceDisk to control"
	echo "udev_path=/dev/$evidenceDisk" > /sys/kernel/config/target/core/iblock_0/sbpStore/control

	#echo "readonly=1" > /sys/kernel/config/target/core/iblock_0/sbpStore/control
		echo "Enabling /sys/kernel/config/target/core/iblock_0/sbpStore/enable"
	echo 1 > /sys/kernel/config/target/core/iblock_0/sbpStore/enable

	#create the sbp2 target
		echo "Creating /sys/kernel/config/target/sbp/0011066600000009/tpgt_1/lun/lun_0"
	mkdir -p /sys/kernel/config/target/sbp/0011066600000009/tpgt_1/lun/lun_0
		echo "Creating link"
	ln -s /sys/kernel/config/target/core/iblock_0/sbpStore /sys/kernel/config/target/sbp/0011066600000009/tpgt_1/lun/lun_0/sbpStore
		echo "Enabling /sys/kernel/config/target/sbp/0011066600000009/tpgt_1/enable"
	echo 1 > /sys/kernel/config/target/sbp/0011066600000009/tpgt_1/enable
else
	lcd c
	lcd g 0 0 ; lcd p "  Evidence drive"
	lcd g 0 1 ; lcd p "  not found!!"
	sleep 2
fi




#stty raw; read -n 1 key; stty -raw
#lcd c
#lcd g 0 0 ; lcd p "  Drive exported"
#lcd g 0 1 ; lcd p "  Press any key"
#lcd g 0 2 ; lcd p "  to poweroff..."
#poweroff