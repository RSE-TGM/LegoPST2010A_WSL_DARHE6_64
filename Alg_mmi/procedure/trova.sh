#!/bin/sh
#
#  Script:			trova.sh
#  Instance:		1
#  %version:		2 %
#  Description:		
#  %created_by:		famgr %
#  %date_created:	Tue May  6 10:06:47 1997 %


FILE_EXT="${1}"
STRING=$2
echo $STRING

if [  ! "${FILE_EXT}" -o ! "${STRING}" ]
then
        echo "Sintassi: sh trova <fileextension> <string to search>"
        exit
fi
echo "Searching in *.${FILE_EXT}"
find . -name "*.${FILE_EXT}" -exec grep "${STRING}" {} \; -print

