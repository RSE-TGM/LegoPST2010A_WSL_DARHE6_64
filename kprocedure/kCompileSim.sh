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
if [ -f $KLOG/kCompileSim.log ]
then
mv $KLOG/kCompileSim.log $KLOG/kCompileSim.log.kold
fi
echo ${star}
echo ${star} >> $KLOG/kCompileSim.log
kAddScreen kCompileSim Start
kAddLog kCompileSim Start
echo ${star}
echo ${star} >> $KLOG/kCompileSim.log
#
clean
cd $KWIN
echo "Cleaning $KWIN directory ..."
ls | grep err | while read poubelle
do
rm  ${poubelle}
done
kconfig -c compall
###############################################################################
###############################################################################
pagepagenumber=`ls | grep rtf_err | wc -l`
echo "\n\t * Animated pages number compilied : "${pagepagenumber}"\n"
echo "\n\t * Animated pages number compilied : "${pagepagenumber}"\n" >> $KLOG/kCompileSim.log
	ls | grep rtf_err | while read errorpage
	do
	errlinenumber=`cat ${errorpage} | wc -l`
	if [ "${errlinenumber}" -gt "5" ]
	then
	echo "\t * ERROR in Animated page "${errorpage}"\n"
	echo "\t * ERROR in Animated page "${errorpage}"\n" >> $KLOG/kCompileSim.log
	fi
	done
###############################################################################
#
echo "$star"
echo "$star" >> $KLOG/kCompileSim.log
kAddScreen kCompileSim End 
kAddLog kCompileSim End
echo "$star"
echo "$star" >> $KLOG/kCompileSim.log
#
echo "Log file $KLOG/kCompileSim.log\a\a\a"
