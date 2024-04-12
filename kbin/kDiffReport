#!/bin/ksh
#
clear
${KBIN}/kTest
KTEST=`cat $KSTATUS/kTest.status`
echo "kTest result : $KTEST"
if [ ! "$KTEST" = "OK" ]
then
echo "Environement test not succesful\a"
banner "NOK"
exit
fi
kpresentation
if [ -f $KLOG/kDiffReport.log ]
then
mv $KLOG/kDiffReport.log $KLOG/kDiffReport.log.kold
fi
echo ${star}
echo ${star} >> $KLOG/kDiffReport.log
kAddScreen kDiffReport Start
kAddLog kDiffReport Start
echo "\n$star8"
echo "Available simulators :\n"
$KBIN/kArchiveDisponibility
echo "\n$star8\n"
OldRevision=$1
NewRevision=$2
if [ "$NewRevision" = "" ]
then
	NewRevision=`cat $KINFO/Simulator_Revision.info`
	if [ -f $KINFO/Original_Revision.info ]
	then
	OldRevision=`cat $KINFO/Original_Revision.info`
	else
	echo "\nSorry ..."
	echo "The simulator $NewRevision is a version without father.\n\a"
	exit
	fi
fi
	CONFIRM=""
	echo "Please confirm :"
	echo "\tOld version : [$OldRevision]"
	echo "\tNew version : [$NewRevision]"	
	echo "\nPress y to confirm"
	read CONFIRM
	if [ ! "${CONFIRM}" = "y" ]
	then
	echo "\nSorry ...\a\n"
	echo "$star8"
	exit
	fi
#
if [ ! -f $KARCHIVE/$OldRevision/.info/kProcessReport.info ]
then
echo "\aSorry : File $KARCHIVE/$OldRevision/.info/kProcessReport.info not found"
exit
fi
if [ ! -f $KARCHIVE/$NewRevision/.info/kProcessReport.info ]
then
echo "\aSorry : File $KARCHIVE/$NewRevision/.info/kProcessReport.info not found"
exit
fi
echo "\nFrom $OldRevision to $NewRevision simulator,"
echo "the following legocad blocks have been modified :\n"
diff $KARCHIVE/$OldRevision/.info/kProcessReport.info $KARCHIVE/$NewRevision/.info/kProcessReport.info | \
     cut -f 1-3 -d ";" | grep ";" | tr -d '>' | tr -d '<' | uniq | sed  "s/;/ \| /g"
echo
#
echo "\nFrom $OldRevision to $NewRevision simulator," >> $KLOG/kDiffReport.log
echo "the following legocad blocks have been modified :\n" >> $KLOG/kDiffReport.log
diff $KARCHIVE/$OldRevision/.info/kProcessReport.info $KARCHIVE/$NewRevision/.info/kProcessReport.info | \
     cut -f 1-3 -d ";" | grep ";" | tr -d '>' | tr -d '<' | uniq | sed  "s/;/ \| /g" >> $KLOG/kDiffReport.log
echo >> $KLOG/kDiffReport.log
#
kAddScreen kDiffReport End
kAddLog kDiffReport End
echo "Log File :\t$KLOG/kDiffReport.log\a"
echo "$star"
echo "$star" >> $KLOG/kDiffReport.log

