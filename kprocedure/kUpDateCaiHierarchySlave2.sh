#!/bin/ksh
#
echo $star8
echo $star8 >> $KLOG/kUpDateCaiHierarchy.log
kAddLog kUpDateCaiHierarchy "Start UpDate PlantDisplay Hierarchy"
kAddScreen kUpDateCaiHierarchy "Start UpDate PlantDisplay Hierarchy"
if [ ! -f $KEXPORT/kpd.txt ]
then
echo "ERROR : File kpd.txt not found in $KEXPORT"
banner NOK
exit
fi
#
cd $KWIN
ls M_S_*.pag | grep -v _GR | while read page
	do
	PLANTDISPLAY_SHORT=`echo ${page} | sed "s/M_S_//g" | sed "s/.pag//g"`
	HIERARCHY=`cat $KEXPORT/kpd.txt | tr -s '\011' ' ' | grep -F "${PLANTDISPLAY_SHORT}" | cut -f3 -d" "`
	if [ "${HIERARCHY}" = "" ]
	then
	HIERARCHY="-1,-1,-1,-1,-1,-1"
	echo "\n\n\aERROR : Hierarchy of plant display [${PLANTDISPLAY_SHORT}] not found in $KEXPORT/kpd.txt"
	echo "ERROR : Hierarchy of plant display [${PLANTDISPLAY_SHORT}] not found in $KEXPORT/kpd.txt" >> $KLOG/kUpDateCaiHierarchy.log
        else
        echo ". \c"
	fi
	grep -v "gerarchia:" ${page} > ${page}.tmp
	echo "*gerarchia:\t${HIERARCHY}" >> ${page}.tmp
	mv ${page}.tmp ${page}
	done
	echo "\n"
kAddLog kUpDateCaiHierarchy "End UpDate PlantDisplay Hierarchy"
kAddScreen kUpDateCaiHierarchy "End UpDate PlantDisplay Hierarchy"
echo "$star8"
echo "$star8" >> $KLOG/kUpDateCaiHierarchy.log
