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
   modulo monit_var_malf.c
   tipo 
   release 5.4
   data 2/19/96
   reserved @(#)monit_var_malf.c	5.4
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)monit_var_malf.c	5.4\t2/19/96";
/*
        Fine sezione per SCCS
*/
#if defined MFFR
# include <stdio.h>
# include <math.h>
# include <string.h>
#if defined UNIX
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/msg.h>
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
# include <Xm/ScrolledW.h>
# include <Xm/List.h>
# include <Xm/Label.h>
# include <Xm/Text.h>
# include <Xm/Frame.h>
# include <Xm/ToggleB.h>
# include <Xm/PushB.h>
# include <Xm/PushBG.h>
# include <Xm/RowColumn.h>
# include <Xm/Form.h>
# include <Xm/Xm.h>
# include <Xm/ArrowB.h>
# include "monit.h"
# include "monituil.h"
# include "libutilx.h"
# include "sked.h"
# include "dispatcher.h"
# include "agg_manovra.h"

#include "monit_mffr.h"
# include <Rt/RtMemory.h>

char   *nome_modello (char *, int);

int carica_dati_malf();
int titolo();
int tasti_comando();
static int leggi_riga(FILE *, char *);
int estrai_dati (char *, char *, char *);
int inserisci_sistema (Widget , int );
int presa_dati(int );
int next_down(int );
int test_sistema (char *);
int leggi_dati(int  , int );

extern SOMMARIO_MF sommario_mf;

int sistema_selezionato;   /* sistema scelto 0/n  */
int variabile_selezionata;  /* variabile scelta 0/n */

extern char *ind_sh_top;   /* puntatore inizio shared memory sh_var */
extern VARIABILI *variabili;  /* database delle variabili  */
extern int tot_variabili;  /* numero totale delle variabili      */
extern VALORI_AGG val_agg;

struct malf_st
	{
	char label[MAX_LUN_NOME_VAR];
	char descr[MAX_LUN_DESCR_VAR];
	int addr;
	};
typedef struct malf_st MALF;

struct listamf_sist_st
	{
	int nvar;                  /* numero malfunzioni del sistema       */
	MALF malf[MAX_MALF_SIST];  /* dati delle malfunzioni               */
	};
typedef struct listamf_sist_st LISTA_MF;
LISTA_MF *lista_mf;

struct lista_sist_mf_st
	{
	int nsist;                  /* numero sistemi che hanno mf o fr     */
	char sigla[MAX_MODEL][MAX_LUNGH_SIGLA]; /* sigla contenuta nelle variabili*/
	char descrizione[MAX_MODEL] [MAX_LUN_DESCR_VAR];/*descrizione modello */
	};
typedef struct lista_sist_mf_st LISTA_SIST;
LISTA_SIST lista_sist;         /* struttura contenente la lista dei sistemi */

struct find_malf_st
	{
	int n;                      /* numero di match nella lista               */
	int pos[MAX_MALF_SIST];     /* array dei match position 0 - n-1          */
	};
typedef struct find_malf_st FIND_MALF;
FIND_MALF find_malf;

int numero_match;               /* numero di elementi trovati in lista */
int *array_found;               /* elenco items trovati                */

extern struct timeb tempo;      /* tempo di orologio            */
extern Widget widget_array[MAX_WIDGETS];
extern Widget main_window_widget;
extern Widget toplevel_widget; 

extern Widget toggle_w[MAX_MF_SOMM];
extern Widget label_w[MAX_MF_SOMM];
extern Widget descrizione_w[MAX_MF_SOMM];
extern Widget val_default_w[MAX_MF_SOMM];
extern Widget delay_w[MAX_MF_SOMM];
extern Widget durata_w[MAX_MF_SOMM];
extern Widget rampa_w[MAX_MF_SOMM];
extern Widget val_fin_w[MAX_MF_SOMM];
extern Widget val_att_w[MAX_MF_SOMM];
extern Widget stato_mf_w[MAX_MF_SOMM];
/* ****************  procedure inserite  ************************ */

void select_malf_proc(); /* procedura che attiva il colloquio malfunzioni    */
void ricerca_volo_var(); /*ricerca (ad ogni variazione di carattere) di una
													 stringa nella lista   */
void cerca_tutte_var(); /* effettua la ricerca di una stringa nella lista   */
void ricerca_var();      /* posiziona sulla prossima stringa                */
void exit_ricerca();     /* termina l' attuale colloquio */
void inserisci_somm();   /* inserisce la mf selezionata in sommario       */
void seleziona_sistema_mf(); /* seleziona un sistema mf ed estrae le var. */
void seleziona_var_mf(); /* seleziona una variabile da lista        */
int next_up(int p);



extern float leggi_valore(int p);
extern Widget PostDialog();
extern Widget malf_shell;
/********************************************************************/
/*
 * definizioni malfunzioni
 */
Widget select_malf_shell;
Widget form_principale, frame_principale;
Widget form_titolo, frame_titolo;
Widget form_sistemi, frame_sistemi, lista_scroll_sistemi;
Widget form_variabili, frame_variabili, lista_scroll_variabili;
Widget form_selezione, variabile_w, bottone_su, bottone_giu;
Widget form_tasti_comando;
Widget frame_tasto_ok, tasto_ok, frame_tasto_exit, tasto_xit;
/********************************************************************/
static  int attivato = 0;
int selez_malf_attivo = 0;
extern int selez_frem_attivo;
/***************************************************************************/
/***************************************************************************/
/*
 * specifiche fonts
 */
extern XmFontList  fontlist_mffr;
/****************************************************************************/
void select_malf_proc(w, tag, reason)
    Widget w;
    int *tag;
    XmListCallbackStruct *reason;
{
int     widget_num = *tag;
int i;
char app_char[200];

      def_cursore (toplevel_widget, OROLOGIO);
      vis_messaggio("Attivazione selezione malf",0);
                                                   
		if (attivato)
			{
			XtManageChild (select_malf_shell);
			undef_cursore (toplevel_widget);
			return;
			}


      select_malf_shell = XtVaCreateManagedWidget (NULL,
      				topLevelShellWidgetClass,toplevel_widget, 
						XmNallowShellResize       , False,
						XmNiconName               , "Selezione malfunzioni",
/*						XmNiconic                 , True,            */
                  XmNx                   ,  200,
                  XmNy                   ,  300,
						XmNmaxWidth            ,  700,
						XmNminWidth            ,  700,
						XmNminHeight           ,  550,
                  XmNbackground             , colore_sfondo,
						XmNfontList               , fontlist_mffr,
						NULL);
						
      form_principale = XtVaCreateManagedWidget (NULL,
                  xmFormWidgetClass, select_malf_shell,
                  XmNbackground             , colore_sfondo,
						XmNfontList               , fontlist_mffr,
                  NULL);
		frame_principale = XtVaCreateManagedWidget (NULL,
                  xmFrameWidgetClass     ,  form_principale,
                  XmNwidth               ,  700,
                  XmNheight              ,  550,
						XmNbottomAttachment    ,  XmATTACH_FORM,
						XmNtopAttachment       ,  XmATTACH_FORM,
						XmNleftAttachment      ,  XmATTACH_FORM,
						XmNrightAttachment     ,  XmATTACH_FORM,
                  XmNbackground             , colore_sfondo,
						XmNfontList               , fontlist_mffr,
                  NULL);

		carica_dati_malf();
		titolo();
		lista_sistemi();   
		lista_variabili(); 
		selezione_variabile();
		tasti_comando();

		undef_cursore (toplevel_widget);

		XmListSelectPos(lista_scroll_sistemi, 1, TRUE);
		attivato = 1;
		selez_malf_attivo = 1;

		if (sommario_mf.numero >= MAX_MF_SOMM)
      	tasto_bloccato(tasto_ok,"MF");

}
/***************************************************************/
int titolo()
{
      frame_titolo = XtVaCreateManagedWidget ("Selezione Malfunzioni",
                  xmFrameWidgetClass     ,  form_principale,
                  XmNwidth               ,  700,
                  XmNheight              ,  30,
                  XmNtopAttachment       ,  XmATTACH_FORM,
                  XmNleftAttachment      ,  XmATTACH_FORM,
                  XmNrightAttachment     ,  XmATTACH_FORM,
						XmNfontList               , fontlist_mffr,
                  NULL);
      XtVaCreateManagedWidget (NULL,
                  xmLabelWidgetClass     ,  frame_titolo,
                  XmNlabelString         ,  XmStringCreateLtoR
                                             ("Selezione Malfunzioni",
                                             XmSTRING_DEFAULT_CHARSET),
                  XmNbackground          ,  pix_val[0],
						XmNfontList               , fontlist_mffr,
                  NULL);
		return(0);
}
/***************************************************************/
int lista_sistemi()
{
int i;
char app_char[100];
Widget vert_scr_w;

      form_sistemi  = XtVaCreateManagedWidget (NULL,
                  xmFormWidgetClass, form_principale,
                  XmNwidth               ,  500,
                  XmNheight              ,  100,
                  XmNtopAttachment       ,  XmATTACH_FORM,
                  XmNtopOffset           ,  50,
                  XmNrightAttachment     ,  XmATTACH_FORM,
                  XmNrightOffset         ,  200,
                  XmNleftAttachment      ,  XmATTACH_FORM,
						XmNleftOffset          ,  50,
						XmNfontList               , fontlist_mffr,
                  NULL);
      frame_sistemi = XtVaCreateManagedWidget (NULL,
                  xmFrameWidgetClass     ,  form_sistemi,
                  XmNwidth               ,  500,
                  XmNheight              ,  100,
                  XmNtopAttachment       ,  XmATTACH_FORM,
                  XmNrightAttachment     ,  XmATTACH_FORM,
                  XmNleftAttachment      ,  XmATTACH_FORM,
						XmNfontList               , fontlist_mffr,
                  NULL);
      lista_scroll_sistemi =  XmCreateScrolledList (form_sistemi,
                  "lista_sistemi",NULL, 0);

      XtManageChild (lista_scroll_sistemi);

      XtVaSetValues (lista_scroll_sistemi,
                  XmNselectionPolicy        , XmSINGLE_SELECT,
                  XmNwidth                  ,  500,
                  XmNvisibleItemCount       , 5,
                  XmNbackground          ,  colore_tabelle,
						XmNfontList               , fontlist_mffr,
                  NULL);
      XtVaSetValues (XtParent(lista_scroll_sistemi),
                  XmNwidth                  ,  500,  
						XmNheight                 , 100,
                  XmNrightAttachment        , XmATTACH_WIDGET,
                  XmNrightWidget             , form_sistemi,
                  XmNbackground             , colore_tabelle,
                  NULL);

		XtVaGetValues (XtParent(lista_scroll_sistemi),
						XmNverticalScrollBar, &vert_scr_w, NULL);
		XtVaSetValues (vert_scr_w, 
						XmNtroughColor, colore_scrollbar, 
						XmNbackground , colore_tabelle,
						NULL);

		XtAddCallback (lista_scroll_sistemi, 
							XmNsingleSelectionCallback,
							seleziona_sistema_mf,NULL);
		XtAddCallback (lista_scroll_sistemi,
                     XmNsingleSelectionCallback,
							cerca_tutte_var, NULL);

		for (i=0; i<lista_sist.nsist; i++)
			{
			sprintf(app_char,"%s     %s",
						lista_sist.sigla[i],
						lista_sist.descrizione[i]);
			XmListAddItemUnselected(lista_scroll_sistemi,
                  XmStringCreate(app_char,XmSTRING_DEFAULT_CHARSET),
                  0);
			}

		return(0);
}
/*******************************************************************/
int elenco_sistemi()
{
FILE *fp;
char app_char[100];

	if ((fp = fopen (file_elenco_sistemi,"r")) == NULL)
		{
		sprintf (app_char,"%s: %s\n %s",
					file_elenco_sistemi,
					FILE_NOT_FOUND,
					NIENTE_SISTEMI);
		PostDialog(malf_shell, XmDIALOG_WARNING, app_char);
		return(-1);
		}
	leggi_riga(fp,app_char);
	leggi_riga(fp,app_char);
	leggi_riga(fp,app_char);
	leggi_riga(fp,app_char);
	
	lista_sist.nsist=0;

	while (leggi_riga (fp,app_char) >= 0) 
		{
		estrai_dati(app_char,
							lista_sist.sigla[lista_sist.nsist],
							lista_sist.descrizione[lista_sist.nsist]);
		lista_sist.nsist++;
		}

	fclose(fp);
	return (lista_sist.nsist);
}
/*******************************************************************/
int estrai_dati (char *s, char *sigla, char *descr)
{
int i,j;
/*
 * estrae la sigla
 */
	i = 0;
	j = 0;
	while (s[i] != ' ')	
		{
		sigla[j] = s[i];
		i++;
		j++;
		}
	sigla[i] = '\0';

/*
 * salta i blank in testa
 */
	while (s[i] == ' ')
		i++;
/*
 * estrae la descrizione
 */
	j = 0;
	while (s[i] != '\0')
		{
		descr[j] = s[i];
		i++;
		j++;
		}	
	descr[j] = s[i];

	return (0);
}
/*******************************************************************/
int leggi_riga(fp, stringa)
FILE *fp;
char *stringa;
{
int i;
int c;

		i = 0;
		while ((c = getc(fp)) != EOF)
			{
			stringa[i] = c;
			if (stringa[i] == '\n')
				{
				stringa[i] = '\0';
				return(i);
				}
			i++;
			}
		return(-1);

}
/*******************************************************************/
int lista_variabili()
{
int i;
char app_char[100];
Widget vert_scr_w;

      form_variabili  = XtVaCreateManagedWidget (NULL,
                  xmFormWidgetClass, form_principale,
                  XmNwidth               ,  600,
						XmNheight              ,  100,
                  XmNbottomAttachment    ,  XmATTACH_FORM,
                  XmNbottomOffset        ,  170,
                  XmNtopAttachment       ,  XmATTACH_WIDGET,
                  XmNtopWidget           ,  form_sistemi,
						XmNtopOffset           ,  50,
                  XmNrightAttachment     ,  XmATTACH_FORM,
                  XmNrightOffset         ,  50,
                  XmNleftAttachment      ,  XmATTACH_FORM,
                  XmNleftOffset          ,  50,         
						XmNfontList               , fontlist_mffr,
                  NULL);
      frame_variabili = XtVaCreateManagedWidget (NULL,
                  xmFrameWidgetClass     ,  form_variabili,
                  XmNwidth               ,  600,
						XmNbottomAttachment    ,  XmATTACH_FORM,
                  XmNtopAttachment       ,  XmATTACH_FORM,
                  XmNrightAttachment     ,  XmATTACH_FORM,
                  XmNleftAttachment      ,  XmATTACH_FORM,
						XmNfontList               , fontlist_mffr,
                  NULL);
      lista_scroll_variabili =  XmCreateScrolledList (form_variabili,
						"lista_variabili",NULL ,0);

      XtVaSetValues (lista_scroll_variabili,
                  XmNselectionPolicy        , XmSINGLE_SELECT,
                  XmNwidth                  ,  600,
                  XmNbackground          ,  colore_tabelle,
						XmNfontList               , fontlist_mffr,
                  NULL);
      XtVaSetValues (XtParent(lista_scroll_variabili),
						XmNwidth                  ,  600,
                  XmNrightAttachment        , XmATTACH_WIDGET,
                  XmNrightWidget             , form_variabili,
						XmNbottomAttachment        , XmATTACH_WIDGET,
                  XmNbottomWidget             , form_variabili,
						XmNbackground          ,  colore_tabelle,
                  NULL);

      XtVaGetValues (XtParent(lista_scroll_variabili),
                  XmNverticalScrollBar, &vert_scr_w, NULL);
      XtVaSetValues (vert_scr_w,
                  XmNtroughColor, colore_scrollbar,
                  XmNbackground , colore_tabelle,
                  NULL);
      XtAddCallback (lista_scroll_variabili,
                     XmNsingleSelectionCallback,
                     seleziona_var_mf,NULL);

      XtManageChild (lista_scroll_variabili);
	return(0);
}
/*******************************************************************/
int selezione_variabile()
{

		form_selezione = XtVaCreateManagedWidget (NULL,
                  xmFormWidgetClass, form_principale,
                  XmNtopAttachment , XmATTACH_WIDGET,
                  XmNtopWidget     , form_variabili,
                  XmNtopOffset     , 30,
                  XmNleftAttachment  , XmATTACH_FORM,
                  XmNleftOffset     ,  150,
                  XmNbackground        , colore_sfondo,
						XmNfontList               , fontlist_mffr,
                  NULL);
                    
		bottone_su = XtVaCreateManagedWidget (NULL,
                  xmArrowButtonWidgetClass, form_selezione,
                  XmNleftAttachment      , XmATTACH_FORM,
                  XmNarrowDirection       , XmARROW_UP,
						XmNheight               , 30,
						XmNwidth                , 80,
                  XmNbackground        , colore_tasti,
						XmNfontList               , fontlist_mffr,
                  NULL);

		variabile_w = XtVaCreateManagedWidget ("label",
                  xmTextWidgetClass,   form_selezione,
                  XmNcolumns      ,    20,
                  XmNleftAttachment,    XmATTACH_WIDGET,
						XmNleftWidget    ,    bottone_su,
						XmNleftOffset    ,    20,
                  XmNcursorPositionVisible, True,
                  XmNvalue      ,      "selezione",
						XmNheight               , 30,
                  XmNbackground        , colore_tabelle,
						XmNfontList               , fontlist_mffr,
                  NULL);

		bottone_giu = XtVaCreateManagedWidget (NULL,
						xmArrowButtonWidgetClass, form_selezione,
						XmNleftAttachment      , XmATTACH_WIDGET,
						XmNleftWidget          , variabile_w,
						XmNleftOffset          , 20,
						XmNarrowDirection       , XmARROW_DOWN,
						XmNheight               , 30,
						XmNwidth                , 80,
                  XmNbackground        , colore_tasti,
						XmNfontList               , fontlist_mffr,
						NULL);

		XtVaSetValues (form_principale, XmNdefaultButton, bottone_giu, NULL);
		XtVaSetValues (bottone_giu, XmNshowAsDefault , 1, NULL);

/*		XtAddCallback (variabile_w, 
							XmNvalueChangedCallback, ricerca_volo_var, NULL);  */

		XtAddCallback (variabile_w, XmNactivateCallback, cerca_tutte_var, NULL);
		XtAddCallback(bottone_su,XmNactivateCallback, ricerca_var, direzione_up);
		XtAddCallback(bottone_giu,XmNactivateCallback,ricerca_var,direzione_down);

}
/*******************************************************************/
int tasti_comando()
{
Widget frame_tasti;

      form_tasti_comando = XtVaCreateManagedWidget ("form_tasti_comando",
                  xmFormWidgetClass, form_principale,
                  XmNtopAttachment , XmATTACH_WIDGET,
                  XmNtopWidget     , form_selezione,
                  XmNtopOffset     , 10,
                  XmNleftAttachment  , XmATTACH_FORM,
						XmNleftOffset          ,   10,
						XmNrightAttachment  , XmATTACH_FORM,
						XmNrightOffset          ,  10,
						XmNbottomAttachment , XmATTACH_FORM,
						XmNbottomOffset        ,  20,
                  XmNbackground        , colore_sfondo,
						XmNfontList               , fontlist_mffr,
                  NULL);
		frame_tasti = XtVaCreateManagedWidget ("frame_tasti_comando",
                  xmFrameWidgetClass     ,  form_tasti_comando,
						XmNleftAttachment  , XmATTACH_FORM,
                  XmNrightAttachment  , XmATTACH_FORM,
                  XmNheight              ,  70,
                  XmNbackground        , colore_sfondo,
						XmNfontList               , fontlist_mffr,
                  NULL);

		frame_tasto_ok = XtVaCreateManagedWidget ("frame_ok",
                  xmFrameWidgetClass     ,  form_tasti_comando,
                  XmNwidth               ,  120,
                  XmNheight              ,  30,
                  XmNleftAttachment      ,  XmATTACH_FORM,
                  XmNleftOffset          ,  20,
                  XmNbottomAttachment    ,  XmATTACH_FORM,
                  XmNbottomOffset        ,  20,
                  XmNbackground      , colore_tasti,
						XmNfontList               , fontlist_mffr,
                  NULL);
		tasto_ok      = XtVaCreateManagedWidget ("tasto_ok",
						xmPushButtonWidgetClass , frame_tasto_ok,
                  XmNlabelString         , XmStringCreateLtoR ("CONFERMA",
                                                XmSTRING_DEFAULT_CHARSET),
                  XmNwidth               , 120,
                  XmNheight              , 30,
                  XmNdefaultButtonShadowThickness ,  1,
						XmNbackground      , colore_tasti,
						XmNfontList               , fontlist_mffr,
                  NULL);

      frame_tasto_exit = XtVaCreateManagedWidget ("frame_exit",
                  xmFrameWidgetClass     ,  form_tasti_comando,
                  XmNwidth               ,  120,
                  XmNheight              ,  30,
                  XmNrightAttachment      ,  XmATTACH_FORM,
                  XmNrightOffset          ,  20,
                  XmNbottomAttachment    ,  XmATTACH_FORM,
                  XmNbottomOffset        ,  20,
                  XmNbackground      , colore_tasti,
						XmNfontList               , fontlist_mffr,
                  NULL);
		tasto_xit  = XtVaCreateManagedWidget ("tasto_exit",
                  xmPushButtonWidgetClass , frame_tasto_exit,
                  XmNlabelString         , XmStringCreateLtoR ("USCITA",
                                                XmSTRING_DEFAULT_CHARSET),
                  XmNwidth               , 120,
                  XmNheight              , 30,
                  XmNdefaultButtonShadowThickness ,  2,
						XmNbackground      , colore_tasti,
						XmNfontList               , fontlist_mffr,
                  NULL);
/*
 * callback relative ai tasti
 */
		XtAddCallback (tasto_xit, XmNactivateCallback, exit_ricerca, NULL);
		XtAddCallback (tasto_ok, XmNactivateCallback, inserisci_somm, NULL);
}
/*******************************************************************/
void ricerca_volo_var(w, tag, reason)
    Widget w;
    char *tag;
    XmAnyCallbackStruct *reason;
{
char *stringa;

	stringa = XmTextGetString (w);
   printf ("ricerca con :%s:\n",stringa);
   XtFree (stringa);
}
/*******************************************************************/
void cerca_tutte_var(w, tag, reason)
    Widget w;
    char *tag;
    XmAnyCallbackStruct *reason;
{
char *stringa;
XmString str;
LISTA_MF *l_mf;
int i;
int ntot;

  stringa = XmTextGetString (variabile_w);
/*   printf ("activate:ricerca con :%s:\n",stringa); */
	find_malf.n = 0;       /* reset precedente array                */
	l_mf = lista_mf + sistema_selezionato;
	ntot = l_mf->nvar;
	for (i=0; i<ntot; i++)
		{
		if ((Utstrstr(l_mf->malf[i].label, stringa) != NULL) ||
			 (Utstrstr(l_mf->malf[i].descr, stringa) != NULL))
			{
			find_malf.pos[find_malf.n] = i;
			find_malf.n++;
/*			printf ("trovato %s a riga %d\n",stringa,i); */
			}
		}
   XtFree (stringa);
}
/*******************************************************************/
void ricerca_var(w, tag, reason)
    Widget w;
    XtPointer *tag;
    XmArrowButtonCallbackStruct *reason;
{
int pos,next_pos;
int i;

	pos = variabile_selezionata;

	if (find_malf.n > 0)
		{
		if (!strcmp((char*)tag,"UP"))
			{
			next_pos = next_up(pos);
/*			printf ("UP:pos = %d next = %d\n",pos,find_malf.pos[next_pos]); */
			}
		else
			{
			next_pos = next_down(pos);
/*			printf ("DOWN:pos = %d next = %d\n",pos,find_malf.pos[next_pos]); */
			}
		posiziona_lista(lista_scroll_variabili,
							find_malf.pos[next_pos]+1);
		XmListSelectPos(lista_scroll_variabili,find_malf.pos[next_pos]+1, TRUE);
		}
/********* non funziona: ricerca in memoria
	str = XmStringCreateSimple(stringa);
	if (XmListGetMatchPos (lista_scroll_variabili,
									str,
									&array_found,
									&numero_match))
		{
		printf ("trovati %d match\n",numero_match);
		for (i=0; i<numero_match; i++)
			printf ("%d ) %d\n",i,array_found[i]);

		XtFree(array_found);
		}
	else
		{
		XtWarning ("Item non trovato");
		}

	printf ("trovato %s in pos %d\n", stringa,
									XmListItemPos (lista_scroll_variabili,
														str));
*******************************************************************/
}
/*******************************************************************/
int posiziona_lista (Widget w, int riga)
{
int n;
int primo;
int tot;
int next_primo;


   XtUnmanageChild (w);
   XtVaGetValues (w,
         XmNvisibleItemCount, &n,
			XmNtopItemPosition , &primo,
			XmNitemCount       , &tot,
         NULL);
/*   printf ("visibili %d items: primo = %d riga = %d\n",n,primo,riga); */

	if ((riga >= primo) && (riga <= (primo+n-1)))
		next_primo = primo;
	else 
		next_primo = riga;

/*	printf ("next primo = %d\n",next_primo); */
	XtVaSetValues (w,
			XmNtopItemPosition , next_primo,
			NULL); 
   XtManageChild (w);
	return(0);
}
/*******************************************************************/
int next_down(int p)
{
int i=0;

   while (find_malf.pos[i] <= p)
		{
      i++;
		if (i == find_malf.n) return(0);
		}
   return(i);
}
/*******************************************************************/
int next_up(int p)
{
int i=0;

	while (find_malf.pos[i] < p)
		i++;
	if (i == 0) return(find_malf.n-1);
	return(i-1);
}
/*******************************************************************/
void exit_ricerca(w, tag, reason)
    Widget w;
    char *tag;
    XmAnyCallbackStruct *reason;
{
	XtDestroyWidget (select_malf_shell);
	free (lista_mf);
	attivato = 0;
	selez_malf_attivo = 0;
}
/*******************************************************************/
void inserisci_somm(w, tag, reason)
    Widget w;
    char *tag;
    XmAnyCallbackStruct *reason;
{
int n,i;
LISTA_MF *l_mf;
float valore;
int valore_int;
int new_address;
char stringa[100];

	if (val_agg.stato_sked == STATO_STOP)
		{
		PostDialog (w, XmDIALOG_WARNING, NON_IN_STOP);
		return;
		}
	l_mf = lista_mf + sistema_selezionato;

	new_address = l_mf->malf[variabile_selezionata].addr;
	for (i=0; i<sommario_mf.numero; i++)
		{
		if ((sommario_mf.occupato[i] == OCCUPATO) &&
			 (sommario_mf.address[i] == new_address))  /* gia in sommario */
			{
			sprintf (stringa,"%s: %s",
               l_mf->malf[variabile_selezionata].label,
               GIA_IN_SOMMARIO);
         PostDialog (w,XmDIALOG_WARNING,stringa);
			return;
			}
		}
printf ("confermato inserimento %s\n",
			(lista_mf+sistema_selezionato)->malf[variabile_selezionata].label);	

	for (n=0; n<sommario_mf.numero; n++)
		if (sommario_mf.occupato[n] == NON_OCCUPATO)
			break;

	strcpy (sommario_mf.label[n],l_mf->malf[variabile_selezionata].label);
	strcpy (sommario_mf.descrizione[n],l_mf->malf[variabile_selezionata].descr);
	sommario_mf.address[n] = l_mf->malf[variabile_selezionata].addr;
	valore = leggi_valore (sommario_mf.address[n]);
	sommario_mf.val_def[n] = valore;
	sommario_mf.delay[n] = DELAY_DEFAULT; 
	sommario_mf.durata[n] = DURATA_DEFAULT;
	sommario_mf.durata_non_inf[n] = 0;  
	sommario_mf.rampa[n] = RAMPA_DEFAULT;
	sommario_mf.target[n] = valore;
	strcpy (sommario_mf.stato[n], SELEZIONATO);
	sommario_mf.attuale[n] = valore;
	sommario_mf.marcato[n] = NON_MARCATO;
	sommario_mf.occupato[n] = OCCUPATO;
	sommario_mf.da_riattivare[n] = 0;
	sommario_mf.delay_in_modifica[n] = 0;
	sommario_mf.durata_in_modifica[n] = 0;

	XmToggleButtonSetState (toggle_w[i],False,True);

	sommario_mf.numero++;

	aggiorna_riga_sommario(n);

	if (sommario_mf.numero >= MAX_MF_SOMM)
		tasto_bloccato(tasto_ok,"MF");
}
/*******************************************************************/
int aggiorna_riga_sommario(int riga)
{
char temp[100];
int digitale;
Pixel colore_att, colore_dest;

if (sommario_mf.occupato[riga])
	{
	digitale = isdigital(sommario_mf.label[riga]);
	XtVaSetValues (label_w[riga],XmNvalue,sommario_mf.label[riga],NULL);
	XtVaSetValues (descrizione_w[riga],XmNvalue,
								sommario_mf.descrizione[riga],NULL);
	if (digitale)
		sprintf (temp,"%1.0f",sommario_mf.val_def[riga]);
	else
		sprintf (temp,"%f",sommario_mf.val_def[riga]);
	XtVaSetValues (val_default_w[riga],XmNvalue,temp,NULL);
	sprintf (temp,"%4.0f",sommario_mf.delay[riga]);
	XtVaSetValues (delay_w[riga],XmNvalue,temp,XmNeditable,True,NULL);
	sprintf (temp,"%4.0f",sommario_mf.durata[riga]);
	XtVaSetValues (durata_w[riga],XmNvalue,temp,XmNeditable,True,NULL);
	if (digitale)
		{
		strcpy (temp,"");
		XtVaSetValues (rampa_w[riga],
					XmNcursorPositionVisible, False,
					XmNeditable     ,    False,
					XmNvalue        ,    temp,
					NULL);

		if (sommario_mf.val_def[riga] == 0.0)
			sommario_mf.target[riga] = 1.0;
		else if (sommario_mf.val_def[riga] == 1.0)
			sommario_mf.target[riga] = 0.0;
		else
			{
         sprintf (temp,"%s:\n %s = %f",
                  sommario_mf.label[riga],
                  VALORE_NON_CORRETTO,
                  sommario_mf.val_def[riga]);
         PostDialog (malf_shell,XmDIALOG_WARNING, temp);
         }
		sprintf (temp,"%1.0f",sommario_mf.target[riga]);
		XtVaSetValues (val_fin_w[riga],
               XmNcursorPositionVisible, False,
               XmNeditable     ,    False,
               XmNvalue        ,    temp,
               NULL);
		}
	else
		{
		sprintf (temp,"%f",sommario_mf.target[riga]);
		XtVaSetValues (val_fin_w[riga],
					XmNcursorPositionVisible, True,
               XmNeditable     ,    True,
               XmNvalue        ,    temp,
               NULL);
		sprintf (temp,"%7.3f",sommario_mf.rampa[riga]);
		XtVaSetValues (rampa_w[riga],
               XmNcursorPositionVisible, True,
               XmNeditable     ,    True,
               XmNvalue        ,    temp,
               NULL);
		}
	if (digitale)
		sprintf (temp,"%1.0f",sommario_mf.attuale[riga]);
	else
		sprintf (temp,"%f",sommario_mf.attuale[riga]);
	XtVaSetValues (val_att_w[riga],XmNvalue,temp,NULL);

	XtVaSetValues (stato_mf_w[riga],XmNvalue,sommario_mf.stato[riga],NULL);
	XtVaGetValues (descrizione_w[riga], XmNbackground, &colore_att, NULL);
	if (!strcmp(sommario_mf.stato[riga],INSERITO))
		colore_dest = colore_inserito;
	else if ((!strcmp(sommario_mf.stato[riga],ATTIVATO)) ||
				(!strcmp(sommario_mf.stato[riga],DISATTIVATO)))
		colore_dest = colore_attivato;
	else
		colore_dest = colore_selezionato;
	if (colore_att != colore_dest)
		cambia_colori_mf (colore_dest, riga);
	}
else
	{
	XtVaSetValues (label_w[riga],XmNvalue,"",NULL);
	XtVaSetValues (descrizione_w[riga],XmNvalue,"",NULL);
	XtVaSetValues (val_default_w[riga],XmNvalue,"",NULL);
	XtVaSetValues (delay_w[riga],XmNvalue,"",XmNeditable,False,NULL);
	XtVaSetValues (durata_w[riga],XmNvalue,"",XmNeditable,False,NULL);
	XtVaSetValues (rampa_w[riga],XmNvalue,"",XmNeditable,False,NULL);
	XtVaSetValues (val_fin_w[riga],XmNvalue,"",XmNeditable,False,NULL);
	XtVaSetValues (val_att_w[riga],XmNvalue,"",NULL);
	XtVaSetValues (stato_mf_w[riga],XmNvalue,"",NULL);
	cambia_colori_mf (colore_selezionato, riga);
	}

return(0);
}
/*******************************************************************/
int tasto_bloccato (w,who)
Widget w;
char *who;
{
	if (!strcmp (who,"MF"))
		if (selez_malf_attivo)
			XtVaSetValues (w, XmNsensitive, False, NULL);

	if (!strcmp (who,"FR"))
		if (selez_frem_attivo)
			XtVaSetValues (w, XmNsensitive, False, NULL);

	return (0);
}
/*******************************************************************/
int tasto_sbloccato (w)
Widget w;
{
   XtVaSetValues (w, XmNsensitive, True, NULL);
   return (0);
}
/*******************************************************************/
void seleziona_sistema_mf(w, tag, reason)
    Widget w;
    char *tag;
	 XmListCallbackStruct *reason;
{
int indice_sistema;
		indice_sistema = reason->item_position;
		sistema_selezionato = indice_sistema - 1;
		printf ("seleziona_sistema: scelto sistema %d\n",
				reason->item_position);
		pulisci_lista(lista_scroll_variabili);
		if (inserisci_sistema(lista_scroll_variabili, indice_sistema))
		    XmListSelectPos(lista_scroll_variabili, 1, TRUE);
}
/*******************************************************************/
void seleziona_var_mf(w, tag, reason)
    Widget w;
    char *tag;
    XmListCallbackStruct *reason;
{

	printf ("selezionato item %d\n",reason->item_position);
	variabile_selezionata = reason->item_position - 1;

	printf ("label = :%s:\n",
				(lista_mf+sistema_selezionato)->malf[variabile_selezionata].label);
}
/*******************************************************************/
int carica_dati_malf()
{
int nmod,i,nblocchi;
unsigned short indice_modello;
unsigned short indice_blocco;
LISTA_MF *l_mf;
char app[100];
int ret;

   if (elenco_sistemi() <= 0)
      {
      printf ("**** e' impossibile generare la lista dei sistemi mf ***\n");
      XtDestroyWidget (select_malf_shell);
      attivato = 0;
		selez_malf_attivo = 0;
      }
/*	printf ("per malf alloco %d bytes\n",sizeof(LISTA_MF)*lista_sist.nsist); */
	lista_mf = (LISTA_MF *)malloc (sizeof(LISTA_MF)*lista_sist.nsist);
	l_mf = lista_mf;
	for (i=0; i<lista_sist.nsist; i++,lista_mf++)
		lista_mf->nvar = 0;
			
	lista_mf = l_mf;

	ret = dati_blocco_malf(&nmod, &indice_modello, &nblocchi, &indice_blocco);
        if( ret<0 )
            return(0);

	for (i=0; i<tot_variabili; i++)
		{
		if ((variabili[i].mod == (indice_modello+1)) && /* modello        */
			 (variabili[i].blocco == (indice_blocco+1)))  /* blocco         */
			{
/* printf ("%d) %s %s\n",i,variabili[i].nome, variabili[i].descr);  */
			presa_dati(i);
			}
		}
/*
	for (i=0; i<lista_sist.nsist; i++)
		printf ("sistema %s var %d\n",lista_sist.sigla[i],(lista_mf+i)->nvar);
*/
}
/*****************************************************************/
int dati_blocco_malf (n, indx_mod, nb, indx_b)
int *n;
unsigned short *indx_mod;
int *nb;
unsigned short *indx_b;
{
int i;
char app[100];

   *n = numero_modelli(ind_sh_top);
   for (i=0; i<*n; i++)
      {
      if (!strcmp(nome_modello(ind_sh_top,i+1),nome_modello_mffr))
         {
         *indx_mod = i;
         break;
         }
      }
   if( i == *n )
      return(-1);

   *nb = numero_blocchi(ind_sh_top,*indx_mod+1);

   for (i=0; i<*nb; i++)
      {
      sprintf (app,"%s",nome_blocco(ind_sh_top,*indx_mod+1,i+1));
/*      printf ("blocco %d) :%s: :%s: %d\n",
               i,app,nome_blocco_malf,sizeof(nome_blocco_malf)-1); */
      if (strncmp(app, nome_blocco_malf,sizeof(nome_blocco_malf)-1) == 0)
         {
         *indx_b = i;
         break;
         }
      }
	return(0);
}
/*****************************************************************/
/*
 * registra i dati delle malfunzioni nelle apposite strutture.   
 * prende in considerazione solo le variabili di ingresso (YI JI)
 * in quanto il blocco MALFMALF non introduce modifiche alla variabile
 */
int presa_dati(int i)
{
int sist;
char *s;

	if ((s = strstr(variabili[i].nome,digital_inp)) != NULL)
		{
		if (!strcmp(variabili[i].nome,s))
			{
			if (strncmp(variabili[i].nome,"JIMA",4) == 0)
				return(0);
			if ((sist = test_sistema(variabili[i].nome)) >= 0)
				leggi_dati(sist,i);
			}
		}

	else if ((s = strstr(variabili[i].nome,digital_out)) != NULL)
      {
      if (!strcmp(variabili[i].nome,s))
         {
         if ((sist = test_sistema(variabili[i].nome)) >= 0)
				;
         }
      }

   else if ((s = strstr(variabili[i].nome,analog_inp)) != NULL)
      {
      if (!strcmp(variabili[i].nome,s))
         {
         if ((sist = test_sistema(variabili[i].nome)) >= 0)
				leggi_dati(sist,i);
         }
      }

   else if ((s = strstr(variabili[i].nome,analog_out)) != NULL)
      {
      if (!strcmp(variabili[i].nome,s))
         {
         if ((sist = test_sistema(variabili[i].nome)) >= 0)
				;
         }
      }

	else
		{
	printf ("var %s non nota\n",variabili[i].nome);
		}
}
/*****************************************************************/
int test_sistema (char *label)
{
int i;
char *s;

	for (i=0; i<lista_sist.nsist; i++)
		{
		if ((s = strstr(label,lista_sist.sigla[i])) != NULL)
		if (!strcmp(lista_sist.sigla[i],s))
			return(i);
		}

	return(-1);
}
/*****************************************************************/
int leggi_dati(int  s, int i)
{
int n;
LISTA_MF *l_mf;             /* puntatore di appoggio          */
	
	l_mf = lista_mf+s;
	n = l_mf->nvar;          /* numero variabili del sistema s */
	strcpy (l_mf->malf[n].label, variabili[i].nome);
	strcpy (l_mf->malf[n].descr, variabili[i].descr);
	l_mf->malf[n].addr = variabili[i].addr;

	taglia_descr(l_mf->malf[n].descr);

	l_mf->nvar ++;
	return(0);
}
/*****************************************************************/
int taglia_descr(char *s)
{
int i,j;
char app[MAX_LUN_DESCR_VAR];

	i=0;
	while (s[i] != ')')
		i++;

	for (j=0,i++; s[i]!='\0'; j++,i++)
		app[j] = s[i];

	app[j]='\0';
	strcpy(s,app);
	return(0);
}
/*****************************************************************/
int pulisci_lista (Widget w)
{
int n;
int i;

	XtUnmanageChild (w);
	XtVaGetValues (w, 
			XmNitemCount, &n,
			NULL);

	for (i=0; i<n; i++)
		XmListDeletePos (w, 1);
	XtManageChild (w);
	
	return(0);
}
/*****************************************************************/
int inserisci_sistema (Widget w, int s)
{
int n,i;
LISTA_MF *l_mf;
char app_char[200];

	l_mf = lista_mf + (s-1);
	n = l_mf->nvar;         /* numero mf nel sistema      */

	XtUnmanageChild (w);
	for (i=0; i<n; i++)
		{
		sprintf (app_char,"%s %s",l_mf->malf[i].label,
											l_mf->malf[i].descr);
		XmListAddItemUnselected(w,
                  XmStringCreate(app_char,XmSTRING_DEFAULT_CHARSET),
                  0);
		}
	XtManageChild (w);
	return(n);
}
/****************************************************************/
int isdigital (char *s)
{
	if (strncmp(s,digital_inp,strlen(digital_inp)) == 0)
		return (1);
	return (0);
}
#endif
