#!/bin/ksh
#
$KBIN/kTest
banner "OLD PROGRAM"
echo " Please Use kCheckAlarm"
rm -f $KLOG/sosti.log $KLOG/sosti2.log $KWIN/*.newhier
if [ -f $KWIN/sosti.dat ]
then
  ls $KWIN/N_win*.list | grep -v DFGK_S | while read file
  do
      echo "Elaborating ${file} ..."
      cp ${file} ${file}.old
      numcampo=` grep "@#L@HIER" ${file} | tr -s '\011' ' ' |  awk ' { print NF } '  `
      let numcampohier=${numcampo}-1
      grep "@#L@HIER" ${file} > ${file}.newhier
      grep -v "@#" ${file} | while read riga 
      do
        stringa=` echo "${riga}" | tr -s '\011' ' ' | cut -f1,${numcampohier} -d' ' `
        owin=` echo "${stringa}" | cut -f1 -d' ' | cut -c3- `
        oldhier=`echo "${stringa}" | cut -f2 -d' '`
        newhier=`grep ${owin} $KWIN/sosti.dat | cut -f4 -d'"'`
        if [ "${oldhier}" = "" ]
        then
          echo ${owin} without hierarchy in ${file} >> $KLOG/sosti.log
          grep ${owin} ${file}.old >> ${file}.newhier
        else
          if [ "${newhier}" = "" ]
          then
            echo ${owin} not found in database afsin >> $KLOG/sosti.log
            grep ${owin} ${file}.old >> ${file}.newhier
          else
            grep ${owin} ${file}.old | sed s/${oldhier}/${newhier}/ >> ${file}.newhier
            if [ "${newhier}" != ${oldhier} ]
            then 
            echo " Warning ${owin} Old : ${oldhier} New : ${newhier}" >> $KLOG/sosti2.log
            fi
          fi
        fi
      done
      mv ${file}.newhier ${file}
  done
  if [ -f $KLOG/sosti.log ]
  then
    echo Errors in file $KLOG/sosti.log
    banner NOK
    exit
  fi
 if [ -f $KLOG/sosti2.log ]
  then
    echo Warnings in file $KLOG/sosti2.log
  fi
else
  echo File $KWIN/sosti.dat not found !!
fi
