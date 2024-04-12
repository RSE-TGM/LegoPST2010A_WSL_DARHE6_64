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

#include <stdio.h>
#include <string.h>

#include "tag.h"

/*
        la subroutine ricerca verifica l'esistenza di un punto
        data la sigla pbuf sul file fnomi
        il file fnomi e' composto da 256 blocchi + 16*4 di overflow
        in ogni blocco ci sono le prime 8 hw spare
        il ritorno =0 se il punto esiste
                   =1 se il punto non esiste
                   =2 se il nome deve essere cambiato
        se il punto non esiste in blocco ed in posiz sono
        memorizzati il blocco e la posizione all'interno
        del blocco in cui andra' inserito
*/

short r_tamp[SCD_FATBLK/2];
short r_tampo[SCD_FATBLK/2];   /* buffer per overflow */

ricerca(pbuf,point,ext,blocco,posiz,fp)

short *pbuf ; /* puntatore al nome del punto */
short *point ; /* indice  in data base */
short *ext  ; /* tipo di estensione */
long  *blocco; /* blocco in cui andra' inserito o e' inserito */
short *posiz ; /* posizione all'interno del blocco */
FILE *fp   ; /* canale open fnomi */
{

short somma,i;
long toto ;
short j;
long tot ;
short newposiz,newblocco ;
short flow ;
char *p1, *p2 ;
/*
        calcolo il blocco in cui e' inserito il nome
*/
p1= (char *) & r_tamp[0];
p2 = (char *) & r_tampo[0] ;
flow=0 ;  /* non sono ancora nei blocchi di overflow */
newblocco=-1;  /* iniz. nuovo posto non trovato */

for(i=0,somma=0;i<SCD_SIGLA;i++)
	{
	char *kk = (char*)pbuf;
	somma = (somma << ONE_EIGHT) + *(kk+i);
	if((j=somma&HIGH_BITS)!=0)
		somma = (somma^(j>>THREE_QUARTERS))&~HIGH_BITS;
        }
somma = somma % BLK_NORM;

/*
        lettura da file fnomi
*/
      /*printf(" somma %d tot*SCD_FATBLK = %d\n",somma,tot*SCD_FATBLK) ;  */
RIPROVA :
tot=somma;
rbyte(fileno(fp),r_tamp,tot*SCD_FATBLK,SCD_FATBLK) ;
/*
        ciclo di scansione del buffer per verificare
        se il nome esiste
*/
for(i=SCD_BLK_OVER_FLOW;i<(SCD_FATBLK)/2;i=i+SCD_RECORD)
{
if(!memcmp(r_tamp+i,pbuf,SCD_SIGLA))
        {
                *point=r_tamp[i+SCD_SIGLA/2];
                *ext =r_tamp[i+SCD_SIGLA/2+1];
                *blocco=somma ;
                *posiz=i;
                return(0);
        }
        if(r_tamp[i]==0 && newblocco==-1) { /* memorizzo il primo */
                        newblocco=somma ; /* posto libero */
                        newposiz=i;
                        }
}
/*
        il nome non e' stato trovato
        se sono in overflow incrememto il numero del
        blocco da esaminare fino a BLK_TOT
*/
if(flow && somma < (BLK_TOT-1)){ somma++; goto RIPROVA ;}
if(! r_tamp[SCD_OVERF] || somma >= (BLK_TOT-1)) {
     if (newblocco==-1) {
/*
      il nome deve essere cambiato
*/
         if(somma>=(BLK_TOT-1)) return(2) ;
 /* 
      esamino i blocchi di overflow per trovare un posto
      libero
*/
         for(i=BLK_NORM;i<BLK_TOT;i++)
            {
            toto=i ;
				rbyte(fileno(fp),p2,toto*SCD_FATBLK,SCD_FATBLK) ;
				for(j=SCD_BLK_OVER_FLOW;j<SCD_FATBLK/2;j=j+SCD_RECORD) 
               {    if(!r_tampo[j]) goto OK ; }
            }
            return(2) ;
OK:     
            if(!flow){              /* setto l'overflow */
                     r_tamp[SCD_OVERF]=i ;
                		wbyte(fileno(fp),p1,tot*SCD_FATBLK,SCD_FATBLK) ;
							}
            *blocco=i ;
            *posiz=j ;
            return(1);
        }
      else
        {
/*
        trovato posto libero per inserire il nuovo nome
*/
        *blocco=newblocco ;
        *posiz=newposiz ;
        return(1) ;
        }
}
flow=1;
somma=r_tamp[SCD_OVERF] ;
goto RIPROVA ;
}

