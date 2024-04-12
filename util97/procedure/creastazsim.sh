#############################################################################
#
# Prepara il direttorio o_win per un simulatore di una o piu' task
# residente nel path $HOME/sked/nome_simulatore
#
# Dragoni M. 14/10/97
#
#############################################################################
#
#############################################################################
# Operazioni preliminari
#############################################################################
#
# controllo dei parametri passati
#
if [ "$1" = "" ]
then
  echo "\n uso: creastazsim directory_simulatore \n\a"
  exit
fi
#
# inizializzazioni
#
count=0
num_page=0
list_page=""
nome_simulatore=$1
dirsim=$HOME/sked/${nome_simulatore}
dirstaz=${dirsim}/o_win
#
# controllo dell'esistenza del file S01
#
cd ${dirsim}
if [ ! -f S01 ]
then
  echo Errore: non esiste il file S01
  exit
fi
#
# preparazione direttorio o_win
#
echo Preparazione direttorio o_win
rm -rf ${dirstaz}
mkdir ${dirstaz}
#
#############################################################################
# analisi del file S01 per individuare i modelli
#############################################################################
#
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
grep ' R ' |
while read tok1 tok2 tok3 tok4
#
# tok1 pathname
# tok2 Process/Regulation
# tok3 Task name
# tok4 Prima lettera degli schemi di regolazione
#
#############################################################################
# merge dei file .list
#############################################################################
#
do
  cd ${tok1}
  echo merge operating windows ${tok1}
  if [ -f N_win*.list ]
  then
    ls N_win*.list |
    while read var
    do
      if [ ! -f ${dirstaz}/${var} ]
      then
        cat ${var} | grep '^[a-zA-Z@]' > ${dirstaz}/${var}
      else
        cat ${var} | grep -v '@#L@' | grep '^[a-zA-Z]' >> ${dirstaz}/${var}
      fi
      sort ${dirstaz}/${var} > ${dirstaz}/${var}.ord
      mv ${dirstaz}/${var}.ord ${dirstaz}/${var}
    done
  fi
  if [ -f mal*.list ]
  then
    ls mal*.list |
    while read var
    do
      if [ ! -f ${dirstaz}/${var} ]
      then
        cat ${var} | grep '^[a-zA-Z@]' > ${dirstaz}/${var}
      else
        cat ${var} | grep -v '@#L@' | grep '^[a-zA-Z]' >> ${dirstaz}/${var}
      fi
      sort ${dirstaz}/${var} > ${dirstaz}/${var}.ord
      mv ${dirstaz}/${var}.ord ${dirstaz}/${var}
    done
  fi
  if [ -f DirLinksAn.list ]
  then
    ls DirLinksAn.list |
    while read var
    do
      if [ ! -f ${dirstaz}/${var} ]
      then
        cat ${var} > ${dirstaz}/${var}
      else
        cat ${var} | grep -v 'Offset' >> ${dirstaz}/${var}
      fi
    done
  fi
  cd ${dirsim}
done
#
#############################################################################
# generazione dei plant display
#############################################################################
#
echo Generazione plant display
direct.sh ${nome_simulatore}
#
#############################################################################
# generazione delle operating windows
#############################################################################
#
cd ${dirstaz}
ls N_win*.list |
cut -f1 -d. |
while read file
do
  echo Generazione operating windows ${file}
  mkstaz ${file}
done
ls mal*.list |
cut -f1 -d. |
while read file
do
  echo Generazione operating windows ${file}
  mkstaz ${file}
done
#
#############################################################################
# generazione file Context.ctx
#############################################################################
#
echo Generazione file Context.ctx
ls *.pag | while read pagina
do
  tag=`echo ${pagina} | cut -f1 -d'.'`
  list_page="${list_page} ${tag}"
  let num_page=num_page+1
  echo '*'${tag}.`grep 'tagPag:' ${pagina} | cut -c2-` >> Context.ctx
  echo '*'${tag}.`grep 'top_descrizione:' ${pagina} | cut -c2-` >> Context.ctx
  echo '*'${tag}.`grep 'schemeInUse:' ${pagina} | cut -c2-` >> Context.ctx
  stringa=`grep 'gerarchia:' ${pagina}`
  if [ "${stringa}" = "" ]
  then
    echo "*${tag}.gerarchia:\t-1,-1,-1,-1,-1,-1" >> Context.ctx
  else
    echo '*'${tag}.`grep 'gerarchia:' ${pagina} | cut -c2-` >> Context.ctx
  fi
  echo '*'${tag}.`grep 'refresh_freq:' ${pagina} | cut -c2-` >> Context.ctx
  echo '*'${tag}.`grep 'top_tipo:' ${pagina} | cut -c2-` >> Context.ctx
done
cat >> Context.ctx << !EOF
*hostName:	
*hostNameS:	
*iconlib_list:	\\ 
*displayList:	
*numDisplay:	0
*iconlib_num:	0
*description:	Operating Window and Plant Display
*iconlib_label:	\\ 
*nextTagPag:	00
*simulator:	${dirsim}
*pages:		${dirstaz}
*objectLibraries:	$HOME/legocad/libut_reg/libreg
*animatedIconLibraries:	$HOME/legocad/libut_reg/libreg
*pag_num:	${num_page}
*page_list:	${list_page}
!EOF
#
#############################################################################
# sostituisci l'attributo Sinottico con Teleperm
#############################################################################
#
ls M_S_*.pag | while read plantd
do
  sed s/Sinottico/Teleperm/ ${plantd} > ${plantd}.Tel
  mv ${plantd}.Tel ${plantd}
done
if [ -f Context.ctx ]
then
  sed s/Sinottico/Teleperm/ Context.ctx > Context.ctx.Tel
  mv Context.ctx.Tel Context.ctx
fi
