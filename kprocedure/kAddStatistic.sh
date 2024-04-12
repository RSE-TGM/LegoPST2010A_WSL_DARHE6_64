#!/bin/ksh
#
if [ ! "${KSIMNAME}" ]
then
echo "Ambient variable KSIMNAME not defined"
exit
fi
if [ ! "${KSTATISTIC}" ]
then
echo "Warning : Ambient variable KSTATISTIC not defined"
exit
fi
if [ ! -r ${KSTATISTIC} ]
then
mkdir ${KSTATISTIC}
chmod 777 ${KSTATISTIC}
fi
if [ ! -f ${KSTATISTIC}/$1.statistic ]
then
echo "| $1 | ${USER} | 1 |" >> ${KSTATISTIC}/$1.statistic
chmod 777 ${KSTATISTIC}/$1.statistic
else
	OldNumber=` grep "$1 | ${USER}"  ${KSTATISTIC}/$1.statistic | cut -f4 -d'|' | tr -d '[:space:]'`
	if [ "${OldNumber}" != "" ]
	then
	NewNumber=`expr $OldNumber + 1`
	mv ${KSTATISTIC}/$1.statistic ${KSTATISTIC}/$1.statistic.kold
	grep -v "| $1 | ${USER} | ${OldNumber} |" ${KSTATISTIC}/$1.statistic.kold > ${KSTATISTIC}/$1.statistic
	echo "| $1 | ${USER} | ${NewNumber} |" >> ${KSTATISTIC}/$1.statistic
	rm -f ${KSTATISTIC}/$1.statistic.kold
	chmod 777 ${KSTATISTIC}/$1.statistic
	else
	echo "| $1 | ${USER} | 1 |" >> ${KSTATISTIC}/$1.statistic
	fi
fi
