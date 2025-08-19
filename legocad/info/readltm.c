/**********************************************************************
*
*       C Source:               readltm.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Nov  7 13:53:26 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: readltm.c-3 %  (%full_filespec: readltm.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)readltm.c	1.11\t3/27/95";
/*
        Fine sezione per SCCS
*/
/*------------------------------------------------------
 *
 * nome modulo:   AUX.c
 *
 * descrizione:   Questo modulo contiene le routine
 *                ausiliarie della applicazione LINFO
 *
 *------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linfo.h"

#if defined LINUX
#define TRUE 1
#define FALSE 0
#endif

/* Forward declarations */
extern void skip_riga(FILE *fp);
extern int read_riga(FILE *fp, char *riga);
extern int FileExist(char *filename);


/*--------------------------------------------------------
  restituisce il numro di moduli presenti in crealtm.dat 
*---------------------------------------------------------*/
int ContaModuli(FILE *fp)
{
   int nmoduli;
   char riga [120];

   rewind(fp);     /* riposiziono il file pointer all'inizio del file */
   skip_riga(fp);  /* skip prima riga */

   nmoduli=0;      /* ogni record conta un modulo */
   while( read_riga(fp,riga) != EOF)
      nmoduli++;

   return(nmoduli);
}

int AllocaLtm(LTM **ltm,int nrecord)
{
    if(nrecord > 0 )
       (*ltm) = (LTM *)calloc(nrecord,sizeof(LTM));
       if(*ltm == NULL)
          return(FALSE);
    return(TRUE);
}

int LeggiLtm(LTM *ltm,FILE *fp)
{
   int ind;
   char riga[100],*appo;
     
   rewind(fp);     /* riposiziono il file pointer all'inizio del file */
   skip_riga(fp);  /* skip prima riga */

   ind =0;
   while( read_riga(fp,riga) != EOF)
   {
      strncpy(ltm[ind].nome_modulo,riga,4);
      appo = &riga[4];
      if( *appo == '*' )
         ltm[ind].rout_std = TRUE;
      else
         ltm[ind].rout_std = FALSE;

      appo++;
      strcpy(ltm[ind].descr_modulo,appo);
      ind++;
   }   
}

int ReadCrealtm(char *path,LTM **ltm,int *nmoduli)
{
   char fname[256];
   FILE *fpltm;     /* fp a crealtm.dat */
   int i;           /* nmoduli e' numero moduli in modello (crealtm.dat) */
   
   strcpy(fname,path);
   strcat(fname,"/proc/");
   strcat(fname,FNAME_CREALTM);   

   printf("apro il file ltm %s\n",fname);
   if( FileExist(fname) )
   {
      fpltm = fopen(fname,"r");
      *nmoduli = ContaModuli(fpltm);
   }
   else
      return(FALSE);

   printf("\n\tIl file crealtm contiene %d moduli\n\n",*nmoduli);
 
   if( AllocaLtm(ltm,*nmoduli) == FALSE)
      printf("\n\n\tallocazione lista moduli fallita \n");
   
   LeggiLtm(*ltm,fpltm);


   for(i=0;i< *nmoduli;i++)
      printf("modulo %s , descr %s , stdrout? %d\n",(*ltm)[i].nome_modulo,(*ltm)[i].descr_modulo,(*ltm)[i].rout_std);

   return(TRUE);
}


/*------------------------ end of file ---------------------------*/
