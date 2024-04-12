#!/bin/ksh
# 
#  Script:			clean.sh
#  Instance:		1
#  %version:		4 %
#  Description:		
#  %created_by:		lomgr %
#  %date_created:	Tue Aug  5 10:30:06 2003 %
export IO_SONO=`whoami`
for var in `ps -ef | grep $IO_SONO  | grep client_mmi | grep -v grep |  awk ' {print $2} '`
do
        kill -9 $var
done
for var in `ps -ef | grep $IO_SONO  | grep client_scada | grep -v grep |  awk ' {print $2} '`
do
        kill -9 $var
done
for var in `ps -ef | grep $IO_SONO  | grep demone_mmi | grep -v grep |  awk ' {print $2} '`
do
        kill -9 $var
done
for var in `ps -ef | grep $IO_SONO  | grep server_mmi | grep -v grep |  awk ' {print $2} '`
do
        kill -9 $var
done
if [ $OS = "Linux" ]
then
	for var in ` ipcs -q | grep $USER | cut -f2 -d' ' `
	do
        	ipcrm msg $var
	done
else
	for var in ` ipcs -q | grep $USER | awk ' /q/ { print $2 } ' `
	do
        	ipcrm -q $var
	done
fi
if [ $OS = "Linux" ]
then
	for var1 in ` ipcs -m | grep $USER | grep -v "0x3e7" | grep -v "999" |  cut -f2 -d' ' `
	do
        	ipcrm shm $var1
	done
else
	for var1 in ` ipcs -m | grep $USER | grep -v "0x3e7" | grep -v "999" | awk ' /m/ { print $2 } ' `
	do
        	ipcrm -m $var1
	done
fi
if [ $OS = "Linux" ]
then
	for var2 in ` ipcs -s | grep $USER | cut -f2 -d' ' `
	do
        	ipcrm sem $var2
	done
else
	for var2 in ` ipcs -s | grep $USER | awk ' /s/ { print $2 } ' `
	do
        	ipcrm -s $var2
	done
fi
