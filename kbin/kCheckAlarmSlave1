#!/bin/ksh
#
#
kAddStatus kCheckAlarm1 UNKNOWN
echo ${star5}
echo ${star5} >> $KLOG/kCheckAlarm.log
kAddScreen kCheckAlarm "Verification n.1 : START"
kAddLog kCheckAlarm "Verification n.1 : START"
echo "\n\tAlarm selection in ALARM.txt with the criterion Functional Area"
echo "\tpresents in al_sim.conf file.\n"
echo "\tFunctional Area List: "$MMI_K_FA_LIST""
echo "\n\tAlarm selection in ALARM.txt with the criterion Functional Area" >> $KLOG/kCheckAlarm.log
echo "\tpresents in al_sim.conf file.\n" >> $KLOG/kCheckAlarm.log
echo "\tFunctional Area List: "$MMI_K_FA_LIST"" >> $KLOG/kCheckAlarm.log
#
echo "Waiting ..."
grep "AL_ID" $KSTART_TABLES/ALARM.txt > $KSTART_TABLES/ALARM.tmp
grep -v "AL_ID" $KSTART_TABLES/ALARM.txt | while read line
do
 FA=` echo "${line}" | cut -f12 -d';' `
 for facrit in $MMI_K_FA_LIST
 do
 if [ "${FA}" = "${facrit}" ]
 then
 echo "${line}" >> $KSTART_TABLES/ALARM.tmp
 fi
 done
done
mv $KSTART_TABLES/ALARM.txt $KSTART_TABLES/ALARM.txt.kold
mv $KSTART_TABLES/ALARM.tmp $KSTART_TABLES/ALARM.txt
echo "\n\tResults are in $KSTART_TABLES/ALARM.txt file\n"
echo "\n\tResults are in $KSTART_TABLES/ALARM.txt file\n" >> $KLOG/kCheckAlarm.log
kAddStatus kCheckAlarm1 OK
#
kAddScreen kCheckAlarm "Verification n.1 : END"
kAddLog kCheckAlarm "Verification n.1 : END"
echo "${star5}\n"
echo "${star5}\n" >> $KLOG/kCheckAlarm.log
