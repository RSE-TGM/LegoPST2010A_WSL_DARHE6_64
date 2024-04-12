/**********************************************************************
*
*       C Source:               init_modello.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 13:58:59 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: init_modello.c,2 %  (%full_filespec: 1,csrc,init_modello.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)init_modello.c	2.24\t3/30/95";
/*
        Fine sezione per SCCS
*/


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "lg1.h"
#include "errore.h"




MODELLO modello;
BLOCCO  blocchi[MAX_BLOCCHI];
MODULO  moduli[MAX_MODULI];
int     num_blocchi;
int     num_tot_moduli;


extern ERR_LEVEL err_level;


init_modello(nome_modello, path_legocad)
char *nome_modello, *path_legocad;
{
   char appmod[400];
   mode_t modo = (S_IRWXG | S_IRWXO | S_IRUSR | S_IWUSR | S_IXUSR);

   err_level = NO_ERROR;

   libera_modello();
   num_blocchi = num_tot_moduli = 0;

   strcpy(modello.nome, nome_modello);
   strcpy(modello.path_legocad, path_legocad);
   if ( modello.path_legocad[strlen(modello.path_legocad)-1] != '/' )
     strcat ( modello.path_legocad, "/" );

   read_moduli();

   if (err_level == ERROR)
   {
      printf("Errore in read moduli\n");
      return(-1);
   }

   strcpy(appmod,path_legocad);
   strcat(appmod,"/");
   strcat(appmod,nome_modello);

   if(chdir(appmod) == -1)
   {
     printf("Cannot open model/n CREATE NEW ONE\n");
     if(mkdir(appmod,modo) == -1)
     {
        printf("SORRY CANNOT CREATE NEW MODEL\n");
        err_level = ERROR;
        errore("Can't open the model"); 
        return;
     }
   }

   read_f01();

   if (err_level == ERROR)
   {
     printf("ERROR returned from read_f01\n");
     errore("ERROR returned when read F01.dat\n");
     libera_modello();
     num_blocchi = num_tot_moduli = 0;
   }
}





libera_modello()
{
  int i;

  for ( i=0; i<num_blocchi; i++ )
    libera_blocco( i );
}

