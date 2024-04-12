/**********************************************************************
*
*       C Header:               sdi_conf.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed May 28 14:36:28 1997 %
*
**********************************************************************/
/*
   modulo sdi_conf.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)sdi_conf.h	5.1
*/
#define FPUNTI  0
#define FPAGINE 1
/*
	definizione record di header che precede i dati
	del file fdbdp.rtf
*/
#define max_ab_inet     32              /* n. massimo nodi da abilitare */

struct sdidate_t {
	unsigned char day;		/* 1-31 */
	unsigned char month;		/* 1-12 */
	unsigned short year;		/* 1980-2099 */
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
		char	fpunti;		/* = 1 modificati su config database */
		char	fpagine;	/* = 1 modificato su config mmi.dsk  */
		char 	subuten[10];	/* nome di sottoutente */
                char    inet_nodo;      /* n. nodo stop */
                char    inet_rms;       /* master o slave di rete */
                char    inet_nms;       /* nodo master o slave */
                char    inet_ab[max_ab_inet];   /* nodi da abilitare */
			} DB_HEADER;	

#define ldb_header	512		/* viene riservato un
					   blocco disco */
DB_HEADER h_db;  /* definisce una variabile atta a contenere
                    l'header del data-base */

/* Per oggetto Cai ed oggetto OlTree */
#define ALLARM_CAI 'A'
#define WARNING_CAI 'W'
#define TOLERANCE_CAI 'T'
#define SIMUL_CAI 'S'
#define MANUAL_CAI 'M'
#define FAULT_CAI 'F'
#define NULL_CAI  '0'

#define ALL_A_MASK      0x0101 /* allarm A pending or archived */
#define ALL_W_MASK      0x0202
#define ALL_T_MASK      0x0404
#define ALL_S_MASK      0x0808
#define ALL_M_MASK      0x1010
#define ALL_F_MASK      0x2020
#define ALL_N_MASK      0x4040

#define ALL_A_PEN_MASK	0x0001 /* allarm A pending */
#define ALL_W_PEN_MASK      0x0002
#define ALL_T_PEN_MASK      0x0004
#define ALL_S_PEN_MASK      0x0008
#define ALL_M_PEN_MASK      0x0010
#define ALL_F_PEN_MASK      0x0020
#define ALL_N_PEN_MASK      0x0040

