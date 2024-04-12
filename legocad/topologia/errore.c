/**********************************************************************
*
*       C Source:               errore.c
*       Subsystem:              2
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Jul 19 10:39:05 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: errore.c-4 %  (%full_filespec: errore.c-4:csrc:2 %)";
#endif
/*
   modulo errore.c
   tipo 
   release 2.24
   data 3/30/95
   reserved @(#)errore.c	2.24
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)errore.c	2.24\t3/30/95";
/*
        Fine sezione per SCCS
*/



#include <stdarg.h>
#include "errore.h"


errore ( char * StringaErrore, ... )
{
   va_list args;

   ERR_LEVEL err_lev;
   char *str_arg;
   int  int_arg;

   char *fmt, *format, fmt_ch, save_ch, str[2001], mess[2001];
   char *format2, format_save;

   extern show_error( char * );
   extern fatal_err( char * );

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
      *fmt    = '\0';
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
      *fmt = save_ch;
   }

   va_end(args);

   strcat ( mess, format );

//   format=format_save;
//   free(format);


   /* Visualizzazione errore */
   if ( err_level == ERROR )
     show_error( mess );
   else if ( err_level == FATAL_ERROR )
     fatal_err( mess );
   else
     write_message( mess );


}


