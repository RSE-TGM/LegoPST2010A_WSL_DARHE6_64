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
   modulo banco.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)banco.h	5.1
*/
#define BANCO 			1
#define BI 			1
#define MONIT 			2
#define SUPERVISIONE		3
#define BM 			4
#define TASTIERA 		5
#define SKED 			6
#define TRANSPUTER 		7


/* include per i messaggi fra:

	MONIT <-> SKED
	BANCO <-> SKED

*/

# define MAX_LUN_COMANDI_SKDIS        200    /*lunghezza massima dei comandi*/

struct comando_banco_st {
	char sorgente;
	char dati[MAX_LUN_COMANDI_SKDIS];
		};

typedef struct comando_banco_st COMANDO_SKDIS;

struct msg_banco_st {
        long mtype;
	COMANDO_SKDIS comando_banco;
                };

typedef struct msg_banco_st MSG_SKDIS;

# define MAX_LUN_COMANDI_DISPATCHER    200    /*lunghezza massima dei comandi*/

struct comando_dispatcher_st {
        int sorgente;
        int tipo;
        int num;
        int num_tot;
        int size;
        char dati[MAX_LUN_COMANDI_DISPATCHER];
                };

typedef struct comando_dispatcher_st COMANDO_DISPATCHER;

struct msg_dispatcher_st {
        long mtype;
        COMANDO_DISPATCHER comando_dispatcher;
                };

typedef struct msg_dispatcher_st MSG_DISPATCHER;


/* elenco dei comandi */

#define SKDIS_STATO		  1
#define SKDIS_STATO_ACK		  2
#define SKDIS_AGGANCIO_MONIT      3
#define SKDIS_AGGANCIO_MONIT_ACK  4
#define SKDIS_SGANCIO_MONIT	  5
#define SKDIS_SGANCIO_MONIT_ACK	  6
#define SKDIS_AGGANCIO_BANCO      7
#define SKDIS_AGGANCIO_BANCO_ACK  8
#define SKDIS_SGANCIO_BANCO	  9
#define SKDIS_SGANCIO_BANCO_ACK	 10
#define SKDIS_INITIALIZE	 11
#define SKDIS_INITIALIZE_ACK	 12
#define SKDIS_RUN		 13
#define SKDIS_RUN_ACK		 14
#define SKDIS_FREEZE	 	 15
#define SKDIS_FREEZE_ACK	 16
#define SKDIS_STEP		 17
#define SKDIS_STEP_ACK		 18
#define SKDIS_BACKTRACK		 19
#define SKDIS_BACKTRACK_ACK	 20
#define SKDIS_REPLAY		 21
#define SKDIS_REPLAY_ACK	 22
#define SKDIS_STOP		 23
#define SKDIS_STOP_ACK		 24
#define SKDIS_TIMESCALING	 25
#define SKDIS_TIMESCALING_ACK	 26
#define SKDIS_STEPCR		 27
#define SKDIS_STEPCR_ACK	 28
#define SKDIS_SET		 29
#define SKDIS_SET_ACK		 30
#define SKDIS_LOADIC		 31
#define SKDIS_LOADIC_ACK	 32
#define SKDIS_SAVEIC		 33
#define SKDIS_SAVEIC_ACK	 34
#define SKDIS_EDITIC		 35
#define SKDIS_EDITIC_ACK	 36
#define SKDIS_REMOVE		 38
#define SKDIS_REMOVE_ACK	 39
#define SKDIS_GO_UP		 40
#define SKDIS_GO_UP_ACK	         41
#define SKDIS_GO_DOWN		 42
#define SKDIS_GO_DOWN_ACK        43

#define SKDIS_AGGANCIO_BI      7
#define SKDIS_AGGANCIO_BI_ACK  8

#define SKDIS_AGGANCIO_BM      44
#define SKDIS_AGGANCIO_BM_ACK  45
#define SKDIS_AGGANCIO_SUPERVISIONE      46
#define SKDIS_AGGANCIO_SUPERVISIONE_ACK  47
#define SKDIS_SGANCIO_BM      48
#define SKDIS_SGANCIO_BM_ACK  49
#define SKDIS_SGANCIO_SUPERVISIONE      50
#define SKDIS_SGANCIO_SUPERVISIONE_ACK  51



#define SKDIS_OFFSET		 100


/* strutture inserite nel campo dati del COMANDO_SKDIS */

struct statistica_sked_st{
		int stato_sked;
		float tempo_sim;
		float tempo_ritardo;
		float timescaling_sim;
		int   grandezze_mem;
		float passo_reg;    
		float tempi_task[MAX_MODEL];
		float tempo_cpu;
		int stato_task[MAX_MODEL];
		int stato_snapshot;
		int stato_prepf22;
		};

typedef struct statistica_sked_st STATISTICA_SKED;

struct snapshot_sked_st{
		char stat;
		char spare;
		short prog;
		char descr[SNAP_DESC];
		};

typedef struct snapshot_sked_st SNAPSHOT_SKED;

