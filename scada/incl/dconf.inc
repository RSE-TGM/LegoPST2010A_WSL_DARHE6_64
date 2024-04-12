/**********************************************************************
*
*       C Header:               dconf.inc
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Sep 17 15:30:43 1998 %
*
**********************************************************************/
/*
 *    CONF.INC contiene le definizioni relative al file di descrizione
 *           della configurazione di default.
 */
#include <all_1.h>
#include "defpub.h"
#include <fileop_names.h>

#define N_ENV  9      /* numero di variabili di environment da settare   */
#define l_path 255    /* lunghezza del path specificabile per ogni var.
                        di environment.                                 */


/* Numero di utenti ISA che possono accedere a SCADA. */
/* Attenzione!! Questo parametro deve essere uguale a NCHAN_ISA */
/* definito nel file CONFDEF.INC per i moduli Assembler. */

#define NCHAN_ISA       4       // Numero di utenti ISA

pub     char conf[N_ENV][l_path];
/*
        Posizione delle definizioni delle var. di env. in CONF
*/
#define EXE  0
#define COL  1
#define EDT  2
#define RTF  3  
#define MMI  4
#define PAG  5
#define DEV  6		// device per installazione pagine solo disco/ disco + seriale
#define UTEN 7		// device per installazione pagine solo disco/ disco + seriale
#define EDIT 8		// tipo di editor
             
#define rec_conf sizeof (conf)

#define FPUNTI  0
#define FPAGINE 1
/*
	definizione record di header che precede i dati
	del file fdbdp.rtf
*/
#define max_ab_inet     32                      // n. massimo nodi da abilitare

struct sdidate_t {
	unsigned char day;		/* 1-31 */
	unsigned char month;		/* 1-12 */
	unsigned short year;        /* 1980-2099 */
	unsigned char dayofweek;	/* 0-6, 0=Sunday */
	};

struct sditime_t {
	unsigned char hour;	/* 0-23 */
	unsigned char minute;	/* 0-59 */
	unsigned char second;	/* 0-59 */
	unsigned char hsecond;	/* 0-99 */
	};

#define d_release 	6
#define d_nome	  	10
#define d_descrizione 	24

typedef struct db_header {
       struct sdidate_t data;
       struct sditime_t ora;
		char	nome[d_nome];
		char	descrizione[d_descrizione];
		char	release[d_release];
		short	dimaa;
		short	dimas;
		short	dimac;
		short  	dimad;
		short	dimao;
		short	dimda;
		short	dimds;
		short	dimdc;
		short	dimdd;
		short	dimdo;
		short	dimor;
		short	dimst;
		char	fpunti;			// = 1 modificati su config database
		char	fpagine;		// = 1 modificato su config mmi.dsk
		char 	subuten[10];		// nome di sottoutente
                char    inet_nodo;              // n. nodo stop
                char    inet_rms;               // master o slave di rete
                char    inet_nms;               // nodo master o slave
                char    inet_ab[max_ab_inet];   // nodi da bailitare
			} DB_HEADER;	

#define ldb_header	512			// viene riservato un
						// blocco disco

/*
	definizione parametri per chiamata a rwdb parte real time
	per scritture parziali data base
*/
#define	wr_fl	  99		// flush periodico dbs ad dd e as
#define wr_header 98            // scrittura header fdbdp

#include <all_16.h>
