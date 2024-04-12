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
static char SccsID[] = "@(#)def_cursore.c	5.1\t11/10/95";
/*
   modulo def_cursore.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)def_cursore.c	5.1
*/
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
XDefineCursor(XtDisplay(padre),XtWindow(padre),cursore);
XSync(XtDisplay(padre),False);
}
