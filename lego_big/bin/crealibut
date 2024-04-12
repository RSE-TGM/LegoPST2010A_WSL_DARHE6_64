
#!/bin/ksh
# Script Shell per la manutenzione di una libreria di oggetti
# usando una procedura make.
# Si copia questo file nella directory contenente i sorgenti
# e si personalizza seguendo l'esempio presente:
# Si prepara una variabile d'ambiente LISTA con tutti i targets
# che si desiderano aggiornare.

#  creazione procedura modidat.f per svincolo i2
$LEGO_BIN/svinli2

LISTA=`ls *.f |grep -v forausbase | cut -f1 -d. | while read var 
do
  echo ''$var'.o'
done`
echo $LISTA
export LISTA
NOME_LIB='modulilib.a'
LIBRERIA='modulilib.a'
export LIBRERIA
export NOME_LIB

# Si esegue il makefile makelibr a cui si passa la LISTA.
make -f $LEGO_BIN/makelibr

# Creazione refresh_dat
make -f $LEGO_BIN/maketask main_refresh_l
