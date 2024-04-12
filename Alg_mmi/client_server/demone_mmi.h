/**********************************************************************
*
*       C Header:               demone_mmi.h
*       Subsystem:              2
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Nov 29 09:49:34 2005 %
*
**********************************************************************/
/*
   modulo demone_mmi.h
   tipo 
   release 1.6
   data 1/12/96
   reserved @(#)demone_mmi.h	1.6
*/
/*
	File di include del processo demone_mmi

*/

/*
Per abilitazione aggancio
*/
#define ABILITAZIONE      "Protocol Ver1.0"
#define REQ_ABILITAZIONE  -2  
#define REQ_ABILITAZIONE_OPC  -3  
#define RICHIESTA_SERVER  "dummy"


#define DEMONE_PORT	88888   /* port  per richieste di connessione */
#define CLIENT_MMI_PORT 99999   /* porta per rispedire  a client_mmi
				   msg contenente il
				   numero di porta del server_mmi appena creato
				   vedi funz. invia_numero_porta in demone_-
				   mmi*/
#define DEMONE_MSG      88888   /* key per la coda di comunicazione
                                   tra il processo demone e i suoi figli */

#define NUMDAEMONCONN   5       /* max nun daemon su stessa macchina */

#define MAXHOSTNAMELUN 200

struct msg_demone_mmi_st
        {
	int richiesta;
	int port;
        char host[256];
        char path_sim[FILENAME_MAX];
        };
typedef struct msg_demone_mmi_st MSG_DEMONE_MMI;

#define MSG_PORT_SERVER	1

struct msg_demone_port_st
	{
	long mtype;
	int port;
	};

typedef struct msg_demone_port_st MSG_DEMONE_PORT;
