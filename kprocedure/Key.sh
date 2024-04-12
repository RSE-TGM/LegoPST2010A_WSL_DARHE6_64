#!/bin/ksh
#
kAddStatistic Key
echo ${star2}
echo "Find key in topolgic files :"
echo
cd $LEGOCAD_USER/legocad
echo "$*" > $TMPDIR/Keyhoriz.tmp
tr '[:space:]' '[\n*]' < $TMPDIR/Keyhoriz.tmp > $TMPDIR/Keylower.tmp
tr '[:lower:]' '[:upper:]' < $TMPDIR/Keylower.tmp > $TMPDIR/Keyupper.tmp
grep -f $TMPDIR/Keyupper.tmp */f01.dat | sed "s/f01.dat:/ :/g" | tr -d '.' | tr -d '/' 
grep -f $TMPDIR/Keyupper.tmp g*/proc/n04.dat | tr -d '/' | sed "s/procn04.dat:/ :/g" 
echo ${star2}
