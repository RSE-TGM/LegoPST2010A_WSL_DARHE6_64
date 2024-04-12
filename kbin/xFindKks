#!/bin/ksh
#
grep w.labelText: ????.pag | \
sed "s/.pag:/ /g" | awk '{ print $1, $3, $4, $5, $6, $7 }'| \
sort -k2 | cut -c 1-30 >> $KINFOTAG/KKS.list
