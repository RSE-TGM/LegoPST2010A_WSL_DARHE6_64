/**********************************************************************
*
*       C Source:               lc_comandi.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Jul 19 10:35:00 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: lc_comandi.c-10 %  (%full_filespec: lc_comandi.c-10:csrc:1 %)";
#endif
/*
   modulo lc_comandi.c
   tipo 
   release 2.4
   data 2/13/95
   reserved @(#)lc_comandi.c	2.4
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)lc_comandi.c	2.4\t2/13/95";
/*
        Fine sezione per SCCS
*/
/*
 lc_comandi.c
*/
#ifdef _BSD
#undef _BSD
#endif
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdlib.h>
#include <stdarg.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>

#include "legocad.h"  /* definizioni generali per legocad e le sue
                         sottoattivita' */
#include "lc_errore.h"

/*
 Esecuzione di comando di shell con intercettazione dell'output
 e sua visualizzazione tramite la routine lc_errore
*/
static char riga[2001]; /* la dimensione e' notevole perche' l'output
                           puo' essere composto da comandi di link o
                           di creazione librerie notevolmente lunghi */
esegui_comando(comando)
char *comando;
{
extern ERR_LEVEL err_level;
FILE *fp;
int retval,exit_stat;
signal(SIGCHLD,(SIG_DFL) );
fp=popen(comando,"r");
while(fgets(riga,2000,fp)!=NULL)
        {
        err_level=NO_ERROR;
        lc_errore(riga);
        }
retval=pclose(fp);
printf("\n FINE COMANDO retval=%d exit status= %d\n",retval,WEXITSTATUS(retval));
return(WEXITSTATUS(retval));
}

/* La funzione lancia_comando e' simile alla funzione esegui comando */
/* con l'eccezione che viene effettuato il dispatch degli eventi. */
lancia_comando(display, comando)
Display *display;
char *comando;
{
   extern ERR_LEVEL err_level;
   FILE *fp;
   int retval,exit_stat;
   static XEvent evento;
   Boolean predicate_proc();

   signal(SIGCHLD,(SIG_DFL) );
   fp = popen(comando,"r");
   while(fgets(riga,2000,fp) != NULL)
   {
       err_level = NO_ERROR;
        lc_errore(riga);
/*
       show_warning(riga);
*/

       while (XCheckIfEvent(display, &evento, predicate_proc, NULL))
           XtDispatchEvent(&evento);

   }
   retval = pclose(fp);
   return(WEXITSTATUS(retval));
}

/*** Boolean predicate_proc(display, event, arg)
 ***
 ***    Descrizione:
 ***       utilizzata per discriminare gli eventi da accettare ...
 ***       (in questo caso TUTTI).
 ***       La funzione viene chiamata da XCheckIfEvent in lancia_comando()
 ***/
Boolean predicate_proc(display, event, arg)
Display *display;
XEvent *event;
char *arg;
{
    return(True);
}
