#!/bin/ksh
#
#
kAddStatus kCheckAlarm3 UNKNOWN
echo ${star5}
echo ${star5} >> $KLOG/kCheckAlarm.log
kAddScreen kCheckAlarm "Verification n.3 : START"
kAddLog kCheckAlarm "Verification n.3 : START"
echo "\n\tAlarm selection in cai_var.dat with the criterion Functional Area"
echo "\tpresents in al_sim.conf file.\n"
echo "\tFunctional Area List: "$MMI_K_FA_LIST""
echo "\n\tAlarm selection in cai_var.dat with the criterion Functional Area" >> $KLOG/kCheckAlarm.log
echo "\tpresents in al_sim.conf file.\n" >> $KLOG/kCheckAlarm.log
echo "\tFunctional Area List: "$MMI_K_FA_LIST"" >> $KLOG/kCheckAlarm.log
#
rm -f $KSIM/cai_var.tmp
cat $KSIM/cai_var.dat | awk -v FS="," ' {print $1, $2, $3, $4, $5, $6, $7, $8} ' | \
while read field1 FA field3 field4 field5 field6 type kks
do
	for facrit in $MMI_K_FA_LIST
	do
	if [ $FA = $facrit ]
	then
	echo "$field1,$FA,$field3,$field4,$field5,$field6,$type,$kks" >> $KSIM/cai_var.tmp
	fi
	done
done
mv $KSIM/cai_var.dat $KSIM/cai_var.dat.kold
mv $KSIM/cai_var.tmp $KSIM/cai_var.dat
echo "\n\tResults are in $KSIM/cai_var.dat file\n"
echo "\n\tResults are in $KSIM/cai_var.dat file\n" >> $KLOG/kCheckAlarm.log
kAddStatus kCheckAlarm3 OK
#
kAddScreen kCheckAlarm "Verification n.3 : END"
kAddLog kCheckAlarm "Verification n.3 : END"
echo "${star5}\n"
echo "${star5}\n" >> $KLOG/kCheckAlarm.log
