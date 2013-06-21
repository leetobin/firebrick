#!/bin/sh
#
# Write/Blocking & Imaging - no return
# last edit 17/06/2013 - Lee Tobin

#export evidential drive

if ls -la /sys/block | grep ata. | grep host0 | grep -qo sd.
then
	export evidenceDisk=$(ls -la /sys/block | grep ata. | grep host0 | grep -o sd. | tail -1)
	#Export the evidence drive
	sh evidenceExport.sh
	if [[ ${#storageDevice} -gt 2 ]] ; then
	
		#if RAID not assembled, RAID assemble!
		if [[ $storageDevice -eq "/dev/md0" ]] ; then
			mdadm --assemble /dev/md0 /dev/$storageDisk1 /dev/$storageDisk2
			fdisk -l
			sleep 3
			fdisk -l
		fi

		#mount the storage
		echo mounting "${storageDevice}1" on /firestor
		mount "${storageDevice}1"  /firestor

		trap 'echo "ignoring"' INT

		lcd c

		while [ 1 == 1 ]
		do
			lcd g 0 0 ; lcd p "1. Image & verify"
			lcd g 0 1 ; lcd p "2. Power off"
			lcd g 0 3 ; lcd p "Free:"
			df -h | grep firestor | tr -s " " | cut -d ' ' -f 4 | tr -d $"\n" | lcd j 6 3

			stty raw; read -n 1 key ; stty -raw
			case $key in
			1)
				evidenceID=''
				while [ "$evidenceID" == "" ]
				do
				lcd c
				lcd g 0 1 ; lcd p "Enter Evidence ID:"

				stty raw
				evidenceID=$(lcd i 0 2 20 | tr -d "?*/\\><|")
				stty -raw

				destDir="/firestor/$evidenceID"      
				if test -d destDir 
				then
				  lcd c
				  lcd g 0 1 ; lcd p "Evidence ID Exists!"
				  sleep 2
				  evidenceID=''
				fi
				done

				mkdir $destDir

				imghash=$(./evidenceImage.sh /dev/$evidenceDisk $destDir $evidenceID)
				exitCode=$?

				if [ $exitCode != 0 ]
				then
				lcd c 
				lcd g 0 1 ; lcd p "Imaging Failed"
				lcd g 0 2 ; lcd p "Deleting image"
				rm -r $destDir/*
				rmdir $destDir
				else
				./evidenceVerify.sh $destDir $evidenceID $imghash
				exitCode=$?
				if [ $exitCode != 0 ]
				then
				   lcd c 
				   lcd g 0 1 ; lcd p "Verification falied"
				   lcd g 0 2 ; lcd p "Deleting image"
				   rm -r $destDir/*
				   rmdir $destDir
				else
				   lcd c
				   lcd g 0 1 ; lcd p "Verification Success"
				   sleep 1
				fi    
				fi

				lcd c
				;;

			2)
				poweroff
				sleep 10
				;;
			s)
				lcd c
				exit
				;;
			*)
				;;
			esac
		done
	else
		lcd c
		lcd g 0 0 ; lcd p "Evidence exported"
		lcd g 0 1 ; lcd p "Press any key"
		lcd g 0 2 ; lcd p "to poweroff..."
		stty raw; read -n 1 key; stty -raw
		poweroff
		sleep 10
	fi

else
	lcd c
	lcd g 0 0 ; lcd p "  Evidence drive"
	lcd g 0 1 ; lcd p "  not found!!"
	sleep 2
fi