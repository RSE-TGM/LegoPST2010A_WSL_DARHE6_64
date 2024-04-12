#!/bin/ksh
#
grep "*tagPag:" ????.pag | \
sed "s/.pag:/ /g" | \
awk '{ print $1, $3 }'| \
sort -k2 | \
cut -c 1-10 >> $KINFOTAG/TAG.list
