/*
   modulo CreateLOG.h
   tipo 
   release 2.5
   data 6/7/96
   reserved @(#)CreateLOG.h	2.5
*/

#include "all_1.h"

#define lLogData        20
#define lLogDesc        2048
#define lLogNome        13
#define lLogszBuffer     512
#define szFormatoData "%02d:%02d:%02d %02d/%02d/%4d"

#define WORD	short
#define UINT	unsigned short
#define BOOL	short

#define g1tiptc   21      // tipo tabulati gestione
#define g1tiptg   22      // tipo tabulati caratteristiche
#define g1tipin   0x4E49  // corrispondente a IN  tipo include

// Definizione strutture e record per files associati ai tabulati
#define  n_tabu    32    // n. tabulati max. definibili
#define  l_nomtab  10    // lunghezza nome tabulato       	

// Tipi di variabili locali POL
#define b_analogico 0
#define b_digitale 1
#define b_organo 2
#define b_reale  3
#define b_intero 4
#define b_logico 5
#define b_stringa 7
#define b_pan           9
#define b_pdi           10
#define b_por           11
#define b_pdo           12              // comando digitale
#define b_pbl           13              // puntatore a blocco
#define b_pst           15

// Definizione file dizionario tabulati 
typedef struct s_diztab { char nome[l_nomtab] ;
                          short periodo ;
                        } S_DIZTAB ;
                        
#define rec_fdiztab sizeof(S_DIZTAB)
	 	
// Dimensioni massime in byte parte dati del programma di gestione tabulati
#define l_datab 2048   

// Struttura header file FTAB.
typedef struct s_htab   { short tip_dat ;
                          short arc_frq ;
                          short cicli ;
                          short spare ;	 
			} S_HTAB;
#define l_htab sizeof(S_HTAB)

// Caratteristiche del tabulato
#define PERIODICO		1
#define NON_PERIODICO	0 

#define DATBAS   1    // dati prelevati da data base
#define ARCHIVIO 2    // dati prelevati da archivio

// Offset all'interno di un record a cui inizia la sezione dati
#define off_dat l_htab
 			  
// Offset a cui inizia la sezione codice
#define off_cod (l_htab+l_datab)

// Struttura header parte codice di FTAB
#define nSpare 	  14
#define nEntryInt 48
#define N_MENU 	  12
typedef struct s_hcod {
      			short lung;		// lung. file oggetto
       			short percamp;		// periodo di campionamento
          		short spare[nSpare];	 
               		short entryI;		// entry init
               		short entry0;		// entry 0
               		short entry1;		// entry 1
		       	short entryT;		// entry term
		       	short entint[nEntryInt];// entry int 0 ... entry int 47
               		short menu[N_MENU];	
             	      } S_HCOD;
             	      
#define l_hcod sizeof(S_HCOD)
#define rec_ftab (l_htab+l_datab+l_codtab)

// HEADER del blocco DATI di FTAB.RTF
typedef struct head_datab {
			    short n_link;     	    // numero delle variabili di link
			    short l_data;     	    // occupazione totale in byte dei DATA
			    unsigned char n_point;  // numero costanti puntatori.
			    unsigned char spare;    // spare ?.
			    short camp;             // periodo di campionamento.
			  } HEAD_DATAB;
#define l_hdat sizeof(HEAD_DATAB)

// FTAB.RTF record generico
typedef struct s_log {
		       S_HTAB     htab;		    // proprieta' del tabulato
		       char       chDBL[l_datab];   // DBL
		       S_HCOD     hcod;		    // proprieta' del codice ed entry
		     } S_LOG;

// Dinensioni massime in byte parte codice del programma di gestione tabulati (== 3 kbyte)
#define l_codtab (6144-l_hcod)

// Struttura con le proprieta' del tabulato
typedef struct s_logprop {
			   char szNome[lLogNome];
			   int	iPeriodo;// Periodo del tabulato
			   BOOL bPeriodico;// Flag che indica se il tabulato e' periodico o meno
			   UINT nCicli;// Numero di volte che si deve eseguire il programma corpo del t.
			   UINT nAttesa;// Tempo di attesa in min. tra un ciclo e l'altro
			   char szData[lLogData];// Data di ultima modifica del tabulato
			   char szDesc[lLogDesc];// Descrizione del tabulato
			   float fVer;// Versione del tabulato
			   WORD wTipo;// Tipo del tabulato
                         } S_LOGPROP;

// Conversione del file POL
#define EXT_POL_IN          "tcr"
#define EXT_POL_OUT         ""
#define MAXRIGA 5000
#define DEFINE              "DEFINE"
#define DATA                "DATA"
#define LINK                "LINK"
#define UC_PA               "PA"
#define UC_PD               "PD"
#define UC_PO               "PO"
#define UC_PS               "PS"
#define UC_PC               "PC"
#define LC_PA               "pa"
#define LC_PD               "pd"
#define LC_PO               "po"
#define LC_PS               "ps"
#define LC_PC               "pc"
#define ENTRY_INIT          ";[ENTRY_INIT]"
#define ENTRY_INIT_ADD      "ENTRY INIT"
#define ENTRY_PERIODIC      ";[ENTRY_PERIODIC]"
#define ENTRY_PERIODIC_ADD  "ENTRY 0"
#define ENTRY_TERM          ";[ENTRY_TERM]"
#define ENTRY_TERM_ADD      "ENTRY TERM"

//	CODICE.AB
#define N_ENTRY	128
typedef struct s_codice {   
							short lung;
							short periodo;
							short spare[14];
							short entry[N_ENTRY];
							short menu[N_MENU];
						} S_CODICE;

// CODICE.MAP 
typedef struct s_map {		// struttura header Map
				short link_var;
				short define_var;
				short  gruppi;
				short  pointer;
				short data_var;
				  } S_MAP;  
	
#define DIM_LINK_VAR	14
#define DIM_DEFINE_VAR	14
#define SCD_SIGLA_CORTA 10

typedef	struct s_data {
			char	name[SCD_SIGLA_CORTA];	// nome del gruppo o della costante
			short	tipo;		// tipo della costante
			short	ind;		// indirizzo nel data base locale
		      } S_DATA;	

typedef	struct s_parLink {
			   char	name[SCD_SIGLA_CORTA];	// nome della variabile nel data base di sistema
			   short tDBL;		// tipo della variabile come definito nella lista parametri dell'istruzione PAG
			 } S_PARLINK;							
			
typedef struct s_healink {
			   short n_link;  	// n. variabili link
			   short n_pointer;	// n. costanti puntatore
			   short n_parLink;	// n. dei parametri Link definiti nelle istruzioni PAG
			   short spare[2];	// per possibili usi futuri
		  	  } S_HEALINK;
						                
typedef struct s_link {
			S_HEALINK hea;
			S_DATA    link;
		      } S_LINK;
						 						                
typedef struct s_pdbs	{
			  char tipo;
			  char ext;
			  short indice;
			} S_PDBS;							 									 
// Prototipi delle funzioni
int SistemaPol(char *);
static int legge_riga(FILE *, char *);
BOOL SetRecord(S_LOGPROP *logprop);
int LogCompila(S_LOGPROP *logprop);
int LogInstalla(S_LOGPROP *logprop);
void EliminaFileAppoggio(S_LOGPROP *logprop);
int Link(S_LOG *pLog, char *pCodeBuff,const char *pchNome);

void ToLower(char *szBuffer);
void ToUpper(char *szBuffer);

#include "all_16.h"
