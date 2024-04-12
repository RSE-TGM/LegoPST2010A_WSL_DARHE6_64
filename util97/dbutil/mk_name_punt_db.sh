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
# controllo dell'esistenza del file variabili.edf
#
if [ ! -f variabili.edf ]
then
  echo Errore: non esiste il file variabili.edf
  exit 2
fi
#
touch NAME_PUNT_DB.dir
touch NAME_PUNT_DB.pag
#
grep "\-\-..\-\-" variabili.edf | cut -f 2,3 -d " " | dbmins_mul  NAME_PUNT_DB
ls -l NAME_PUNT_DB*
