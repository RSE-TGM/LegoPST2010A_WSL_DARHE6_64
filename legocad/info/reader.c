/**********************************************************************
*
*       C Source:               reader.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Nov  7 13:49:15 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: reader.c-3 %  (%full_filespec: reader.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)reader.c	1.11\t3/27/95";
/*
        Fine sezione per SCCS
*/
/*------------------------------------------------------
 *
 * nome modulo:   reader.c 
 *
 * descrizione:   Questo modulo contiene le routine
 *                per la lettura dei file 
 *
 *------------------------------------------------------*/

#include <stdio.h>
#include <sys/stat.h>
#include "linfo.h"

#if defined LINUX
#define TRUE 1
#define FALSE 0
#endif


/*-----------------------------------------------
  verifica la esistenza del file 'nome_file'
  se esiste ritorna True, altrimenti False.
*----------------------------------------------*/
int FileExist(char *nome_file)
{
   FILE *fp;

   if( (fp = fopen(nome_file,"r")) != NULL)
   {
      fclose(fp);
      return(TRUE);
   }
   else
      return(FALSE);
}


int read_riga(FILE *fp,char *riga)
{
   int retval;
   char nl;

   retval = fscanf(fp,"%[^\n]",riga); /* legge fino al newline */
   fscanf(fp,"%c",&nl);               /* legge il new_line     */
   return(retval);                    /* ritorna il numero di char letti */
}


void skip_riga(FILE *fp)
{
    char riga[100];

    read_riga(fp,riga);               /* effettua la read di una riga
                                         il cui contenuto viene perduto*/
}

int read_file(char *filename,char **texto)
{
   FILE *fp;
   struct stat info_file;
   char *stringa = NULL;
   char *ptr2 = NULL;
   
   fp = fopen (filename,"r");
   if (fp == NULL)
      fprintf (stderr,"Can't open file %s\n", filename);
   else
   {
 /* Recupera la dimensione del file */
 /* Lettura del file */
      if ( !fstat(fileno(fp),&info_file))
      {
         stringa = (char *) XtMalloc ((unsigned) info_file.st_size+1);
         printf("dimensione del file: %d\n",info_file.st_size);
      }
      else
         stringa = (char *) XtMalloc (sizeof(char) * 100000);

      printf("dopo XtMalloc.\n");
      ptr2 = stringa;
      while (fgets(ptr2,140,fp) != NULL)
         ptr2 = ptr2+strlen(ptr2);
   }
   printf("lunghezza stringa: %d\n",strlen(stringa));

   (*texto) = stringa;

   fclose(fp);

}
