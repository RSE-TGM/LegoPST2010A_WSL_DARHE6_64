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
static char SccsID[] = "@(#)get_something.c	5.1\t11/10/95";
/*
   modulo get_something.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)get_something.c	5.1
*/
#include <X11/Xlib.h>
#include <Mrm/MrmAppl.h>

void get_something();

/*
 get_something
    legge un singolo attributo di un Widget
 */
void get_something(w, resource, value)
    Widget w;
    char *resource, *value;
{
Arg al[1];
XtSetArg(al[0], resource, value);
XtGetValues(w, al, 1);
}
