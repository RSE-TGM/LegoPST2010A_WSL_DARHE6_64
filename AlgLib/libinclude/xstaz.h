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
   modulo xstaz.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)xstaz.h	5.1
*/
/*
 *  XSTAZ.H
 *     header per l'applicativo xstaz: contiene i dimensionamenti e
 *     le strutture dati utilizzate
 */


/*
 Definizione tempo di refresh delle stazioni espresso in millisec.
*/
#define TREFRESH 400
#define DELTA_REF  15
#define TREFRESH_FAST TREFRESH/DELTA_REF
/*
 Definizione tempo di timeout per richiesta da stazione non ricevuta:
 e' espresso in multipli del tempo di refresh delle stazioni
*/
#define TWAIT 10

#define DIM_UNITSTAZ    62
#define MAX3_PAG        20
#define MAX_CEL         50
#define MAX_STAZ        2000
#define MAX_PAG         500
#define MAX_OGG         200
#define MAX_WIDGET_STAZ 10

#define LUN_NOM_PAG 8
#define LUN_NOM_STAZ 8
#define LUN_DES_PAG 50

#define MINIMO_INDICE_NEW_STAZ   100

/*
	struttura file r02.dat 
        header iniziale
*/

typedef struct head_r02 {
			char data[32];
			int  tot_pagine;
			int  tot_staz;
			char spare[24];
			} HEAD_R02;

/*
	per tot_pagine la struttura seguente
*/

typedef struct s_pagina{
	int attiva;
	char nome[LUN_NOM_PAG+1];
	char descrizione[LUN_DES_PAG+1];
	int posmx;
	int posmy;
	int num_staz;
	int offset_staz;
	} S_PAGINA;

/*
 struttura pagine visualizzate 
*/
typedef struct s_pagvis{
	int attiva;
	int x;
	int y;
	int width;
	int height;
	int pagina; /* indice della pagina associata */
	Widget w;   /* indice di widget della pagina */
	}S_PAGVIS;
	
/*
	struttura dati utilizzata per la compilazione      
*/
typedef struct s_comp_pag{
        int numero_pagina;
        int posix0[MAX_OGG];
        int posiy0[MAX_OGG];
        int posix1[MAX_OGG];
        int posiy1[MAX_OGG];
        int staz[MAX_OGG];
        int fill_pag[MAX_CEL][MAX_CEL];
        } S_COMP_PAGINA;


/*
        per tot_staz la struttura  S_STAZIONE
*/

typedef struct s_pagine{
        S_PAGINA p[MAX_PAG];
        } S_PAGINE;
                                                      
                                                      

/* tipi oggetti previsti per le stazioni */

#define	LED		1 
#define PULS_LUCE	2
#define PULSANTE	3
#define LAMPADA		4
#define SELETTORE	5
#define INDICATORE	6
#define STRINGA_DESCR	7
#define DISPLAY		8
#define	LUCE		9
#define	TASTO		10
#define	SET_VALORE	11
#define DISPLAY_SCALATO 12
#define INDICATORE_SINCRO 13
#define VUOTO		-1

/*  dimensioni tipi oggetti */

#define W_LED 15
#define H_LED  5
#define W_LAMPADA 15
#define H_LAMPADA 15
#define W_PULSANTE 15
#define H_PULSANTE 15
#define W_SELETTORE 20
#define H_SELETTORE 20
#define W_DISPLAY   90
#define H_DISPLAY   30
#define W_LUCE	    90
#define H_LUCE      35
#define W_TASTO	    60
#define H_TASTO     30
#define W_TASTO_GROSSO  100 
#define H_TASTO_GROSSO  90 
#define H_SETVALORE  15
#define W_SETVALORE  100
#define R_INDICATORE_SINCRO 100

/*
	define per sincronoscopio
*/
#define SINCRO_DELTA_FASE  	5
#define SINCRO_DELTA_V		5
#define SINCRO_DELTA_F		0.1
#define SINCRO_TIME_AGG		TREFRESH_FAST

#define NERO 		0
#define BIANCO 		1
#define GIALLO 		2
#define C_VERDE		3
#define C_ROSSO		4
#define GRIGIO		5
#define BLU		6


/* tipi perturbazioni 	previste	*/

#define	STEP		1
#define IMPULSO		2
#define NEGAZIONE	3
#define UP_DOWN		4


/* struttura  dei record del file r02.dat per le nuove stazioni */


typedef struct punt_var { int	nmod;     /* indice modello */
                          int	indice;   /* indice variabile */
                          int	tipo_pert;/* tipo perturbazione */
			  float value;    /* valore della perturbazione (se
                                             specificato per perturbaz.
                                             a scalino) */
			} PUNT_VAROUT;

#define LUNG_ETICHETTA 31
#define ETIC_SOTTO	1 
#define ETIC_DESTRA  	2
#define ETIC_MIN  	0	
#define ETIC_MAX  	1	/* max 20 caratteri */


typedef struct tipo_led { 
                  int	tipo_oggetto;
                  int	colore;
		  char  etic[LUNG_ETICHETTA+1];
		  int	input_colore;
		  int   neg_colore; /* indica se il valore della variabile
				       deve essere negato */
		  int	input_blink; 
		  int   neg_blink;  /* indica se il valore deve essere negato 
                                       */
	          } TIPO_LED;

typedef struct tipo_puls
                   {
                  int   tipo_oggetto;
		  int	 colore;
                  PUNT_VAROUT out;
		  } TIPO_PULS;
                

typedef struct tipo_puls_luce{
                  int   tipo_oggetto;
                  int   colore;
                  PUNT_VAROUT out;
                  int   input_colore;
		  int   neg_colore; 
                  int   input_blink;
		  int   neg_blink;
	          } TIPO_PULS_LUCE;

typedef struct tipo_lampada {
	 	  int	tipo_oggetto;
                  int   colore;
                  int   input_colore;
		  int   neg_colore;
                  int   input_blink;
		  int   neg_blink;
		  } TIPO_LAMPADA;

#define TASTO_NORM 0
#define TASTO_GROSSO  1
typedef struct tipo_tasto
                   {
                  int   tipo_oggetto;
                  int    colore;
                  PUNT_VAROUT out;
                  } TIPO_TASTO;


typedef struct tipo_luce {
                  int   tipo_oggetto;
                  int   colore;
                  int   input_colore;
		  int   neg_colore;
                  int   input_blink;
		  int   neg_blink;
                  } TIPO_LUCE;


#define	SELET_TIPO_A	1
#define	SELET_TIPO_B	2

typedef struct tipo_selet {
                  int   tipo_oggetto;
		  char	etic_0[LUNG_ETICHETTA+1];
		  char	etic_1[LUNG_ETICHETTA+1];
                  PUNT_VAROUT out;
                  int   input;
                  } TIPO_SELETTORE;

typedef struct tipo_setval {
                  int   tipo_oggetto;
                  char  etic[LUNG_ETICHETTA+1];
                  PUNT_VAROUT out;
                  PUNT_VAROUT rltarget;
                  int   input;
                  int   inibiz;
		  float scalam;
		  float offset;
                  } TIPO_SET_VALORE;
                                              
#define INDIC_BARRA1	1
#define INDIC_BARRA2	2
#define INDIC_AGO	3
#define INDIC_AGO_ERR	4
#define INDIC_BARRA_VD  5
#define INDIC_BARRA_VS  6
#define LARG_INDIC	100
#define ALTEZZA_INDIC	20
#define DELTA_X_BARRA2	30
#define ALTEZZA_INDIC_VERT 200

typedef struct tipo_indic {
                  int   tipo_oggetto;
                  int   input;
                  int   input_err;
		  float	alto_norm;
		  float	basso_norm;
		  float	scalam;
		  float	alto_err;
		  float	basso_err;
		  float	scalam_err;
		  float	offset;
                  } TIPO_INDICATORE;

#define STRINGA_GEN    0
#define STRINGA_TESTO  1
#define STRINGA_ETIC   2
#define STRINGA_ETIC_BIG   3
typedef struct tipo_stringa {
		 int 	tipo_oggetto;
		 char   etic[LUNG_ETICHETTA+1];
		 } TIPO_STRINGA_DESCR;
    
typedef struct tipo_display {
                 int    tipo_oggetto;
		 int	input;
                 } TIPO_DISPLAY;

typedef struct tipo_display_scalato {
                 int    tipo_oggetto;
                 int    input;
		 float  scalam;
		 float  offset;
                 } TIPO_DISPLAY_SCALATO;

typedef struct tipo_indicatore_sincro {
		int    tipo_oggetto;
                int    input_1;
                int    input_2;
                int    input_3;
                int    input_4;
                int    input_5;
                int    input_6;
                PUNT_VAROUT out_1;
                PUNT_VAROUT out_2;
		} TIPO_INDICATORE_SINCRO;

/*  struttura header stazioni */

  typedef struct s_head_staz{
             char nome[LUN_NOM_STAZ+1];
             int pagina;
             int tipo;
             int posix0;
             int posiy0;
             int posix1;
             int posiy1;
             } HEADER_STAZ;


union u { TIPO_STRINGA_DESCR stringa;
	   TIPO_INDICATORE indic;
           TIPO_SELETTORE selet;
	   TIPO_PULS puls;
	   TIPO_PULS_LUCE puls_luce;
	   TIPO_LED led;
	   TIPO_LAMPADA lamp;};
	    
#define LUNG_NEW_STAZ sizeof(HEADER_STAZ)+sizeof(TIPO_LED)*MAX_WIDGET_STAZ

/* 
	struttura vecchia delle stazioni 
*/

typedef struct s_old_stazione{
	int pagina;
	int tipo;
	int posix0;
	int posiy0;
	int posix1;
	int posiy1;
	char descrizione[2][34];
	char etic[6][4];
	char mod[12][15];
	int nmodi;
	char umis[6];
	float scalam;
	float scalaerr;
	float fs[4];
	int slstaz;
	int slesamr;
	int valore;
	int rlstaz[2];
	int rlaum[4];
	int rldim[4];
	int rltarget[2];
	int target[2];
	int stassoc[2];
	short incorso;
	short timer;
	int pos_ago[3];
		} S_OLD_STAZIONE;

#define LUNG_OLD_STAZ   sizeof(S_OLD_STAZIONE)

/*
	E' uguale alla vecchia, solo e' stato aggiunto un campo spare
	per allineare il record delle nuove stazioni 
*/

typedef struct s_stazione{
        char nome[LUN_NOM_STAZ+1];
        int pagina;
        int tipo;
        int posix0;
        int posiy0;
        int posix1;
        int posiy1;
        char descrizione[2][34];
        char etic[6][4];
        char mod[12][15];
        int nmodi;
        char umis[6];
        float scalam;
	float scalaerr;
        float fs[4];
        int slstaz;
        int slesamr;
        int valore;
        int rlstaz[2];
        int rlaum[4];
        int rldim[4];
        int rltarget[2];
        int target[2];
        int stassoc[2];
        short incorso;
	short timer;
        int pos_ago[3];
	char spare[LUNG_NEW_STAZ - LUNG_OLD_STAZ];
       } S_STAZIONE;

typedef struct s_stazioni {
		S_STAZIONE s[MAX_STAZ];
		} S_STAZIONI;

typedef struct s_wstaz {
		Widget w[MAX_WIDGET_STAZ]; /* numero di
                                            widget normali 
                                            che possono costituire
                                            una stazione */
		} S_WSTAZIONE;
/*
	Tabella elenco e descrizione stazioni di tipo > 100 
*/

#define LUN_NOME_STAZ   8


typedef struct oggetto {
			int 	tipo;	/* tipo oggetto */
			int	sottotipo;
			int	x;       /*posizione dell' oggetto*/
			int	y;	
			int	flag;	 /* uso vario */
			} OGGETTO;

typedef struct tipo_newstaz {
                            char nomestaz[LUN_NOME_STAZ+1];
		            int	num_oggetti;	/* nuemro oggetti */
			    int	larg;		/* larghezza */
			    int	altezza;	/* altezza */
		            OGGETTO ogg[MAX_WIDGET_STAZ];
			   } TIPI_NEWSTAZ;


/*
	struttura di definizione della tabella refresh_newstaz
*/

typedef	struct	dati_refr { Widget w;
				char *pdati;
				char flag;  } DATI_REFRESH;

/*
        messaggio di richiesta stazioni da lato schedulatore
*/

typedef  struct richiesta_staz_st {
                long mtype;
                char nome_pagina[LUN_NOM_PAG+1];
                } RICHIESTA_STAZ;

#define RIC_STAZ        1
/*
        chiavi di ricerca nel file r01.dat delle nuove stazioni
*/
#define s_colore "COLORE"
#define s_inp  "INPUT"
#define s_inperr  "INPUT_ERR"
#define s_inpb  "INPUT_BLINK"
#define s_etic   "ETICHETTA"
#define s_out "OUTPUT"
#define s_scalam "SCALAMENTO"
#define s_scalam_err "SCALAMENTO_ERR"
#define s_minmax "MINMAX"
#define s_minmax_err "MINMAX_ERR"
#define s_offset "OFFSET"
#define s_inib "INIBIZIONE"
#define s_not  "NOT"
