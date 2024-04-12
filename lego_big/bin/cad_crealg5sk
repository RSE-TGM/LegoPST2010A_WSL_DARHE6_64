#!/bin/ksh
#
#  Script:                      cad_crealg5sk.sh
#  Subsystem:           1
#  %version:            4 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Fri Sep 19 15:59:10 1997 %

#!/bin/ksh
if [ "$1" != t -a "$1" != T ]
then
if [ "$LEGOCAD_EMM" = YES  ]
then
make -f $LEGO_BIN/cad_maketask proc/f04.dat  CAD_LIB_MODULI="`cad_f012lis`"
else
make -f $LEGO_BIN/cad_maketask proc/f04.dat
fi
fi
if [ $# -eq 0 ]
then 
make -f $LEGO_BIN/cad_maketask lg5sk CAD_LIB_MODULI="../libut_reg/schemi_reg.a ../libut/modulilib.a ../libut_reg/libreg/reglib.a" 
elif [ $1 = r -o $1 = R ]
then
make -f $LEGO_BIN/cad_maketask rg5sk CAD_LIB_MODULI="../libut_reg/schemi_reg.a ../libut_reg/libreg/reglib.a" 
elif [ $1 = l -o $1 = L ]
then
make -f $LEGO_BIN/cad_maketask rg5sk CAD_LIB_MODULI="./proc/schemi_reg.a ../libut_reg/libreg/reglib.a" LG1_FLAGS="L" CAD_LISTA_SCHEMI="$LEGOMMI_PAG/proc/lista_schemi.dat"
elif [ \( $1 = p -o $1 = P \) -a \( "$LEGOCAD_EMM" != YES \) ]
then
make -f $LEGO_BIN/cad_maketask lg5sk CAD_LIB_MODULI="../libut/modulilib.a"
elif [ $1 = t -o $1 = T ]
then
make -q -f $LEGO_BIN/cad_maketask lg5sk CAD_LIB_MODULI="../libut/modulilib.a"
elif [ \( $1 = p -o $1 = P \) -a \( "$LEGOCAD_EMM" = YES \) ]
then
CAD_LIB_MODULI="`cad_f012lis`"
if [ $? -eq 0 ]
then
make -f $LEGO_BIN/cad_maketask lg5sk CAD_LIB_MODULI="`cad_f012lis`"
ERROR=$?
if [ $ERROR -ne 0 ]
then
 echo errore make $ERROR
fi
else
 echo errore cad_f012lis $?
fi
fi
