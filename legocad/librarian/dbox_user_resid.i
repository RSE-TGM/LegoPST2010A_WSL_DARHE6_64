! UIMX ascii 2.0 key: 9898                                                      

*dbox_user_resid.class: dialogShell
*dbox_user_resid.parent: NO_PARENT
*dbox_user_resid.static: true
*dbox_user_resid.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo dbox_user_resid.i\
   tipo \
   release 2.22\
   data 5/9/95\
   reserved @(#)dbox_user_resid.i	2.22\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#endif\
/****************************************************************/\
/* INCLUDE FILES						*/\
/****************************************************************/\
\
#include <stdio.h>\
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
extern XmFontList fontList;\
\
extern num_var_stato, num_var_algebriche;\
extern char *str_dichMOD, *str_codMOD, *str_resMOD[];\
\
/****************************************************************/\
/* VARIABILI GLOBALI 						*/\
/****************************************************************/\
\
Boolean dbox_userresid_managed = False;\
\
Widget *text_residui;
*dbox_user_resid.ispecdecl:
*dbox_user_resid.funcdecl: swidget create_dbox_userresid()\

*dbox_user_resid.funcname: create_dbox_userresid
*dbox_user_resid.funcdef: "swidget", "<create_dbox_userresid>(%)"
*dbox_user_resid.icode: Dimension height;
*dbox_user_resid.fcode: /* Visualizzazione text per l'input */\
text_user_resid (&height);\
\
UxPopupInterface (rtrn, no_grab);\
dbox_userresid_managed = True;\
\
/* Dimensionamento dell'altezza della form dei text */\
set_something (UxGetWidget(resid_resid_form),XmNheight,height);\
\
/* Aggiorna i text dichiarazione e codice */\
if ( str_dichMOD != NULL )\
   XmTextSetString(UxGetWidget(resid_decl_scrolledText),str_dichMOD);\
\
if ( str_codMOD != NULL )\
   XmTextSetString(UxGetWidget(resid_code_scrolledText),str_codMOD);\
\
return(rtrn);\

*dbox_user_resid.auxdecl: /*** text_user_resid (form_height)\
 ***   Parametri:\
 ***     Dimension *form_height: dimensione della form in altezza (uscita)\
 ***\
 ***   Descrizione:\
 ***     Compone le righe di label e text per la caratterizzazione\
 ***     dei residui delle equazioni del nuovo modulo.\
 ***     Abilitata dopo le definizioni per il nuovo modulo.\
 ***/\
text_user_resid (form_height)\
Dimension *form_height;\
{\
   int i;\
   Position posy = 10;\
\
/* Allocazione della memoria per i text-widget dei residui */\
   text_residui = (Widget *) XtCalloc(num_var_stato+num_var_algebriche,\
				      sizeof(Widget));\
\
/**********************************************************************/\
/* Riempimento righe residui equazioni di uscita (stato e algebriche) */\
/**********************************************************************/\
   for (i=0; i<num_var_stato+num_var_algebriche; i++)\
   {\
   /* Label RN ( ) */\
      crea_label_resid (i+1,1,posy);\
\
   /* Text Residui */\
      crea_texts_resid (&text_residui[i],15,posy,65);\
      if (str_resMOD[i] != NULL)\
         XmTextSetString(text_residui[i],str_resMOD[i]);\
\
      posy += ALTEZZA_LABEL * TEXT_FORTRAN_LINES + 10;\
   }\
\
   *form_height = posy;\
}\
\
/*************************************************************/\
/***\
 *** crea_label_resid (num_resid,leftPos,posy)\
 ***   Parametri:\
 ***      int num_resid : indice del residuo\
 ***      int leftPos : left position\
 ***      Position posy : posizione y della label\
 ***\
 ***   Descrizione:\
 ***      Crea la label di intestazione dei residui.\
 ***\
 ***/\
crea_label_resid (num_resid,leftPos,posy)\
int num_resid;\
int leftPos;\
Position posy;\
{\
   Widget wdg;\
   char temp[20];\
   XmString cstring;\
\
   sprintf (temp,"RN (%d) = ",num_resid);\
   cstring = CREATE_CSTRING (temp);\
\
   argcount = 0;\
   XtSetArg (args[argcount],XmNy,posy); argcount++;\
   XtSetArg (args[argcount],XmNheight,ALTEZZA_TEXT); argcount++;\
   XtSetArg (args[argcount],XmNleftAttachment,XmATTACH_POSITION); argcount++;\
   XtSetArg (args[argcount],XmNleftPosition,leftPos); argcount++;\
   XtSetArg (args[argcount],XmNlabelString,cstring); argcount++;\
   XtSetArg (args[argcount],XmNalignment,XmALIGNMENT_BEGINNING); argcount++;\
   wdg = XmCreateLabel (UxGetWidget(resid_resid_form),"DboxUserResid",\
                         args,argcount);\
   XtManageChild (wdg);\
\
   XmStringFree (cstring);\
}\
\
/*************************************************************/\
/***\
 *** crea_texts_resid (wdg,leftPos,posy,num_col)\
 ***   Parametri:\
 ***     Widget *wdg : text-widget creato (uscita)\
 ***     int leftPos : left position\
 ***     Position posy : posizione y del text-widget.\
 ***     int num_col : numero colonne del text-widget.\
 ***\
 ***   Descrizione:\
 ***     Crea i text per l'inserimento del Fortran relativo ai residui\
 ***     delle equazioni.\
 ***     Si tratta di scrolledTextWidget MULTILINE (5 righe) da 65 caratteri\
 ***     che devono contenere le istruzioni Fortran da colonna 7 a 72.\
 ***     Per le eventuali istruzioni comprese tra la riga 2 e la 5, il\
 ***     generatore di Fortran si preoccupa di porre un simbolo di\
 ***     continuazione ('$') a colonna 6.\
 ***/\
crea_texts_resid (wdg,leftPos,posy,num_col)\
Widget *wdg;\
int leftPos;\
Position posy;\
int num_col;\
{\
   argcount = 0;\
   XtSetArg (args[argcount],XmNheight,ALTEZZA_LABEL*TEXT_FORTRAN_LINES);argcount++;\
   XtSetArg (args[argcount],XmNresizeHeight,False);argcount++;\
   XtSetArg (args[argcount],XmNresizeWidth, False);argcount++;\
   XtSetArg (args[argcount],XmNy,posy); argcount++;\
   XtSetArg (args[argcount],XmNcolumns,num_col);argcount++;\
   XtSetArg (args[argcount],XmNrows,TEXT_FORTRAN_LINES);argcount++;\
   XtSetArg (args[argcount],XmNeditMode,XmMULTI_LINE_EDIT);argcount++;\
   XtSetArg (args[argcount],XmNeditable,True);argcount++;\
   XtSetArg (args[argcount],XmNleftAttachment,XmATTACH_POSITION); argcount++;\
   XtSetArg (args[argcount],XmNleftPosition,leftPos); argcount++;\
   XtSetArg (args[argcount],XmNrightAttachment,XmATTACH_FORM); argcount++;\
   XtSetArg (args[argcount],XmNrightOffset,10); argcount++;\
   XtSetArg (args[argcount],XmNfontList,fontList); argcount++;\
   *wdg = XmCreateScrolledText (UxGetWidget(resid_resid_form),"DboxUserEq",\
                                args,argcount);\
   XtAddCallback(*wdg, XmNmodifyVerifyCallback, text_maius_callback, NULL);\
   XtManageChild (*wdg);\
}\
\
/*** memo_textMOD(flag)\
 ***   Parametri:\
 ***     Boolean flag : indica se la window deve sparire o meno.\
 ***\
 ***   Descrizione:\
 ***     memorizza il contenuto dei text-widget della window dei dati nelle\
 ***     variabili globali str_dichMOD, str_codMOD e str_resMOD\
 ***/\
memo_textMOD(flag)\
Boolean flag;\
{\
   int i;\
\
   non_salvato = True;\
\
/* Dealloca la memoria precedentemente allocata da XmTextGetString() */\
   XtFree( str_dichMOD );\
   XtFree( str_codMOD );\
\
   str_dichMOD = XmTextGetString(UxGetWidget(resid_decl_scrolledText));\
   str_codMOD = XmTextGetString(UxGetWidget(resid_code_scrolledText));\
\
   for ( i=0 ; i<num_var_stato+num_var_algebriche ; i++ )\
   {\
       XtFree(str_resMOD[i]);\
       str_resMOD[i]=XmTextGetString(text_residui[i]);\
   }\
\
   if (flag)\
   {\
      UxDestroySwidget(dbox_user_resid);\
      dbox_userresid_managed = False;    \
      XtFree(text_residui);\
   }\
}\

*dbox_user_resid.name: dbox_user_resid
*dbox_user_resid.x: 150
*dbox_user_resid.y: 560
*dbox_user_resid.width: 700
*dbox_user_resid.height: 750
*dbox_user_resid.geometry: "+230+280"
*dbox_user_resid.title: "RESIDUAL SECTION - NEWMOD "

*resid_pane.class: panedWindow
*resid_pane.parent: dbox_user_resid
*resid_pane.static: true
*resid_pane.name: resid_pane
*resid_pane.unitType: "pixels"
*resid_pane.x: 0
*resid_pane.y: 0
*resid_pane.width: 694
*resid_pane.height: 450

*resid_form_1.class: form
*resid_form_1.parent: resid_pane
*resid_form_1.static: true
*resid_form_1.name: resid_form_1
*resid_form_1.unitType: "pixels"
*resid_form_1.x: 3
*resid_form_1.y: 0
*resid_form_1.width: 690
*resid_form_1.height: 200

*labelGadget14.class: labelGadget
*labelGadget14.parent: resid_form_1
*labelGadget14.static: true
*labelGadget14.name: labelGadget14
*labelGadget14.x: 20
*labelGadget14.y: 0
*labelGadget14.width: 150
*labelGadget14.height: 20
*labelGadget14.alignment: "alignment_beginning"
*labelGadget14.labelString: "Declarations"
*labelGadget14.bottomAttachment: "attach_none"
*labelGadget14.leftAttachment: "attach_form"
*labelGadget14.leftOffset: 20
*labelGadget14.rightAttachment: "attach_none"
*labelGadget14.topAttachment: "attach_form"
*labelGadget14.topOffset: 10

*scrolledWindow8.class: scrolledWindow
*scrolledWindow8.parent: resid_form_1
*scrolledWindow8.static: true
*scrolledWindow8.name: scrolledWindow8
*scrolledWindow8.scrollingPolicy: "application_defined"
*scrolledWindow8.unitType: "pixels"
*scrolledWindow8.x: 10
*scrolledWindow8.y: 30
*scrolledWindow8.visualPolicy: "variable"
*scrolledWindow8.scrollBarDisplayPolicy: "static"
*scrolledWindow8.shadowThickness: 0
*scrolledWindow8.bottomAttachment: "attach_form"
*scrolledWindow8.leftAttachment: "attach_form"
*scrolledWindow8.leftOffset: 20
*scrolledWindow8.rightAttachment: "attach_form"
*scrolledWindow8.rightOffset: 20
*scrolledWindow8.topAttachment: "attach_widget"
*scrolledWindow8.topOffset: 10
*scrolledWindow8.topWidget: "labelGadget14"
*scrolledWindow8.bottomOffset: 10

*resid_decl_scrolledText.class: scrolledText
*resid_decl_scrolledText.parent: scrolledWindow8
*resid_decl_scrolledText.static: false
*resid_decl_scrolledText.name: resid_decl_scrolledText
*resid_decl_scrolledText.width: 680
*resid_decl_scrolledText.height: 160
*resid_decl_scrolledText.x: 0
*resid_decl_scrolledText.y: 0
*resid_decl_scrolledText.columns: 80
*resid_decl_scrolledText.editMode: "multi_line_edit"
*resid_decl_scrolledText.resizeHeight: "true"
*resid_decl_scrolledText.resizeWidth: "true"
*resid_decl_scrolledText.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*resid_decl_scrolledText.modifyVerifyCallback.source: public
*resid_decl_scrolledText.modifyVerifyCallback: text_maius_callback

*resid_form_2.class: form
*resid_form_2.parent: resid_pane
*resid_form_2.static: true
*resid_form_2.name: resid_form_2
*resid_form_2.unitType: "pixels"
*resid_form_2.x: -3
*resid_form_2.y: -10
*resid_form_2.width: 690
*resid_form_2.height: 200

*labelGadget15.class: labelGadget
*labelGadget15.parent: resid_form_2
*labelGadget15.static: true
*labelGadget15.name: labelGadget15
*labelGadget15.x: 30
*labelGadget15.y: 10
*labelGadget15.width: 120
*labelGadget15.height: 20
*labelGadget15.bottomAttachment: "attach_none"
*labelGadget15.labelString: "User code"
*labelGadget15.leftAttachment: "attach_form"
*labelGadget15.leftOffset: 20
*labelGadget15.rightAttachment: "attach_none"
*labelGadget15.topAttachment: "attach_form"
*labelGadget15.topOffset: 10
*labelGadget15.alignment: "alignment_beginning"

*scrolledWindow10.class: scrolledWindow
*scrolledWindow10.parent: resid_form_2
*scrolledWindow10.static: true
*scrolledWindow10.name: scrolledWindow10
*scrolledWindow10.scrollingPolicy: "application_defined"
*scrolledWindow10.unitType: "pixels"
*scrolledWindow10.x: 10
*scrolledWindow10.y: 30
*scrolledWindow10.visualPolicy: "variable"
*scrolledWindow10.scrollBarDisplayPolicy: "static"
*scrolledWindow10.shadowThickness: 0
*scrolledWindow10.bottomAttachment: "attach_form"
*scrolledWindow10.bottomOffset: 10
*scrolledWindow10.leftAttachment: "attach_form"
*scrolledWindow10.leftOffset: 20
*scrolledWindow10.rightAttachment: "attach_form"
*scrolledWindow10.rightOffset: 20
*scrolledWindow10.topAttachment: "attach_widget"
*scrolledWindow10.topOffset: 10
*scrolledWindow10.topWidget: "labelGadget15"

*resid_code_scrolledText.class: scrolledText
*resid_code_scrolledText.parent: scrolledWindow10
*resid_code_scrolledText.static: false
*resid_code_scrolledText.name: resid_code_scrolledText
*resid_code_scrolledText.width: 680
*resid_code_scrolledText.height: 160
*resid_code_scrolledText.x: 0
*resid_code_scrolledText.y: 0
*resid_code_scrolledText.columns: 80
*resid_code_scrolledText.editMode: "multi_line_edit"
*resid_code_scrolledText.resizeHeight: "true"
*resid_code_scrolledText.resizeWidth: "true"
*resid_code_scrolledText.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*resid_code_scrolledText.modifyVerifyCallback.source: public
*resid_code_scrolledText.modifyVerifyCallback: text_maius_callback

*resid_form_3.class: form
*resid_form_3.parent: resid_pane
*resid_form_3.static: true
*resid_form_3.name: resid_form_3
*resid_form_3.unitType: "pixels"
*resid_form_3.x: 3
*resid_form_3.y: 211
*resid_form_3.width: 690
*resid_form_3.height: 250

*labelGadget16.class: labelGadget
*labelGadget16.parent: resid_form_3
*labelGadget16.static: true
*labelGadget16.name: labelGadget16
*labelGadget16.x: 20
*labelGadget16.y: 10
*labelGadget16.width: 300
*labelGadget16.height: 20
*labelGadget16.alignment: "alignment_beginning"
*labelGadget16.bottomAttachment: "attach_none"
*labelGadget16.labelString: "Residuals"
*labelGadget16.leftAttachment: "attach_form"
*labelGadget16.leftOffset: 20
*labelGadget16.rightAttachment: "attach_none"
*labelGadget16.topAttachment: "attach_form"
*labelGadget16.topOffset: 10

*ok_resid_pb.class: pushButton
*ok_resid_pb.parent: resid_form_3
*ok_resid_pb.static: true
*ok_resid_pb.name: ok_resid_pb
*ok_resid_pb.x: 20
*ok_resid_pb.y: 300
*ok_resid_pb.width: 100
*ok_resid_pb.height: 30
*ok_resid_pb.bottomAttachment: "attach_form"
*ok_resid_pb.bottomOffset: 10
*ok_resid_pb.leftAttachment: "attach_form"
*ok_resid_pb.leftOffset: 20
*ok_resid_pb.rightAttachment: "attach_none"
*ok_resid_pb.rightOffset: 0
*ok_resid_pb.topAttachment: "attach_none"
*ok_resid_pb.topOffset: 0
*ok_resid_pb.labelString: "Ok"
*ok_resid_pb.activateCallback: memo_textMOD(True);

*apply_resid_pb.class: pushButton
*apply_resid_pb.parent: resid_form_3
*apply_resid_pb.static: true
*apply_resid_pb.name: apply_resid_pb
*apply_resid_pb.x: 140
*apply_resid_pb.y: 300
*apply_resid_pb.width: 90
*apply_resid_pb.height: 28
*apply_resid_pb.labelString: "Apply"
*apply_resid_pb.bottomAttachment: "attach_form"
*apply_resid_pb.bottomOffset: 10
*apply_resid_pb.leftAttachment: "attach_widget"
*apply_resid_pb.leftOffset: 20
*apply_resid_pb.leftWidget: "ok_resid_pb"
*apply_resid_pb.rightAttachment: "attach_none"
*apply_resid_pb.topAttachment: "attach_none"
*apply_resid_pb.topOffset: 0
*apply_resid_pb.activateCallback: memo_textMOD(False);

*cancel_resid_pb.class: pushButton
*cancel_resid_pb.parent: resid_form_3
*cancel_resid_pb.static: true
*cancel_resid_pb.name: cancel_resid_pb
*cancel_resid_pb.x: 250
*cancel_resid_pb.y: 300
*cancel_resid_pb.width: 90
*cancel_resid_pb.height: 28
*cancel_resid_pb.labelString: "Cancel"
*cancel_resid_pb.bottomAttachment: "attach_form"
*cancel_resid_pb.bottomOffset: 10
*cancel_resid_pb.leftAttachment: "attach_widget"
*cancel_resid_pb.leftOffset: 20
*cancel_resid_pb.leftWidget: "apply_resid_pb"
*cancel_resid_pb.rightAttachment: "attach_none"
*cancel_resid_pb.topAttachment: "attach_none"
*cancel_resid_pb.topOffset: 0
*cancel_resid_pb.activateCallback: {\
UxDestroySwidget(dbox_user_resid);\
dbox_userresid_managed = False;    \
XtFree(text_residui);\
}

*scrolledWindow12.class: scrolledWindow
*scrolledWindow12.parent: resid_form_3
*scrolledWindow12.static: true
*scrolledWindow12.name: scrolledWindow12
*scrolledWindow12.scrollingPolicy: "automatic"
*scrolledWindow12.unitType: "pixels"
*scrolledWindow12.x: 20
*scrolledWindow12.y: 50
*scrolledWindow12.width: 660
*scrolledWindow12.height: 420
*scrolledWindow12.bottomAttachment: "attach_widget"
*scrolledWindow12.bottomOffset: 10
*scrolledWindow12.bottomWidget: "ok_resid_pb"
*scrolledWindow12.leftAttachment: "attach_form"
*scrolledWindow12.leftOffset: 20
*scrolledWindow12.rightAttachment: "attach_form"
*scrolledWindow12.rightOffset: 20
*scrolledWindow12.topAttachment: "attach_widget"
*scrolledWindow12.topOffset: 10
*scrolledWindow12.topWidget: "labelGadget16"

*resid_resid_form.class: form
*resid_resid_form.parent: scrolledWindow12
*resid_resid_form.static: true
*resid_resid_form.name: resid_resid_form
*resid_resid_form.unitType: "pixels"
*resid_resid_form.x: 0
*resid_resid_form.y: -2
*resid_resid_form.width: 630
*resid_resid_form.height: 200

