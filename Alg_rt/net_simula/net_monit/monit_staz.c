/**********************************************************************
*
*       C Source:               monit_staz.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Fri Nov 21 11:55:39 1997 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: monit_staz.c-3 %  (%full_filespec: monit_staz.c-3:csrc:1 %)";
#endif
/*
	Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)monit_staz.c	5.1\t11/7/95";
/*
   modulo monit_staz.c
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)monit_staz.c	5.1
*/
# include <stdio.h>
# include <math.h>
# include <string.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
#endif
#if defined VMS
# include <stdlib.h>
# include "vmsipc.h"
#endif
# include "sim_param.h"
# include "sim_types.h"       /* tipi di varibili LEGO               */
# include "sim_ipc.h"
# include <X11/Xlib.h>
# include <Mrm/MrmAppl.h>
# include <Xm/List.h>
# include <Xm/Text.h>
# include <Xm/Xm.h>
# include "monituil.h"
# include "libutilx.h"
# include "xstaz.h"
# include <Rt/RtMemory.h>

#define MIN_NUM_STAZ 1
/* ***************** definizione variabili globali ***************** */



extern Widget widget_array[MAX_WIDGETS];
extern Widget main_window_widget;


/* ****************  procedure inserite  ************************ */

void elenca_staz(); /* visualizza nella lista le pagine di stazioni disponibili
				*/
void seleziona_staz(); /* funzione di callback per la selezione di uno 
			 pagina dalla lista                        */
void activate_staz(); /* funzione di callback per tutti i bottoni delle 
			dialog box relative alle stazioni  */

/* elenco variabili per la lista delle pagine di stazioni */


char **lista_pag;
int tot_pagine = -1;
int pag_selez;

int stato_staz=0;       /* 1 processo staz gia' attivato */
int pid_staz= -1;
                                                
extern int id_msg_staz;         /* coda di messaggi con staz */
RICHIESTA_STAZ richiesta_staz;  /* struttura per richiesta staz */
                                        
void elenca_staz(lista)
Widget lista;
{
int k,totale;
char *str;
XmString c_str;
int posizione =0;
if (read_r02() == -1) return;
get_something(lista,XmNitemCount, (void*) &totale);
if(totale)
for(k=0;k<=totale;k++,XmListDeletePos(lista,1));

for (k=0;k<tot_pagine;k++)
{
   ++posizione;
   c_str=XmStringCreate(lista_pag[k],XmSTRING_DEFAULT_CHARSET);
   XmListAddItemUnselected(lista,c_str,0);
   set_something(lista,XmNitemCount, (void*) posizione);
}
}

void seleziona_staz(w, tag, reason)
    Widget w;
    int *tag;
    XmListCallbackStruct *reason;
{
        pag_selez=reason->item_position -1;
}


void activate_staz(w, tag, reason)
    Widget w;
    int *tag;
    unsigned long *reason;
{
int widget_num = *tag;
int i;
char *proc_argv[4];
char *proc_envp[20];
char proc_name[FILENAME_MAX];
char *getenv();
char *path;
char app[80];

switch (widget_num){
    case k_staz_ok:
	{

	/* verifica la necessita' di lanciare il processo staz */
	
	 stato_staz=stato_processo(pid_staz);
       	 if(stato_staz<=0)
         {
         /* lancia il processo staz */
         path=getenv("LEGORT_BIN");

         printf("Attivazione sked\n");
         proc_argv[0]=(char*)malloc(FILENAME_MAX+1);
         proc_argv[1]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[0]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[1]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[2]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[3]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[4]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[5]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[6]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[7]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[8]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[9]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[10]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[11]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[12]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[13]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[14]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[15]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[16]=(char*)malloc(FILENAME_MAX+1);
         proc_envp[17]=(char*)malloc(FILENAME_MAX+1);
         printf("Dopo malloc\n");
                                                           
#if defined UNIX
         sprintf(proc_name,"%s/xstaz\00",path);
#endif
#if defined VMS
         sprintf(proc_name,"%sxstaz\00",path);
#endif
         sprintf(proc_argv[0],"xstaz\00");
         sprintf(proc_argv[1],"%d\00",1);
         proc_argv[2]=NULL;
         printf("Dopo argv\n");
#if defined UNIX
         sprintf(proc_envp[0],"DISPLAY=%s\00",getenv("DISPLAY"));
         sprintf(proc_envp[1],"SHR_USR_KEY=%s\00",getenv("SHR_USR_KEY"));
         sprintf(proc_envp[2],"SHR_TAV_KEY=%s\00",getenv("SHR_TAV_KEY"));
         sprintf(proc_envp[3],"LEGORT_BIN=%s\00",getenv("LEGORT_BIN"));
         sprintf(proc_envp[4],"HOME=%s\00",getenv("HOME"));
         sprintf(proc_envp[5],"DEBUG=%s\00",getenv("DEBUG"));
 	 sprintf(proc_envp[6], "N000=%s\00", getenv("N000"));
 	 sprintf(proc_envp[7], "N001=%s\00", getenv("N001"));
 	 sprintf(proc_envp[8], "N002=%s\00", getenv("N002"));
 	 sprintf(proc_envp[9], "N003=%s\00", getenv("N003"));
 	 sprintf(proc_envp[10], "N004=%s\00", getenv("N004"));
 	 sprintf(proc_envp[11], "N005=%s\00", getenv("N005"));
 	 sprintf(proc_envp[12], "N007=%s\00", getenv("N007"));
 	 sprintf(proc_envp[13], "M001=%s\00", getenv("M001"));
 	 sprintf(proc_envp[14], "M002=%s\00", getenv("M002"));
 	 sprintf(proc_envp[15], "M003=%s\00", getenv("M003"));
 	 sprintf(proc_envp[16], "M004=%s\00", getenv("M004"));
 	 sprintf(proc_envp[17], "M005=%s\00", getenv("M005"));
 	 proc_envp[18]=NULL;
#endif
#if defined VMS
         proc_envp[0]=NULL;
#endif
printf("Prima vfork\n");
#ifndef SCO_UNIX
         pid_staz = vfork();
#else
         pid_staz = fork();
#endif
         stato_staz=pid_staz;
         if(stato_staz==(-1))
                 perror("vfork staz");
         if ( stato_staz == 0 )
              {
#ifndef SCO_UNIX
              sigsetmask(0);      /* sblocca tutti i segnali */
#endif
              execve(proc_name,proc_argv,proc_envp);
              perror("execve staz");
              exit(0);
              }
        free(proc_argv[0]);
	free(proc_argv[1]);
        for(i=0; i<18; i++)
		free(proc_envp[i]);
	}

/*  accoda richiesta al processo XSTAZ */

	strncpy(app,lista_pag[pag_selez],LUN_NOM_PAG);
	app[LUN_NOM_PAG]=0;
	for (i=0; i<LUN_NOM_PAG; i++) if (app[i] == ' ') app[i]=0; 
	strcpy(richiesta_staz.nome_pagina,app);
	richiesta_staz.mtype=RIC_STAZ;
	msg_snd(id_msg_staz,&richiesta_staz,sizeof(richiesta_staz.nome_pagina),IPC_NOWAIT);
        break;
	}
	case k_staz_annulla:
	{
          XtUnmanageChild(widget_array[k_staz_dialog]);
          break;
	}
}
}

/*
	routine lettura di lettura dal file r02.dat dei descrittori 
        delle pagine di stazioni 
*/
read_r02()
{
FILE *fp;
int  i, col, ilista;
char *pdata, app[10];
HEAD_R02 header;
S_PAGINA pagina;

/* legge il file r02.dat */

fp=fopen("r02.dat","r+");
if (fp == NULL)
{
        printf("\n monit_staz: errore in apertura r02.dat ");
        return(-1);
}

/* lettura header file r02.dat e allocamento area di memoria necessaria */

fread(header.data,sizeof (HEAD_R02), 1, fp);
tot_pagine=header.tot_pagine;
printf(" tot_pagine %d \n",tot_pagine);

col=LUN_NOM_PAG + LUN_DES_PAG +5 ;
pdata = (char *) calloc(tot_pagine * col,  sizeof(char));
if(pdata==(char *)NULL) {
                printf("\n monit_staz mancanza di spazio per allocazione");
                exit(1);
                }
lista_pag = (char **) calloc(tot_pagine, sizeof(char *))
;
if(lista_pag==(char **)NULL) {
                printf("\n monit_staz mancanza di spazio per allocazione");
                exit(1);
                }
for(i=0; i<tot_pagine ;i++)
                {
                lista_pag[i]=pdata;
                pdata+=col;
                }
ilista=0;
for (i=0; i< tot_pagine; i++)
{
        fread((char*)&pagina.attiva,sizeof (S_PAGINA), 1, fp);
	if (pagina.num_staz < MIN_NUM_STAZ) continue;
	memset(app,' ',LUN_NOM_PAG);
	memcpy(app,pagina.nome,strlen(pagina.nome));
	app[LUN_NOM_PAG]=0;
        sprintf(lista_pag[ilista],"%s - %s",app,pagina.descrizione);
	ilista++;
}
fclose(fp);
return(0);
}
