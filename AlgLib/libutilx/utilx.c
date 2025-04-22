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
static char SccsID[] = "@(#)utilx.c	5.1\t11/10/95";
/*
   modulo utilx.c
   tipo 
   release 5.1
   data 11/10/95
   reserved @(#)utilx.c	5.1
*/
/* utilx.c */

/* Buffo Massimo, Calleri Nicola 11/06/1992 */

/* routine di utilita' generale */

#include <stdio.h>
#include <stdlib.h>
#include <Xm/Xm.h>
#include "libutilx.h"

/* Macro per la creazioni di compound stringhe */
#define CS  			XmSTRING_DEFAULT_CHARSET
#define CREATE_CSTRING(string)  (XmStringCreateLtoR((string),CS))

/*-----------------------------------------------------------------------*/
/*** converti_stringhe( array_dest, array_sorg, num_itemi, free_mem )
 *** parametri :
 ***       array_dest : array di compound string di destinazione
 ***       array_sorg : array di stringhe sorgente
 ***       num_item   : numero elementi nell'array sorgente
 ***       free_mem   : (Booleano) indica se bisogna deallocare l'array di
 ***                    stringhe sorgenti.
Duplica un array di stringhe in un array di compound string */
void converti_stringhe( array_dest, array_sorg, num_item, free_mem )
XmString array_dest[];
char     *array_sorg[];
int      num_item;
Bool	 free_mem;
{
  int i;

  for( i = 0; i < num_item ; i++ )
  {
       array_dest[i] = CREATE_CSTRING(array_sorg[i]);
       if ( free_mem )
          XtFree( array_sorg[i] );
  }
}

/*-----------------------------------------------------------------------*/
/*** free_array_XmString( cstrings, num )
 *** parametri:
 ***            XmString cstrings : array di compound string
 ***            int      num     : numero di compound string
funzione utilizzata per deallocare la memoria utilizzata per le compound
string */
void free_array_XmString( cstrings, num )
XmString cstrings[];
int      num;
{
   int i;

   for ( i=0 ; i<num ;i++ )
      XmStringFree( cstrings[ i ] );
}

/*-----------------------------------------------------------------------*/
/*** free_array_list( lista, num )
 *** parametri:
 ***           char *lista[] : array di stringhe
 ***           int      num  : numero di stringhe
funzione utilizzata per deallocare la memoria degli array di stringhe */
void free_array_list( lista, num )
char *lista[];
int      num;
{
   while ( num )
      XtFree( lista[ num-- ] );
}


/*-----------------------------------------------------------------------*/
/*** void s_warning(toplevel, nome_appl, warning_mesg, codice)
 *** Parametri:
 ***    Widget toplevel : toplevel widget dell'applicativo (se NULL
 ***	  	 	  il messaggio viene stampato sullo standard error)
 ***    Dialog_geometry geom : impostazione della dialog-box.
 ***    char *nome_appl : nome dell'applicativo in run (descrittivo).
 ***    char *warning_mesg[] : array di stringhe contenenti i messaggi
 ***                      di warning dell'applicativo.
 ***    int codice : codice di warning ( riferimento per l'array sopra citato
Visualizza un messaggio di warning su di una dialog-box oppure , semplicemente,
sullo standard error. ***/
void s_warning(toplevel, geom, nome_appl, warning_mesg, codice)
Widget toplevel;
Dialog_geometry *geom;
char *nome_appl, *warning_mesg[];
int codice;
{
   static Widget warning_widget = NULL;
   int flag;

   if ( toplevel == NULL )
      fprintf( stderr, "%s : %s\n", nome_appl, warning_mesg[codice]);
   else
   {
      flag = ( warning_widget == NULL) ? CREA | MAPPA : MAPPA;

      warning_widget = attention(toplevel, warning_mesg[codice],
                                 flag, *geom);
   }
}

/*-----------------------------------------------------------------------*/
/*** void s_error(appl_name, error_mesg, codice)
 *** Parametri:
 ***   char *appl_name : nome dell'applicativo in run.
 ***   char *error_mesg[] : messaggi di errore
 ***   int codice : codice errore
 ***   int exit_number : numero di uscita dell'applicativo al sistema operativo
stampa messaggio di errore sullo standard error */
void s_error(appl_name, error_mesg, codice, exit_number)
char *appl_name, *error_mesg[];
int codice, exit_number;
{
   fprintf(stderr,"%s : %s\n",appl_name, error_mesg[codice]);
   exit(exit_number);
}

/*** fine utilx.c ***/
