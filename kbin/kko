#!/bin/ksh
#
kAddStatistic kks
cd $LEGOCAD_USER/legocad
echo "$*" > $TMPDIR/kkshoriz.tmp
tr '[:space:]' '[\n*]' < $TMPDIR/kkshoriz.tmp > $TMPDIR/kkslower.tmp
tr '[:lower:]' '[:upper:]' < $TMPDIR/kkslower.tmp > $TMPDIR/kksupper.tmp
grep -f $TMPDIR/kksupper.tmp ./*/KKS.list | sed "s/KKS.list:/ /g"
