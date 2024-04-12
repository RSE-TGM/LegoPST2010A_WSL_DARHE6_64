/**********************************************************************
*
*       C Source:               mscada.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Jul 11 19:04:29 2006 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: mscada.c-10 %  (%full_filespec: mscada.c-10:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*-> mscada*
 *   Main che provvede alla inizializzazione dei dati
 *   e delle attivita' relative al sistema PSCS VERSIONE STOPPC
 *
 *   Provvede:
 *   1 - mappa in memoria il Data Base 
 *   2 - attiva il MARTE
 *
 *    20 Ottobre 1994 inserimento modifiche per SELTA
 *		09 Ottobre 1995																		 
 *			Inserimento protezione Hasp - CD												 
 *   ----------------------------------------------------------
 */

#include <osf1.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <math.h>

#define _PUBLIC 0

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "g2ptrdb.inc"
#include "dconf.inc"
#include "pscs.cfg"
#include "comunic.inc"
#include "tipal.inc"
#include "ttipal.inc"
#include "tdeflag.inc"
#include "messcada.inc"
#include "diagnodi.inc"
#include "diagnoan.inc"
#include "video.inc"
#include "print.inc"
#include "allar.inc"
# include "CAP.h"		/* Serve per la gestione delle licenze */
#include "skey_manager3.h"	/* Serve per la gestione delle licenze hardware*/

#if defined (STAR_SDI)
   #include "diaginet.inc"
#endif
#if defined (STAR_SEPA)
   #include "sepdiag.inc"
#endif

#define com_file 15

short   nbyte[com_file];
long  off_f[com_file];

short debsamp;

DB_HEADER h_db;				// header data base

#if defined (PROT_DALLAS)
	char protezione[17];
#endif

int    flag_demo = 0;		/* 0 --> disponibile licenza tipo full
                                   1 --> disponibile licenza tipo demo  */
double tempo_license = 0.0;     /* Tempo limite per la validita' della
                                   licenza                              */
char   *dati_license[2];        /* Vettore utilizzato per passare
                                   informazioni relative alle licenze
                                   (tempo_license) a Xscada             */

main(argc,argv)
short int argc;
char *argv[];

{
char    Buffer[ENELINFO_LEN + 1];
int    indiceSocieta; //serve per gestire eventualmente comportamenti differenziati
char   messaggioErrore[1024];
int    errorCode;
int    richiestaScrittura;
short   i;
int     ret;
double  tempo_corr;

/*
   Si controlla se esiste la licenza per l'attivazione del programma.
   Prima la chiave hardware ed eventualmente quella software
*/
        // Controllo chiave hardware
        richiestaScrittura=KEYWRITE;
        errorCode=skey_verifica_e_carica3(richiestaScrittura, KEYLABEL, KEYPASSWD,
                                          LICSCADA, &indiceSocieta);
	if(errorCode != 0)
	{
		skey_stampa_errore(errorCode, &messaggioErrore);
		printf("scada:%s \n", messaggioErrore);

		//provo l'eventuale chiave software
		if(CAP(SCADA_LIC, Buffer) == -1)
		{
			exit(1);
		}
		if(manageLicense(Buffer,"scada",&flag_demo,&tempo_license) == -1)
		{
			exit(1);
		}
	}
	else
	{
		flag_demo=0;
		tempo_license=10000000;
	}




/* 
printf("scada main DEBUG: flag_demo = %d\ttempo_license = %lf\n",
       flag_demo, tempo_license);
*/
        ret = setTimeLicense(flag_demo, &tempo_license);
        if(ret == -1)
           exit(1);


#ifdef PROT_HASP
	haspinit();
#endif

#if defined (PROT_DALLAS)
	char *env;
	if((env=getenv("KEY")) != NULL)
		{
		memset(protezione,' ',16);
		protezione[16]=0;
		if(strlen(env) > 16)
			env[16]=0;
		strcpy(protezione,env);
		memcpy(protezione,env,strlen(env));
		}
#endif

#if defined (SELTA)
  striuk("SELTA");         // caricamento scritte per SELTA
#else
  striuk("");              // caricamento scritte per altri
#endif

// inizializzazioni di default per gli switch di attivazione

TABUL=0;                  // tabulati non abilitati
ARCHIVI_NV=0;             // archivi non abilitati
SYS_DUALE=0;              // non duale
sys_master=1;             // master
ISA=0;                    // isa non abilitato
NET_ABIL=1;               // rete ethernet abilitata
HCPY=0;                   // hard copy disabilitata (solo per pagina diagnostica) 
GESREP=0;             // reperibili non abilitati

CONT_ALL_ZONE=0;          // contatori allarmi per zone e database non abil.
SEGNALA_RIC_ALLARMI=0;    // segnala su stampante riconosc. allarmi non abil.
SKR_ALL=0;                // visita intera pagina allarmi nonabili.
RIC_SI=0;                 // riconosc. singolo allarme non abil.
PER_GDAC=1;               // frequenza aggiornamento pagine a 1
BUZZER=0;                 // abilitazione comando contatto buzzer
SEC_FORMAT=0;				  // formato stringa allarmi: GG/HH/MM...	

PAS_STOP=0;               // presenza pas 
NPC_PAS=0;                // numero pas a 0
PAS_INI=0;                // pas 1 non subito attivo
num_video=1;              // numero MMI a 1

DEBUG=0;                   // non debug per default 

/* analisi argomenti passati in attivazione */
for (i=1; i<argc ;i++)
   scan_arg(argv[i]);

if(getenv("DEBSAMP") != NULL)
	debsamp=1;
else
	debsamp=0;
/*
	disabilito la ricezione ^C
*/
	signal(SIGINT,	SIG_IGN);

restart() ;
}


//
//	effettua il restart del sistema
//--------------------------------
restart()
{
char c;
   	readef();
  	   readdb(&h_db);				//	lettura parametri data base

	nbyte[0]=lun_stato;				off_f[0]=lun_stato;
	nbyte[1]=rec_fdaa;				off_f[1]=of_fdaa;
	nbyte[2]=rec_fdas;				off_f[2]=of_fdas;
	nbyte[3]=rec_fdac;				off_f[3]=of_fdac;
	nbyte[4]=rec_fdad;				off_f[4]=of_fdad;
	nbyte[5]=rec_fdao;				off_f[5]=of_fdao;

	nbyte[7]=rec_fdda;				off_f[7]=of_fdda;
	nbyte[8]=rec_fdds;				off_f[8]=of_fdds;
	nbyte[9]=rec_fddc;				off_f[9]=of_fddc;
	nbyte[10]=rec_fddd;				off_f[10]=of_fddd;
	nbyte[11]=rec_fddo;				off_f[11]=of_fddo;

	nbyte[13]=rec_fdor;				off_f[13]=of_fdor;
	nbyte[14]=rec_fdst;				off_f[14]=of_fdst;

   NetDosStartup();

   allocdb(0,&h_db);
   rwdbal(0,&h_db,&h_db); /* allocazione database  */
/*
   verifico se e' stato variato il dbs ed aggiorno la release
*/
#if defined (STAR_SDI)
   aggfconf(FPUNTI);   //MAX era commentato
#endif

init();	       /* open file operativi								*/

   initdb();		 /* inizializzazione data base					*/
   initcalc();		 /* calcolate										   */
   initor();		 /* organi											   */

#ifdef MMI_PC
//   cinitvideo();     //    attenzione !! viene fatto nello SCADA altrimenti 
#endif               //    il reset della pcbx fatto nell' MMI sprogramma l'iSBX507

   leggifile();	 /* definizione linee 			               */

#ifdef MMI_PC
#else
   initline();		 /* inizializzazione linee							*/	  
#endif             //    reset della pcbx

#if defined (STAR_SEPA)
	sepiniz();
#endif
#if defined (STAR_SELTA)
	leggides();
#endif

#if !defined OSF1 && !defined LINUX
Riderr();        // ridirige gli errori disco del DOS
#endif
/*
	setto timer per attivazione calcolate e calcolo organi e calcolate
	digitali
*/

#if defined (utente_ordi)
	time_ordi=utente_ordi ;
#else
	time_ordi=tval_ordi;
#endif	
#if defined (utente_aa)
	time_aa=utente_aa;
#else
	time_aa=tval_aa;
#endif	
#if defined (utente_as)
	time_as=utente_as ;
#else
	time_as=tval_as;
#endif

#ifdef MMI_PC
mainmmi();
#endif

/* inizializzazione PAG */
#if !defined OSF1 && !defined LINUX
PagInitDos();
#endif

#if defined ALARM_SIGNAL
   ReadAlarmSignal(&h_db);
#endif
beg_marte() ;   
#if defined OSF1 || defined LINUX
#ifdef XSCADA_INTERFACE
/*
   Attivazione di Xscada: viene passato il tempo limite di validita' della
   licenza. 
*/
   dati_license[0] = (char *)calloc((ENELINFO_LEN + 100),sizeof(char)); 
   sprintf(dati_license[0], "%lf", tempo_license);
   dati_license[1] = NULL;
printf("mscada restart() DEBUG: dati_license[0] = %s\n",
       dati_license[0]);
   AttivaXscada(1,dati_license);
#else
system("clear");
printf("- SCADA - \n\n");
printf("  Q) Quit\n");

for(;(c=getchar())!='q' || c!='q';)
{
        system("clear");
        printf("- SCADA -\n\n");
        printf("  Q) Quit\n");
}

QuitScada();
#endif
#endif
}
