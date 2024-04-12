#!/bin/sh
#   modulo ExpRtf.sh
#   tipo 
#   release 1.10
#   data 96/06/13
#   reserved @(#)ExpRtf.sh	1.10
#
if [ $# -lt 2 ]
then
echo "usage: ExpRtf <source> <dest>"
exit
fi
if [ ! -d $1 ]
then
echo "error: " $1 " not exist"
exit
fi
if [ ! -d $2 ]
then
echo "error: " $2 " not exist"
exit
fi
cp $1/editConfDB.txt $2/ConfDB.txt
cp $1/editAllarDB.txt $2/AllarDB.txt
cp $1/editAllarLin.txt $2/AllarLin.txt
cp $1/editAllarServ.txt $2/AllarServ.txt
cp $1/editAllarLiv.txt $2/AllarLiv.txt
cp $1/editAllarStr.txt $2/AllarStr.txt
cp $1/editaa.txt $2/PuntAA.txt
cp $1/editac.txt $2/PuntAC.txt
cp $1/editad.txt $2/PuntAD.txt
cp $1/editao.txt $2/PuntAO.txt
cp $1/editas.txt $2/PuntAS.txt
cp $1/editda.txt $2/PuntDA.txt
cp $1/editdc.txt $2/PuntDC.txt
cp $1/editdd.txt $2/PuntDD.txt
cp $1/editdo.txt $2/PuntDO.txt
cp $1/editds.txt $2/PuntDS.txt
cp $1/editor.txt $2/PuntOR.txt
cp $1/editst.txt $2/PuntST.txt
cp $1/editarc.txt $2/PuntARC.txt
cp $1/editto.txt $2/PuntTO.txt
cp $1/editTabPeri.txt $2/TabPeri.txt
cp $1/editCPerif.txt $2/CPerif.txt
cp $1/editDescriSc.txt $2/DescriSc.txt
cp $1/editMisTabK.txt $2/MisTabK.txt
cp $1/editTDIZST.txt $2/TDIZST.txt
cp $1/editNomi.txt $2/Nomi.txt
cp $1/editlog.txt $2/Tabulati.txt
cp $1/*.tcr $2/.
