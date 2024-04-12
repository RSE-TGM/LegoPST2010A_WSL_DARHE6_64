#!/bin/ksh
#
#  Script:                      lg3debug.sh
#  Subsystem:           1
#  %version:            2 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Wed Feb 19 17:00:12 1997 %

dbx -I${LEGO}/tavole -I${HOME}/legocad/libut -I${HOME}/legocad/libut_reg/libreg  -I./proc  proc/lg3 core
