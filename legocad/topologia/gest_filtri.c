/**********************************************************************
*
*       C Source:               gest_filtri.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Jan 21 12:14:48 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: gest_filtri.c-3 %  (%full_filespec: gest_filtri.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)gest_filtri.c	2.24\t3/30/95";
/*
        Fine sezione per SCCS
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filtri.h"

extern FILTRI *filtri;
FILE *fpedf;

/* filtro_init() 
   Parametri: none
   Ret Value: ftr    - puntatore al vettore filtri  - 
 
   inizializza il vettorre dei filtri 

*/
FILTRI *filtro_init() 
{
   short j;
   FILTRI *ftr;

   ftr = (FILTRI *)(calloc(1,DIM_FILTRO));
   for(j=0;j<MAXPARFILTRO;j++)
   {
      ftr->var[j] = (char *)(calloc(1, DIM_PAR )); 
   }
   return(ftr);
}

int libera_filtri(FILTRI *filtri,int num_filtri)
{
   int j;

   for(j=0;j<MAXPARFILTRO;j++)
      free(filtri->var[j]);

   free(filtri);
   return 0;
}

/*=================================================================== 
| 
|  openedf:   apertura file di editing.  Il file pointer e' globale
|             ed e' definito in filtri.h. Attualmente il nome del file
|             e' cablato ed anche lui risiede in filtri.h, cosi' come
|             le definizioni di errore.
|
===================================================================*/

int openedf()
{
   char fname[300],*getenv();

   strcpy(fname,getenv("LEGOCAD_USER")); 
   strcat(fname,"/filtri.edf");

   if( ( fpedf=fopen(fname,"r+") ) == NULL)
   {
/*      fclose(fpedf); */
      system("touch $LEGOCAD_USER/filtri.edf"); 
      if( (fpedf=fopen(fname,"r+")) == NULL)
      {
         printf("Impossible open file %s/filtri.edf\n",getenv("HOME")); 
         return(-1);
      }
      return(-1);
       
   }

   return(OK);
}



/*===================================================================
|
|  readedf:   lettura file di editing.  Il file pointer e' globale
|             ed e' definito in filtri.h. 
|             cosi come le condizioni di errore
|
|             struttura record del file:
|
|             FILTRO nome
|             var1
|             var2
|             FILTRO nome
|             var1
|             ....
|
===================================================================*/

int readedf(FILTRI *filtri[],int *num_filtri)
{
   char buff[MAXCHNAME];
   short i=0,j=0,filtro_corrente=0;
 
   while(1)
   {
/* lettura record del file */
      fscanf(fpedf,"%s",buff);
/* fine del file */
      if(feof(fpedf))
      {
         fclose(fpedf);
         break;
      }
/* inizio definizione nuovo filtro */
      if(!strcmp(buff,TAPPO))   
      {
/* avendo letto il TAPPO adesso leggo il nome filtro */
         fscanf(fpedf,"%s",buff);
         strcpy(filtri[i]->nome_filtro,buff);
         filtro_corrente=i;
         i++;
         j=0;
      }
      else
      {
/* se non ho letto il TAPPO quello che ho letto e' una variabile */
         strcpy((filtri[filtro_corrente])->var[j],buff);
         j++;
         filtri[filtro_corrente]->num_var = j;
      }
   }
   *num_filtri = filtro_corrente+1; 
}


int inizializza_filtri(FILTRI *filtri[],int *num_filtri)
{
   short i=0,j=0;
 
   printf("inizializzazione filtri\n");
   if( (openedf()) != OK)                 /* apertura file di editing */
   {
      printf("openedf != OK\n");
      return(ERROPEN);
   }

   printf("openedf OK\n");
   for(i=0;i<MAXFILTRI;i++)          /* inizializzazione vettore filtri */
      filtri[i] = filtro_init();

   readedf(filtri,num_filtri);                        /* lettura file di editing */
}

