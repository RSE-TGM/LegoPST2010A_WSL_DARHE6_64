#############################################################################
#
# Sostituisce la gerarchia delle operating window nei file *.list 
#
#############################################################################
#
export file
export numcampo
export oldhier
export newhier
export owin
export stringa
export riga
rm -f sosti.log *.newhier*
if [ -f sosti.dat ]
then
  grep -v 'DFGK_S' sosti.dat > sosti.dat.tmp
  mv sosti.dat.tmp sosti.dat
  ls N_win*.list | while read file
  do
    if [ "${file}" != "N_winDFGK_S.list" ]
    then
      numcampo=`grep '@#L@HIER' ${file} | tr -s '\011' ' ' | \
        awk '{ print NF }'`
      cp ${file} ${file}.old
      grep '@#L@HIER' ${file} > ${file}.newhier2
      grep -v '@#' ${file} | while read riga 
      do
        stringa=`echo ${riga} | tr -s '\011' ' ' | cut -f1,${numcampo} -d' '`
        owin=`echo ${stringa} | cut -f1 -d' ' | cut -c3-`
        oldhier=`echo ${stringa} | cut -f2 -d' '`
        newhier=`grep ${owin} sosti.dat | cut -f4 -d'"'`
        if [ "${oldhier}" = "" ]
        then
          echo ${owin} non ha gerarchia in ${file} >> sosti.log
          grep ${owin} ${file}.old >> ${file}.newhier2
        else
          if [ "${newhier}" = "" ]
          then
            echo ${owin} non trovata nel database >> sosti.log
            grep ${owin} ${file}.old >> ${file}.newhier2
          else
            grep ${owin} ${file}.old | sed s/${oldhier}/${newhier}/ >> ${file}.newhier2
          fi
        fi
      done
      mv ${file}.newhier2 ${file}
    fi
  done
  if [ -f sosti.log ]
  then
    echo Sono stati riscontrati errori!! Vedere il file sosti.log
  fi
else
  echo File sosti.dat non presente !!
fi
