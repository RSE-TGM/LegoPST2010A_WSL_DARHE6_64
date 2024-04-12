#!/bin/ksh
#
cd $KBASIC
ls $KWIN/win*.list > creasuperlist.inp
creasuperlist2 creasuperlist.inp superlista.list
sort -o superlista.list superlista.list
echo
echo Background Treatement
ech
cp M_S*.bkg $KWIN
echo
echo Page Treatement
echo
ls M_S*.pag |
while read var
do
chgvar < $var > $KWIN/$var
done
echo
echo Basic Display Created
echo
echo End Program
echo 
