/**********************************************************************
*
*       C Source:               init_new_modello.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 13:59:04 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: init_new_modello.c,2 %  (%full_filespec: 1,csrc,init_new_modello.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)init_new_modello.c	2.24\t3/30/95";
/*
        Fine sezione per SCCS
*/

#include <stdio.h>
#include "lg1.h"
#include "errore.h"




MODELLO modello;
BLOCCO  blocchi[MAX_BLOCCHI];
MODULO  moduli[MAX_MODULI];
int     num_blocchi;
int     num_moduli;


extern ERR_LEVEL err_level;
extern int libera_modello();



init_new_modello(nome_modello, path_legocad)
char *nome_modello, *path_legocad;
{

   err_level = NO_ERROR;

   libera_modello();
   num_blocchi = num_moduli = 0;

   strcpy(modello.nome, nome_modello);
   strcpy(modello.path_legocad, path_legocad);
   if ( modello.path_legocad[strlen(modello.path_legocad)-1] != '/' )
     strcat ( modello.path_legocad, "/" );

   read_moduli();


   if (err_level == ERROR)
   {
     libera_modello();
     num_blocchi = num_moduli = 0;
   }

   printf("\nTERMINATA routine INIT_NEW_MODELLO\n");
}



