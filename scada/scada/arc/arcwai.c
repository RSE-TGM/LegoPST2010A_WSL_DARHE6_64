/**********************************************************************
*
*       C Source:               arcwai.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Oct 31 14:15:15 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: arcwai.c-3 %  (%full_filespec: arcwai.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   arcwai.c

   Il task arcwai ha una periodicita' pari al minimo periodo di 
   archiviazione. Ad ogni attivazione chiama la routine "arcrac",
   che raccoglie i dati degli archivi definiti in base alla loro
   frequenza. Provvede inoltre, mediante la funzione "arcwr", a 
   scrivere su disco i dati raccolti.

   Parametri:   nessuno.

   Creazione:
      10 Marzo 1992  Rel. 1.0    Fc

   Aprile 1995 Fc
      Aggiunti periodi di archiviazione 5, 10, 15 minuti per archiviazione
      normale

*/
#include <osf1.h>
#include <stdio.h>
#include <dos.h>

///#include "pscs.cfg"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "diagnoan.inc"
				
#include "taskwd.inc"

#include "print.inc"
#define _PUBLIC				// definisco le strutture dati
#include "arc.inc"
#include "arctab.inc"

// External function declarations
extern void waisim(int);
extern void arcfile(int);
extern int SimArcwai(void);
extern void arcrac(long);
extern void arclen(long);
extern void arcwr(void);

extern short time_as;
#define attesa 18

#if defined ENEL_SIM  // la chiamata waisim attende sull'orologio del simulatore
#define wai(par) waisim(par)
#endif

void arcwai(void)
{
short test_time, timer;
short mes_prec=0;
int   i;
short previsto;

test_time=ArcMin-1;

/*
      attendo che il task delle calcolate sia attivo. Il periodo di attesa
      e' dato da time_as + 1 minuto per la sincronizzazione al minuto
   */
   wai((time_as*20)
        +0
		   /*
#if defined ENEL_SIM  // nel caso ENEL_SIM le calcolate non sono allineate
        +0
#else
        +20*60
#endif
*/
        );

/*
   inizializzazione nomi file per archivi in base alla durata
*/
for(i=0;i<n_dur;i++) arcfile(i);
/*
   inizializzo a zero i campi dell'header relativi al n. di misure
   archiviate
*/
hea_camp.n_mis=0;
hea_camp.n_misvel=0;
mes_prec=(char)dbadv[db_mese];

for(;;)
	{
#if defined ENEL_SIM
	while(!SimArcwai())
		wai(5);
#endif
	timer=ArcMin-((short)dbadv[db_secondi] % ArcMin); 
   if(!timer) timer=ArcMin;
   previsto=(short)dbadv[db_secondi]+timer;
#if defined OSF1 || defined LINUX
	wai(timer*attesa);            // attende il periodo di archiviazione
#else
	wai(timer*attesa+2);            // attende il periodo di archiviazione
#endif
   if(previsto > 59)
      while((short) dbadv[db_secondi] > 10) wai(5);   // problemi allineamento orario ?
   else
      while(previsto > (short) dbadv[db_secondi]) wai(5);   // problemi allineamento orario ?

   // reset contatore di watch-dog
   wd[wd_arc].cont=wd_max_arc;
/*
        chiedo il tempo corrente per calcolare
        se e' variato il secondo
*/
	hea_camp.minuti=(char)dbadv[db_minuti];
	hea_camp.ore=(char)dbadv[db_ora];
	hea_camp.secondi=(short)dbadv[db_secondi];
	hea_camp.giorno=(char)dbadv[db_giorno];
	hea_camp.mese=(char)dbadv[db_mese];
	hea_camp.anno=(short)dbadv[db_anno];
   timer=hea_camp.secondi;

#if defined (DEBUG)
//   printf("\n %d ",timer);
#endif

/*
   verifico se sono scattati i timer per le durate di archiviazione
   8 ore, 1 giorno, 7 giorni, 1 mese
*/
	if(hea_camp.minuti==0 && hea_camp.secondi<=test_time) 
	{
		if(hea_camp.ore % 8==0) arcfile(0);    // 8 ore
		if(hea_camp.ore==0) 
      {
            arcfile(1);                             // 1 giorno
   		   if(dbadv[db_gioset]==1) arcfile(2);     // 7 giorni
      		if(mes_prec != hea_camp.mese) 
                  arcfile(3);                       // 1 mese
            mes_prec=hea_camp.mese;
      }
   }
   
/*
        preparo archiviazione al  5, 15, 30 secondi
*/
	if((timer%5) <=test_time) arcrac(5L);
	if((timer%15)<=test_time) arcrac(15L);
	if((timer%30)<=test_time) arcrac(30L);
	if((timer%60)<=test_time) arcrac(60L);

   if(hea_camp.secondi <= test_time)         // al secondo circa 0
   {
/*
   archiviazione lenta: 5 minuti, 15 minuti
   archiviazione normale: 5 minuti, 10 minuti, 15 minuti
*/
   	if(!(hea_camp.minuti % 5))
      {
	    	arcrac(300L);
         arclen(300L);
      }
	   if(!(hea_camp.minuti % 10))
      {
	    	arcrac(600L);
      }
	   if(!(hea_camp.minuti % 15))
      {
	    	arcrac(900L);
         arclen(900L);
      }
/*
    archiviazione normale e lenta: 30 minuti
*/
   	if((hea_camp.minuti == 30 || hea_camp.minuti == 0)) 
      {
          arcrac(1800L) ;  arclen(1800L);
      }
/*
   archiviazioni normali o veloci : 1 ora, 8 ore, 24 ore
*/         
   	if(!hea_camp.minuti) 
   	{
	   	arcrac(3600L) ;                        // 1 ora
		   if(hea_camp.ore % 8==0)                // 8 ore
   		{
	   		arcrac(28800L);
 		   	if(hea_camp.ore==0) arcrac(86400L); // 24 ore
   		}
      }
   }
	arcwr();	            // scrittura su disco
	}
}
