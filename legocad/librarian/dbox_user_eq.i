! UIMX ascii 2.0 key: 1065                                                      

*dbox_user_eq.class: dialogShell
*dbox_user_eq.parent: NO_PARENT
*dbox_user_eq.static: true
*dbox_user_eq.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo dbox_user_eq.i\
   tipo \
   release 2.22\
   data 5/9/95\
   reserved @(#)dbox_user_eq.i	2.22\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#endif\
/****************************************************************/\
/* INCLUDE FILES						*/\
/****************************************************************/\
\
#include <stdio.h>\
#include <Xm/Xm.h>\
#include <Xm/Label.h>\
#include <Xm/Text.h>\
\
#include "definizioni.h"\
\
#ifndef LIBUTILX\
#include <libutilx.h>\
#define LIBUTILX\
#endif\
\
/****************************************************************/\
/* VARIABILI GLOBALI ESTERNE					*/\
/****************************************************************/\
\
extern Boolean non_salvato;\
\
extern Arg args[20];\
extern Cardinal argcount;\
\
extern Widget UxTopLevel;\
extern Dialog_geometry geom_attention;\
extern Widget attention_wdg;\
\
extern int num_var_stato;\
extern int num_var_algebriche;\
extern int num_var_ingresso;\
extern char *str_signeq[], *str_uniteq[], *str_cosnor[];\
\
extern XmFontList fontList;\
\
/****************************************************************/\
/* VARIABILI GLOBALI      					*/\
/****************************************************************/\
\
Boolean dbox_usereq_managed = False;\
\
Widget *text_signeq, *text_uniteq, *text_cosnor;
*dbox_user_eq.ispecdecl:
*dbox_user_eq.funcdecl: swidget create_dbox_usereq()\

*dbox_user_eq.funcname: create_dbox_usereq
*dbox_user_eq.funcdef: "swidget", "<create_dbox_usereq>(%)"
*dbox_user_eq.icode: Dimension height;
*dbox_user_eq.fcode: /* Visualizzazione text per l'input */\
text_user_eq();\
\
UxPopupInterface (rtrn, no_grab);\
dbox_usereq_managed = True;\
\
/* Controllo per ridimensionamento form delle label */\
/* per l'allineamento con le colonne di text */\
XtAddEventHandler(UxGetWidget(form_labels_eq), StructureNotifyMask, False,\
                  cambio_dimensione, NULL);\
\
/* Dimensionamento dell'altezza della form dei text */\
set_something (UxGetWidget(form_eq_scroll),XmNheight,\
               ALTEZZA_TEXT*(num_var_stato+num_var_algebriche)+\
               SPAZIO_FRA_SEZIONI*3);\
\
return(rtrn);\

*dbox_user_eq.auxdecl: /*** text_user_eq()\
 ***\
 ***   Descrizione:\
 ***     Compone le righe di label e text per la caratterizzazione\
 ***     delle equazioni del nuovo modulo.\
 ***     Abilitata dopo le definizioni per il nuovo modulo.\
 ***/\
text_user_eq()\
{\
   int i;\
   XmString cstring;\
   Position posy = 10;\
\
/* Allocazione della memoria per i text-widget relativi a: */\
/* significato, unita di misura e costante di normalizzazione delle equazioni */\
   text_signeq = (Widget *) XtCalloc(num_var_stato+num_var_algebriche,\
                                     sizeof(Widget));\
 \
   text_uniteq = (Widget *) XtCalloc(num_var_stato+num_var_algebriche,\
                                     sizeof(Widget));\
\
   text_cosnor = (Widget *) XtCalloc(num_var_stato+num_var_algebriche,\
                                     sizeof(Widget));\
\
/****************************************/\
/* Riempimento righe equazioni          */\
/****************************************/\
   for (i=0; i<num_var_stato+num_var_algebriche; i++)\
   {\
   /* Label EQUATION... */\
      if ( i<num_var_stato )\
         crea_label_eq ("STATE EQUATION # ",i+1,1,29,posy);\
      else\
         crea_label_eq ("ALGEBRAIC EQUATION # ",i+1,1,29,posy);\
\
   /* Text DESCRIPTION */\
      crea_texts_eq (&text_signeq[i],30,69,0,posy,50);\
      if (str_signeq[i] != NULL)\
         XmTextSetString(text_signeq[i], str_signeq[i]);\
\
   /* Text UNIT */\
      crea_texts_eq (&text_uniteq[i],70,79,0,posy,6);\
      if (str_uniteq[i] != NULL)\
         XmTextSetString(text_uniteq[i], str_uniteq[i]);\
\
   /* Text NORMALIZATION... */\
      crea_texts_eq (&text_cosnor[i],80,100,10,posy,8);\
      if (str_cosnor[i] != NULL)\
         XmTextSetString(text_cosnor[i], str_cosnor[i]);\
\
      posy += 35;\
   }\
\
   posy += SPAZIO_FRA_SEZIONI;\
}\
\
/*************************************************************/\
/***\
 *** crea_label_eq (stringa,num_eq,leftPos,rightPos,posy)\
 ***   Parametri:\
 ***      char *stringa : stringa da visualizzare\
 ***      int num_eq : numero equazione\
 ***      int leftPos : left position\
 ***      int rightPos : right position\
 ***      Position posy : posizione y della label\
 ***\
 ***   Descrizione:\
 ***      Crea la label per intestare i text relativi al significato delle\
 ***      equazioni.\
 ***/\
crea_label_eq (stringa,num_eq,leftPos,rightPos,posy)\
char *stringa;\
int num_eq;\
int leftPos, rightPos;\
Position posy;\
{\
   Widget wdg;\
   char temp[50];\
   XmString cstring;\
\
   sprintf (temp,"%s%d",stringa,num_eq);\
   cstring = CREATE_CSTRING (temp);\
\
   argcount = 0;\
   XtSetArg (args[argcount],XmNy,posy); argcount++;\
   XtSetArg (args[argcount],XmNheight,ALTEZZA_TEXT); argcount++;\
   XtSetArg (args[argcount],XmNleftAttachment,XmATTACH_POSITION); argcount++;\
   XtSetArg (args[argcount],XmNrightAttachment,XmATTACH_POSITION); argcount++;\
   XtSetArg (args[argcount],XmNleftPosition,leftPos); argcount++;\
   XtSetArg (args[argcount],XmNrightPosition,rightPos); argcount++;\
   XtSetArg (args[argcount],XmNlabelString,cstring); argcount++;\
   XtSetArg (args[argcount],XmNalignment,XmALIGNMENT_BEGINNING); argcount++;\
   wdg = XmCreateLabel (UxGetWidget(form_eq_scroll),"DboxUserEq",\
                         args,argcount);\
   XtManageChild (wdg);\
\
   XmStringFree (cstring);\
}\
\
\
/*************************************************************/\
/***\
 *** crea_texts_eq (wdg,leftPos,rightPos,rightOff,posy,num_col)\
 ***   Parametri:\
 ***      Widget *wdg : text-widget creato\
 ***      int leftPos : left position\
 ***      int rightPos : right position\
 ***      int rightOff : right offset\
 ***      Position posy : posizione y della label\
 ***      int num_col : numero colonne del text\
 ***\
 ***   Descrizione:\
 ***      Crea i text widget relativi al significato delle equazioni, unita di\
 ***      misura e costante di normalizzazione.\
 ***/\
crea_texts_eq (wdg,leftPos,rightPos,rightOff,posy,num_col)\
Widget *wdg;\
int leftPos, rightPos, rightOff;\
Position posy;\
int num_col;\
{\
\
   argcount = 0;\
   XtSetArg (args[argcount],XmNy,posy); argcount++;\
   XtSetArg (args[argcount],XmNheight,ALTEZZA_TEXT); argcount++;\
   XtSetArg (args[argcount],XmNleftAttachment,XmATTACH_POSITION); argcount++;\
   XtSetArg (args[argcount],XmNrightAttachment,XmATTACH_POSITION); argcount++;\
   XtSetArg (args[argcount],XmNleftPosition,leftPos); argcount++;\
   XtSetArg (args[argcount],XmNrightPosition,rightPos); argcount++;\
   XtSetArg (args[argcount],XmNrightOffset,rightOff); argcount++;\
   XtSetArg (args[argcount],XmNmaxLength,num_col);argcount++;\
   XtSetArg (args[argcount],XmNfontList,fontList);argcount++;\
   *wdg = XmCreateText (UxGetWidget(form_eq_scroll),"DboxUserEq",\
                         args,argcount);\
   XtAddCallback(*wdg, XmNmodifyVerifyCallback, text_maius_callback, NULL);\
   XtManageChild (*wdg);\
}\
\
/*------------------------------------------------------------------*/\
/*** void cambio_dimensione(w, ev, params, num_params)\
 *** Ad ogni ridimensionamento della finestra, legge le nuove\
 *** dimensioni (LARGHEZZA) della form delle label di intestazione\
 *** e le passa alla form all'interno della scrolled window dei text.\
 ***\
 ***/\
void cambio_dimensione (w, client_data, ev, boh)\
Widget w;\
char *client_data;\
XEvent *ev;\
Boolean boh;\
{\
   Dimension width;\
\
    get_something( UxGetWidget(form_labels_eq), XmNwidth, &width );\
    set_something( UxGetWidget(form_eq_scroll), XmNwidth, width-20 );\
}\
\
\
/*** memo_textD1(flag)\
 ***   Parametri:\
 ***     Boolean flag : indica se la window deve sparire o meno.\
memorizza il contenuto dei text-widget della window dei dati nelle\
variabili globali str_dichMOD, str_codMOD e str_resMOD */\
memo_textD1(flag)\
Boolean flag;\
{\
   int i;\
\
   non_salvato = True;\
\
   for ( i=0 ; i<num_var_stato+num_var_algebriche ; i++ )\
   {\
       XtFree(str_signeq[i]);\
       str_signeq[i]=XmTextGetString(text_signeq[i]);\
\
       XtFree(str_uniteq[i]);\
       str_uniteq[i]=XmTextGetString(text_uniteq[i]);\
\
       XtFree(str_cosnor[i]);\
       str_cosnor[i]=XmTextGetString(text_cosnor[i]);\
   }\
\
   if (flag)\
   {\
      UxDestroySwidget(dbox_user_eq);\
      dbox_usereq_managed = False;    \
      XtFree(text_signeq);\
      XtFree(text_uniteq);\
      XtFree(text_cosnor);\
   }\
}\
\
\

*dbox_user_eq.name: dbox_user_eq
*dbox_user_eq.x: 160
*dbox_user_eq.y: 440
*dbox_user_eq.width: 800
*dbox_user_eq.height: 530
*dbox_user_eq.title: "D1 EQUATIONS SECTION - NEWMOD "

*form_user_eq.class: form
*form_user_eq.parent: dbox_user_eq
*form_user_eq.static: true
*form_user_eq.name: form_user_eq
*form_user_eq.unitType: "pixels"
*form_user_eq.x: 544
*form_user_eq.y: 170
*form_user_eq.width: 800
*form_user_eq.height: 530
*form_user_eq.autoUnmanage: "false"

*form_labels_eq.class: form
*form_labels_eq.parent: form_user_eq
*form_labels_eq.static: true
*form_labels_eq.name: form_labels_eq
*form_labels_eq.unitType: "pixels"
*form_labels_eq.x: 0
*form_labels_eq.y: 0
*form_labels_eq.width: 760
*form_labels_eq.height: 50
*form_labels_eq.bottomAttachment: "attach_none"
*form_labels_eq.leftAttachment: "attach_form"
*form_labels_eq.leftOffset: 20
*form_labels_eq.rightAttachment: "attach_form"
*form_labels_eq.rightOffset: 20
*form_labels_eq.topAttachment: "attach_form"
*form_labels_eq.topOffset: 0

*descr_eq_label.class: label
*descr_eq_label.parent: form_labels_eq
*descr_eq_label.static: true
*descr_eq_label.name: descr_eq_label
*descr_eq_label.x: 240
*descr_eq_label.y: 20
*descr_eq_label.width: 130
*descr_eq_label.height: 20
*descr_eq_label.alignment: "alignment_beginning"
*descr_eq_label.labelString: "Description"
*descr_eq_label.topOffset: 0
*descr_eq_label.bottomAttachment: "attach_form"
*descr_eq_label.bottomOffset: 5
*descr_eq_label.topAttachment: "attach_none"
*descr_eq_label.leftAttachment: "attach_position"
*descr_eq_label.leftOffset: 0
*descr_eq_label.leftPosition: 30

*unit_eq_label.class: label
*unit_eq_label.parent: form_labels_eq
*unit_eq_label.static: true
*unit_eq_label.name: unit_eq_label
*unit_eq_label.x: 390
*unit_eq_label.y: 20
*unit_eq_label.width: 60
*unit_eq_label.height: 20
*unit_eq_label.alignment: "alignment_beginning"
*unit_eq_label.labelString: "Unit"
*unit_eq_label.topOffset: 0
*unit_eq_label.bottomAttachment: "attach_form"
*unit_eq_label.bottomOffset: 5
*unit_eq_label.topAttachment: "attach_none"
*unit_eq_label.leftAttachment: "attach_position"
*unit_eq_label.leftOffset: 0
*unit_eq_label.leftPosition: 70
*unit_eq_label.rightAttachment: "attach_position"
*unit_eq_label.rightPosition: 79

*norm_eq_label.class: label
*norm_eq_label.parent: form_labels_eq
*norm_eq_label.static: true
*norm_eq_label.name: norm_eq_label
*norm_eq_label.x: 510
*norm_eq_label.y: 20
*norm_eq_label.width: 150
*norm_eq_label.height: 40
*norm_eq_label.alignment: "alignment_beginning"
*norm_eq_label.labelString: "Normalization \nconstant"
*norm_eq_label.topOffset: 0
*norm_eq_label.bottomAttachment: "attach_form"
*norm_eq_label.bottomOffset: 5
*norm_eq_label.topAttachment: "attach_none"
*norm_eq_label.leftAttachment: "attach_position"
*norm_eq_label.leftOffset: 0
*norm_eq_label.leftPosition: 80

*ok_eq_pb.class: pushButton
*ok_eq_pb.parent: form_user_eq
*ok_eq_pb.static: true
*ok_eq_pb.name: ok_eq_pb
*ok_eq_pb.x: 20
*ok_eq_pb.y: 480
*ok_eq_pb.width: 90
*ok_eq_pb.height: 30
*ok_eq_pb.bottomAttachment: "attach_form"
*ok_eq_pb.bottomOffset: 10
*ok_eq_pb.leftAttachment: "attach_form"
*ok_eq_pb.leftOffset: 20
*ok_eq_pb.rightAttachment: "attach_none"
*ok_eq_pb.topAttachment: "attach_none"
*ok_eq_pb.topOffset: 0
*ok_eq_pb.labelString: "Ok"
*ok_eq_pb.activateCallback: memo_textD1(True);

*apply_eq_pb.class: pushButton
*apply_eq_pb.parent: form_user_eq
*apply_eq_pb.static: true
*apply_eq_pb.name: apply_eq_pb
*apply_eq_pb.x: 130
*apply_eq_pb.y: 480
*apply_eq_pb.width: 90
*apply_eq_pb.height: 30
*apply_eq_pb.bottomAttachment: "attach_form"
*apply_eq_pb.bottomOffset: 10
*apply_eq_pb.leftAttachment: "attach_widget"
*apply_eq_pb.leftOffset: 20
*apply_eq_pb.leftWidget: "ok_eq_pb"
*apply_eq_pb.rightAttachment: "attach_none"
*apply_eq_pb.topAttachment: "attach_none"
*apply_eq_pb.topOffset: 0
*apply_eq_pb.labelString: "Apply"
*apply_eq_pb.activateCallback: memo_textD1(False);

*cancel_eq_pb.class: pushButton
*cancel_eq_pb.parent: form_user_eq
*cancel_eq_pb.static: true
*cancel_eq_pb.name: cancel_eq_pb
*cancel_eq_pb.x: 240
*cancel_eq_pb.y: 480
*cancel_eq_pb.width: 90
*cancel_eq_pb.height: 30
*cancel_eq_pb.bottomAttachment: "attach_form"
*cancel_eq_pb.bottomOffset: 10
*cancel_eq_pb.leftAttachment: "attach_widget"
*cancel_eq_pb.leftOffset: 20
*cancel_eq_pb.rightAttachment: "attach_none"
*cancel_eq_pb.topAttachment: "attach_none"
*cancel_eq_pb.topOffset: 0
*cancel_eq_pb.leftWidget: "apply_eq_pb"
*cancel_eq_pb.activateCallback: {\
UxDestroySwidget(dbox_user_eq);\
dbox_usereq_managed = False;\
\
XtFree(text_signeq);\
XtFree(text_uniteq);\
XtFree(text_cosnor);\
}
*cancel_eq_pb.labelString: "Cancel"

*scrolledWindow11.class: scrolledWindow
*scrolledWindow11.parent: form_user_eq
*scrolledWindow11.static: true
*scrolledWindow11.name: scrolledWindow11
*scrolledWindow11.scrollingPolicy: "automatic"
*scrolledWindow11.unitType: "pixels"
*scrolledWindow11.x: 20
*scrolledWindow11.y: 50
*scrolledWindow11.width: 660
*scrolledWindow11.height: 420
*scrolledWindow11.bottomAttachment: "attach_widget"
*scrolledWindow11.bottomOffset: 10
*scrolledWindow11.bottomWidget: "ok_eq_pb"
*scrolledWindow11.leftAttachment: "attach_form"
*scrolledWindow11.leftOffset: 20
*scrolledWindow11.rightAttachment: "attach_form"
*scrolledWindow11.rightOffset: 20
*scrolledWindow11.topAttachment: "attach_widget"
*scrolledWindow11.topOffset: 0
*scrolledWindow11.topWidget: "form_labels_eq"

*form_eq_scroll.class: form
*form_eq_scroll.parent: scrolledWindow11
*form_eq_scroll.static: true
*form_eq_scroll.name: form_eq_scroll
*form_eq_scroll.unitType: "pixels"
*form_eq_scroll.x: 0
*form_eq_scroll.y: -2
*form_eq_scroll.width: 760
*form_eq_scroll.height: 500

