/**********************************************************************
*
*       C Source:               read_ftn.c
*       Subsystem:              3
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Jul 19 10:09:06 2005 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: read_ftn.c-5 %  (%full_filespec: read_ftn.c-5:csrc:3 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)read_ftn.c	1.2\t3/21/96";
/*
   modulo read_ftn.c
   tipo 
   release 1.2
   data 3/21/96
   reserved @(#)read_ftn.c	1.2
*/

/*
        Fine sezione per SCCS
*/
/* file read_ftn.c */

/* Buffo Massimo, Calleri Nicola 02/07/1992 */

/* Contiene le funzioni che trattano i file scritti in fortran */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdarg.h>

#include "read_ftn.h"

/*** leggi_record_ftn( fd, dim, num_elem, nuovo_record, narg, ... )
 *** Parametri :
 ***           fd : descrittore del file fortran
 ***          dim : dimensione del buffer
 ***     num_elem : numero elementi da leggere
 *** nuovo_record : flag che indica se e' un nuovo record (TRUE)
 ***         narg : numero di variabili passati come argomenti
 ***
 *** (successivamente gli argomenti devono essere passati a coppie e cioe'
 ***  puntatore della variabile e dimensione della variabili)
funzione che permette di leggere un file in formato fortran. Bisogna fare
attenzione che il fortran ,quando memorizza una serie di informazioni con
una singola WRITE, aggiunge dei byte all'inizio del record.Di qui la
necessita' di utilizzare un flag (nuovo record) per sapere se tratto
un nuovo record o meno. */

leggi_record_ftn( int fd, int dim, int num_elem, char nuovo_record, int narg, ...)
{
   char    unita[10], buffer[BUFSIZE], *ptr;
   int     i, j, val, pos, bytes_tot, bytes_letti;
   va_list arg;

   if ( nuovo_record ) {
#ifdef VMS
      read( fd, unita, 2 ); 
#else
      read( fd, unita, 8 ); 
#endif

#if defined x86_64
      read( fd, unita, 8 );
#endif
   }

   for ( i=0 ; i < num_elem ; i++ )
   {
      bytes_letti = read( fd, buffer, dim );
      if ( bytes_letti == -1)
         return(1); /* Errore di lettura del file fortran! */

      if ( bytes_letti == 0)
         return( 1 );

      bytes_tot = bytes_letti;
      while ( bytes_tot < dim && bytes_letti)
      {

#ifdef VMS
         read( fd, unita, 2 );
#endif
/*
         bytes_letti = read( fd, buffer+bytes_tot, dim-bytes_tot );
*/
	bytes_letti = read( fd, &buffer[bytes_tot], dim-bytes_tot );
         bytes_tot += bytes_letti + 2;
      }

 /* Assegna il contenuto opportuno a ciascuna variabile */
     pos = 0;
     va_start( arg, narg );
     for (j=0; j < narg; j++)
     {
        ptr = va_arg( arg, char *);
        val = va_arg( arg, int );
        ptr += val*i; 
/*
        memcpy( ptr, buffer+pos, val );
*/
	memcpy( ptr, &buffer[pos], val);
        pos += val;
     }
     va_end( arg );
   }
   return( 0 );
}

/*-------------------------------------------------------------------*/
/*** crea_array_bidim( array_bd, array_mono, num_elem, size_elemento
 *** Parametri :
 ***             array_bd : array di puntatori (char *)
 ***             array_mono : array monodimensionale che contiene i dati
 ***             num_elem : numero di puntatori in array_bd
 ***             size_elemento : ampiezza in byte (char) di ciascun elemento
la funzione aggiusta i puntatori dell'array array_bd in array_mono */ 
crea_array_bidim( array_bd, array_mono, num_elem, size_elemento )
char *array_bd[], array_mono[];
int  num_elem, size_elemento;
{
   int i;

   for ( i = 0 ; i < num_elem ; i ++ )
     array_bd[ i ] = &array_mono[ i*size_elemento ];
}


/*** fine read_ftn.c ***/
