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
        arcvis.inc

        Continene le strutture dei messaggi utilizzati per la visualizzazione
        dei dati di archivio


        27 Marzo 1992   rel. 1.0        Fc
*/
/*
        messaggio richiesta dati di un quadrante inviato da mmi a scada
*/
#include <all_1.h>
#include <tag.h>
#undef long
#define long  int
#define  maggr          21              // indice messaggio
#define  max_sigqua      4              // n. massimo sigle in un quadrante
#define  l_pagina       10

typedef struct h_mtrend {
                        short   nodo;
                        char    indice;
                        char    spare;
                        char    zona;
                        char    video;
                        char    pagina[l_pagina];
                        short   codtrend;       // codice trend assegnato da scada
                        char    indqua;         // indice quadrante
                        char    n_mis;          // numero curve
                        } H_MTREND;

typedef struct s_maggr {
                        H_MTREND hea;
                        char    archivio;       // numero archivio
                        char    spare2;
                        char    sigla[max_sigqua*SCD_SIGLA]; 
		       } S_MAGGR;
/*
        messaggio inviato a tabul per l'invio dati storici a mmi
*/
#define mvisarc    42
typedef struct s_visarc {
                        H_MTREND hea;
                        char    archivio;       // numero archivio
                        char    spare2;
                        char    point[max_sigqua];
                        } S_VISARC;
/*
	messaggio di invio parametri di configurazione di un quadrante
        trend storico da scada a mmi
*/
#define vprgr           54              // indice messaggio      

typedef struct qmisdes { 
                        char descr[SCD_DESCRIZIONE];
			char stat0[SCD_STATO];
			char stat1[SCD_STATO];
                        } QMISDES;

typedef struct s_vprgr {
                        H_MTREND hea;
			float t_iniz;    // tempo iniziale in sec.
			float durata;    // durata temporale in sec.
                        float interv;    // minimo intervallo campionamento
			short giorno;  	 // giorno inizio estrazione
			short mese;      // mese inizio estrazione
			short anno;      // anno inizio estrazione
			QMISDES md[max_sigqua]; 
                                         // unit… di misura e descrizione
					 // dei punti richiesti
		       } S_VPRGR;

#define l_vprgr (sizeof(S_VPRGR)-sizeof(QMISDES)*max_sigqua)
/*
	messaggio di invio dati un quadrante  trend storico da scada a mmi
*/
#define vdsgr           46      // indice messaggio
#define num_qcamp      200      // n. massimo campioni


typedef struct qcamp {
		        float temp;             // tempo campione
                        DATDBS val;             // valore campione
		    } QCAMP;

#define l_ftemp  4                               // dimensionamento campo
                                                // float temp

typedef struct s_vdsgr {
                        H_MTREND hea;
               unsigned char    n_camp;     // n. campioni
                        char    flag;       // flag fine ultimi dati
			QCAMP   b;          // buffer campioni     
			}S_VDSGR;

#define l_vdsgr (sizeof(S_VDSGR)-sizeof(QCAMP))

#define l_maxgr 512                    // dimensione massima messaggio
#define l_maxgrWin  1400                  // dimensione massima messaggio
/*
        messaggio per trasferimento file su floppy
*/
#define l_filext   13                    // lunghezza massima nome file + estensione
#define mtrasfarc  41
typedef struct s_floppy {
                        short lung;
                        short mess;
                        char  nome[l_filext];
                        short blocco;   // n. blocco richiesto
                        short dim;      // dimensione blocco a multipli di 1k
                        char  archivio; 
                        char  n_file;
                        short flag;     // =1 ultimo blocco
                        } S_FLOPPY;
  

#include <all_16.h>
#undef long
#define long long
