#!/bin/ksh
#
rm -f ${KWIN}/kMalfunctionGroupWindow.in
if [ "`wc -l ${KWIN}/mgw.conf | cut -f1 -d"/"`" -gt "1" ]
then
cat ${KWIN}/mgw.conf | sort | while read mf group
do
grep ";${mf};" $KWIN/component.mf | awk -v FS=";" ' {print $1, $3, $4, $2} ' | \
while read  MfType kks supertag descrtmp
do
#echo ${mf} $kks $supertag $descrtmp
if [ ! "${kks}" = "${mf}" ]
then
banner "NOK"
exit
fi
maintag=`echo ${supertag} | cut -f1 -d"-"`
if [ "${descrtmp}" = "Descr" ]
then
descrtmp="Generic&Malfunction"
	if [ "${MfType}" = "0" -o "${MfType}" = "1" -o "${MfType}" = "3" -o "${MfType}" = "5" \
	-o "${MfType}" = "7" -o "${MfType}" = "8" -o "${MfType}" = "9" -o "${MfType}" = "10" \
	-o "${MfType}" = "11" -o "${MfType}" = "12" ]
	then
	variable1="IA${maintag}&BLOCCO&TASK&NOT&1.0&0.0&---"
	elif [ "${MfType}" = "2" -o "${MfType}" = "6" ]
	then
	variable1="IB${maintag}&BLOCCO&TASK&NOT&1.0&0.0&---"
	elif [ "${MfType}" = "17" ]
	then
	variable1="IG${maintag}&BLOCCO&TASK&NOT&1.0&0.0&---"
	elif [ "${MfType}" = "4" ]
	then
	variable1="I1${maintag}&BLOCCO&TASK&NOT&1.0&0.0&---"
	else
	variable1="Type&[${MfType}]&not&configurated&in&kMalfunctionGroupWindowSlave4"
	fi
variable2=pipo
variable3=pipo
variable4=pipo
else
variable1="V0${maintag}&BLOCCO&TASK&NOT&1.0&0.0&---"
variable2=pipo
variable3=pipo
variable4=pipo
fi
description1="${descrtmp}&${kks}"
description=`echo ${description1} | tr ' ' '&'`
ow="F_${kks}"
page=`echo ${supertag} | cut -c 8-11`
echo "${group} ${description} ${ow} ${page} ${variable1} ${variable2} ${variable3} ${variable4}" >> ${KWIN}/kMalfunctionGroupWindow.in
done
done
else
echo "Warning : File ${KWIN}/mgw.conf is empty"
fi


