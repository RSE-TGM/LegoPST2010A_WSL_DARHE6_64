#!/bin/ksh
#
#  Script %name:	rerunlg2.sh %
#  Instance:		1
#  %version:		1 %
#  Description:		
#  %created_by:		jurij %
#  %date_created:	Wed Mar 28 16:24:10 2007 %

rm -f lg2_done.out
echo $LG_BIN
make -f $LG_BIN/rerunlg2.mk
