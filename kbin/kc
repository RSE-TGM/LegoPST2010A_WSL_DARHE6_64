#!/bin/ksh
#
task=$1
clear
if [ -a $LEGOCAD_USER/legocad/${task}/f01.dat ]
then
cd $LEGOCAD_USER/legocad/${task}
echo "\nStart config in `pwd`.\n"
sleep 1
config &
else
echo "\nSorry : task [${task}] not found.\a\n"
fi
