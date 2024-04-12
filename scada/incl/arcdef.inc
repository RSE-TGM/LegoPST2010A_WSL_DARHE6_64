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
	ARCDEF.INC
	Contiene le definizioni delle strutture utilizzate per la gestione
	degli archivi (configurazione e real-time).

	Creazione:  Antecedente 21.02.92  -  Rel. 1.06

	Revisioni:  GM.Furlan  -  28.02.92  -  Rel. 2.00
	            Modifiche delle strutture dei file, conseguenti 
	            all'introduzione della gestione degli archivi "veloci". 

                    Fc. 7 Novembre 1994 inserito condizionamento per gestione
                    64 archivi come richiesto da Tavazzano - CISE

*/
#include "defpub.h"
#include <all_1.h>
#include <tag.h>
#undef long 
#define long int
#if defined (ARC64)
#define n_arc 64
#else
#define n_arc  8	// numero massimo di archivi
#endif

#define n_farc 32	// numero massimo di file per singolo archivio.
#define n_misarc 83	// numero massimo misure archiviabili per singolo archivio.
#define g1tipar 25	// tipo archivio
#define M_Tot 1 	// memorizzazione totale
#define M_Par 2		// memorizzazione parziale
/*
        definizione tipi di archivi possibili
*/
#define arc_Norm     1       //      archivio normale 
#define arc_Len      2       //      archivio lento
#define arc_Vet	     3	     //	     archivio vettoriale

// Codici di trigger

#define trig_s    1	// sicurezza 
#define trig_sc   2	// sicurezza-conduzione
#define trig_c    3	// conduzione
#define trig_off 20	// offset trigger digitali: trigger digitali dal 21ø in poi
#define trig_sl  21	// variazione digitale 0/1

// 1. FILES DESCRITTORE "ASCII": DE_ARCxx.RTF

#define l_indice 2
#define l_freq 3
#define l_dur 3
#define l_fil 2

// descrittore punto acquisito in archivio
typedef struct descr_parc {
			  char sigla[SCD_SIGLA];
			  char descr[SCD_DESCRIZIONE];
			  char st_umis[SCD_UNIMIS];
			  char stato1[SCD_UNIMIS];
			  } DESCR_PARC;

// record file descrittore archivio (tutti i campi sono in ASCII)
typedef struct arc_descr {
			 char indice[l_indice];	// indice archivio in ASCII
			 char descr[SCD_DESCRIZIONE];	// descrizione arch.
			 char tipo;		// tipo archivio (N/L)
			 char spare0;
			 char freq_N[l_freq];	// frequenza arch. N
			 char spare1;
			 char dur_N[l_dur];		// durata arch. N
			 char spare2;
			 char n_fil_N[l_fil];	// numero file arch. N
			 char freq_L[l_freq];	// frequenza lenta arch. L
			 char spare3;
			 char freq_VL[l_freq];	// frequenza veloce (normale) arch. L
			 char spare4;
			 char dur_L[l_dur];		// durata arch. L
			 char spare5;
			 char n_fil_L[l_fil];	// numero file arch. L
			 char trigga;		// codice trigger analogico
			 char triggd;		// codice trigger digitale
			 char t_mem;		// tipo di memorizzazione (T/P)
			 char spare6;
			 DESCR_PARC p[n_misarc];	// 83 punti in archivio
			 } ARC_DESCR;

#define l_desarc sizeof(ARC_DESCR)


// 2.	Struttura descrittore archivio: record del file FDARC.RTF

// 	header del record 
typedef struct head_fdarc {
		        char iarc;      // indice archivio
 			char tipo;      // tipo dell'archivio (1=N, 2=L)
		        char flag;      // flag vari
			char t_mem;	// tipo di memorizzazione: 1=Totale;2=Parziale
		        char c_freqN;   // codice frequenza normale (=veloce per archivi L)
		        char c_freqL;   // codice frequenza lenta
			long freqN;     // frequenza normale (=veloce per archivi L) in secondi
			long freqL;     // frequenza lenta in secondi (arch. L)
		        short c_dur;	// codice durata archivio (0=08H,1=01G,2=07G,3=01M) 
			short n_mis; 	// numero effettivo di punti in archivio
			short n_file;   // numero max files costituenti arch.
			short p_st;     // punt. a dig: stato arch.
			short p_nc;     // punt. a ana: numero di camp.
			short p_fc;     // punt. a ana: numero file corr.
			short p_nfmax;	// punt. a ana: numero max file d'archivio
			short p_1f;   	// punt. a ana: 1øfile dei campioni
			char trigga;	// trigger ana:1=Sic;2=Sic+Cond;3=Cond;
			char triggd;	// trigger dig:1=Var 0/1;
			short p_pd;     // punt. a ana: periodo e durata per pagine video
			} HEAD_ARC;
#define l_harc sizeof(HEAD_ARC)

//	informazioni punti in archivio
typedef struct puntdbs	{  short ext;
			   short punt;
			} PUNTDBS;

// record completo			     
typedef struct rec_fdarc {
			HEAD_ARC head;		// header
			PUNTDBS mis[n_misarc]; // punt. a misure da archiviare
			} DES_ARC;
#define rec_fdarc sizeof(DES_ARC)



// 3. strutture tabelle di decodifica

#define n_freq 11       // num. freq. previste per archivi 
#define n_dur  4 	// num. massimo durate
#define n_flag 8	// num. massimo flag
#define n_comb 14  	// num. combinazioni periodo\durata per archivi normali


typedef struct frequen { 	// tabella decodifica frequenze (ARCTAB.INC)
			char string[4];	// codifica in ascii
			long val;	// decodifica in secondi
			} FREQUEN;

typedef struct per_dur { 	// tabella controllo periodo/durata (ARCTAB.INC)
			char per[4];	// periodo in ascii
			char dur[4];	// durata in ascii
			} PER_DUR;



#include <all_16.h>
#undef long 
#define long long
