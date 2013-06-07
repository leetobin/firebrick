#!/bin/sh
#
# Firebrick 
# 
umount /dev/md0p1

#create the iblock backstore
	echo "Creating /sys/kernel/config/target/core/iblock_0/sbpStore"
mkdir -p /sys/kernel/config/target/core/iblock_0/sbpStore
	echo "Adding udev_path=/dev/md0,readonly=1 to control"
echo "udev_path=/dev/md0" > /sys/kernel/config/target/core/iblock_0/sbpStore/control

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

lcd c
lcd g 0 0 ; lcd p "Storage exported"
lcd g 0 1 ; lcd p "Press any key"
lcd g 0 2 ; lcd p "to poweroff..."
stty raw; read -n 1 key; stty -raw
poweroff
sleep 10