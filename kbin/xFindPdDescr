#!/bin/ksh
#
grep top_descrizione: M_S*.pag | \
sed "s/.pag:/ /g" | awk '{ print $1, $3, $4, $5, $6, $7 }'| \
sort -k2 | cut -c 1-50 >> $KINFOTAG/PDDESCR.list
