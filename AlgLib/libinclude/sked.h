/**********************************************************************
*
*       C Header:               sked.h
*       Subsystem:              3
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Sat Dec  7 14:47:50 2002 %
*
**********************************************************************/
/*
   modulo sked.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)sked.h	5.1
*/
/* **********************************************************************
		INCLUDE DEL PROCESSO SKED
************************************************************************* */
/*
Num max variabili di environment presenti
*/
#define MAXENVVAR		500
/* stato dello sked */

#define STATO_STOP      	0
#define STATO_RUN       	1
#define STATO_FREEZE    	2
#define STATO_BACKTRACK		3
#define STATO_REPLAY		4
#define STATO_ERRORE    	5

/* operazioni eseguite dallo sked */
#define ESEGUITO_DEFAULT	0
#define ESEGUITO_STEP		1
#define ESEGUITO_LOADIC		2
#define ESEGUITO_SAVEIC		3
#define ESEGUITO_LOADBT		4
#define ESEGUITO_ALLINEAMENTO   5

/* costanti per il lancio delle task */

#define  NUMPAR         40         /* numero parametri per execve   */
#define  LUN_ENV        FILENAME_MAX         /* lunghezza massima delle var.
                                       di environment passate */
#define  LUN_ARG        FILENAME_MAX         /* lunghezza massima argomenti
                                       passati */
#define  LUN_PATH       FILENAME_MAX         /* lunghezza path modelli */

struct stato_cr_st
        {
        int last_snap_save;
        int last_snap_load;
#if defined BACKTRACK
        int last_bktk_save;
        int last_bktk_load;
#endif
        };
typedef struct stato_cr_st STATO_CR;
