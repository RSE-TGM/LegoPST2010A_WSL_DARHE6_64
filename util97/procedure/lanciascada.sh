#!/bin/sh
#
#  Script %name:	lanciascada.sh %
#  Instance:		1
#  %version:		1 %
#  Description:		
#  %created_by:		lomgr %
#  %date_created:	Mon Oct 24 18:18:51 2005 %

#############################################################################
#
#############################################################################
#
# controllo dei parametri passati
#
if [ "$1" = "" ]
then
  echo "\n uso: creascada directory_simulatore [-startinformix] \n\a"
  exit
fi
fileop=~/sked/$1/scada/fileop
if [ ! -d ${fileop} ]
then
  echo "\n Non esiste la directory ${fileop} !! \n\a"
  exit
fi
cd ${fileop}
scada /FAT /AFRV /M4 &

