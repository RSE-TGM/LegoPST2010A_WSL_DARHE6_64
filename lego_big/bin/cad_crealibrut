#!/bin/ksh
#
#  Script:                      cad_crealibrut.sh
#  Subsystem:           1
#  %version:            3 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Wed Feb 19 16:58:30 1997 %

#!/bin/ksh
if [ $# -eq 0 ]
then 
make -f $LEGO_BIN/cad_maketask lib CAD_LIB_MODULI="../libut_reg/schemi_reg.a ../libut/modulilib.a ../libut_reg/libreg/reglib.a" 
elif [ $1 = l -o $1 = L ]
then
make -f $LEGO_BIN/cad_maketask lib CAD_LIB_MODULI="./proc/schemi_reg.a ../libut_reg/libreg/reglib.a"
elif [ $1 = r -o $1 = R ]
then
make -f $LEGO_BIN/cad_maketask lib CAD_LIB_MODULI="../libut_reg/schemi_reg.a ../libut_reg/libreg/reglib.a" 
elif [ $1 = p -o $1 = P ]
then
make -f $LEGO_BIN/cad_maketask lib CAD_LIB_MODULI="../libut/modulilib.a"
elif [ $1 = t -o $1 = T ]
then
make -q -f $LEGO_BIN/cad_maketask ../libut/modulilib.a
fi
