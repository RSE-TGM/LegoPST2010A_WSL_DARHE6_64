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
if [ ! -r $KINFO ]
then 
mkdir $KINFO
fi
rm -f $KINFO/$1.info
echo $2 > $KINFO/$1.info
chmod -f 777 $KINFO/$1.info
