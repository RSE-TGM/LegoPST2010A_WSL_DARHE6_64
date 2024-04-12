#!/bin/sh
#
#  Script:			superscape.sh
#  Instance:		1
#  %version:		1 %
#  Description:		
#  %created_by:		lomgr %
#  %date_created:	Tue May  8 13:40:34 2001 %

if [ "$#" != 1 ]
then
echo "Usage: $0 URL_name"
exit 1
fi
echo $1
netscape -remote "openURL(${1})"
if [ "$?" != 0 ]
then
netscape $1 &
fi
