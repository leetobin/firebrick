lcd command line display manipulation utility
Based on test appliapplication by Till Harbaum 
http://www.harbaum.org/till/lcd2usb
----------------------------------------------------------------

Package libusb-dev must be istalled before compilation.

To compile, type 'make'

Usage: 
   lcd             - without any parameters will act like TEE
   lcd c           - erase LCD screen
   lcd g 2 5       - set cursor to the row 2 column 5
   lcd p "Hello"   - print Hello message on LCD and exit
   lcd o 123       - set LCD cOntrast to 123 
   lcd b 123       - set LCD brightness to 123 

