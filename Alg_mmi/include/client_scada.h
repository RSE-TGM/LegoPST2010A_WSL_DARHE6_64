/**********************************************************************
*
*       C Header:               client_scada.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Nov  3 16:41:02 1998 %
*
**********************************************************************/
/*
   modulo client_scada.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)client_scada.h	5.1
*/
#include "sdi_messhost.h"


#define SCADA_PORT    1900
#define MAX_PUNTI_SCADA 640
#define MAX_ZONE 11
#define ZONA_ALLARMI  2
#define ZONA_TEMPO  11
#define MAX_DIM_MESSAGGIO_SCADA         5000
#define SIZE_FLAG 	2


#define P_AA		1
#define P_AS            2
#define P_AC		3
#define P_AD            4
#define P_AO		5
#define P_DA		7
#define P_DS            8
#define P_DC		9
#define P_DD            10
#define P_DO		11
#define P_OR		12
#define P_ST		13

#define SIZE_ANA		6
#define SIZE_DIG		1
#define SIZE_OR		0
#define SIZE_ST		0

/*
Definisco max num DB allarmi
*/
#define MAXNUMDBALARM	4
