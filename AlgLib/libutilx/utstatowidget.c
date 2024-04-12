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
static char SccsID[] = "@(#)utstatowidget.c	5.1\t11/10/95";
/*
   modulo utstatowidget.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)utstatowidget.c	5.1
*/
#include <X11/Xlib.h>
#include <Mrm/MrmAppl.h>
#include "libutilx.h"

/*
 UtStatoWidget
 ritorna lo stato di un widget
 */
int UtStatoWidget(w)
    Widget w;
{
if(w==NULL)
	return(NON_ESISTE);
else
  if(XtIsManaged(w))
	return(MAPPA);
  else
	return(UNMAPPA);
}
