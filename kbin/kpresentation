#!/bin/ksh
#
echo ${star3}
if [ -f $KINFO/Simulator_Revision.info ]
then
KREV=`cat $KINFO/Simulator_Revision.info`
banner "$KREV"
else
echo "No simulator revision defined"
fi
#
if [ -f $KINFO/Simulator_Description.info ]
then
KDESCR=`cat $KINFO/Simulator_Description.info`
echo ${star3}
echo "$KDESCR"
else
echo "No simulator description defined"
fi
#
echo ${star3}
