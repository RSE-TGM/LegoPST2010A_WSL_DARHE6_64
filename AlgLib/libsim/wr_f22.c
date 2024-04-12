/**********************************************************************
*
*       C Source:               wr_f22.c
*       Subsystem:              3
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Fri Aug 29 16:10:50 2003 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: wr_f22.c-2 %  (%full_filespec: wr_f22.c-2:csrc:3 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)wr_f22.c	5.1\t11/7/95";
/*
   modulo wr_f22.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)wr_f22.c	5.1
*/
#include <stdio.h>
#include <string.h>
#if defined VMS
# include <unixio.h>
# include <file.h>
#endif
# include "sim_param.h"            /* parametri generali LEGO       */
# include "sim_types.h"            /* tipi di uso LEGO              */
#include <Rt/RtMemory.h>

#if defined UNIX || defined SCADA_MMI
FILE *fpdat_f22 ;          
#else
int fpdat_f22;
#endif


#if defined SCADA_MMI
void f22_open(char *nome_file,char *titolo_graf,
		char *nomi_variabili,char *descrizioni,int nvar)
#else
void f22_open(char *nome_file,char *nomi_variabili,char *descrizioni,int nvar)
#endif
{
char titolo[81];
char nome_var[MAX_LUN_NOME_VAR];
char descr_var[MAX_LUN_DESCR_VAR];
char buffone[120];
char nome_modello[MAX_LUN_NOME_VAR];
int j;

// printf("apertura file %s num_var %d\n",nome_file,nvar);
#if defined UNIX || defined SCADA_MMI
   fpdat_f22 = (FILE *)fopen(nome_file,"w");
   if(fpdat_f22 == NULL)
	{
	exit(printf("Errore apertura file %s\n",nome_file));
	}
#else
   fpdat_f22=open(nome_file,O_RDWR|O_NDELAY|O_APPEND|O_CREAT,0,
                "ctx=rec","rfm=var","shr=get","shr=put");
#endif
#if defined SCADA_MMI
   strncpy(titolo,titolo_graf,80);
#else
   strncpy(titolo,"TITOLO DELLA SIMULAZIONE",80);
#endif
   titolo[80] = '\00';

#if defined UNIX || defined SCADA_MMI
   fwrite(titolo,80,1,fpdat_f22);
   fwrite(&nvar,sizeof(int),1,fpdat_f22);
#else
   write(fpdat_f22,titolo,80);
   write(fpdat_f22,&nvar,sizeof(int));
#endif

#if defined UNIX || defined SCADA_MMI
                fwrite(nomi_variabili,(MAX_LUN_NOME_VAR-1)*sizeof(char),nvar,fpdat_f22);
#else
                write(fpdat_f22,nomi_variabili,(MAX_LUN_NOME_VAR-1)*sizeof(char)*nvar);
#endif
   strncpy(nome_modello,"MOD1+2      ",MAX_LUN_NOME_VAR-1);
   nome_modello[MAX_LUN_NOME_VAR-1] = '\00';
#if defined UNIX || defined SCADA_MMI
   fwrite(nome_modello,(MAX_LUN_NOME_VAR-1)*sizeof(char),1,fpdat_f22);
   fwrite(&nvar,sizeof(int),1,fpdat_f22);
#else
   write(fpdat_f22,nome_modello,(MAX_LUN_NOME_VAR-1)*sizeof(char));
   write(fpdat_f22,&nvar,sizeof(int));
#endif
   buffone[0]=0;
   for( j = 0 ; j < nvar ; j++ )
      {
// printf("scrittura header var %d\n",j);
	  memcpy(buffone,&nomi_variabili[j*(MAX_LUN_NOME_VAR-1)],
		MAX_LUN_NOME_VAR-1);
	  buffone[MAX_LUN_NOME_VAR-1]=' ';
	  memcpy(&buffone[MAX_LUN_NOME_VAR],
		&descrizioni[j*(MAX_LUN_DESCR_VAR-1)],MAX_LUN_DESCR_VAR-1);
/*
          strcat( buffone, variabili[j-1].nome);
          strcat( buffone, "  ");
          strcat( buffone, variabili[j-1].descr);
*/
          buffone[79]=0;
#if defined UNIX || defined SCADA_MMI
          fwrite( buffone,80*sizeof(char),1,fpdat_f22);
#else
          write(fpdat_f22,buffone,80*sizeof(char));
#endif
          buffone[0]=0;
      }
}

void f22_write(tempo_f22,val,nvar)
float tempo_f22;
float *val;
int nvar;
{
float app_tempo;

app_tempo=tempo_f22;
 

#if defined UNIX || defined SCADA_MMI
   /* scrive i dati su disco */
   fwrite(&app_tempo,sizeof(float),1,fpdat_f22);
   fwrite(&val[0],sizeof(float),nvar,fpdat_f22);
#ifndef SCADA_MMI
   /* svuota l'eventuale buffer */
   fflush(fpdat_f22);
#endif
#else
   write(fpdat_f22,&app_tempo,sizeof(float));
   write(fpdat_f22,&val[0],nvar*sizeof(float));
#endif
}

void f22_close()
{
printf("Chiusura f22\n");
#if defined UNIX || defined SCADA_MMI
	fclose(fpdat_f22);
#else
	close(fpdat_f22);
#endif
}
