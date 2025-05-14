/**********************************************************************
*
*       C Source:               rest_func.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Tue Oct 22 14:04:57 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: rest_func.c-1.1.1 %  (%full_filespec: rest_func.c-1.1.1:csrc:1 %)";
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "sim_param.h"
#include "sim_types.h"
#include "sim_ipc.h"
#include "comandi.h"
#include "sked.h"
#include "f22_circ.h"

/* Variabili globali */
   int _MAX_BACK_TRACK;
   int _MAX_CAMPIONI;
   int _NUM_VAR;
   int _SPARE_SNAP;
   int _MAX_PERTUR;
   int SIZE_AREA_DATI;

   HEADER_REGISTRAZIONI hreg_bktk;


/* Prototyping funzioni */
   int rest_backtrack(char *);
   int rest_f22circ(char *);
   int rest_move(char *);



   
int rest_backtrack(path_dir_arch)
char	*path_dir_arch;
{
FILE	*fp_bktk=NULL;
FILE	*fp_bktk_n=NULL;
BKTAB	*bk_hea;
SNAP_SKED	sommari_backtrack;
TIPO_PERT	*pert_tmp,*pert_tmp_att;
char	path_back_n[FILENAME_MAX],path_back[FILENAME_MAX];
char	*app,*area_spare;
int	i,j,tempo;
int	size_area_spare,num_back_arch;
float	*area_dati;
STATO_CR     stato_cr;

   sprintf(path_back_n,"%s/backtrackn.dat",path_dir_arch);
   sprintf(path_back,"%s/backtrack.dat",path_dir_arch);
   if((fp_bktk_n = fopen(path_back_n, "r"))==NULL) {
      perror("backtrackn.dat");
      return(-1);
   }
   if((fp_bktk = fopen(path_back, "w"))==NULL) {
      perror("backtrack.dat");
      return(-1);
   }
/*
   Lettura dell'header del file (HEADER_REGISTRAZIONI) ed estrazione
   di alcune informazioni di interesse.
*/
   fread(&hreg_bktk,sizeof(HEADER_REGISTRAZIONI),1,fp_bktk_n);
   _MAX_BACK_TRACK = hreg_bktk.simulator.max_back_track;
   _MAX_CAMPIONI = hreg_bktk.simulator.max_campioni;
   _NUM_VAR = hreg_bktk.simulator.num_var;
   _SPARE_SNAP = hreg_bktk.simulator.spare_snap;
   _MAX_PERTUR = hreg_bktk.simulator.max_pertur;
   SIZE_AREA_DATI = hreg_bktk.size_area_dati;

   size_area_spare=_SPARE_SNAP * AREA_SPARE;

/*
   Allocazione delle strutture dinamiche necessarie per la lettura
   e scrittura del file 
*/
   bk_hea=(BKTAB *)calloc(_MAX_BACK_TRACK,sizeof(BKTAB));
   area_dati=(float *)calloc(SIZE_AREA_DATI,sizeof(float));
   app=(char *)calloc(DIM_SNAP_AUS,sizeof(char));
   if(size_area_spare>0)
      area_spare = (char*)calloc(size_area_spare,sizeof(char));
   pert_tmp     = (TIPO_PERT *)calloc(_MAX_PERTUR,sizeof(TIPO_PERT));
   pert_tmp_att = (TIPO_PERT *)calloc(_MAX_PERTUR,sizeof(TIPO_PERT));

/*
   Scrittura dell'header nel file da ripristinare
*/
   fwrite(&hreg_bktk,sizeof(HEADER_REGISTRAZIONI),1,fp_bktk);
/*
   Lettura del numero di backtrack presenti nel file di archivio.
*/
   load_stato_cr_arch(&stato_cr,path_dir_arch);
   num_back_arch=stato_cr.last_bktk_save;
/*
printf("num_back_arch = %d\n",num_back_arch);
*/
/*
   Lettura degli header dei backtrack che sono stati archiviati e
   scrittura nel file da ripristinare.
*/
   for(i=0;i<num_back_arch;i++) {
      fread(&bk_hea[i],sizeof(BKTAB),1,fp_bktk_n);
   }
   for(j=i;j<_MAX_BACK_TRACK;j++) {
      bk_hea[j].stat = 0;
      bk_hea[j].prog = j+1;
      bk_hea[j].pos  = 0;
      bk_hea[j].forzato = 0;
      bk_hea[j].tempo   = 10.0+j;
      strcpy(bk_hea[j].descr," >>>>    BACKTRACK FREE    <<<<\00");
      strcpy(bk_hea[j].datasn,"00/00/00\00");
      strcpy(bk_hea[j].temposn,"0\00");
   }
   fwrite(bk_hea,sizeof(BKTAB),_MAX_BACK_TRACK,fp_bktk);
/*
   Lettura dei backtrack archiviati e scrittura nel file da
   ripristinare.
*/   
   for(i=0;i<num_back_arch;i++) {
/* 1) Area dati */
      fread(area_dati, SIZE_AREA_DATI,1, fp_bktk_n);
      fwrite(area_dati, SIZE_AREA_DATI,1, fp_bktk);
/* 2) Lettura del tempo */
      fread(&tempo,1,sizeof(float), fp_bktk_n);
      fwrite(&tempo,1,sizeof(float),fp_bktk);
/* 3) DIM_SNAP_AUS */
      fread(app, DIM_SNAP_AUS, 1, fp_bktk_n);
      fwrite(app,DIM_SNAP_AUS, 1, fp_bktk);
/* 4) Sommari */
      fread(&sommari_backtrack, sizeof(SNAP_SKED), 1, fp_bktk_n);
      fwrite(&sommari_backtrack, sizeof(SNAP_SKED), 1, fp_bktk);
/* 5) Area libera */
      if ( size_area_spare > 0 ) {
         fread(area_spare, sizeof(char), size_area_spare, fp_bktk_n);
         fwrite(area_spare, sizeof(char), size_area_spare, fp_bktk);
      }
/* 6) Area pert che comprende gli updown */
      fread(pert_tmp,     sizeof(TIPO_PERT), _MAX_PERTUR, fp_bktk_n);
      fread(pert_tmp_att, sizeof(TIPO_PERT), _MAX_PERTUR, fp_bktk_n);
      fwrite(pert_tmp,     sizeof(TIPO_PERT), _MAX_PERTUR, fp_bktk);
      fwrite(pert_tmp_att, sizeof(TIPO_PERT), _MAX_PERTUR, fp_bktk);
   }
   for(j=i;j<_MAX_BACK_TRACK;j++) {
      fwrite(area_dati, SIZE_AREA_DATI,1, fp_bktk);
      fwrite(&tempo,1,sizeof(float),fp_bktk);
      fwrite(app,DIM_SNAP_AUS, 1, fp_bktk);
      fwrite(&sommari_backtrack, sizeof(SNAP_SKED), 1, fp_bktk);
      if(size_area_spare>0)
         fwrite(area_spare, sizeof(char), size_area_spare, fp_bktk);
      fwrite(pert_tmp,     sizeof(TIPO_PERT), _MAX_PERTUR, fp_bktk);
      fwrite(pert_tmp_att, sizeof(TIPO_PERT), _MAX_PERTUR, fp_bktk);
   }
   fclose(fp_bktk_n);
   fclose(fp_bktk);

   free(bk_hea);
   free(area_dati);
   free(app);
   if ( size_area_spare > 0 )
      free(area_spare);
   free(pert_tmp);
   free(pert_tmp_att);
   
return(0);
}




int rest_f22circ(path_dir_arch)
char	*path_dir_arch;
{
PUNT_FILE_F22 fp_f22_n,fp_f22;
F22CIRC_HD head;
SIMULATOR simpar;
F22CIRC_VAR *var_tot;
F22CIRC_T t_22;
float *valori;
char	path_f22_n[FILENAME_MAX],path_f22[FILENAME_MAX];
int	i;
char	comando[FILENAME_MAX+10];
 
   sprintf(path_f22_n,"%s/f22circn",path_dir_arch);
   sprintf(path_f22,"%s/f22circ",path_dir_arch);
   if(f22_open_file(path_f22_n,&fp_f22_n)==0) {
      fprintf(stderr,"Error opening file f22circn.dat\n");
      return(-1);
   }
   if(f22_create_file_dat(path_f22,&fp_f22)==0) {
      fprintf(stderr,"Error opening file f22circ.dat\n");
      return(-1);
   }
/*
   Scrittura dell'header HEADER_REGISTRAZIONI nel file ripristinato
*/
   fwrite(&hreg_bktk,sizeof(HEADER_REGISTRAZIONI),1,fp_f22.fp);

   fseek(fp_f22_n.fp,sizeof(HEADER_REGISTRAZIONI),SEEK_SET);
   if(f22_leggo_header(&head,fp_f22_n,0,&simpar)==0) {
      fprintf(stderr,"Errore reading header file f22circn.dat\n");
      sprintf(comando,"rm %s",path_f22);
      return(-1);
   }
   fwrite(&head,sizeof(F22CIRC_HD),1,fp_f22.fp);
/*
   Lettura dei nomi e descrizioni delle variabili presenti nel file
   f22circn.dat.
*/   
/*
printf("num_var_graf_n = %d\tnum_campioni_n = %d\n",head.num_var_graf,
       head.num_campioni);
*/
   var_tot=(F22CIRC_VAR *)calloc(_NUM_VAR,sizeof(F22CIRC_VAR));
   fread(var_tot,sizeof(F22CIRC_VAR),head.num_var_graf,fp_f22_n.fp);
   for(i=head.num_var_graf;i<_NUM_VAR;i++) {
      strcpy(var_tot[i].nomevar,"libera");
   }
   fwrite(var_tot,sizeof(F22CIRC_VAR),_NUM_VAR,fp_f22.fp);
   free(var_tot);  

   valori=(float*)calloc(_NUM_VAR,sizeof(float));
   for(i=0;i<head.num_campioni;i++) {
      fread(&t_22,sizeof(F22CIRC_T),1,fp_f22_n.fp);
      fread(valori,sizeof(float),head.num_var_graf,fp_f22_n.fp);
      fwrite(&t_22,sizeof(F22CIRC_T),1,fp_f22.fp);
      fwrite(valori,sizeof(float),_NUM_VAR,fp_f22.fp);
   }
   memset(valori,0,sizeof(float)*_NUM_VAR);
   memset(&t_22,0,sizeof(F22CIRC_T)); 
   for(i=head.num_campioni;i<_MAX_CAMPIONI;i++) {
      fwrite(&t_22,sizeof(F22CIRC_T),1,fp_f22.fp);
      fwrite(valori,sizeof(float),_NUM_VAR,fp_f22.fp);
      fflush(fp_f22.fp);
   }
/*
   Aggiornamento dell'header.
*/
   head.num_campioni=_MAX_CAMPIONI;
   head.num_var_graf=_NUM_VAR;
   fseek(fp_f22.fp,sizeof(HEADER_REGISTRAZIONI),SEEK_SET);
   fwrite(&head,sizeof(F22CIRC_HD),1,fp_f22.fp);
   fflush(fp_f22.fp);

   f22_close_file(fp_f22_n);
   f22_close_file(fp_f22);

   free(valori);
       


}




int rest_move(dir_arch)
char	*dir_arch;
{
char	comando[300];

   sprintf(comando,"mv -i ./%s/backtrack.dat .",dir_arch);

printf("comando = %s\n", comando);

   system(comando);
   sprintf(comando,"mv -i ./%s/f22circ.dat .",dir_arch);
   system(comando);
   sprintf(comando,"mv -i ./%s/perturbazioni.dat .",dir_arch);
   system(comando);
   sprintf(comando,"mv -i ./%s/stato_cr.rtf .",dir_arch);
   system(comando);
   sprintf(comando,"mv -i ./%s/recorder.edf .",dir_arch);
   system(comando);

}
