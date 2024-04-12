/*
   modulo f22.h
   tipo 
   release 1.3
   data 7/21/94
   reserved @(#)f22.h	1.3
*/
/*
 * F22.H
 *   - contiene le definizioni delle strutture appartenenti ai file
 *     f22 utilizzati nella applicazione GRAF per LEGOCAD.
 *   - contiene i dimensionamenti relativi ai medesimi files.
 */

/*
 *  File F22_HEADER.DAT o header del file F22.DAT
 */

#define NUM_VAR 600
#define LUN_TITOLO 80
#define LUN_NOME 8   /* lunghezza nome modello e nomi variabili */
#define LUN_SIMB 100  /* lunghezza record della tabella dei simboli */

typedef struct s_head1 {
		char titolo[LUN_TITOLO];
		int nvar;  /* numero variabili presenti */
		} S_HEAD1;

typedef struct s_head2 {
		char nome_mod[LUN_NOME];
		int ncasi; /* numero record tabella dei simboli */
		} S_HEAD2;

/*
 *  File F22.DAT (=file dati dalla simulazione)
 */


typedef struct s_dati {
			float t;
			float mis[NUM_VAR];
			} S_DATI;

/*
 * File UNI_MIS.DAT (= files per conversione unita' di misura)
 */

#define NUM_UMIS 15

typedef struct s_min_max {
                        float min;
                        float max;
                        } S_MIN_MAX;

typedef struct s_uni_mis {
			char codice[9]; /* tipo della misura per esteso */
			char type;      /* iniziale variabile lego per individuazione
							   unita' di misura  */
			int sel;        /* indice fattore di scala selezionato */
			char codm[5][7];
			float A[5];
			float B[5];
			} S_UNI_MIS;

/*
 *  struttura del file F22_GRAF.DAT
 *
 */
 
typedef struct s_gruppo {
		int autoscaling[4];
                S_MIN_MAX fix_min_max[4];
                int ind_mis[4]; /* indice delle misure
				   selezionate    */
                int ind_umis[4]; /* indice della posizione
                                    nella tabella delle unita' 
                    	            di misura */		 
		int umis_sel[4];
		char descr_mis[4][LUN_SIMB+1];
		} S_GRUPPO;

typedef struct rec_gruppo {
		char pieno; /* flag indicante se il gruppo e'
                               gia' stato utilizzato */
		char descr[81]; /* descrizione gruppo */
		S_GRUPPO gr;
		} REC_GRUPPO;
#define NUM_GRUPPI  24    /* numero massimo di gruppi presenti
                             sul file */

/*
 * F22_PAG.DAT
 *   struttura del file contenente le informazioni di pagina
 */
#define NUM_GRPAG 2     /* numero di gruppi per pagina */
#define NUM_PAGINE 64   
typedef struct rec_pagina {
	char pieno; /* flag indicante se la pagina e' gia' stata
                       utilizzata */
	char descr[81];  /* decrizione pagina */
	S_GRUPPO gr[NUM_GRPAG];
	} REC_PAGINA;
