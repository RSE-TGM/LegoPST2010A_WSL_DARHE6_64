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
static char SccsID[] = "@(#)attention.c	5.1\t11/10/95";
/*
   modulo attention.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)attention.c	5.1
*/
/*   ATTENTION.C  versione angloamericana di 'attenzione.c'  */
/*   visualizza un messaggio di attesa passato come parametro

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

Widget attention(padre,messaggio,flag,geometry)
Widget padre;
char *messaggio;
int flag;
Dialog_geometry geometry;
{
Arg args[15];
int n;
static Widget finestra;
XmFontList font_list;

if((flag&CREA)||(flag&MAPPA))
	{
	if(flag&CREA)
		{
		n=0;
		XtSetArg(args[n],XmNdialogStyle,XmDIALOG_APPLICATION_MODAL);n++;
		XtSetArg(args[n],XmNdialogTitle, CREATE_CSTRING("Notice")); n++;
		XtSetArg(args[n],XmNokLabelString,
                        CREATE_CSTRING("Continue")); n++;
		XtSetArg(args[n],XmNnoResize,True); n++;
		XtSetArg(args[n],XmNresizePolicy,XmRESIZE_NONE); n++;
		XtSetArg(args[n],XmNallowOverlap,False); n++;
		XtSetArg(args[n],XmNmessageAlignment,XmALIGNMENT_CENTER); n++;
		XtSetArg(args[n],XmNdefaultPosition,geometry.default_pos); n++;
		XtSetArg(args[n],XmNheight,geometry.height); n++;
		finestra=XmCreateWarningDialog(padre,"finestra",args,n);
		}
	if(flag&MAPPA)
		{
/*
 se la message box non e' stata creata ritorna con errore
 */   

/*                n=0;
                XtSetArg(args[n],XmNtextFontList, font_list); n++;
		XtGetValues(finestra,args,n);

                printf("ascent: %d\n",font_list->font.ascent);
                printf("descent: %d\n",font_list->font.descent); */

		if(!finestra) return(0);
		n=0;
                XtSetArg(args[n],XmNmessageString, CREATE_CSTRING(messaggio)); 
		n++;
                XtSetArg(args[n],XmNwidth,(30+10*strlen(messaggio)));
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
