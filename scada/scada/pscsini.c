/**********************************************************************
*
*       C Source:               pscsini.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug  1 09:15:53 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: pscsini.c-3.2.1 %  (%full_filespec: pscsini.c-3.2.1:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/****************************************************************************/
/* -> pscsini                                                               */
/*                                                                          */
/*  task che procede alla attivazione delle varie attivita;                 */
/*  di cui e` composto PSCS 2000                                            */
/*                                                                          */
/* Modifiche:                                                               */
/*    15.10.92  -  GM.Furlan                                                */
/*         Aggiunta attivazione task aggiornamento configurazione           */
/*                                                                          */
/*    agosto 93   mp   porting a 32 bit                                     */
/*                                                                          */
/*    10.10.94  -  M. Andreasi Bassi                                        */
/*         Aggiunta attivazione periodica task trasmissione MMI remoto      */
/*         in sistemi SELTA.                                                */
/*                                                                          */
/*    10 Novembre 1994 Fc                                                   */
/*         Attivazione task cte-arch                                        */
/*                                                                          */
/*    28.01.95  -  M. Andreasi Bassi                                        */
/*         Aggiunta attivazione gestori protocollo 0xAA55 seriale verso     */
/*         front-end nei sistemi AEM.                                       */
/*                                                                          */
/*    18.04.95  - MWw                                                       */
/*         Aggiunto task idle per evitare sblocchi anomali                  */
/*                                                                          */
/*    11 Settembre                                                          */
/*    Stampanti remote e clock gps                                          */
/*                                                                          */
/****************************************************************************/
#include <osf1.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#if defined OSF1 || defined LINUX
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <sys\types.h>
#include <sys\stat.h>
#endif
#include <io.h>

#include "pscs.cfg"
#include "messcada.inc"
#include "g2comdb.inc"
#include "dconf.inc"
#include "maxpar.inc"
#include	"allar.inc"
#include "comunic.inc"

#define _PUBLIC 0

#include "taskwd.inc"

#ifndef MMI_PC                 // protezione in libreria matrox
   char _STR_LOCK[] = "KEY \0.\0ss.pp";
#endif
extern int pscswd_tcb, pccom_tcb;
extern int asinct_tcb;
extern int _call_tcb, stampe_tcb, scgev_tcb, tcval_tcb;
extern int attiper_tcb, monitor_tcb, gdac_tcb;
extern int monitor_tcb, taggcfg_tcb, schc_tcb, thcwin_tcb;
extern int tcte3_tcb, tcte4_tcb;
extern int reptask_tcb;
extern int idle_tcb;		// 18.4 mb
extern int gps_tcb; 
#ifdef GERARC
        extern short mbox_abilger;
#endif

#ifndef AC_SIMU
    extern int acqui_tcb;
#endif

#if defined (AC_INETDUALE)            //                   inet
   extern int inibus_tcb;
#endif

#if defined (STAR_SDI)           // le periferiche sono di tipo Star SDI
   extern int carac_tcb;
#endif

#if defined (AC_SAMP)            //                   samp
   extern int dac_tcb;
#endif

#if defined (SELTA)
   extern int lnkrem_tcb;
#endif

#ifdef MMI_PC
   extern int mmiini_tcb;
#endif

extern int _tabulati_tcb, tabper_tcb;
extern short int mbox_lbg;
extern short int mbox_disk;
extern int arcsend_tcb;
extern int arcwai_tcb;
char   farc[60 * max_video * 4]; 
extern int _isa_tcb;
extern int rxpio_tcb, txpio_tcb, duatask_tcb;


#if defined (RCE)
   extern int rceprn_tcb;
#endif

// inserito 18.4 task idle m.b.
long idletime;

// Function declarations
void tra(int mbox, int flag);
void scd(void);
void NetMarteStartup(void);
void syn(int tcb, int priority1, int priority2);
void alldef(void);
void tas(int tcb);
void synsim(int tcb, int priority1, int priority2);
void arcopen(void);
void sce(void);
void ter(void);

void idle()
{
	while(1)
		idletime +=1;
}
// fine task

void* pscsini()
{
short i; 

   tra(mbox_disk,1);       // libero lock accessi a disco

#ifdef GERARC
//printf("pscsini.c: prima tra a uno su %d\n",mbox_abilger);
        tra(mbox_abilger,1);
#endif

#if !defined OSF1 && !defined LINUX
   tas(idle_tcb);				// attivo il task idle 18.4
	wai(2);						// do tempo di partire
#endif

      
 // inizializzazione tabella di watch-dog per task

for(i = 0; i < n_task; i++)
   {
   wd[i].task_per = TNONPERIODICO;// tutti i task inizialmente come non periodici 
   wd[i].task_st  = TRUN;         // tutti i task in RUN
   }
wd[wd_attiper].task_per = TPERIODICO;
wd[wd_attiper].cont     = 4 * wd_max_attiper; // tiene conto del tempo di attivazione del task

if(ARCHIVI_NV)
   {
	wd[wd_arc].task_per = TPERIODICO;
	wd[wd_arc].cont     = 8 * wd_max_arc; // tiene conto del tempo di attivazione del task
   }
else
   {
	wd[wd_arc].task_st = TSTOP;   // se archivi non definiti, task in STOP
   }

if(TABUL)
   {
	wd[wd_tabul].task_per = TPERIODICO;
   wd[wd_tabul].cont     = wd_max_tabul;  // tiene conto del tempo di attivazione del task
   }
else
   {
	wd[wd_tabul].task_st  = TSTOP;   // se tabulati non definiti, task in STOP
   }

if(!PAS_STOP)
   wd[wd_pas].task_st = TSTOP;   // se pas non definiti, task in STOP

scd();                           // blocco lo Scheduler

//reset_stack();         // !! resetta stack per verifica occupazione mbmb


/* Attiva gestione lan */

if(NET_ABIL) NetMarteStartup();

#if defined (AC_PLCS5)
   s5_ini();
#endif

#if defined OSF1 || defined LINUX
syn(pscswd_tcb,2,1);         // task wdog principale che gestisce
#else
syn(pscswd_tcb,18,1);         // task wdog principale che gestisce
#endif
                              // l'aggiornamento dell'ora in dbs

#if defined(AC_INETDUALE)
   if(!DEBUG) tas(inibus_tcb);// in fase di debugging non lo attivo
#endif


#if defined(STAR_SDI)         // le periferiche sono di tipo Star SDI
   tas(carac_tcb);
#endif

#if defined(AC_SAMP)
	_InitSamp8250();
	tas(dac_tcb);
#endif

#if defined(AC_SERIALE)
	_InitSeri8250();       // Inizializza COM1 e COM2 e attiva i task di comunicazione
#endif

#if defined(SELTA)
   InitTxRem();           // Inizializza linea comunicazione a MMI remoto
   syn(lnkrem_tcb,300,20);// Attiva il task in attivazione periodica (ogni 15", la prima dopo 1")
#endif

#if !defined OSF1 && !defined LINUX
if(PAS_STOP) init_pas();
#endif

alldef();
for(i = 0; i < max_dbsall; i++) tra(mbox_all_0 + i,1);


#if !defined OSF1 && !defined LINUX
_lancperif();             // task output verso le periferiche
#endif


tas(scgev_tcb);
tas(stampe_tcb);
tas(_call_tcb) ;
tas(asinct_tcb);
tas(tcval_tcb);

tas(taggcfg_tcb);
tas(schc_tcb) ;
tas(thcwin_tcb) ;

#ifndef AC_SIMU		
   tas(acqui_tcb) ;
#endif

#if defined ENEL_SIM
synsim(attiper_tcb,18,18);
#else
syn(attiper_tcb,18,18);
#endif

#if defined(RCE)
   tas(rceprn_tcb);
#endif

syn(gdac_tcb,18 / PER_GDAC,30);

if(TABUL)
   {
   tas(_tabulati_tcb);         /* tabulati */
   tas(tabper_tcb);
   tra(mbox_lbg,1);            /* libero lock files libro giornale */
   }

if(ARCHIVI_NV)                 // archivi
   {
   arcopen();
   tas(arcwai_tcb);
   }

if(ISA) tas(_isa_tcb);

tas(monitor_tcb);

#ifdef MMI_PC
   tas(mmiini_tcb);
#endif

/* Attiva pag */

#if !defined OSF1 && !defined LINUX
PagInitMarte();
#endif

#if defined (REPERIBILI)
   if(GESREP)
   {
      RepInit();
      tas(reptask_tcb);
   }
#endif

#if !defined OSF1 && !defined LINUX
if(SYS_DUALE)
   {
   IniBus();
   syn(pccom_tcb,9,10);							// task watch dog hardware
   tas(rxpio_tcb);		  						// driver link master slave
   tas(txpio_tcb);
   tas(duatask_tcb);
   }
#endif

#if defined (CTEARCH)
	cteini(fpp[fnomi], fpp[fdde]);
	tas(tcte3_tcb);
	tas(tcte4_tcb);
#endif

#if defined (PRNSERVER)
   PrnTas();
#endif
#if defined (GPS_CLOCK)
   tas(gps_tcb);
#endif

sce();     // attivo lo scheduler
ter();     // termina, si fa una volta sola!
}
