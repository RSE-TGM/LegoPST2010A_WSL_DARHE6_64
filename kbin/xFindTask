#!/bin/ksh
#
task=$1
ls ????.pag | sed "s/.pag/ /g" | while read page
do
echo "${page} ${task}" >> $KINFOTAG/TASK.list
done
