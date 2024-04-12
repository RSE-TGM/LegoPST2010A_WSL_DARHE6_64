#!/bin/ksh
#
#############################################################################
#
# Esegue la sostituzione delle tags nei plant display con le variabili
#
#############################################################################
#
#############################################################################
# Operazioni preliminari
#############################################################################
#
export plantd
export file
export tag
export variabile
export variabile1
export variabile2
export variabile3
export scal
export offset
export dirsim
export dirplant
export dirstaz
export sim
export lista_plant
#
#----------------------------------------------------------------------------
# Decodifica dei parametri in input
#----------------------------------------------------------------------------
#
echo "$1 | $2 | $3 | $4"
if [ "$1" = "" ]
then
  lista_plant="M_S_*.pag"
  dirsim=$PWD
  dirplant=$PWD
  dirstaz=$PWD
  sim="local"
elif [ "$1" = "-s" ] && [ "$2" != "" ] && [ "$3" = "" ] && [ "$4" = "" ]
then
  lista_plant="M_S_*.pag"
  dirsim=$HOME/sked/$2
  dirplant=${dirsim}/plant_display
  dirstaz=${dirsim}/o_win
  sim="remote"
elif [ "$1" = "-p" ] && [ "$2" != "" ] && [ "$3" = "" ] && [ "$4" = "" ]
then
  lista_plant="M_S_$2.pag"
  dirsim=$PWD
  dirplant=$PWD
  dirstaz=$PWD
  sim="local"
elif [ "$1" = "-s" ] && [ "$2" != "" ] && [ "$3" = "-p" ] && [ "$4" != "" ]
then
  lista_plant="M_S_$4.pag"
  dirsim=$HOME/sked/$2
  dirplant=${dirsim}/plant_display
  dirstaz=${dirsim}/o_win
  sim="remote"
elif [ "$1" = "-p" ] && [ "$2" != "" ] && [ "$3" = "-s" ] && [ "$4" != "" ]
then
  lista_plant="M_S_$2.pag"
  dirsim=$HOME/sked/$4
  dirplant=${dirsim}/plant_display
  dirstaz=${dirsim}/o_win
  sim="remote"
else
  echo "usage: direct.sh [-s nome_simulatore] [-p plant_display] \a"
  exit
fi
#  echo $lista_plant
#
#----------------------------------------------------------------------------
# Controllo esistenza dei direttori
#----------------------------------------------------------------------------
#
if [ ! -d ${dirsim} ]
then
  echo "Non esiste la directory ${dirsim} !! Fine procedura \a"
  exit
fi
if [ ! -d ${dirplant} ]
then
  echo "Non esiste la directory ${dirplant} !! Fine procedura \a"
  exit
fi
if [ ! -d ${dirstaz} ]
then
  echo "Non esiste la directory ${dirstaz} !! Fine procedura \a"
  exit
fi
#
#----------------------------------------------------------------------------
# Prepara lo svincolo variabili-tags
#----------------------------------------------------------------------------
#
if [ -f ${dirsim}/variabili.edf ] 
then
  grep @#K@ ${dirsim}/variabili.edf | grep -v BLOCCO | tr -s '[:space:]'| \
    cut -f2,6 -d' ' | sort | uniq > ${dirplant}/variabili.tag
else
  echo "Non esiste il file ${dirsim}/variabili.edf !! Fine procedura \a"
  exit
fi
#
#----------------------------------------------------------------------------
# Sostituisce le tags delle operating window nei plant display
#----------------------------------------------------------------------------
#
cd ${dirplant}
rm -f direct.sh.log
ls ${dirstaz}/N_win*.list > creasuperlist.inp
echo "\n" | creasuperlist creasuperlist.inp superlista.list > direct.sh.log
echo ${star4} creasuperlist
cp superlista.list superlista.list_old
sort superlista.list_old > superlista.list
echo ${lista_plant}
ls ${lista_plant} |
while read plantd
do
#  echo 
  echo "****** chgvar: Elaborating ${plantd}\t*********"
  cp -p ${plantd} ${plantd}.ori
  chgvar < ${plantd} > ${plantd}.new
  if [ $? != 0 ]
  then
     echo "\n${star3}" >> direct.sh.log
     echo Errore in ${plantd} rilevato da chgvar >> direct.sh.log
     echo verificare eseguendo chgvar \< ${plantd} \> ${plantd}.new >> direct.sh.log
     echo leggendo il file error_chgvar.msg >> direct.sh.log
     echo ${star3} >> direct.sh.log
  fi       
  mv ${plantd}.new ${plantd}
done
rm -f superlista.list_old creasuperlist.inp
#
#############################################################################
# Preparazione degli script di input di pagmod
#############################################################################
#----------------------------------------------------------------------------
# Prepara lo script di ricerca per Indic
#----------------------------------------------------------------------------
#
echo "widgetclass=Indic" > rep_indic.scr
echo "attrib=objectTag" >> rep_indic.scr
echo "samevalue=" >> rep_indic.scr
#
#----------------------------------------------------------------------------
# Prepara lo script di ricerca per Pictograph
#----------------------------------------------------------------------------
#
echo "widgetclass=Pictograph" > rep_picto.scr
echo "hasattrib=nomeFile" >> rep_picto.scr
echo "value=valveNormally" >> rep_picto.scr
echo "attrib=objectTag" >> rep_picto.scr
echo "samevalue=" >> rep_picto.scr
echo " " >> rep_picto.scr
echo "widgetclass=Pictograph" >> rep_picto.scr
echo "hasattrib=nomeFile" >> rep_picto.scr
echo "value=pumplittle_Normally" >> rep_picto.scr
echo "attrib=objectTag" >> rep_picto.scr
echo "samevalue=" >> rep_picto.scr
echo " " >> rep_picto.scr
echo "widgetclass=Pictograph" >> rep_picto.scr
echo "hasattrib=nomeFile" >> rep_picto.scr
echo "value=compressorNormally" >> rep_picto.scr
echo "attrib=objectTag" >> rep_picto.scr
echo "samevalue=" >> rep_picto.scr
echo " " >> rep_picto.scr
echo "widgetclass=Pictograph" >> rep_picto.scr
echo "hasattrib=nomeFile" >> rep_picto.scr
echo "value=motorNormally" >> rep_picto.scr
echo "attrib=objectTag" >> rep_picto.scr
echo "samevalue=" >> rep_picto.scr
#
#----------------------------------------------------------------------------
# Prepara lo script di ricerca per IndicTelep
#----------------------------------------------------------------------------
#
echo "widgetclass=IndicTelep" > rep_intel.scr
echo "hasattrib=tipoInd" >> rep_intel.scr
echo "value=0" >> rep_intel.scr
echo "attrib=objectTag" >> rep_intel.scr
echo "samevalue=" >> rep_intel.scr
echo " " >> rep_intel.scr
echo "widgetclass=IndicTelep" >> rep_intel.scr
echo "hasattrib=tipoInd" >> rep_intel.scr
echo "value=1" >> rep_intel.scr
echo "attrib=objectTag" >> rep_intel.scr
echo "samevalue=" >> rep_intel.scr
echo " " >> rep_intel.scr
echo "widgetclass=IndicTelep" >> rep_intel.scr
echo "hasattrib=tipoInd" >> rep_intel.scr
echo "value=2" >> rep_intel.scr
echo "attrib=objectTag" >> rep_intel.scr
echo "samevalue=" >> rep_intel.scr
echo " " >> rep_intel.scr
echo "widgetclass=IndicTelep" >> rep_intel.scr
echo "hasattrib=tipoInd" >> rep_intel.scr
echo "value=3" >> rep_intel.scr
echo "attrib=objectTag" >> rep_intel.scr
echo "samevalue=" >> rep_intel.scr
echo " " >> rep_intel.scr
echo "widgetclass=IndicTelep" >> rep_intel.scr
echo "hasattrib=tipoInd" >> rep_intel.scr
echo "value=5" >> rep_intel.scr
echo "attrib=objectTag" >> rep_intel.scr
echo "samevalue=" >> rep_intel.scr
echo " " >> rep_intel.scr
echo "widgetclass=IndicTelep" >> rep_intel.scr
echo "hasattrib=tipoInd" >> rep_intel.scr
echo "value=6" >> rep_intel.scr
echo "attrib=objectTag" >> rep_intel.scr
echo "samevalue=" >> rep_intel.scr
#
#----------------------------------------------------------------------------
# Prepara lo script di ricerca per IndicTelep con O.W.
#----------------------------------------------------------------------------
#
echo "widgetclass=IndicTelep" > rep_indow.scr
echo "hasattrib=tipoInd" >> rep_indow.scr
echo "value=4" >> rep_indow.scr
echo "attrib=objectTag" >> rep_indow.scr
echo "samevalue=" >> rep_indow.scr
#
#############################################################################
# Loop di elaborazione per le pagine da processare
#############################################################################
#
echo ${star5}
echo "\n" >> direct.sh.log
ls ${lista_plant} | while read plantd
do
  file=`echo ${plantd} | cut -f1 -d'.'`
#  echo 
  echo "****** pagmod: Elaborating ${file}\t*********"
  rm -f ${plantd}.scr
#
#----------------------------------------------------------------------------
# Prepara le liste delle tag da sostituire
#----------------------------------------------------------------------------
#
  pagmod -g -n -p ${plantd} -s rep_indic.scr 2> ${plantd}.listatag.indic
  pagmod -g -n -p ${plantd} -s rep_picto.scr 2> ${plantd}.listatag.picto
  pagmod -g -n -p ${plantd} -s rep_intel.scr 2> ${plantd}.listatag.intel
  pagmod -g -n -p ${plantd} -s rep_indow.scr 2> ${plantd}.listatag.indow
  echo ${star2} >> direct.sh.log
  echo ${plantd} >> direct.sh.log
#
#----------------------------------------------------------------------------
# Elaborazione degli Indic
#----------------------------------------------------------------------------
#
  cat ${plantd}.listatag.indic | cut -f2 -d: | tr -d ' \011' | while read tag
  do
#
# Cerca la tag specificata 
#
    variabile=`grep ${tag} variabili.tag | cut -f1 -d' '`
    VariableLineNumber=`grep ${tag} variabili.tag | wc -l | tr -s '\011' ' '| tr -d ' '`
#
# Prepara lo script di sostituzione
#
    if [ "${variabile}" = "" ]
    then
      echo "ERROR\t: Tag ["${tag}"] of ${plantd} not found in the simulator" >> direct.sh.log
      echo "ERROR\t: Tag ["${tag}"] of ${plantd} not found in the simulator"
    elif [ ! "${VariableLineNumber}" = "1" ]
    then
      echo ${star4} >> direct.sh.log
      echo "ERROR\t: Tag ["${tag}"] of ${plantd} found more than one time in the simulator" >> direct.sh.log
      echo "ERROR\t: Tag ["${tag}"] of ${plantd} found more than one time in the simulator"
      grep ${tag} variabili.tag >> direct.sh.log
      echo ${star4} >> direct.sh.log
    else
      scal=`grep ${tag} ${dirstaz}/DirLinksAn.list | tr -s '\011' ' ' | cut -f2 -d' '`
      offset=`grep ${tag} ${dirstaz}/DirLinksAn.list | tr -s '\011' ' ' | cut -f3 -d' '`
      if [ "${scal}" = "" ]
      then
        echo "ERROR\t: Tag ${tag} of ${plantd} not found in ${dirstaz}/DirLinksAn.list" >> direct.sh.log
        echo "ERROR\t: Tag ${tag} of ${plantd} not found in ${dirstaz}/DirLinksAn.list"
      else
        echo "#" >> ${plantd}.scr
        echo "#" Modifiche in ${plantd} per tag ${tag} >> ${plantd}.scr
        echo "#" >> ${plantd}.scr
        echo widgetclass=Indic >> ${plantd}.scr
        echo hasattrib=objectTag >> ${plantd}.scr
        echo value=${tag} >> ${plantd}.scr
        echo attrib=scalamento >> ${plantd}.scr
        echo value=${scal} >> ${plantd}.scr
        echo attrib=offset >> ${plantd}.scr
        echo value=${offset} >> ${plantd}.scr
        echo newattrib=varInputCambioColore1 >> ${plantd}.scr
        echo "value=${variabile} BLOCCO TASK NOP 1.0 0.0 ---" >> ${plantd}.scr
        echo attrib=varInputCambioColore1 >> ${plantd}.scr
        echo "value=${variabile} BLOCCO TASK NOP 1.0 0.0 ---" >> ${plantd}.scr
      fi
    fi
  done
#
#----------------------------------------------------------------------------
# Elaborazione dei Pictograph
#----------------------------------------------------------------------------
#
  cat ${plantd}.listatag.picto | cut -f2 -d: | tr -d ' \011' | while read tag
  do
#
# Cerca la tag specificata
#
    variabile=`grep ${tag} variabili.tag | cut -f1 -d' '`
#
# Prepara lo script di sostituzione
#
    if [ "${variabile}" = "" ]
    then
      echo "ERROR\t: Tag [${tag}] of ${plantd} not found in simulator" >> direct.sh.log
      echo "ERROR\t: Tag [${tag}] of ${plantd} not found in simulator"
    else
      echo "#" >> ${plantd}.scr
      echo "#" Modifiche in ${plantd} per tag ${tag} >> ${plantd}.scr
      echo "#" >> ${plantd}.scr
      echo widgetclass=Pictograph >> ${plantd}.scr
      echo hasattrib=objectTag >> ${plantd}.scr
      echo value=${tag} >> ${plantd}.scr
      echo attrib=varInputCambioColore1_1 >> ${plantd}.scr
      echo "value=${variabile} BLOCCO TASK NOP 1.0 0.0 ---" >> ${plantd}.scr
    fi
  done
#
#----------------------------------------------------------------------------
# Elaborazione degli IndicTelep
#----------------------------------------------------------------------------
#
  cat ${plantd}.listatag.intel | cut -f2 -d: | tr -d ' \011' | while read tag
  do
#
# Cerca la tag specificata
#
    variabile=`grep ${tag} variabili.tag | cut -f1 -d' '`
#
# Prepara lo script di sostituzione
#
    if [ "${variabile}" = "" ]
    then
      echo "ERROR\t: Tag [${tag}] of ${plantd} not found in simulator" >> direct.sh.log
      echo "ERROR\t: Tag [${tag}] of ${plantd} not found in simulator"
    else
      echo "#" >> ${plantd}.scr
      echo "#" Modifiche in ${plantd} per tag ${tag} >> ${plantd}.scr
      echo "#" >> ${plantd}.scr
      echo widgetclass=IndicTelep >> ${plantd}.scr
      echo hasattrib=tipoInd >> ${plantd}.scr
      echo value=0 >> ${plantd}.scr
      echo hasattrib=objectTag >> ${plantd}.scr
      echo value=${tag} >> ${plantd}.scr
      echo attrib=varInputCambioColore1 >> ${plantd}.scr
      echo "value=${variabile} BLOCCO TASK NOP 1.0 0.0 ---" >> ${plantd}.scr
      echo " " >> ${plantd}.scr
      echo widgetclass=IndicTelep >> ${plantd}.scr
      echo hasattrib=tipoInd >> ${plantd}.scr
      echo value=1 >> ${plantd}.scr
      echo hasattrib=objectTag >> ${plantd}.scr
      echo value=${tag} >> ${plantd}.scr
      echo attrib=varInputCambioColore1 >> ${plantd}.scr
      echo "value=${variabile} BLOCCO TASK NOP 1.0 0.0 ---" >> ${plantd}.scr
      echo " " >> ${plantd}.scr
      echo widgetclass=IndicTelep >> ${plantd}.scr
      echo hasattrib=tipoInd >> ${plantd}.scr
      echo value=2 >> ${plantd}.scr
      echo hasattrib=objectTag >> ${plantd}.scr
      echo value=${tag} >> ${plantd}.scr
      echo attrib=varInputCambioColore1 >> ${plantd}.scr
      echo "value=${variabile} BLOCCO TASK NOP 1.0 0.0 ---" >> ${plantd}.scr
      echo " " >> ${plantd}.scr
      echo widgetclass=IndicTelep >> ${plantd}.scr
      echo hasattrib=tipoInd >> ${plantd}.scr
      echo value=3 >> ${plantd}.scr
      echo hasattrib=objectTag >> ${plantd}.scr
      echo value=${tag} >> ${plantd}.scr
      echo attrib=varInputCambioColore1 >> ${plantd}.scr
      echo "value=${variabile} BLOCCO TASK NOP 1.0 0.0 ---" >> ${plantd}.scr
      echo " " >> ${plantd}.scr
      echo widgetclass=IndicTelep >> ${plantd}.scr
      echo hasattrib=tipoInd >> ${plantd}.scr
      echo value=5 >> ${plantd}.scr
      echo hasattrib=objectTag >> ${plantd}.scr
      echo value=${tag} >> ${plantd}.scr
      echo attrib=varInputCambioColore1 >> ${plantd}.scr
      echo "value=${variabile} BLOCCO TASK NOP 1.0 0.0 ---" >> ${plantd}.scr
      echo " " >> ${plantd}.scr
      echo widgetclass=IndicTelep >> ${plantd}.scr
      echo hasattrib=tipoInd >> ${plantd}.scr
      echo value=6 >> ${plantd}.scr
      echo hasattrib=objectTag >> ${plantd}.scr
      echo value=${tag} >> ${plantd}.scr
      echo attrib=varInputCambioColore1 >> ${plantd}.scr
      echo "value=${variabile} BLOCCO TASK NOP 1.0 0.0 ---" >> ${plantd}.scr
    fi
  done
#
#----------------------------------------------------------------------------
# Elaborazione degli IndicTelep con Operating Window
#----------------------------------------------------------------------------
#
  if [ -f superlista.list ]
  then
    cat ${plantd}.listatag.indow | cut -f2 -d: | tr -d ' \011' | while read tag
    do
#
# Cerca la tag specificata
#
      variabile1=UU`grep ${tag}'$'S531 superlista.list | \
        tr -s '\011' ' ' | cut -f2 -d' '`
      variabile2=VF`grep ${tag}'$'S531 superlista.list | \
        tr -s '\011' ' ' | cut -f2 -d' '`
      variabile3=`grep ${tag}'$'KKS_MEAS superlista.list | \
        tr -s '\011' ' ' | cut -f2 -d' '`'_XZ01$F SUPERVIS'
      scal=`grep ${tag}'$'SCALVAL superlista.list | \
        tr -s '\011' ' ' | cut -f2 -d' '`
      offset=`grep ${tag}'$'OFFSET superlista.list | \
        tr -s '\011' ' ' | cut -f2 -d' '`
#
# Prepara lo script di sostituzione
#
      if [ "${variabile1}" = "UU" ]
      then
        echo "ERROR\t: OW [${tag}] of ${plantd} not found in superlista.list" >> direct.sh.log
        echo "ERROR\t: OW [${tag}] of ${plantd} not found in superlista.list"
      else
        echo "#" >> ${plantd}.scr
        echo "#" Modifiche in ${plantd} per tag ${tag} >> ${plantd}.scr
        echo "#" >> ${plantd}.scr
        echo widgetclass=IndicTelep >> ${plantd}.scr
        echo hasattrib=tipoInd >> ${plantd}.scr
        echo value=4 >> ${plantd}.scr
        echo hasattrib=objectTag >> ${plantd}.scr
        echo value=${tag} >> ${plantd}.scr
        echo attrib=scalamento >> ${plantd}.scr
        echo value=${scal} >> ${plantd}.scr
        echo attrib=offset >> ${plantd}.scr
        echo value=${offset} >> ${plantd}.scr
        echo attrib=varInputCambioColore1 >> ${plantd}.scr
        echo "value=${variabile1} BLOCCO TASK NOP 1.0 0.0 ---" >> ${plantd}.scr
        echo attrib=varInputCambioColore2 >> ${plantd}.scr
        echo "value=${variabile2} BLOCCO TASK NOT 1.0 0.0 ---" >> ${plantd}.scr
        echo attrib=varInputCambioColore3 >> ${plantd}.scr
        echo "value=${variabile3}" >> ${plantd}.scr
      fi
    done
  else
    echo "Non esiste il file superlista.list !!!"
  fi
#
#----------------------------------------------------------------------------
# Esegue lo script di sostituzione
#----------------------------------------------------------------------------
#
  if [ -f "${plantd}.scr" ]
  then
    pagmod -p ${plantd} -s ${plantd}.scr
#
# Sostituisce il risultato del pagmod nel .pag originale
#
    mv ${plantd}.mod ${dirstaz}/${plantd}
  else
    if [ "${sim}" = "remote" ]
    then
      cp ${plantd} ${dirstaz}/${plantd}
    fi
#    echo Plant display ${plantd} non viene elaborato >> direct.sh.log
    cp -p ${plantd}.ori ${plantd} 
  fi
  if [ "${sim}" = "remote" ]
  then
    cp ${file}.bkg ${dirstaz}/${file}.bkg
    mv ${plantd}.ori ${plantd}
  fi
done
#
#############################################################################
# Fine loop - Operazioni di chiusura
#############################################################################
#
rm -f ${dirstaz}/*.listatag.*
cd ${dirplant}
ls | grep listatag | while read poubelle
do
rm -f ${poubelle}
done
rm -f ${dirstaz}/variabili.tag

