/**********************************************************************
*
*       C Header:               comandi.h
*       Subsystem:              3
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jan 22 11:35:53 1997 %
*
**********************************************************************/
/*
   modulo comandi.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)comandi.h	5.1
*/

#ifndef _comandi_h_
#define _comandi_h_
/* numeri base per le porte */
#define WRITE_PORT 5000
#define READ_PORT 2500


/*  tipo di schedulatore*/

#define SLAVE  	0
#define MASTER	1


/* Tipo di messaggi
	
        SKED_MASTER -> SKED_SLAVE
						*/
/* campo codice del messaggio  per la simulazione*/

#define 	START           	1
#define         STOP            	2
#define         NEXT            	3
#define         STEPCR			4
#define		FREEZE			5
#define		START_STEP		6
#define		STOP_STEP		7
#define         SAVESNAP        	8
#define         LOADSNAP        	9
#define         DELSNAP        		10
#define         SAVEBKTK                11
#define         LOADBKTK                12
#define         DELBKTK                 13
#define         START_RBT               14
#define         STOP_RBT                15
#define         START_FBT               16
#define         PREVIOUS                17
#define         START_REPLAY            18
#define         STOP_REPLAY             19
#define         CONNESSIONE_CHIUSA      20
#define         INVIO_PERT		21
#define         CLEAR_PERT		22
#define		STEPSCALING		23
#define         CLEAR_AREA_PERT         24
#define         CLEAR_UPDOWN            25
#define         CLEAR                   26
#define         CLEAR_PERT_FILE         27
#define         NO_ACTIONS              28


struct header_net_st {
		char sorg;  /* nodo da cui provengono i dati */
                char dest;  /* nodo di destinazione dati */
                char tasksorg; /* task da cui provengono i dati */
                char taskdest; /* task destinazione             */
                char tipo;  /* tipo di messaggio */
                char flag;  /* flags di utilita' */
                short codice; /* per utilizzi vari (dipende dal tipo
                                 di messaggio) */
                unsigned int lun;  /* lunghezza della parte DATI del 
					messaggio in bytes        */
		/*short spare;*/
                };

typedef struct header_net_st HEADER_NET;


/* massimo numero di dati contenuto in un pacchetto */
#define MAX_DATI_NET	1000

struct pacchetto_net_st{
	HEADER_NET header_net;
	float dato[MAX_DATI_NET];
		};

typedef struct pacchetto_net_st PACCHETTO_NET;

struct pacchetto_snap_st{
	HEADER_NET header_net;
	float *dato;
		};
typedef struct pacchetto_snap_st PACCHETTO_SNAP;


struct pacchetto_startup_st{
	HEADER_NET header_net;
	S02 s02_;
		};

typedef struct pacchetto_startup_st PACCHETTO_STARTUP;

struct msg_net_st{
	long mtype;
	HEADER_NET header_net;
	float dato[MAX_DATI_NET];
		};

typedef struct msg_net_st MSG_NET;

/* Tipo di messaggi dell'HEADER_NET nel campo tipo */

#define ERRORE          1
#define DATISIM         2
#define PERT            3
#define DATISNAP        4
#define DATIGRAF        5
#define DATISIN         6
#define DATISTAT        7
#define DATIPERT        8
#define DATISTARTUP     9
#define COMSIM          10
#define DATIREPLAY	11
#define ACKOWNLEDGE     12


/* Segnale di fine per le task di read */

#define SIGFINE		99


/* tipo messaggio per perturbazioni */

struct msg_pert_st{
	long mtype;
	TIPO_PERT perturbazione;
		};

typedef struct msg_pert_st MSG_PERT;


/* indici dei processi per perturbazioni */
# define AING	1
# define STAZ	2

# define OFFSET_PERT	30 /* deve essere maggiore di tutti gli indici
			      dei processi che possono effettuare
			      perturbazioni */

/* comandi per processi ausiliari */

#define START_AUS	1
#define STOP_AUS	2
#define RESET_AUS	3
#define RELOAD_AUS      4



/* indici dei processi ausiliari */

# define PREP_F22	1
# define SNAPSHOT	2
# define LEGOGRAF	3
#if defined SCADA
#define AGG_SCADA     	4
#endif
#if defined BANCO_MANOVRA
#define AGG_MANOVRA     5
#endif


#define OFFSET_AUS	50

# define MAX_PROC_AUS OFFSET_AUS-1

/*
   Tipo contenete le informazioni per i processi ausiliari
*/

struct tipo_aus_st{
        char comando;
        char messaggio[MAX_LUN_COMANDI];
                };

/*
  Tipo contenete le informazioni per i processi legograf
*/

struct tipo_legograf_st{
        int sezione[MAX_MODEL];
        int dimensione[MAX_MODEL];
                };

typedef struct tipo_aus_st     TIPO_AUS  ;

typedef struct tipo_legograf_st     TIPO_LEGOGRAF;

/* tipo messaggio per processi ausiliari */

struct msg_aus_st{
	long mtype;
	TIPO_AUS ausiliario;
		};

typedef struct msg_aus_st MSG_AUS;

/* tipo messaggio per i processi di aggiornamento legograf */

struct msg_legograf_st{
	long mtype;
	TIPO_LEGOGRAF dati;
		};

typedef struct msg_legograf_st MSG_LEGOGRAF;

#endif
