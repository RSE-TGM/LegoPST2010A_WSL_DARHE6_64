#!/bin/ksh
#
#
kAddStatus kCheckAlarm5 UNKNOWN
echo ${star5}
echo ${star5} >> $KLOG/kCheckAlarm.log
kAddScreen kCheckAlarm "Verification n.5 : START"
kAddLog kCheckAlarm "Verification n.5 : START"
echo "\n\tVerification that all Operating Windows present in Nwin_XXX.list"
echo "\thave a defined hierarchy.\n"
echo "\n\tVerification that all Operating Windows present in Nwin_XXX.list" >> $KLOG/kCheckAlarm.log
echo "\thave a defined hierarchy.\n" >> $KLOG/kCheckAlarm.log
#
rm -f $KSIM/hierOW.pb
echo "-1,-1,-1,-1,-1,-1" > $TMPDIR/hier.tmp
grep -f $TMPDIR/hier.tmp $KWIN/*list | grep -v ALWAYS | grep -v -w BOUND >> $KSIM/hierOW.pb
if [ ! -s $KSIM/hierOW.pb ]
then
kAddStatus kCheckAlarm5 OK
kAddScreen kCheckAlarm "Verification n.5 : OK"
kAddLog kCheckAlarm "Verification n.5 : OK"
else
kAddStatus kCheckAlarm5 NOK
kAddScreen kCheckAlarm "Verification n.5 : NOK"
kAddLog kCheckAlarm "Verification n.5 : NOK"
echo "\nSee files:\n\t$KSIM/hierOW.pb\a\n"
banner NOK
cat $KSIM/hierOW.pb >> $KLOG/kCheckAlarm.log
banner NOK >> $KLOG/kCheckAlarm.log
#exit
fi
rm -f $TMPDIR/hier.tmp
#
kAddScreen kCheckAlarm "Verification n.5 : END"
kAddLog kCheckAlarm "Verification n.5 : END"
echo ${star5}\n
echo ${star5}\n >> $KLOG/kCheckAlarm.log
