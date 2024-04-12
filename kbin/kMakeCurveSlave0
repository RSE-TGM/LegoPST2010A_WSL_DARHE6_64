#!/bin/ksh
#
kAddStatus kMakeCurveSlave0 OK
cd $KGRAF
rm -f VariablesInGroup.test AvailableVariables.test
cat grugraf.txt | tr '[:blank:]' '&' | sed "s/;;/;\&;/g" | sed "s/;;/;\&;/g" | tr ';' ' '  > grugraf.rtf
cat kksgrafi.txt | tr '[:blank:]' '&' | sed "s/;;/;\&;/g" | sed "s/;;/;\&;/g" | tr ';' ' ' > kksgrafi.rtf
cat vargraf.txt | tr '[:blank:]' '&' | sed "s/;;/;\&;/g" | sed "s/;;/;\&;/g" | tr ';' ' ' > vargraf.rtf
cat grugraf.rtf | while read Group GroupDescr var1 var2 var3 var4 var5 var6 var7 var8 var9 var10 Indice
do
echo "${var1}" >> VariablesInGroup.test
echo "${var2}" >> VariablesInGroup.test
echo "${var3}" >> VariablesInGroup.test
echo "${var4}" >> VariablesInGroup.test
echo "${var5}" >> VariablesInGroup.test
echo "${var6}" >> VariablesInGroup.test
echo "${var7}" >> VariablesInGroup.test
echo "${var8}" >> VariablesInGroup.test
echo "${var9}" >> VariablesInGroup.test
echo "${var10}" >> VariablesInGroup.test
done
cat VariablesInGroup.test | sort | uniq > VariablesInGroup.tmp
mv VariablesInGroup.tmp VariablesInGroup.test
cut -f1 -d" "  vargraf.rtf > AvailableVariables.test
#
cat VariablesInGroup.test | grep -Fv "&" | while read kks
do
Present=`grep "${kks}" AvailableVariables.test | wc -l | tr -d '[:space:]'`
	if [ "${Present}" = "0" ]
	then
	echo "ERROR : The signal [${kks}] is not configurated in ACCESS database" 
	echo "ERROR : The signal [${kks}] is not configurated in ACCESS database" >> $KLOG/kMakeCurve.log
	echo "[${kks}] not configurated in ACCESS database" >> $KLOG/kMakeCurve.err
	kAddStatus kMakeCurveSlave0 NOK
	fi
done


