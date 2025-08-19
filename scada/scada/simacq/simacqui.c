/**********************************************************************
*
*       C Source:               simacqui.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug 29 16:27:27 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: simacqui.c-5 %  (%full_filespec: simacqui.c-5:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/* 
   SIMACQUI.C

	   task gestione acquisizione da simulatore (ENEL PC)
   
   05.08.92  -  Rel. 1.00  -  GM.Furlan

	28 Novembre 1994 Rel. 1.01 Fc
		Inserita verifica protezione

   20.12.94  -  Rel. 1.02  -  GM.Furlan
	   Inserito azzeramento del DBS prima del caricamento del
		DB di Backtrack

   27 Marzo 1995  Fc
      Inserimento nella struttura 32bit (la prima versione non
      comprende la gestione dei messaggi di START, STOP, LOADCI
      (senza inizializzazioni data base, allarmi e pagine), ALT,
      RUN, SIMTIME, DBUPD)
      Gli altri messaggi sono accettati ma non provocano nessuna
      gestione


*/
#include <osf1.h>
#include <stdio.h>
#include <math.h>
#include <dos.h>

#include "g2comdb.inc"
#include "comunic.inc"
#include "mesqueue.h"
#include "pscserr.inc"                   
#include "arc.inc"
#include "taskwd.inc"      // tabella di watch-dog e stato dei task
#include "simula.inc"      // definizioni e variabili generali per simulatore
#include <stdlib.h>
#include <string.h>
#include "simmsg.inc"      // strutture messaggi da simulatore
#include "simdia.inc"      // indirizzi in DB dei digitali di diagnostica per simulatore
#include "simana.inc"      // indirizzi in DB degli analogici di diagnostica per simulatore
#include "netmsg.h"

// External function declarations
extern int siminit(void);
extern void diagnet(short, void *, void *);
extern int bitvalue(short *, short);
extern int simsdcfg(int, void *);
extern void bitset(short *, short, short);
extern void simvardd(short, short);
extern void pscserr(int, int, int, int, int);
extern void simcldbs(void);
extern void simclall(void);
extern void simclpag(int, int);
extern int simlddbs(void *);
extern void simlgini(short);
extern void simclarc(void);
extern int simsvdbs(int);
extern int simsvall(int);
extern void ter(void);

extern short arcwai_tcb;
extern short mbox_time;
extern short mbox_tab;
extern short mbox_arc;
short stepon;

float simtime;        // tempo di simulazione 
float sav_time;       // salva tempo finale precedente simulazione
short sav_sec;        // salva secondo passo precedente 

/* union messaggi da Simulatore a SSC */
union msim {
            char bufmes[MAXDIMMSG];   
            SM_HEAD  h;     
            SM_LOADCI  ci;   /* caricamento CI */
            SM_LOADBT  bt;   /* caricamento BT */
            SM_SIMTIME st;   /* tempo di simulazione BT */
            SM_DBUPD   ud;   /* aggiornamento DB */
            SM_DIAGNO  rc;   /* dignostica ricezione configurazione */
           } msgsim;

#if defined ENEL_SIM
int clear_operation=0;
char riconosci_all=LOADCIRICALLDIS; /* variabile per ric. allarmi dopo LOADCI */
                           /* puo' assumere 4 val: 
                              -1: ric disabled (LOADCIRICALL not set)
                               1: ric active
                               2: ric carried out
                               0: not active
                           */
extern int ora_simulatore;
extern int minuti_simulatore;
extern int secondi_simulatore;
extern int milli_simulatore;
extern int giorno_simulatore;
extern int mese_simulatore;
extern int anno_simulatore;
extern float tempo_simulatore;
#endif

int acqui() 
{

double divisione;
double intero;
double fraz;
short i;
struct   dosdate_t   data;
QUEUE_PACKET packin;   // pacchetto da inserire in coda di ricezione
QUEUE_PACKET packout;  // pacchetto da inserire in coda di trasmissione
short porta;

/* union messaggi da SSC a Simulatore */
union mssc {
            char bufmes[MAXDIMMSG];   
            SM_DIAGNO dia;              // diagnostica
            SM_CONFIG cfg;              // send configurazione
            SM_COM com;                 // comandi analogici o digitali
           } msgssc;

// inizializzazione coda di ricezione
packin.que=c_ut_rx;
packin.flg=MSG_WAIT;
packin.wto=0;
packin.amsg=(char *)&msgsim;

// inizializzazione coda di trasmissione
packout.que=c_ut_tx;
packout.wto=0;
packout.flg=MSG_WAIT;
packout.lmsg=sizeof(SM_DIAGNO);
packout.amsg=(char*)&msgssc;

// inizializzazione messaggio in trasmissione
msgssc.dia.hea.nodo=0;
msgssc.dia.hea.mess=DIAGNO;

// inizializzazione task e data base di diagnostica
siminit();

/*
Verifico ins autom. all in archivio  x INITDB x SICRE
*/
if(getenv("LOADCIRICALL"))
   {
   if(!strcmp(getenv("LOADCIRICALL"),"YES"))
       riconosci_all=LOADCIRICALLON;
   else riconosci_all=LOADCIRICALLDIS;
   }

// ciclo infinito di attesa messaggio in ricezione
while(1)
{
SCODA:
	dequeue(&packin);       // scodamento

	switch(msgsim.h.mess)
	{
      case STATOPORTA:
         diagnet(sscsimon,&msgsim,&porta);
         goto SCODA;
      break;
      case START:
         if (!bitvalue(&dbdd[sscstop],g2di_sl))
         {   
            // open file di svincolo: FSVINANA.RTF, FSVINDIG.RTF
            // invio al simulatore dei punti configurati
            if( simsdcfg(ANA,&msgsim.rc)==0 && simsdcfg(DIG,&msgsim.rc)==0 )
            {
               // close file di svincolo: FSVINANA.RTF, FSVINDIG.RTF
               // set digitali di diagnostica
               bitset(&dbdd[sscstop],g2di_sl,1);
               simvardd(sscstop,1);          // allarme variazione stato digitale 
               bitset(&dbdd[sscwait],g2di_sl,0);
               simvardd(sscwait,0);
               msgssc.dia.tipo=OK;
            }
            else
            {
               // errore lettura file di svincolo: FSVINANA.RTF, FSVINDIG.RTF
               pscserr(ERR_IO,TASK_SIMACQUI,ROU_SDCFG,1,SYS_HALT);
               msgssc.dia.tipo=NOSTART;
            }
         }
         else
            msgssc.dia.tipo=NOSTART;
      break;

      case STOP:
         if (!bitvalue(&dbdd[sscwait],g2di_sl))
         { 
            // set digitali di diagnostica
            bitset(&dbdd[sscwait],g2di_sl,1);
            simvardd(sscwait,1);
            bitset(&dbdd[sscstop],g2di_sl,0);
            simvardd(sscstop,0);
            msgssc.dia.tipo=OK;
         }
         else
            msgssc.dia.tipo=NOSTOP;
      break;

      case LOADCI:
//printf("Ricevuto LOADCI: %d\n",msgsim.ci.numci);
         if (  bitvalue(&dbdd[sscwait],g2di_sl)  &&
               bitvalue(&dbdd[sscfreeze],g2di_sl)  ) goto NACK;
         // numero CI
         dbadv[sscnumci]=msgsim.ci.numci;
         // azzeramento del DBS
         simcldbs();   
         // clear allarmi
         simclall();
         // refresh pagine allarmi e trend 
         simclpag(CLALL,CLTRD);
         // trasmissione ack
         msgssc.dia.tipo=OK;
         enqueue(&packout);
         // scodamento messaggio tempo iniziale
         dequeue(&packin);       
         if (msgsim.h.mess!=SIMTIME) goto NACK;
         // salvataggio tempo finale precedente simulazione
      	sav_time=dbadv[dbtemp_sim];   
         // data/ora nuova simulazione
         simtime=msgsim.st.time;
        	dbadv[dbtemp_sim]=simtime;
        	dbadv[db_giorno_sim]=(float)msgsim.st.dd;
		   dbadv[db_mese_sim]=(float)msgsim.st.ms;
		   dbadv[db_anno_sim]=(float)msgsim.st.yy;
		   dbadv[db_ora_sim]=(float)msgsim.st.hh;
         dbadv[db_minuti_sim]=(float)msgsim.st.mm;
         // reset variabile di salvataggio del secondo passo precedente 
         sav_sec=0;
         dbadv[db_secondi_sim]=(float)msgsim.st.ss;
#if defined ENEL_SIM
	    ora_simulatore = dbadv[db_ora_sim];
	    minuti_simulatore = dbadv[db_minuti_sim];
	    secondi_simulatore = dbadv[db_secondi_sim];
	    milli_simulatore = 0;
	    giorno_simulatore = dbadv[db_giorno_sim];
	    mese_simulatore = dbadv[db_mese_sim];
	    anno_simulatore = dbadv[db_anno_sim];
	    tempo_simulatore = dbadv[dbtemp_sim];
/******
printf("SIMTIME-LOADC [%f] -  %d:%d:%d  %d/%d/%d\n",dbadv[dbtemp_sim],ora_simulatore,
	minuti_simulatore,secondi_simulatore,giorno_simulatore,mese_simulatore,
	anno_simulatore);
******/
#endif
         // trasmissione ack
         msgssc.dia.tipo=OK;
         enqueue(&packout);
         // inizializzazione DB
        	dequeue(&packin);       // scodamento messaggio aggiornamento DB       
         while(msgsim.h.mess!=INITDB)
         {
            if (msgsim.h.mess!=DBUPD) goto NACK;
            // caricamento DBS ricevuto e generazione allarmi relativi
            printf("DEBUG:simacq:Completato loadci\n");
            /*
            Setto riconosci_all a 1. Quando faccio l'update degli all.
            setto il bit 13 in dbdatr x ogni punto in emissione,
            affinche' venga inserito da call() direttamente in archivio
            (riconoscimento automatico allo startup).
            */
            if(riconosci_all!=LOADCIRICALLDIS)
               riconosci_all=LOADCIRICALLON;
            if (!simlddbs(&msgsim.ud) ) 
            {
               // trasmissione ack
               msgssc.dia.tipo=OK;
               enqueue(&packout);
            }
         	dequeue(&packin);       // scodamento messaggio init DB       
         }
         // segnalazioni avvenuta inizializzazione
         simlgini(sscnumci);     // segnalazione su libro giornale 
         if (  !bitvalue(&dbdd[sscwait],g2di_sl)  )
         {
            // set digitali di diagnostica
            bitset(&dbdd[sscwait],g2di_sl,1);
            simvardd(sscwait,1);
         }
         if (  !bitvalue(&dbdd[sscfreeze],g2di_sl)  )  
         {
            bitset(&dbdd[sscfreeze],g2di_sl,1);
            simvardd(sscfreeze,1);
         }                          
         bitset(&dbdd[sscready],g2di_sl,0);
         simvardd(sscready,0);
         msgssc.dia.tipo=OK;

         /* controllo tra tempo iniziale nuova simulazione e tempo finale 
         precedente simulazione */
         // se nuovo tempo inferiore a tempo precedente simulazione, o t=0,
         // cancellazione file d'archivio precedente simulazione
printf("simclarc[LOADCI]: sav_time = %f  dbtem_sim= %f test cancellazione arc\n",
                sav_time,dbadv[dbtemp_sim]);
         if ((dbadv[dbtemp_sim]+TIMESIM_TOLLERANCE)<sav_time || 
		dbadv[dbtemp_sim]==0)
         {                                
printf("simclarc[LOADCI]: sav_time = %f  dbtem_sim= %f cancellazione arc\n",
		sav_time,dbadv[dbtemp_sim]);
            simclarc();                   
         }
      break;
NACK:
         msgssc.dia.tipo=NOLOADCI;
      break;

      case INITDB:                  // da BackTrack
//printf("Ricevuto INITDB\n");
         if (  !bitvalue(&dbdd[sscbktk],g2di_sl)  )
         {  
            if (  !bitvalue(&dbdd[sscbktk],g2di_sl)  )
            {
               // segnalazione su libro giornale caricamento foto
               simlgini(sscnumbt);
               // set digitali di diagnostica
               bitset(&dbdd[sscbktk],g2di_sl,1);
               simvardd(sscbktk,1);
               // refresh trend 
               simclpag(SVALL,CLTRD);
            }
            bitset(&dbdd[sscready],g2di_sl,0);
            simvardd(sscready,0);
            msgssc.dia.tipo=OK;
            // reset variabile di salvataggio del secondo del passo precedente 
            sav_sec=0;
            /* controllo tra tempo iniziale nuova simulazione e tempo finale 
            precedente simulazione */
printf("simclarc[INITDB]: sav_time = %f  dbtem_sim= %f test cancellazione arc\n",
		sav_time,dbadv[dbtemp_sim]);
            if ((dbadv[dbtemp_sim]+TIMESIM_TOLLERANCE)<sav_time)  
				// se nuovo tempo inferiore, cancellazione 
            {                                // file d'archivio precedente simulazione
printf("simclarc[INITDB]: sav_time = %f  dbtem_sim= %f cancellazione arc\n",
		sav_time,dbadv[dbtemp_sim]);
               simclarc();                   
            }
         }
         else
            msgssc.dia.tipo=NOINITDB;
      break;

      case ALT:
//printf("Ricevuto ALT\n");
         if ( bitvalue(&dbdd[sscstop],g2di_sl)  &&
              bitvalue(&dbdd[sscwait],g2di_sl) )
         {
#if defined (AC_SIM_ENEL)
               // forza task in stop
               for (i=0;i<n_task;i++) 
                  wd[i].task_st=TSTOP;
#endif
               // set digitali di diagnostica
               bitset(&dbdd[sscwait],g2di_sl,0);
               simvardd(sscwait,0);
               if (!bitvalue(&dbdd[sscready],g2di_sl))
               {
                  bitset(&dbdd[sscready],g2di_sl,1);
                  simvardd(sscready,1);
               }
               if (!bitvalue(&dbdd[sscrun],g2di_sl))     
               {
                  bitset(&dbdd[sscrun],g2di_sl,1);
                  simvardd(sscrun,1);
               }
               if (!bitvalue(&dbdd[sscfreeze],g2di_sl))  
               {
                  bitset(&dbdd[sscfreeze],g2di_sl,1);
                  simvardd(sscfreeze,1);
               }
               if (!bitvalue(&dbdd[sscbktk],g2di_sl))  
               {
                  bitset(&dbdd[sscbktk],g2di_sl,1);
                  simvardd(sscbktk,1);
               }
               if (!bitvalue(&dbdd[sscreplay],g2di_sl))  
               {
                  bitset(&dbdd[sscreplay],g2di_sl,1);
                  simvardd(sscreplay,1);
               }
               msgssc.dia.tipo=OK;
         }
         else
            msgssc.dia.tipo=NOALT;
      break;

      case RRUN:   
//printf("Ricevuto RUN\n");
         if ( !bitvalue(&dbdd[sscfreeze],g2di_sl) )
         { 
            // forza task in RUN
            for (i=0;i<n_task;i++) 
               wd[i].task_st=TRUN;
            // set digitali di diagnostica
            bitset(&dbdd[sscfreeze],g2di_sl,1);
            simvardd(sscfreeze,1);
            bitset(&dbdd[sscrun],g2di_sl,0);
            simvardd(sscrun,0);
            msgssc.dia.tipo=OK;
         }
         else
            msgssc.dia.tipo=NORUN;
      break;

      case SIMTIME:
//printf("Ricevuto SIMTIME\n");
         if ( !bitvalue(&dbdd[sscwait],g2di_sl)   ||
              !bitvalue(&dbdd[sscrun],g2di_sl)    ||
              !bitvalue(&dbdd[sscfreeze],g2di_sl) ||
              !bitvalue(&dbdd[sscbktk],g2di_sl) ||
              !bitvalue(&dbdd[sscreplay],g2di_sl)   )
         { 
            // aggiornamento tempo di simulazione
            simtime=msgsim.st.time;
	    /*
		verifico che il tempo precedente non sia superiore
		a quello inviato (richiesto messaggio clear).
		in tal caso riazzero gli archivi
	    */
	    if((simtime<(dbadv[dbtemp_sim]+TIMESIM_TOLLERANCE))&&
			(!bitvalue(&dbdd[sscfreeze],g2di_sl)))
		{
		simclarc();
                /*
                Devo resettare var di sincronizzazione con 
                innesco attivita' periodiche
                */
                clear_operation=1;
//		printf("\n\n\n\n\n\n CLEAR  simtime = %f dbadv[dbtemp_sim] = %f\n\n\n\n",simtime,dbadv[dbtemp_sim]);
                }

           dbadv[dbtemp_sim]=simtime;
           dbadv[db_giorno_sim]=(float)msgsim.st.dd;
	   dbadv[db_mese_sim]=(float)msgsim.st.ms;
	   dbadv[db_anno_sim]=(float)msgsim.st.yy;
	   dbadv[db_ora_sim]=(float)msgsim.st.hh;
           dbadv[db_minuti_sim]=(float)msgsim.st.mm;

            // salvataggio secondo passo precedente 
            sav_sec=dbadv[db_secondi_sim];
            dbadv[db_secondi_sim]=(float)msgsim.st.ss;
#if defined ENEL_SIM
	    tempo_simulatore = dbadv[dbtemp_sim];
	    ora_simulatore = dbadv[db_ora_sim];
	    minuti_simulatore = dbadv[db_minuti_sim];
	    secondi_simulatore = dbadv[db_secondi_sim];
#ifdef FABIO
	    milli_simulatore = 0;
#endif
            /*
            Calcolo anche i millesimi del simulatore
            In questo modo attivero' le calcolate dopo 
            pochi decimi.
            */
            fraz=modf(tempo_simulatore,&intero);
            fraz=fraz * 1000;
            milli_simulatore=fraz;
#ifdef SCADA_DEBUG
            printf("DEBUG: tempo_simulatore=%f milli_simulatore=%d\n",tempo_simulatore,milli_simulatore);
#endif
	    giorno_simulatore = dbadv[db_giorno_sim];
	    mese_simulatore = dbadv[db_mese_sim];
	    anno_simulatore = dbadv[db_anno_sim];

/******
printf("SIMTIME [%f] -  %d:%d:%d  %d/%d/%d\n",dbadv[dbtemp_sim],ora_simulatore,
	minuti_simulatore,secondi_simulatore,giorno_simulatore,mese_simulatore,
	anno_simulatore);
*********/
#endif

#if defined (AC_SIM_ENEL)
            // attivazione task "attiper" (ad ogni invio del tempo di simulazione)
            tra(mbox_time,2);
            // attivazione task "tabper" (ogni mezz'ora di simulazione)
            // verifica lo scadere della mezz'ora
            if ((short)dbadv[db_minuti_sim]%30==0 && dbadv[db_secondi_sim]==0.)
               tra(mbox_tab,1);
            // se non sono nello stato di REPLAY, attivazione task "arcwai" 
            if ( bitvalue(&dbdd[sscreplay],g2di_sl) )
            {
               // verifica lo scadere del tempo di archiviazione minimo
               if( (short)dbadv[db_secondi_sim]%ArcMin < sav_sec%ArcMin )
                  tra(mbox_arc,1);
            }
#endif
            msgssc.dia.tipo=OK;
         }
         else
            msgssc.dia.tipo=NOSIMTIME;
      break;

      case DBUPD: 
//printf("Ricevuto DBUPD\n");
         if (  bitvalue(&dbdd[sscstop],g2di_sl)  )
         {   
            // caricamento DBS ricevuto e generazione allarmi relativi
            if (!simlddbs(&msgsim.ud) ) 
               msgssc.dia.tipo=OK;
            else
               msgssc.dia.tipo=NODBUPD;
         }
         else
            msgssc.dia.tipo=NODBUPD;
      break;

      case FFREEZE:
//printf("Ricevuto FREEZE\n");
         if ( !bitvalue(&dbdd[sscready],g2di_sl)  ||
              !bitvalue(&dbdd[sscrun],g2di_sl) )
         { 
            // set digitali di diagnostica
            if ( !bitvalue(&dbdd[sscready],g2di_sl) )
            {
               bitset(&dbdd[sscready],g2di_sl,1);
               simvardd(sscready,1);
            }
            if ( !bitvalue(&dbdd[sscrun],g2di_sl) )
            {
               bitset(&dbdd[sscrun],g2di_sl,1);
               simvardd(sscrun,1);
            }
            bitset(&dbdd[sscfreeze],g2di_sl,0);
            simvardd(sscfreeze,0);
            msgssc.dia.tipo=OK;
         }
         else
            msgssc.dia.tipo=NOFREEZE;
      break;

      case STEP:
//printf("Ricevuto STEP\n");
         if ( !bitvalue(&dbdd[sscfreeze],g2di_sl) )
         {
               stepon=1;
               msgssc.dia.tipo=OK;
         }
         else
            msgssc.dia.tipo=NOSTEP;
      break;
     
      case BKTKON: 
//printf("Ricevuto BKTKON\n");
         if ( !bitvalue(&dbdd[sscfreeze],g2di_sl) )
         {

#if defined (AC_SIM_ENEL)
            // forza task in stop
            for (i=0;i<n_task;i++) 
               wd[i].task_st=TSTOP;
#endif

            // salvataggio tempo finale attuale simulazione
         	sav_time=dbadv[dbtemp_sim];   
            // salvataggio DBS e Allarmi
            if (!simsvdbs(SAVE) && !simsvall(SAVE)) 
            {
               // set digitali di diagnostica
               bitset(&dbdd[sscfreeze],g2di_sl,1);
               simvardd(sscfreeze,1);
               bitset(&dbdd[sscbktk],g2di_sl,0);
               simvardd(sscbktk,0);
               msgssc.dia.tipo=OK;
            }     
            else   // errore apertura file FDBDP.SAV o ALLAR.SAV
               msgssc.dia.tipo=NOBKTKON;
         }     
         else
            msgssc.dia.tipo=NOBKTKON;
      break;

      case BKTKOFF:
//printf("Ricevuto BKTKOFF\n");
         if ( !bitvalue(&dbdd[sscbktk],g2di_sl) )
         {   
            // carica dbs e allarmi salvati in freeze  
            if (!simsvdbs(RESTORE) && !simsvall(RESTORE)) 
            {
               // refresh pagine allarmi
               simclpag(CLALL,SVTRD);
               // set digitali di diagnostica
               bitset(&dbdd[sscbktk],g2di_sl,1);
               simvardd(sscbktk,1);
               bitset(&dbdd[sscfreeze],g2di_sl,0);
               simvardd(sscfreeze,0);
               msgssc.dia.tipo=OK;
            }
            else       // errore apertura file FDBDP.SAV o ALLAR.SAV
               msgssc.dia.tipo=NOBKTKOFF;
         }
         else
            msgssc.dia.tipo=NOBKTKOFF;
      break;

      case LOADBT: 
//printf("Ricevuto LOADBT: %d\n",msgsim.bt.numbt);
         if ( !bitvalue(&dbdd[sscbktk],g2di_sl) )
         {   
            // numero BT
            dbadv[sscnumbt]=msgsim.bt.numbt;

            // 20.12.94: inserito azzeramento del DBS
            simcldbs();
				
            // clear allarmi
            simclall();
            // refresh pagine allarmi
            simclpag(CLALL,SVTRD);
            msgssc.dia.tipo=OK;
            enqueue(&packout);
            // scodamento messaggio tempo iniziale
            dequeue(&packin);       
            if (msgsim.h.mess==SIMTIME)
            {
               // data/ora nuova simulazione
               simtime=msgsim.st.time;
        	      dbadv[dbtemp_sim]=simtime;
        	      dbadv[db_giorno_sim]=(float)msgsim.st.dd;
		         dbadv[db_mese_sim]=(float)msgsim.st.ms;
		         dbadv[db_anno_sim]=(float)msgsim.st.yy;
		         dbadv[db_ora_sim]=(float)msgsim.st.hh;
               dbadv[db_minuti_sim]=(float)msgsim.st.mm;
               dbadv[db_secondi_sim]=(float)msgsim.st.ss;
#if defined ENEL_SIM
	    ora_simulatore = dbadv[db_ora_sim];
	    minuti_simulatore = dbadv[db_minuti_sim];
	    secondi_simulatore = dbadv[db_secondi_sim];
	    milli_simulatore = 0;
	    giorno_simulatore = dbadv[db_giorno_sim];
	    mese_simulatore = dbadv[db_mese_sim];
	    anno_simulatore = dbadv[db_anno_sim];
	    tempo_simulatore = dbadv[dbtemp_sim];
printf("SIMTIMELOADB [%f] -  %d:%d:%d  %d/%d/%d\n",dbadv[dbtemp_sim],ora_simulatore,
	minuti_simulatore,secondi_simulatore,giorno_simulatore,mese_simulatore,
	anno_simulatore);
#endif
            }
            else
               msgssc.dia.tipo=NOSIMTIME;
            // trasmissione ack o nack
            enqueue(&packout);
         }
         else
            msgssc.dia.tipo=NOLOADBT;
      break;

      case REPON:  
//printf("Ricevuto REPON\n");
         if ( !bitvalue(&dbdd[sscbktk],g2di_sl) )
         {   
            // segnalazione su libro giornale avvenuta inizializzazione
            simlgini(sscnumbt);
            // refresh pagine allarmi e trend 
            simclpag(CLALL,CLTRD);
            // set digitali di diagnostica
            bitset(&dbdd[sscbktk],g2di_sl,1);
            simvardd(sscbktk,1);
            bitset(&dbdd[sscreplay],g2di_sl,0);
            simvardd(sscreplay,0);
            msgssc.dia.tipo=OK;
         }
         else
            msgssc.dia.tipo=NOREPON;
      break;

      case REPOFF: 
//printf("Ricevuto REPOFF\n");
         if ( !bitvalue(&dbdd[sscreplay],g2di_sl) )
         {   
            // set digitali di diagnostica
            bitset(&dbdd[sscreplay],g2di_sl,1);
            simvardd(sscreplay,1);
            bitset(&dbdd[sscbktk],g2di_sl,0);
            simvardd(sscbktk,0);
            msgssc.dia.tipo=OK;
         }
         else
            msgssc.dia.tipo=NOREPOFF;
      break;
      default:    // messaggio sconosciuto
	printf("errore ack :messaggio sconosciuto\n");
            pscserr(ERR_TASK,TASK_SIMACQUI,ROU_MESS,1,SYS_CONT);
            msgssc.dia.tipo=NOMESS;
      break;
   }   
   // trasmissione da SSC a simulatore di "msgssc.dia"
   if(msgssc.dia.tipo!=OK)
         {   
printf("errore ack [%d]\n",msgssc.dia.tipo);
      pscserr(ERR_TASK,TASK_SIMACQUI,ROU_MESS,2,SYS_CONT);
        }   
   enqueue(&packout);
}

ter();
}



