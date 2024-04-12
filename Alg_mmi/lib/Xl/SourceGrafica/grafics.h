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
   modulo grafics.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)grafics.h	5.1
*/
/*
        Fine sezione per SCCS
*/
/*
 * GRAF.H
 *   contiene dimensionamenti e strutture utilizzate internamente al
 *   client GRAF
 */

/*
  Dimensionamenti relativi al buffer contenente i valori delle variabili
  di simulazione
*/

#define NUM_CAMP_Z0 901   /* numero campioni visualizzati a zoom 0 */
#define NUM_CAMP_Z1 451   /* numero campioni visualizzati a zoom 1 */
#define NUM_CAMP_Z2 181   /* numero campioni visualizzati a zoom 2 */
#define NUM_CAMP_Z3 61    /* numero campioni visualizzati a zoom 3 */
#define NUM_CAMP_Z4 31    /* numero campioni visualizzati a zoom 3 */

#define DIM_BUFCIRC  (NUM_CAMP_Z0+20)
/*
 tempo intercorrente tra due campioni del buffer dei valori
 */
#define INC_SEC 2

/*
 flags utilizzati per la chiamata della routine di lettura dati
 */
#define AGGIORNA 0
#define TUTTI    1
#define DA_FILE  3

/*
  Dimensionamenti e strutture relative alla grafica; la struttura
  S_GRAFICO contiene tutte le informazioni relative ad una area grafica.
*/
#define NUM_GRAFICI 1 /* numero di grafici rappresentati  */
typedef struct s_grafico {
			int zoom;  /* fattore di zoom selezionato */
			float fatt_y[4];
			int autoscaling[4];
			S_MIN_MAX fix_min_max[4];
			int ind_mis[4]; /* indice delle misure selezionate
*/
			int ind_umis[4]; /* indice della posizione
                                            nella tabella delle unita'
                                            di misura */
			int umis_sel[4]; /* unita' di misura selezionata
                                            tra quelle ammissibili */

			char descr_mis[4][LUN_SIMB+1];
			float ultimo[4]; /* valore degli ultimi dati
                                            acquisiti  */
			XmString x_descr_mis[4];
			char str_ord[5][4][20];
			S_MIN_MAX sel_min_max[4];
			S_MIN_MAX var_min_max[4];
			char pendente;
			int wiew_first;
			int wiew_last;
			Widget w_draw;  /* indice del widget per grafico */
			Widget w_mis;   /* indice del widget per descr.
                                        misure */
			Widget w_tim;   /* indice del widget per scala
  				        tempi */
			Widget w_ord;   /* indice del widget per ordinate
                                           */
			Widget w_val;   /* indice del widget per valori
					   correnti */
			} S_GRAFICO;


