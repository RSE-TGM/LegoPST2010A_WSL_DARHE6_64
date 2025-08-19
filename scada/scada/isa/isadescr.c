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
/*
        Fine sezione per SCCS
*/
/*
		la function descriz invia la descrizione di un punto in base
		al suo tipo
		se il punto e' analogico invia descrizione e unita' di misura
		se e' digitale descrizione e stati
		se e' organo descrizione e tipo di organo
*/
#include <osf1.h>
#include <stdio.h>
#include <string.h>

#include "g1tipdb.inc"
#include "g2comdb.inc"
#include "comunic.inc"
#include "dconf.inc"
#include "messcada.inc"
#include "isarc.inc"
#include "isa.h"

/* Function prototypes */
extern int rbyte(int fd, char *buffer, long offset, int len);

/*
	leggo la descrizione dai file operativi
*/

void isadescr(STINF * st, short ext,short pointdb)
   {
   char buf[64];
   long offset;
   short nbyte ;

   memset(st,' ',sizeof(STINF)) ;
	switch(ext) 
	   {
   	case g1tipaa :	 nbyte=rec_fdaa; 	offset=of_fdaa ;		break ;
   	case g1tipas :	 nbyte=rec_fdas;	offset=of_fdas ;		break ;
   	case g1tipac :	 nbyte=rec_fdac;	offset=of_fdac ;		break ;
   	case g1tipad :	 nbyte=rec_fdad;	offset=of_fdad ;		break ;
   	case g1tipao :	 nbyte=rec_fdao;	offset=of_fdao ;		break ;
	
      case g1tipda :	 nbyte=rec_fdda; 	offset=of_fdda ;		break ;
   	case g1tipds :	 nbyte=rec_fdds;	offset=of_fdds ;		break ;
   	case g1tipdc :	 nbyte=rec_fddc;	offset=of_fddc ;		break ;
	   case g1tipdd :	 nbyte=rec_fddd;	offset=of_fddd ;		break ;
   	case g1tipdo :	 nbyte=rec_fddo;	offset=of_fddo ;		break ;
      
      case g1tipor: 	nbyte=rec_fdor ;  offset=of_fdor ;    	break;
      case g1tipst:  nbyte=rec_fdst;   offset=of_fdst;      break;
      
      default:    return;
      }
   rbyte(fileno(fpp[fdde]),buf,offset+nbyte*pointdb,nbyte) ;
   memcpy(st->sigla,buf,10);           // sigla
   memcpy(st->descri,&buf[10],24);     // descrizione

	switch(ext) 
      {
      case g1tipaa :
      case g1tipas :
      case g1tipac :
      case g1tipad :
         memcpy(st->info1,&buf[34],8);           // sigla
         break;
      case g1tipda :
      case g1tipds :
      case g1tipdc :
      case g1tipdd :
         memcpy(st->info1,&buf[34],8);           // 
         memcpy(st->info2,&buf[42],8);           // 
         break;
      case g1tipao :
      case g1tipdo :
      case g1tipst: 
         break;
      case g1tipor: 
         memcpy(st->info1,&buf[34],10);           // tipo
         break;
      }
   return;
   }
