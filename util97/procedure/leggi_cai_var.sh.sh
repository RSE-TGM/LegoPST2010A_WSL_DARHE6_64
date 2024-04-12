export gerarchia=""
export ger_prec=""
export counter=0
export lista_kks=""
export IFS=,
rm -f CAI_VAR_DB.dir CAI_VAR_DB.pag leggi_cai_var.log
touch CAI_VAR_DB.dir CAI_VAR_DB.pag
echo
echo " " >> $KLOG/kMakeCaiVar.log
cat cai_var.dat | sort | tr -d \" | while read ger1 ger2 ger3 ger4 ger5 ger6 tipo kks
do
export gerarchia=${ger1}:${ger2}:${ger3}:${ger4}:${ger5}:${ger6}:${tipo}
kks=${kks}\$${tipo}
if [ "$ger_prec" != "" ]
then
  if [ "$ger_prec" != "$gerarchia" ]
  then
    if [ "${counter}" -le 10 ]
    then
      echo ${ger_prec} ${counter}:${lista_kks}
    else
      echo "WARNING\t: The hierarchy ${ger_prec} is associated to $counter alarms"
      echo "WARNING\t: The hierarchy ${ger_prec} is associated to $counter alarms" >> $KLOG/kMakeCaiVar.log
    fi
       ger_prec=$gerarchia
      let counter=1
      lista_kks=$kks
  else
    let counter=$counter+1
    lista_kks="${lista_kks}:${kks}"
  fi
else
  ger_prec=$gerarchia
  let counter=1
  lista_kks=$kks
fi
done  | dbmins_mul CAI_VAR_DB >>leggi_cai_var.log 2>>leggi_cai_var.log 
#done >> log.log
 
