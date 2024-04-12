#!/bin/ksh
#
#  Script:                      cad_crealg1.sh
#  Subsystem:           1
#  %version:            11 %
#  Description:
#  %created_by:         jurij %
#  %date_created:       Tue Mar 27 17:43:40 2007 %

#!/bin/ksh
if [ $# -eq 0 ]
then 
make -f $LEGO_BIN/cad_maketask lg1 CAD_LIB_MODULI="../libut_reg/schemi_reg.a ../libut/modulilib.a ../libut_reg/libreg/reglib.a" 
elif [ $1 = l -o $1 = L ]
then
make -f $LEGO_BIN/cad_maketask lg1 CAD_LIB_MODULI="./proc/schemi_reg.a ../libut_reg/libreg/reglib.a"
elif [ $1 = r -o $1 = R ]
then
make -f $LEGO_BIN/cad_maketask lg1 CAD_LIB_MODULI="../libut_reg/schemi_reg.a ../libut_reg/libreg/reglib.a" 
elif [ $1 = p -o $1 = P ]
then
make -f $LEGO_BIN/cad_maketask lg1 CAD_LIB_MODULI="../libut/modulilib.a ../libut/auxlegolib.a"
elif [ $1 = c -o $1 = C ]
then
  $LG_TOOLS/pag2f01 `basename $PWD`".top"
  if [ $? -ne 0 ]
  then
  return 34
  fi
  make -f $LEGO_BIN/cad_maketask lg1 CAD_LIB_MODULI="../libut/modulilib.a ../libut/auxlegolib.a"
  if [ $? -ne 0 ]
  then
  return 35
  fi
  return 0
elif [ $1 = t -o $1 = T ]
then
  make -q -f $LEGO_BIN/cad_maketask lg1 CAD_LIB_MODULI="../libut/modulilib.a"
fi
