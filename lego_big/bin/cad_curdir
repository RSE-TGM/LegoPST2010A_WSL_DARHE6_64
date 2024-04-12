#!/bin/ksh
#
#  Script:			cad_curdir.sh
#  Instance:		1
#  %version:		5 %
#  Description:		
#  %created_by:		lomgr %
#  %date_created:	Thu Dec 12 10:37:07 2002 %
#
# Lo script restituisce il nome della directory corrente
# privato del path che la precede
#
#pwd | tr "/" "\012" | while read pathname
#do
#dirname=${pathname}
#done

dirname=`basename $PWD`

if [ "$1" = "R" ]
then
dirname=`echo $dirname | cut -f2 -d_` 
fi
echo ${dirname}
