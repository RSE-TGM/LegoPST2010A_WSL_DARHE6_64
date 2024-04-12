/**********************************************************************
*
*       C Source:               information.c
*       Subsystem:              2
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jan 22 11:36:15 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: information.c-3 %  (%full_filespec: information.c-3:csrc:2 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)information.c	5.1\t11/10/95";
/*
   modulo information.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)information.c	5.1
*/
/*   INFORMATION.C  */
/*
     padre     widget da cui deve dipendere
     messaggio messaggio da visualizzare
     flag      vedere libutilx.h
     geometry  definito in libutilx.h
  ritorna l'indice di Widget della message box se l'operazione ha avuto
  successo altrimenti ritorna 0.
*/

#include <stdio.h>
#if defined UNIX
#include <sys/types.h>
#include <sys/stat.h>
#elif defined VMS
#include <types.h>
#include <stat.h>
#endif
#include <X11/Xlib.h>
#include <Mrm/MrmAppl.h>
#include <Xm/MessageB.h>
#include <Xm/PushB.h>
#include <Xm/DialogS.h>
#include <Xm/Xm.h>

#include "libutilx.h"

/* Macro per la creazioni di compound stringhe */
#define CS  			XmSTRING_DEFAULT_CHARSET
#define CREATE_CSTRING(string)  (XmStringCreateLtoR((string),CS))

Widget information(padre,messaggio,flag,geometry)
Widget padre;
char *messaggio;
int flag;
Dialog_geometry geometry;
{
Arg args[15];
int n;
static Widget finestra;

if((flag&CREA)||(flag&MAPPA))
	{
	if(flag&CREA)
		{
		n=0;
		XtSetArg(args[n],XmNdialogStyle,XmDIALOG_APPLICATION_MODAL);n++;
		XtSetArg(args[n],XmNdialogTitle,
                                 CREATE_CSTRING("Information")); n++;
		XtSetArg(args[n],XmNokLabelString,
                        CREATE_CSTRING("Continue")); n++;
		XtSetArg(args[n],XmNnoResize,True); n++;
		XtSetArg(args[n],XmNresizePolicy,XmRESIZE_NONE); n++;
		XtSetArg(args[n],XmNallowOverlap,False); n++;
		XtSetArg(args[n],XmNmessageAlignment,XmALIGNMENT_CENTER);n++;
		XtSetArg(args[n],XmNheight,geometry.height); n++;

		finestra=XmCreateInformationDialog(padre,"finestra",args,n);
		}
	if(flag&MAPPA)
		{
/*
 se la message box non e' stata creata ritorna con errore
 */   
		if(!finestra) return(0);
		n=0;
                XtSetArg(args[n],XmNmessageString, CREATE_CSTRING(messaggio)); 
		n++;
                XtSetArg(args[n],XmNwidth,(60+8*strlen(messaggio))); n++;
		XtSetArg(args[n],XmNdefaultPosition,geometry.default_pos); n++;
		XtSetArg(args[n],XmNx,geometry.x); n++;
		XtSetArg(args[n],XmNy,geometry.y); n++;
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

