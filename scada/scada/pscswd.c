/**********************************************************************
*
*       C Source:               pscswd.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Mon Aug  4 13:58:47 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: pscswd.c-4.1.1 %  (%full_filespec: pscswd.c-4.1.1:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*    
   PSCSWD.C
   
   task watch dog software: decrementa il contatore di watch-dog
   (il valore del contatore e' settato all'attivazione del task in esecuzione)
  
   14/07/92   -  GM.Furlan  -  Rel. 2.00
                 Nuova versione per STOP-PC

	20 Aprile Fc
	Nel caso di star di Sepa ogni minuto viene chiamata la routine
	seprich per ora e richiesta globale digitali
*/

#include <osf1.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>
#include <bios.h>

#include "dconf.inc"
#include "diagnoan.inc"
#include "g2comdb.inc"
#include "pscserr.inc"                   
#include "taskwd.inc"
#include "pscs.cfg"
#include "comunic.inc"
#include "mesest.inc"                   
#if defined ENEL_SIM
#include "./simacq/simana.inc"
#endif

#define GE	31
#define FE  28
#define MR	31
#define AP  30
#define MG  31
#define GI	30
#define LU	31
#define AG  31
#define SE	30
#define OT  31
#define NO  30
#define DI	31

	short coefmese[12]={ 0, GE, GE+FE, GE+FE+MR, GE+FE+MR+AP, GE+FE+MR+AP+MG,
			GE+FE+MR+AP+MG+GI, GE+FE+MR+AP+MG+GI+LU, GE+FE+MR+AP+MG+GI+LU+AG,
			GE+FE+MR+AP+MG+GI+LU+AG+SE, GE+FE+MR+AP+MG+GI+LU+AG+SE+OT,
			GE+FE+MR+AP+MG+GI+LU+AG+SE+OT+NO};
   short giomese[12]={ GE, FE, MR, AP, MG, GI, LU, AG, SE, OT, NO, DI};

extern DB_HEADER h_db;
char leggi_data=1;
char leggi_data_sim=1;

#if defined ENEL_SIM
extern int ora_simulatore;
extern int minuti_simulatore;
extern int secondi_simulatore;
extern int milli_simulatore;
extern int giorno_simulatore;
extern int mese_simulatore;
extern int anno_simulatore;
extern float tempo_simulatore;
#endif

pscswd()
{
   short i;

#if defined ENEL_SIM
/*
	nel caso di funzionamento con il simulatore viene settata
	la data salvata nei punti di diagnostica del simulatore
*/
/*printf("DEBUG PSCSWD !!!!\n");*/
    ora_simulatore = dbadv[db_ora_sim];
    minuti_simulatore = dbadv[db_minuti_sim];
/*printf("secondi_simulatore=%d\n",secondi_simulatore);*/
    secondi_simulatore = dbadv[db_secondi_sim];
/*printf("secondi_simulatore dopo=%d\n",secondi_simulatore);*/
#ifdef PROVA
    milli_simulatore = ;
#endif
    giorno_simulatore = dbadv[db_giorno_sim];
    mese_simulatore = dbadv[db_mese_sim];
    anno_simulatore = dbadv[db_anno_sim];
    tempo_simulatore = dbadv[dbtemp_sim];
#endif

#if defined OSF1 || defined LINUX
   _time();                  // legge ora attuale
#else
   time();                  // legge ora attuale
#endif
   for (i=0;i<n_task;i++)   // per tutti i task da controllare
      {
      if (wd[i].task_per==TPERIODICO)  // solo per i periodici
         {
         if (wd[i].task_st!=TRUN) continue; // task fermo: non si considera wd
         wd[i].cont--; 
         //MAX PER DEBUG  if (wd[i].cont==0) 
         //MAX PER DEBUG     pscserr(ERR_TASK,TASK_WD,ROU_PSCSWD,i,SYS_HALT);
         }
      }
#if defined OSF1 || defined LINUX
//dprintf(2,"pscswd secondi = ",dbadv[db_secondi]);
#endif
   ter();
}

// time.c
//
// Legge l'ora corrente dai counters in area BIOS
// settando le opportune variabili in data base
// se rileva un cambiamento della data, la reinizializza
// ----------------------------------------------------
//
/* 16/11/92  -  GM.Furlan  
       Nel caso di simulatore, tratta l'ora di simulazione */

#if !defined OSF1 && !defined LINUX
time() 
{
   struct   bios_date   {
      short day;
      short month;
      short year;
      short dayofweek;
      };
//   struct bios_date data;
   struct dosdate_t data;
   double   temp ;
	float	   sav_min;
   long     timeval;
   long     ore1,minuti1,secondi1;
   unsigned timer_ofl;
   struct cmos_time{
      short hour;
      short minute;
      short second;
      };
   struct cmos_time tempocmos;

#define cost_ora		1.0/(1193180.0/65536.0)		 		// durata singolo tick in secondi
#define recover_tick	176.0									 	// n. di ticks (55 ms ca) correzione giornata
#define recover_msec	(176.0/(24.0*3600.0))*cost_ora  	// n. di ms correzione al secondo


   timer_ofl=_bios_timeofday(_TIME_GETCLOCK,&timeval);

	temp = (float)timeval * cost_ora ;                 // secondi totali
	
	dbadv[db_ora]= (float)((short)(temp/3600.0));  		// setto ora
	temp=temp-dbadv[db_ora]*3600.0; 					  		// secondi + minuti
	sav_min=dbadv[db_minuti];
   dbadv[db_minuti]= (float)((short)(temp/60.)); 		// setto minuti
   dbadv[db_secondi]= temp-dbadv[db_minuti]*60.; 		// setto secondi

/*
   occorre riallineare il contatore BIOS con l'orologio
   del calendar clock
*/
#if defined (STAR_SEPA)
#else
   if((short)dbadv[db_secondi] == 35) 
      {
      _cmos_gettime(&tempocmos);                     // lettura orologio CMOS
	   ore1 = (long)(tempocmos.hour) * 3600;           // conversione a ticks
	   minuti1 = (long)(tempocmos.minute) * 60;
	   secondi1 = (long)(tempocmos.second) + minuti1 + ore1; 
	   timeval = secondi1 * 18.2065;
	   _bios_timeofday(_TIME_SETCLOCK,&timeval);      // scrittura counter BIOS
      }
#endif

	if ( timer_ofl || leggi_data || (sav_min != dbadv[db_minuti]))
	   {											// se data variata o inesistente
		_bios_getdate(&data);
      if (dbadv[db_giorno]!=(float)data.day || dbadv[db_mese]!=(float)data.month ||(float)dbadv[db_anno]!=data.year)
         _dos_setdate(&data);
		dbadv[db_anno]=data.year;
		dbadv[db_mese]=data.month;
		dbadv[db_giorno]=data.day;
		dbadv[db_numgio]=coefmese[data.month-1]+data.day;
		dbadv[db_gioset]=(float) ((((data.year-1992)*365+    // 0=dom..6=sab
         (data.year-1992)/4+                               
         (short)dbadv[db_numgio])+3)%7);
		if(data.month>2 && !(data.year%4)) 
         dbadv[db_numgio]++;
		dbadv[db_numset]=((short)(dbadv[db_numgio])/7)+1;
		leggi_data= 0;
	   }
#if defined (STAR_SEPA)         
	if(sav_min != dbadv[db_minuti]) 
      seprich();
#endif

#if defined (RCE_LAC)         
   aggtime(RUNMODE);
#endif

 return(0);
}
#else
_time()
{
int ora,minuti,secondi,milli;
int giorno,mese,anno,gio_set,gio_anno;
int app;

if(GetOra(&ora,&minuti,&secondi,&milli)!=1)
	printf("Errore GetOra\n");
if(GetData(&giorno,&mese,&anno,&gio_set,&gio_anno)!=1)
	printf("Errore GetData\n");
dbadv[db_ora]= (float)ora;  		// setto ora
dbadv[db_minuti]= (float)minuti; 		// setto minuti
dbadv[db_secondi]= (float)secondi+(float)milli/1000.0; 		// setto secondi
dbadv[db_anno]=anno;
dbadv[db_mese]=mese;
dbadv[db_giorno]=giorno;
dbadv[db_numgio]=gio_anno;
dbadv[db_gioset]=gio_set;
dbadv[db_numset]=((short)(dbadv[db_numgio])/7)+1;
}
#endif
