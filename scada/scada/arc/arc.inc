/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
        Arc.inc

        Contiene le tabelle e i descrittori relativi al task 
        real time Archivi.
        Include il file arcdef.inc

        9 Marzo 1992    Rel. 0.1        Fc.
*/
#include "defpub.h"


#include "pscserr.inc"
#include "arcdef.inc"
#include <all_1.h>
#undef long 
#define long int
/*
        definizione tabelle descrittori archivi
        Lo spazio relativo alle misure associate all'archivio viene
        allocato dinamicamente (vedi Arcopen.c)
*/
typedef struct {        HEAD_ARC hea;
                        PUNTDBS  *mis;
                        long     offset;        // offset per scrittura nel file
                        short    canc;          // indice ultimo file cancellato
                } PARCDES;
pub PARCDES arcdes[n_arc];
/*
        definizione data base di archiviazione normale/veloce e lenta
        I data base vengono allocati dinamicamente in base all'esistenza
        dell'archivio ed al numero di misure associate
        Se l'archivio non e' installato il valore di arcdbs[] e' 0
*/
typedef struct head_camp {
			 char tipo;	   // tipo di archivio (1=N, 2=V)
			 char n_mis;	   // numero effettivo misure in archivio
			 short n_misvel;   // num. mis.campionate velocemente
			 char giorno;
			 char mese;
			 short anno;
			 char ore;
			 char minuti;
			 short secondi;
			 short spare;
			 } HEAD_CAMP;
#define l_hcamp sizeof(HEAD_CAMP)

typedef struct anval {	     	// caso archiviazione normale per analogici
		   float val;	// valore campione
		   char flag;	// flag campione
		   char imis;	// indice misura all'interno del record di FDARC.RTF
		  } ANVAL;
typedef struct anave {	     	// caso archiviazione lenta per analogici
		   float med;	// media campioni attuale
		   char ctot;	// numero totale campioni attuale
		   char cfsfa;	// numero campioni non validi (fuori scans, fuori att) attuale
		  } ANAVE;
typedef union an {	     	// caso analogico
		   ANVAL camp;
		   ANAVE ave;
		  } AN;

typedef struct di {		// caso digitali
		  short dtipo;
		  short f_s;    // flag e stato digitale
                  char  dspare1;
                  char  imis;
		  } DI;

typedef struct or {	        // caso organi
		  short otipo;
		  short f_s;    // flag e stato organo
                  char  ospare1;
                  char  imis;
		  } OR;

typedef union datdbs { 
		       AN a;
		       DI d;
		       OR o;
		      } DATDBS;
					      
typedef struct {        HEAD_CAMP hea;
                        DATDBS    dbs[n_misarc];
                } ARC_DBS;
pub ARC_DBS  *arcdbsN[n_arc],*arcdbsL[n_arc];
/*
        definizione header record di memorizzazione
*/
pub HEAD_CAMP hea_camp;
/*
        definizione tabelle di timer per la memorizzazione su disco
        distribuita dei campioni  (esiste un timer per archiviazione
        normale/veloce e un timer per archiviazione lenta)
        Al massimo la scrittura su disco viene posticipata di 2 minuti
        (ArcRit)
        Ad ogni periodo di archiviazione minimo (ArcMin) vengono scritti
        su disco in base al valore di arc_toc
*/
#define ArcRit  120             //      massimo ritardo archiviazione
#define ArcMin  5               //      minimo periodo archiviazione

typedef struct {
        long     tin;            //      time-out calcolato per archiviazione
        long     tco;            //      time-out corrente  
        } ARTIME;

pub ARTIME t_N[n_arc], t_L[n_arc];  
/*
        definizione tabelle con nomi file di archivio
        I nomi sono lunghi 8+4 caratteri, la tabella
        e' dimensionata in base al numero massimo effettivo
        di file che formano l'archivio
*/
#define  l_arcnome      (8+3+1+1)         // 8 nome + '.' + 3 (estensione) + \0
typedef struct {
                 char nome[l_arcnome];  // 
                } ARCNOME;
pub struct {
         short use;                     // indice file in uso
         ARCNOME *arc;                  // puntatore ai nomi dei file
        } arcnome[n_arc];
/*
        definizione coefficiente accettabilita' valore accumulo
*/
#define coefm_fa       0.4
/*
        definizione della struttura contente indirizzo e dimensionamento
        del buffer da utilizzare per le operazioni di I/O di ricerca
        dati di archivio
*/
pub struct {      ARC_DBS *indir;            // indirizzo buffer I/O
                short dim;               // dimensionamento
                 char *vis;              // indirizzo buffer per messaggi trend storici       
                short vdim;              // dimensionemento
        } arcsort;
/*
        funzione per il calcolo del tempo di campionamento
        Vengono presi in considerazione: giorno, ora minuti e secondi
        Anno e mese sono gia' selezionati dal nome del file
*/
#define LMIN     60L
#define LORA     (60L*LMIN)
#define LGIO     (24L*LORA)

#define tsec(sec,min,ora,giorno)       sec+min*LMIN+ora*LORA+giorno*LGIO
/*
        funzione per il calcolo del tempo di campionamento in floating
        Vengono presi in considerazione: secondi, minuti, ora, giorno
        mese ed anno (su due cifre)
*/
#define FMIN     60.
#define FORA     (60.*FMIN)
#define FGIO     (24.*FORA)
#define FMES     (31.*FGIO)
#define FANN     (12.*FMES)

#define fsec(sec,min,ora,giorno,mese,anno)   sec+min*FMIN+ora*FORA+giorno*FGIO+mese*FMES+anno*FANN
/*
        dichiarazione della mail box utilizzata per archiviare
        lock fra memorizzazione e ricerca dati
*/
extern short mbox_archiv;
/*
        dichiarazione path per la creazione file di archivio
        (non necessarriamente devono risiedere nel direttorio
        conf[RTF])
        Il campo viene inizializzato nella routine arcopen
*/
pub char arcpath[255];
#include <all_16.h>
#undef long 
#define long long
