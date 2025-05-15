/**********************************************************************
*
*       C Source:               f11.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Mon May 12 11:40:13 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: f11.c-3 %  (%full_filespec: f11.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)f11.c	2.2\t2/13/95";
/*
        Fine sezione per SCCS
*/
/* file f11.c */

/* Buffo Massimo, Calleri Nicola 02/07/1992 */


/* funzioni per la lettura dei risultati del calcolo stazionario */
/* memorizzati nel file f11.dat */

/* Funzioni definite utilizzabili all'esterno: */

/* - read_header_f11( fd_f11 ) */
/* - read_data_f11( fd_f11 ) */

#define TRUE	1
#define	FALSE	0

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <X11/Intrinsic.h>

#include "read_ftn.h"
#include "f11.h"

int leggi_record_ftn( int , int , int , char , int , ...);
int dim_array_f11(_INTEGER,_INTEGER,_INTEGER,_INTEGER);
void crea_array_bidim( char*[], char[], int, int );
// void crea_array_bidim( array_bd, array_mono, num_elem, size_elemento )
// char *array_bd[], array_mono[];
// int  num_elem, size_elemento;

/*-------------------------------------------------------------------*/
/*** read_header_f11( fd_f11 )
 *** Parametri :
 ***       fd_f11 : descrittore del file F11.DAT
 ***   dimensiona : indica se bisogna effettuare il dimensionamento degli
 ***                array utilizzati nella lettura dei risultati.
 funzione che inizializza le variabili e gli array opportuni leggendo
 l'header del file f11.dat.
 Ritorna l'offset del puntatore del file alla fine dell'header (cioe' alla
 prima iterazione del calcolo). */
long read_header_f11( fd_f11, dimensiona )
int  fd_f11;
int dimensiona;
{
   int  flag, dim_buffer, i;
   char unita[4];
   _INTEGER dim;

/* posiziona il puntatore all'inizio del file */
   lseek( fd_f11, 0L, SEEK_SET );

/* f11.dat : record 1 (header) */
#ifndef VMS
   read( fd_f11, unita, 4 );
#endif

#ifdef VMS
   flag = TRUE;
#else
   flag = FALSE;
#endif

/* f11.dat : record 1 (header) */
   leggi_record_ftn( fd_f11, DIMTIPO(_INTEGER,4), 1, flag, 4, 
                     &neqsis_f11,sizeof(_INTEGER),
                     &npvrt_f11,sizeof(_INTEGER),
                     &nu_f11,sizeof(_INTEGER),
                     &nvart_f11,sizeof(_INTEGER));

/* dimensiona gli array del file f11.dat se richiesto */
   if (dimensiona)
      dim_array_f11( neqsis_f11, npvrt_f11, nu_f11, nvart_f11);

   dim_buffer = DIMTIPO(char,8) + sizeof(_REAL) + DIMTIPO(_INTEGER,2);

/* f11.dat : record 2 (header) */
   leggi_record_ftn( fd_f11, dim_buffer, neqsis_f11, TRUE, 4,
                     varsi[0], DIMTIPO(char,8),
                     xy0, sizeof(_REAL),
                     iresbl, sizeof(_INTEGER),
                     ibleqz, sizeof(_INTEGER));

/* f11.dat : record 3 (header) */
   leggi_record_ftn( fd_f11, sizeof(_INTEGER), neqsis_f11+1, TRUE, 1,
                     ips_f11, sizeof(_INTEGER));

/* f11.dat : record 4 (header) */
   leggi_record_ftn( fd_f11, sizeof(_INTEGER), npvrt_f11, TRUE, 1,
                     ipvrt_f11, sizeof(_INTEGER));

/* f11.dat : record 5 (header) */
   dim_buffer = DIMTIPO(char,8) + sizeof(_REAL);

   leggi_record_ftn( fd_f11, dim_buffer, nu_f11, TRUE, 2,
                     varno[0], DIMTIPO(char,8),
                     uu, sizeof(_REAL));

/* f11.dat : record 6 (header) */
   dim_buffer = sizeof(_REAL) + sizeof(_INTEGER);
   leggi_record_ftn( fd_f11, dim_buffer, nvart_f11, TRUE, 2,
                     cnxyu , sizeof(_REAL),
                     ipvrs_f11_bis, sizeof(_INTEGER));

   ipvrs_f11=ipvrs_f11_bis; 

   for(i=0 ; i<neqsis_f11 ; i++ )
   {
      char tt[60];

  /* dim e' uguale al numero delle variabili del blocco ... */
      leggi_record_ftn( fd_f11, sizeof(_INTEGER), 1, TRUE, 1, &dim,
                        sizeof(_INTEGER));

      dim_buffer = sizeof(_REAL) + DIMTIPO(char,60);
      leggi_record_ftn( fd_f11, dim_buffer, 1, FALSE, 3,
                        signeq[i], DIMTIPO(char,50),
                        uniteq[i], DIMTIPO(char,10),
                       &cosnor[i], sizeof(_REAL));

      leggi_record_ftn( fd_f11, sizeof(_INTEGER), dim, FALSE, 1,
                        itopva[i], sizeof(_INTEGER));
   }
   return( lseek( fd_f11, 0L, SEEK_CUR ));
}

/*-------------------------------------------------------------------*/
/*** read_data_f11( fd_f11 )
 *** Parametri :
 ***            fd_f11 : descrittore del file F11.DAT
funzione che legge le informazioni memorizzate durante il calcolo dello
stazionario nel file F11.DAT . chi utilizza tale funzione deve preoccuparsi
di spostare il puntatore del file alla fine dell'header del file (E' suf=
ficiente ,comunque, chiamare prima la funzione che legge l'header e,
successivamente, questa funzione).
Ritorna 0 se tutto ok, ritorna 1 se si e' raggiunti la fine del file */
int read_data_f11( fd_f11 )
int fd_f11;
{
   int uscita, dim_buffer;

/* Leggi il valore di IRC11 per sapere quali informazioni sono memorizzate
   successivamente */
   uscita = leggi_record_ftn( fd_f11, sizeof(_INTEGER), 1, TRUE, 1,
                             &irc11, sizeof(_INTEGER));
   if ( uscita )
      return(1);

   switch ( irc11 ) {

          case C_RESIDUI: 
                  dim_buffer = DIMTIPO(_REAL,2) + sizeof(_INTEGER);
                  leggi_record_ftn( fd_f11, dim_buffer, neqsis_f11,
                                    TRUE, 3,
	                            xy, sizeof(_REAL),
			            rn, sizeof(_REAL),
				    iconv, sizeof(_INTEGER));

                  leggi_record_ftn( fd_f11, DIMTIPO(_INTEGER,3), 1, FALSE, 3,
				    &itert, sizeof(_INTEGER),
				    &iconve, sizeof(_INTEGER),
				    &norma, sizeof(_INTEGER));
                  break;

          case C_SOLUZIONI:
                  leggi_record_ftn( fd_f11, sizeof(_INTEGER), 1, TRUE, 1,
				    &itert, sizeof(_INTEGER));

                  leggi_record_ftn( fd_f11, sizeof(_REAL), neqsis_f11,
                                     FALSE, 1,
			             tn, sizeof(_REAL));
                   break;

          case C_JACOBIANO:
                  leggi_record_ftn( fd_f11, DIMTIPO(_INTEGER,2), 1, TRUE, 2,
				    &nzter, sizeof(_INTEGER),
				    &itert, sizeof(_INTEGER));

                  dim_buffer = sizeof(_REAL) + DIMTIPO(_INTEGER,2);
                  leggi_record_ftn( fd_f11, dim_buffer, nzter,
                                    FALSE, 3,
			            irj, sizeof(_INTEGER),
				    icj, sizeof(_INTEGER),
				    fj,  sizeof(_REAL));

                  leggi_record_ftn( fd_f11, sizeof(_INTEGER), 1, TRUE, 1,
				    &iflag, sizeof(_INTEGER));
                  break;

          case C_PROBLEMI:
                  leggi_record_ftn( fd_f11, DIMTIPO(_INTEGER,3), 1, TRUE, 3,
			            &itert, sizeof(_INTEGER),
				    &kbeta, sizeof(_INTEGER),
				    &ibeta, sizeof(_INTEGER));

                  leggi_record_ftn( fd_f11, sizeof(_REAL), neqsis_f11,
                                    FALSE, 1,
			            xy, sizeof(_REAL));
                  break;

          case C_MAX_JACOBIANI:
                  break;

          case C_NON_OK:
                  dim_buffer = DIMTIPO(_INTEGER,2) + DIMTIPO(_REAL,2);
                  leggi_record_ftn( fd_f11, dim_buffer, 1, TRUE, 4,
				    &icef    , sizeof(_INTEGER),
			            &irx     , sizeof(_INTEGER),
				    &residuo , sizeof(_REAL),
				    &tolle   , sizeof(_REAL));
                  break;
                     
          case C_OK:
                  leggi_record_ftn( fd_f11, 2*sizeof(_INTEGER), 1, TRUE, 2,
				    &itert, sizeof(_INTEGER),
				    &jac  , sizeof(_INTEGER));

                  leggi_record_ftn( fd_f11, sizeof(_REAL), neqsis_f11,
                                    FALSE, 1,
			            xy, sizeof(_REAL));

                  break;
   }
   return(0);
}

/*-------------------------------------------------------------------*/
/*** dim_array_f11(neqsis,npvrt,nu,nvart) */
/* funzione che alloca dinamicamente memoria per gli array utilizzati nelle */
/* lettura del file f11.dat. Tale procedura deve essere chiamata prima della */
/* lettura dei dati del file. */
/* Ritorna -1 se c'e stato errore di allocazione della memoria. */
int dim_array_f11(neqsis,npvrt,nu,nvart)
_INTEGER neqsis,nu,nvart,npvrt;
{
   varsi       = (char **) XtCalloc( neqsis, sizeof(char *));
   xy0         = (_REAL *) XtCalloc( neqsis, sizeof(_REAL));
   xy          = (_REAL *) XtCalloc( neqsis, sizeof(_REAL));
   iresbl      = (_INTEGER  *) XtCalloc( neqsis, sizeof(_INTEGER));
   ibleqz      = (_INTEGER  *) XtCalloc( neqsis, sizeof(_INTEGER));
   varno       = (char **) XtCalloc( nu, sizeof(char *));
   uu          = (_REAL *) XtCalloc( nu, sizeof(_REAL));
   cnxyu       = (_REAL *) XtCalloc( nvart, sizeof(_REAL));
   ipvrs_f11   = (_INTEGER  *) XtCalloc( nvart, sizeof(_INTEGER ));
   ips_f11     = (_INTEGER  *) XtCalloc( neqsis+1, sizeof(_INTEGER ));
   ipvrt_f11   = (_INTEGER  *) XtCalloc( npvrt, sizeof(_INTEGER ));
   rn          = (_REAL *) XtCalloc( neqsis, sizeof(_REAL));
   tn          = (_REAL *) XtCalloc( neqsis, sizeof(_REAL));
   iconv       = (_INTEGER *)  XtCalloc( neqsis, sizeof(_INTEGER));
   fj          = (_REAL *) XtCalloc( neqsis*neqsis, sizeof(_REAL));
   irj         = (_INTEGER *)  XtCalloc( neqsis*neqsis, sizeof(_INTEGER));
   icj         = (_INTEGER *)  XtCalloc( neqsis*neqsis, sizeof(_INTEGER));
   ipvrs_f11_bis   = (_INTEGER  *) XtCalloc( nvart*10, sizeof(_INTEGER ));
/**** significato delle equazioni ****/
   signeq      = (char **) XtCalloc( neqsis, sizeof(char *));
   uniteq      = (char **) XtCalloc( neqsis, sizeof(char *));
   cosnor      = (_REAL *) XtCalloc( neqsis, sizeof(_REAL));
   itopva      = (_INTEGER **)  XtCalloc( neqsis, sizeof(_INTEGER *));
   
   if (varsi    == NULL || xy        == NULL || iresbl == NULL ||
       ibleqz   == NULL || varno     == NULL || uu     == NULL ||
       cnxyu    == NULL || ipvrs_f11 == NULL || ips_f11== NULL ||
       rn       == NULL || tn        == NULL || iconv  == NULL ||
       fj       == NULL || irj       == NULL || icj    == NULL ||
       ipvrt_f11== NULL || signeq    == NULL || uniteq == NULL ||
       cosnor   == NULL || itopva    == NULL )
      return(-1);

   varno[0]    = (char *) XtCalloc( nu, DIMTIPO(char,8));
   varsi[0]    = (char *) XtCalloc( neqsis, DIMTIPO(char,8));
   signeq[0]   = (char *) XtCalloc( neqsis, DIMTIPO(char,50));
   uniteq[0]   = (char *) XtCalloc( neqsis, DIMTIPO(char,10));
   itopva[0]   = (_INTEGER *) XtCalloc( neqsis, DIMTIPO(_INTEGER,nu+neqsis));
   if (varsi[0]  == NULL || varno[0]  == NULL || signeq[0] == NULL ||
       uniteq[0] == NULL || itopva[0] == NULL )
      return(-1);

/* Creazione degli array bidimensionali.  ( solitamente sono array 
   di stringhe ) */
   crea_array_bidim( varsi, varsi[0], neqsis, DIMTIPO(char,8));
   crea_array_bidim( varno, varno[0], nu, DIMTIPO(char,8));
   crea_array_bidim( signeq, signeq[0], neqsis, DIMTIPO(char,50));
   crea_array_bidim( uniteq, uniteq[0], neqsis, DIMTIPO(char,10));
   crea_array_bidim( (char **)itopva, (char*)itopva[0], neqsis, DIMTIPO(_INTEGER,nu+neqsis));
   return(0);
}

/*** Fine file f11.c ***/
