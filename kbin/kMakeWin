#!/bin/ksh
#
cd $KWIN
punt2canc.sh
rm *.tab
ls N_win*.list |
cut -f1 -d. |
while read file
do
  echo "Generazione O.W. ${file}..."
  mkstaz ${file}
  mkdtw  ${file}
done
