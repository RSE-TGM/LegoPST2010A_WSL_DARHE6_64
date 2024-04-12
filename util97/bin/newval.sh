#############################################################################
#
# Sostituisce uno o piu valori di un attributo inputValue specificato 
# internamente allo script nelle pagine di una task di regolazione
#
#############################################################################
#
#############################################################################
# Operazioni preliminari
#############################################################################
#
export pagina
rm -f newval.sh.log
#
#############################################################################
# Preparazione dello script di input di pagmod
#############################################################################
#
echo "widgetclass=IconReg" > newval.scr
echo "hasattrib=modulName" >> newval.scr
echo "value=sac1" >> newval.scr
echo "inputrep=19,1" >> newval.scr
echo "value=|1.0000E+00|" >> newval.scr
echo "inputrep=37,1" >> newval.scr
echo "value=|4.0000E+02|" >> newval.scr
echo "inputrep=38,1" >> newval.scr
echo "value=|2.0000E+02|" >> newval.scr
echo "widgetclass=IconReg" >> newval.scr
echo "hasattrib=modulName" >> newval.scr
echo "value=sac2" >> newval.scr
echo "inputrep=8,1" >> newval.scr
echo "value=|1.0000E+00|" >> newval.scr
echo "inputrep=14,1" >> newval.scr
echo "value=|4.0000E+02|" >> newval.scr
echo "inputrep=15,1" >> newval.scr
echo "value=|2.0000E+02|" >> newval.scr
echo "widgetclass=IconReg" >> newval.scr
echo "hasattrib=modulName" >> newval.scr
echo "value=sac3" >> newval.scr
echo "inputrep=8,1" >> newval.scr
echo "value=|1.0000E+00|" >> newval.scr
echo "inputrep=16,1" >> newval.scr
echo "value=|4.0000E+02|" >> newval.scr
echo "inputrep=17,1" >> newval.scr
echo "value=|2.0000E+02|" >> newval.scr
echo "widgetclass=IconReg" >> newval.scr
echo "hasattrib=modulName" >> newval.scr
echo "value=sac4" >> newval.scr
echo "inputrep=9,1" >> newval.scr
echo "value=|1.0000E+00|" >> newval.scr
echo "inputrep=17,1" >> newval.scr
echo "value=|4.0000E+02|" >> newval.scr
echo "inputrep=18,1" >> newval.scr
echo "value=|2.0000E+02|" >> newval.scr
#
#############################################################################
# Loop sulle pagine
#############################################################################
#
ls ????.pag | while read pagina
do
  grep 'sac1' ${pagina} > newval.tmp
  grep 'sac2' ${pagina} >> newval.tmp
  grep 'sac3' ${pagina} >> newval.tmp
  grep 'sac4' ${pagina} >> newval.tmp
  if [ -s newval.tmp ]
  then
    echo ${pagina}
    pagmod -g -p ${pagina} -s newval.scr 2> newval.sh.log
    cp ${pagina} ${pagina}.old
    sed s/'||'/'| |'/g ${pagina}.mod | sed s/'|  |'/'| |'/g > ${pagina}
    rm -f ${pagina}.mod
  fi
done
#
#############################################################################
# Fine loop
#############################################################################
#
rm -f newval.tmp
rm -f newval.scr
