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
static char SccsID[] = "@(#)attesa.c	5.1\t11/10/95";
/*
   modulo attesa.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)attesa.c	5.1
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

Widget attesa(padre,messaggio,flag)
Widget padre;
char *messaggio;
int flag;
{
Arg args[10];
int n;
static Widget work;

if((flag&CREA)||(flag&MAPPA))
{
	if(flag&CREA)
	{
		n=0;
		XtSetArg(args[n],XmNmessageString,
			XmStringCreate(messaggio,XmSTRING_DEFAULT_CHARSET)); n++;
		XtSetArg(args[n],XmNdialogTitle,
                        XmStringCreate("Attesa",XmSTRING_DEFAULT_CHARSET)); n++;
		XtSetArg(args[n],XmNnoResize,True); n++;
		XtSetArg(args[n],XmNresizePolicy,XmRESIZE_NONE); n++;
		XtSetArg(args[n],XmNallowOverlap,False); n++;
		XtSetArg(args[n],XmNmessageAlignment,XmALIGNMENT_CENTER); n++;
		XtSetArg(args[n],XmNwidth,(60+10*strlen(messaggio))); n++;
		XtSetArg(args[n],XmNheight,120); n++;
		work=XmCreateWorkingDialog(padre,"work",args,n);
		
	}
	if(flag&MAPPA)
		{
		XtManageChild(work);
		XtUnmanageChild(
			XmMessageBoxGetChild(work,XmDIALOG_CANCEL_BUTTON));
		XtUnmanageChild(
                        XmMessageBoxGetChild(work,XmDIALOG_OK_BUTTON));
		XtUnmanageChild(
                        XmMessageBoxGetChild(work,XmDIALOG_HELP_BUTTON));
		XtUnmanageChild(
                        XmMessageBoxGetChild(work,XmDIALOG_SEPARATOR));
		}
}
else
{
	if ((work!=NULL)&&(flag==DISTRUGGI))
		XtDestroyWidget(work);
	if ((work!=NULL)&&(flag==UNMAPPA))
                XtUnmanageChild(work);
}
return(work);
}
