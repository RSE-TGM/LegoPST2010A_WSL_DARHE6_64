#!/bin/ksh
#
#!/bin/ksh
#
#  Script:                      lg5debug.sh
#  Subsystem:           1
#  %version:            2 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Thu Feb  3 12:16:32 2005 %

dbx -I${LEGO}/tavole -I${LEGO}/sorglego/sub -I${LEGO}/sorglego/main  -I${HOME}/legocad/libut  -I${HOME}/legocad/libut_reg/libreg  -I./proc  $1 $2
