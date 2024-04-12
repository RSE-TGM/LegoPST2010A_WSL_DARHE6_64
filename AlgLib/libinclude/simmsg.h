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
   modulo simmsg.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)simmsg.h	5.1
*/
/*
        SIMMSG.INC
        
                Contiene strutture messaggi da Simulatore a 
                Sistema di Supervisione e Controllo (SSC)
                (Simulatore ENEL PC).

        09.10.92  -  Rev. 2.00  -  GM.Furlan

*/

/*#include "simfile.inc" */   /* contiene strutture record file FSVINANA.RTF, FSVINDIG.RTF */

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
                int    tipo;         /* specificazione messaggio */
               } SM_DIAGNO;


/*
        Codici messaggi da simulatore a SSC
*/
#define START_SCADA           1       /* start */
#define STOP_SCADA            2       /* stop */
#define LOADCI          3       /* carica condizione iniziale */
#define INITDB          4       /* inizializzazione DB  */
#define ALT             5       /* alt */
#define RUN_SCADA       6       /* run */
#define DBUPD           7       /* aggiornamento DB */
#define SIMTIME         8       /* tempo di simulazione */
#define FREEZE_SCADA    9       /* freeze */
#define BKTKON         10       /* back track on */
#define BKTKOFF        11       /* back track off */
#define LOADBT         12       /* caricamento foto di back track */
#define REPON          13       /* replay on */
#define REPOFF         14       /* replay off */
#define STEP           15       /* step */
#define CFG            16       /* ricezione configurazione */

/* Tipi di messaggi di diagnostica */
#define NOCFG          16       /* problemi ricezione configurazione */

/*
        Strutture messaggi da simulatore a SSC
*/

/* invio tempo di simulazione */
typedef struct {
                SM_HEAD hea;          /* nodo, codice */
                double time;          /* tempo di simulazione */
               } SM_SIMTIME;


/* inizializzazione DB da condizione iniziale */
typedef struct {
                SM_HEAD hea;          /* nodo, codice */
                int numci;           /* numero condizione iniziale */
               } SM_LOADCI;

/* caricamento foto di BT */
typedef struct {
                SM_HEAD hea;          /* nodo, codice */
                int numbt;           /* numero foto di BT */
               } SM_LOADBT;

/* aggiornamento DB  */
#define         DBDIM 125  /* numero massimo punti contenuti nel messaggio di  */
                            /* aggiornamento del DB (dim. max. messaggio=1K) */
/* informazione punto in DB */
typedef struct {
                float val;           /* valore misura */
                int punt;           /* puntatore nel DB del SSC */
               } SM_DB;

typedef struct {
                SM_HEAD hea;          /* nodo, codice */
                int tipopunti;       /* 0=Analogici; 1=Digitali */
                int numpunti;        /* numero punti di cui si fornisce il valore */
                int indpack;         /* indice progressivo pacchetto inviato */
                int lastpack;        /* 0=no ultimo; 1=ultimo pacchetto inviato */
                SM_DB db[DBDIM];      /* dbs */
               } SM_DBUPD; 


/* union messaggi da Simulatore a SSC */
union msim {
            char bufmes[MAXDIMMSG];   
            SM_HEAD  h;     
            SM_LOADCI  ci;   /* caricamento CI */
            SM_LOADBT  bt;   /* caricamento BT */
            SM_SIMTIME st;   /* tempo di simulazione BT */
            SM_DBUPD   ud;   /* aggiornamento DB */
            SM_DIAGNO  rc;   /* dignostica ricezione configurazione */
           } msgsim;



 
/*
        Codici messaggi da SSC a simulatore 
*/
#define DIAGNO          257     /* (0x101) Diagnostica */
#define CONFIG          258     /* (0x102) Invio punti configurati */

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

/* aggiunta Marcello */
typedef struct {
	char	sigla[8];
	int	punt;
	} SVINREC;
	
typedef struct {
                SM_HEAD hea;          /* nodo, codice */
                int tipopunti;       /* 0=Analogici; 1=Digitali */
                int numpunti;        /* numero punti di cui si fornisce il valore */
                int indpack;         /* indice progressivo pacchetto inviato */
                int lastpack;        /* 0=no ultimo; 1=ultimo pacchetto inviato */
                SVINREC rec[NUMREC];  /* sigla punto simulatore, puntatore in DB di SSC */
               } SM_CONFIG;


/* union messaggi da SSC a Simulatore */
union mssc {
            char bufmes[MAXDIMMSG];   
            SM_DIAGNO dia;              /* diagnostica*/
            SM_CONFIG cfg;              /* send configurazione*/
           } msgssc;

