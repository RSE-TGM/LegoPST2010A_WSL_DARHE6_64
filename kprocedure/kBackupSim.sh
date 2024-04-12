#############################################################################
#
# Programma di backup di un simulatore ready to start con sked, modelli,
# librerie e appligips pi file accessori
#
# Villa G.W. 2006
#
#############################################################################
#
#############################################################################
# Operazioni preliminari
#############################################################################
#
# controllo dei parametri passati
#
if [ "$1" != "" ]
then
  echo "Error! use: $0 (without any parameter)"
  exit
fi
#
# controllo che sia definito il KSIM
#
if [ "$KSIM" = "" ]
then
  echo "Error! environment variable KSIM must be defined"
  exit
fi
#
# inizializzazioni
#
cd $HOME

export dirsim=`echo $KSIM | sed s#$HOME#.#`
export count=0
export listafiletar="./appligips "
listafiletar=${listafiletar}"./legocad/libut ./legocad/libut_reg ./legocad/libut_mmi ./legocad/libut_bin " 
listafiletar=${listafiletar}" "$dirsim" "`echo $KCASSAFORTE | sed s#$HOME#.#`
listafiletar=${listafiletar}" ./fluidiroot.dat ./gipsroot.dat ./task_process.dat ./task_treatment.dat ./taskroot.dat ./gips.korn ./bin ./risorse"
#
#############################################################################
# pulizia preventiva dai file inutili
#############################################################################
#
#kPulirSim
#
# controllo dell'esistenza del file S01
#
cd ${dirsim}
if [ ! -f S01 ]
then
  echo "Error: file S01 not found in ${dirsim}"
  exit
fi
#
#############################################################################
# analisi del file S01 per individuare i modelli
#############################################################################
#
listafiletar=${listafiletar}" "`cat S01 |
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
done  | while read tok1 tok2 
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
echo ${dirsim}/${tok1}
done` 
cd $HOME
#
#############################################################################
# Creazione del tar completo e compresso
#############################################################################
#

tar  cvzf `basename ${KSIM}`-`whoami`-`hostname`-`date +%d_%b_%Y`.tgz ${listafiletar}
