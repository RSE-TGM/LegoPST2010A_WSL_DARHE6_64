#!/bin/ksh
#
if [ ! "${KSIMNAME}" ]
then
echo "Ambient variable KSIMNAME not defined"
exit
fi
if [ ! -r $HOME/sked ]
then
mkdir $HOME/sked
fi
if [ ! -r $KSIM ]
then
mkdir $KSIM
fi
if [ ! -r $KSTATUS ]
then 
mkdir $KSTATUS
fi
rm -f $KSTATUS/$1.status
echo $2 > $KSTATUS/$1.status
chmod 777 $KSTATUS/$1.status
#echo "| `date +"#%d/%m/%y#%T#"` | $1 | $2 |" > $KSTATUS/$1.status
