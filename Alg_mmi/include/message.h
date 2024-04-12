/**********************************************************************
*
*       C Header:               message.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Thu Oct 16 17:59:55 1997 %
*
**********************************************************************/
/*
   modulo message.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)message.h	5.1
*/
/*----------------------- MESSAGE.H ------------------------
 *
 * Contiene le definizioni dei messaggi standard utilizzati
 * nella interfaccia di visualizzazione messaggi           
 *
 *----------------------------------------------------------*/


#ifndef MESSAGE_H
#define MESSAGE_H

#define MAXLABEL  10
#define MAXTITLE  20
#define MAXLENMSG 150

#define INFMSG 0          /* info message */
#define WRNMSG 1          /* warning message */
#define ERRMSG 2          /* error message */
#define SYSMSG 3          /* error message */
#define QUEMSG 4          /* error message */

#define MEMERR    9999    /* errore in gestione memoria */ 


typedef struct {
                  int     idOp;                  /* id operazione */
                  int     idType;                /* tipo messaggio INFMSG,WRNMSG,ERRMSG */
                  char    msg[MAXLENMSG];        /* messaggio     */
                  char    titolo[MAXTITLE];      /* titolo della shell */
                  Boolean CancelButton;
                  Boolean HelpButton;
                  char    LabelOk[MAXLABEL];     /* Label OkButton */
                  char    LabelCancel[MAXLABEL];
                  char    LabelHelp[MAXLABEL];
               } MESSAGGI;
#endif

/*------------------------ end of file message.h --------------------------------*/
