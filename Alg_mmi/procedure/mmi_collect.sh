#!/bin/ksh
#
#   modulo mmi_collect.sh
#   tipo 
#   release 1.2
#   data 96/04/04
#   reserved @(#)mmi_collect.sh	1.2
#
#Programma per la raccolta di tutti gli schemi di regolazione di un simulatore
#in una sola directory
#Non vengono copiate le .pag ma solo i .rtf e i .bkg opportunamente tradotti
#tramite rilocazione dei puntatori rispetto allo spazio occupato da ogni task
#in shared memory
#
#Inizializzazioni
#
savepwd=$PWD
count=0
page_count=0
stringa=''
GLOBPAGES=globpages
WINDIR=o_win
#
#Controllo dell'esistenza dei files
#
if [ ! -d $GLOBPAGES ]
then
echo Errore: non esiste la directory $GLOBPAGES
exit 1
fi
#
if [ ! -d $WINDIR ]
then
echo Errore: non esiste la directory $WINDIR
exit 1
fi
if [ ! -f S01 ]
then
echo Errore: non esiste il file S01
exit 2
fi
if [ ! -f variabili.edf ]
then
echo Errore: non esiste il file variabili.edf
exit 3
fi
#

#Generazione della prima parte del file Context.ctx
#
cat >$GLOBPAGES/Context.ctx <<!EOF
*numTagPag:	0
*iconlib_list:
*displayList:   puerto2 puerto7
*numDisplay:	2
*hostName:
*iconlib_num:  0
*description:
*iconlib_label: 
*nextTagPag:	01
*simulator: $PWD
*pages:	$PWD/$GLOBPAGES
*objectLibraries:	$PWD
*animatedIconLibraries:	$PWD/../../legocad/libut_reg/libreg
*project:	$PWD
!EOF
#
#Determinazione dello spazio allocato ad una task (vale solo per simulatore
#ad allocazione statica)
#
MAX_ALLOC_MODEL=`rt_get_param max_alloc_model`

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
#per ogni modello analisi del variabili.edf per determinarne la posizione
#
do
grep 'NOME MODELLO' variabili.edf | grep $tok3  | read toka tokb tokc tokd toke
let posizione=tokc-1
let offset=posizione\*$MAX_ALLOC_MODEL
echo $tokd $tok1 $tokc $offset
#
#per ogni directory di modello 
#
cd $tok1
ls $tok4???.rtf | 
while read file
do
#
#riloco tutte i file rtf delle pagine di regolazione
#
chgcompiled $posizione $offset <$file >$savepwd/$GLOBPAGES/$file
done
cd $savepwd
ls $tok1/$tok4???.bkg | 
while read file
do
#
#creo un link per tutti i bkg delle pagine di regolazione
#
ln -sf ../$file $GLOBPAGES
done
cd $tok1
ls $tok4???.rtf | 
cut -f1 -d. |
while read tag
do
let page_count=page_count+1
stringa="$stringa $tag"
done
cd $savepwd
done
#
#creo un link per tutte le rtf ed i bkg delle stazioni di regolazione
#
cd $WINDIR
ls O_*.rtf | 
cut -f1 -d. | 
while read file
do
ln -sf ../$WINDIR/$file.rtf ../$GLOBPAGES
ln -sf ../$WINDIR/$file.bkg ../$GLOBPAGES
let page_count=page_count+1
stringa="$stringa $file"
done
#
ls F_*.rtf | 
cut -f1 -d. | 
while read file
do
ln -sf ../$WINDIR/$file.rtf ../$GLOBPAGES
ln -sf ../$WINDIR/$file.bkg ../$GLOBPAGES
let page_count=page_count+1
stringa="$stringa $file"
done
#
ls M_*.rtf |
cut -f1 -d. |
while read file
do
ln -sf ../$WINDIR/$file.rtf ../$GLOBPAGES
ln -sf ../$WINDIR/$file.bkg ../$GLOBPAGES
let page_count=page_count+1
stringa="$stringa $file"
done
#
#Generazione della seconda parte del file Context.ctx
#
cd $savepwd
echo *pag_num: $page_count >> $GLOBPAGES/Context.ctx
echo *page_list: $stringa >> $GLOBPAGES/Context.ctx
#

