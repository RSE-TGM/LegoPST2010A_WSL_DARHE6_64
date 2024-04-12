/**********************************************************************
*
*       C Source:               verifica_file.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 13:59:37 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: verifica_file.c,2 %  (%full_filespec: 1,csrc,verifica_file.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)verifica_file.c	2.24\t3/30/95";
/*
        Fine sezione per SCCS
*/

#include <stdio.h>
#include <Xm/Xm.h>
#include <UxXt.h>
#include "lg1.h"
#include "errore.h"
#include "macro.h"


extern int num_macro;
extern MacroBlockType *macroblocks;
extern int err_level;
extern swidget create_IconvertDialog();

verifica_congruenza_file()
{
   int i,j,k,tot_block=0,found=False;
   char nome_riferim[10];


   for(i=0;i<num_macro;i++)
     for(j=0;j<macroblocks[i].num_blocchi;j++)
        if(macroblocks[i].blocks[j].tipo == TP_BLOCK)
           tot_block++;

   printf("num_blocchi %d num_macro %d tot_block %d\n",num_blocchi,num_macro,tot_block);

   if(tot_block != num_blocchi)
   {
/***
      err_level = FATAL_ERROR;
      errore("ERROR, differences between icon and list, \nI have see %d icon and %d block\nand they must be equal number\nYou must run ICONVERT ",tot_block,num_blocchi);
****/
      UxPopupInterface(create_IconvertDialog(),no_grab);
      return(-1);
   }
   for(i=0;i<num_blocchi;i++)
   {
      strcpy(nome_riferim,blocchi[i].sigla_modulo);
      strcat(nome_riferim,blocchi[i].sigla_blocco);

      for(j=0;j<num_macro;j++)
      {
         for(k=0;k<macroblocks[j].num_blocchi;k++)
         {
             if(!strcmp(nome_riferim,macroblocks[j].blocks[k].nome_blocco) )
             {
                found = True;
                break;
             }
         }
         if(found)
            break;
      }
      if(!found)
         err_level = FATAL_ERROR;
   }

  if(err_level == FATAL_ERROR)
  {
/***
      errore("ERROR, differences between icon and list, \nI have see %d icon and %d block\nand they must be equal number\nYou must run ICONVERT ",tot_block,num_blocchi);
***/
      UxPopupInterface(create_IconvertDialog(),no_grab);
      return(-1);
  }

  return(0);
}
