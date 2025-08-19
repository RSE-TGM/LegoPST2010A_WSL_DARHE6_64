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
	Routine per la generazione stringhe in italiano, inglese o
	altre lingue

	17 Gennaio 1994 Fc
   20 Ottobre 1994 Fc   personalizzazione Selta
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include "switch.inc"

/* definizioni in italiano */

/*	Rce	*/

char *rcest1i="S T A M P A   P E R T U R B O G R A F I C A ";
char *rcest3i="  Prg   hh:mm:ss,mil Arm.    Sigla  Cat.   Descrizione        Val Stato";
char *rcest4i=" *** EVENTO SGANCIATORE *** ";
char *rcest5i=" *** R C E   C O N C L U S A *** ";
char *rcedatei="Data :";
char *rcetimei="Ore :";
char *rceRCEi="-RCE";

/*	archivi */

char *arc_numberi="ARCHIVIO N.";
char *arc_stampatoi="STAMPATO ALLE ";
char *arc_errorei="RICHIESTA STAMPA ARCHIVIO NON CORRETTA PER INCONGRUENZA TEMPO";

/*	dbs	*/

char *dballoci="Allocati";
char *dballocpointi="puntatore";
char *dballocfailedi="Fallita allocazione";
char *notenmemi=" Memoria  non sufficiente";

char *dbs_readingi="LETTURA DBS               ";
char *dbs_writingi="SCRITTURA DBS             ";

/*	help rtdebug	*/

char * exitmemi="\nQ Uscita";
char * esamemi="\nE Esam. mem";
char * dummemi="\nD Dump mem";
char * dusmemi="\n\n Dump Spec";

/* tipi di punti */

char *tipoani[]={
                " AN. ACQ  ",
                " AN. CAL  ",
                " AN. CALNS",
                " AN. DIA  ",
                " AN. OUT  "
              };
char *tipodii[]={
                " DI. ACQ  ",
                " DI. CAL  ",
                " DI. CALNS",
                " DI. DIA  ",
                " DI. OUT  "
              };

char *orgi="  ORGANO  ";

// usata da modifica

char *sa_si="SIC. ALTA";
char *sb_si="SIC. BASSA";
char *ca_si="COND. ALTA";
char *cb_si="COND.BASSA";

char *stato_0i="STATO  0";
char *stato_1i="STATO  1";

// MANDB.INC

char *operazionii="[ESC] PER USCIRE - [M] PER MODIFICA";
char *quale_misurai="NUMERO DELLA MISURA DA MODIFICARE:"; 
char *istruzionei="INSERISCI I PUNTI - [ESC] PER TERMINARE ";
char *nome_puntoi="  NOME PUNTO : ";
char *non_accettoi="MISURA NON ACCETTABILE - [CR] PER CONTINUARE";

// MODFAN.INC

static char *valori_flagi="MODIFICA VALORI [V] O FLAG [F] PER USCIRE [CR] ? " ;
static char *status_flagi="MODIFICA STATO [S] O FLAG [F] PER USCIRE [CR] ? " ;
static char *nuovo_valorei="NUOVO VALORE : ";

//MODFDI.INC

static char *inv_comi="INVIO COMANDO [I] PER USCIRE [CR] ? ";

// stringhe per libro giornale

char *intes_1i=
   "    DATA         ORA        SIGLA             DESCRIZIONE          TIPO ALLARME  UNIT.MIS    RIFERIMENTO    VALORE        " ;
char *intes_2i=
   "                                                                                STATO.ATTU.  STATO PREC.                   " ;

char *intar_1i=
" ZI GG HH-MM-SS   SIGLA                DESCRIZIONE        TIPO ALLARME    STATO     SOGLIA" ;

char *intel_1i=
"    SIGLA              DESCRIZIONE                                                  STATO              " ;

char *intel_2i=
"    SIGLA              DESCRIZIONE    UN.DI MIS.  VALORE " ;

char *intel_3i=
"    SIGLA              DESCRIZIONE    UN.DI MIS. ALT.SIC. ALT.CON. BAS.CON. BAS.SIC. VALORE" ;

char *st_alpagei="  ALLARMI PAGINA N.  ";

char *s_tipui[]={
		"  ANAL.ACQUISITI    ", 
		"  ANAL.CALCOLATI    ",
		"ANAL.CALC.NON STAN. ",
		"ANAL. DI DIAGNOSTICA",
		0,0,
		" DIGITALI  ACQUISITI",
		" DIGITALI  CALCOLATI",
		"DIG.CALCOL.NON STAN.",
		"DIG. DI DIAGNOSTICA ",
		0,0,
		"      ORGANI        "}; 
char *s_tieli[]={
		" FUORI SCANS.",
		"    FORZATI  ",
		" IN ALLARME  ",
		" IN ALLARME  ",
		"SOGL. VARIATE",
		"NON ATTENDIB."};

char *point_ti="PUNTI ";


/* titoli in inglese 
*/

char *rcest1uk="             S O E    P R I N T             ";
char *rcest3uk="  Prg   hh:mm:ss,mil Cab.    Tag   Class   Description       Val Status";
char *rcest4uk=" ***   TRIGGER  EVENT   *** ";
char *rcest5uk=" ***    S O E   FINISHED     *** ";
char *rcedateuk="Date :";
char *rcetimeuk="Time:";
char *rceRCEuk="-SOE";

/*	archivi */

char *arc_numberuk="HISTORIC N.";
char *arc_stampatouk="  PRINTED AT  ";
char *arc_erroreuk="BAD HISTORIC PRINT REQUEST - INCORRECT DATE ";

/*	dbs	*/

char *dballocuk="Allocating";
char *dballocpointuk="pointer";
char *dballocfaileduk="Memory allocation failed";
char *notenmemuk="Not enaugh memory";


char *dbs_readinguk="DBS LOADING               ";
char *dbs_writinguk="DBS STORING               ";

/*	help	rtdebug	*/

char * exitmemuk="\nQ Exit";
char * esamemuk="\nE Mem.Exam";
char * dummemuk="\nD Mem.Dump";
char * dusmemuk="\n\n Spec.Dump";

char *tipoanuk[]={
                " AN. INP. ",
                " COMP. AN.",
                " COM.NS.AN",
                " AN. DIAG.",
                " AN. OUT  "
              };
char *tipodiuk[]={
                " DIG. INP.",
                " COMP. DIG",
                " COM.NS.DI",
                " DI. DIAG ",
                " DI. OUT  "
              };
static char *sa_suk="HIGH HIGH";
static char *sb_suk="LOW LOW ";
static char *ca_suk="HIGH    ";
static char *cb_suk="LOW     ";

// AD USO DI MANDB

// INTESTDI.INC

char *stato_0uk="STATUS  0";
char *stato_1uk="STATUS  1";

// INTESTOR.INC

char *orguk="  DEVICE  ";

// MANDB.INC

char *operazioniuk="[ESC] TO ESCAPE - [M] TO MODIFY";
char *quale_misurauk=" TAG NUMBER TO MODIFY :"; 
char *istruzioneuk="POINT TAG  - [ESC] TO END        ";
char *nome_puntouk="  POINT TAG  : ";
char *non_accettouk="INVALID POINT TAG [CR] TO CONTINUE      ";

// MODFAN.INC

static char *valori_flaguk=" VALUE [V]   FLAG [F] - [CR]  END   ? " ;
static char *status_flaguk=" STATUS [S]  FLAG [F] - [CR] END   ? " ;
static char *nuovo_valoreuk=" VALUE  : ";

//MODFDI.INC

static char *inv_comuk="SEND COMMAND [I] TO END [CR] ? ";

// stringhe per libro giornale

char *intes_1uk=
	"     DATE       TIME        TAG               DESCRIPTION           ALARM TYPE   UNIT        REFER.     VALUE             " ;
char *intes_2uk=
	"                                                                            ACT. VALUE   OLD VALUE                      " ;

char *intar_1uk=
" ZI DD MM-HH-SS    TAG                 DESCRIPTION        ALARM TYPE      VALUE     REFER." ;

char *intel_1uk=
"     TAG               DESCRIPTION                                                  VALUE              " ;

char *intel_2uk=
"     TAG               DESCRIPTION       UNIT     VALUE  " ;

char *intel_3uk=
"     TAG               DESCRIPTION       UNIT   HIGHHIGH    HIGH     LOW   LOWLOW    VALUE " ;

char *st_alpageuk="  A L A R M  PAGE N. ";

char *s_tipuuk[]={
		"  ANALOG INPUT      ",  
		"  COMPUTED ANALOG   ",  
		"COMP. NON ST. ANALOG",  
		" ANALOG DIAGNOSTIC  ",  
		0,0,
		"  DIGITAL INPUT     ",
		"  COMPUTED DIGIT    ",
		"COMP. NON ST. DIGIT ",
		" DIGITAL DIAGNOSTIC ",
		0,0,
		"       DEVICE       "}; 
char *s_tieluk[]={
		" OUT OF SCAN ",
		"   FORCED    ",
		"   ALARM     ",
		"   ALARM     ",
		"MODIF. LIMITS",
		"INVALID STAT."};

char *point_tuk="POINT ";

/* variabili esportate */


char *rcest1;			 	// RCE
char *rcest3;
char *rcest4;
char *rcest5;
char *rcedate;
char *rcetime;
char *rceRCE;

char *arc_number;
char *arc_stampato;
char *arc_errore;

char *exitmem;
char *esamem;
char *dummem;
char *dusmem;

char *dballoc;
char *dballocpoint;
char *dballocfailed;
char *notenmem;

char *dbs_reading;
char *dbs_writing;

char **tipoan;
char **tipodi;

char *sa_s;
char *sb_s;
char *ca_s;
char *cb_s;

// usati da MANDB

char *stato_0;
char *stato_1;

char *org;

char *istruzione;
char *nome_punto;
char *non_accetto;
char *operazioni;
char *quale_misura;

char *valori_flag;
char *nuovo_valore;

char *status_flag;
char *st0s; 
char *st1s; 
char *inv_com;

char *valori_flag;
char *nuovo_stato;

char *intes_1;
char *intes_2;
char *intar_1;
char *intel_1;
char *intel_2;
char *intel_3;
char *st_alpage;

char **s_tipu=s_tipui;
char **s_tiel=s_tieli;

char *point_t;

void striuk(char *utente)
   {
   /* Determina le stringhe di intestazione della stampante in funzione dell'utente */

   if(!strcmp(utente,"SELTA"))
      {
      strcpy(intes_1i,
     "  DATA E ORA         GIORNO/ORA      SIGLA      DESCRIZIONE             TIPO ALL. UNIT.MIS   RIFERIMENTO    VALORE             ");
      strcpy(intes_2i,
     "  SUPERVISIONE       PERIFERICO                                                  STATO ATTU. STATO PREC.                       ");
      }
   if(getenv("INGLESE") !=NULL)
      {
      INGLESE=1;
		rcest1=rcest1uk;
		rcest3=rcest3uk;
		rcest4=rcest4uk;
		rcest5=rcest5uk;
		rcedate=rcedateuk;
		rcetime=rcetimeuk;
		rceRCE=rceRCEuk;

		arc_number=arc_numberuk;
		arc_stampato=arc_stampatouk;
		arc_errore=arc_erroreuk;

		exitmem= exitmemuk;
		esamem= esamemuk;
		dummem= dummemuk;
		dusmem= dusmemuk;

      dballoc      =dballocuk;
      dballocpoint =dballocpointuk;  
      dballocfailed=dballocfaileduk; 
      notenmem=notenmemuk;
		dbs_reading=  dbs_readinguk;
		dbs_writing=  dbs_writinguk;

		tipoan=		  tipoanuk;
		tipodi=		  tipodiuk;

      sa_s=         sa_suk;
      sb_s=         sb_suk;
      ca_s=         ca_suk;
      cb_s=         cb_suk;

      stato_0=        stato_0uk;
      stato_1=        stato_1uk;

      org=            orguk;

		operazioni=		 operazioniuk;
		quale_misura=	 quale_misurauk;
      istruzione=     istruzioneuk;
      nome_punto=     nome_puntouk;
      non_accetto=    non_accettouk;

      valori_flag=    valori_flaguk;
      status_flag=    status_flaguk;
      nuovo_valore=   nuovo_valoreuk;

      valori_flag=    valori_flaguk;
      st0s=           stato_0uk; // risparmio
      st1s=           stato_1uk; 
      inv_com=        inv_comuk;

      valori_flag=    valori_flaguk;
      nuovo_stato=    nuovo_valoreuk;

      intes_1= intes_1uk;
      intes_2= intes_2uk;
      intar_1= intar_1uk;
      intel_1= intel_1uk;
      intel_2= intel_2uk;
      intel_3= intel_3uk;
      s_tipu=  s_tipuuk;
      s_tiel=  s_tieluk;
		
		st_alpage=st_alpageuk;

      point_t=point_tuk;
      }
   else
      {
      INGLESE=0;
		rcest1=rcest1i;
		rcest3=rcest3i;
		rcest4=rcest4i;
		rcest5=rcest5i;
		rcedate=rcedatei;
		rcetime=rcetimei;
		rceRCE=rceRCEi;

		arc_number=arc_numberi;
		arc_stampato=arc_stampatoi;
		arc_errore=arc_errorei;

		exitmem= exitmemi;
		esamem= esamemi;
		dummem= dummemi;
		dusmem= dusmemi;

      dballoc      =dballoci;
      dballocpoint =dballocpointi ;
      dballocfailed=dballocfailedi;
      notenmem=notenmemi;


		dbs_reading=  dbs_readingi;
		dbs_writing=  dbs_writingi;

		tipoan=		  tipoani;
		tipodi=		  tipodii;

      sa_s=         sa_si;
      sb_s=         sb_si;
      ca_s=         ca_si;
      cb_s=         cb_si;

      stato_0=        stato_0i;
      stato_1=        stato_1i;

      org=            orgi;

		operazioni=		 operazionii;
		quale_misura=	 quale_misurai;
      istruzione=     istruzionei;
      nome_punto=     nome_puntoi;
      non_accetto=    non_accettoi;

      valori_flag=    valori_flagi;
      status_flag=    status_flagi;
      nuovo_valore=   nuovo_valorei;

      valori_flag=    valori_flagi;
      st0s=           stato_0i; // risparmio
      st1s=           stato_1i; 
      inv_com=        inv_comi;

      valori_flag=    valori_flagi;
      nuovo_stato=    nuovo_valorei;

      intes_1= intes_1i;
      intes_2= intes_2i;
      intar_1= intar_1i;
      intel_1= intel_1i;
      intel_2= intel_2i;
      intel_3= intel_3i;
      s_tipu=  s_tipui;
      s_tiel=  s_tieli;

		st_alpage=st_alpagei;

		point_t=point_ti;
      }
   }
