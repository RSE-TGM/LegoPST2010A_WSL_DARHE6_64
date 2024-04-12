#!/bin/sh
#
#  Script:                      cad_f012lis.sh
#  Subsystem:           1
#  %version:            3.1.1 %
#  Description:
#  %created_by:         ciccotel %
#  %date_created:       Mon Jan 13 09:52:06 2003 %
#####################################################################
#   modulo cad_f012lis.sh
#   tipo 
#   release 1.4
#   data 96/04/23
#   reserved @(#)cad_f012lis.sh	1.4
#
#####################################################################
#
# Questa script shell consente la costruzione dell'elenco dei
# moduli utilizzati da un modello a partire dalla lettura
# del file f01.dat locale alla directory da dove viene eseguita
# l'elenco fornito su standard output e' quello dei files oggetto
# da utilizzare nel linking dei vari programmi lego con una
# gestione della priorita' tra moduli presenti localmente 
# rispetto a quelli in libut
#
#####################################################################
#
export OBJECTS=''
if [ ! -r f01.dat ]
then
 exit 1 
fi
export FLAG=1
cat f01.dat | while read var
do
if [ $FLAG = 1 ]
then
 FLAG=2
elif [ "$var" != "****" ]
then
 echo "$var"
else
exit 0
fi
done | cut -c1-4 | sort | uniq | tr 'ABCDEFGHIJKLMNOPQRSTUVWXYZ' 'abcdefghijklmnopqrstuvwxyz' \
| while read base
do
if [ -r ${base}.f ]
then
OBJECTS="$OBJECTS ${base}.o"
echo $OBJECTS > appo
elif [ -r ../libut/${base}.f ] 
then
OBJECTS="$OBJECTS ../libut/${base}.o"
echo $OBJECTS > appo
else
exit 2
fi
done
OBJECTS=$(cat appo)
rm appo
if [ "$LEGOCAD_EMM" = YES ]
then
if [ -r ../libut/auxlegolib.a ]
then
OBJECTS="$OBJECTS ../libut/auxlegolib.a"
else
exit 4
fi
else
cat ../libut/lista_complementari.dat | cut -f1 -d. | while read base
do
if [ -r ${base}.f ]
then
OBJECTS="$OBJECTS ${base}.o"
elif [ -r ../libut/${base}.f ] 
then
OBJECTS="$OBJECTS ../libut/${base}.o"
else
exit 3
fi
done
fi
echo $OBJECTS
