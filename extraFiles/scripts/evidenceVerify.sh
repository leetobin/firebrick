#!/bin/sh
#
# verify <evidence dir> <evidence file no extension> <hash>
# last edit 17/06/2013 - Lee Tobin

stty intr '^['
trap 'echo "Trapped"; stty intr "" ;exit 1' INT

lcd c
lcd g 0 0 ; lcd p "Verifying..."
lcd g 0 1 ; lcd p "ESC to Stop"
./evidenceVerifyFeed.sh $1/$2 | md5sum > verify.res
read hash <verify.res
if [ "$hash"="$3" ] ; then
   stty intr ''
   echo "Match"
   exit 0
else
   stty intr ''
   echo "Does not match"
   exit 1;
fi
