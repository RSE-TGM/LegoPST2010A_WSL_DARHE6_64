/**********************************************************************
*
*       C Source:               monit_perturba.c
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Wed Apr  8 14:19:27 1998 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: monit_perturba.c-7 %  (%full_filespec: monit_perturba.c-7:csrc:1 %)";
#endif
/*
Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)monit_perturba.c	5.4\t6/18/96";
/*
modulo monit_perturba.c
tipo 
release 5.4
data 6/18/96
reserved @(#)monit_perturba.c	5.4
*/
/*
*  moperturba.c
*     legge la lista delle variabili di ingresso e le mostra all'utente
*     per la scelta delle variabili da perturbare  */

#include <sys/types.h>
#include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
#include	<signal.h>

#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
#endif
#if defined VMS
# include "vmsipc.h"
#endif
# include <X11/Xlib.h>
# include <Mrm/MrmAppl.h>
# include <Xm/List.h>
# include <Xm/Text.h>
# include <Xm/Xm.h>
# include "sim_param.h"         /* parametri generali LEGO          */
# include "sim_types.h"         /* tipi e costanti LEGO             */
# include "monit.h"
# include "monituil.h"
# include "ric_aing.h"
# include "dispatcher.h"
# include "libutilx.h"
# include <Rt/RtMemory.h>


/* ************** Definizione variabili globali ******************** */

extern VALORI_AGG val_agg;        /* struttura contenente i valori che 
			     richiedono aggiornamento periodico  */
extern TIPO_PERT * perturbazioni; /* puntatore alla tabella perturbazioni  */
extern VARIABILI *variabili;      /* database delle variabili  */
extern int tot_variabili;         /* numero totale delle variabili */
extern char *ind_sh_top;          /* puntatore inizio shared memory sh_var */
Display *display;
int modello_selezionato;
int blocco_selezionato;
int posizione_ingresso;
int perturbazione_selezionata;
int lung_ingr;  /* numero di variabili non selezionate visualizzate
						 */
int start_ricerca_ingr = 1;

extern int id_msg_aing;		/* coda di messaggi con aing */
extern int id_msg_ret_aing;	/* coda di messaggi con aing x legocad*/
RICHIESTA_AING richiesta_aing;  /* struttura per richiesta aing */
RITORNO_AING ritorno_aing;      /* struttura per ritorno aing x legocad*/

int stato_aing=0;	/* 1 processo aing gia' attivato */
int pid_aing= -1;
int editpert_addr = -1;
int editpert_pos = -1;
TIPO_PERT perturbazione_esaminata;
char editpert_label[MAX_LUN_NOME_VAR];
Widget widget_array[MAX_WIDGETS];/* Place to keep all other */
	     


/* ***************** Elenco procedure inserite ******************** */
void mo_per_sel(Widget);
void seleziona_pert();
void seleziona_pert_activate();
void cerca_ingr_avanti();
void cerca_ingr_indietro();
void elenca_pert();
void elenca_modpert();
void seleziona_inputstat();
void seleziona_inputstat_activate();
extern void tab_perturba();
void aing();
void  stringa_pert();


extern int _MAX_SNAP_SHOT;
extern int _MAX_BACK_TRACK;
extern int _MAX_CAMPIONI;
extern int _NUM_VAR;
extern int _MAX_PERTUR;
extern int _SPARE_SNAP;


/* **************** Procedure *************************************** */


void mo_pert_sel(lista)
Widget lista;
/* *************** Definizione variabili locali  ***************** */
{
int k;
char testo[500];
char *str;
int totale;
XmString c_str;
int posizione =0;
XmString c_app_str;
char app_str[80];

XtUnmanageChild(lista);
get_something(lista,XmNitemCount,(void*) &totale);
for(k=1;k<=totale;k++,XmListDeletePos(lista,1));
for( k =1 ; k <= tot_variabili ; k++ )
{
if((variabili[k-1].mod==(modello_selezionato))&&
((blocco_selezionato==1+numero_blocchi(ind_sh_top,modello_selezionato))||
(variabili[k-1].blocco==(blocco_selezionato)))&&
((variabili[k-1].tipo==INGRESSO_NC)))
{
++posizione;
sprintf(testo,"%s - %s",variabili[k-1].nome,variabili[k-1].descr);
str=(char*)XtMalloc(sizeof(char)*(strlen(testo)+20));
strcpy(str,testo);
c_str=XmStringCreateLtoR(str,XmSTRING_DEFAULT_CHARSET);
XmListAddItemUnselected(lista,c_str,0);
set_something_val(lista,XmNitemCount,(XtArgVal) posizione);
XSync(display,False);
XtFree(str);
XmStringFree(c_str);
}
}
lung_ingr=posizione;
XtManageChild(lista);
}


void seleziona_pert(w, tag, reason)
Widget w;
int *tag;
XmListCallbackStruct *reason;
{
int i;
XSync(display,False);
if (*tag==k_elenco_modelli_pert)
{
modello_selezionato=reason->item_position;
blocco_selezionato=1;
mo_blocchi(widget_array[k_elenco_blocchi_pert]);
mo_pert_sel(widget_array[k_elenco_ingressi]);
start_ricerca_ingr=1;
}
if (*tag==k_elenco_blocchi_pert)
{
blocco_selezionato=reason->item_position;
mo_pert_sel(widget_array[k_elenco_ingressi]);
start_ricerca_ingr=1;
}
if (*tag==k_elenco_ingressi);
posizione_ingresso=reason->item_position;

}

void seleziona_pert_activate(w, tag, reason)
Widget w;
int *tag;
unsigned long *reason;
{
int k;
int j;
int i;
XmString c_app_str;
char app_str[80];
int posizione = 0;
char app[10];
static int pos_x =0;
static int pos_y =90;
static int inc_pos=0;
char *proc_argv[4];
char *proc_envp[20];
char proc_name[FILENAME_MAX];
char *getenv();
char *path;

XSync(display,False);

if (*tag==k_elenco_pert_cerca_avanti)
{
cerca_ingr_avanti();
}
if (*tag==k_elenco_pert_cerca_ind)
{
cerca_ingr_indietro();
}
if (*tag==k_elenco_pert_fine)
{
XtUnmanageChild(widget_array[k_elenco_pert_dialog]);
}
if (*tag==k_elenco_pert_ok)
{
for( k =1 ; k <= tot_variabili ; k++ )
{
  if((variabili[k-1].mod==(modello_selezionato))&&
((blocco_selezionato==1+numero_blocchi(ind_sh_top,modello_selezionato))||
    (variabili[k-1].blocco==(blocco_selezionato)))&&
     ((variabili[k-1].tipo==INGRESSO_NC)))
	{
	++posizione;
	if(posizione==posizione_ingresso) break;
	}
}
/* verifica la necessita' di lanciare il processo aing */
stato_aing=stato_processo(pid_aing);
if(stato_aing<=0)
 {
 /* lancia il processo aing */
 path=getenv("LEGORT_BIN");

 proc_argv[0]=(char*)malloc(FILENAME_MAX+1);
 proc_argv[1]=(char*)malloc(FILENAME_MAX+1);
 proc_argv[2]=(char*)malloc(FILENAME_MAX+1);
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
 proc_envp[18]=(char*)malloc(FILENAME_MAX+1);
 proc_envp[19]=(char*)malloc(FILENAME_MAX+1);
 
#if defined UNIX
 sprintf(proc_name,"%s/xaing\00",path);
#endif
#if defined VMS
 sprintf(proc_name,"%sxaing\00",path);
#endif
 sprintf(proc_argv[0],"xaing\00");
 sprintf(proc_argv[1],"%d\00",1);
/* MAURIC */
 free(proc_argv[2]);

 proc_argv[2]=NULL;
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
/* MAURIC */ 
 free(proc_envp[18]);
 free(proc_envp[19]);
 proc_envp[18]=NULL;
 proc_envp[19]=NULL;
#endif
#if defined VMS
 proc_envp[0]=NULL;
#endif
#ifndef SCO_UNIX
 pid_aing = vfork();
#else
 pid_aing = fork();
#endif
 stato_aing=pid_aing;
 if(stato_aing==(-1))
	 perror("vfork aing");
 if ( stato_aing == 0 )
      {
#ifndef SCO_UNIX
      sigsetmask(0);      /* sblocca tutti i segnali */
#endif
      execve(proc_name,proc_argv,proc_envp);
      perror("execve aing");
      exit(0);
      }
#if defined UNIX
free(proc_argv[0]);
free(proc_argv[1]);
for(i=0; i<18; i++)
        free(proc_envp[i]);
printf("Fine delle free\n");
#endif
 }

strcpy(richiesta_aing.nome_variabile,variabili[k-1].nome);
richiesta_aing.mtype=RIC_AING;
msg_snd(id_msg_aing,&richiesta_aing,
	sizeof(RICHIESTA_AING) - sizeof(long),IPC_NOWAIT);
/*set_nom_log_s(app,strlen(app)+1,"VAR_AING","EASE$LNM");*/

/* posizione Y da passare ad AING  */
/*
strcpy(app,"100");*/
sprintf(app,"%d",pos_y+inc_pos);
/*
set_nom_log_s(app,strlen(app)+1,"Y_AING","EASE$LNM");*/

/* posizione X da passare ad AING  */
/*
strcpy(app,"100");*/
sprintf(app,"%d",pos_x+inc_pos);
/*set_nom_log_s(app,strlen(app)+1,"X_AING","EASE$LNM");*/
/*	
set_ef(7,1);
set_ef(6,1);*/
/* gestione posizione AING */
pos_x=pos_x+50;
if (pos_x==200)
	{
	pos_x=0;
	pos_y=pos_y+40;
	}
if (pos_y==170)
	{
	pos_y=90;
	inc_pos=inc_pos+10;
	}
}
}

void cerca_ingr_avanti()
{
char app_str[80];
char mom[120];
int posizione = 0;
int k;
int trovata =0;

strcpy(app_str,XmTextGetString
	    (widget_array[k_elenco_pert_text_cerca]));
/* cerca da start_ricerca_ingr alla fine */
for( k = 1 ; k <= tot_variabili ; k++ )
{
if((variabili[k-1].mod==(modello_selezionato))&&
((blocco_selezionato==1+numero_blocchi(ind_sh_top,modello_selezionato))||
(variabili[k-1].blocco==(blocco_selezionato)))&&
((variabili[k-1].tipo==INGRESSO_NC)))
{
strcpy(mom,variabili[k-1].nome);
++ posizione;
if((Utstrstr(strcat(mom,variabili[k-1].descr),app_str)!=NULL)&&
(variabili[k-1].tipo==INGRESSO_NC)&&(k>start_ricerca_ingr))
{
start_ricerca_ingr=k;
trovata=1;
UtListaScroll(widget_array[k_elenco_ingressi],
	lung_ingr,6,posizione-1);
XSync(display,False);
break;
}
}
}
if(!trovata)
{
/*cerca dall'inizio a start_ricerca_ingr  */
posizione = 0;
for( k = 1 ; k <= tot_variabili ; k++ )
{
if((variabili[k-1].mod==(modello_selezionato))&&
((blocco_selezionato==1+numero_blocchi(ind_sh_top,modello_selezionato))||
(variabili[k-1].blocco==(blocco_selezionato)))&&
((variabili[k-1].tipo==INGRESSO_NC)))
{
strcpy(mom,variabili[k-1].nome);
++ posizione;
if((Utstrstr(strcat(mom,variabili[k-1].descr),app_str)!=NULL)&&
(variabili[k-1].tipo==INGRESSO_NC)&&(k<=start_ricerca_ingr))
{
start_ricerca_ingr=k;
UtListaScroll(widget_array[k_elenco_ingressi],
	lung_ingr,6,posizione-1);
XSync(display,False);
break;
}
}
}
}
}
void cerca_ingr_indietro()
{
char app_str[80];
char mom[120];
int posizione = 0;
int k;
int trovata =0;
		       
posizione = lung_ingr+1;
strcpy(app_str,XmTextGetString
	    (widget_array[k_elenco_pert_text_cerca]));
/* cerca da start_ricerca_ingr alla fine */
for( k = tot_variabili ; k >= 1 ; k-- )
{
if((variabili[k-1].mod==(modello_selezionato))&&
((blocco_selezionato==1+numero_blocchi(ind_sh_top,modello_selezionato))||
(variabili[k-1].blocco==(blocco_selezionato)))&&
((variabili[k-1].tipo==INGRESSO_NC)))
{
strcpy(mom,variabili[k-1].nome);
-- posizione;
if((Utstrstr(strcat(mom,variabili[k-1].descr),app_str)!=NULL)&&
(variabili[k-1].tipo==INGRESSO_NC)&&(k<start_ricerca_ingr))
{
start_ricerca_ingr=k;
trovata=1;
UtListaScroll(widget_array[k_elenco_ingressi],
	lung_ingr,6,posizione-1);
XSync(display,False);
break;
}
}
}
if(!trovata)
{
/*cerca dall'inizio a start_ricerca_ingr  */
posizione = lung_ingr+1;
for( k = tot_variabili ; k >= 1 ; k-- )
{
if((variabili[k-1].mod==(modello_selezionato))&&
((blocco_selezionato==1+numero_blocchi(ind_sh_top,modello_selezionato))||
(variabili[k-1].blocco==(blocco_selezionato)))&&
((variabili[k-1].tipo==INGRESSO_NC)))
{
strcpy(mom,variabili[k-1].nome);
-- posizione;
if((Utstrstr(strcat(mom,variabili[k-1].descr),app_str)!=NULL)&&
(variabili[k-1].tipo==INGRESSO_NC)&&(k>=start_ricerca_ingr))
{
start_ricerca_ingr=k;
UtListaScroll(widget_array[k_elenco_ingressi],
	lung_ingr,6,posizione-1);
XSync(display,False);
break;
}
}
}
}
}

void elenca_pert(lista_1,lista_2)
Widget lista_1,lista_2;
/* *************** Definizione variabili locali  ***************** */
{
int k;
char testo[500];
char *str;
int totale_1,totale_2;
XmString c_str;
int posizione =0;
XmString c_app_str;
char app_str[80];
int variab;

XtUnmanageChild(lista_1);
XtUnmanageChild(lista_2);
get_something(lista_1,XmNitemCount,(void*) &totale_1);
get_something(lista_2,XmNitemCount,(void*) &totale_2);
for(k=1;k<=totale_1;k++,XmListDeletePos(lista_1,1));
for(k=1;k<=totale_2;k++,XmListDeletePos(lista_2,1));
for( k =0 ; k < _MAX_PERTUR*2 ; k++ )
{
if(perturbazioni[k].tipo != -1)
{
++posizione;
perturbazioni[k].rateo_durata=
	(float)fabs((double)perturbazioni[k].rateo_durata);
for( variab = 0; variab < tot_variabili ; variab ++ )
if(variabili[variab].addr == perturbazioni[k].indirizzo)
	break;

switch(perturbazioni[k].tipo){
case (PERT_SCALINO):
	{
	sprintf(testo,"STEP on %s - target value %f",
	    variabili[variab].nome, perturbazioni[k].valore_delta);
	break;
	};
case (PERT_RAMPA):
	{
	sprintf(testo,"RAMP on %s - target value %f - grad. %f",
	    variabili[variab].nome, perturbazioni[k].valore_delta,
		perturbazioni[k].rateo_durata);
	break;
	};
case (PERT_RAMPA_STOP):
	{
	sprintf(testo,"STOP RAMP on %s", variabili[variab].nome);
	break;
	};
case (PERT_TO):
	{
	sprintf(testo,"TO on %s - target value %f",
	    variabili[variab].nome, perturbazioni[k].valore_delta);
	break;
	};
case (PERT_TO_STOP):
	{
	sprintf(testo,"STOP TO on %s", variabili[variab].nome);
	break;
	};
case (PERT_IMPULSO):
	{
	sprintf(testo,"PULSE on %s - target value %f - wide %f",
	    variabili[variab].nome, perturbazioni[k].valore_delta,
		perturbazioni[k].rateo_durata);
	break;
	};
case (PERT_IMPULSO_STOP):
	{
	sprintf(testo,"STOP PULSE on %s", variabili[variab].nome);
	break;
	};
case (PERT_UP):
	{
	sprintf(testo,"UP on %s", variabili[variab].nome);
	break;
	};
case (PERT_DOWN):
	{
	sprintf(testo,"DOWN on %s", variabili[variab].nome);
	break;
	};
case (PERT_NOT):
	{
	sprintf(testo,"NOT on %s", variabili[variab].nome);
	break;
	};
case (PERT_PERIODIC):
	{
	if(perturbazioni[k].valore_delta== -1)
		sprintf(testo,
   "SINUSOIDAL on %s - period= %f - wide = %f - mean value = %f - phase = %f", 
		variabili[variab].nome, perturbazioni[k].period,
		perturbazioni[k].wide,perturbazioni[k].meanvalue,
		perturbazioni[k].phase);
	else
		sprintf(testo,
   "TRAPEZOIDAL on %s - period= %f - wide = %f - mean value = %f - phase = %f T1=%f - T2 = %f - T3 = %f", 
		variabili[variab].nome, perturbazioni[k].period,
		perturbazioni[k].wide,perturbazioni[k].meanvalue,
		perturbazioni[k].phase, perturbazioni[k].valore_delta,
		perturbazioni[k].rateo_durata,perturbazioni[k].t_null_var);
	break;
	};
case (PERT_PERIODIC_STOP):
	{
	sprintf(testo,"STOP PERIODIC on %s", variabili[variab].nome);
	break;
	};
case (PERT_WHITENOISE):
	{
	sprintf(testo,"WHITE NOISE on %s - variance %f - mean value %f", 
			variabili[variab].nome,perturbazioni[k].t_null_var,
			perturbazioni[k].meanvalue);
	break;
	};
case (PERT_WHITENOISE_STOP):
	{
	sprintf(testo,"STOP WHITE NOISE on %s",variabili[variab].nome);
	break;
	};
case (PERT_MALFUNCTION):
        {
        sprintf(testo,"MALFUNCTION on %s - type %f - target value %f",
                        variabili[variab].nome,perturbazioni[k].t_null_var,
                        perturbazioni[k].valore_delta);
        break;
        };
case (PERT_MALFUNCTION_STOP):
        {
        sprintf(testo,"STOP MALFUNCTION on %s",variabili[variab].nome);
        break;
        };
};
if(perturbazioni[k].t >0)
sprintf(testo,"%s  [on at %f]", 
	testo, perturbazioni[k].t+val_agg.tempo_sim);


str=(char*)XtMalloc(sizeof(char)*(strlen(testo)+20));
strcpy(str,testo);
c_str=XmStringCreateLtoR(str,XmSTRING_DEFAULT_CHARSET);
if(perturbazioni[k].t <= 0)
{
XmListAddItemUnselected(lista_1,c_str,0);
}
else
{
XmListAddItemUnselected(lista_2,c_str,0);
}
XSync(display,False);
XtFree(str);
XmStringFree(c_str);
}
}
XtManageChild(lista_1);
XtManageChild(lista_2);
}

void seleziona_inputstat(w, tag, reason)
Widget w;
int *tag;
XmListCallbackStruct *reason;
{
static Widget attenzione=NULL;

perturbazione_selezionata=reason->item_position;
}

void seleziona_inputstat_activate(w, tag, reason)
Widget w;
int *tag;
unsigned long *reason;
{
int widget_num = *tag;
int cont = 0;
int k;

for(k=_MAX_PERTUR;k<_MAX_PERTUR*2;k++)
	{
	if((perturbazioni[k].tipo!= -1)&&(perturbazioni[k].t>0))
		cont++;
	if((cont == perturbazione_selezionata)&&(perturbazioni[k].t>0))
		break;
	}
/*
perturbazione_selezionata=k-_MAX_PERTUR+1;
*/
perturbazione_selezionata=perturbazioni[k].posizione;
if((perturbazione_selezionata>0)&&
	(perturbazione_selezionata<=_MAX_PERTUR))
	if(SD_removepert(MONIT,&perturbazione_selezionata)>0)
		vis_messaggio("Pert removed",0);
	else
		vis_messaggio("Error pert not removed",1);
perturbazione_selezionata=0;	
}

void seleziona_editpert(w, tag, reason)
Widget w;
int *tag;
XmListCallbackStruct *reason;
{
static Widget attenzione=NULL;
int widget_num = *tag;
int posizione = reason->item_position;
char testo[200];
int variab;



/* estrae la stringa dalla lista */
strcpy(testo,extract_string(reason->item));

if(widget_num == k_editpert_lista_1)
{
memcpy(editpert_label,testo,MAX_LUN_NOME_VAR-1);
editpert_label[MAX_LUN_NOME_VAR-1]=0;
/*
      Cerca la label
*/
for( variab = 0; variab < tot_variabili ; variab ++ )
     if(strncmp(variabili[variab].nome, 
		editpert_label,MAX_LUN_NOME_VAR-1)==0)
	     break;
editpert_addr=variabili[variab].addr;
editpert_pos = -1;
elenca_modpert (widget_array[k_editpert_lista_1],
		widget_array[k_editpert_lista_2],2);
}

if(widget_num == k_editpert_lista_2)
	{
	editpert_pos = posizione;
	}

}

void seleziona_editpert_activate(w, tag, reason)
Widget w;
int *tag;
unsigned long *reason;
			  
{
int widget_num = *tag;
int cont = 0;
int k,k1;
int pos = 0;
static Widget attenzione=NULL;
Dialog_geometry geom;


/*
    CASO DI EDIPERT
*/
    if( widget_num == k_editpert_mod )
        {
	if(editpert_addr>0)
          {
          for( k =0 ; k < _MAX_PERTUR*2 ; k++ )
	    {
            if( (perturbazioni[k].tipo != -1)&&
                (perturbazioni[k].indirizzo==editpert_addr) )
                {
                pos ++;
                if(pos == editpert_pos)
			{
			memcpy(&perturbazione_esaminata,
				&perturbazioni[k],sizeof(TIPO_PERT));
/*
                        printf(" editpert_addr=%d editpert_pos=%d k=%d\n",
                                 editpert_addr,editpert_pos,k);
*/
			break;
			}
		}
/*
            printf("\t\t k=%d tipo=%d ind=%d (e_addr=%d)\n",
                    k,perturbazioni[k].tipo,perturbazioni[k].indirizzo,
                    editpert_addr);
*/
	    }
	  if(k!=_MAX_PERTUR*2)
	     {
             aing(editpert_label);
             msg_rcv(id_msg_ret_aing,&ritorno_aing,
                     sizeof (RITORNO_AING)-sizeof(long),
                     (long)RIC_AING, !IPC_NOWAIT, 0) ;
	     if(ritorno_aing.modifica_pert == PERT_ERRORE)
		{
		geom.default_pos=1;
        	geom.height=200;
        	if(attenzione==NULL)
                	attenzione=attention(widget_array[k_editpert],
                        	"Warning impossible modify input",
                        	CREA|MAPPA,geom);
        	else
                	attenzione=attention(widget_array[k_editpert],
                        	"Warning mpossible modify input",
                        	MAPPA,geom);
		}
	     else
                if(ritorno_aing.modifica_pert == PERT_MODIFICATA)
			{
			k1=k-_MAX_PERTUR+1; 
/*
                        PERT_MODIFICA:
                        Consentito solo per quelle in attesa per cui 
                        si fara' remove_pert direttamente sulle
                        _MAX_PERTUR pert_att e si deve passare un indice
                        che va da 1 a _MAX_PERTUR.
*/
/*
                        printf("\t sel_editpert_act,rm k1=%d (k=%d, MAX=%d)\n",
                               k1,k,_MAX_PERTUR);
*/
                        if( k1>=0 )
                           SD_removepert(MONIT,&k1);
                        else
                           fprintf(stderr, 
                   " ATTENZIONE perturbazione in corso, non rimuovibile\n");
			}
	     } /* Fine test su k!=_MAX_PERTUR*2   */
          }    /* Fine test su editpert_addr>0   */
        }      /* Fine test su k_editpert_mod    */

   
/*
    CASO DI EDIPERT DEL
*/
    if( widget_num == k_editpert_del )
        {
	if(editpert_addr>0)
          {
	  for( k =0 ; k < _MAX_PERTUR*2 ; k++ )
            {
	    if((perturbazioni[k].tipo != -1)&&
		(perturbazioni[k].indirizzo==editpert_addr))
                {
	        pos ++;
		if(pos == editpert_pos)
			{
			k1=k-_MAX_PERTUR+1;
/*
                        printf("\t sel_editpert_activate2,rm k1=%d k=%d\n",
                                  k1,k);
*/
			SD_removepert(MONIT,&k1);
			tab_perturba();
			elenca_modpert (widget_array[k_editpert_lista_1],
                                        widget_array[k_editpert_lista_2],1);
			elenca_modpert (widget_array[k_editpert_lista_1],
                                        widget_array[k_editpert_lista_2],2);
			editpert_pos= -1;
			break;
			}
                }
            }   /* Fine ciclo k<_MAX_PERTUR*2    */
          }     /* Fine test su editpert_addr>0 */
	}       /* Fine test su k_editpert_del  */

/*
    CASO DI EDIPERT DEL ALL
*/
    if( widget_num == k_editpert_del_all )
        {
	for( k =0 ; k < _MAX_PERTUR*2 ; k++ )
	   if( (perturbazioni[k].tipo != -1)&&
               (perturbazioni[k].t >= 0) )
  		{
		k1=k-_MAX_PERTUR+1;
		SD_removepert(MONIT,&k1);
		}
        editpert_addr = -1;
        editpert_pos = -1;
	tab_perturba();
	elenca_modpert (widget_array[k_editpert_lista_1],
			widget_array[k_editpert_lista_2],1);
	elenca_modpert (widget_array[k_editpert_lista_1],
			widget_array[k_editpert_lista_2],2);
        }
}

void elenca_modpert(Widget lista_1,Widget lista_2,int modo)
/* *************** Definizione variabili locali  ***************** */
{
int k, i;
char testo[500];
char *str;
int totale_1,totale_2;
XmString c_str;
int posizione =0;
XmString c_app_str;
char app_str[80];
int variab;
int label_doppia;


tab_perturba();

if(modo==1)
	{
	XtUnmanageChild(lista_1);
	get_something(lista_1,XmNitemCount,(void*) &totale_1);
	for(k=1;k<=totale_1;k++,XmListDeletePos(lista_1,1));
	}

if(modo==2)
	{
	XtUnmanageChild(lista_2);
	get_something(lista_2,XmNitemCount,(void*) &totale_2);
	for(k=1;k<=totale_2;k++,XmListDeletePos(lista_2,1));
	}

if(modo==1)
	{
	for( k =0 ; k < _MAX_PERTUR*2 ; k++ )
	 {
	if((perturbazioni[k].tipo != -1)&&(perturbazioni[k].t >= 0))
   	   {
   	   ++posizione;
	   /* 
		Evita la ripetizione delle label
           */
	   label_doppia = 0;
	   for(i=0; i < k ; i++ )
		if((perturbazioni[k].indirizzo==perturbazioni[i].indirizzo)&&
			(perturbazioni[i].t >= 0))
				{
	   			label_doppia = 1;
				break;
				}
	   if(label_doppia)
		continue;


   	   /*
	 	   Cerca la label
   	   */
   	   for( variab = 0; variab < tot_variabili ; variab ++ )
		   if(variabili[variab].addr == perturbazioni[k].indirizzo)
			   break;
 	    
   	   sprintf(testo,"%s - %s",variabili[variab].nome,
			variabili[variab].descr);
   	   str=(char*)XtMalloc(sizeof(char)*(strlen(testo)+20));
   	   strcpy(str,testo);
   	   c_str=XmStringCreateLtoR(str,XmSTRING_DEFAULT_CHARSET);
   	   XmListAddItemUnselected(lista_1,c_str,0);
   	   XSync(display,False);
   	   XtFree(str);
   	   XmStringFree(c_str);
  	   }
	 }
        XtManageChild(lista_1);
  	}
if(modo==2)
	{
	if(editpert_addr>0)
          {
	  for( k =0 ; k < _MAX_PERTUR*2 ; k++ )
	    {
	    if((perturbazioni[k].tipo != -1)&&
		(perturbazioni[k].indirizzo==editpert_addr))
  		{
		stringa_pert(testo,perturbazioni[k],editpert_label);
   	        str=(char*)XtMalloc(sizeof(char)*(strlen(testo)+20));
   	        strcpy(str,testo);
   	        c_str=XmStringCreateLtoR(str,XmSTRING_DEFAULT_CHARSET);
   	        XmListAddItemUnselected(lista_2,c_str,0);
   	        XSync(display,False);
   	        XtFree(str);
   	        XmStringFree(c_str);
		}
	     }
	  XtManageChild(lista_2);
	  }

	}
}


void  stringa_pert(testo,perturbazione,label)
char *testo,*label;
TIPO_PERT perturbazione;
{
   switch(perturbazione.tipo){
        case (PERT_SCALINO):
                {
                sprintf(testo,"STEP on %s - target value %f",
                    label, perturbazione.valore_delta);
                break;
                };
        case (PERT_RAMPA):
                {
                sprintf(testo,"RAMP on %s - target value %f - grad. %f",
                    label, perturbazione.valore_delta,
                        perturbazione.rateo_durata);
                break;
                };
        case (PERT_RAMPA_STOP):
                {
                sprintf(testo,"STOP RAMP on %s", label);
                break;
                };
        case (PERT_TO):
                {
                sprintf(testo,"TO on %s - target value %f",
                    label, perturbazione.valore_delta);
                break;
                };
        case (PERT_TO_STOP):
                {
                sprintf(testo,"STOP TO on %s", label);
                break;
                };
        case (PERT_IMPULSO):
                {
                sprintf(testo,"PULSE on %s - target value %f - wide %f",
                    label, perturbazione.valore_delta,
                        perturbazione.rateo_durata);
                break;
                };
        case (PERT_IMPULSO_STOP):
                {
                sprintf(testo,"STOP PULSE on %s", label);
                break;
                };
        case (PERT_UP):
                {
                sprintf(testo,"UP on %s", label);
                                                                             
                };
        case (PERT_DOWN):
                {
                sprintf(testo,"DOWN on %s", label);
                break;
                };
        case (PERT_NOT):
                {
                sprintf(testo,"NOT on %s", label);
                break;
                };
	case (PERT_PERIODIC):
		{
		if(perturbazione.valore_delta== -1)
			sprintf(testo,
   "SINUSOIDAL on %s - period= %f - wide = %f - mean value = %f - phase = %f", 
			label, perturbazione.period,
		 	perturbazione.wide,perturbazione.meanvalue,
			perturbazione.phase);
		else
			sprintf(testo,
   "TRAPEZOIDAL on %s - period= %f - wide = %f - mean value = %f - phase = %f T1=%f - T2 = %f - T3 = %f", 
			label, perturbazione.period,
			perturbazione.wide,perturbazione.meanvalue,
			perturbazione.phase, perturbazione.valore_delta,
	 		perturbazione.rateo_durata,
			perturbazione.t_null_var);
		break;
		};
	case (PERT_PERIODIC_STOP):
		{
		sprintf(testo,"STOP PERIODIC on %s", label);
		break;
		};
	case (PERT_WHITENOISE):
		{
     	      sprintf(testo,"WHITE NOISE on %s - variance %f - mean value %f", 
			label,perturbazione.t_null_var,
				perturbazione.meanvalue);
		break;
		};
	case (PERT_WHITENOISE_STOP):
		{
		sprintf(testo,"STOP WHITE NOISE on %s",label);
		break;
		};
        case (PERT_MALFUNCTION):
                {
              sprintf(testo,"MALFUNCTIONE on %s - variance %f - mean value %f",
                        label,perturbazione.t_null_var,
                        perturbazione.valore_delta);
                break;
                };
        case (PERT_MALFUNCTION_STOP):
                {
                sprintf(testo,"STOP MALFUNCTIONE on %s",label);
                break;
                };
        };
   if(perturbazione.t >0)
        sprintf(testo,"%s  [on at %f]",
                testo, perturbazione.t+val_agg.tempo_sim);
}



void aing(label)
char *label;
{
int k;
int j;
XmString c_app_str;
char app_str[80];
int posizione = 0;
char app[10];
static int pos_x =0;
static int pos_y =90;
static int inc_pos=0;
char *proc_argv[4];
char *proc_envp[20];
char proc_name[FILENAME_MAX+1];
char *getenv();
char *path;

/* verifica la necessita' di lanciare il processo aing */
stato_aing=stato_processo(pid_aing);
if(stato_aing<=0)
 {
 /* lancia il processo aing */
 path=getenv("LEGORT_BIN");

 proc_argv[0]=(char*)malloc(FILENAME_MAX+1);
 proc_argv[1]=(char*)malloc(FILENAME_MAX+1);
 proc_argv[2]=(char*)malloc(FILENAME_MAX+1);
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
 proc_envp[18]=(char*)malloc(FILENAME_MAX+1);
 proc_envp[19]=(char*)malloc(FILENAME_MAX+1);

#if defined UNIX
 sprintf(proc_name,"%s/xaing\00",path);
#endif
#if defined VMS
 sprintf(proc_name,"%sxaing\00",path);
#endif
 sprintf(proc_argv[0],"xaing\00");
 sprintf(proc_argv[1],"%d\00",1);
 proc_argv[2]=NULL;
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
#ifndef SCO_UNIX
 pid_aing = vfork();
#else
 pid_aing = fork();
#endif
 stato_aing=pid_aing;
 if(stato_aing==(-1))
         perror("vfork aing");
 if ( stato_aing == 0 )
      {
#ifndef SCO_UNIX
      sigsetmask(0);      /* sblocca tutti i segnali */
#endif
      execve(proc_name,proc_argv,proc_envp);
      perror("execve aing");
      exit(0);
      }

 }

strcpy(richiesta_aing.nome_variabile,label);
memcpy(&richiesta_aing.perturbazione,
	&perturbazione_esaminata,sizeof(TIPO_PERT));
richiesta_aing.mtype=RIC_AING;
msg_snd(id_msg_aing,&richiesta_aing,
        sizeof(RICHIESTA_AING) - sizeof(long) ,IPC_NOWAIT);
memset(&richiesta_aing.perturbazione,0,sizeof(TIPO_PERT));
}
