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
static char SccsID[] = "@(#)undef_cursore.c	5.1\t11/10/95";
/*
   modulo undef_cursore.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)undef_cursore.c	5.1
*/
/*  modifica l'aspetto del cursore 

per def_cursore
     padre     		widget da cui deve dipendere
*/

#include <stdio.h>
#include <X11/Xlib.h>
#include <Mrm/MrmAppl.h>
#include <X11/cursorfont.h>

#include "libutilx.h"


void undef_cursore(padre)
Widget padre;
{
XUndefineCursor(XtDisplay(padre),XtWindow(padre));
}
