/**********************************************************************
*
*       C Header:               f22_circ.h
*       Subsystem:              3
*       Description:
*       %created_by:    mauric %
*       %date_created:  Mon Jan 12 11:45:56 1998 %
*
**********************************************************************/
/*
   File contenente le strutture e le definizioni
   per la gestione del file f22 "circolare".
*/



#include "sim_types.h"
#define OVER_CAMP	100
#define NUMMAXVAR	10


/*
  Struttura contenente un header per il file f22_circ
*/
struct f22circ_hd_st
       {
       int p_iniz;           /* puntatore prima variabile su f22circ_var  */
       int p_fine;           /* puntatore ultima variabile su f22circ_var */
       int num_campioni;     /* numero massimo di campioni salvabili      */
       int num_var_graf;     /* numero di variabili grafiche selezionate  */
       int ore;		     /* ore di creazione del file                 */
       int minuti;	     /* minuti di creazione del file                 */
       int secondi;	     /* secondi di creazione del file                 */
       int giorno;	     /* giorno di creazione del file                 */
       int mese;	     /* mese di creazione del file                 */
       int anno;	     /* anno di creazione del file                 */
       };
typedef struct f22circ_hd_st F22CIRC_HD;



/*
  Struttura contenente il nome della variabile e altre informazioni
*/
struct f22circ_var_st
       {
       char nomevar[MAX_LUN_NOME_VAR];
       char descvar[71];
       };
typedef struct f22circ_var_st F22CIRC_VAR;




/*
  Struttura contenente il tempo del campione salvato
*/
struct f22circ_t_st
       {
       float tempo;
       };
typedef struct f22circ_t_st F22CIRC_T;



/*
  Strutture per la lettura dei dati della simulazione
  con f22 circolare da parte del grafics 
*/
typedef struct scirc_dati 
        {
        F22CIRC_T tempo;
        float mis[6000];
        } SCIRC_DATI;

typedef struct scirc_sel_dati 
        {
        F22CIRC_T tempo;
        float mis[4];
        } SCIRC_SEL_DATI;

typedef struct scirc_sel_new
        {
        F22CIRC_T tempo;
        float mis[NUMMAXVAR];
        } SCIRC_SEL_NEW;


typedef struct s_min_max_new
	{
        float min;
        float max;
        } S_MIN_MAX_NEW;


typedef struct punt_file_f22_st 
        {
#if defined VMS
	int fp;
	int fphd;
#else
	FILE *fp;
	FILE *fphd;
#endif
        } PUNT_FILE_F22;

/*  funzioni   per la lettura del file*/
int f22_open_plus_file(char *, PUNT_FILE_F22 *);
int f22_create_new_file(char *, PUNT_FILE_F22 *);
int f22_create_file_dat(char *, PUNT_FILE_F22 *);
int f22_open_file(char *, PUNT_FILE_F22 *);
int f22_open_file_new(char *, PUNT_FILE_F22 *);
int f22_leggo_header(F22CIRC_HD *, PUNT_FILE_F22, int , SIMULATOR *);
int f22_close_file (PUNT_FILE_F22);
int f22_leggi_campioni(PUNT_FILE_F22,F22CIRC_HD,float *, SCIRC_SEL_DATI **,
                        int, int, int, int);
int f22_leggi_new(PUNT_FILE_F22,F22CIRC_HD,float *, SCIRC_SEL_NEW **, int *);
int f22_leggi_tutti_camp(PUNT_FILE_F22,F22CIRC_HD, SCIRC_SEL_NEW *, int *);
int f22_stampa_campioni(SCIRC_SEL_DATI *dati);
int f22_leggo_nomi_var(PUNT_FILE_F22 ,F22CIRC_VAR **,int *);
float f22_last_t(char *);
