#!/bin/ksh
#
#  Script:                      testerr.sh
#  Subsystem:           1
#  %version:            2 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Wed Feb 19 17:00:48 1997 %

exit `cat $1 |tr -d " "`
