/**********************************************************************
*
*       C Header:               simmsg.inc
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Dec 16 13:28:10 2002 %
*
**********************************************************************/
/*
        SIMMSG.INC
        
                Contiene strutture messaggi da Simulatore a 
                Sistema di Supervisione e Controllo (SSC)
                (Simulatore ENEL PC).

        09.10.92  -  Rev. 2.00  -  GM.Furlan

*/

#include "simfile.inc"    /* contiene strutture record file FSVINANA.RTF, FSVINDIG.RTF */

#if defined OSF1 || defined LINUX
#undef long
#define long int
#endif

#define ANA     0
#define DIG     1

#define      MAXDIMMSG 1024   /* massima dimensione messaggio */

/*
        Header messaggi da simulatore a nodi rete
*/
typedef struct {
               short nodo;     /* indirizzo nodo destinazione (0=SCADA) */
               short mess;     /* codice msg. */
               } SM_HEAD;

/* 
        Messaggio di diagnostica
*/
typedef struct {
                SM_HEAD hea;          /* nodo, codice */
                long    tipo;         /* caso specifico di diagnostica */
               } SM_DIAGNO;


/*
        Codici messaggi da simulatore a SSC
*/
#define START           1       /* start */
#define STOP            2       /* stop */
#define LOADCI          3       /* carica condizione iniziale */
#define INITDB          4       /* inizializzazione DB  */
#define ALT             5       /* alt */
#define RRUN             6       /* run */
#define DBUPD           7       /* aggiornamento DB */
#define SIMTIME         8       /* tempo di simulazione */
#define FFREEZE          9       /* freeze */
#define BKTKON         10       /* back track on */
#define BKTKOFF        11       /* back track off */
#define LOADBT         12       /* caricamento foto di back track */
#define REPON          13       /* replay on */
#define REPOFF         14       /* replay off */
#define STEP           15       /* step */
#define CFG            16       /* diagnostica ricezione configurazione */
#define COM            17       /* diagnostica ricezione comando */

/* Tipi di messaggi di diagnostica */
#define NOCFG          16       /* problemi ricezione configurazione */
#define NOCOM          17       /* problemi ricezione comando */

/*
        Strutture messaggi da simulatore a SSC
*/

/* invio tempo di simulazione */
typedef struct {
                SM_HEAD hea;          /* nodo, codice */
                float time;           /* tempo di simulazione */
                long  hh  ;           /* ora di simulazione */
                long  mm  ;           /* minuto di simulazione */
                long  ss  ;           /* secondo di simulazione */
                long  dd  ;           /* giorno di simulazione */
                long  ms  ;           /* mese di simulazione */
                long  yy  ;           /* anno di simulazione */
               } SM_SIMTIME;


/* inizializzazione DB da condizione iniziale */
typedef struct {
                SM_HEAD hea;          /* nodo, codice */
                long numci;           /* numero condizione iniziale */
               } SM_LOADCI;

/* caricamento foto di BT */
typedef struct {
                SM_HEAD hea;          /* nodo, codice */
                long numbt;           /* numero foto di BT */
               } SM_LOADBT;

/* aggiornamento DB  */
#define         DBDIM 125   /* numero massimo punti contenuti nel messaggio di  */
                            /* aggiornamento del DB (dim. max. messaggio=1K) */
/* informazione punto in DB */
typedef struct {
                float val;           /* valore misura */
                long punt;           /* puntatore nel DB del SSC */
               } SM_DB;

typedef struct {
                SM_HEAD hea;          /* nodo, codice */
                long tipopunti;       /* 0=Analogici; 1=Digitali */
                long numpunti;        /* numero punti di cui si fornisce il valore */
                long indpack;         /* indice progressivo pacchetto inviato */
                long lastpack;        /* 0=no ultimo; 1=ultimo pacchetto inviato */
                SM_DB db[DBDIM];      /* dbs */
               } SM_DBUPD; 

/*
        Codici messaggi da SSC a simulatore 
*/
#define DIAGNO          257     /* (0x101) Diagnostica */
#define CONFIG          258     /* (0x102) Invio punti configurati */
#define COMAO           259     /* (0x103) Invio Analogico di Output (set point) */
#define COMDO           260     /* (0x104) Invio Digitale di Output (set point) */

/* Tipi di messaggi di diagnostica */
#define NOMESS     -1    /* ricevuto messaggio sconosciuto */
#define OK          0    /* operazioni relative a msg da sim. terminate correttamente */
#define NOSTART     1    /* fallito start */
#define NOSTOP      2    /* fallito stop */
#define NOLOADCI    3    /* fallito caricamento condizione iniziale */
#define NOINITDB    4    /* fallita inizializzazione DB  */
#define NOALT       5    /* fallito alt */
#define NORUN       6    /* fallito run */
#define NODBUPD     7    /* fallito aggiornamento DB */
#define NOSIMTIME   8    /* fallito aggiornamento DB */
#define NOFREEZE    9    /* fallito freeze */
#define NOBKTKON   10    /* fallito back track on */
#define NOBKTKOFF  11    /* fallito back track off */
#define NOLOADBT   12    /* fallito caricamento foto di back track */
#define NOREPON    13    /* fallito replay on */
#define NOREPOFF   14    /* fallito replay off */
#define NOSTEP     15    /* fallito step */

/*
        Strutture messaggi da SSC a simulatore
*/

/* Punti configurati */
#define         NUMREC  83            /* numero max di punti inviati per messaggio */
typedef struct {
                SM_HEAD hea;          /* nodo, codice */
                long tipopunti;       /* 0=Analogici; 1=Digitali */
                long numpunti;        /* numero punti di cui si fornisce il valore */
                long indpack;         /* indice progressivo pacchetto inviato */
                long lastpack;        /* 0=no ultimo; 1=ultimo pacchetto inviato */
                SVINREC rec[NUMREC];  /* sigla punto simulatore, puntatore in DB di SSC */
               } SM_CONFIG;

/* Invio Analogici o Digitali di Output */
typedef struct {
                SM_HEAD hea;          /* nodo, codice */
                long pcom;            /* puntatore comando nel DB del SSC */
                float val;            /* valore Analogico o Digitale di Output */
               } SM_COM;
/*
	viene definita una tolleranza per il tempo di reset degli
	archivi in secondi
*/
#define TIMESIM_TOLLERANCE       0.25

#if defined OSF1 || defined LINUX
#undef long
#define long long
#endif

