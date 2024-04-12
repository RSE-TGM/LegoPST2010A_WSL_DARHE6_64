#!/bin/ksh
#
#  Script:                      cad_crealibut.sh
#  Subsystem:           1
#  %version:            7 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Tue Apr 21 13:28:38 2009 %

#!/bin/ksh
# Script Shell per la manutenzione di una libreria di oggetti
# usando una procedura make.
# Si copia questo file nella directory contenente i sorgenti
# e si personalizza seguendo l'esempio presente:
# Si prepara una variabile d'ambiente LISTA con tutti i targets
# che si desiderano aggiornare.
#
LISTA=`ls *.f |grep -v forausbase |grep -v modi | cut -f1 -d. | while read var 
do
  echo ''$var'.o'
done | tr "\n" " "`
echo $LISTA
export LISTA
NOME_LIB='modulilib.a'
LIBRERIA='modulilib.a'
export NOME_LIB
export LIBRERIA
export FFLAGS
export CFLAGS

# Si esegue il makefile makelibr a cui si passa la LISTA.
make -f $LEGO_BIN/makelibr
if [ "$LEGOCAD_EMM" = YES ]
then
# crea file oggetto e non libreria
make `cad_lism2lis` FFLAGS="${F_FLAGS}"
make `cad_lisc2lis` FFLAGS="${F_FLAGS}"
LISTA=`cad_lisc2lis`
LIBRERIA="auxlegolib.a"
# Si esegue il makefile makelibr a cui si passa la LISTA.
make -f $LEGO_BIN/makelibr
fi
ranlib $NOME_LIB
# crea la routine modi.f
creamodi
mv modi.for modi.f
# esegue il makefile per la (eventuale) creazione di legoserver
# cioe' del processo che viene interrogato per la instanziazione
# dei moduli lego
make -f $LEGOCAD/legoserver/Makefile
echo 'Done'
