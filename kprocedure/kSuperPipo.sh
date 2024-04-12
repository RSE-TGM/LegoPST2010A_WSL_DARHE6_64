#!/bin/ksh
#
rm -f $TMPDIR/kSuperPipo.txt
cd $LEGOCAD_USER/legocad
ls -d r_* | while read task
do
cd $task
echo ${star5}
echo $task : Cleaning rego task $1
echo ${star5}
#
ls *pag | while read page
do
Algo=`grep elenco_wid0 $page | tr '[:space:]' '[\n*]' | grep w | grep -v elenco_wid0 | sort | uniq -d`
if [ "$Algo" != "" ]
then
echo "\n${star7}\nPage $page :\n $Algo\n${star7}"
echo "\n${star7}\nPage $page :\n $Algo\n${star7}" >> $TMPDIR/kSuperPipo.txt
fi
done
#
cd $LEGOCAD_USER/legocad
done
echo "\n\a"
