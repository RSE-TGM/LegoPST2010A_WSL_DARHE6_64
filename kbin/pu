#!/bin/ksh
#
numberback=0
numberkold=0
numbertmp=0
if [ -f *bak ]
then
numberback=`ls *bak | wc -w`
rm *bak
fi
#
if [ -f *kold ]
then
numberkold=`ls *kold | wc -w`
rm *kold
fi
#
if [ -f tmp.* ]
then
numbertmp=`ls tmp.* | wc -w`
rm tmp.*
fi
#
tot=`expr ${numberback} + ${numberkold} + ${numbertmp}`
echo ""${tot}" files have been removed"
