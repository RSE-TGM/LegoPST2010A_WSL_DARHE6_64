#!/bin/sh
#
#  Script:                      cad_lism2lis.sh
#  Subsystem:           1
#  %version:            2.1.1 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Mon Dec 16 15:26:07 2002 %

#!/bin/ksh
#####################################################################
#   modulo cad_lism2lis.sh
#   tipo 
#   release 1.1
#   data 96/04/23
#   reserved @(#)cad_lism2lis.sh	1.1
#
#####################################################################
#
# Questa script shell consente la costruzione dell'elenco dei
# moduli dichiarati in una libut a partire dalla lettura
# del file lista_moduli.dat presente nella libut stessa
# l'elenco fornito su standard output e' quello dei files oggetto
# da compilare (se necessario) senza collocarli in alcuna libreria
#
#####################################################################
#
if [ ! -r lista_moduli.dat ]
then
 exit 1 
fi
cat lista_moduli.dat | cut -c1-4 | uniq \
| tr 'ABCDEFGHIJKLMNOPQRSTUVWXYZ' 'abcdefghijklmnopqrstuvwxyz' \
| while read base
do
if [ -r ${base}.f ]
then
OBJECTS="$OBJECTS ${base}.o"
echo $OBJECTS > appo
else
exit 2
fi
done
cat appo
rm appo
echo $OBJECTS
