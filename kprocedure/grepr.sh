#!/bin/ksh
#
find . -print | while read file
do
	grep -l $1 $file
done
