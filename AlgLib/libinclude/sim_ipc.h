/**********************************************************************
*
*       C Header:               sim_ipc.h
*       Subsystem:              3
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Sep  1 15:15:03 1998 %
*
**********************************************************************/
/*
   modulo sim_ipc.h
   tipo 
   release 5.2
   data 3/8/96
   reserved @(#)sim_ipc.h	5.2
*/

#ifndef _sim_ipc_h_
#define _sim_ipc_h_


/*
  sim_ipc.h
    definisce i parametri utilizzati per la InterProcessCommunication
    tra i processi che gestiscono la simulazione
*/

/*
  Numero limite di semafori e shared memory
*/
#define  NUM_MAX_SEM    10         /* numero massimo semafori attivi */
#define  NUM_MAX_SHM    10         /* numero massimo shared memory attive */

/*
  Offset per semafori
*/
#define OFF_SEM         5         /* Offset da aggiungere alla SHR_USR_KEY
                                     per determinare la key dei semafori  */

/* 
  Dimensionamento  set di semafori 
*/
# define NUM_SEM_MOD   MAX_MODEL*2   /* numero semafori per modelli    */
# define NUM_SEM_AUX    24         /* numero semafori ausiliari      */

/*
 Gestione semafori con timeout
*/
# define TIMEOUT_SCADUTO	 -100
# define TIMEOUT	 20  /* moltiplicando tale valore per nrip si
			       ottiene il massimo tempo di attesa sui
			       semafori dei modelli                  */
				
/*
 Tipi di messaggio
*/
#define MSG_CREA  1
#define MSG_NUMWR 2
#define MSG_ABORT  10

struct messaggi_task_st
	{
        long mtype;
	int mtext;
#if defined HELIOS
	int inizio;
	int size;
#endif
	};

typedef struct messaggi_task_st    MESSAGGI_TASK;

/*
tipi messaggi per task
*/

#define TASK_NEXT	1
#define TASK_SNAP 	2
#define TASK_STEP 	3
#define TASK_TEST 	4
#define TASK_FINE 	5
#define TASK_BM 	6
#define TASK_SAVE_SNAP 	7


/* 
   Identificatori code messaggi  
   la chiave e' data da SHR_USR_KEY+ID_MSG_... 
*/
/*
Parte per messaggi mmi e clients (prima era in Cs.h)
Utilizzata sia da Alg_mmi sia da Alg_rt (killsim)
Modificati FROM_MMI_MSG e SERVER_MMI_MSG perche' non intralcino code fra
demoni e server.
Logica costruzione code:
	demone_mmi-><-server_mmi    DEMONE_MSG+offset_daemon (demone_mmi.c).
                                    (cioe' da 88888 a 88888 +5)
        server_mmi1-><-server_mmi2  SERVER_MMI_MSG + prog    (server_mmi.c)
        client_mmi -><-mmi          FROM_MMI_MSG
by Fabio 
*/
#define FROM_MMI_MSGS                   77778
#define FROM_MMI_MSG                    90000
#define SERVER_MMI_MSG                  90001

/* fine parte per mmi*/

#define ID_MSG_MONIT       3  /* fra MONIT e SKED */
#define ID_MSG_BANCO       4  /* fra il BANCO e SKED */
#define ID_MSG_SKED        5  /* fra i proc. READ e SKED   */
#define ID_MSG_SNAP        6  /* fra SKED e net_snapshot   */
#define ID_MSG_PREP        7  /* fra SKED e net_prepf22   */
#define ID_MSG_LEG         8  /* fra SKED e net_legograf   */
#define ID_MSG_PERT        9  /* fra SKED e perturbazioni     */
#define ID_MSG_MANDB      10 /* per MANDB */
#define ID_MSG_AING       11 /* per AING */
#define ID_MSG_STAZ       12 /* per STAZ */
#define ID_MSG_RET_AING   13 /* per AING(legocad)*/
#define ID_MSG_PERT_MMI   14 /* per client MMI */
#define ID_MSG_AGG_SCADA  58
#define ID_MSG_BUFFER     60 /* coda buffer per accodamenti dati da task
                                provenienti da net_read non relativi al
                                modello in esame */
/*
   Code da e per le task: 
    ID_MSG_RETTASK e' la coda del ritono fra tutte le task e lo schedulatore
    ID_MSG_TASK    e' la coda fra lo schedulatore e la task 0, le altre sono
                   create in numero uguale al numero delle task e con ID
                   progressivo.
*/
#define BASE_TASK        100
#define ID_MSG_RETTASK	 BASE_TASK
#define ID_MSG_TASK      BASE_TASK + 1 

/* tempi massimi di attesa su code messaggi  */

#define TIMEOUT_BASE	45
#define TIMEOUT_TASK 	TIMEOUT_BASE 		/* timeout per le task  */
#define TIMEOUT_INF	0 			/* attesa senza timeout */
#define TIMEOUT_AUS	TIMEOUT_BASE*3 		/* attesa per proc. ausiliari */
#define TIMEOUT_SKED	TIMEOUT_BASE*2 		/* attesa per proc. sked */
#define TIMEOUT_DISP	TIMEOUT_BASE*15 	/* attesa per dispatcher */

/* Tempo di aggiornamento delle statistiche da parte dello schedulatore */
#define TIME_AGG_STAT   200

/* identificatori semafori  
	( la chiave e' data da SHR_USR_KEY+ID_SEM... )  */

#define ID_SEM_SHR	5  /*    semaforo shared memory    */
#define ID_SEM_MDB_1	6  /*    semaforo modifica data-base */
#define ID_SEM_MDB_2	7  /*    semaforo modifica data-base */
#define ID_SEM_MDB_3	8  /*    semaforo modifica data-base */
#define ID_SEM_MDB_4	9  /*    semaforo modifica data-base */
#define ID_SEM_MSG     10  /*    semaforo contatore code messaggi */

#define ID_SEM_DISP    11  /*    semaforo contatore dei messaggi
                                 presenti nelle code al dispatcher */

/* identificatori shared memory  */

#define ID_SHM_SIM	0 /* shared memory del simulatore  */
#define ID_SHM_VAR	5 /* shared memory delle variabili */
#define ID_SHM_LEG	2 /* shared memory di legograf     */
#define ID_SHM_MDB	3 /* shared memory del mandb	   */
#define ID_SHM_GRAF	4 /* shared memory di graf	   */


#endif
