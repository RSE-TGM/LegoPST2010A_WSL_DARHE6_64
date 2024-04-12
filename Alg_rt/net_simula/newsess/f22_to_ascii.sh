#!/bin/ksh
#
#  Script:			f22_to_ascii.sh
#  Instance:		1
#  %version:		1 %
#  Description:		
#  %created_by:		lomgr %
#  %date_created:	Tue Jun  1 14:25:05 1999 %

if [ "$#" != 3 ]
then
echo "Programma di conversione di un file tipo f22circ in un file ascii"
echo " "
echo "Usage: f22_to_ascii f22circ_di_input Tmin Tmax"
echo " "
echo "ATTENZIONE f22circ_di_input verrà copiato sul file f22circ.dat eventualmente esistente"
echo "           Dal file f22circ_di_input verrà prodotto il file f22circ_di_input.asc"
exit 1
fi
if [ -f "$1" ]
then
    print "Il file ""$1"" verrà copiato sul file f22circ.dat. Continuo? [Yes\No]"
    read answer
    case $answer in
    Yes|yes|Y|y|Si|S|si|s)
   cp "$1" f22circ.dat
   echo nsession "$2" "$3" 4
   echo " Allora procedo"
   nsession "$2" "$3" 4 .
   mv f22circ.asc ${1}.asc    
    continue;;
    No|no|N|n)
   echo "Ciao"
    break;;
    esac   
else
   echo Error: file "$1" doesn\'t exist
fi
