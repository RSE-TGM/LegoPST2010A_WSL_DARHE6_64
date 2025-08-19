/**********************************************************************
*
*       C Source:               attiper.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Mon Aug  4 14:04:08 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: attiper.c-4 %  (%full_filespec: attiper.c-4:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <stdio.h>
#include <dos.h>
#ifdef PROT_HASP
#include "\pscs32\hasp\haspdef.h"
#endif
/*
	il task attiper provvede ad eseguire le seguenti attivita' periodiche
	- timer organi
   - calcolate analogiche
  viene attivato ogni secondo

   9 1 1992    rev 1.1     di Fc
      aggiunto reset lock_scada watch dog scada per sistemi MB

   6 Giugno 1992  rev. 1.2 Fc
      Modificato allineamento calcolate al minuto.

   10 Novembre 1994
      Getione periodica CTE-ARCH e comunicazione SDS

   16 Marzo 1995
      Inserimento gestione flag flag_ordi per ricalcolo di tutti i
      digitali ed organi in seguito a coda c_digor piena

	09 Ottobre 1995
		Inserimento protezione Hasp
*/

#include "pscs.cfg"
#include "comunic.inc"
#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "organi.inc"
#include "mesqueue.h"
#include "mesest.inc"
#include "messcada.inc"
#include "diagnodi.inc"
#include "diagnoan.inc"
#include "dconf.inc"

#include "taskwd.inc"

#define T_HTEST   15

/* Function prototypes */
extern void wai(int);
extern void calc(void);
extern void timeor(short, short);
extern void calcor(short);
extern void calcdi(short);
extern int bitvalue(short *, short);
extern void ter(void);

extern DB_HEADER h_db;
short count_calc=-1;
short minuto;


void attiper()
{
short i;
QUEUE_PACKET packs;
short mess;

//dprintf(2,"attiper: secondi = ",dbadv[db_secondi]);

// reset contatore di watch-dog
wd[wd_attiper].cont=wd_max_attiper;
/*
	calcolate  analogiche standard	il timer viene corretto in
	modo che partano allineate al minuto
*/

#if defined ENEL_SIM

count_calc=3;  // disabilitato l'allineamento al minuto
#endif

if(! time_as) 
{
/*
	se count_calc == -1 siamo in fase di avvio attendo l'allineamento
	al minuto (n. secondi =0)
*/

	if(count_calc==-1)
          {
          while(dbadv[db_secondi] > 0.9)
             { 
             wai(2);
             }
  	  minuto=dbadv[db_minuti];
          }
	count_calc++;


#if defined (PROT_DALLAS)
   if(!count_calc)	 
            readkey();
 	if(count_calc==30) 
               checkkey();
#endif

   if(count_calc==1) 
      {
      minuto=dbadv[db_minuti]+1;
      if(minuto==60) minuto=0;
      }

   if(count_calc==60) 	 /* ogni 60 secondi verifico allineamento */
      {
      count_calc=0 ;

      if(minuto== (short)dbadv[db_minuti])  
         {
         calc(); 		
         }
      else
        {
              /*
              attendo il minuto previsto (la variabile i interviene in caso
              di cambio data)
              */
              i=0;
	      while(dbadv[db_minuti] != minuto && i<30) 
                 {
                 wai(2); 
                 i++;
                 }
              calc();
         }

#ifdef AC_SAMP
		diagsamp();
  		sendora2pc();
#endif
	}
	else 
           {
           /*
           PER AMBIENTE ALTERLEGO VIENE LANCIATA LA calc DA QUI
           */
           calc();
           }


#ifdef AC_INETDUALE
/*
   ogni 10 secondi richiedo la diagnostica di rete
	Per armadi di tipo Sepa richiedo ogni minuto la data e 
	tutti i digitali (un armadio ogni tot minuti)
*/
	#if defined (STAR_SEPA)
      if(!(count_calc % 10 ))    
         gesrete();
	#endif
#endif
#if defined (CTEARCH)
	if(!(count_calc%60)) cteattiva();			// messaggio ciclico attivazione
#endif
#if defined (AC_SDS)
	sdstemp(count_calc);
#endif
if (ISA)
	//if(!(count_calc%60)) isadia(-1,0);
	printf("isadia() chiamata commentata\n"); // MOMENTANEAMENTE
}


#ifdef PROT_HASP
   if(!(((short)dbadv[db_minuti])%T_HTEST)&& !count_calc)
	// verifica protezione Hasp
	haspqry(0,0,0,QUERY_MODE,HSCADA);
#endif


/*
	calcolo organi
*/
timeor(or_tab[inizio_or].iniz,or_tab[inizio_or].num) ;
inizio_or++;
if(inizio_or==5) inizio_or=0 ;
/*
	decremento i timer
*/
if(time_as) time_as--;
if(time_aa) time_aa--;
if(time_ordi > 0) time_ordi-- ;
if( ! time_ordi)						/* scaduto timer organi e digitali procedo al calcolo */
{
	for(i=0;i<h_db.dimor;i++)											 
      if(dbou[i] != -1) calcor(i);
	for(i=0;i<h_db.dimds;i++)											 
      if(dbdsu[i] != -1)  calcdi(i);
	time_ordi=-1;
/*
	se sono slave e sono aggiornato invio il messaggio di slave on
*/
if (SYS_DUALE)
   {
	if(!sys_master && bitvalue(&dbdd[slaveagg],g2di_sl))
	   {
		packs.flg=MSG_WAIT;
		packs.wto=0;
		packs.que=c_dua_tx;
		packs.amsg=(char*) & mess;
		mess=SL_ONLINE;
		packs.lmsg=sizeof(mess);
		enqueue(&packs);
	   }
   }
}
//
// se e' =1 il flag di ricalcolo digitali ed organi: procedo al nuovo
// ricalcolo e reset del flag (vedi anche calcdi)
//
if(flag_ordi)
{
   flag_ordi=0;
	for(i=0;i<h_db.dimor;i++)											 
      if(dbou[i] != -1) calcor(i);
	for(i=0;i<h_db.dimds;i++)											 
      if(dbdsu[i] != -1)  calcdi(i);
}

ter() ;

}

