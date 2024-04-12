/**********************************************************************
*
*       C Source:               cursore.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Tue Sep 10 14:16:23 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: cursore.c,3 %  (%full_filespec: 1,csrc,cursore.c,3 %)";
#endif
/*  modifica l'aspetto del cursore 

per def_cursore
     padre     		widget da cui deve dipendere
     tipo_cursore	tipo di cursore da settare 
*/

#include <stdio.h>
#include <X11/Xlib.h>
#include <Mrm/MrmAppl.h>
#include <X11/cursorfont.h>

#include "libutilx.h"


void def_cursore(padre,tipo_cursore)
Widget padre;
int tipo_cursore;
{
Cursor cursore;
if(tipo_cursore==OROLOGIO) tipo_cursore=XC_watch;
else if(tipo_cursore==BARCA) tipo_cursore=XC_boat;
else if(tipo_cursore==PENDOLO) tipo_cursore=XC_clock;
else if(tipo_cursore==SCAMBIA) tipo_cursore=XC_exchange;
else if(tipo_cursore==PENNA) tipo_cursore=XC_pencil;
else if(tipo_cursore==TESCHIO) tipo_cursore=XC_pirate;

cursore=XCreateFontCursor(XtDisplay(padre),tipo_cursore);
XDefineCursor((XtDisplay(padre)),(XtWindow(padre)),cursore);
XSync((XtDisplay(padre)),False);

}


void undef_cursore(padre)
Widget padre;
{
XUndefineCursor(XtDisplay(padre),XtWindow(padre));
}


void cursore_attesa(padre,flag)
Widget padre;
int flag;
{
if(!XtIsRealized(padre)) return;
if(flag)
	{
	def_cursore(padre,OROLOGIO);
	}
else
	{
	undef_cursore(padre);
	}
}

