#!/bin/ksh
#
kAddStatistic S01
echo ${star2}
echo "Find key S01 :"
echo
cd $KSIM
echo "$*" > $TMPDIR/S01horiz.tmp
tr '[:space:]' '[\n*]' < $TMPDIR/S01horiz.tmp > $TMPDIR/S01lower.tmp
tr '[:lower:]' '[:upper:]' < $TMPDIR/S01lower.tmp > $TMPDIR/S01upper.tmp
grep -hf $TMPDIR/S01upper.tmp S01 
echo ${star2}
