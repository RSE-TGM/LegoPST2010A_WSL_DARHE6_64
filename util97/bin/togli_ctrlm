#!/bin/sh
#
#  Script:			togli_ctrlm.sh
#  Instance:		1
#  %version:		1 %
#  Description:		
#  %created_by:		lomgr %
#  %date_created:	Fri Feb  9 15:52:48 2001 %
#
if [ $# = 0 ]
then
echo "Usage: togli_ctrlm wildcard" 
exit
fi
ls $* | while read var 
do
mv ${var} ${var}.save
cat ${var}.save | tr -d "\r" > ${var}
done

