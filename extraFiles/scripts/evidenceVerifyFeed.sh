#!/bin/sh

totlen=$(du -c $1.* | tail -n 1 | grep -o "[0-9]*")
runlen=0

for inp in $1.*
do
  flen=$(du $inp | grep -o "[0-9]*" | head -n 1)
  runlen=$(($flen + $runlen))
  lcd g 0 3 ; lcd p "$(( $runlen / ( $totlen / 100 ) ))%"
  cat $inp
done
