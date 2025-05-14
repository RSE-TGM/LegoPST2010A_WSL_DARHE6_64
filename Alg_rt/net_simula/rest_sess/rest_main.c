/**********************************************************************
*
*       C Source:               rest_main.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Tue Apr  7 11:38:14 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: rest_main.c-2 %  (%full_filespec: rest_main.c-2:csrc:1 %)";
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "sim_param.h"
#include "sim_types.h"
#include "sim_ipc.h"
#include "comandi.h"
#include "sked.h"


#define	MAX_NAME_DIR	200
#define LENGTH_DEL	2
#define LENGTH_COD	20
#define NUM_TOKEN	6
#define TOKEN		"_"


/* Prototyping funzioni */
   int checkDirSession(char *);
   int splitNameDir(char *,char *,char *,char *);

   extern int rest_backtrack(char *);
   extern int rest_f22circ(char *);
   extern int rest_move(char *);



int main(argc,argv)
int argc;
char *argv[];
{
char	*dir_archive,*path_archive;
char	comando[FILENAME_MAX+10],selection[10];
int	trasfer;
struct stat buf;

printf("****************************************************\n\n");
printf("Process:	restsess\n\n");
printf("****************************************************\n");

   if(argc!=2) {
      fprintf(stderr,
      "Error!!! Number of parameters on command line\n\t");
      fprintf(stderr,
      "<restsess> <archiving_directory>\n");
      exit(1);
   }
   else {
      if((dir_archive=(char *)calloc(strlen(argv[1]),sizeof(char)))==NULL)
         exit(fprintf(stderr,"calloc error: dir_archive"));
      strcpy(dir_archive,argv[1]);

printf("Archiving directory selected:\n\t%s\n\n", dir_archive);

      path_archive=(char *)getcwd((char *) NULL, FILENAME_MAX+1);
      strcat(path_archive,"/");
      strcat(path_archive,dir_archive);

printf("Archiving path:\n\t%s\n", path_archive);
printf("****************************************************\n\n");

/*
   Si controlla se esiste la directory di archiviazione selezionata
*/
      if(stat(path_archive,&buf)==-1) {
         perror("restsess archiving directory");
         exit(1);
      } 
/*
   Controllo della struttura del nome della directory. Si controlla se
   i files da ripristinare appartengono al simulatore corrente
*/

printf("***********************************************************\n");
printf("Check if the archived session files has been generated from\n");
printf("the current simulator\n"); 
printf("***********************************************************\n");

      if(checkDirSession(dir_archive)==-1) {
         fprintf(stderr,"Error on selected directory name!!!\n");
         exit(1);
      } 

printf("\nCheck ------> OK\n\n");
/*
   Ripristino dei files 
*/
printf("***********************************************************\n");
printf("Restore files perturbazioni.dat, stato_cr.rtf, recorder.edf\n");
printf("in the current archiving directory\n");
printf("***********************************************************\n");
     sprintf(comando,"cp ./%s/stato_crn.rtf ./%s/stato_cr.rtf",dir_archive,
     dir_archive);
     system(comando);
     sprintf(comando,"cp ./%s/perturbazionin.dat ./%s/perturbazioni.dat",
     dir_archive,dir_archive);
     system(comando);
     sprintf(comando,"cp ./%s/recordern.edf ./%s/recorder.edf",dir_archive,
     dir_archive);
     system(comando);

printf("\nFile perturbazioni.dat -----> RESTORED\n\n");
printf("File stato_cr.rtf      -----> RESTORED\n\n");
printf("File recorder.edf      -----> RESTORED\n\n");
printf("***********************************************************\n");
printf("Restoring file backtrack.dat. This file is generated\n");
printf("in the current archiving directory\n");
printf("***********************************************************\n");
     if(rest_backtrack(path_archive)==-1) { 
        fprintf(stderr,
        "Error!!! File backtrack.dat not restored. EXIT\n");
        exit(0);
     }
printf("\nFile backtrack.dat -----> RESTORED\n\n");
printf("***********************************************************\n");
printf("Restoring file f22circ.dat. This file is generated\n");
printf("in the current archiving directory\n");
printf("***********************************************************\n");
     if(rest_f22circ(path_archive)==-1) {
        fprintf(stderr,
        "Error!!! File f22circ.dat not restored. EXIT\n");
/*
   Si rimuove il file backtrack.dat gia' prodotto
*/
        sprintf(comando,"rm %s/backtrack.dat",path_archive);
        system(comando);
        exit(0);
     }

printf("\nFile f22circ.dat -----> RESTORED\n\n");
printf("***********************************************************\n");
        
/*
   Ripristino andato a buon fine.
*/
     
     printf("\nDo you want to move the restored files in the simulation directory?(y/n): ");
     // GUAG2025
     // gets(selection);
     // Usa fgets invece:
     if (fgets(selection, sizeof(selection), stdin) != NULL) {
         // fgets può includere il carattere di newline ('\n') se c'è spazio.
         // Dobbiamo rimuoverlo se presente, altrimenti strcmp("y") fallirà.
         char *newline = strchr(selection, '\n');
         if (newline != NULL) {
             *newline = '\0'; // Sostituisci il newline con il terminatore di stringa
         }
     } else {
         // Errore nella lettura o EOF, gestisci come preferisci
         // Ad esempio, assumi 'n' o esci
         fprintf(stderr, "Errore nella lettura dell'input o EOF.\n");
         strcpy(selection, "n"); // Assumi 'no' come default in caso di errore
     }
    
     if(strcmp(selection,"y")==0) {
        rest_move(dir_archive);
printf("\n***********************************************************\n");
printf("Restoring session and moving -------> COMPLETED\n");
printf("***********************************************************\n");
     }
     else {
printf("\n***********************************************************\n");
printf("Restoring session in the archiving directory -------> COMPLETED\n");
printf("***********************************************************\n");
     } 
   }

   free(path_archive);
   free(dir_archive);


}




int checkDirSession(name_dir)
char	*name_dir;
{
FILE	*fp_app;
char	var_cod[LENGTH_COD],s02_cod[LENGTH_COD],sim_cod[LENGTH_COD];
char	var_cod_ck[LENGTH_COD],s02_cod_ck[LENGTH_COD],sim_cod_ck[LENGTH_COD];
char	path_tmp[FILENAME_MAX],pid_curr[10];
char	comando[FILENAME_MAX+20],name_dir_check[MAX_NAME_DIR];

/*
   Si recuperano i codici dei files che identificano il simulatore dal
   nome della directory di archivio
*/
   if((splitNameDir(name_dir,var_cod,s02_cod,sim_cod))==-1)
      return(-1);
/*
printf("var_cod = %s\ts02_cod = %s\tsim_cod = %s\n", var_cod,s02_cod,sim_cod);
*/
/*
   Calcolo i codici dei files correnti nel simulatore
*/
   strcpy(path_tmp,getenv("HOME"));
   strcat(path_tmp,"/tmp");
   strcat(path_tmp,"/app_arch_");
   sprintf(pid_curr,"%d",getpid());
   strcat(path_tmp,pid_curr);

   strcpy(comando,"archive > ");
   strcat(comando,path_tmp);
/*
printf("recupero codici check:\n\tcomando = %s\n",comando);
*/
   if((system(comando))==-1) {
      perror("esecuzione della shell: archive");
      return(-1);
   }
   if((fp_app=fopen(path_tmp,"r")) == NULL) {
      perror("apertura del file: app_archive");
      return(-1);
   }
   fgets(name_dir_check,MAX_NAME_DIR,fp_app);
   name_dir_check[strlen(name_dir_check)-1]='\0';  /* toglie il new line */
   fclose(fp_app);
   strcpy(comando,"rm ");
   strcat(comando,path_tmp);
/*
printf("Directory di archiviazione selezionata:\n\t%s\n", name_dir_check);
printf("rimozione file d'appoggio:\n\tcomando = %s\n",comando);
*/
   system(comando);

   if(splitNameDir(name_dir_check,var_cod_ck,s02_cod_ck,sim_cod_ck)==-1)
      return(-1);
/*
printf("var_cod_ck = %s\ts02_cod_ck = %s\tsim_cod_ck = %s\n",
       var_cod_ck,s02_cod_ck,sim_cod_ck);
*/
   if((strcmp(var_cod,var_cod_ck)==0)&&(strcmp(s02_cod,s02_cod_ck)==0)&&
      (strcmp(sim_cod,sim_cod_ck)==0)) 
      return(0);
   else
      return(-1);
}




int splitNameDir(name_dir_tot,var_cod_app,s02_cod_app,sim_cod_app)
char	*name_dir_tot;
char	*s02_cod_app;
char	*var_cod_app;
char	*sim_cod_app;
{
char	delimiters[LENGTH_DEL],string1[MAX_NAME_DIR];
char	*pstr;
int	counter=0;

   strcpy(string1,name_dir_tot);
   strcpy(delimiters,TOKEN);
   if ((pstr = strtok(string1, delimiters ))!= NULL) {
/*
      printf("Token 1 is %s\n", pstr);
*/
      counter=2;
      while ((pstr = strtok((char *)NULL, delimiters ))!= NULL) {
/*
         printf("Token %d is %s\n", counter, pstr);
*/
         if(counter==(NUM_TOKEN-2))
            strcpy(var_cod_app,pstr); 
         if(counter==(NUM_TOKEN-1))
            strcpy(s02_cod_app,pstr); 
         if(counter==(NUM_TOKEN))
            strcpy(sim_cod_app,pstr);
         counter++;
      }
   }
   if(counter!=(NUM_TOKEN+1)) {
      fprintf(stderr,
         "Error!!! Archiving directory name structure :\n\t%s\n",name_dir_tot);
      return(-1);
   }
return(0);
}

