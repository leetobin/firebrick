#!/bin/sh
#
# image <source> <evidence dir> <evidence file no extension>
# last edit 17/06/2013 - Lee Tobin

checkDest=$(mount | grep firestor)
if [ "$checkDest" == "" ] 
then
  lcd c
  lcd g 0 1; lcd p "Storage isn't"
  lcd g 0 2; lcd p "initialised"
  sleep 2
  lcd c
  exit 1
fi

stty intr '^['
trap 'echo "Grapped"; stty intr "" ; exit 1' INT

lcd c
lcd g 0 0 ; lcd p "Imaging..."
lcd g 0 1 ; lcd p "ESC to Stop"

dcfldd if=/dev/$evidenceDisk conv=noerror statusinterval=2048 hash=md5 split=256M of="$2/$3" hashlog="$2/hashlog.log" 2>&1 | tr -d "()ocwriten." | lcd j 0 3

imghash=$(tail -n 1 "$2/hashlog.log" | grep -o "[0-9a-f]*" | tail -n 1)

echo $imghash

stty intr ''
exit 0

