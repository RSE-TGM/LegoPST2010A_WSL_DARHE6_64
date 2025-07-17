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
   modulo get_something_val.c
   tipo 
   release 5.1
   data 14/07/25
   reserved @(#)get_something_val.c	5.1
*/
#include <X11/Xlib.h>
#include <Mrm/MrmAppl.h>

#include <stdarg.h> // Necessario per le funzioni variadiche

/*
 get_something_val
    legge un singolo attributo di un Widget come un valore
 */

/**
 * get_something_val
 *
 * Recupera un valore scalare da una risorsa di un widget.
 * Funziona come un wrapper per XtVaGetValues per una singola risorsa.
 *
 * PARAMETRI:
 *   wid: Il widget da cui leggere la risorsa.
 *   resource_name: Il nome della risorsa (es. XmNwidth).
 *   value_ptr: Un puntatore a una variabile in cui verrà memorizzato
 *              il valore della risorsa (es. &my_width).
 *
 * ESEMPIO DI UTILIZZO:
 *   Dimension my_width;
 *   get_something_val(my_widget, XmNwidth, (XtPointer)&my_width);
 */
void get_something_val(Widget wid, String resource_name, XtPointer value_ptr)
{
    if (wid == NULL || resource_name == NULL || value_ptr == NULL) {
        return;
    }
    
    XtVaGetValues(wid, resource_name, value_ptr, NULL);
}


