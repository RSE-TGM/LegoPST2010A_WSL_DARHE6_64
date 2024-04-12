#!/bin/sh
#
#  Script:			proc_monit.sh
#  Instance:		1
#  %version:		2 %
#  Description:		
#  %created_by:		zanna %
#  %date_created:	Fri Jan 10 16:17:47 1997 %

while [ True ]
do
        clear
        echo "Per uscire Ctrl + c"
        #ps -o pid -o pcpu -o pmem -o command | sort -r -k 2
        ps -o pid,pcpu,pmem,command | sort -d -r -k 2 
        sleep 5
done
