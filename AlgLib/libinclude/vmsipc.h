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
   modulo vmsipc.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)vmsipc.h	5.1
*/
/* include per la gestione delle code di messaggi in VMS */

/* Mode bits. */
#define IPC_CREAT       0001000         /* create entry if key doesn't exist */
#define IPC_EXCL        0002000         /* fail if key exists */
#define IPC_NOWAIT      0004000         /* error if request must wait */

/* Struttura base del messaggio */

#define MAX_DIMENSIONE_MESSAGGIO_BASE		1100 /* in byte */

struct struttura_messaggio_base_st{
	int	size;
	char	messaggio[MAX_DIMENSIONE_MESSAGGIO_BASE];
		};

typedef struct struttura_messaggio_base_st STRUTTURA_MESSAGGIO_BASE;


