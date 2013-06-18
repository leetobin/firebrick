#!/bin/sh
#
# Firebrick main script
# last edit 17/06/2013 - Lee Tobin

#--- Check the LCD device nodes

#Get LCD location on USB bus
lcdnodeinfo=$(lsusb | grep 0403:c630)
IFS=' '
set --  $lcdnodeinfo
lcdnodedir=/dev/bus/usb/$2
lcdnode=$lcdnodedir/${4%?}
echo Found LCD on $lcdnode

if [ ! -e $lcdnode ] ; then 

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
		
		lcd c
		lcd o 190
		
		cd /scripts
	fi
fi

#Storage check
export storageDisk1=$(ls -la /sys/block | grep ata. | grep host2 | grep -o sd. | tail -1)
export storageDisk2=$(ls -la /sys/block | grep ata. | grep host3 | grep -o sd. | tail -1)

# check if /dev/sda and /dev/sdb are present and the same size
if [[ ${#storageDisk1} -gt 2  &&  ${#storageDisk2} -gt 2 ]] ; then
	export storageDevice="/dev/md0"
elif [ ${#storageDisk1} -gt 2 ] ; then
	export storageDevice="/dev/${storageDisk1}"
elif [ ${#storageDisk2} -gt 2 ] ; then
	export storageDevice="/dev/${storageDisk2}"	
#No disks!!!
else
	export storageDevice=""
fi

echo Storage found on:$storageDevice

sh main.sh 