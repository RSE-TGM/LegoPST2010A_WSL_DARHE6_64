/**********************************************************************
*
*       C Source:               crea_widget.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 10:17:41 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: crea_widget.c,2 %  (%full_filespec: 1,csrc,crea_widget.c,2 %)";
#endif


/* CREA_WIDGET.C 	file di servizio per TABLES
			Crea tutti gli widget dell'applicativo
   Versione 0.1		16.7.92			Buffo & Calleri  */

#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/StringDefs.h>
#include <Xm/Xm.h>
#include <Xm/Label.h>
#include <Xm/Text.h>
#include <Xm/SeparatoG.h>
#include <Xm/DialogS.h>
#include <Xm/RowColumn.h>
#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/PushB.h>
#include <Xm/MainW.h>
#include <Xm/CascadeB.h>
#include <Xm/BulletinB.h>
#include <Xm/ToggleB.h>
#include <Xm/ScrolledW.h>
#include <Xm/List.h>

#include "tables.h"

/* Variabili esterne dichiarate in tables.c ... */
extern Widget top_level, main_window, menubar, form_widget;
extern Widget radio_box, input_box, output_box;
extern Widget sep1, sep2, w_clear, w_equal;
extern Widget titolo_funzione;
extern Widget atoggles[MAX_TOGGLEB];
extern Widget ainputlabel[MAX_INPUT_VALUE];
extern Widget ainputtext[MAX_INPUT_VALUE];
extern Widget aoutputlabel[MAX_OUTPUT_VALUE];
extern Widget aresultlabel[MAX_OUTPUT_VALUE];
extern Widget aresultframe[MAX_OUTPUT_VALUE];
extern Widget funct_history, function_list, done;
extern Widget in_out_form, info_risultati;

extern float ainputval[];

extern XFontStruct *finfo;
extern XmFontList  fontList;
extern char        *font_name;
extern XmString    stringa_nulla , cstring;

extern Arg args[20];
extern Cardinal nargs;

extern Struct_toggle *tavola_scelta;
extern int num_funzioni;

extern int toggle_premuto;

/*------------------------------------------------------------------*/
/*
 *** void crea_main_window()
creazione della main-window */
void crea_main_window()
{
/* Creazione della main window vera e propria */
   nargs=0;
   XtSetArg(args[nargs],XmNmainWindowMarginHeight,0); nargs++;
   XtSetArg(args[nargs],XmNmainWindowMarginWidth, 0); nargs++;
   XtSetArg(args[nargs], XmNwidth,660); nargs++;
   XtSetArg(args[nargs], XmNheight,570); nargs++;
   main_window = XmCreateMainWindow (top_level,"Main_window",args,nargs);
   XtManageChild (main_window);

/* Creazione della menubar con le relative voci */
   nargs=0;
   XtSetArg(args[nargs],XmNheight,30); nargs++;
   XtSetArg(args[nargs],XmNspacing,60); nargs++;
   XtSetArg(args[nargs],XmNorientation,XmHORIZONTAL); nargs++;
   menubar = XmCreateMenuBar (main_window,"Menubar",args,nargs);
   XtManageChild (menubar);

   componi_menu();

/* Creazione della work region (= form) */
   nargs=0;
   XtSetArg(args[nargs],XmNheight,800); nargs++;
   XtSetArg(args[nargs],XmNwidth, 800); nargs++;
   form_widget = XmCreateForm (main_window,"Form",args,nargs);

/* Completamento della main window */
   XmMainWindowSetAreas(main_window,menubar,NULL,NULL,NULL,form_widget);
/*   XtUnmanageChild (form_widget); */
}

/*------------------------------------------------------------------*/
/*** void componi_menu()
*** Il menu � composto da tre voci (=CascadeButton):

FILE	SELECT		HISTORY
====	======		=======
Quit	H2O		Show
	Combustion	Clear
	 gasses

***/
void componi_menu()
{
   Widget file, select, history;
   Widget pulldown1,pulldown2,pulldown3;
   Widget quit, vapore, gas, show, clear;

/* Creazione del menu FILE */
   pulldown1 = XmCreatePulldownMenu (menubar,"Pulldown1",NULL,0);

   quit = XmCreatePushButton (pulldown1,"Quit",NULL,0);
   XtAddCallback (quit,XmNactivateCallback,quit_tables,NULL);
   XtManageChild (quit);

   nargs=0;
   XtSetArg(args[nargs],XmNtraversalOn,True); nargs++;
   XtSetArg(args[nargs],XmNmnemonic,70); nargs++;
   XtSetArg(args[nargs],XmNsubMenuId,pulldown1); nargs++;
   file = XmCreateCascadeButton (menubar,"File",args,nargs);
   XtManageChild (file);

/* Creazione del menu SELECT */
   pulldown2 = XmCreatePulldownMenu (menubar,"Pulldown2",NULL,0);

   vapore = XmCreatePushButton (pulldown2,"H2O",NULL,0);
   XtAddCallback (vapore,XmNactivateCallback,selez_tavola,(XtPointer)K_VAPORE);
   XtManageChild (vapore);

   nargs=0;
   XtSetArg(args[nargs],XmNsensitive,False); nargs++;
   gas = XmCreatePushButton (pulldown2,"Combustion\ngasses",args,nargs);
   XtAddCallback (gas,XmNactivateCallback,selez_tavola,(XtPointer)K_GAS);
   XtManageChild (gas);

   nargs=0;
   XtSetArg(args[nargs],XmNtraversalOn,True); nargs++;
   XtSetArg(args[nargs],XmNmnemonic,83); nargs++;
   XtSetArg(args[nargs],XmNsubMenuId,pulldown2); nargs++;
   select = XmCreateCascadeButton (menubar,"Select",args,nargs);
   XtManageChild (select);

/* Creazione del menu HISTORY */
   pulldown3 = XmCreatePulldownMenu (menubar,"Pulldown3",NULL,0);

   show = XmCreatePushButton (pulldown3,"Show",NULL,0);
   XtAddCallback(show,XmNactivateCallback,apri_dialog,NULL);
   XtManageChild (show);

   clear = XmCreatePushButton (pulldown3,"Clear",NULL,0);
   XtAddCallback(clear,XmNactivateCallback,svuota_lista,NULL);
   XtManageChild (clear);

   nargs=0;
   XtSetArg(args[nargs],XmNtraversalOn,True); nargs++;
   XtSetArg(args[nargs],XmNmnemonic,72); nargs++;
   XtSetArg(args[nargs],XmNsubMenuId,pulldown3); nargs++;
   history = XmCreateCascadeButton (menubar,"History",args,nargs);
   XtManageChild (history);
}

/*------------------------------------------------------------------*/
/*
 *** void crea_elenco_funzioni()
Aggiorna la work area della main window con i row-column dei toggle-button */
void crea_elenco_funzioni()
{
   int i;

/******************************************************/
/* ROWCOLUMN 1 - Elenco delle funzioni                */
/******************************************************/

/* Creazione della XmRowColumn relativa ai toggles-button */
   nargs= 0;
   XtSetArg(args[nargs], XmNtopAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNtopOffset, 20); nargs++;
   XtSetArg(args[nargs], XmNleftAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNrightAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNmarginHeight, 10); nargs++;
   XtSetArg(args[nargs], XmNmarginWidth, 20); nargs++;
   XtSetArg(args[nargs], XmNradioBehavior, True); nargs++;
   XtSetArg(args[nargs], XmNresizeHeight, True); nargs++;
   XtSetArg(args[nargs], XmNresizeWidth, True); nargs++;
   XtSetArg(args[nargs], XmNresizePolicy, XmRESIZE_ANY); nargs++;
   XtSetArg(args[nargs], XmNspacing, 10); nargs++;
   XtSetArg(args[nargs], XmNorientation, XmVERTICAL); nargs++;
   XtSetArg(args[nargs], XmNpacking, XmPACK_COLUMN); nargs++;
   XtSetArg(args[nargs], XmNnumColumns, 5); nargs++;

   radio_box = XmCreateRowColumn(form_widget, "RadioBox", args, nargs);
   XtManageChild(radio_box);

/* creazione dei toggle-buttons */
   for( i=0; i < num_funzioni; i++ )
   {
      nargs= 0;
      cstring = CREATE_CSTRING(tavola_scelta[i].nome_funzione);
      XtSetArg(args[nargs], XmNlabelString, cstring); nargs++;
      atoggles[i] = XmCreateToggleButton(radio_box, "", args, nargs);
      XtAddCallback(atoggles[i], XmNvalueChangedCallback, toggle_on, (XtPointer)i);
      XtManageChild(atoggles[i]);
      XmStringFree(cstring);
   }
}

/*------------------------------------------------------------------*/
/*
 *** void crea_input_output()
Aggiorna la work area della main window con i row-column dei toggle-button,
input ed output */
void crea_input_output()
{
   int i;
   int max_input, max_output;

   max_input = tavola_scelta[ toggle_premuto ].num_input;
   max_output = tavola_scelta[ toggle_premuto ].num_output;

/******************************************************/
/* FORM DELL'INPUT E DELL'OUTPUT ...                  */
/******************************************************/

   nargs=0;
   XtSetArg(args[nargs], XmNleftAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNrightAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNbottomAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNtopWidget, radio_box); nargs++;
   XtSetArg(args[nargs], XmNtopAttachment, XmATTACH_WIDGET); nargs++;
   in_out_form = XmCreateForm(form_widget,"in_out_form",args,nargs);

/******************************************************/
/* SEPARATOR ...                                      */
/******************************************************/

   nargs=0;
   XtSetArg(args[nargs], XmNleftAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNrightAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNtopAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNtopOffset, 20); nargs++;
   XtSetArg(args[nargs], XmNleftOffset, 5); nargs++;
   XtSetArg(args[nargs], XmNrightOffset, 5); nargs++;
   sep1 = XmCreateSeparatorGadget(in_out_form,"Separatore",args, nargs);
   XtManageChild(sep1);

/******************************************************/
/* LABEL DI DESCRIZIONE FUNZIONE ATTIVATA             */
/******************************************************/

/* Creazione della label di descrizione della funzione attivata  */
   cstring = CREATE_CSTRING(tavola_scelta[toggle_premuto].descr_funzione);
   nargs= 0;
   XtSetArg(args[nargs], XmNtopWidget, sep1); nargs++;
   XtSetArg(args[nargs], XmNtopAttachment, XmATTACH_WIDGET); nargs++;
   XtSetArg(args[nargs], XmNtopOffset, 20); nargs++;
   XtSetArg(args[nargs], XmNleftAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNleftOffset, 100); nargs++;
   XtSetArg(args[nargs], XmNrightAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNrightOffset, 100); nargs++;
   XtSetArg(args[nargs] ,XmNlabelString, cstring ); nargs++;
   titolo_funzione = XmCreateLabel(in_out_form, "Titolo_funzione", args, nargs);
   XtManageChild(titolo_funzione);
   XmStringFree(cstring);

/******************************************************/
/* ROWCOLUMN 2                                        */
/******************************************************/

/* Creazione della XmRowColumn relativa agli ingressi (input). */
   nargs= 0;
   XtSetArg(args[nargs], XmNleftAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNrightAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNtopWidget, titolo_funzione); nargs++;
   XtSetArg(args[nargs], XmNtopAttachment, XmATTACH_WIDGET); nargs++;
   XtSetArg(args[nargs], XmNtopOffset, 20); nargs++;
   XtSetArg(args[nargs], XmNmarginHeight, 10); nargs++;
   XtSetArg(args[nargs], XmNmarginWidth, 20); nargs++;
   XtSetArg(args[nargs], XmNresizeWidth, True); nargs++;
   XtSetArg(args[nargs], XmNresizeHeight, True); nargs++;
   XtSetArg(args[nargs], XmNadjustMargin, False); nargs++;
   XtSetArg(args[nargs], XmNspacing, 10); nargs++;
   XtSetArg(args[nargs], XmNorientation, XmHORIZONTAL); nargs++;
   XtSetArg(args[nargs], XmNpacking, XmPACK_COLUMN); nargs++;
   XtSetArg(args[nargs], XmNnumColumns, max_input ); nargs++;
/*  XtSetArg(args[nargs], XmNresizePolicy, XmRESIZE_NONE); nargs++; */

   input_box = XmCreateRowColumn(in_out_form, "RowColumn", args, nargs);
   XtManageChild(input_box);

   for( i=0; i < max_input ; i++ )
   {
      char strval[20];

   /* label descrizione input */
      cstring = CREATE_CSTRING(tavola_scelta[toggle_premuto].nomi_input[i]);
      nargs= 0;
      XtSetArg(args[nargs], XmNlabelString, cstring); nargs++;
      ainputlabel[i] = XmCreateLabel(input_box, "Label", args, nargs);
      XtManageChild(ainputlabel[i]);
      XmStringFree(cstring);

   /* text di inserimento dati */
      sprintf(strval,"%g", ainputval[i]);
      nargs=0;
      XtSetArg(args[nargs], XmNeditMode, XmSINGLE_LINE_EDIT); nargs++;
      XtSetArg(args[nargs], XmNcolumns, MAX_COL_TESTO); nargs++;
      XtSetArg(args[nargs], XmNmaxLength,  MAX_COL_TESTO); nargs++;
      XtSetArg(args[nargs], XmNwidth, 100); nargs++;
      XtSetArg(args[nargs], XmNheight, 20); nargs++;
      XtSetArg(args[nargs], XmNresizeHeight, False); nargs++;
      XtSetArg(args[nargs], XmNvalue, strval); nargs++;
      ainputtext[i] = XmCreateText(input_box, "Text", args, nargs);
      XtAddCallback(ainputtext[i], XmNactivateCallback, next_text, (XtPointer)i);
      XtAddCallback(ainputtext[i], XmNmodifyVerifyCallback, text_verify, (XtPointer)i);
      XtManageChild(ainputtext[i]);
   }

/******************************************************/
/* PUSH-BUTTONS '=' e 'Clear'                         */
/******************************************************/
   cstring = CREATE_CSTRING(PB_EQUAL);
   nargs=0;
   XtSetArg(args[nargs], XmNrightAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNrightOffset, 10); nargs++;
   XtSetArg(args[nargs], XmNtopWidget, input_box); nargs++;
   XtSetArg(args[nargs], XmNtopAttachment, XmATTACH_WIDGET); nargs++;
   XtSetArg(args[nargs], XmNtopOffset, 10); nargs++;
   XtSetArg(args[nargs], XmNlabelString, cstring); nargs++;
   w_equal = XmCreatePushButton(in_out_form,PB_EQUAL,args, nargs);
   XtAddCallback(w_equal, XmNactivateCallback, display_results, (XtPointer)i);
   XtManageChild(w_equal);
   XmStringFree(cstring);

   cstring = CREATE_CSTRING(PB_CLEAR);
   nargs=0;
   XtSetArg(args[nargs], XmNrightWidget, w_equal); nargs++;
   XtSetArg(args[nargs], XmNrightAttachment, XmATTACH_WIDGET); nargs++;
   XtSetArg(args[nargs], XmNrightOffset, 10); nargs++;
   XtSetArg(args[nargs], XmNtopWidget, input_box); nargs++;
   XtSetArg(args[nargs], XmNtopAttachment, XmATTACH_WIDGET); nargs++;
   XtSetArg(args[nargs], XmNtopOffset, 10); nargs++;
   XtSetArg(args[nargs], XmNlabelString, cstring); nargs++;
   w_clear = XmCreatePushButton(in_out_form,PB_CLEAR,args, nargs);
   XtAddCallback(w_clear, XmNactivateCallback, clear_input, NULL);
   XtManageChild(w_clear);
   XmStringFree(cstring);

/******************************************************/
/* SEPARATOR ...                                      */
/******************************************************/

   nargs=0;
   XtSetArg(args[nargs], XmNleftAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNrightAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNtopWidget, w_equal); nargs++;
   XtSetArg(args[nargs], XmNtopAttachment, XmATTACH_WIDGET); nargs++;
   XtSetArg(args[nargs], XmNtopOffset, 20); nargs++;
   XtSetArg(args[nargs], XmNleftOffset, 5); nargs++;
   XtSetArg(args[nargs], XmNrightOffset, 5); nargs++;
   sep2 = XmCreateSeparatorGadget(in_out_form,"Separatore",args, nargs);
   XtManageChild(sep2);

/******************************************************/
/* ROWCOLUMN 3                                        */
/******************************************************/

/* Creazione della XmRowColumn relativa alle uscite (output) */
   nargs= 0;
   XtSetArg(args[nargs], XmNleftAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNrightAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNtopWidget, sep2); nargs++;
   XtSetArg(args[nargs], XmNtopAttachment, XmATTACH_WIDGET); nargs++;
   XtSetArg(args[nargs], XmNtopOffset, 20); nargs++;
   XtSetArg(args[nargs], XmNadjustLast, False); nargs++;
   XtSetArg(args[nargs], XmNmarginHeight, 10); nargs++;
   XtSetArg(args[nargs], XmNmarginWidth, 20); nargs++;
   XtSetArg(args[nargs], XmNspacing, 10); nargs++;
   XtSetArg(args[nargs], XmNorientation, XmHORIZONTAL); nargs++;
   XtSetArg(args[nargs], XmNpacking, XmPACK_COLUMN); nargs++;
   XtSetArg(args[nargs], XmNnumColumns, max_output); nargs++;

   output_box = XmCreateRowColumn(in_out_form, "RowColumn", args, nargs);
   XtManageChild(output_box);

/* label di visualizzazione risultati */
   for( i=0; i < max_output; i++ )
   {
      cstring = CREATE_CSTRING(tavola_scelta[toggle_premuto].nomi_output[i]);
      nargs= 0;
      XtSetArg(args[nargs], XmNlabelString, cstring); nargs++;
      aoutputlabel[i] = XmCreateLabel(output_box, "Label", args, nargs);
      XtManageChild(aoutputlabel[i]);
      XmStringFree(cstring);

      nargs=0;
      XtSetArg(args[nargs], XmNwidth, 100); nargs++;
      aresultframe[i] = XmCreateFrame(output_box, "Frame", args, nargs);
      XtManageChild(aresultframe[i]);

      nargs=0;
      XtSetArg(args[nargs], XmNrecomputeSize, True); nargs++;
      XtSetArg(args[nargs], XmNwidth, 100); nargs++;
      XtSetArg(args[nargs], XmNlabelString, stringa_nulla ); nargs++;
      aresultlabel[i] = XmCreateLabel(aresultframe[i], "Label", args, nargs);
      XtManageChild(aresultlabel[i]);
   }

/******************************************************/
/* LABEL DI INFORMAZIONE SUI RISULTATI		      */
/******************************************************/

/* Creazione della label che informa se i risultati sono sballati */
   nargs= 0;
   XtSetArg(args[nargs], XmNbottomAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNleftAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNrightAttachment, XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs], XmNtopAttachment, XmATTACH_WIDGET); nargs++;
   XtSetArg(args[nargs], XmNbottomOffset, 10); nargs++;
   XtSetArg(args[nargs], XmNtopWidget, output_box); nargs++;
   XtSetArg(args[nargs], XmNtopOffset, 20); nargs++;
   XtSetArg(args[nargs] ,XmNlabelString, stringa_nulla ); nargs++;
   info_risultati = XmCreateLabel(in_out_form, "Info_risultati", args, nargs);
   XtManageChild(info_risultati);

   XtManageChild(in_out_form);
}

/*------------------------------------------------------------------*/
/*** void crea_dialog()
La dialog box contiene una history delle funzioni di cui
e' stato richiesto il calcolo.
Viene creata all'avviamento del programma per ricevere 
gli elementi in tempo reale. Viene poi visualizzata su
richiesta dell'utente. */
void crea_dialog()
{

/* Creazione della dialog box */
   cstring = CREATE_CSTRING(DIALOG_TITLE);
   nargs=0;
   XtSetArg(args[nargs],XmNautoUnmanage,True); nargs++;
   XtSetArg(args[nargs],XmNnoResize,False); nargs++;
   XtSetArg(args[nargs],XmNdialogStyle,XmDIALOG_MODELESS); nargs++;
   XtSetArg(args[nargs],XmNdialogTitle,cstring); nargs++;
   XtSetArg(args[nargs],XmNhorizontalSpacing,10); nargs++;
   XtSetArg(args[nargs],XmNverticalSpacing,10); nargs++;
/*   XtSetArg(args[nargs],XmNheight,280); nargs++; */
   XtSetArg(args[nargs],XmNwidth,770); nargs++;
   funct_history = XmCreateFormDialog(top_level,"Funct_history",args,nargs);
   XmStringFree(cstring);

/* Creazione della scroll list */
   nargs=0;
   XtSetArg(args[nargs],XmNleftAttachment,XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs],XmNrightAttachment,XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs],XmNtopAttachment,XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs],XmNtraversalOn,False); nargs++;
   XtSetArg(args[nargs],XmNlistSizePolicy,XmRESIZE_IF_POSSIBLE); nargs++;
   XtSetArg(args[nargs],XmNscrollBarDisplayPolicy,XmAS_NEEDED); nargs++;
   XtSetArg(args[nargs],XmNvisibleItemCount,VISIBLE_ITEMS); nargs++;
   function_list = XmCreateScrolledList (funct_history,"Function_list",
       				         args,nargs);
   XtManageChild (function_list);

/* Creazione del push button di UnManage */
   nargs=0;
   XtSetArg(args[nargs],XmNrightAttachment,XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs],XmNbottomAttachment,XmATTACH_FORM); nargs++;
   XtSetArg(args[nargs],XmNbottomOffset,20); nargs++;
   XtSetArg(args[nargs],XmNtopAttachment,XmATTACH_WIDGET); nargs++;
   XtSetArg(args[nargs],XmNtopWidget, function_list); nargs++;
   XtSetArg(args[nargs],XmNtopOffset, 20); nargs++;
   done = XmCreatePushButton (funct_history,"Done",args,nargs);
   XtManageChild (done);
}
