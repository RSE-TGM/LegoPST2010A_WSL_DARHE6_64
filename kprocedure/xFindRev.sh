#!/bin/ksh
#
grep w.labelText: ????.pag | grep 'Rev' | \
sed "s/.pag:/ /g" | awk '{ print $1, $4 }'| \
sort -k2 | cut -c 1-10 >> $KINFOTAG/REV.list
