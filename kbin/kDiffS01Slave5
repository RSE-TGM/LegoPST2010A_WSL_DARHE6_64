#!/bin/ksh
#
cd /usr/users3/igccr1/appsid/gimpns22/db
grep -h EXPR * > kDiffS01Slave5.expr
cut -f2 -d= kDiffS01Slave5.expr | sed  "s/EXPR//g" | \
tr -d '(' | tr -d ')' | tr -d '+' | tr -d '*' | \
tr -s '[:space:] ' | tr -s '[:space:]' '[\n*]' | \
sort | uniq > kDiffS01Slave5.input
cat kDiffS01Slave5.input | while read InputName
do
if [ ! "$InputName" = "" ]
then
InputValue=`grep -w $InputName kDiffS01.DB | cut -c17-27`
	if [ "$InputValue" = "" ]
	then
	echo $InputName not found in kDiffS01.DB
	fi
else
echo ERROR
fi
done
