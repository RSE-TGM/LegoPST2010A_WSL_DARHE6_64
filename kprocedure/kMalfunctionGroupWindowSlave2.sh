#!/bin/ksh
#
rm -f ${KWIN}/*.ListVert
if [ -f ${KWIN}/kMalfunctionGroupWindow.in ]
then
oldmgw="pipo"
cat ${KWIN}/kMalfunctionGroupWindow.in | sort | awk -v FS=" " ' {print $1, $2, $3, $4, $5, $6, $7, $8} ' | \
while read mgw descr ow page var1 var2 var3 var4
do
if [ "${mgw}" = "${oldmgw}" ]
then
echo "${ow}" >> ${KWIN}/${mgw}.ListVert
echo "${descr}" >> ${KWIN}/${mgw}.ListVert
echo "${page}" >> ${KWIN}/${mgw}.ListVert
echo "${var1}" >> ${KWIN}/${mgw}.ListVert
echo "${var2}" >> ${KWIN}/${mgw}.ListVert
echo "${var3}" >> ${KWIN}/${mgw}.ListVert
echo "${var4}" >> ${KWIN}/${mgw}.ListVert
else
echo Elaborating mgw : "${mgw}" ...
echo "O_${mgw}_MGW" > ${KWIN}/${mgw}.ListVert
mgwdescr=`grep ${mgw} ${KWIN}/mgw.descr | cut -f2`
if [ "${mgwdescr}" = "" ]
then
echo "Warning : Description for group ${mgw} not found in ${KWIN}/mgw.descr"
mgwdescr="Description&Not&Found"
fi
mgwtype=`grep ${mgw} ${KWIN}/mgw.descr | cut -f3`
if [ "${mgwtype}" = "" ]
then
echo "Warning : Type for group ${mgw} not found in ${KWIN}/mgw.descr"
mgwtype="XX"
fi
if [ "${mgwtype}" = "MF" ]
then
gtype="MALFUNCTION"
background="DarkSeaGreen"
elif [ "${mgwtype}" = "RP" ]
then
gtype="REMOTE&PARAMETERS"
background="CornFlowerBlue"
else
gtype="TYPE&NOT&DEFINED"
background="Coral"
fi
echo "${mgwdescr}" >> ${KWIN}/${mgw}.ListVert
echo "WindowHeigh" >> ${KWIN}/${mgw}.ListVert
echo "${gtype}" >> ${KWIN}/${mgw}.ListVert
echo "${background}" >> ${KWIN}/${mgw}.ListVert
echo "${ow}" >> ${KWIN}/${mgw}.ListVert
echo "${descr}" >> ${KWIN}/${mgw}.ListVert
echo "${page}" >> ${KWIN}/${mgw}.ListVert
echo "${var1}" >> ${KWIN}/${mgw}.ListVert
echo "${var2}" >> ${KWIN}/${mgw}.ListVert
echo "${var3}" >> ${KWIN}/${mgw}.ListVert
echo "${var4}" >> ${KWIN}/${mgw}.ListVert
fi
oldmgw=${mgw}
done
# Updating Window height
ls ${KWIN}/*.ListVert | while read file
do
linenumber=`grep F_ ${file} | wc -l`
heigh=`expr ${linenumber} \* 40  + 120`
mv ${file} ${file}.sav
sed  "s/WindowHeigh/${heigh}/g" ${file}.sav > ${file}
rm ${file}.sav
done
else
echo "Warning : File ${KWIN}/kMalfunctionGroupWindow.in not found"
fi


