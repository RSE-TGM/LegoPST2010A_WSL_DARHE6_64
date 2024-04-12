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
   modulo agg_scada.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)agg_scada.h	5.1
*/
/* 

	define per la comunicazione fra 

		il processo DISPATCHER e AGG_SCADA

*/

#include "simmsg.h"

#define errore(stringa)         exit(printf("Processo agg_scada: %s\n",stringa))

#define FORM_DATI       ULTRIX_ULTRIX

#define 	SIM_TIME		100 
#define 	SIM_TIME_EXTRA		101
#define 	DB_ALL			102
#define 	DB_ANA			103
#define 	SIM_TIME_INT	104 


