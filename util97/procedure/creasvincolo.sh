# Script che crea il DB di svincolo per le variabili 
# collegate all'interno degli schemi di regolazione.
touch REG_INT_CONN_DB.dir
touch REG_INT_CONN_DB.pag
grep -h "<===" *_01.dat | cut -f1 -d. | while read primo salta secondo
do
echo ${secondo}${primo}
dbmins REG_INT_CONN_DB 10 ${secondo}${primo}
done
ls -l REG_INT_CONN_DB*
