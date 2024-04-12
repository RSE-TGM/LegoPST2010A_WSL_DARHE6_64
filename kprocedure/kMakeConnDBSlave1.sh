#!/bin/ksh
#
#############################################################################
# Test
#############################################################################
#
if [ ! -f S01 ]
then
  echo "ERROR : not found $KSIM/S01"
  echo "ERROR : not found $KSIM/S01" >> $KLOG/kMakeConnDB.log
  exit
fi
#
#
#############################################################################
# Reading S01
#############################################################################
#
export count=0
cat S01 |
while read var
do
  if [ $count -lt 3 ]
  then
    if [ "${var}" = '****' ]
    then 
      let count=count+1 
    fi
    continue
  fi
  if [ "${var}" = '****' ]
  then 
    break 
  fi
  echo ${var}
done |
grep ' R' |
while read tok1 tok2 tok3 tok4
#
# tok1 pathname
# tok2 Process/Regulation
# tok3 Task name
# tok4 Prima lettera degli schemi di regolazione
#
#############################################################################
# Elaborating ASCII Tempory Database
#############################################################################
#
do
if [ ! "${tok1}" = "" ]
then
cd ${tok1}
echo "Elaborating ASCII Tempory Database for task : ${tok1} ..."
grep -h "<===" ./proc/*_01.dat | cut -f1 -d. |tr "#" " "| while read primo salta secondo
	do
	echo ${secondo} ${primo} >> ${KSIM}/REG_INT_CONN_DB.tmp
	done 
cd ${KSIM}
else
echo "Directory [${tok1}] not found"
fi
done
#############################################################################
# Elaborating  Database
#############################################################################
#
touch $KSIM/REG_INT_CONN_DB.dir
touch $KSIM/REG_INT_CONN_DB.pag
echo "Elaborating Binadatabase REG_INT_CONN_DB ..."
cat ${KSIM}/REG_INT_CONN_DB.tmp | while read variable1 variable2
do
echo ${variable1} ${variable2}
done | dbmins_mul REG_INT_CONN_DB
rm -f ${KSIM}/REG_INT_CONN_DB.tmp
#
