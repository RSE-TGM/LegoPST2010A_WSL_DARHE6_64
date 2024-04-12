#!/bin/ksh
#
ls | grep -v mdb$ | while read file
do
kAddScreen kExport "kControlM : Elaborating $file"
kAddLog kExport "kControlM : Elaborating $file" 
mv $file $file.controlM
sed "s///g" $file.controlM > $file
rm -f *controlM
done
