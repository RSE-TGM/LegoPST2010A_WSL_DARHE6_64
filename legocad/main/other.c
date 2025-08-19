/**********************************************************************
*
*       C Source:               other.c
*       Subsystem:              3
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Thu Nov  7 14:53:55 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: other.c-3 %  (%full_filespec: other.c-3:csrc:3 %)";
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <X11/Intrinsic.h>

#include "legomain.h"

#if defined LINUX
#define TRUE 1
#define FALSE 0
#endif

char *varenv;

void set_var_env(char *var,char *value)
{
   varenv = malloc(sizeof(char)*(strlen(var) + strlen(value)));
   strcpy(varenv,"");
   sprintf(varenv,"%s=%s",var,value);
   putenv(varenv);
}

int save_descr(char *path,char *descr)
{
   FILE *fp;
   char pathfile[200];

printf("save_descr path=%s descr=%s\n",path,descr);
   sprintf(pathfile,"%s/%s",path,FILEDESCR);
   if( (fp = fopen(pathfile,"w")) != NULL)
   {
      fprintf(fp,"%s\n",descr); 
      printf("salvo la descrizione sul file descr.dat\n");
      fclose(fp);
      return(TRUE);
   }
   fclose(fp);
   return(FALSE);
}
 
int read_descr(char *path,char **out_text)
{
   FILE *fp;
   struct stat info_file;
   char *stringa = NULL;
   char *ptr2 = NULL;
   char pathfile[200];

   sprintf(pathfile,"%s/%s",path,FILEDESCR);

   if( (fp = fopen (pathfile,"r")) ==  NULL)
   {
       fclose(fp);
       return(FALSE);
   }   
   else
   {
 /* Recupera la dimensione del file */
 /* Lettura del file */
      if ( !fstat(fileno(fp),&info_file))
         stringa = (char *) XtMalloc ((unsigned) info_file.st_size+1);
      else
         stringa = (char *) XtMalloc (sizeof(char) * 100000);

      ptr2 = stringa;
      while (fgets(ptr2,140,fp) != NULL)
         ptr2 = ptr2+strlen(ptr2);
   }
   (*out_text) = stringa;
   fclose(fp);
   return(TRUE);
}


