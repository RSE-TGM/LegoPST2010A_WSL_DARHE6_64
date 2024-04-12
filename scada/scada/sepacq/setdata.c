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

	La funzione setta la data del PC	uguale alla data della SEPA
	se questa Š accettabile.

	Parametri
   
	timepc	 puntatore alla struttura contenente la data del PC

	timesepa	 puntatore alla struttura contenente la data SEPA

   16 Febbraio 1995 - R.L.
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


#define ungiorno 86400	//un giorno espresso in secondi
#define unminuto 60	//un minuto espresso in secondi

setdata (struct tm *tpc,struct tm *tsepa)
{
	static struct tm timetemp;

	time_t orapc,orasepa,oratemp;
	static short retry=-1;	
	double diff,adiff;

	//trasformo la struttura tpc in tipo time_t
	orapc=mktime(tpc);
//	printf ("PC: %s\n", ctime(&orapc));

	//trasformo la struttura tsepa in tipo time_t
	orasepa=mktime(tsepa);
//	printf ("SEPA: %s\n", ctime(&orasepa));

	diff=difftime(orapc,orasepa);
	adiff=fabs(diff);
//	printf ("diff. fra PC e SEPA %f secondi\n",adiff);

	//se la differenza Š maggiore di un giorno
	if (adiff > ungiorno)
	{
//		printf ("diff fra PC e SEPA > di un giorno\n");
		retry=-1;
		return;
	}
	//se la differenza Š compresa nel minuto
	if (adiff<= unminuto)
	{
		//setto la data del PC come quella della Sepa
//		printf ("diff fra PC e SEPA compresa nel minuto\n");
      settapc (tsepa);
		retry=-1;
		return;
	}

	if (retry==-1)	//se Š la prima volta
	{
		timetemp=*tsepa;	//salvo in data temporanea 
		retry++;
		return;
	}

	oratemp=mktime(&timetemp);
	diff=difftime(oratemp,orasepa);
	adiff=fabs(diff);

//	printf ("diff. fra TEMP e SEPA %f secondi\n",adiff);
	//se la differenza Š compresa nel minuto
	if (adiff<=unminuto*2)
	{
		retry++;
		timetemp=*tsepa;	//salvo in data temporanea
		if (retry==2)	   //terza volta
		{
         settapc (tsepa);
			retry=-1;
			return;
		}
	}
	else
	{
		retry=0;
		timetemp=*tsepa;
	}
	return ;
}

settapc (struct tm* tsepa)
{
   struct dosdate_t date;
   struct dostime_t time;

   if(dbadv[db_giorno]!=tsepa->tm_mday)	// giorno diverso ?
   {
      date.day=tsepa->tm_mday;
      date.month=tsepa->tm_mon+1;
      date.year=tsepa->tm_year+1900;
      date.dayofweek=0;
      if(_dos_setdate(&date))
         	pscserr(ERR_TASK,TASK_ACQUI,ROU_DATE,0,SYS_CONT);
   }
   time.hour=tsepa->tm_hour;
   time.minute=tsepa->tm_min;
   time.second=tsepa->tm_sec;
   time.hsecond=0;
   if(_dos_settime(&time))
        pscserr(ERR_TASK,TASK_ACQUI,ROU_TIME,0,SYS_CONT);
      return;
}   
 
