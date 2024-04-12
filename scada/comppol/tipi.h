/*
   modulo tipi.h
   tipo 
   release 1.1
   data 6/10/96
   reserved @(#)tipi.h	1.1
*/
/********************************************************************
*			   File TIPI.H 				                                *
*            							                                   *
*	Contiene tutte le variabili comuni  e le inizializzazioni        *
********************************************************************/

#include "all_1.h"

#define  N_ENTRY	 128	// n. massimo entry definibili 
								// init, term, periodic, event, rclk, lclk
								// rdbclk, ldbclk + 120 per key

#define 	NMXOPCMP  6		/* Numero opzioni per attivare il compilatore */

#define 	NUM_ISTR  133  /* Numero di nomi istruzioni linguaggio    */
#define 	NU_ISTRS  16   /* Numero di nomi istruzioni non operative */
#define 	COISLOOP  124  /* Codice operativo istruzione LOOP */
#define 	COISRLOOP 134  /* Codice operativo istruzione REPLOOP */

#define 	NUM_TIPVAR 16  /* Numero di tipi per DEFINE/DATA */
#define 	NUM_TIPLK  9   /* Numero di tipi per istr. LINK */
#define 	NUM_TIPRD  9   /* Numero di tipi per istr. READ */
#define 	NUM_TIPWR  12  /* Numero di tipi per istr. WRITE */
#define  NUM_TIPWR_EXT 18  /* Numero tipi estesi GBxy per Read e Write */
#define  NUM_TIPWR_MAX 32  /* n. massimo variabili per tipo */

#define 	LUNGLISTA   40
#define 	MAXIF	   	20
#define 	MAXCASE     10
#define 	MAXLOOP     10
#define 	MAXISTR	 2000
#define 	MAX_EST	  35
#define 	LUNG_VAR   40
#define 	MAX_VAR    500
#define 	EF_LUNGVAR 11

/*
	DEFINE dei tipi di variabili di data base locale
*/
#define tanalogico 0
#define tdigitale  1
#define torgano    2
#define treale     3
#define tintero    4
#define tlogico    5
#define tdig_out   6
#define tstringa   7
#define tpuntan    9
#define tpuntdi   10
#define tpuntor   11
#define tpuntcom  12
#define tpdesblk  13
#define tpuntst   15

#define tanls		19
#define tanlc		20
#define tanhc		21
#define tanhs		22

struct variabili {
			char nome[LUNG_VAR]; /* nome della variabile */
			int tipo;      /* tipo della variabile */
			int indirizzo; /* indirizzo nel D.B.   */
			int nriga_input; /* riga file di input  */
			short codicevar;   /* codice della variabile
									  1 variabile LINK
									  2 variabile DEFINE
									  3 variabile DATA
									  4 variabile istruzione CASE
									  5 variabile istruzione SUBROUTINE */
			char codicelk;		/* codifica tipo istruzione LINK */
			char *valcost;
			int flag;      /* vale 1 se tipo gruppo
					  				vale 0 se altro tipo
				          		vale 2 se var. in subr. */
			int bal;       /* serve per bilanciare */
			struct variabili *left,*right;
		} *testa;

struct symb_list  {
			char stringa[LUNGLISTA];
			int codice_ogg;
			int tipovar;    /* -1 se label o par. chiavi */
			int dimvar;
			int riga_def;
			int tipocodice; /* 0 --> label
					   1 --> variabili e costanti
					   2 --> par. chiavi
 				   3 --> var. di subr. */
			struct symb_list *destra;
			struct symb_list *sinistra;
		} *inizio;

struct etichette {
			int nomelabel;
			int vallabel;
			struct etichette *prox;
		} *cima;

/* Definizione delle opzioni di attivazione del compilatore */

char *stropcmp[NMXOPCMP];

short utiopcmp[NMXOPCMP];

              /* nomi delle istruzioni */

char *par_chiav[NUM_ISTR];

char *altre_istr[NU_ISTRS];

char *tipovar[NUM_TIPVAR];

char *tipistlk[NUM_TIPLK];

short tipvarlk[NUM_TIPLK];

short codistlk[NUM_TIPLK];


char *tipistrd[NUM_TIPRD];

short codistrd[NUM_TIPRD];

short tvdblrd[NUM_TIPRD];

short tvdbsrd[NUM_TIPRD];


char *tipistwr[NUM_TIPWR];

short codistwr[NUM_TIPWR];

short tvdblwr[NUM_TIPWR];

short tvdbswr[NUM_TIPWR];


int wordpar_ch[NUM_ISTR];

char *estensioni[MAX_EST];

int val_est[MAX_EST][5];

#include "all_16.h"
