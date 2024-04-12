#!/bin/sh
#
#  Script:			clip.sh
#  Instance:		1
#  %version:		3 %
#  Description:		
#  %created_by:		lomgr %
#  %date_created:	Tue Aug  5 15:39:02 2003 %

if [ $OS = "Linux" ] 
then
	for var in ` ipcs -q  | grep $USER | cut -f2 -d' ' `
	do
        	ipcrm msg $var
	done
	for var1 in ` ipcs -m | grep $USER | cut -f2 -d' ' `
	do
        	ipcrm shm $var1
	done
	for var2 in ` ipcs -s | grep $USER | cut -f2 -d' ' `
	do
        	ipcrm sem $var2
	done
else
	for var in ` ipcs -q | grep $USER | awk ' /q/ { print $2 } ' `
	do
        	ipcrm -q $var
	done
	for var1 in ` ipcs -m | grep $USER | awk ' /m/ { print $2 } ' `
	do
        	ipcrm -m $var1
	done
	for var2 in ` ipcs -s | grep $USER | awk ' /s/ { print $2 } ' `
	do
        	ipcrm -s $var2
	done
fi
