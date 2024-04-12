/**********************************************************************
*
*       C Source:               pscserr.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Fri Dec 13 12:11:28 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: pscserr.c-3 %  (%full_filespec: pscserr.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
   pscserr

   La funzione gestisce la presentazione degli errori rilevati
   nel funzionamento del pacchetto scada

   Parametri

   tipoerr  short    tipo errore
   task     short    nome del task
   codice   short    routine coinvolta
   errore   short    informazione aggiuntiva
   flag     short    =SYS_HALT il programma si ferma e ritorna a DOS
                     =SYS_CONT il programma continua
							=SYS_HALT_DOS il programma si ferma (marte non ancora
							attivo)
							=SYS_HALT_FLUSH il programma si ferma ed esce senza
							 errore (exit(0)) dopo aver salvato il data base
				  			 Il marte deve essere gia' installato
   Ritorno

   nessuno

   06 Aprile 1992    Rel. 1.0    Fc
	19 Aprile 1993		Rel. 1.1		Fc
	Aggiunta gestione errore con marte non ancora attivo
*/
#include <stdlib.h>
#include "pscserr.inc"
#include "dconf.inc"
#include "switch.inc"
#include "pscs.cfg"

extern DB_HEADER h_db;

pscserr(tipoerr,task,codice,errore,flag)
short tipoerr,task,codice,errore,flag;
{
printf("\n");
switch(tipoerr)
{
case ERR_IO:
   perror("IOerr:");
   break;
case ERR_MEM:
   printf("ERRMEM:");
   break;
case ERR_TASK:
   printf("ERRTASK:");
   break;
case STOP_TASK:
   printf("STOP SISTEMA:");
   break;
}
printf(" %d rout: %d info: %d \n \n",task,codice,errore);
switch (flag)
{
	case SYS_HALT:
#if defined (AC_INETDUALE) 
		InetEnd();					// fine comunicazioni Inet
#endif
#if defined (PRNSERVER)
      PrnClose();
#endif
      scd() ;
      if(NET_ABIL)
   	   NetMarteEnd();          // chiusura comunicazione rete Etehernet
  	   RestIDT();
	case SYS_HALT_DOS:
#if !defined OSF1 && !defined LINUX
	   exit(errore);                // uscita con ripartenza
#else
	QuitScadaNoWriteDBS(errore);
#endif
	break;
	case SYS_HALT_FLUSH:
#if defined (AC_INETDUALE) 
	InetEnd();					// fine comunicazioni Inet
#endif
#if defined (PRNSERVER)
      PrnClose();
#endif
      scd() ; 
      if(NET_ABIL)
         NetMarteEnd();          // chiusura comunicazione rete Etehernet
  	   RestIDT();
   	rwdbal(1,&h_db,&h_db);
      allocdb(1,&h_db);
		fcloseall();
#if !defined OSF1 && !defined LINUX
		exit(errore);
#else
        QuitScadaNoWriteDBS(errore);
#endif
	break;
	case SYS_CONT:
    	return(0);
}
return(0);
}
