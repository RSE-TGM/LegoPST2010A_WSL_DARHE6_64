#!/bin/ksh
#
while true
do
clear
echo "%CPU  Processor   TASK"
ps -o pcpu,psr,command | grep lg5sk | sort | sed "s/lg5sk/       /g" | grep -v "grep" | grep -v "sed"
sleep 3
done
