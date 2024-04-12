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
   modulo ric_aing.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)ric_aing.h	5.1
*/

struct richiesta_aing_st{
		long mtype;
		char nome_variabile[MAX_LUN_NOME_VAR];
		char nome_display[100];
		int x;
		int y;
		int id_shm;  
		TIPO_PERT perturbazione;
		};

typedef struct richiesta_aing_st RICHIESTA_AING;

#define RIC_AING	1
#define ACK_AING	2

#define AING_OFFSET     10

struct ritorno_aing{
	long mtype;
	int modifica_pert;
		};
typedef struct ritorno_aing RITORNO_AING;

#define PERT_ANNULLA		0
#define PERT_MODIFICATA		1
#define PERT_ERRORE		2
