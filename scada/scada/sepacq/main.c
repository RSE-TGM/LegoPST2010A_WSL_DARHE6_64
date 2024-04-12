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
	datasepa.c

	La funzione setta la data del PC	uguale alla data della SEPA
	se questa Š accettabile.

	Parametri
   
	timepc	 puntatore alla struttura contenente la data del PC

	timesepa	 puntatore alla struttura contenente la data della SEPA

	Ritorno

	0	se la data del PC non Š stata cambiata
	1	se la data del PC Š stata settata pari a quella della SEPA

   16 Febbraio 1995 - R.L.
*/
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

datasepa();

#define ungiorno 86400	//un giorno espresso in secondi
#define unminuto 60	//un minuto espresso in secondi


void main(void)
{
	struct tm *timepc;
	struct tm timesepa;
	struct tm apptimepc;

	short ret;
	time_t orapc;
	short var1,var2,var3,var4,var5,var6;

	time (&orapc); //recupero l'ora in secondi
	//converto l'ora nella struttura tm
	timepc=localtime (&orapc);
	printf ("La data e ora del PC sono: %s\n", asctime (timepc));
	
	//inserisci la data e ora Sepa
	printf ("Inserisci data e ora Sepa\n");

	printf("\nGiorno [1-31]:");
	scanf ("%d",&var1);
	timesepa.tm_mday=var1;
	
	printf("\nMese [0-11]:");
	scanf ("%d",&var2);
	timesepa.tm_mon=var2;
	
	printf("\nAnno [dal 1900]:");
	scanf ("%d",&var3);
	timesepa.tm_year=var3;

	printf("\nOra [0-23]:");
	scanf ("%d",&var4);
	timesepa.tm_hour=var4;

	printf("\nMinuti [0-59]:");
	scanf ("%d",&var5);
	timesepa.tm_min=var5;

	printf("\nSecondi [0-59]:");
	scanf ("%d",&var6);
	timesepa.tm_sec=var6;
	
   apptimepc=*timepc;
	ret=datasepa (&apptimepc,&timesepa);
	printf ("\nprimo ret=%d\n",ret);
	
	ret=datasepa (&apptimepc,&timesepa);
	printf ("secondo ret=%d\n",ret);

	ret=datasepa (&apptimepc,&timesepa);
	printf ("terzo ret=%d",ret);
	
	printf ("\nLa data e ora del PC sono: %s",asctime(&apptimepc));
}

short datasepa (struct tm *tpc,struct tm *tsepa)
{
	static struct tm timetemp;

	time_t orapc,orasepa,oratemp;
	static short retry=-1;	
	double diff,adiff;
	short sec;

	//trasformo la struttura tpc in tipo time_t
	orapc=mktime(tpc);
	printf ("PC: %s\n", ctime(&orapc));

	//trasformo la struttura tsepa in tipo time_t
	orasepa=mktime(tsepa);
	printf ("SEPA: %s\n", ctime(&orasepa));
	printf ("\nInserisci di quanto varia l'ora SEPA [in secondi]:");
	scanf ("%d",&sec);
	orasepa=orasepa+sec;

	//converto l'ora nella struttura tm
	tsepa=localtime (&orasepa);
	printf ("SEPA: %s\n", asctime (tsepa));

	diff=difftime(orapc,orasepa);
	adiff=fabs(diff);
	printf ("diff. fra PC e SEPA %f secondi\n",adiff);

	//se la differenza Š maggiore di un giorno
	if (adiff > ungiorno)
	{
		printf ("diff fra PC e SEPA > di un giorno\n");
		retry=-1;
		return (0);
	}
	//se la differenza Š compresa nel minuto
	if (adiff<= unminuto)
	{
		//setto la data del PC come quella della Sepa
		printf ("diff fra PC e SEPA compresa nel minuto\n");
		tpc=tsepa;
		retry=-1;
		return (1);
	}

	if (retry==-1)	//se Š la prima volta
	{
		timetemp=*tsepa;	//salvo in data temporanea 
      printf ("\nora temporanea %s",asctime(&timetemp));
		retry++;
		return (0);
	}

	if (retry!=-1)	//se non Š la prima volta
	{
		oratemp=mktime(&timetemp);
		diff=difftime(oratemp,orasepa);
		adiff=fabs(diff);

		printf ("diff. fra TEMP e SEPA %f secondi\n",adiff);
		//se la differenza Š compresa nel minuto
		if (adiff<=unminuto)
		{
			retry++;
			timetemp=*tsepa;	//salvo in data temporanea
         printf ("\nora temporanea %s",asctime(&timetemp));
			if (retry==2)	   //terza volta
			{
				tpc=tsepa;
				retry=0;
				return (1);
			}
		}
		else
		{
			retry=0;
			timetemp=*tsepa;
         printf ("\nora temporanea %s",asctime(&timetemp));
		}
	}
	return (0);
}
 
