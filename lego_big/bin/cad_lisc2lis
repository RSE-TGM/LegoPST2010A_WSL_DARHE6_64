#!/bin/sh
#
#  Script:			cad_lisc2lis.sh
#  Instance:		1
#  %version:		1.1.2 %
#  Description:		
#  %created_by:		lomgr %
#  %date_created:	Mon Dec 16 15:23:57 2002 %
#####################################################################
#
# Questa script shell consente la costruzione dell'elenco dei
# files fortran dichiarati in una libut a partire dalla lettura
# del file lista_complementari.dat presente nella libut stessa
# l'elenco fornito su standard output e' quello dei files oggetto
# da compilare (se necessario) senza collocarli in alcuna libreria
#
#####################################################################
#
if [ ! -r lista_complementari.dat ]
then
 exit 1
fi
cat lista_complementari.dat | cut -f1 -d. | while read base
do
if [[ -r ${base}.f || -r ${base}.c ]]
then
OBJECTS="$OBJECTS ${base}.o"
#Modifica per Windows NT
echo $OBJECTS > appo
else
exit 2
fi
done
cat appo 
rm appo
echo $OBJECTS
