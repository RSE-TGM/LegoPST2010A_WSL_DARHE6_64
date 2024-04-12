#!/bin/ksh
#
#!/bin/sh
#
#  Script:			k_crea_cassaforte.sh
#  Instance:		1
#  %version:		2 %
#  Description:		
#  %created_by:		lomgr %
#  %date_created:	Thu Feb  3 12:17:09 2005 %

if [ "$KCASSAFORTE" ]
then
   if [ ! -d $KCASSAFORTE ]
   then
      mkdir  $KCASSAFORTE
      echo Directory $KCASSAFORTE created
   fi
#
   if [ ! -d $KCASSAFORTE/curve ]
   then
      mkdir  $KCASSAFORTE/curve
      echo Directory $KCASSAFORTE/curve created
   fi
#
   if [ ! -d $KCASSAFORTE/plant_display ]
   then
      mkdir  $KCASSAFORTE/plant_display
      echo Directory $KCASSAFORTE/plant_display created
   fi
#
   if [ ! -d $KCASSAFORTE/scada ]
   then
      mkdir  $KCASSAFORTE/scada
      echo Directory $KCASSAFORTE/scada created
   fi
#
else
	echo k_crea_cassaforte usage: Set KCASSAFORTE environment variable
fi
