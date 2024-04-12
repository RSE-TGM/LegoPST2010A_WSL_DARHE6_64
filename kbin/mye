#!/bin/ksh
#
if [ -x ${KSOURCE}/legocad/libut_bin/asedit ]
then
asedit $1 $2 $3 $4 $5 $6 $7 $8 &
elif [ -x /usr/dt/bin/dtpad ]
then
/usr/dt/bin/dtpad -statusLine $1 $2 $3 $4 $5 $6 $7 $8 &
else
echo "Editor not found"
fi
