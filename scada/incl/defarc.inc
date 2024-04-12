/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/* ->DEFARC.INC
 *    Definizione strutture utilizzate nel task archivi.
 */
/*
	Definizione header del record che verr… memorizzato per
        ogni archivio.
*/
#define CIRCOLARE 1
#define LINEARE 2
typedef struct head_camp {
			 short anno;
			 char mese;
			 char giorno;
			 char ore;
			 char minuti;
			 short secondi;
			 } HEAD_CAMP;
#define l_hcamp sizeof(HEAD_CAMP)
/*
	Definizione ( e sottodefinizioni) record di registrazione su archivio
*/

typedef struct an {
		   float val;
		   short flag;
		  } AN;
typedef struct di {
		  short s[2];
		  short f_s;    // flag e stato digitale
		  } DI;
typedef struct or {
		  short s[2];
		  short f_s;    // flag e stato organo
		  } OR;

typedef union datdbs { short s[3];
		       AN a;
		       DI d;
		       OR o;
		      } DATDBS;
								     
typedef struct arc_rec {
			HEAD_CAMP h;
 			DATDBS misura[n_tmis];
			} ARC_REC;
#define l_arcrec sizeof(ARC_REC)

typedef struct arc_buf {
		       short iarc;  // indice archivio (-1 tappo )
		       ARC_REC r;   // record da scrivere sull'archivio
		       } ARC_BUF;
/*
	Strutture utilizzate nel file di descrizione ASCII archivio
*/

// descrittore punto acquisito in archivio

typedef struct descr_parc {
			  char sigla[10];
			  char descr[24];
			  char st_umis[8];
			  char stato1[8];
			  } DESCR_PARC;

// record file descrittore archivio (tutti i campi sono in ASCII

typedef struct arc_descr {
			 char indice[2];	// indice archivio in ASCII
			 char tipo[3];		// b , L/C/E , b
			 char freq[3];		// frequenza
			 short spare[12];
			 DESCR_PARC p[18];	// 18 punti in archivio
			 } ARC_DESCR;

typedef struct frequen {
			char string[4];	// decodifica in ascii
			long val;	// valore short corrispondente
			} FREQUEN;

typedef struct numcamp {
			char strfr[4];  // decodifica in ascii
			char strdu[4];  // decodifica in ascii
			short val;      // valore short corrispondente
			} NUMCAMP;

#define l_desarc sizeof(ARC_DESCR)

#define n_tipo 4
#define n_freq 10
#define combin 24
#define n_flag 8
#define camp_def 720
/*
	periodo minimo di archiviazione
*/
#if defined (PER_ARCHIV)
#else
#define PER_ARCHIV	5
#endif
