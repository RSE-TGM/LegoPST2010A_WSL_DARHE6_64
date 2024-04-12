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
   modulo monit_var_frem.c
   tipo 
   release 5.4
   data 2/16/96
   reserved @(#)monit_var_frem.c	5.4
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)monit_var_frem.c	5.4\t2/16/96";
/*
        Fine sezione per SCCS
*/
#ifdef MFFR
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

# include "monit_mffr.h"
#include <Rt/RtMemory.h>

char   *nome_modello (char *, int);

extern SOMMARIO_FR sommario_fr;

int sistema_selezionato_fr;   /* sistema scelto 0/n  */
int variabile_selezionata_fr;  /* variabile scelta 0/n */

extern char *ind_sh_top;   /* puntatore inizio shared memory sh_var */
extern VARIABILI *variabili;  /* database delle variabili  */
extern int tot_variabili;  /* numero totale delle variabili      */
extern VALORI_AGG val_agg;

struct frem_st
	{
	char label[MAX_LUN_NOME_VAR];
	char descr[MAX_LUN_DESCR_VAR];
	int addr;
	};
typedef struct frem_st FREM;

struct listafr_sist_st
	{
	int nvar;                  /* numero malfunzioni del sistema       */
	FREM frem[MAX_FREM_SIST];  /* dati delle malfunzioni               */
	};
typedef struct listafr_sist_st LISTA_FR;
LISTA_FR *lista_fr;

struct lista_sist_fr_st
	{
	int nsist;                  /* numero sistemi che hanno mf o fr     */
	char sigla[MAX_MODEL][MAX_LUNGH_SIGLA]; /* sigla contenuta nelle variabili*/
	char descrizione[MAX_MODEL] [MAX_LUN_DESCR_VAR];/*descrizione modello */
	};
typedef struct lista_sist_fr_st LISTA_SIST;
LISTA_SIST lista_sist;         /* struttura contenente la lista dei sistemi */

struct find_frem_st
	{
	int n;                      /* numero di match nella lista               */
	int pos[MAX_FREM_SIST];     /* array dei match position 0 - n-1          */
	};
typedef struct find_frem_st FIND_FREM;
FIND_FREM find_frem;

int numero_match;               /* numero di elementi trovati in lista */
int *array_found;               /* elenco items trovati                */

extern struct timeb tempo;      /* tempo di orologio            */
extern Widget widget_array[MAX_WIDGETS];
extern Widget main_window_widget;
extern Widget toplevel_widget; 

extern Widget toggle_fr_w[MAX_FR_SOMM];
extern Widget label_fr_w[MAX_FR_SOMM];
extern Widget descrizione_fr_w[MAX_FR_SOMM];
extern Widget val_default_fr[MAX_FR_SOMM];
extern Widget rampa_fr_w[MAX_FR_SOMM];
extern Widget val_fin_fr_w[MAX_FR_SOMM];
extern Widget val_att_fr_w[MAX_FR_SOMM];
extern Widget stato_fr_w[MAX_FR_SOMM];

/* ****************  procedure inserite  ************************ */

void select_frem_proc(); /* procedura che attiva il colloquio malfunzioni    */
void ricerca_volo_fr(); /*ricerca (ad ogni variazione di carattere) di una
													 stringa nella lista   */
void cerca_tutte_var_fr();/* effettua la ricerca di una stringa nella lista   */
void ricerca_fr();      /* posiziona sulla prossima stringa                */
void exit_ricerca_fr();     /* termina l' attuale colloquio */
void inserisci_somm_fr();   /* inserisce la fr selezionata in sommario       */
void seleziona_sistema_fr(); /* seleziona un sistema mf ed estrae le var. */
void seleziona_var_fr(); /* seleziona una variabile da lista        */

extern float leggi_valore(int p);
extern Widget PostDialog();
/********************************************************************/
/*
 * definizioni malfunzioni
 */
Widget select_frem_shell;
Widget form_principale_fr, frame_principale_fr;
Widget form_titolo_fr, frame_titolo_fr;
Widget form_sistemi_fr, frame_sistemi_fr, lista_scroll_sistemi_fr;
Widget form_variabili_fr, frame_variabili_fr, lista_scroll_variabili_fr;
Widget form_selezione_fr, variabile_fr_w, bottone_su_fr, bottone_giu_fr;
Widget form_tasti_comando_fr;
Widget frame_tasto_ok_fr, tasto_fr_ok, frame_tasto_exit_fr, tasto_fr_xit;
extern Widget frem_shell;
/********************************************************************/
static  int attivato_fr = 0;
int selez_frem_attivo = 0;
/***************************************************************************/
/***************************************************************************/
/*
 * specifiche fonts
 */
extern XmFontList  fontlist_mffr;
/****************************************************************************/

void select_frem_proc(w, tag, reason)
    Widget w;
    int *tag;
    XmListCallbackStruct *reason;
{
int     widget_num = *tag;
int i;
char app_char[200];

      def_cursore (toplevel_widget, OROLOGIO);
      vis_messaggio("Attivazione selezione frem",0);
                                                   
		if (attivato_fr)
			{
			XtManageChild (select_frem_shell);
			undef_cursore (toplevel_widget);
			return;
			}


      select_frem_shell = XtVaCreateManagedWidget (NULL,
      				topLevelShellWidgetClass,toplevel_widget, 
						XmNallowShellResize       , False,
						XmNiconName               , "Selezione Funzioni Remote",
/*						XmNiconic                 , True,            */
                  XmNx                   ,  200,
                  XmNy                   ,  300,
						XmNmaxWidth            ,  700,
						XmNminWidth            ,  700,
						XmNminHeight           ,  550,
						XmNbackground             , colore_sfondo_fr,
						XmNfontList               , fontlist_mffr,
						NULL);
						
      form_principale_fr = XtVaCreateManagedWidget (NULL,
                  xmFormWidgetClass, select_frem_shell,
						XmNbackground             , colore_sfondo_fr,
						XmNfontList               , fontlist_mffr,
                  NULL);
		frame_principale_fr = XtVaCreateManagedWidget (NULL,
                  xmFrameWidgetClass     ,  form_principale_fr,
                  XmNwidth               ,  700,
                  XmNheight              ,  550,
						XmNbottomAttachment    ,  XmATTACH_FORM,
						XmNtopAttachment       ,  XmATTACH_FORM,
						XmNleftAttachment      ,  XmATTACH_FORM,
						XmNrightAttachment     ,  XmATTACH_FORM,
                  XmNbackground             , colore_sfondo_fr,
						XmNfontList               , fontlist_mffr,
                  NULL);

		carica_dati_frem();
		titolo_fr();
		lista_sistemi_fr();   
		lista_variabili_fr(); 
		selezione_variabile_fr();
		tasti_comando_fr();

		undef_cursore (toplevel_widget);

		XmListSelectPos(lista_scroll_sistemi_fr, 1, TRUE);
		attivato_fr = 1;
		selez_frem_attivo =1;

		if (sommario_fr.numero >= MAX_MF_SOMM)
      	tasto_bloccato(tasto_fr_ok,"FR");

}
/***************************************************************/
int titolo_fr()
{
      frame_titolo_fr = XtVaCreateManagedWidget ("Selezione Funzioni Remote",
                  xmFrameWidgetClass     ,  form_principale_fr,
                  XmNwidth               ,  700,
                  XmNheight              ,  30,
                  XmNtopAttachment       ,  XmATTACH_FORM,
                  XmNleftAttachment      ,  XmATTACH_FORM,
                  XmNrightAttachment     ,  XmATTACH_FORM,
						XmNfontList               , fontlist_mffr,
                  NULL);
      XtVaCreateManagedWidget (NULL,
                  xmLabelWidgetClass     ,  frame_titolo_fr,
                  XmNlabelString         ,  XmStringCreateLtoR
                                             ("Selezione Funzioni Remote",
                                             XmSTRING_DEFAULT_CHARSET),
                  XmNbackground          ,  pix_val[0],
						XmNfontList               , fontlist_mffr,
                  NULL);
		return(0);
}
/***************************************************************/
int lista_sistemi_fr()
{
int i;
char app_char[100];
Widget vert_scr_w;

      form_sistemi_fr  = XtVaCreateManagedWidget (NULL,
                  xmFormWidgetClass, form_principale_fr,
                  XmNwidth               ,  500,
                  XmNheight              ,  100,
                  XmNtopAttachment       ,  XmATTACH_FORM,
                  XmNtopOffset           ,  50,
                  XmNrightAttachment     ,  XmATTACH_FORM,
                  XmNrightOffset         ,  200,
                  XmNleftAttachment      ,  XmATTACH_FORM,
						XmNleftOffset          ,  50,
						XmNbackground          ,  colore_tabelle_fr,
						XmNfontList               , fontlist_mffr,
                  NULL);
      frame_sistemi_fr = XtVaCreateManagedWidget (NULL,
                  xmFrameWidgetClass     ,  form_sistemi_fr,
                  XmNwidth               ,  500,
                  XmNheight              ,  100,
                  XmNtopAttachment       ,  XmATTACH_FORM,
                  XmNrightAttachment     ,  XmATTACH_FORM,
                  XmNleftAttachment      ,  XmATTACH_FORM,
						XmNfontList               , fontlist_mffr,
                  NULL);
      lista_scroll_sistemi_fr =  XmCreateScrolledList (form_sistemi_fr,
                  "lista_sistemi",NULL, 0);

      XtManageChild (lista_scroll_sistemi_fr);

      XtVaSetValues (lista_scroll_sistemi_fr,
                  XmNselectionPolicy        , XmSINGLE_SELECT,
                  XmNwidth                  ,  500,
                  XmNvisibleItemCount       , 5,
                  XmNbackground          ,  colore_tabelle_fr,
						XmNfontList               , fontlist_mffr,
                  NULL);
      XtVaSetValues (XtParent(lista_scroll_sistemi_fr),
                  XmNwidth                  ,  500,  
						XmNheight                 , 100,
                  XmNrightAttachment        , XmATTACH_WIDGET,
                  XmNrightWidget             , form_sistemi_fr,
						XmNbackground          ,  colore_tabelle_fr,
                  NULL);

      XtVaGetValues (XtParent(lista_scroll_sistemi_fr),
                  XmNverticalScrollBar, &vert_scr_w, NULL);
      XtVaSetValues (vert_scr_w,
                  XmNtroughColor, colore_scrollbar_fr,
                  XmNbackground , colore_tabelle_fr,
                  NULL);
		XtAddCallback (lista_scroll_sistemi_fr, 
							XmNsingleSelectionCallback,
							seleziona_sistema_fr,NULL);
		XtAddCallback (lista_scroll_sistemi_fr,
                     XmNsingleSelectionCallback,
							cerca_tutte_var_fr, NULL);

		for (i=0; i<lista_sist.nsist; i++)
			{
			sprintf(app_char,"%s     %s",
						lista_sist.sigla[i],
						lista_sist.descrizione[i]);
			XmListAddItemUnselected(lista_scroll_sistemi_fr,
                  XmStringCreate(app_char,XmSTRING_DEFAULT_CHARSET),
                  0);
			}

/*		XmListSelectPos(lista_scroll_sistemi_fr, 1, TRUE);   */
		return(0);
}
/*******************************************************************/
int lista_variabili_fr()
{
int i;
char app_char[100];
Widget vert_scr_w;

      form_variabili_fr  = XtVaCreateManagedWidget (NULL,
                  xmFormWidgetClass, form_principale_fr,
                  XmNwidth               ,  600,
						XmNheight              ,  100,
                  XmNbottomAttachment    ,  XmATTACH_FORM,
                  XmNbottomOffset        ,  170,
                  XmNtopAttachment       ,  XmATTACH_WIDGET,
                  XmNtopWidget           ,  form_sistemi_fr,
						XmNtopOffset           ,  50,
                  XmNrightAttachment     ,  XmATTACH_FORM,
                  XmNrightOffset         ,  50,
                  XmNleftAttachment      ,  XmATTACH_FORM,
                  XmNleftOffset          ,  50,         
						XmNbackground          ,  colore_tabelle_fr,
						XmNfontList               , fontlist_mffr,
                  NULL);
      frame_variabili_fr = XtVaCreateManagedWidget (NULL,
                  xmFrameWidgetClass     ,  form_variabili_fr,
                  XmNwidth               ,  600,
						XmNbottomAttachment    ,  XmATTACH_FORM,
                  XmNtopAttachment       ,  XmATTACH_FORM,
                  XmNrightAttachment     ,  XmATTACH_FORM,
                  XmNleftAttachment      ,  XmATTACH_FORM,
						XmNfontList               , fontlist_mffr,
                  NULL);
      lista_scroll_variabili_fr =  XmCreateScrolledList (form_variabili_fr,
						"lista_variabili",NULL ,0);

      XtVaSetValues (lista_scroll_variabili_fr,
                  XmNselectionPolicy        , XmSINGLE_SELECT,
                  XmNwidth                  ,  600,
                  XmNbackground          ,  colore_tabelle_fr,
						XmNfontList               , fontlist_mffr,
                  NULL);
      XtVaSetValues (XtParent(lista_scroll_variabili_fr),
						XmNwidth                  ,  600,
                  XmNrightAttachment        , XmATTACH_WIDGET,
                  XmNrightWidget             , form_variabili_fr,
						XmNbottomAttachment        , XmATTACH_WIDGET,
                  XmNbottomWidget             , form_variabili_fr,
						XmNbackground          ,  colore_tabelle_fr,
                  NULL);

      XtVaGetValues (XtParent(lista_scroll_variabili_fr),
                  XmNverticalScrollBar, &vert_scr_w, NULL);
      XtVaSetValues (vert_scr_w,
                  XmNtroughColor, colore_scrollbar_fr,
                  XmNbackground , colore_tabelle_fr,
                  NULL);
      XtAddCallback (lista_scroll_variabili_fr,
                     XmNsingleSelectionCallback,
                     seleziona_var_fr,NULL);

      XtManageChild (lista_scroll_variabili_fr);
	return(0);
}
/*******************************************************************/
int selezione_variabile_fr()
{

		form_selezione_fr = XtVaCreateManagedWidget (NULL,
                  xmFormWidgetClass, form_principale_fr,
                  XmNtopAttachment , XmATTACH_WIDGET,
                  XmNtopWidget     , form_variabili_fr,
                  XmNtopOffset     , 30,
                  XmNleftAttachment  , XmATTACH_FORM,
                  XmNleftOffset     ,  150,
                  XmNbackground        , colore_sfondo_fr,
						XmNfontList               , fontlist_mffr,
                  NULL);
                    
		bottone_su_fr = XtVaCreateManagedWidget (NULL,
                  xmArrowButtonWidgetClass, form_selezione_fr,
                  XmNleftAttachment      , XmATTACH_FORM,
                  XmNarrowDirection       , XmARROW_UP,
						XmNheight               , 30,
						XmNwidth                , 80,
                  XmNbackground        , colore_tasti_fr,
						XmNfontList               , fontlist_mffr,
                  NULL);

		variabile_fr_w = XtVaCreateManagedWidget ("label",
                  xmTextWidgetClass,   form_selezione_fr,
                  XmNcolumns      ,    20,
                  XmNleftAttachment,    XmATTACH_WIDGET,
						XmNleftWidget    ,    bottone_su_fr,
						XmNleftOffset    ,    20,
                  XmNcursorPositionVisible, True,
                  XmNvalue      ,      "selezione",
						XmNheight               , 30,
                  XmNbackground        , colore_tabelle_fr,
						XmNfontList               , fontlist_mffr,
                  NULL);

		bottone_giu_fr = XtVaCreateManagedWidget (NULL,
						xmArrowButtonWidgetClass, form_selezione_fr,
						XmNleftAttachment      , XmATTACH_WIDGET,
						XmNleftWidget          , variabile_fr_w,
						XmNleftOffset          , 20,
						XmNarrowDirection       , XmARROW_DOWN,
						XmNheight               , 30,
						XmNwidth                , 80,
                  XmNbackground        , colore_tasti_fr,
						XmNfontList               , fontlist_mffr,
						NULL);

		XtVaSetValues (form_principale_fr, XmNdefaultButton, bottone_giu_fr, NULL);
		XtVaSetValues (bottone_giu_fr, XmNshowAsDefault , 1, NULL);

/*		XtAddCallback (variabile_fr_w, 
							XmNvalueChangedCallback, ricerca_volo_fr, NULL);  */

		XtAddCallback(variabile_fr_w, XmNactivateCallback, cerca_tutte_var_fr, NULL);
		XtAddCallback(bottone_su_fr,XmNactivateCallback, ricerca_fr, direzione_up);
		XtAddCallback(bottone_giu_fr,XmNactivateCallback,ricerca_fr,direzione_down);

}
/*******************************************************************/
int tasti_comando_fr()
{
Widget frame_tasti;

      form_tasti_comando_fr = XtVaCreateManagedWidget ("form_tasti_comando",
                  xmFormWidgetClass, form_principale_fr,
                  XmNtopAttachment , XmATTACH_WIDGET,
                  XmNtopWidget     , form_selezione_fr,
                  XmNtopOffset     , 10,
                  XmNleftAttachment  , XmATTACH_FORM,
						XmNleftOffset          ,   10,
						XmNrightAttachment  , XmATTACH_FORM,
						XmNrightOffset          ,  10,
						XmNbottomAttachment , XmATTACH_FORM,
						XmNbottomOffset        ,  20,
                  XmNbackground        , colore_sfondo_fr,
						XmNfontList               , fontlist_mffr,
                  NULL);
		frame_tasti = XtVaCreateManagedWidget ("frame_tasti_comando",
                  xmFrameWidgetClass     ,  form_tasti_comando_fr,
						XmNleftAttachment  , XmATTACH_FORM,
						XmNrightAttachment  , XmATTACH_FORM,
                  XmNheight              ,  70,
                  XmNbackground        , colore_sfondo_fr,
						XmNfontList               , fontlist_mffr,
                  NULL);

		frame_tasto_ok_fr = XtVaCreateManagedWidget ("frame_ok",
                  xmFrameWidgetClass     ,  form_tasti_comando_fr,
                  XmNwidth               ,  120,
                  XmNheight              ,  30,
                  XmNleftAttachment      ,  XmATTACH_FORM,
                  XmNleftOffset          ,  20,
                  XmNbottomAttachment    ,  XmATTACH_FORM,
                  XmNbottomOffset        ,  20,
                  XmNbackground      , colore_tasti_fr,
						XmNfontList               , fontlist_mffr,
                  NULL);
		tasto_fr_ok      = XtVaCreateManagedWidget ("tasto_fr_ok",
						xmPushButtonWidgetClass , frame_tasto_ok_fr,
                  XmNlabelString         , XmStringCreateLtoR ("CONFERMA",
                                                XmSTRING_DEFAULT_CHARSET),
                  XmNwidth               , 120,
                  XmNheight              , 30,
                  XmNdefaultButtonShadowThickness ,  1,
						XmNbackground      , colore_tasti_fr,
						XmNfontList               , fontlist_mffr,
                  NULL);

      frame_tasto_exit_fr = XtVaCreateManagedWidget ("frame_exit",
                  xmFrameWidgetClass     ,  form_tasti_comando_fr,
                  XmNwidth               ,  120,
                  XmNheight              ,  30,
                  XmNrightAttachment      ,  XmATTACH_FORM,
                  XmNrightOffset          ,  20,
                  XmNbottomAttachment    ,  XmATTACH_FORM,
                  XmNbottomOffset        ,  20,
                  XmNbackground      , colore_tasti_fr,
						XmNfontList               , fontlist_mffr,
                  NULL);
		tasto_fr_xit  = XtVaCreateManagedWidget ("tasto_exit",
                  xmPushButtonWidgetClass , frame_tasto_exit_fr,
                  XmNlabelString         , XmStringCreateLtoR ("USCITA",
                                                XmSTRING_DEFAULT_CHARSET),
                  XmNwidth               , 120,
                  XmNheight              , 30,
                  XmNdefaultButtonShadowThickness ,  2,
						XmNbackground      , colore_tasti_fr,
						XmNfontList               , fontlist_mffr,
                  NULL);
/*
 * callback relative ai tasti
 */
		XtAddCallback (tasto_fr_xit, XmNactivateCallback, exit_ricerca_fr, NULL);
		XtAddCallback (tasto_fr_ok, XmNactivateCallback, inserisci_somm_fr, NULL);
}
/*******************************************************************/
void ricerca_volo_fr(w, tag, reason)
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
void cerca_tutte_var_fr(w, tag, reason)
    Widget w;
    char *tag;
    XmAnyCallbackStruct *reason;
{
char *stringa;
XmString str;
LISTA_FR *l_fr;
int i;
int ntot;

  stringa = XmTextGetString (variabile_fr_w);
/*   printf ("activate:ricerca con :%s:\n",stringa); */
	find_frem.n = 0;       /* reset precedente array                */
	l_fr = lista_fr + sistema_selezionato_fr;
	ntot = l_fr->nvar;
	for (i=0; i<ntot; i++)
		{
		if ((Utstrstr(l_fr->frem[i].label, stringa) != NULL) ||
			 (Utstrstr(l_fr->frem[i].descr, stringa) != NULL))
			{
			find_frem.pos[find_frem.n] = i;
			find_frem.n++;
/*			printf ("trovato %s a riga %d\n",stringa,i); */
			}
		}
   XtFree (stringa);
}
/*******************************************************************/
void ricerca_fr(w, tag, reason)
    Widget w;
    XtPointer *tag;
    XmArrowButtonCallbackStruct *reason;
{
int pos,next_pos;
int i;

	pos = variabile_selezionata_fr;

	if (find_frem.n > 0)
		{
		if (!strcmp(tag,"UP"))
			{
			next_pos = next_up_fr(pos);
			}
		else
			{
			next_pos = next_down_fr(pos);
			}
		posiziona_lista(lista_scroll_variabili_fr,
							find_frem.pos[next_pos]+1);
		XmListSelectPos(lista_scroll_variabili_fr,find_frem.pos[next_pos]+1, TRUE);
		}
/********* non funziona: ricerca in memoria
	str = XmStringCreateSimple(stringa);
	if (XmListGetMatchPos (lista_scroll_variabili_fr,
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
									XmListItemPos (lista_scroll_variabili_fr,
														str));
*******************************************************************/
}
/*******************************************************************/
int next_down_fr(int p)
{
int i=0;

   while (find_frem.pos[i] <= p)
		{
      i++;
		if (i == find_frem.n) return(0);
		}
   return(i);
}
/*******************************************************************/
int next_up_fr(int p)
{
int i=0;

	while (find_frem.pos[i] < p)
		i++;
	if (i == 0) return(find_frem.n-1);
	return(i-1);
}
/*******************************************************************/
void exit_ricerca_fr(w, tag, reason)
    Widget w;
    char *tag;
    XmAnyCallbackStruct *reason;
{
	XtDestroyWidget (select_frem_shell);
	free (lista_fr);
	attivato_fr = 0;
		selez_frem_attivo =0;
}
/*******************************************************************/
void inserisci_somm_fr(w, tag, reason)
    Widget w;
    char *tag;
    XmAnyCallbackStruct *reason;
{
int n,i;
LISTA_FR *l_fr;
float valore;
int valore_int;
int new_address;
char stringa[100];

   if (val_agg.stato_sked == STATO_STOP)
      {
		PostDialog (w,XmDIALOG_WARNING, NON_IN_STOP);
      return;
      }

   l_fr = lista_fr + sistema_selezionato_fr;

   new_address = l_fr->frem[variabile_selezionata_fr].addr;
   for (i=0; i<sommario_fr.numero; i++)
      {
      if ((sommario_fr.occupato[i] == OCCUPATO) &&
          (sommario_fr.address[i] == new_address))  /* gia in sommario */
         {
		   sprintf (stringa,"%s: %s",
					l_fr->frem[variabile_selezionata_fr].label,
					GIA_IN_SOMMARIO);
			PostDialog (w,XmDIALOG_WARNING,stringa);
         return;
         }
      }

printf ("confermato inserimento %s\n",
       (lista_fr+sistema_selezionato_fr)->frem[variabile_selezionata_fr].label);

   for (n=0; n< sommario_fr.numero; n++)
      if (sommario_fr.occupato[n] == NON_OCCUPATO)
         break;

   strcpy (sommario_fr.label[n],l_fr->frem[variabile_selezionata_fr].label);
   strcpy (sommario_fr.descrizione[n],
							l_fr->frem[variabile_selezionata_fr].descr);
   sommario_fr.address[n] = l_fr->frem[variabile_selezionata_fr].addr;
	valore = leggi_valore (sommario_fr.address[n]);
   sommario_fr.rampa[n] = RAMPA_DEFAULT;
   sommario_fr.target[n] = valore;
   strcpy (sommario_fr.stato[n], SELEZIONATO);
   sommario_fr.attuale[n] = valore;
   sommario_fr.val_def[n] = valore;
   sommario_fr.marcato[n] = NON_MARCATO;
   sommario_fr.occupato[n] = OCCUPATO;
	sommario_fr.da_riattivare[n] = 0;

	XmToggleButtonSetState (toggle_fr_w[i],False,True);

   sommario_fr.numero++;

   aggiorna_riga_sommario_fr(n);

   if (sommario_fr.numero >= MAX_FR_SOMM)
      tasto_bloccato(tasto_fr_ok,"FR");
}
/*******************************************************************/
int aggiorna_riga_sommario_fr(int riga)
{
char temp[100];
int digitale;
Pixel colore_att, colore_dest;

if (sommario_fr.occupato[riga])
	{
   digitale = isdigital(sommario_fr.label[riga]);
	XtVaSetValues (label_fr_w[riga],XmNvalue,sommario_fr.label[riga],NULL);
	XtVaSetValues (descrizione_fr_w[riga],
						XmNvalue,sommario_fr.descrizione[riga],NULL);
	if (digitale)
		sprintf (temp,"%1.0f",sommario_fr.val_def[riga]);
	else
		sprintf (temp,"%f",sommario_fr.val_def[riga]);
	XtVaSetValues (val_default_fr[riga],XmNvalue,temp,NULL);
	if (digitale)
   	{
   	strcpy (temp,"");
   	XtVaSetValues (rampa_fr_w[riga],
               XmNcursorPositionVisible, False,
               XmNeditable     ,    False,
               XmNvalue        ,    temp,
               NULL);
   	if (sommario_fr.val_def[riga] == 0.0)
      	sommario_fr.target[riga] = 1.0;
   	else if (sommario_fr.val_def[riga] == 1.0)
      	sommario_fr.target[riga] = 0.0;
   	else
			{
			sprintf (temp,"%s:\n %s = %f",
						sommario_fr.label[riga],
						VALORE_NON_CORRETTO,
						sommario_fr.val_def[riga]);
			PostDialog (frem_shell,XmDIALOG_WARNING, temp);
			}
   	sprintf (temp,"%1.0f",sommario_fr.target[riga]);
   	XtVaSetValues (val_fin_fr_w[riga],
               XmNcursorPositionVisible, False,
               XmNeditable     ,    False,
               XmNvalue        ,    temp,
               NULL);
   	}
	else
   	{
   	sprintf (temp,"%f",sommario_fr.target[riga]);
   	XtVaSetValues (val_fin_fr_w[riga],
               XmNcursorPositionVisible, True,
               XmNeditable     ,    True,
               XmNvalue        ,    temp,
               NULL);
   	sprintf (temp,"%7.3f",sommario_fr.rampa[riga]);
   	XtVaSetValues (rampa_fr_w[riga],
               XmNcursorPositionVisible, True,
               XmNeditable     ,    True,
               XmNvalue        ,    temp,
               NULL);
   	}
	if (digitale)
		sprintf (temp,"%1.0f",sommario_fr.attuale[riga]);
	else
		sprintf (temp,"%f",sommario_fr.attuale[riga]);
	XtVaSetValues (val_att_fr_w[riga],XmNvalue,temp,NULL);
	XtVaSetValues (stato_fr_w[riga],XmNvalue,sommario_fr.stato[riga],NULL);
   if (!strcmp(sommario_fr.stato[riga],INSERITO))
      colore_dest = colore_inserito;
   else if ((!strcmp(sommario_fr.stato[riga],ATTIVATO)) ||
				(!strcmp(sommario_fr.stato[riga],DISATTIVATO)))
      colore_dest = colore_attivato;
   else
      colore_dest = colore_selezionato_fr;
   if (colore_att != colore_dest)
      cambia_colori_fr (colore_dest, riga);
	}
else
	{
   XtVaSetValues (label_fr_w[riga],XmNvalue,"",NULL);
   XtVaSetValues (descrizione_fr_w[riga],XmNvalue,"",NULL);
   XtVaSetValues (val_default_fr[riga],XmNvalue,"",NULL);
   XtVaSetValues (rampa_fr_w[riga],XmNvalue,"",XmNeditable,False,NULL);
   XtVaSetValues (val_fin_fr_w[riga],XmNvalue,"",XmNeditable,False,NULL);
   XtVaSetValues (val_att_fr_w[riga],XmNvalue,"",NULL);
   XtVaSetValues (stato_fr_w[riga],XmNvalue,"",NULL);
   cambia_colori_fr (colore_selezionato_fr, riga);
	}
                                              
return(0);
}
/*******************************************************************/
void seleziona_sistema_fr(w, tag, reason)
    Widget w;
    char *tag;
	 XmListCallbackStruct *reason;
{
int indice_sistema;
		indice_sistema = reason->item_position;
		sistema_selezionato_fr = indice_sistema - 1;
		printf ("seleziona_sistema: scelto sistema %d\n",
				reason->item_position);
		pulisci_lista(lista_scroll_variabili_fr);
		if (inserisci_sistema_fr(lista_scroll_variabili_fr, indice_sistema))
		    XmListSelectPos(lista_scroll_variabili_fr, 1, TRUE);
}
/*******************************************************************/
void seleziona_var_fr(w, tag, reason)
    Widget w;
    char *tag;
    XmListCallbackStruct *reason;
{

	printf ("selezionato item %d\n",reason->item_position);
	variabile_selezionata_fr = reason->item_position - 1;

	printf ("label = :%s:\n",
				(lista_fr+sistema_selezionato_fr)->frem[variabile_selezionata_fr].label);
}
/*******************************************************************/
int carica_dati_frem()
{
int nmod,i,nblocchi;
unsigned short indice_modello;
unsigned short indice_blocco;
LISTA_FR *l_fr;
char app[100];
int ret;

   if (elenco_sistemi() <= 0)
      {
      printf ("**** e' impossibile generare la lista dei sistemi fr ***\n");
      XtDestroyWidget (select_frem_shell);
      attivato_fr = 0;
		selez_frem_attivo = 0;
      }
/*	printf ("per frem alloco %d bytes\n",sizeof(LISTA_FR)*lista_sist.nsist); */
	lista_fr = (LISTA_FR *)malloc (sizeof(LISTA_FR)*lista_sist.nsist);
	l_fr = lista_fr;
	for (i=0; i<lista_sist.nsist; i++,lista_fr++)
		lista_fr->nvar = 0;
			
	lista_fr = l_fr;

	ret = dati_blocco_frem (&nmod, &indice_modello, &nblocchi, &indice_blocco);
        if( ret<0 )
           return(0);

	for (i=0; i<tot_variabili; i++)
		{
		if ((variabili[i].mod == (indice_modello+1)) && /* modello        */
			 (variabili[i].blocco == (indice_blocco+1)))  /* blocco         */
			{
/* printf ("%d) %s %s\n",i,variabili[i].nome, variabili[i].descr);  */
			presa_dati_fr(i);
			}
		}
/*
	for (i=0; i<lista_sist.nsist; i++)
		printf ("sistema %s var %d\n",lista_sist.sigla[i],(lista_fr+i)->nvar);
*/
}
/*****************************************************************/
int dati_blocco_frem (n, indx_mod, nb, indx_b)
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
/*
      printf ("blocco %d) :%s: :%s: %d\n",
               i,app,nome_blocco_frem,sizeof(nome_blocco_frem)-1);
*/
      if (strncmp(app, nome_blocco_frem,sizeof(nome_blocco_frem)-1) == 0)
         {
         *indx_b = i;
         break;
         }
      }
   return(0);
}
/*****************************************************************/
/*
 * registra i dati delle funz. remote nelle apposite strutture.   
 * prende in considerazione solo le variabili di ingresso (YI JI)
 * in quanto il blocco FREMFREM non introduce modifiche alla variabile
 */
int presa_dati_fr(int i)
{
int sist;
char *s;

	if ((s = strstr(variabili[i].nome,digital_inp)) != NULL)
		{
		if (!strcmp(variabili[i].nome,s))
			{
			if ((sist = test_sistema_fr(variabili[i].nome)) >= 0)
				leggi_dati_fr(sist,i);
			}
		}

	else if ((s = strstr(variabili[i].nome,digital_out)) != NULL)
      {
      if (!strcmp(variabili[i].nome,s))
         {
         if ((sist = test_sistema_fr(variabili[i].nome)) >= 0)
				;
         }
      }

   else if ((s = strstr(variabili[i].nome,analog_inp)) != NULL)
      {
      if (!strcmp(variabili[i].nome,s))
         {
         if ((sist = test_sistema_fr(variabili[i].nome)) >= 0)
				leggi_dati_fr(sist,i);
         }
      }

   else if ((s = strstr(variabili[i].nome,analog_out)) != NULL)
      {
      if (!strcmp(variabili[i].nome,s))
         {
         if ((sist = test_sistema_fr(variabili[i].nome)) >= 0)
				;
         }
      }

	else
		{
	printf ("var %s non nota\n",variabili[i].nome);
		}
}
/*****************************************************************/
int test_sistema_fr (char *label)
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
int leggi_dati_fr(int  s, int i)
{
int n;
LISTA_FR *l_fr;             /* puntatore di appoggio          */
	
	l_fr = lista_fr+s;
	n = l_fr->nvar;          /* numero variabili del sistema s */
	strcpy (l_fr->frem[n].label, variabili[i].nome);
	strcpy (l_fr->frem[n].descr, variabili[i].descr);
	l_fr->frem[n].addr = variabili[i].addr;

	taglia_descr(l_fr->frem[n].descr);

	l_fr->nvar ++;
	return(0);
}
/*****************************************************************/
int inserisci_sistema_fr (Widget w, int s)
{
int n,i;
LISTA_FR *l_fr;
char app_char[200];

	l_fr = lista_fr + (s-1);
	n = l_fr->nvar;  

	XtUnmanageChild (w);
	for (i=0; i<n; i++)
		{
		sprintf (app_char,"%s %s",l_fr->frem[i].label,
											l_fr->frem[i].descr);
		XmListAddItemUnselected(w,
                  XmStringCreate(app_char,XmSTRING_DEFAULT_CHARSET),
                  0);
		}
	XtManageChild (w);
	return(n);
}
/****************************************************************/
#endif
