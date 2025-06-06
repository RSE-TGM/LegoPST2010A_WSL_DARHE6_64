#!/bin/bash
#
#  Script:                      crealibut_reg.sh
#  Subsystem:           1
#  %version:            3 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Wed Feb 19 16:59:42 1997 %

#!/bin/ksh
# Script Shell per la manutenzione di una libreria di oggetti
# usando una procedura make.
# Si copia questo file nella directory contenente i sorgenti
# e si personalizza seguendo l'esempio presente:
# Si prepara una variabile d'ambiente LISTA con tutti i targets
# che si desiderano aggiornare.


#  creazione procedura modidat.f per svincolo i2 (per inserimento in lib)
$LEGO_BIN/svinri2

LISTA_ARRAY=() # In ksh o bash, per array
for f in *.f; do
  if [[ "$f" != "forausbase.f" ]]; then # Evita forausbase.f
    basename="${f%.f}" # Rimuove .f
    LISTA_ARRAY+=("${basename}.o")
  fi
done
LISTA="${LISTA_ARRAY[*]}" # Converte l'array in una stringa separata da spazi

echo "LISTA generata: [$LISTA]" # Debug
export LISTA


#LISTA=`ls *.f |grep -v forausbase | cut -f1 -d. | while read var 
#do
#  echo ''$var'.o'
#done`
#echo $LISTA
#export LISTA

NOME_LIB='schemi_reg.a'
LIBRERIA='schemi_reg.a'
export NOME_LIB
export LIBRERIA

# Si esegue il makefile makelibr a cui si passa la LISTA.
make -f $LEGO_BIN/makelibr

rm -f modidat.f
rm -f errori.comp

ls *.f |grep -v forausbase | cut -f1 -d. | while read var
do
if [ `grep -c BUFDATI $var.f` = 0 ]
        then
        echo 'Errore: modificare lo schema' $var'.f' >> errori.comp
        fi
done

FILE='errori.comp'

if test -r "$FILE"
then
      echo '******************************************************************'
      echo '* Rinvenuti errori di compilazione, vedi file errori.comp        *'
      echo '* utilizzare il programma main_modscreg per inserire la modifica *'
      echo '******************************************************************'
      exit 0
fi


#  creazione procedura modidat.f per svincolo i2 (compilazione main_refresh_r)
$LEGO_BIN/svinri2

# Creazione refresh_dat
make -f $LEGO_BIN/maketask main_refresh_r
