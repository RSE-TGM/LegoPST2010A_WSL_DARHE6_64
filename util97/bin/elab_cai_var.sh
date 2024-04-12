#!/bin/ksh
#
export PAGMOD=pagmod
export display_dir=o_win
echo "widgetclass=CaiVar" > CaiVar.scr
echo "attrib=objectTag" >> CaiVar.scr
echo "samevalue=" >> CaiVar.scr
echo " " >> CaiVar.scr
echo " " >> $KLOG/kMakeCaiVar.log
#
ls ${display_dir}/M_S*.pag | while read pagina
do
	rm -f ${pagina}.scr
	touch ${pagina}.scr
	$PAGMOD -g -n -p $pagina -s CaiVar.scr 2> $pagina.elencocai
	cat $pagina.elencocai | cut -f2 -d':'| sort | while read riga
	do
	    echo $riga | tr ', ' '::' | while read chiave
	    do
	        tipo_alarm=`echo ${chiave} | cut -f7 -d:`
	        gerarchia=`echo ${chiave} | cut -f1-6 -d:`
	        if [ "${tipo_alarm}" = "X" ]
	        then
                   contenuto=""
                   counter=0
	           parziale=`dbmftc2 CAI_VAR_DB ${gerarchia}:A 2>> /dev/null`
                   if [ "${parziale}" != "" ]
		   then		     	      
		      inc_count=`echo ${parziale} | cut -f1 -d: `  
		      allarme=`echo ${parziale} | cut -f2-11 -d: `
		      let counter=${counter}+${inc_count}
		      contenuto=":${allarme}"
		      
                   fi
	           parziale=`dbmftc2 CAI_VAR_DB ${gerarchia}:P 2>> /dev/null`
                   if [ "${parziale}" != "" ]
		   then
		      inc_count=`echo ${parziale} | cut -f1 -d: `  
		      allarme=`echo ${parziale} | cut -f2-11 -d: `		      
		      let counter=${counter}+${inc_count}
		      contenuto="${contenuto}:${allarme}"
		      	
                   fi
	           parziale=`dbmftc2 CAI_VAR_DB ${gerarchia}:T 2>> /dev/null`
                   if [ "${parziale}" != "" ]
		   then
		      inc_count=`echo ${parziale} | cut -f1 -d: `  
		      allarme=`echo ${parziale} | cut -f2-11 -d: `		      
		      let counter=${counter}+${inc_count}
		      contenuto="${contenuto}:${allarme}"
		      		      
                   fi	
                   if [ $counter != 0 ]
                   then
                      contenuto="${counter}${contenuto}" 
                   fi 
                    
	        else
	           contenuto=""
	           counter=0
	           parziale=`dbmftc2 CAI_VAR_DB ${gerarchia}:${tipo_alarm} 2>> /dev/null`
                   if [ "${parziale}" != "" ]
		   then
		      contenuto="${parziale}"
		      counter=`echo ${parziale} | cut -f1 -d: `
		   fi
	        fi
	        identificativo="`echo ${gerarchia} | tr ':' ','` ${tipo_alarm}"
	        echo "#" >> ${pagina}.scr
	        echo "#" Updating ${pagina} for hierarchy ${gerarchia} >> ${pagina}.scr
	        echo "#" >> ${pagina}.scr
	        echo widgetclass=CaiVar >> ${pagina}.scr
	        echo hasattrib=objectTag >> ${pagina}.scr
	        echo value=${identificativo} >> ${pagina}.scr
	        jj=1
	        array_var=`echo ${contenuto} | cut -f2-12 -d:`
	        while [ ${jj} -le ${counter} ]
	        do
	           echo attrib=input${jj} >> ${pagina}.scr
	           echo value="`echo ${array_var} | cut -f${jj} -d:` SUPERVIS" | sed -e 's/$P/$W/' >> ${pagina}.scr
	           echo newattrib=input${jj} >> ${pagina}.scr
	           echo value="`echo ${array_var} | cut -f${jj} -d:` SUPERVIS" | sed -e 's/$P/$W/' >> ${pagina}.scr
	           let jj=${jj}+1
	        done   
	    done
	done
	if [ -s ${pagina}.scr ]
	then
	   $PAGMOD -p ${pagina} -s ${pagina}.scr
	   mv ${pagina} ${pagina}.save
	   mv ${pagina}.mod ${pagina}
	   echo "Plant display ${pagina}\telaborated"
	   echo "${pagina}" >> $KLOG/kMakeCaiVar.log
#	else
#	   echo "Info: ${pagina}\twithout cai_var"
	fi
done  

