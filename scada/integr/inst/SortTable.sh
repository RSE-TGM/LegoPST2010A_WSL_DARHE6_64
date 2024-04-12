#!/bin/sh
#   modulo SortTable.sh
#   tipo 
#   release 1.2
#   data 96/06/13
#   reserved @(#)SortTable.sh	1.2
#
if [ $# -lt 1 ]
then
echo "usage: SortTable <source table> "
exit
fi
if [ ! -f $1 ]
then
echo "error: " $1 " not exist"
exit
fi
righe=`cat $1 | wc -l`
rr=`echo "$righe -1"|bc`
head -1 $1 > qq
tail -`echo $rr` $1 | sort >> qq
mv qq $1
