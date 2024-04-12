#!/bin/ksh
#
#  Script:                      crealibreg.sh
#  Subsystem:           1
#  %version:            3 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Wed Feb 19 16:59:27 1997 %

#!/bin/ksh
# Script Shell per la manutenzione di una libreria di oggetti
# usando una procedura make.
# Si copia questo file nella directory contenente i sorgenti
# e si personalizza seguendo l'esempio presente:
# Si prepara una variabile d'ambiente LISTA con tutti i targets
# che si desiderano aggiornare.
#
# La procedura si blocca automaticamente se vengono rinvenuti 
# dei moduletti non corretti per la modifica dei dati
#


LISTA=`ls *.f *.pf *.c |grep -v forausbase | cut -f1 -d. | while read var 
do
  echo ''$var'.o'
done`
echo $LISTA
export LISTA
NOME_LIB='reglib.a'
LIBRERIA='reglib.a'
export NOME_LIB
export LIBRERIA

# Si esegue il makefile makelibr a cui si passa la LISTA.
make -f $LEGO_BIN/makelibr

rm -f errori.comp
rm -f modidat.f

ls *.f |grep -v forausbase | cut -f1 -d. | while read var
do
if [ `grep -c BUFDATI $var.f` = 0 ]
        then
        echo 'Errore: modificare il modulo' $var'.f' >> errori.comp
        fi
done

FILE='errori.comp'

if test -r "$FILE"
then
        echo '***********************************************************'
        echo '* Rinvenuti errori di compilazione, vedi file errori.comp *'
        echo '***********************************************************'
        exit 0
fi
       
