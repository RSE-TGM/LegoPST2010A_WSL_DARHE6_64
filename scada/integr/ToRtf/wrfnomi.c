/*
   modulo wrfnomi.c
   tipo 
   release 2.6
   data 6/13/96
   reserved @(#)wrfnomi.c	2.6
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#include <osf1.h>
#include <stdio.h>
#include <string.h>
#include <tag.h>

/* 
      la subroutine wrfnomi dato il blocco la posizione 
      inserisce un nuovo punto nel file fnomi
*/

short r_tamp[SCD_FATBLK/2];


wrfnomi(pbuf,point,ext,blocco,posiz,fp)

short *pbuf ; /* puntatore al nome del punto */
short point ; /* indice in data base */
short ext ;   /* tipo di estensione */
long  blocco ;/* blocco in cui andra' inserito o e' inserito */
int   posiz ; /* posizione all'interno del blocco */
FILE *fp ;    /* canale open del file */

{
short ier,j,numread ;
int i   ;

/*
        lettura e scrittura sul file fnomi
*/
ier=fseek(fp,blocco*SCD_FATBLK,0) ;
if(ier){ return(-1) ;}
numread=fread(r_tamp,SCD_FATBLK,1,fp) ;
/*
        inserimento del nome del puntatore nel buffer
*/
for(i=0;i<SCD_SIGLA/2;i++)
        r_tamp[i+posiz]=*(pbuf+i) ;
r_tamp[posiz+SCD_SIGLA/2]= point ;
r_tamp[posiz+SCD_SIGLA/2+1]= ext ;
ier=fseek(fp,blocco*SCD_FATBLK,0);
if(ier){perror("fseek 2 wrfnomi");  return(-1) ;}
numread=fwrite(r_tamp,SCD_FATBLK,1,fp);
fflush(fp) ;
return(0);
}
