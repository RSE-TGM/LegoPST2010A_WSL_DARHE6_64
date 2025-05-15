/**********************************************************************
*
*       C Source:               lc_errore.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Jul 19 10:28:47 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: lc_errore.c-7 %  (%full_filespec: lc_errore.c-7:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)lc_errore.c	2.2\t2/13/95";
/*
        Fine sezione per SCCS
*/
/*
 Provveda alla formattazione di stringhe di errore o warning e alla successiva
 chiamata alle funzioni ( tipiche dell'interfaccia) che permettono 
 la visualizzazione dei warning (show_warning) e di errore (show_error).
 Le due funzioni citate devono definite esternamente insieme alla
 variabile globale err_level (che puo' assumere i valori NO_ERROR,
 WARNING ed ERROR). 
*/

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#include "lc_errore.h"
static char str[2001],mess[2001];

void show_warning(char*);


void lc_errore ( char * StringaErrore, ... )
{
   va_list args;

   char *str_arg;
   int  int_arg;

   char *fmt, *format, fmt_ch, save_ch;

   char* format2;

   char* format_save;

   extern void show_error( char * );

   extern ERR_LEVEL err_level;



   va_start(args, StringaErrore);


   /* Il primo parametro contiene la stringa di format. Il numero ed il 
    * tipo dei restanti parametri e' determinato dai specificatori di formato
    * contenuti nella stringa.
    */
   format = malloc (2001*sizeof(char));
   format_save = format;
   strcpy(format, StringaErrore);   


   /* Costruzione del messaggio di errore
    */
   if ( err_level == WARNING )
      strcpy ( mess, "Warning: " );
   else
      *mess='\0';

   for ( ; fmt = (char*)strchr ( format, '%' ); format = fmt )
   {
      fmt_ch  = *(++fmt);
      save_ch = *(++fmt);

#ifdef LINUX
      *fmt    = '\0';
#else
      *fmt    = '\0';
#endif

      switch ( fmt_ch )
      { 
         case 's':
                   str_arg = va_arg(args, char *);
                   sprintf ( str, format, str_arg );
                   break;
         case 'd':
                   int_arg = va_arg(args, int);
                   sprintf ( str, format, int_arg );
                   break;
         default: 
                   /* sto pippo */
                   break;
      }
 
      strcat ( mess, str );

#ifdef LINUX
      *fmt = save_ch;
#else
      *fmt = save_ch;
#endif

   }

   va_end(args);

   strcat ( mess, format );

   free(format_save);


   /* Visualizzazione errore */
   if ( err_level == ERROR )
     show_error( mess );
   else
     show_warning( mess );


}


