#!/bin/ksh
#
kAddStatus kTest OK
if [ ! "${KSIMNAME}" ]
then
echo "Ambient variable KSIMNAME not defined"
kAddStatus kTest NOK
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
if [ ! -r $KLOG ]
then
mkdir $KLOG
fi
if [ ! -r $KSTATUS ]
then
mkdir $KSTATUS
fi
if [ ! -r $KWIN ]
then
mkdir $KWIN
fi
if [ ! -r $KEXPORT ]
then
mkdir $KEXPORT
fi
if [ ! -r $KINFO ]
then
mkdir $KINFO
fi
if [ ! -r $KINFOTAG ]
then
mkdir $KINFOTAG
fi
if [ ! -r $KDATABASES ]
then
mkdir $KDATABASES
fi
#
chmod -Rf 777 $KSTATUS
chmod -Rf 777 $KLOG
