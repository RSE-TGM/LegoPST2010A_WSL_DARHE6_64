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
static char SccsID[] = "@(#)set_something.c	5.1\t11/10/95";
/*
   modulo set_something.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)set_something.c	5.1
*/
#include <X11/Xlib.h>
#include <Mrm/MrmAppl.h>

void set_something();

/*
 set_something
    setta un singolo attributo di un Widget
 */
void set_something(w, resource, value)
    Widget w;
    char *resource, *value;
{
Arg al[1];
XtSetArg(al[0], resource, value);
XtSetValues(w, al, 1);
}
