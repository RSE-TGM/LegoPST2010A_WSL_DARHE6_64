/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
	setdata.c

	La funzione setta la data del PC	uguale alla data fornita
   al task Acqui attraverso il messaggio S_MSCLOCK

	Parametri
   
   S_MCLOCK *  messaggio

   16 Settembre 1995
*/
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <dos.h>

#include "comunic.inc"
#include "g2comdb.inc"
#include "mesqueue.h"
#include "messcada.inc"
#include "pscserr.inc"
#include "diagnodi.inc"
#include "diagnoan.inc"


setdata (mess)
S_MCLOCK* mess;
{
	struct tm timet, *ptime;
   time_t orapc;
   struct dosdate_t date;
   struct dostime_t time;

   timet.tm_mday=mess->gio;
   timet.tm_mon=mess->mese-1;
   if(mess->anno < 90) timet.tm_year=mess->anno+100;  // anni da 2000
   else timet.tm_year=mess->anno;
   timet.tm_hour=mess->ore;
   timet.tm_min=mess->min;
   timet.tm_sec=mess->sec;
   timet.tm_wday=0;
   timet.tm_yday=0;
   timet.tm_isdst=-1;

	//trasformo la struttura tpc in tipo time_t
	orapc=mktime(&timet);
   
   // aggiungo ora grenwich
   orapc=orapc+3600;

   ptime=localtime(&orapc);

   date.day=ptime->tm_mday;
   date.month=ptime->tm_mon+1;
   date.year=ptime->tm_year+1900;
   date.dayofweek=0;
   if(_dos_setdate(&date))
      	pscserr(ERR_TASK,TASK_ACQUI,ROU_DATE,0,SYS_CONT);
   time.hour=ptime->tm_hour;
   time.minute=ptime->tm_min;
   time.second=ptime->tm_sec;
   time.hsecond=0;
   if(_dos_settime(&time))
        pscserr(ERR_TASK,TASK_ACQUI,ROU_TIME,0,SYS_CONT);
      return;
}   
 
