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
   modulo agg_manovra.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)agg_manovra.h	5.1
*/
/****************************************************************************/
/*
 *
 *   agg_manovra.h    file che contiene le definizioni di uso per la connessione
 *             in rete tra target e skedulatore
 *
 *			10nov92 fm
 *
 */

/*
	Definisce, sulle piattaforme UNIX l'utilizzo o meno delle
	FIFO al posto delle code di messaggi
*/
/*
#if defined ULTRIX
#define FIFO
#endif
*/

/*
 * nota: indici di modello da 0 a n
 */

#define MAX_DATI_RETE    15000 	     /* max lunghezza messaggio in bytes      */
#define MAX_DIM_RIGA_STATO	200  /* massima lunghessa riga di stato       */
#define MAX_PUNTI_DIGITALI	3840 /* numero massimo di digitali 
			                configurabili                         */
#define MAX_PUNTI_ANALOGICI	432  /* numero massimo di analogici 
				        configurabili                         */

/*
 *  definizioni campo tipo 
 */

#define AGG_MANOVRA_STATO   	1   /* aggiornamento sullo stato del 
                                       simulatore                             */
#define AGG_MANOVRA_DATI     	2   /* aggiornamento dati da simulatore       */
#define AGG_MANOVRA_DATI_CHECK  3   /* aggiornamento dati check da simulatore */
#define ELENCO_PUNTI        	4   /* elenco punti configurati per 
                                       aggiornamento                          */
#define ELENCO_PUNTI_CHECK  	5   /* elenco punti configurati per 
                                       aggiornamento                          */
#define RISPOSTA_CHECK      	6   /* risposta richiesta allinaeamento       */
#define PERTURBAZIONE	    	7   /* perturbazione da banco manovra         */
#define STATO_BM	    	8   /* stato banco manovra                    */
#define STATO_BM_RET	    	9   /* stato banco manovra  (ritorno)         */
#define ERRORE_BM              10  /* condizione di errore banco manovra     */
#define ELENCO_PUNTI_DIG       11   /* elenco punti digital input             */


struct head_rete_mess_st
	{
	int nodo_from;               /* nodo che genera i dati                */
	int nodo_to;                 /* nodo di destinazione                  */
	int modello;                 /* indice del modello                    */
	int tipo;                    /* tipo di messaggio
                                        (comando o dato da master)            */
	int stato_sim;               /* stato simulatore associato al 
                                        messaggio                             */
	int operazione;              /* ultima operazione eseguita            */
	int size;		     /* dimensione buffer                     */
	int size_digitali;           /* dimensione del buffer dei digitali    */
	int size_analogici;          /* dimensione del buffer degli analogici */
	int indice_pacchetto;        /* da 0 a n-1 numero della trance        */
	int totale_pacchetti;        /* numero totale dei pacchetti per il
                                        modello                               */
	}; 	
typedef struct head_rete_mess_st HEAD_MESS;

struct rete_mess_st
	{
	HEAD_MESS header;            /* testata del messaggio                 */
	char dati[MAX_DATI_RETE];    
	};
typedef struct rete_mess_st RETE_MESS;

#define MAX_DIG_MOD     1024
#define MAX_ANA_MOD     512
#define LUN_LABEL_ALL	16

struct punti_st
	{
   int punt;    /* max tra dig_mod,check e dimod         */
   char label[LUN_LABEL_ALL];
	};
typedef struct punti_st PUNTI;

struct lista_punti_st
	{
	HEAD_MESS header;            /* testata del messaggio                 */
	PUNTI     punti[MAX_DIG_MOD];
	};
typedef struct lista_punti_st LISTA_PUNTI;

struct write_mess_st
   {
   HEAD_MESS    header;             /* header per perturbazioni            */
   TIPO_PERT    perturbazione;      /* dati convertiti                     */
   };
typedef struct write_mess_st WRITE_MESS;

struct messaggi_taskbm_st
	{
	long mtype;
	int task[MAX_MODEL];
	};
typedef struct messaggi_taskbm_st MESSAGGI_TASKBM;

/*
 *  definizioni campo tipo_punto 
 */

#define PUNTO_ANALOGICO   	0 
#define PUNTO_DIGITALE   	1 

struct dati_bm_st
	{
	int modello;                 /* indice del modello                    */
	int tipo_punto;              /* tipo di punto ANALOGICO/DIGITALE      */
        int ind_bm;		   /* indirizzo del punto nel database del BM */
        int ind_sked;           /* indirizzo del punto nel database dello sked*/
	char nome[MAX_LUN_NOME_VAR];   /* nome della variabile                 */
	};
typedef struct dati_bm_st DATI_BM;

#define LUN_COOR_CHECK		24   /* lunghezza campo coordinate della 
                                        struttura CHECK_BM                    */
#define LUN_DESCR_CHECK		80   /* lunghezza campo descrizione della 
                                        struttura CHECK_BM                    */
#define MAX_ELEMENTI_CHECK   48   /* numero massimo di elementi da 
					controllare nella fase di allineamento*/
#define MAX_VAL   11            /* max lunghezza campo valore  */
#define LUN_SIGLA 9             /* numero caratteri per la sigla    */

struct check_bm_st
	{
	int modello;                 /* indice del modello                    */
	int tipo_punto;              /* tipo di punto ANALOGICO/DIGITALE      */
   int ind_bm;		     /* indirizzo del punto nel database del BM */
   int ind_sked;                /* indirizzo del punto nel database dello sked*/
	char nome[MAX_LUN_NOME_VAR];   /* nome della variabile                 */
	char coordinate[LUN_COOR_CHECK];    /* coordinate del componente sul banco */
	char descrizione[LUN_DESCR_CHECK];/*descr. identificativa del componente*/
	};
typedef struct check_bm_st CHECK_BM;

struct allineamento_st
	{
	char sigla[MAX_ELEMENTI_CHECK][LUN_SIGLA];  
   	char descrizione[MAX_ELEMENTI_CHECK][LUN_DESCR_CHECK];
	char coordinate[MAX_ELEMENTI_CHECK][LUN_COOR_CHECK]; 
	char val_att[MAX_ELEMENTI_CHECK][MAX_VAL];          
	char val_ci[MAX_ELEMENTI_CHECK][MAX_VAL];          
	int  punt_last;     /* puntatore all'ultimo record caricato    */
	};
typedef struct allineamento_st ALLINEAMENTO;

struct allineamento_msg_st
	{
	long mtype;                   /* tipo di messaggio */
	ALLINEAMENTO allineamento;
	};
typedef struct allineamento_msg_st MSG_ALLINEAMENTO;

struct write_check_st
   {
   HEAD_MESS    header;            /* header per controllo allineamento   */
   ALLINEAMENTO allineamento;      /* dati convertiti                     */
   };
typedef struct write_check_st WRITE_CHECK;


/*
        OFFSET PER APERTURA DEI SOCKET DI RETE
*/
#define SOCKET_MASTER             0
#define SOCKET_SLAVE            100
#define SOCKET_STATO            210
#define SOCKET_PERT             200
#define SOCKET_MASTER_SLAVE     300
