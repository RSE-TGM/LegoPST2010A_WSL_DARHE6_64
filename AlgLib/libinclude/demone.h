/**********************************************************************
*
*       C Header:               demone.h
*       Subsystem:              3
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jan 22 11:35:59 1997 %
*
**********************************************************************/
/*
   modulo demone.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)demone.h	5.1
*/
/*
MESSAGGIO PER DEMONE
*/

#define SERVER_PORT 2000
#define CLIENT_PORT 2001

#define MAX_LUN_COM_DEMONE 100

struct msg_demone_st
	{
	int tipo;
	char host[MAX_LUN_HOST];
	char comando_1[MAX_LUN_COM_DEMONE];
	char comando_2[MAX_LUN_COM_DEMONE];
        SIMULATOR      simul;
	};

typedef struct msg_demone_st MSG_DEMONE;

#define DEMONE_FINE  	    		0
#define DEMONE_START_SKED   		1
#define DEMONE_AGG_LEGOGRAF 		2
#define DEMONE_FINESTRA     		3
#define DEMONE_START_SKED_MASTER     	4
#define DEMONE_BANCO_TRASM     		5
#define DEMONE_BANCO_RICEZ     		6
#define DEMONE_KILLSIM     		7
#define DEMONE_START_BM     		8
#define DEMONE_STOP_BM     		9
