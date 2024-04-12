#!/bin/ksh
#
#  Script:                      librmake.tpl.sh
#  Subsystem:           1
#  %version:            2 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Wed Feb 19 17:00:30 1997 %

#!/bin/ksh
# Script Shell per la manutenzione di una libreria di oggetti
# usando una procedura make.
# Si copia questo file nella directory contenente i sorgenti
# e si personalizza seguendo l'esempio presente:
# Si prepara una variabile d'ambiente LISTA con tutti i targets
# che si desiderano aggiornare.
# Si inserisce in NOME_LIB il nome della libreria

LISTA=`ls *.f |grep -v forausbase | cut -f1 -d. | while read var 
do
  echo '$(LEGO_LIB)/NomeLibreria.a('$var'.o)'
done`
echo $LISTA
export LISTA
NOME_LIB=''
export NOME_LIB

# Si esegue il makefile makelibr a cui si passa la LISTA.
make -f $LEGO_BIN/makelibr

