/**********************************************************************
*
*       C Source:               monit_snapshot.c
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Tue Jan 18 14:48:06 2000 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: monit_snapshot.c-7 %  (%full_filespec: monit_snapshot.c-7:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)monit_snapshot.c	5.5\t2/20/96";
/*
   modulo monit_snapshot.c
   tipo 
   release 5.5
   data 2/20/96
   reserved @(#)monit_snapshot.c	5.5
*/
# include <stdio.h>
# include <math.h>
# include <string.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
# include <sys/time.h>
# include <sys/timeb.h>
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
# include "monit.h"
# include "monituil.h"
# include "libutilx.h"
# include "sked.h"
# include "dispatcher.h"
#if defined BANCO_MANOVRA
# include "agg_manovra.h"
#endif
# include <Rt/RtMemory.h>

/* ***************** definizione variabili globali ***************** */

extern SNTAB *snapshot;         /* puntatore alla tabella snapshot  */
extern void tab_snapshot();

#if defined BANCO_MANOVRA
extern ALLINEAMENTO lista_comp;
void prepara_lista();
#endif

#if defined MFFR
extern SNAP_SKED sommari;
#endif

#if defined BACKTRACK
extern BKTAB *backtrack;         /* puntatore alla tabella backtrack  */
extern void tab_backtrack();
/*extern int punt_rec_backtrack[MAX_BACK_TRACK+1];*/
extern int *punt_rec_backtrack;
extern float intervallo_backtrack;
extern int last_backtrack;
extern int modo_bt;
extern int direzione_bt;
extern int last_load_bt;
extern int first_session_bt;
extern int last_session_bt;
extern int step_selezionato;
extern int num_bt_list;
/*extern int sessioni_bt[MAX_BACK_TRACK];*/
extern int *sessioni_bt;
extern time_t timer_auto_bt;
extern time_t old_time_bt;
extern int backtrack_selezionato;
#endif

extern struct timeb tempo;      /* tempo di orologio            */

/* area nomi variabili degli slot degli snapshot */
extern char var_slot[MAX_VAL_SNAP][MAX_LUN_NOME_VAR];


extern VALORI_AGG val_agg;


extern Widget widget_array[MAX_WIDGETS];
extern Widget main_window_widget;
extern Widget toplevel_widget; 

int snapshot_selezionato = 0;

/* coda di messaggi con sked */
extern int id_msg_monit;

#if defined BANCO_MANOVRA
extern int run_abilitato;
extern int check_in_corso;
#endif

extern int _MAX_SNAP_SHOT;
extern int _MAX_BACK_TRACK;
extern int _MAX_CAMPIONI;
extern int _NUM_VAR;
extern int _MAX_PERTUR;
extern int _SPARE_SNAP;

int BacktrackImmediato;

/* ****************  procedure inserite  ************************ */

void elenca_snapshot(); /* visualizza nella lista gli snapshot disponibili
		      per la funzione di visione snapshot            */
void carica_snapshot(); /* visualizza nella lista gli snapshot disponibili
		      per la funzione di caricamento                 */
void seleziona_snapshot(); /* funzione di callback per la selezione di uno 
			 snapshot dalla lista                        */
void snapshot_activate(); /* funzione di callback per tutti i bottoni delle 
			dialog box relative agli snapshot */

void carica_backtrack(); /* visualizza nella lista  backtrack disponibili
                      per la funzione di caricamento                 */
void carica_lista_comp(); /* visualizza la lista componenti disallineati */
void limiti_sessione();  /* calcola i limiti della sessione corrente */
void seleziona_backtrack(); /* funzione di callback per la selezione di un
                         backtrack dalla lista                        */
void backtrack_activate(); /* funzione di callback per tutti i bottoni delle
                        dialog box relative ai backtrack */
void check_banco();        /* esegue la procedura di controllo allineamento
                              componenti del banco manovra */
void override_allineamento(); /* bypassa la procedura di controllo
                                 allineamento*/

/***************************************************************************/



void elenca_snapshot(lista)
Widget lista;
{
int k,totale,i;
char testo[500];
char *str;
XmString c_str;
int posizione =0;

	get_something(lista,XmNitemCount, (void*) &totale);
	if(totale)
	for(k=1;k<=totale;k++,XmListDeletePos(lista,1));
	
	for (k=1;k<=_MAX_SNAP_SHOT;k++)
	{
   	++posizione;
   	if(snapshot[k-1].mod==0)
     	{
     	sprintf(testo,"%3d  -  %s",
			snapshot[k-1].prog,snapshot[k-1].descr);
     	if(snapshot[k-1].stat==1)
		{
        	sprintf(testo,"%s - %s - %s",
			testo,snapshot[k-1].datasn,snapshot[k-1].temposn);
        	for(i=0;i<MAX_VAL_SNAP;i++)
	  	if(var_slot[i][0]!=0)
			sprintf(testo,"%s - %s = %f\n",
				testo,var_slot[i],snapshot[k-1].val[i]);
		}
     	}
   	else
     	{
     	sprintf(testo,"%3d (*) -  %s",
			snapshot[k-1].prog,snapshot[k-1].descr);
     	if(snapshot[k-1].stat==1)
		{
        	sprintf(testo,"%s - %s - %s",
			testo,snapshot[k-1].datasn,snapshot[k-1].temposn);
        	for(i=0;i<MAX_VAL_SNAP;i++)
	  	if(var_slot[i][0]!=0)
			sprintf(testo,"%s - %s = %f\n",
				testo,var_slot[i],snapshot[k-1].val[i]);
		}
     	}
   str=(char*)XtMalloc(sizeof(char)*(strlen(testo)+20));
   strcpy(str,testo);
   c_str=XmStringCreate(str,XmSTRING_DEFAULT_CHARSET);


   XmListAddItemUnselected(lista,c_str,0);
   set_something(lista,XmNitemCount, (void*) posizione);

   XmStringFree(c_str);
   XtFree(str);
   	}
}

void carica_snapshot(lista)
Widget lista;
{
int k,totale,i;
char testo[500];
char *str;
XmString c_str;
int posizione =0;

if(val_agg.stato_sked!=STATO_BACKTRACK)
    {

get_something(lista,XmNitemCount, (void*) &totale);
if(totale)
for(k=1;k<=totale;k++,XmListDeletePos(lista,1));

for (k=1;k<=_MAX_SNAP_SHOT;k++)
{
   ++posizione;
   if(snapshot[k-1].mod==0)
	{
        sprintf(testo,"%3d  -  %s",
		snapshot[k-1].prog,snapshot[k-1].descr);
        if(snapshot[k-1].stat==1)
	   {
           sprintf(testo,"%s - %s - %s",
		testo,snapshot[k-1].datasn,snapshot[k-1].temposn);
           for(i=0;i<MAX_VAL_SNAP;i++)
	     if(var_slot[i][0]!=0)
		   sprintf(testo,"%s - %s = %f\n",
			   testo,var_slot[i],snapshot[k-1].val[i]);
	}
	}
   else
	{
      	sprintf(testo,"%3d (*) -  %s",
		snapshot[k-1].prog,snapshot[k-1].descr);
      	if(snapshot[k-1].stat==1)
	 	{
         	sprintf(testo,"%s - %s - %s",
			testo,snapshot[k-1].datasn,snapshot[k-1].temposn);
         	for(i=0;i<MAX_VAL_SNAP;i++)
	   	if(var_slot[i][0]!=0)
		 	sprintf(testo,"%s - %s = %f\n",
			testo,var_slot[i],snapshot[k-1].val[i]);
	 	}
	}

   str=(char*)XtMalloc(sizeof(char)*(strlen(testo)+20));
   strcpy(str,testo);
   c_str=XmStringCreate(str,XmSTRING_DEFAULT_CHARSET);


   XmListAddItemUnselected(lista,c_str,0);
   set_something(lista,XmNitemCount, (void*) posizione);

   XmStringFree(c_str);
   XtFree(str);
}
}
else
{
#if defined BACKTRACK
        get_something(lista,XmNitemCount, (void*) &totale);
        if(totale)
        for(k=1;k<=totale;k++,XmListDeletePos(lista,1));
        posizione=0;
        for (k=1;k<=_MAX_BACK_TRACK;k++)
           {
           ++posizione;
           sprintf(testo,"%3d  -  %s",
                           backtrack[k-1].prog,backtrack[k-1].descr);
           if(backtrack[k-1].stat==1)
                   sprintf(testo,"%s - %s - %s",
                           testo,backtrack[k-1].datasn,backtrack[k-1].temposn);
   	   str=(char*)XtMalloc(sizeof(char)*(strlen(testo)+20));
   	   strcpy(str,testo);
   	   c_str=XmStringCreate(str,XmSTRING_DEFAULT_CHARSET);
   	   XmListAddItemUnselected(lista,c_str,0);
   	   set_something(lista,XmNitemCount, (void*) posizione);

           XmStringFree(c_str);
           XtFree(str);
           }
#endif
}
}

void carica_lista_comp(lista,numero)
Widget lista;
int *numero;
{
#if defined BANCO_MANOVRA

int k,totale,i;
char testo[500];
XmString c_str;
char *str;
int posizione =0;

        get_something(lista,XmNitemCount, (void*) &totale);
        if(totale)
        for(k=1;k<=totale;k++,XmListDeletePos(lista,1));
        posizione=0;

                for (k=0; k<= lista_comp.punt_last; k++)
                        {
                        sprintf (testo,"%s",
                                lista_comp.descrizione[k]);

                        str=(char*)XtMalloc(sizeof(char)*(strlen(testo)+20));
         strcpy(str,testo);
         c_str=XmStringCreate(str,XmSTRING_DEFAULT_CHARSET);
         XmListAddItemUnselected(lista,c_str,0);
                        }
                *numero = lista_comp.punt_last+1;

#endif
}


void carica_backtrack(lista)
Widget lista;
{
#if defined BACKTRACK
int k,totale,i;
char testo[500];
char appoggio[10];
char *str;
XmString c_str;
int posizione =0;
int contatore_sessioni=0;
char flag[2];


printf ("carica_backtrack in esecuzione last_backtrack = %d\n",
                                                                last_backtrack);


        strcpy(flag,"*");

        get_something(lista,XmNitemCount, (void*) &totale);
        if(totale)
        for(k=1;k<=totale;k++,XmListDeletePos(lista,1));

        posizione=0;

                for (k=last_backtrack+1; ;k++)
                        {
                        if (k > _MAX_BACK_TRACK)
                                k = 1;
                        if(backtrack[k-1].stat==1)
                                {
                                ++posizione;
                                sessioni_bt[posizione-1]=contatore_sessioni;
                                punt_rec_backtrack[posizione] = k;
                                sprintf(appoggio,"%3d ",posizione);
                                strcat (appoggio,flag);
                sprintf(testo,"%s - %s - %s - %8.1f",
                                                       appoggio ,
                           backtrack[k-1].datasn,
                           backtrack[k-1].temposn,
                                               backtrack[k-1].tempo/1000);

            if (backtrack[k-1].forzato != 0)
                                                {
                                                contatore_sessioni++;
                  if (!strcmp(flag," "))
                     strcpy(flag,"*");
                  else
                     strcpy(flag," ");
                                                }

/*              printf ("testo = %sx\n",testo);
                printf ("posizione = %d \n",posizione);           */

         str=(char*)XtMalloc(sizeof(char)*(strlen(testo)+20));
         strcpy(str,testo);
         c_str=XmStringCreate(str,XmSTRING_DEFAULT_CHARSET);

/*         XmListAddItemUnselected(lista,c_str,0);      */
         XmListAddItemUnselected(lista,c_str,posizione);

         XmStringFree(c_str);
         free(str);

/*        set_something(lista,XmNitemCount, (void*) posizione);     */

                        if (k == last_backtrack)
                                {
                                num_bt_list=posizione;
                                XmListSelectPos(lista,posizione,TRUE);
                                XmListSetBottomPos(lista,posizione);
                                step_selezionato=posizione;
                                backtrack_selezionato=punt_rec_backtrack[posizione];
/*                              printf ("prima = %d last = %d\n",first_session_bt,
                                             last_session_bt);*/
printf ("numero sessioni = %d \n",contatore_sessioni);
                                break;
                                }
                                }
                        }

#endif

}

/*********************************************************************/
/*
 * visualizza il record selezionato al centro della lista
 */
void bt_al_centro()
{
#if defined BACKTRACK
int last_pos;
printf ("bt al centro\n");
        if ((step_selezionato > 7) &&
                 (step_selezionato < (num_bt_list-7)))
                {
                last_pos = step_selezionato+7;
                }
        else if (step_selezionato <= 7)
                        last_pos=15;
        else if (step_selezionato >= (num_bt_list-7))
                        last_pos = num_bt_list;

        XmListSetBottomPos(widget_array[k_caricamento_lista_bt],last_pos);
#endif
}
/*********************************************************************/
/*
 * setta i limiti di sessione (indice relativo a display 1/120)
 */
void limiti_sessione()
{
#if defined BACKTRACK
int i;
int basso;
int alto;
int riferimento;
XmString c_app_str;
char     app_str[20];

printf ("limiti: step selezionato %d\n",step_selezionato);

                riferimento = sessioni_bt[step_selezionato-1];

                for (i=0; i<step_selezionato; i++)
                        {
                        if (riferimento == sessioni_bt[i])
                                {
                                first_session_bt = i+1;
                                last_session_bt = first_session_bt;
                                break;
                                }
                        }
                for ( ; i<num_bt_list; i++)
                        {
                        if (riferimento != sessioni_bt[i])
                                {
                                last_session_bt = i;
                                break;
                                }
                        }

                if (i == num_bt_list)  /* era l' ultima sessione */
                        last_session_bt = num_bt_list;

                printf ("primo = %d ultimo = %d num_bt_list = %d i=%d\n",
                                        first_session_bt,last_session_bt,num_bt_list,i);
                sprintf (app_str,"%d - %d",first_session_bt,last_session_bt);
                c_app_str = XmStringCreateLtoR (app_str, XmSTRING_DEFAULT_CHARSET);
                set_something(widget_array[k_limiti_bt_val],
                                             XmNlabelString, (void*) c_app_str);
                XmStringFree (c_app_str);
#endif
}

/*********************************************************************/
void seleziona_backtrack(w, tag, reason)
    Widget w;
    int *tag;
    XmListCallbackStruct *reason;
{
#if defined BACKTRACK
static Widget attenzione=NULL;
Dialog_geometry geom;

        backtrack_selezionato=punt_rec_backtrack[reason->item_position];
        if((*tag==k_caricamento_lista_bt)&&
        (backtrack[backtrack_selezionato-1].mod==1))
                {
                geom.default_pos=1;
                geom.height=200;
                }
/*      step_selezionato=backtrack_selezionato;  */
                step_selezionato=reason->item_position;
        printf ("SELEZIONATO BT n. %d pos. %d\n",
                                        backtrack_selezionato,step_selezionato);
        limiti_sessione();
#endif
}

void override_allineamento(w, tag, reason)
        Widget w;
        int *tag;
        XmListCallbackStruct *reason;
{
#if defined BANCO_MANOVRA
        check_in_corso = 0;
printf ("override del check banco \n");
#endif
}
                                             
void seleziona_snapshot(w, tag, reason)
    Widget w;
    int *tag;
    XmListCallbackStruct *reason;
{
static Widget attenzione=NULL;
Dialog_geometry geom;

 snapshot_selezionato=reason->item_position;
 if((*tag==k_caricamento_lista)&&(snapshot[snapshot_selezionato-1].mod==1))
	{
	geom.default_pos=1;
	geom.height=200;
	if(attenzione==NULL)
		attenzione=attention(widget_array[k_caricamento_lista],
			"Warning snapshot from previous topology",
			CREA|MAPPA,geom);
	else
		attenzione=attention(widget_array[k_caricamento_lista],
			"Warning snapshot from previous topology",
			MAPPA,geom);
	}
}


void check_banco()
{
#if defined BANCO_MANOVRA
char app[30];
int ncomp;
XtIntervalId timer_allineamento;
static int finestra_fuori = 0;

         if (check_in_corso == 1)
            {
            if (SD_allinea(MONIT,(char*)&lista_comp) == NO_ALLINEA )
               {
               vis_messaggio ("Banco manovra non configurato",0);
               check_in_corso = 0;
               run_abilitato = 1;
               return;
               }
            else
               {
               vis_messaggio ("Banco manovra configurato",0);
               printf ("check_banco: ncomp = %d\n",lista_comp.punt_last);
/*
 * visualizzazione componenti disallineati
 */
               if ( (lista_comp.punt_last < 0) && /* nessun comp. disall. */
                    (finestra_fuori == 0) )        /* non liste precedenti */
                   {
                   check_in_corso = 0;
                   run_abilitato = 1;
                   return;
                   }
               sprintf(app,"allineamento_dialog");
               dialog_proc((Widget)k_allineamento_dialog,(int*)app);
               carica_lista_comp(widget_array[k_caricamento_lista_comp],&ncomp);
                                 finestra_fuori = 1;
               }
            }

        timer_allineamento = XtAppAddTimeOut (XtWidgetToApplicationContext
                                              (main_window_widget),
                                              (unsigned long) TM_REFRESH*5,
                                              check_banco, NULL);

        if ((ncomp == 0) || (check_in_corso == 0))
           {
           run_abilitato = 1;
           check_in_corso = 0;
           finestra_fuori = 0;
           XtRemoveTimeOut (timer_allineamento);
           XtUnmanageChild(widget_array[k_allineamento_dialog]);
           }
#endif
}


void snapshot_activate(w, tag, reason)
    Widget w;
    int *tag;
    unsigned long *reason;
{
int widget_num = *tag;
int posizione;
int k,i;
char *testo_p;
char app[200];
char app_1[200];
SNTAB snapshot_sked;
MSG_SKDIS messaggio;
SNTAB app_snap;
char prova[30];
//static char qq='A';
int ret;


switch (widget_num)
       {
       case k_caricamento_ok:
          {
          if(val_agg.stato_sked!=STATO_BACKTRACK)
             {
             snapshot_sked.prog=snapshot_selezionato;
/*           Verifica che  sia stato selezionato uno snapshot valido */
             if(snapshot[snapshot_selezionato-1].stat==1)
                {
                memcpy(app,&snapshot_sked,sizeof(SNTAB));
                vis_messaggio("Command LOAD I.C. send",0);
                def_cursore (toplevel_widget, OROLOGIO);
#if defined MFFR
                if( (ret=SD_loadic(MONIT,&snapshot_selezionato,&sommari)) >0 )
                   {
                   if (snap_to_sommari() < 0)
                      vis_messaggio("CI: sommari non validi",0);
#else
                if( (ret=SD_loadic(MONIT,&snapshot_selezionato,NULL)) >0 ) 
                   {
#endif
                   vis_messaggio("Acknowledge LOAD I.C. received",0);
                   if ( ret==NUOVA_CI )
                      BacktrackImmediato = 1;
                   }  /* Chiude le due parentesi aperte */
                else
                   vis_messaggio("Error Acknowledge LOAD I.C. not received",1);

#if defined BANCO_MANOVRA
                check_in_corso = 1;
                run_abilitato = 0;
                check_banco();
/*              triggera next backtrack */
                intervallo_backtrack = 0.;
#endif
                undef_cursore (toplevel_widget);
                XtUnmanageChild(widget_array[k_caricamento_dialog]);
		}   /* Chiude if su stat */
             } /* Chiude if su STATO diverso da BACKTRACK */
          break;
          }    /* Chiude case */
       case k_caricamento_annulla:
		{
                XtUnmanageChild(widget_array[k_caricamento_dialog]);
                break;
		}
       case k_editing_fine:
		{
                XtUnmanageChild(widget_array[k_editing_dialog]);
                break;
		}
       case k_editing_modify:
		{
		snapshot_sked.prog=snapshot_selezionato;
		/* verifica che sia stato selezionato uno snapshot valido */
		if(snapshot[snapshot_selezionato-1].stat==1)
		{
		  memcpy(app,&snapshot_sked,sizeof(SNTAB));
		  vis_messaggio("Command LOAD I.C. send",0);
		  def_cursore (toplevel_widget, OROLOGIO);
		  if(SD_modic(MONIT,&snapshot_selezionato,"QQQQQqqqqq")>0)
			 vis_messaggio("Acknowledge MODIFY DESCRIPTION received",0);
		  else
			 vis_messaggio("Error Acknowledge MODIFY DESCRIPTION not received",1);
		  undef_cursore (toplevel_widget);
                }
                XtUnmanageChild(widget_array[k_editing_dialog]);
                break;
		}
       case k_scrittura_ok:
		{
                testo_p=XmTextGetString
                    (widget_array[k_scrittura_text]);
		strcpy(snapshot_sked.descr,testo_p);
		snapshot_sked.prog=0;
		memcpy(app,&snapshot_sked,sizeof(SNTAB));
		vis_messaggio("Command SAVE I.C. send",0);
		def_cursore (toplevel_widget, OROLOGIO);
		i=0;
#if defined MFFR
		sommari_to_snap();
		if(SD_saveic(MONIT,&i,testo_p,(char*)&sommari)>0)
#else
		if(SD_saveic(MONIT,&i,testo_p,NULL)>0)
#endif
			vis_messaggio("Acknowledge SAVE I.C. received",0);
		else
			vis_messaggio("Error Acknowledge SAVE I.C. not received",1);
		XtUnmanageChild(widget_array[k_scrittura_dialog]);
		if(UtStatoWidget(widget_array[k_editing_dialog])==MAPPA)
		  {
		  tab_snapshot();
                  elenca_snapshot(widget_array[k_editing_lista]);
		  }
		undef_cursore (toplevel_widget);
                break;
		}
       case k_scrittura_annulla:
		{
		XtUnmanageChild(widget_array[k_scrittura_dialog]);
                break;
		}
       case k_editing_cancella:
		{
		/* verifica che sia stato selezionato uno snapshot valido */
		if(snapshot[snapshot_selezionato-1].stat==1)
		{
		  vis_messaggio("Command REMOVE I.C. send",0);
		  snapshot_sked.prog=snapshot_selezionato;
		  memcpy(app_1,&snapshot_sked,sizeof(SNTAB));
		   def_cursore (toplevel_widget, OROLOGIO);
		  if(SD_removeic(MONIT,&snapshot_selezionato)>0)
			vis_messaggio("Acknowledge REMOVE I.C. received",0);
		  else
                        vis_messaggio("Error Acknowledge REMOVE I.C. not received",1);
		  if(UtStatoWidget(widget_array[k_editing_dialog])==MAPPA)
		    {
		    tab_snapshot();
                    elenca_snapshot(widget_array[k_editing_lista]);
		    }
		undef_cursore (toplevel_widget);
		}
		break;
		}
	}
}

void backtrack_activate(w, tag, reason)
    Widget w;
    int *tag;
    unsigned long *reason;
{
#if defined BACKTRACK
int widget_num = *tag;
int posizione;
int k,i;
char *testo_p;
char app[200];
char app_1[200];
BKTAB backtrack_sked;
SNTAB snapshot_sked;
MSG_SKDIS messaggio;
SNTAB app_snap;
char prova[30];
// static qq='A';
int stato;
int ret;


switch (widget_num){
       case k_step_bt:
            {
            XmListSelectPos(widget_array[k_caricamento_lista_bt],
                            step_selezionato, TRUE);
            bt_al_centro();
            limiti_sessione();
            backtrack_sked.prog=backtrack_selezionato;
/*          Verifica che sia stato selezionato un backtrack valido */
            if(backtrack[backtrack_selezionato-1].stat==1)
               {
               vis_messaggio("Command LOAD B.T. send",0);
               def_cursore (toplevel_widget, OROLOGIO);
#if defined MFFR
               if( SD_loadbt(MONIT,&backtrack_selezionato,&sommari)>0 )
#else
               if( SD_loadbt(MONIT,&backtrack_selezionato,NULL)>0 )
#endif
                  {
#if defined MFFR
                  if (snap_to_sommari() < 0)
                     vis_messaggio("BT: sommari non validi",0);
#endif
                  last_load_bt=step_selezionato;
                  vis_messaggio("Acknowledge LOAD B.T. received",0);
                  }
               else
                  vis_messaggio("Error Acknowledge LOAD B.T. not received",1);
               undef_cursore (toplevel_widget);
               }
            prossimo_step();
            break;
            }
       case k_restart_bt:
            {
/*
 * 1) validazione della banca dati attuale
 * 2) cambio di stato
 */
            if (modo_bt != BT_MANUALE)
               break;
            def_cursore (main_window_widget, OROLOGIO);

/*          Manda il comando di validazione del backtrack */
            if( (ret=SD_validatebt (MONIT)) >0 )
                vis_messaggio ("Command VALIDATE BT send",0);
            else
                vis_messaggio ("Error acknowledge VALIDATE BT not received",1);

            if ( ret==NUOVA_CI )
                 BacktrackImmediato = 1;

/*          Manda il comando di freeze allo sked */
            if( SD_freeze (MONIT)>0 )
                vis_messaggio ("Command FREEZE send",0);
            else
                vis_messaggio ("Error acknowledge FREEZE not received",1);

/*          Triggera il prossimo backtrack */
            intervallo_backtrack = 0.;

            undef_cursore (main_window_widget);
            XtUnmanageChild(widget_array[k_backtrack_dialog]);

/*          Controllo allineamento componenti BM */
            check_in_corso = 1;
            run_abilitato = 0;
            check_banco();
            break;
            }
       case k_reset_bt:
            {
/*
 * ATTENZIONE LA SEQUENZA CORRETTA E' CAMBIATA :
 * si esce da backtrack per ritornare alla situazione di partenza
 * 1) cambio di stato
 * 2) ricarica la ci 60
 * 3) triggera prossimo backtrack
 */
            if (modo_bt != BT_MANUALE)
               break;
            def_cursore (main_window_widget, OROLOGIO);
/* 
 * cambio di stato
 */
            if(SD_freeze (MONIT)>0)
                vis_messaggio ("Command FREEZE send",0);
            else
                vis_messaggio ("Error acknowledge FREEZE not received",1);

/*
 * ricarica la ci 60
 */
            tab_snapshot();   /* carica i descrittori */
            snapshot_sked.prog=_MAX_SNAP_SHOT;
            if( snapshot[snapshot_sked.prog-1].stat==1)
               {
               vis_messaggio("Command LOAD I.C. send",0);
               def_cursore (toplevel_widget, OROLOGIO);
#if defined MFFR
               if( SD_loadic(MONIT,&snapshot_sked.prog,&sommari)>0)
                  {
                  if (snap_to_sommari() < 0)
                     vis_messaggio("CI: sommari non validi",0);
#else
               if( SD_loadic(MONIT,&snapshot_sked.prog,NULL)>0)
                  {
#endif
                  vis_messaggio("Acknowledge LOAD AUTOSNAP received",0);
                  }  /* Chiude gli if in MFFR */
               else
                  vis_messaggio("Error Acknowledge LOAD I.C. not received",1);
               }
            undef_cursore (toplevel_widget);
            undef_cursore (main_window_widget);
            XtUnmanageChild(widget_array[k_backtrack_dialog]);

/*
 * controllo allineamento componenti BM
 */
            check_in_corso = 1;
            run_abilitato = 0;
            check_banco();

            break;
            }

       case k_bt_indietro:
            if (direzione_bt == BT_INDIETRO)
               break;
            bt_indietro();
            break;

       case k_bt_avanti:
            if (direzione_bt == BT_AVANTI)
               break;
            bt_avanti();
            break;

       case k_bt_automatico:
            if (modo_bt == BT_AUTOMATICO)
               break;
            if (step_selezionato == num_bt_list)
               bt_indietro();
            else if (step_selezionato == 1)
               bt_avanti();
            if (last_backtrack != 1)      /* almeno 2 records */
               bt_in_automatico();
            timer_auto_bt=0;
            old_time_bt=tempo.time;
            break;

       case k_bt_manuale:
            {
            if (modo_bt == BT_MANUALE)
                        break;
            bt_in_manuale();
            break;
            }
       default:
            break;
}
#endif
}

int bt_indietro()
{
#if defined BACKTRACK
int stato;
printf ("direzione indietro\n");
        direzione_bt=BT_INDIETRO;
            stato = False;
            set_something (widget_array[k_bt_indietro], XmNsensitive, (void*) stato);
            stato = True;
            set_something (widget_array[k_bt_avanti], XmNsensitive, (void*) stato);
            prossimo_step();
        return(0);
#endif
}



int bt_avanti()
{
#if defined BACKTRACK
int stato;
printf ("direzione avanti\n");
        direzione_bt=BT_AVANTI;
            stato = True;
            set_something (widget_array[k_bt_indietro], XmNsensitive, (void*) stato);
            stato = False;
            set_something (widget_array[k_bt_avanti], XmNsensitive, (void*) stato);
            prossimo_step();
        return(0);
#endif
}


int bt_in_manuale()
{
#if defined BACKTRACK
int stato;
                 modo_bt=BT_MANUALE;
         stato = False;
            set_something (widget_array[k_bt_manuale], XmNsensitive, (void*) stato);
            stato = True;
            set_something (widget_array[k_bt_automatico], XmNsensitive, (void*) stato);
                                return(0);
#endif
}


int bt_in_automatico()
{
#if defined BACKTRACK
int stato;
                modo_bt=BT_AUTOMATICO;
            stato = True;
            set_something (widget_array[k_bt_manuale], XmNsensitive, (void*) stato);
            stato = False;
            set_something (widget_array[k_bt_automatico], XmNsensitive, (void*) stato);
                                return(0);
#endif
}


int prossimo_step()
{
#if defined BACKTRACK
                if (num_bt_list == 1)
                        return(0);           /* un solo step registrato */

      switch (direzione_bt)
         {
         case BT_INDIETRO:
            if (step_selezionato == 1)
                                        bt_avanti();
            else
               step_selezionato--;
            break;

         case BT_AVANTI:
            if (step_selezionato == num_bt_list)
                                        bt_indietro();
            else
               step_selezionato++;

            break;
         }
          return(0);
#endif
}


void prepara_lista()
{
#if defined BACKTRACK
int i;
        for (i=0; i<6; i++)
                {
                strcpy(lista_comp.sigla[i],"12345678");
                strcpy(lista_comp.descrizione[i],"descrizione 34567890123456789012345678901234567890123456789012345678x");
                strcpy(lista_comp.coordinate[i],"coord 8901234567890123x");
                strcpy(lista_comp.val_att[i],"att 567890");
                strcpy(lista_comp.val_ci[i],"ci 4567890");
                lista_comp.punt_last=i;
                }
#endif
}
                                      
