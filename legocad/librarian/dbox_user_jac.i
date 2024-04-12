! UIMX ascii 2.0 key: 6840                                                      

*dbox_user_jac.class: dialogShell
*dbox_user_jac.parent: NO_PARENT
*dbox_user_jac.static: true
*dbox_user_jac.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo dbox_user_jac.i\
   tipo \
   release 2.22\
   data 5/9/95\
   reserved @(#)dbox_user_jac.i	2.22\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#endif\
\
/****************************************************************/\
/* INCLUDE FILES						*/\
/****************************************************************/\
\
#include <stdio.h>\
#include <Xm/Xm.h>\
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
extern StructVars *variabili;\
extern StructDati *dati_geom;\
\
extern JacToggStruct jactoggstruct[MAX_EQUAZIONI][MAX_VARIABILI_IN_OUT];\
extern int jac_rows, jac_cols;\
extern int num_var_stato, num_var_algebriche;\
\
extern int num_yes_toggle;\
extern char *str_dichJC, *str_codJC, *str_coefJC[MAX_EQUAZIONI];\
\
extern XmFontList fontList;\
\
/****************************************************************/\
/* VARIABILI GLOBALI 						*/\
/****************************************************************/\
\
Boolean dbox_userjac_managed = False;\
\
Widget *text_jac_dipend;
*dbox_user_jac.ispecdecl:
*dbox_user_jac.funcdecl: swidget create_dbox_userjac()
*dbox_user_jac.funcname: create_dbox_userjac
*dbox_user_jac.funcdef: "swidget", "<create_dbox_userjac>(%)"
*dbox_user_jac.icode: Dimension height;
*dbox_user_jac.fcode: /* Visualizzazione text per l'input */\
text_user_jac(&height);\
\
UxPopupInterface (rtrn, no_grab);\
dbox_userjac_managed = True;\
\
/* Dimensionamento dell'altezza della form dei text */\
set_something (UxGetWidget(jac_dipend_form),XmNheight,height);\
\
if ( str_dichJC != NULL )\
   XmTextSetString(UxGetWidget(jac_decl_scrolledText),str_dichJC);\
\
if ( str_codJC != NULL )\
   XmTextSetString(UxGetWidget(jac_text_scrolledText),str_codJC);\
\
return(rtrn);\

*dbox_user_jac.auxdecl: /***\
 *** text_user_jac(form_height)\
 ***   Parametri:\
 ***     Dimension *form_height : altezza della form (uscita) \
 ***\
 ***   Descrizione:\
 ***     Compone le righe di label e text per la caratterizzazione\
 ***     delle dipendenze dello jacobiano del nuovo modulo (jac_yes=True=BLACK).\
 ***     Abilitata dopo le definizioni per il nuovo modulo.\
 ***/\
text_user_jac (form_height)\
Dimension *form_height;\
{\
   int i=0, j=0, num_resid = 0;\
   int i_st, i_alg, i_in;\
   Position posy = 10;\
\
   i_st = 0;\
   i_alg = num_var_stato; \
   i_in = i_alg + num_var_algebriche;\
\
/* Allocazione di memoria per l'array di text-widget */\
   text_jac_dipend = (Widget *) XtCalloc(num_yes_toggle, sizeof(Widget));\
\
/* N.B. Dopo un'apparizione del Divo Silvano mi e' pressoche' chiaro che */\
/* accanto alla label "Residual #" va l'INDICE di RIGA della matrice jacob. */\
/* mentre accanto a "Variable ABCD ()" va l'INDICE di COLONNA */\
   for (i=0; i<jac_rows; i++)\
      for (j=0; j<jac_cols; j++)\
         if ( jactoggstruct[i][j].jac_yes )\
         {\
         /* Label AJAC(x,y) */\
            crea_labels_jac (i+1,j+1,variabili[j].nome,posy);\
            posy += ALTEZZA_LABEL;\
\
         /* Text */\
            crea_texts_jac (&text_jac_dipend[num_resid],posy,65,i+1,j+1);\
\
         /* input inserito dall'utente precedentemente */\
            if ( jactoggstruct[i][j].stringa != NULL )\
               XmTextSetString(text_jac_dipend[num_resid],\
                               jactoggstruct[i][j].stringa);\
\
            num_resid++;\
            posy += ALTEZZA_LABEL * TEXT_FORTRAN_LINES + 10;\
         } /* FINE if JAC_JES */\
\
   *form_height = posy;\
}\
\
/*************************************************************/\
/***\
 *** crea_labels_jac (ind_row,ind_col,nome_var,posy)\
 ***   Parametri:\
 ***     int ind_row : indice residuo\
 ***     int ind_col : indice variabile\
 ***     char *nome_var : nome variabile\
 ***     Position posy : posizione y della Label\
 ***\
 ***   Descrizione:\
 ***     Crea le label di intestazione degli elementi della matrice jacobiana\
 ***     (numero del residuo e nome della variabile)\
 ***/\
crea_labels_jac (ind_row,ind_col,nome_var,posy)\
int ind_row,ind_col;\
char *nome_var;\
Position posy;\
{\
   Widget wdg;\
   char temp[50];\
   XmString cstring;\
\
   sprintf (temp,"Residual # %d  -  Variable %s (%d)",\
            ind_row,nome_var,ind_col);\
   cstring = CREATE_CSTRING (temp);\
\
/* Creazione label RESIDUAL # x */\
   argcount = 0;\
   XtSetArg (args[argcount],XmNy,posy); argcount++;\
   XtSetArg (args[argcount],XmNheight,ALTEZZA_LABEL); argcount++;\
   XtSetArg (args[argcount],XmNlabelString,cstring); argcount++;\
   XtSetArg (args[argcount],XmNalignment,XmALIGNMENT_CENTER); argcount++;\
   wdg = XmCreateLabel (UxGetWidget(jac_dipend_form),"DboxUserJac",args,\
                        argcount);\
   XtManageChild (wdg);\
\
   XmStringFree (cstring);\
}\
\
/*************************************************************/\
/***\
 *** crea_texts_jac (wdg,posy,num_col,i,j)\
 ***   Parametri:\
 ***     Widget *wdg : text-widget creato (uscita)\
 ***     Position posy : posizione y del text-widget\
 ***     int num_col : numero colonne editabili\
 ***     int i, j : indici jacobiano per la stampa 'AJAC(I,J) = '\
 ***\
 ***   Descrizione:\
 ***     Crea i text per l'inserimento del Fortran relativo al valore di \
 ***     alcuni elementi della matrice jacobiana.\
 ***     Si tratta di scrolledTextWidget MULTILINE (5 righe) da 65 caratteri\
 ***     che devono contenere le istruzioni Fortran da colonna 7 a 72.\
 ***     Per le eventuali istruzioni comprese tra la riga 2 e la 5, il\
 ***     generatore di Fortran si preoccupa di porre un simbolo di\
 ***     continuazione ('$') alla colonna 6.\
 ***/\
crea_texts_jac (wdg,posy,num_col,i,j)\
Widget *wdg;\
Position posy;\
int num_col;\
int i,j;\
{\
   Widget label_wdg;\
   char temp[20];\
   XmString cstring;\
\
   sprintf (temp,"AJAC (%d,%d) = ",i,j);\
   cstring = CREATE_CSTRING (temp);\
\
/* Creazione label AJAC(x,y) */\
   argcount = 0;\
   XtSetArg (args[argcount],XmNy,posy); argcount++;\
   XtSetArg (args[argcount],XmNheight,ALTEZZA_TEXT); argcount++;\
   XtSetArg (args[argcount],XmNlabelString,cstring); argcount++;\
   XtSetArg (args[argcount],XmNalignment,XmALIGNMENT_CENTER); argcount++;\
   XtSetArg (args[argcount],XmNfontList,fontList); argcount++;\
   label_wdg = XmCreateLabel (UxGetWidget(jac_dipend_form),"DboxUserJac",\
                         args,argcount);\
\
   XtManageChild (label_wdg);\
 \
/* Creazione Scrolled Text */\
   argcount = 0;\
   XtSetArg (args[argcount],XmNheight,ALTEZZA_LABEL*TEXT_FORTRAN_LINES);argcount++;\
   XtSetArg (args[argcount],XmNresizeHeight,False);argcount++;\
   XtSetArg (args[argcount],XmNresizeWidth, False);argcount++;\
   XtSetArg (args[argcount],XmNy,posy); argcount++;\
   XtSetArg (args[argcount],XmNleftAttachment,XmATTACH_WIDGET); argcount++;\
   XtSetArg (args[argcount],XmNleftWidget,label_wdg); argcount++;\
   XtSetArg (args[argcount],XmNrightAttachment,XmATTACH_FORM); argcount++;\
   XtSetArg (args[argcount],XmNrightOffset,30); argcount++;\
   XtSetArg (args[argcount],XmNcolumns,num_col);argcount++;\
   XtSetArg (args[argcount],XmNrows,TEXT_FORTRAN_LINES);argcount++;\
   XtSetArg (args[argcount],XmNeditMode,XmMULTI_LINE_EDIT);argcount++;\
   XtSetArg (args[argcount],XmNeditable,True);argcount++;\
   XtSetArg (args[argcount],XmNfontList,fontList); argcount++;\
   *wdg = XmCreateScrolledText(UxGetWidget(jac_dipend_form),"DboxUserJac",\
                               args,argcount);\
   XtAddCallback(*wdg, XmNmodifyVerifyCallback, text_maius_callback, NULL);\
   XtManageChild (*wdg);\
\
   XmStringFree (cstring);\
}\
\
\
/*** memo_textJC(flag)\
 ***   Parametri:\
 ***     Boolean flag : indica se la window deve sparire o meno.\
 ***\
 ***   Descrizione:\
 ***     memorizza il contenuto dei text-widget della window dei dati nelle\
 ***     variabili globali str_dichJC, str_codJC e str_coefJC\
 ***/\
memo_textJC(flag)\
Boolean flag;\
{\
   int i, j, k;\
\
   non_salvato = True;\
\
/* Dealloca la memoria precedentemente allocata da XmTextGetString() */\
   if ( str_dichJC != NULL )\
      XtFree( str_dichJC );\
\
   if ( str_codJC != NULL )\
      XtFree( str_codJC );\
\
   str_dichJC = XmTextGetString(UxGetWidget(jac_decl_scrolledText));\
   str_codJC = XmTextGetString(UxGetWidget(jac_text_scrolledText));\
\
   k = 0;\
   for ( i=0 ; i<jac_rows ; i++ )\
       for ( j=0 ; j<jac_cols ; j++ )\
           if (jactoggstruct[i][j].jac_yes)\
           {\
              XtFree(jactoggstruct[i][j].stringa);\
              jactoggstruct[i][j].stringa=XmTextGetString(text_jac_dipend[k++]);\
           }\
\
   if (flag)\
   {\
      XtFree(text_jac_dipend);\
      UxDestroySwidget(dbox_user_jac);\
      dbox_userjac_managed = False;\
   }\
}
*dbox_user_jac.name: dbox_user_jac
*dbox_user_jac.x: 110
*dbox_user_jac.y: 550
*dbox_user_jac.width: 730
*dbox_user_jac.height: 500
*dbox_user_jac.geometry: "+200+250"
*dbox_user_jac.title: "JC JACOBIAN MATRIX - NEWMOD "

*jac_pane.class: panedWindow
*jac_pane.parent: dbox_user_jac
*jac_pane.static: true
*jac_pane.name: jac_pane
*jac_pane.unitType: "pixels"
*jac_pane.x: 0
*jac_pane.y: 0
*jac_pane.width: 694
*jac_pane.height: 450

*jac_form_1.class: form
*jac_form_1.parent: jac_pane
*jac_form_1.static: true
*jac_form_1.name: jac_form_1
*jac_form_1.unitType: "pixels"
*jac_form_1.x: 3
*jac_form_1.y: 0
*jac_form_1.width: 690
*jac_form_1.height: 200

*labelGadget11.class: labelGadget
*labelGadget11.parent: jac_form_1
*labelGadget11.static: true
*labelGadget11.name: labelGadget11
*labelGadget11.x: 20
*labelGadget11.y: 0
*labelGadget11.width: 150
*labelGadget11.height: 20
*labelGadget11.alignment: "alignment_beginning"
*labelGadget11.labelString: "Declarations"
*labelGadget11.bottomAttachment: "attach_none"
*labelGadget11.leftAttachment: "attach_form"
*labelGadget11.leftOffset: 20
*labelGadget11.rightAttachment: "attach_none"
*labelGadget11.topAttachment: "attach_form"
*labelGadget11.topOffset: 10

*scrolledWindow7.class: scrolledWindow
*scrolledWindow7.parent: jac_form_1
*scrolledWindow7.static: true
*scrolledWindow7.name: scrolledWindow7
*scrolledWindow7.scrollingPolicy: "application_defined"
*scrolledWindow7.unitType: "pixels"
*scrolledWindow7.x: 10
*scrolledWindow7.y: 30
*scrolledWindow7.visualPolicy: "variable"
*scrolledWindow7.scrollBarDisplayPolicy: "static"
*scrolledWindow7.shadowThickness: 0
*scrolledWindow7.bottomAttachment: "attach_form"
*scrolledWindow7.leftAttachment: "attach_form"
*scrolledWindow7.leftOffset: 20
*scrolledWindow7.rightAttachment: "attach_form"
*scrolledWindow7.rightOffset: 20
*scrolledWindow7.topAttachment: "attach_widget"
*scrolledWindow7.topOffset: 10
*scrolledWindow7.topWidget: "labelGadget11"
*scrolledWindow7.bottomOffset: 10

*jac_decl_scrolledText.class: scrolledText
*jac_decl_scrolledText.parent: scrolledWindow7
*jac_decl_scrolledText.static: false
*jac_decl_scrolledText.name: jac_decl_scrolledText
*jac_decl_scrolledText.width: 680
*jac_decl_scrolledText.height: 160
*jac_decl_scrolledText.x: 0
*jac_decl_scrolledText.y: 0
*jac_decl_scrolledText.columns: 80
*jac_decl_scrolledText.editMode: "multi_line_edit"
*jac_decl_scrolledText.resizeHeight: "true"
*jac_decl_scrolledText.resizeWidth: "true"
*jac_decl_scrolledText.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*jac_decl_scrolledText.modifyVerifyCallback.source: public
*jac_decl_scrolledText.modifyVerifyCallback: text_maius_callback

*jac_form_2.class: form
*jac_form_2.parent: jac_pane
*jac_form_2.static: true
*jac_form_2.name: jac_form_2
*jac_form_2.unitType: "pixels"
*jac_form_2.x: -3
*jac_form_2.y: -10
*jac_form_2.width: 690
*jac_form_2.height: 200

*labelGadget13.class: labelGadget
*labelGadget13.parent: jac_form_2
*labelGadget13.static: true
*labelGadget13.name: labelGadget13
*labelGadget13.x: 30
*labelGadget13.y: 10
*labelGadget13.width: 120
*labelGadget13.height: 20
*labelGadget13.bottomAttachment: "attach_none"
*labelGadget13.labelString: "Text"
*labelGadget13.leftAttachment: "attach_form"
*labelGadget13.leftOffset: 20
*labelGadget13.rightAttachment: "attach_none"
*labelGadget13.topAttachment: "attach_form"
*labelGadget13.topOffset: 10
*labelGadget13.alignment: "alignment_beginning"

*scrolledWindow9.class: scrolledWindow
*scrolledWindow9.parent: jac_form_2
*scrolledWindow9.static: true
*scrolledWindow9.name: scrolledWindow9
*scrolledWindow9.scrollingPolicy: "application_defined"
*scrolledWindow9.unitType: "pixels"
*scrolledWindow9.x: 10
*scrolledWindow9.y: 30
*scrolledWindow9.visualPolicy: "variable"
*scrolledWindow9.scrollBarDisplayPolicy: "static"
*scrolledWindow9.shadowThickness: 0
*scrolledWindow9.bottomAttachment: "attach_form"
*scrolledWindow9.bottomOffset: 10
*scrolledWindow9.leftAttachment: "attach_form"
*scrolledWindow9.leftOffset: 20
*scrolledWindow9.rightAttachment: "attach_form"
*scrolledWindow9.rightOffset: 20
*scrolledWindow9.topAttachment: "attach_widget"
*scrolledWindow9.topOffset: 10
*scrolledWindow9.topWidget: "labelGadget13"

*jac_text_scrolledText.class: scrolledText
*jac_text_scrolledText.parent: scrolledWindow9
*jac_text_scrolledText.static: false
*jac_text_scrolledText.name: jac_text_scrolledText
*jac_text_scrolledText.width: 680
*jac_text_scrolledText.height: 160
*jac_text_scrolledText.x: 0
*jac_text_scrolledText.y: 0
*jac_text_scrolledText.columns: 80
*jac_text_scrolledText.editMode: "multi_line_edit"
*jac_text_scrolledText.resizeHeight: "true"
*jac_text_scrolledText.resizeWidth: "true"
*jac_text_scrolledText.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*jac_text_scrolledText.modifyVerifyCallback.source: public
*jac_text_scrolledText.modifyVerifyCallback: text_maius_callback

*jac_form_3.class: form
*jac_form_3.parent: jac_pane
*jac_form_3.static: true
*jac_form_3.name: jac_form_3
*jac_form_3.unitType: "pixels"
*jac_form_3.x: 3
*jac_form_3.y: 211
*jac_form_3.width: 690
*jac_form_3.height: 250

*labelGadget12.class: labelGadget
*labelGadget12.parent: jac_form_3
*labelGadget12.static: true
*labelGadget12.name: labelGadget12
*labelGadget12.x: 20
*labelGadget12.y: 10
*labelGadget12.width: 300
*labelGadget12.height: 20
*labelGadget12.alignment: "alignment_beginning"
*labelGadget12.bottomAttachment: "attach_none"
*labelGadget12.labelString: "Jacobian matrix coefficients"
*labelGadget12.leftAttachment: "attach_form"
*labelGadget12.leftOffset: 20
*labelGadget12.rightAttachment: "attach_none"
*labelGadget12.topAttachment: "attach_form"
*labelGadget12.topOffset: 10

*ok_jac_pb.class: pushButton
*ok_jac_pb.parent: jac_form_3
*ok_jac_pb.static: true
*ok_jac_pb.name: ok_jac_pb
*ok_jac_pb.x: 20
*ok_jac_pb.y: 300
*ok_jac_pb.width: 100
*ok_jac_pb.height: 30
*ok_jac_pb.bottomAttachment: "attach_form"
*ok_jac_pb.bottomOffset: 10
*ok_jac_pb.leftAttachment: "attach_form"
*ok_jac_pb.leftOffset: 20
*ok_jac_pb.rightAttachment: "attach_none"
*ok_jac_pb.rightOffset: 0
*ok_jac_pb.topAttachment: "attach_none"
*ok_jac_pb.topOffset: 0
*ok_jac_pb.labelString: "Ok"
*ok_jac_pb.activateCallback: {\
memo_textJC(True);\
}

*apply_jac_pb.class: pushButton
*apply_jac_pb.parent: jac_form_3
*apply_jac_pb.static: true
*apply_jac_pb.name: apply_jac_pb
*apply_jac_pb.x: 140
*apply_jac_pb.y: 300
*apply_jac_pb.width: 90
*apply_jac_pb.height: 28
*apply_jac_pb.labelString: "Apply"
*apply_jac_pb.bottomAttachment: "attach_form"
*apply_jac_pb.bottomOffset: 10
*apply_jac_pb.leftAttachment: "attach_widget"
*apply_jac_pb.leftOffset: 20
*apply_jac_pb.leftWidget: "ok_jac_pb"
*apply_jac_pb.rightAttachment: "attach_none"
*apply_jac_pb.topAttachment: "attach_none"
*apply_jac_pb.topOffset: 0
*apply_jac_pb.activateCallback: memo_textJC(False);

*cancel_jac_pb.class: pushButton
*cancel_jac_pb.parent: jac_form_3
*cancel_jac_pb.static: true
*cancel_jac_pb.name: cancel_jac_pb
*cancel_jac_pb.x: 250
*cancel_jac_pb.y: 300
*cancel_jac_pb.width: 90
*cancel_jac_pb.height: 28
*cancel_jac_pb.labelString: "Cancel"
*cancel_jac_pb.bottomAttachment: "attach_form"
*cancel_jac_pb.bottomOffset: 10
*cancel_jac_pb.leftAttachment: "attach_widget"
*cancel_jac_pb.leftOffset: 20
*cancel_jac_pb.leftWidget: "apply_jac_pb"
*cancel_jac_pb.rightAttachment: "attach_none"
*cancel_jac_pb.topAttachment: "attach_none"
*cancel_jac_pb.topOffset: 0
*cancel_jac_pb.activateCallback: {\
XtFree(text_jac_dipend);\
UxDestroySwidget(dbox_user_jac);\
dbox_userjac_managed = False;\
}

*jac_dipend_scrolledW.class: scrolledWindow
*jac_dipend_scrolledW.parent: jac_form_3
*jac_dipend_scrolledW.static: true
*jac_dipend_scrolledW.name: jac_dipend_scrolledW
*jac_dipend_scrolledW.scrollingPolicy: "automatic"
*jac_dipend_scrolledW.unitType: "pixels"
*jac_dipend_scrolledW.x: 10
*jac_dipend_scrolledW.y: 40
*jac_dipend_scrolledW.visualPolicy: "variable"
*jac_dipend_scrolledW.scrollBarDisplayPolicy: "static"
*jac_dipend_scrolledW.shadowThickness: 2
*jac_dipend_scrolledW.bottomAttachment: "attach_widget"
*jac_dipend_scrolledW.bottomOffset: 10
*jac_dipend_scrolledW.bottomWidget: "ok_jac_pb"
*jac_dipend_scrolledW.leftAttachment: "attach_form"
*jac_dipend_scrolledW.leftOffset: 20
*jac_dipend_scrolledW.rightAttachment: "attach_form"
*jac_dipend_scrolledW.rightOffset: 20
*jac_dipend_scrolledW.topAttachment: "attach_widget"
*jac_dipend_scrolledW.topOffset: 10
*jac_dipend_scrolledW.topWidget: "labelGadget12"
*jac_dipend_scrolledW.borderWidth: 0

*jac_dipend_form.class: form
*jac_dipend_form.parent: jac_dipend_scrolledW
*jac_dipend_form.static: true
*jac_dipend_form.name: jac_dipend_form
*jac_dipend_form.unitType: "pixels"
*jac_dipend_form.x: -1
*jac_dipend_form.y: -1
*jac_dipend_form.width: 650
*jac_dipend_form.height: 260

