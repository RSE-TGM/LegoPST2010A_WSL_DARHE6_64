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
	messaggi per gestione pas -  definizione header
*/
typedef struct s_heapas {
		char mess;
		char classe;
		char pas;
		char seq; 	} HEAPAS ;


/* Struttura MSGPAS -->  messaggio scheduler PAS */

struct MSGPAS {
           short lung;	// word lunghezza messaggio
           HEAPAS hea;	// header messaggio (4 byte)
           } ;

