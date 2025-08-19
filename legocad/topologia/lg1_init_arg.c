/**********************************************************************
*
*       C Source:               lg1_init_arg.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 13:59:19 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: lg1_init_arg.c,2 %  (%full_filespec: 1,csrc,lg1_init_arg.c,2 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)lg1_init_arg.c	2.24\t3/30/95";
/*
        Fine sezione per SCCS
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "errore.h"


extern int init_modello();
extern int set_bl_list();
extern int set_model_name();
extern void errore(const char*, ...);
extern int desel_open_but(void);


extern ERR_LEVEL   err_level;
extern int         changes_in_F01;

extern char   path_legocad[];
extern char   nome_modello[];
extern int graphics_on;
extern int verifica_congruenza_file();

int lg1_init_arg(char *pathmodel)
{
   int i,j=0,lenarg,k;
   char appo[300];
/*
   char *envpath,*getenv(),appo[200];

   envpath = getenv("LEGOCAD_USER");
   if( envpath )
      strcpy(path_legocad,envpath);
   else
   {
      errore(ENV_VAR_ERR,"LEGOCAD_USER");
      return(-1);
   }

   strcat(path_legocad,"/legocad");
*/

   lenarg = strlen(pathmodel);
   printf("lg1_init_arg argument %s of len %d\n",pathmodel,lenarg);
   for(i=lenarg;i>=0;i--)
   {
      if(pathmodel[i-1] != '/')
         j++;         
      else
         break;
   } 
   printf("len of model name %d\n",j);

   k=0;
   for(i=(lenarg-j);i<lenarg;i++)
   {
      nome_modello[k]=pathmodel[i];
      k++;
   }

   printf("lg1_init_arg nome_modello %s\n",nome_modello);

   strcpy(path_legocad,pathmodel);
   path_legocad[strlen(pathmodel) -j -1] = 0;
   
   printf("lg1_init_arg path_legocad %s\n",path_legocad);

   if( chdir(pathmodel) )
   {
      errore(OPEN_F01_ERR,pathmodel);
      return(-1);
   }
   
   return 0;
}

int lg1_start_modello() 
{
/* inizializzo il modello
*/
  
init_modello(nome_modello,path_legocad);

if(err_level != NO_ERROR)
{
   printf("init_modello ritorna con errore\n");
   set_bl_list();
   set_model_name();           
   desel_open_but(); 
   return(err_level);
}

if(graphics_on)
{
   desel_open_but(); 
   verifica_congruenza_file();
}
      
if(err_level == NO_ERROR)
   {
      set_bl_list();
      set_model_name();           
      desel_open_but(); 
   }

   return err_level;
}
