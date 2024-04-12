#!/bin/ksh
#
#  Script:                      clean.sh
#  Instance:            1
#  %version:            1 %
#  Description:
#  %created_by:         famgr %
#  %date_created:       Mon May 19 17:38:27 1997 %
for var in `ps | grep server_mmi |  awk ' {print $1} '`
do
        kill -9 $var
done

