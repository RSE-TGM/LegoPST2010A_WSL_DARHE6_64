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
   modulo grsf22.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)grsf22.h	5.1
*/
/*
        Fine sezione per SCCS
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

#define NUM_VAR 6000
#define LUN_TITOLO 80
#if defined SCADA_MMI
#define LUN_NOME 10   /* lunghezza nome modello e nomi variabili */
#else
#define LUN_NOME 8   /* lunghezza nome modello e nomi variabili */
#endif


#define LUN_SIMB  80

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

typedef struct s_sel_dati {
			float t;
			float mis[4];
			} S_SEL_DATI;

typedef struct s_min_max {
                        float min;
                        float max;
                        } S_MIN_MAX;

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
#define NUM_GRUPPI  50    /* numero massimo di gruppi presenti
                             sul file */

/*
 * F22_PAG.DAT
 *   struttura del file contenente le informazioni di pagina
 */
#define NUM_GRPAG 2     /* numero di gruppi per pagina */
#define NUM_PAGINE 16   
typedef struct rec_pagina {
	char pieno; /* flag indicante se la pagina e' gia' stata
                       utilizzata */
	char descr[81];  /* decrizione pagina */
	S_GRUPPO gr[NUM_GRPAG];
	} REC_PAGINA;
/*
 * F22_FILES.DAT
 *    file contenente i nomi (completi di path) dei files da leggere
 */
#define NUM_PATH_FILES 4
#define LUN_PATH_FILES 101

		
