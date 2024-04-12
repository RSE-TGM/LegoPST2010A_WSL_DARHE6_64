/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)mandb_io.c	5.1\t11/7/95";
/*
   modulo mandb_io.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)mandb_io.c	5.1
*/
/*
	routine di accesso al file delle pagine di mandb
*/

#include <stdio.h>                              /* For printf and so on. */
#include <string.h>                              /* For printf and so on. */

#include <X11/Xlib.h>
#include <Mrm/MrmAppl.h>
#include <Xm/Text.h>
#include <Xm/DrawingA.h>


#include "sim_param.h"
#include "sim_types.h"
#include "mandb.h"

FILE *fpPag;

extern DBASE_MANDB *p_db;
extern PAGE_VIS pagina[MAX_PAGINE];
extern char descr_page[MAX_PAGINE][MAX_LUN_DESCRPAGE];
extern float   valori_sp[MAX_TOTVAR];
extern float   tempi_sp[MAX_TOTVAR];

extern VARIABILI *variabili;
extern int tot_variabili;

long offset_descr,offset_indvar,offset_sigle,offset_valori,offset_tempi;


read_all_page_mandb()
{
int i,j, k, *p_indvar, flag, new_ind;
char stringa[60];
char *psigle, *pnomivar;


psigle=XtMalloc (MAX_TOTVAR *  MAX_LUN_NOME_VAR);
memset(psigle,0,MAX_TOTVAR * MAX_LUN_NOME_VAR);
if (psigle == NULL) exit(1);
        fpPag=fopen("page_mandb.dat","r+");
        if(fpPag==NULL)
        {
        /* se non esiste lo crea vuoto */

          fpPag=fopen("page_mandb.dat","w");
	  memset(descr_page,0, MAX_PAGINE*MAX_LUN_DESCRPAGE);
          for (i=0; i< MAX_TOTVAR; i++)
	  {
		 valori_sp[i]=0.;
		 tempi_sp[i]= -1.;
		 p_db->indice_var[i]= -1;
	  }
          fwrite( descr_page, MAX_PAGINE*MAX_LUN_DESCRPAGE,1,fpPag);
	  fwrite( p_db->indice_var,MAX_TOTVAR * sizeof(int),1,fpPag);
          fwrite( psigle,MAX_TOTVAR * MAX_LUN_NOME_VAR,1,fpPag);
          fwrite( (char *) valori_sp, sizeof(valori_sp),1,fpPag);
          fwrite( (char *) tempi_sp, sizeof(tempi_sp),1,fpPag);
        }
        else
        {
          fread( descr_page, MAX_PAGINE*MAX_LUN_DESCRPAGE,1,fpPag);
	  fread( p_db->indice_var,MAX_TOTVAR * sizeof(int),1,fpPag);
          fread( psigle,MAX_TOTVAR * MAX_LUN_NOME_VAR,1,fpPag);
          fread( (char *) valori_sp, sizeof(valori_sp),1,fpPag);
          fread( (char *) tempi_sp, sizeof(tempi_sp),1,fpPag);

/****
pnomivar=psigle;
for (k=0; k< MAX_PAGINE; k++) printf("pag %d %s\n",k,descr_page[k]);
for (k=0; k<MAX_TOTVAR; k++, pnomivar+=MAX_LUN_NOME_VAR)
 if (p_db->indice_var[k] != -1)
	 	printf(" %d  %d  %s  %ld %f  %f \n",k,p_db->indice_var[k],pnomivar,pnomivar,
					valori_sp[k],tempi_sp[k]);
***/
/*
	verifica se le variabili memorizzate sul  file esistono ancora
	e aggiorna la tabella p_db->indice_var
*/
	pnomivar=psigle;
	for (i=0; i< MAX_TOTVAR; i++, pnomivar+=MAX_LUN_NOME_VAR)
	{
          if (p_db->indice_var[i]== -1) continue;

/* se p_db->indice_var[i] > tot_variabili non puo' accedere all'area
   variabili perche' da segmantation fault 
*/
          if (p_db->indice_var[i] >= tot_variabili )
	  { 
   		new_ind=cerca_var(pnomivar);
		p_db->indice_var[i]=new_ind;
		if (new_ind == -1)
		{
			valori_sp[i]=0.;
			tempi_sp[i]= -1.;
			memset(pnomivar,0,MAX_LUN_NOME_VAR);
		}
	  }
	  else
	  {
       		if (strcmp(pnomivar,variabili[p_db->indice_var[i]].nome) != 0)
		{
                         new_ind=cerca_var(pnomivar);
                         p_db->indice_var[i]=new_ind;
			if (new_ind == -1)
			{
				valori_sp[i]=0;
				tempi_sp[i]= -1.;
				memset(pnomivar,0,MAX_LUN_NOME_VAR);
			}
		}
	  }
	}
	
/* annulla le pagine in cui non ci sono piu' variabili */

	for (i=0; i<MAX_PAGINE; i++)
	{
  	  if (!strlen(descr_page[i])) continue;
	  p_indvar= &p_db->indice_var[i*MAX_VAR];
	  flag=0;
	  for (j=0; j<MAX_VAR; j++) if (p_indvar[j] != -1)flag=1;
	  if (!flag) memset(descr_page[i],0, MAX_LUN_DESCRPAGE);
	}
	
/* riscrive il file per le eventuali modifiche eseguite */
/**********
printf("\n riscrive il file \n");
pnomivar=psigle;
for (k=0; k< MAX_PAGINE; k++) printf("pag %d %s\n",k,descr_page[k]);
for (k=0; k<MAX_TOTVAR; k++, pnomivar+=MAX_LUN_NOME_VAR)
	printf(" %d  %d  %s  %f  %f \n",k,p_db->indice_var[k],pnomivar,
					valori_sp[k],tempi_sp[k]);
**********/
	fseek(fpPag,0L,0);
	fwrite( descr_page, MAX_PAGINE*MAX_LUN_DESCRPAGE,1,fpPag);
	fwrite( p_db->indice_var,MAX_TOTVAR * sizeof(int),1,fpPag);
	fwrite( psigle,MAX_TOTVAR * MAX_LUN_NOME_VAR,1,fpPag);
	fwrite( (char *) valori_sp, sizeof(valori_sp),1,fpPag);
	fwrite( (char *) tempi_sp, sizeof(tempi_sp),1,fpPag);
	}


fclose (fpPag);
XtFree(psigle);

offset_descr=0L;
offset_indvar = offset_descr  + (MAX_PAGINE*MAX_LUN_DESCRPAGE);
offset_sigle = offset_indvar  + (MAX_TOTVAR * sizeof (int));
offset_valori = offset_sigle  + (MAX_TOTVAR * MAX_LUN_NOME_VAR);
offset_tempi  = offset_valori  + (MAX_TOTVAR * sizeof (float));
return(0);
}

/*
	cerca il nome della variabile  nell' area shared
*/
int cerca_var(nomevar)
char *nomevar;
{
int j,ind;

for (j=0; j< tot_variabili; j++)
	if (strcmp(nomevar,variabili[j].nome) == 0) return(j);
return(-1);
}

write_page_mandb(indice_rec,flag)
int indice_rec;		/* indice pagina da salvare */
int flag;	        /* se 1 salva tutta la pagina, se 0 salva
			   solo i valori */
			
{
int i;
long offset;

fpPag=fopen("page_mandb.dat","r+");

printf(" write page %d \n",indice_rec);
if (flag )
{
offset=offset_descr +(indice_rec*MAX_LUN_DESCRPAGE);
fseek(fpPag,offset,0);
fwrite(&descr_page[indice_rec][0],MAX_LUN_DESCRPAGE,1,fpPag);

offset= offset_sigle + (indice_rec*MAX_VAR*MAX_LUN_NOME_VAR);
fseek(fpPag,offset,0);
fwrite(pagina[indice_rec].sigle_vis,MAX_VAR*MAX_LUN_NOME_VAR,1,fpPag);

offset = offset_indvar+(indice_rec*MAX_VAR*sizeof(int));
fseek(fpPag,offset,0);
fwrite(&p_db->indice_var[indice_rec*MAX_VAR],MAX_VAR * sizeof(int),1,fpPag);
for (i=0;i<MAX_VAR;i++)
	printf("%d indice_var %d sigla_vis %s \n",i,p_db->indice_var[(indice_rec*MAX_VAR)+i],pagina[indice_rec].sigle_vis[i]);
}

offset = offset_valori+(indice_rec*MAX_VAR*sizeof(float));
fseek(fpPag,offset,0);
fwrite(&valori_sp[indice_rec*MAX_VAR],MAX_VAR * sizeof(float),1,fpPag);

offset = offset_tempi+(indice_rec*MAX_VAR*sizeof(float));
fseek(fpPag,offset,0);
fwrite(&tempi_sp[indice_rec*MAX_VAR],MAX_VAR * sizeof(float),1,fpPag);
fclose (fpPag);
return(0);
}


read_page_mandb(indice_rec)
int indice_rec;         /* indice pagina da salvare */

{
int i;
long offset;

fpPag=fopen("page_mandb.dat","r+");

offset=offset_descr +(indice_rec*MAX_LUN_DESCRPAGE);
fseek(fpPag,offset,0);
fread(&descr_page[indice_rec][0],MAX_LUN_DESCRPAGE,1,fpPag);

offset= offset_sigle + (indice_rec*MAX_VAR*MAX_LUN_NOME_VAR);
fseek(fpPag,offset,0);
fread(pagina[indice_rec].sigle_vis,MAX_VAR*MAX_LUN_NOME_VAR,1,fpPag);

offset = offset_indvar+(indice_rec*MAX_VAR*sizeof(int));
fseek(fpPag,offset,0);
fread(&p_db->indice_var[indice_rec*MAX_VAR],MAX_VAR * sizeof(int),1,fpPag);

offset = offset_valori+(indice_rec*MAX_VAR*sizeof(float));
fseek(fpPag,offset,0);
fread(&valori_sp[indice_rec*MAX_VAR],MAX_VAR * sizeof(float),1,fpPag);

offset = offset_tempi+(indice_rec*MAX_VAR*sizeof(float));
fseek(fpPag,offset,0);
fread(&tempi_sp[indice_rec*MAX_VAR],MAX_VAR * sizeof(float),1,fpPag);
fclose (fpPag);

printf(" legge page %d \n",indice_rec);
for (i=0;i<MAX_VAR;i++)
	printf("%d indice_var %d sigla_vis %s \n",i,p_db->indice_var[(indice_rec*MAX_VAR)+i],pagina[indice_rec].sigle_vis[i]);
return(0);
}


/*
	routine di reset dei valori di forzamento per tutte le pagine
*/
reset_valori_sp()
{
int i;
        
fpPag=fopen("page_mandb.dat","r+");
          
for (i=0; i< MAX_TOTVAR; i++)
          {
                 valori_sp[i]=0.;
                 tempi_sp[i]= -1.;
          }
fseek(fpPag,offset_valori,0);
fwrite( (char *) valori_sp, sizeof(valori_sp),1,fpPag);
fseek(fpPag,offset_tempi,0);
fwrite( (char *) tempi_sp, sizeof(tempi_sp),1,fpPag);
fclose (fpPag);
}

