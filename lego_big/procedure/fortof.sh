#!/bin/ksh
#
#  Script:                      fortof.sh
#  Subsystem:           1
#  %version:            2 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Wed Feb 19 17:00:06 1997 %

echo "     ------------------------------------------------"
echo "rename dei file *.for in *.f "
echo "     ------------------------------------------------"
# Elimino i files .for che sono identici al .f omonimo.
ls -1 | awk '/\.for$/{print "diff "$1" "substr($1,1,(length($1)-2))">/dev/null && rm "$1" "}' > esecom
csh esecom
rm esecom
# Rinomino i files .for in  .f
ls -1 | awk '/\.for$/{print "mv "$1" "substr($1,1,(length($1)-2))" "}' > esecom
csh esecom
rm esecom
echo " "
echo "                  --------- OK ----------"
echo " "
