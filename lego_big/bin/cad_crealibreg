#!/bin/ksh
#
#  Script:                      cad_crealibreg.sh
#  Subsystem:           1
#  %version:            4 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Fri Dec 20 15:30:11 2002 %

#!/bin/ksh
# Script Shell per la manutenzione di una libreria di oggetti
# usando una procedura make.
# Si copia questo file nella directory contenente i sorgenti
# e si personalizza seguendo l'esempio presente:
# Si prepara una variabile d'ambiente LISTA con tutti i targets
# che si desiderano aggiornare.

LISTA=`ls *.f |grep -v forausbase |grep -v modi | cut -f1 -d. | while read var 
do
  echo ''$var'.o'
done | tr "\n" " "`
echo $LISTA
export LISTA
NOME_LIB='reglib.a'
LIBRERIA='reglib.a'
export NOME_LIB
export LIBRERIA

# Si esegue il makefile makelibr a cui si passa la LISTA.
make -f $LEGO_BIN/makelibr
# crea le routines modrvar.f e modrdat.f
svinforms
# esegue il makefile per la (eventuale) creazione di regoserver
# cioe' del processo che viene interrogato per la instanziazione
# dei moduli di regolazione
make -f $LEGOCAD/regoserver/Makefile
if [ -x $LEGOMMI_BIN/crea_regforms ]
then
	crea_regforms
else
	echo "progetto Alg_mmi non presente"
fi
#
# copia il file di template per lg3_reg.f nel direttorio
# libreg
#
cp $LEGO/procedure/lg3_reg.tpl lg3_reg.dat
chmod a+w lg3_reg.dat
#
# copia il file di template per info_mac.f nel direttorio
# libreg
#
cp $LEGO/procedure/info_mac.tpl info_mac.dat
echo "done"
