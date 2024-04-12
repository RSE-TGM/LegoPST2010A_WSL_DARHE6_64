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
   modulo libcom.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)libcom.h	5.1
*/
/*
 * definizioni comuni alle funzioni di libreria
 */
#define EASE_CLUSTER "EES$CLUSTER"
#define SKED_CLUSTER "SKED$$"
#define EASE_EF  64
#define SKED_EF  96
/*
 Posizione semaforo per perturbazioni: e' fissata per la compatibilita'
 con il programma ansaldo
*/
#define SEM_PERT 14
/*
 * definizioni utilizzate solo per ultrix o aix : 
 *    viene definita una struttura che verra' utilizzata per 
 *    emulare il funzionamento dei nomi logici in VMS.
 *    La struttura verra' allocata in area shared.
 */
#ifndef VMS
#define LUN_NOM_LOG 20
#define LUN_VAL_LOG 100
typedef struct s_nome_logico{
	char nome[LUN_NOM_LOG];
	char valore[LUN_VAL_LOG];
	} S_NOME_LOGICO;
#define NUM_NOM_LOG 20 /* dimensione della tabella dei nomi
                          logici */
#endif

