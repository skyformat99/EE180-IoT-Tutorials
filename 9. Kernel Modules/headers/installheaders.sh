#!/bin/bash

ar x $PWD/linux-headers-3.10.17-poky-edison_3.10.17-poky-edison-1_i386.deb

tar x -f $PWD/data.tar.gz

unamestr=$(uname -r)
if [[ "$unamestr" == '3.10.98-poky-edison+' ]]; then
	ln -s $PWD/usr/src/linux-headers-3.10.17-poky-edison $PWD/usr/src/linux-headers-3.10.98-poky-edison+
	echo "#define UTS_RELEASE \"3.10.98-poky-edison+\"" > $PWD/usr/src/linux-headers-3.10.17-poky-edison/include/generated/utsrelease.h
	ln -s $PWD/usr/src/linux-headers-3.10.98-poky-edison+ /lib/modules/3.10.98-poky-edison+/build
else
	echo "#define UTS_RELEASE \"3.10.17-poky-edison+\"" > $PWD/usr/src/linux-headers-3.10.17-poky-edison/include/generated/utsrelease.h
	ln -s $PWD/usr/src/linux-headers-3.10.17-poky-edison /lib/modules/3.10.17-poky-edison+/build
fi

