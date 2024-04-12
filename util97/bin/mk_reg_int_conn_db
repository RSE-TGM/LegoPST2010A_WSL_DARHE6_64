#############################################################################
#
# Prepara il database delle connessioni interne agli schemi di regolazione
#
# Villa G.W. 11/2/98
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
  echo "\n uso: $0 \n\a"
  exit 1
fi
#
# inizializzazioni
#
#
# controllo dell'esistenza del file S01
#
if [ ! -f S01 ]
then
  echo Errore: non esiste il file S01
  exit 2
fi
#
touch REG_INT_CONN_DB.dir
touch REG_INT_CONN_DB.pag
#
#############################################################################
# analisi del file S01 per individuare i modelli
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
# merge dei file .list
#############################################################################
#
do
grep -h "<===" ${tok1}/proc/*_01.dat | cut -f1 -d. |tr "#" " "| while read primo salta secondo
do
echo ${secondo} ${primo}
done | dbmins_mul REG_INT_CONN_DB 
ls -l REG_INT_CONN_DB*
done
