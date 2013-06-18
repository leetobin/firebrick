#!/bin/sh
#
# Firebrick main script
# last edit 17/06/2013 - Lee Tobin

lcd c
lcd o 190

#lcd g 0 1; lcd p "FIRE Brick v1.0"
#lcd g 0 2; lcd p "http://dfire.ucd.ie/"

#--- Check the LCD device nodes
#Get LCD location on USB bus
lcdnodeinfo=$(lsusb | grep 0403:c630)
IFS=' '
set --  $lcdnodeinfo
lcdnodedir=/dev/bus/usb/$2
lcdnode=$lcdnodedir/${4%?}

if ! test -f $lcdnode; then 

	if [ ! -d $lcdnodedir ]; then
		#create dev dir
		mkdir $lcdnodedir
	fi
	#if test -f output/target/etc/init.d/S40network; then rm output/target/etc/init.d/S40network ; fi
	if [ ! -f $lcdnode ]; then
		#Get major and min dev ids
		deviceline=$(dmesg | grep 'idVendor=0403' | tail -1)
		set -- $deviceline
		cd /sys/bus/usb/devices/${4%?}

		majnum=$(grep MAJOR uevent)
		minnum=$(grep MINOR uevent)

		IFS='='
		set -- $majnum
		majnum=$2
		set -- $minnum
		minnum=$2

		#make the device node
		mknod $lcdnode c $majnum $minnum
		cd /scripts
	fi
fi

#Storage check
export storageDisk1=$(ls -la /sys/block | grep ata. | grep host2 | grep -o sd. | tail -1)
export storageDisk2=$(ls -la /sys/block | grep ata. | grep host3 | grep -o sd. | tail -1)

# check if /dev/sda and /dev/sdb are present and the same size
if [[ ${#storageDisk1} -gt 2  &&  ${#storageDisk2} -gt 2 ]] ; then
	export storageDevice="/dev/md0"
elif test -d "/sys/block/$storageDisk1" ; then
	export storageDevice="/dev/${storageDisk1}"
elif test -d "/sys/block/$storageDisk2" ; then
	export storageDevice="/dev/${storageDisk2}"	
#No disks!!!
else
	export storageDevice=""
fi

echo Storage found on:$storageDevice

sh main.sh 