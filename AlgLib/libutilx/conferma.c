/**********************************************************************
*
*       C Source:               conferma.c
*       Subsystem:              2
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jan 22 11:35:56 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: conferma.c-3p1 %  (%full_filespec: conferma.c-3p1:csrc:2 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)conferma.c	5.1\t11/10/95";
/*
   modulo conferma.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)conferma.c	5.1
*/
/*   CONFERMA.C		
     Visualizza una Question Box (<---Message Box) che chiede la 
     conferma di una scelta.
     Permette il passaggio diretto delle label dei Button e delle
     rispettive callback. 

     padre     widget da cui deve dipendere
     messaggio messaggio da visualizzare
     flag      vedere libutilx.h
     chiama_funz  funzione di callback da associare al Button specificato

  ritorna l'indice di Widget della Message Box se l'operazione ha avuto
  successo, altrimenti ritorna 0.
*/

#include <stdio.h>
#include <X11/Xlib.h>
#include <Mrm/MrmAppl.h>
#include <Xm/MessageB.h>
#include <Xm/Xm.h>

#include "libutilx.h"

/* Definizione font per tutte le label, messaggi ecc.  */
#define BOLD   font('ADOBE-Times-Bold-R-Normal--*-140-*-*-P-*-ISO8859-1')
#define NORMAL font('ADOBE-Helvetica-Medium-R-Normal--*-140-*-*-P-*-ISO8859-1')
#define FIXED  font ('8x13');

/* Macro per la creazioni di compound stringhe */
#define CS                      XmSTRING_DEFAULT_CHARSET
#define CREATE_CSTRING(string)  (XmStringCreateLtoR((string),CS))

/*
    Con autoUnmanage
*/
Widget conferma (padre,messaggio,chiama_funz)
Widget padre;
char   *messaggio;	/* Informazione-avviso da visualizzare all'utente */
Elenco_callback chiama_funz;
{
   Arg args[15];
   int n;
   Widget finestra;

   n = 0;
   XtSetArg(args[n],XmNdialogStyle,XmDIALOG_FULL_APPLICATION_MODAL);n++;
   XtSetArg(args[n],XmNdialogTitle, CREATE_CSTRING("Warning")); n++;
   XtSetArg(args[n],XmNnoResize,True); n++;
   XtSetArg(args[n],XmNresizePolicy,XmRESIZE_ANY); n++;
   XtSetArg(args[n],XmNallowOverlap,False); n++;
   XtSetArg(args[n],XmNmessageAlignment,XmALIGNMENT_CENTER); n++;
   XtSetArg(args[n],XmNmessageString,CREATE_CSTRING(messaggio)); n++;
   XtSetArg(args[n],XmNwidth,(60+10*strlen(messaggio))); n++;
   finestra=XmCreateQuestionDialog (padre,"finestra",args,n);

   XtManageChild(finestra);

/* -------------------------------------------------------- */
/* Accetta i parametri per l'OK_BUTTON  */
   if (chiama_funz[0].button_label != NULL)
   {
      set_something (finestra,XmNokLabelString,
                     CREATE_CSTRING(chiama_funz[0].button_label));
      XtAddCallback (finestra,XmNokCallback,
 		     chiama_funz[0].callback,
		     chiama_funz[0].parametro);
   }
   else
     XtUnmanageChild (XmMessageBoxGetChild(finestra, XmDIALOG_OK_BUTTON));

/* Accetta i parametri per il CANCEL_BUTTON  */
   if (chiama_funz[1].button_label != NULL)
   {
      set_something (finestra,XmNcancelLabelString,
	             CREATE_CSTRING(chiama_funz[1].button_label));
      XtAddCallback (finestra,XmNcancelCallback,
                     chiama_funz[1].callback,
		     chiama_funz[1].parametro);
   }
   else
      XtUnmanageChild (XmMessageBoxGetChild(finestra,XmDIALOG_CANCEL_BUTTON));
	
/* Accetta i parametri per l`HELP_BUTTON  */
   if (chiama_funz[2].button_label != NULL)
   {
      set_something (finestra,XmNhelpLabelString,
	             CREATE_CSTRING(chiama_funz[2].button_label));
      XtAddCallback (finestra,XmNhelpCallback,
		     chiama_funz[2].callback,
		     chiama_funz[2].parametro);
   }
   else
     XtUnmanageChild (XmMessageBoxGetChild(finestra,XmDIALOG_HELP_BUTTON));

   return(finestra);
}




/*
    Senza autoUnmanage
*/
Widget Conf (padre,messaggio,chiama_funz)
Widget padre;
char   *messaggio;	/* Informazione-avviso da visualizzare all'utente */
Elenco_callback chiama_funz;
{
   Arg args[15];
   int n;
   Widget finestra;

   n = 0;
   XtSetArg(args[n],XmNdialogStyle,XmDIALOG_FULL_APPLICATION_MODAL);n++;
   XtSetArg(args[n],XmNdialogTitle, CREATE_CSTRING("Warning")); n++;
   XtSetArg(args[n],XmNnoResize,True); n++;
   XtSetArg(args[n],XmNresizePolicy,XmRESIZE_ANY); n++;
   XtSetArg(args[n],XmNallowOverlap,False); n++;
   XtSetArg(args[n],XmNmessageAlignment,XmALIGNMENT_CENTER); n++;
   XtSetArg(args[n],XmNmessageString,CREATE_CSTRING(messaggio)); n++;
   XtSetArg(args[n],XmNwidth,(60+10*strlen(messaggio))); n++;
   XtSetArg(args[n],XmNautoUnmanage,False); n++;
   finestra=XmCreateQuestionDialog (padre,"finestra",args,n);

   XtManageChild(finestra);

/* -------------------------------------------------------- */
/* Accetta i parametri per l'OK_BUTTON  */
   if (chiama_funz[0].button_label != NULL)
   {
      set_something (finestra,XmNokLabelString,
                     CREATE_CSTRING(chiama_funz[0].button_label));
      XtAddCallback (finestra,XmNokCallback,
 		     chiama_funz[0].callback,
		     chiama_funz[0].parametro);
   }
   else
     XtUnmanageChild (XmMessageBoxGetChild(finestra, XmDIALOG_OK_BUTTON));

/* Accetta i parametri per il CANCEL_BUTTON  */
   if (chiama_funz[1].button_label != NULL)
   {
      set_something (finestra,XmNcancelLabelString,
	             CREATE_CSTRING(chiama_funz[1].button_label));
      XtAddCallback (finestra,XmNcancelCallback,
                     chiama_funz[1].callback,
		     chiama_funz[1].parametro);
   }
   else
      XtUnmanageChild (XmMessageBoxGetChild(finestra,XmDIALOG_CANCEL_BUTTON));
	
/* Accetta i parametri per l`HELP_BUTTON  */
   if (chiama_funz[2].button_label != NULL)
   {
      set_something (finestra,XmNhelpLabelString,
	             CREATE_CSTRING(chiama_funz[2].button_label));
      XtAddCallback (finestra,XmNhelpCallback,
		     chiama_funz[2].callback,
		     chiama_funz[2].parametro);
   }
   else
     XtUnmanageChild (XmMessageBoxGetChild(finestra,XmDIALOG_HELP_BUTTON));

   return(finestra);
}
