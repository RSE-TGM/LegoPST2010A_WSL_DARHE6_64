/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)errore.c	5.1\t11/10/95";
/*
   modulo errore.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)errore.c	5.1
*/
/*   visualizza un messaggio di attesa passato come parametro

     padre     widget da cui deve dipendere
     messaggio messaggio da visualizzare
     flag      vedere libutilx.h
*/

#include <stdio.h>
#include <X11/Xlib.h>
#include <Mrm/MrmAppl.h>
#include <Xm/MessageB.h>

#include "libutilx.h"

Widget WidErrore(padre,messaggio,flag)
Widget padre;
char *messaggio;
int flag;
{
Arg args[15];
int n;
static Widget finestra;

if((flag&CREA)||(flag&MAPPA))
	{
	if(flag&CREA)
		{
		n=0;
		XtSetArg(args[n],XmNdialogTitle,
                        XmStringCreate("Errore",XmSTRING_DEFAULT_CHARSET)); n++;
		XtSetArg(args[n],XmNokLabelString,
                        XmStringCreate("Conferma",XmSTRING_DEFAULT_CHARSET)); n++;
		XtSetArg(args[n],XmNnoResize,True); n++;
		XtSetArg(args[n],XmNresizePolicy,XmRESIZE_NONE); n++;
		XtSetArg(args[n],XmNallowOverlap,False); n++;
		XtSetArg(args[n],XmNmessageAlignment,XmALIGNMENT_CENTER); n++;
		XtSetArg(args[n],XmNheight,120); n++;
		finestra=XmCreateErrorDialog(padre,"finestra",args,n);
		}
	if(flag&MAPPA)
		{
		if(!finestra) return(0);
		n=0;
                XtSetArg(args[n],XmNmessageString,
                        XmStringCreate(messaggio,XmSTRING_DEFAULT_CHARSET)); n++;
                XtSetArg(args[n],XmNwidth,(60+10*strlen(messaggio)));
		n++;
		XtSetValues(finestra,args,n);
		XtManageChild(finestra);
		XtUnmanageChild(
			XmMessageBoxGetChild(finestra,XmDIALOG_CANCEL_BUTTON));
		XtUnmanageChild(
                        XmMessageBoxGetChild(finestra,XmDIALOG_HELP_BUTTON));
		XtUnmanageChild(
                        XmMessageBoxGetChild(finestra,XmDIALOG_SEPARATOR));
		}
}
else
{
	if ((finestra!=NULL)&&(flag==DISTRUGGI))
		XtDestroyWidget(finestra);
	if ((finestra!=NULL)&&(flag==UNMAPPA))
                XtUnmanageChild(finestra);
}
return(finestra);
}
