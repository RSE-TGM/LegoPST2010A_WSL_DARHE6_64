#!/bin/sh
#
#  Script:			creascada.sh
#  Instance:		1
#  %version:		2 %
#  Description:		
#  %created_by:		lomgr %
#  %date_created:	Mon Oct 24 18:22:41 2005 %

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
sim=~/sked/$1
if [ ! -d ${sim} ]
then
  echo "\n Non esiste la directory ${sim} !! \n\a"
  exit
fi
cd ${sim}
if [ "$2" = "" ]
then
  if [ ! -d ${sim}/scada ]
  then
    echo "\n Non esiste la directory ${sim}/scada !! Usare l'opzione -startinformix \n\a"
    exit
  fi
  echo "Creo i file operativi senza scaricare il database..."
  para=""
elif [ "$2" = "-startinformix" ]
then
  echo "Creo i file operativi ricaricando il database..."
  para=$2
  rm -rf scada
  mkdir scada
  mkdir scada/fileop
  mkdir scada/rtf
  mkdir scada/start_txt
  mkdir scada/txt
else
  echo "\n uso: creascada directory_simulatore [-startinformix] \n\a"
  exit
fi
start_txt=${sim}/scada/start_txt
fileop=${sim}/scada/fileop
txt=${sim}/scada/txt
rtf=${sim}/scada/rtf
export ALDB_USED=puerccpts
cd scada
if [ ! -d ${sim}/scada/txt ]
then
   echo "\n Non esiste la directory ${sim}/scada/txt la creo \n\a"
   mkdir ${sim}/scada/txt
fi
if [ ! -d ${sim}/scada/rtf ]
then
   echo "\n Non esiste la directory ${sim}/scada/rtf la creo \n\a"
   mkdir ${sim}/scada/rtf
fi
if [ ! -d ${sim}/scada/fileop ]
then
   echo "\n Non esiste la directory ${sim}/scada/fileop la creo \n\a"
   mkdir ${sim}/scada/fileop
fi
PointInst $start_txt $txt $rtf $sim -noinformix ${para}
ExpRtf $txt $rtf -noinformix
ToRtf $rtf $fileop -noinformix
cd ${sim}
ln -fs $fileop/fnomi.rtf

