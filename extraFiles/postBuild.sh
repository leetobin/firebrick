#Add tty0 to secure shell access
if grep -F 'tty0' output/target/etc/securetty ; then
	echo 'tty0 line present not adding...'
else
	echo 'tty0 line NOT present adding...'
	echo 'tty0' >> output/target/etc/securetty 
fi

#Add fstab entries
if grep -F 'configfs' output/target/etc/fstab ; then
	echo 'configfs line present for configfs not adding...'
else
	echo 'configfs	/sys/kernel/config	configfs	defaults	0	0' >> output/target/etc/fstab 
fi

#if grep -F '/dev/sdd1' output/target/etc/fstab ; then
#	echo 'configfs line present for sdd1 not adding...'
#else
#	echo '/dev/sdd1	/mnt	ext2	defaults	0	0' >> output/target/etc/fstab 
#fi


#Add profile tweaks
if grep -F 'scripts' output/target/root/.profile ; then
	echo 'profile line present not adding...'
else
	echo 'profile line NOT present adding...'
	echo "cd /scripts" >> output/target/root/.profile
	echo "./init.sh" >> output/target/root/.profile
fi


if test -f output/target/bin/loginLee.sh ; then
	echo 'autologin present not adding...'
else
	echo 'autologin not present!'
	echo "#!/bin/sh" >> output/target/bin/loginLee.sh
	echo "exec /bin/login -f root" >> output/target/bin/loginLee.sh
fi

chmod +x output/target/bin/loginLee.sh

#Update inittab (not doing it now)
#/bin/sed -i -e '/# GENERIC_SERIAL$/s~^.*#~tty0::respawn:/bin/sh /root/.profile#~' output/target/etc/inittab
/bin/sed -i -e '/# GENERIC_SERIAL$/s~^.*#~tty0::respawn:/sbin/getty -l /bin/loginLee.sh -n -L tty0 115200 vt100 # GENERIC_SERIAL#~' output/target/etc/inittab


#Compile extra userspace apps
output/host/usr/bin/x86_64-buildroot-linux-uclibc-gcc -I output/staging/usr/include/ -L output/staging/usr/lib -L output/staging/lib -lusb -o output/target/usr/bin/lcd ../lcd/lcd.c

output/host/usr/bin/x86_64-buildroot-linux-uclibc-gcc -o output/target/usr/bin/setmax ../setmax/setmax.c

#Add this dir to filesystem
if ! test -d output/target/md0p1 ; then mkdir output/target/md0p1 ; fi
if ! test -d output/target/scripts ; then 
mkdir output/target/scripts
fi

cp -f ../extraFiles/scripts/* output/target/scripts/

#Copy extra files
cp -f ../extraFiles/S99Lee output/target/etc/init.d/ 

#Tweak firewire for read-only
cp -f ../extraFiles/sbp_target.c output/build/linux-3.8.5/drivers/target/sbp 
rm -f output/build/linux-3.8.5/drivers/target/sbp/sbp_target.o

#Cleanup network (not required)
if test -f output/target/etc/init.d/S40network; then rm output/target/etc/init.d/S40network ; fi

sh ../extraFiles/bash/me