#!/bin/ksh
#
#  Script:                      lg5debug.sh
#  Subsystem:           1
#  %version:            2 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Wed Feb 19 17:00:26 1997 %

dbx -I${LEGO}/tavole -I${LEGO}/sorglego/sub -I${LEGO}/sorglego/main  -I${HOME}/legocad/libut  -I${HOME}/legocad/libut_reg/libreg  -I./proc  proc/lg5sk core
