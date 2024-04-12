#!/bin/ksh
#
#
# Procedura per aggiornare i file win*.list e mal*.list
# globali nel direttorio ~/sked/cc_puerto_cold/o_win partendo 
# dai files di ogni task di regolazione
#
# Dragoni M. Vers. 1.0
#
#Inizializzazioni
#
count=0
IOSONOQUI=`pwd`
DIRSIM=`pwd`
DIRSTAZ=$DIRSIM/o_win
#
#Controllo dell'esistenza dei files
#
cd $DIRSIM
if [ ! -f S01 ]
then
echo Errore: non esiste il file S01
exit
fi
rm $DIRSTAZ/win*
rm $DIRSTAZ/mal*
#
#analisi del file S01 per individuare i modelli
#
cat S01 |
while read var
do
if [ $count -lt 3 ]
then
if [ "$var" = '****' ]
then 
let count=count+1 
fi
continue
fi
if [ "$var" = '****' ]
then 
break 
fi
echo $var
done |
grep ' R ' |
while read tok1 tok2 tok3 tok4
#
# tok1 pathname
# tok2 Process/Regulation
# tok3 Task name
# tok4 Prima lettera degli schemi di regolazione
#
do
   cd $tok1
   ls win*.list |
   while read var
   do
      if [ ! -f $DIRSTAZ/$var ]
      then
         cat $var > $DIRSTAZ/$var
      else
         cat $var | grep -v '@#L@' >> $DIRSTAZ/$var
      fi
      sort $DIRSTAZ/$var > $DIRSTAZ/$var.ord
      mv $DIRSTAZ/$var.ord $DIRSTAZ/$var
   done
   ls mal*.list |
   while read var
   do
      if [ ! -f $DIRSTAZ/$var ]
      then
         cat $var > $DIRSTAZ/$var
      else
         cat $var | grep -v '@#L@' >> $DIRSTAZ/$var
      fi
      sort $DIRSTAZ/$var > $DIRSTAZ/$var.ord
      mv $DIRSTAZ/$var.ord $DIRSTAZ/$var
   done
   cd $DIRSIM
done
cd $IOSONOQUI
