/**********************************************************************
*
*       C Source:               f03.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 14:09:59 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: f03.c,2 %  (%full_filespec: 1,csrc,f03.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)f03.c	2.2\t2/13/95";
/*
        Fine sezione per SCCS
*/
/*** file f03.c ***/

/* Buffo Massimo, Calleri Nicola 02/07/1992 */

/* contiene la funzione per la lettura del file binario fortran f03.dat */
/* dimensiona e aggiorna gli array relativi (per maggior chiarezza */
/* riportano lo stesso nome utilizzato nel FORTRAN) */

/* funzioni utilizzabili dall'esterno: */
/* - read_file_f03(). */
#define  TRUE	1
#define  FALSE	0

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>

#include "read_ftn.h"
#include "f03.h"

/* Global variable definitions */
_INTEGER  nbl, neqal, nbl1, nvart, neqsis, neqs1, npvrt;
_INTEGER  nu, nu1, nvri, isiss, nbtri, nst;

char     sigla[8];
char     *nosl;

char     **nosub, **noblc, **nom_bloc;
_INTEGER *nusta, *nusci, *ningr, *islb;

_INTEGER *ip;   /* IP(1,NBL1)   puntatore alle variabili */
char     **var;
_INTEGER *ipvrs;

_INTEGER *ips; /* IPS(1,NEQS1) puntatore variabili di uscita e di stato */
char     **sivar, **nom_sivar;
_INTEGER *iout_sivar;

_INTEGER *ipvrt; /* IPVRT(1,NPVRT) puntatore alle incognite(+) o noti(-) */

_INTEGER *ipi;  /* IPI(1,NPVRT) puntatore alle variabili di ingresso */
char     **vari, **nom_vari;
_INTEGER *iout_vari;

_INTEGER *ipvri; /* IPVRI(1,NVRI)  puntatore alla roulette */

int leggi_record_ftn( int , int , int , char , int , ...);
int dim_array_f03();
void crea_array_bidim( char*[], char[], int, int );


/*** read_file_f03() */
/* funzione che inizializza le variabili e gli array opportuni leggendo */
/* le informazioni dal file f03.dat. Ritorna 0 se tutto ok, altrimenti */
/* ritorna -1 se c'e' stato qualche errore (errore di apertura del file) */
int read_file_f03()
{
   int  fd_f03, flag, dim_buffer;
   char unita[4];

   fd_f03 = open(FILE_F03, O_RDONLY);
   if ( fd_f03 == -1 )
      return(-1);

/* inizio lettura del file f03.dat.
   i primi due record contengono l'header del file f03.dat (i dati dell'header
   sono utilizzati per conoscere le dimensioni degli array)  */
#ifndef VMS
   read( fd_f03, unita, 4 );
#endif

/* f03.dat: record 1 */

#ifdef __VAX__
   flag = TRUE;
#else
   flag = FALSE;
#endif

   leggi_record_ftn( fd_f03, DIMTIPO(_INTEGER,10), 1, flag, 10,
                     &nbl, sizeof(_INTEGER),
                     &neqal, sizeof(_INTEGER),
                     &nbl1, sizeof(_INTEGER),
                     &nvart, sizeof(_INTEGER),
                     &neqsis, sizeof(_INTEGER),
                     &neqs1, sizeof(_INTEGER),
                     &npvrt, sizeof(_INTEGER),
                     &nu, sizeof(_INTEGER),
                     &nu1, sizeof(_INTEGER),
                     &nvri, sizeof(_INTEGER));

/* f03.dat: record 2 */
   dim_buffer = DIMTIPO(_INTEGER,3) + DIMTIPO(char,8);

   leggi_record_ftn( fd_f03, dim_buffer, 1, TRUE, 4,
                     &isiss, sizeof(_INTEGER),
                     &nbtri, sizeof(_INTEGER),
                     &nst, sizeof(_INTEGER),
                     sigla, DIMTIPO(char,8));

/* Allocazione dinamica della memoria per gli array */
   if ( dim_array_f03() )
       return(-1);

   leggi_record_ftn( fd_f03, DIMTIPO(char,4), nst, FALSE,
                     1, nosl, DIMTIPO(char,4));

/* f03.dat: record 3 */
   dim_buffer = DIMTIPO(char,92) + DIMTIPO(_INTEGER,4);

   leggi_record_ftn( fd_f03, dim_buffer, nbl, TRUE, 7,
                     nosub[0], DIMTIPO(char,4),
                     noblc[0], DIMTIPO(char,8),
                     nusta, sizeof(_INTEGER),
                     nusci, sizeof(_INTEGER),
                     ningr, sizeof(_INTEGER),
                     islb , sizeof(_INTEGER),
                     nom_bloc[0], DIMTIPO(char,80));

/* f03.dat: record 4  */
  leggi_record_ftn( fd_f03, sizeof(_INTEGER), nbl1, TRUE, 1, ip,
                    sizeof(_INTEGER));

  dim_buffer = DIMTIPO(char,8) + sizeof(_INTEGER);

  leggi_record_ftn( fd_f03, dim_buffer, nvart, FALSE,
                    2, var[0], DIMTIPO(char,8), ipvrs, sizeof(_INTEGER)); 

/* f03.dat: record 5 */
   leggi_record_ftn( fd_f03, sizeof(_INTEGER), neqs1, TRUE, 1,
                     ips, sizeof(_INTEGER)); 

   dim_buffer = DIMTIPO(char,108) + sizeof(_INTEGER);

   leggi_record_ftn( fd_f03, dim_buffer, neqsis, FALSE, 3,
                     sivar[0], DIMTIPO(char,8),
                     nom_sivar[0],DIMTIPO(char,100),
                     iout_sivar, sizeof(_INTEGER));

   leggi_record_ftn( fd_f03, sizeof(_INTEGER), npvrt, FALSE, 1,
                     ipvrt, sizeof(_INTEGER)); 

/* f03.dat: record 6 */
   leggi_record_ftn( fd_f03, sizeof(_INTEGER), nu1, TRUE, 1, ipi,
                     sizeof(_INTEGER));

   dim_buffer = DIMTIPO(char,108) + sizeof(_INTEGER);

   leggi_record_ftn( fd_f03, dim_buffer, nu, FALSE, 3,
                     vari[0], DIMTIPO(char,8),
                     nom_vari[0], DIMTIPO(char,100),
                     iout_vari, sizeof(_INTEGER));

   leggi_record_ftn( fd_f03, sizeof(_INTEGER), nvri, FALSE, 1,
                     ipvri, sizeof(_INTEGER)); 

   close( fd_f03 );
   return(0);
}
/*-------------------------------------------------------------------*/
/*** crea_array_dinamici() */
/* funzione che alloca dinamicamente memoria per gli array utilizzati nella */
/* lettura del file f03.dat. */
/* Ritorna 0 se tutto ok, altrimenti -1 */
int dim_array_f03()
{
   nosl        = (char *)  calloc( nst, DIMTIPO(char,4));
   nosub       = (char **) calloc( nbl, sizeof(char *));
   noblc       = (char **) calloc( nbl, sizeof(char *));
   nom_bloc    = (char **) calloc( nbl, sizeof(char *));
   nusta       = (_INTEGER * ) calloc( nbl, sizeof(_INTEGER));
   nusci       = (_INTEGER * ) calloc( nbl, sizeof(_INTEGER));
   ningr       = (_INTEGER * ) calloc( nbl, sizeof(_INTEGER));
   islb        = (_INTEGER * ) calloc( nbl, sizeof(_INTEGER));
   ip          = (_INTEGER *)  calloc( nbl1, sizeof(_INTEGER));
   var         = (char **) calloc( nvart, sizeof(char *));
   ipvrs       = (_INTEGER *)  calloc( nvart, sizeof(_INTEGER));
   ips         = (_INTEGER *)  calloc( neqs1, sizeof(_INTEGER));
   sivar       = (char **) calloc( neqsis, sizeof(char *));
   nom_sivar   = (char **) calloc( neqsis, sizeof(char *));
   iout_sivar  = (_INTEGER *)  calloc( neqsis, sizeof(_INTEGER  ));
   ipvrt       = (_INTEGER *)  calloc( npvrt, sizeof(_INTEGER));
   ipi         = (_INTEGER *)  calloc( nu1, sizeof(_INTEGER));
   vari        = (char **) calloc( nu, sizeof(char *));
   nom_vari    = (char **) calloc( nu, sizeof(char *));
   iout_vari   = (_INTEGER *)  calloc( nu, sizeof(_INTEGER  ));
   ipvri       = (_INTEGER *)  calloc( nvri, sizeof(_INTEGER));
   
   if (nosl     == NULL || nosub     == NULL || noblc  == NULL || 
       nom_bloc == NULL || nusta     == NULL || nusci  == NULL ||
       ningr    == NULL || ip        == NULL || var    == NULL ||
       ipvrs    == NULL || ips       == NULL || sivar  == NULL ||
       ipvrt    == NULL || ipi       == NULL || vari   == NULL ||
       nom_vari == NULL || iout_vari == NULL || ipvri  == NULL )
      return(-1);

   nosub[0]    = (char *) calloc( nbl, DIMTIPO(char,4));
   noblc[0]    = (char *) calloc( nbl, DIMTIPO(char,8));
   nom_bloc[0] = (char *) calloc( nbl, DIMTIPO(char,80));
   var[0]      = (char *) calloc( nvart, DIMTIPO(char,8));
   sivar[0]    = (char *) calloc( neqsis, DIMTIPO(char,8));
   nom_sivar[0]= (char *) calloc( neqsis, DIMTIPO(char,100));
   vari[0]     = (char *) calloc( nu, DIMTIPO(char,8));
   nom_vari[0] = (char *) calloc( nu, DIMTIPO(char,100));
   if (nosub[0] == NULL || noblc[0]    == NULL || nom_bloc[0]  == NULL ||
       var[0]   == NULL || sivar[0]    == NULL || nom_sivar[0] == NULL ||
       vari[0]  == NULL || nom_vari[0] == NULL )
      return(-1);

/* Creazione degli array bidimensionali.  ( solitamente sono array 
   di stringhe ) */
   crea_array_bidim( nosub, nosub[0], nbl, DIMTIPO(char,4));
   crea_array_bidim( noblc, noblc[0], nbl, DIMTIPO(char,8));
   crea_array_bidim( nom_bloc, nom_bloc[0], nbl, DIMTIPO(char,80));
   crea_array_bidim( var, var[0], nvart, DIMTIPO(char,8));
   crea_array_bidim( nom_sivar, nom_sivar[0], neqsis, DIMTIPO(char,100));
   crea_array_bidim( sivar, sivar[0], neqsis, DIMTIPO(char,8));
   crea_array_bidim( nom_vari, nom_vari[0], nu, DIMTIPO(char,100));
   crea_array_bidim( vari, vari[0], nu, DIMTIPO(char,8));
   return(0);
}

/*** Fine file f03.c ***/
