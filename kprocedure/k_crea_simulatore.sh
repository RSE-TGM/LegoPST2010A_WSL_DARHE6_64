#!/bin/ksh
#
#!/bin/sh
#
#  Script:			k_crea_simulatore.sh
#  Instance:		1
#  %version:		2 %
#  Description:		
#  %created_by:		lomgr %
#  %date_created:	Thu Feb  3 12:17:10 2005 %

if [ "$KSIM" ]
then
#
   if [ ! -d $KSIM ]
   then
      mkdir  $KSIM
      echo Directory $KSIM created
   fi
#
   if [ ! -d $KSIM/databases ]
   then
      mkdir  $KSIM/databases
      echo Directory $KSIM/databases created
   fi
#
   if [ ! -d $KSIM/export ]
   then
      mkdir  $KSIM/export
      echo Directory $KSIM/export created
   fi
#
   if [ ! -d $KSIM/globpages ]
   then
      mkdir  $KSIM/globpages
      echo Directory $KSIM/globpages created
   fi
#
   if [ ! -d $KSIM/globpages_a ]
   then
      mkdir  $KSIM/globpages_a
      echo Directory $KSIM/globpages_a created
   fi
#
   if [ ! -d $KSIM/globpages_b ]
   then
      mkdir  $KSIM/globpages_b
      echo Directory $KSIM/globpages_b created
   fi
#
   if [ ! -d $KSIM/globpages_c ]
   then
      mkdir  $KSIM/globpages_c
      echo Directory $KSIM/globpages_c created
   fi
#
   if [ ! -d $KSIM/globpages_d ]
   then
      mkdir  $KSIM/globpages_d
      echo Directory $KSIM/globpages_d created
   fi
#
   if [ ! -d $KSIM/log ]
   then
      mkdir  $KSIM/log
      echo Directory $KSIM/log created
   fi
#
   if [ ! -d $KSIM/o_win ]
   then
      mkdir  $KSIM/o_win
      echo Directory $KSIM/o_win created
   fi
#
   if [ ! -d $KSIM/plant_display ]
   then
      mkdir  $KSIM/plant_display
      echo Directory $KSIM/plant_display created
   fi
#
   if [ ! -d $KSIM/scada ]
   then
      mkdir  $KSIM/scada
      echo Directory $KSIM/scada created
   fi
#
   if [ ! -d $KSIM/scada/start_txt ]
   then
      mkdir  $KSIM/scada/start_txt
      echo Directory $KSIM/scada/start_txt created
   fi
#
   if [ ! -d $KSIM/scada/fileop ]
   then
      mkdir  $KSIM/scada/fileop
      echo Directory $KSIM/scada/fileop created
   fi
#
   if [ ! -d $KSIM/scada/txt ]
   then
      mkdir  $KSIM/scada/txt
      echo Directory $KSIM/scada/txt created
   fi
#
   if [ ! -d $KSIM/scada/rtf ]
   then
      mkdir  $KSIM/scada/rtf
      echo Directory $KSIM/scada/rtf created
   fi
#
   if [ ! -d $KSIM/statistic ]
   then
      mkdir  $KSIM/statistic
      echo Directory $KSIM/statistic created
   fi
#
   if [ ! -d $KSIM/status ]
   then
      mkdir  $KSIM/status
      echo Directory $KSIM/status created
   fi
#
   if [ ! -d $KSIM/tmp ]
   then
      mkdir  $KSIM/tmp
      echo Directory $KSIM/tmp created
   fi
#
else
        echo  k_crea_simulatore usage: Set KSIM environment variable
fi

