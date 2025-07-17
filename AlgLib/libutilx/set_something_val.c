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
static char SccsID[] = "@(#)set_something_val.c	5.1\t11/10/95";
/*
   modulo set_something_val.c
   tipo 
   release 5.1
   data 14/07/25
   reserved @(#)set_something_val.c	5.1
*/
#include <X11/Xlib.h>
#include <Mrm/MrmAppl.h>

 #include <stdarg.h> // Necessario per le funzioni variadiche

//static void set_something(Widget, char*, void*);

/*
 set_something_val
    setta un singolo attributo di un Widget come valore
 */


/**
 * set_something_val
 *
 * Imposta una risorsa di un widget a un valore scalare (non un puntatore).
 * Funziona come un wrapper per XtVaSetValues per una singola risorsa.
 * Il valore viene passato per copia, non per riferimento.
 *
 * ATTENZIONE: Il tipo del valore passato (es. int, Dimension, Boolean)
 * deve corrispondere a quello che la risorsa si aspetta. XtArgVal è un
 * tipo abbastanza grande da contenere un puntatore o un intero lungo.
 */
void set_something_val(Widget wid, String resource_name, XtArgVal value)
{
    if (wid == NULL || resource_name == NULL) {
        return;
    }
    
    XtVaSetValues(wid, resource_name, value, NULL);
}

