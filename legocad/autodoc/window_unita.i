! UIMX ascii 2.0 key: 1255                                                      

*window_unita.class: formDialog
*window_unita.parent: NO_PARENT
*window_unita.defaultShell: topLevelShell
*window_unita.static: true
*window_unita.gbldecl: /*\
   modulo window_unita.i\
   tipo \
   release 1.13\
   data 5/15/95\
   reserved @(#)window_unita.i	1.13\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
\
#include <Xm/RowColumn.h>\
\
#include "autodoc.h"\
#include "unita.h"\
\
/************************************************************************/\
/* VARIABILI GLOBALI ESTERNE						*/\
/************************************************************************/\
extern Display *display;\
\
extern Boolean open_window_unita;\
\
extern UnitaMisura unimis[];\
extern int num_unita_misura;\
\
extern Arg args[];\
extern int nargs;\
\
extern XmString cstring;\
\
extern XmFontList fontList;\
\
/************************************************************************/\
/* VARIABILI GLOBALI 							*/\
/************************************************************************/
*window_unita.ispecdecl: Widget *opt_menu;
*window_unita.funcdecl: swidget create_window_unita()\

*window_unita.funcname: create_window_unita
*window_unita.icode: int i, y, ind;\
Widget wlabel, wbutton;\
\
open_window_unita = True;\
\
opt_menu = (Widget *) calloc(num_unita_misura, sizeof(Widget));
*window_unita.fcode: for ( i = 0, y = 10 ; i < num_unita_misura ; i++, y += ALTEZZA_TEXT+5 )\
{\
/* creazione LABEL unita di misura */\
   cstring = CREATE_CSTRING(unimis[i].nome_tipo);\
\
   nargs = 0;\
   XtSetArg(args[nargs], XmNx, 10); nargs++;\
   XtSetArg(args[nargs], XmNy, y); nargs++;\
   XtSetArg(args[nargs], XmNheight, ALTEZZA_TEXT); nargs++;\
   XtSetArg(args[nargs], XmNlabelString, cstring); nargs++;\
   XtSetArg(args[nargs], XmNfontList, fontList); nargs++;\
   XtSetArg(args[nargs], XmNrecomputeSize, True); nargs++;\
   XtSetArg(args[nargs], XmNalignment, XmALIGNMENT_BEGINNING); nargs++;\
   wlabel = XmCreateLabel(UxGetWidget(bboard_unita), "LabelUnita", args,nargs);\
   XmStringFree(cstring);\
\
   opt_menu[i] = crea_opt_menu_unita(i, y);\
\
   XtManageChild(opt_menu[i]);\
   XtManageChild(wlabel);\
}\
\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*window_unita.auxdecl: /*** Widget crea_opt_menu_unita(indice, y)\
 ***    Parametri:\
 ***       int indice : indice array delle unita di misura (unimis[]).\
 ***       int y : posizione y del widget\
 ***\
 ***    Descrizione:\
 ***        option-menu per la selezione dell'unita di misura.\
 ***/\
Widget crea_opt_menu_unita(indice, y)\
int indice, y;\
{\
   int i, ind_dim;\
   Widget wmenu, wpull, wpb[5];\
\
   ind_dim = unimis[indice].ind_selez;\
   nargs = 0;\
   XtSetArg(args[nargs], XmNfontList, fontList); nargs++;\
   wpull = XmCreatePulldownMenu(UxGetWidget(bboard_unita), "PDownMenuUnita",\
                                args, nargs);\
\
   for ( i=0 ; i<5 ; i++ )\
      if ( Empty(unimis[indice].dim[i].codice) )\
         break;\
      else\
      {\
         cstring = CREATE_CSTRING(unimis[indice].dim[i].codice);\
\
         nargs = 0;\
         XtSetArg(args[nargs], XmNwidth, 60); nargs++;\
         XtSetArg(args[nargs], XmNfontList, fontList); nargs++;\
         XtSetArg(args[nargs], XmNlabelString, cstring); nargs++;\
         XtSetArg(args[nargs], XmNuserData, &unimis[indice]); nargs++;\
         XtSetArg(args[nargs], XmNrecomputeSize, False); nargs++;\
         wpb[i] = XmCreatePushButton(wpull, "PushBdimUnita", args, nargs);\
         XtAddCallback(wpb[i], XmNactivateCallback, cambia_dim_unita, i);\
         XtManageChild(wpb[i]);\
\
         XmStringFree(cstring);\
      }\
\
   XtVaSetValues(wpull, XmNmenuHistory, wpb[ind_dim], NULL);\
\
   nargs = 0;\
   XtSetArg(args[nargs], XmNx, 100); nargs++;\
   XtSetArg(args[nargs], XmNy, y); nargs++;\
   XtSetArg(args[nargs], XmNwidth, 60); nargs++;\
   XtSetArg(args[nargs], XmNfontList, fontList); nargs++;\
   XtSetArg(args[nargs], XmNheight, ALTEZZA_TEXT); nargs++;\
   XtSetArg(args[nargs], XmNsubMenuId, wpull); nargs++;\
   XtSetArg(args[nargs], XmNmenuHistory, wpb[ind_dim]);\
   wmenu = XmCreateOptionMenu(UxGetWidget(bboard_unita), "OptMenuUnita", \
			      args,nargs);\
\
   return(wmenu);\
}\
\
/*** void cambia_dim_unita(w, ind_dim, call_data)\
 ***    Parametri:\
 ***       Widget w : widget.\
 ***       int ind_dim : dimensione unita misura\
 ***       XmPushButtonCallbackStruct *call_data : non utilizzato.\
 ***\
 ***    Descrizione:\
 ***       La callback viene chiamata quando l'utente cambia la dimensione\
 ***       dell'unita' di misura.\
 ***/\
void cambia_dim_unita(w, ind_dim, call_data)\
Widget w;\
int ind_dim;\
XmAnyCallbackStruct *call_data;\
{\
   UnitaMisura *umis;\
\
   get_something(w, XmNuserData, &umis);\
   umis->ind_selez = ind_dim;\
}
*window_unita.name: window_unita
*window_unita.unitType: "pixels"
*window_unita.x: 370
*window_unita.y: 350
*window_unita.width: 370
*window_unita.height: 370
*window_unita.background: "#4f9f9f"
*window_unita.dialogTitle: "MEASURING UNIT"
*window_unita.dialogStyle: "dialog_modeless"
*window_unita.autoUnmanage: "false"

*label6.class: label
*label6.parent: window_unita
*label6.static: true
*label6.name: label6
*label6.x: 10
*label6.y: 20
*label6.width: 250
*label6.height: 30
*label6.background: "#4f9f9f"
*label6.fontList: "-adobe-helvetica-Bold-r-normal--14-140-75-75-p-82-iso8859-1"
*label6.leftAttachment: "attach_form"
*label6.leftOffset: 10
*label6.topAttachment: "attach_form"
*label6.topOffset: 10
*label6.alignment: "alignment_beginning"
*label6.labelString: "Select the measure unit to be modified:"
*label6.rightAttachment: "attach_form"
*label6.rightOffset: 10

*pb_done.class: pushButton
*pb_done.parent: window_unita
*pb_done.static: true
*pb_done.name: pb_done
*pb_done.x: 130
*pb_done.y: 330
*pb_done.width: 120
*pb_done.height: 30
*pb_done.background: "#4f9f9f"
*pb_done.fontList: "-adobe-helvetica-Bold-r-normal--14-140-75-75-p-82-iso8859-1"
*pb_done.bottomAttachment: "attach_form"
*pb_done.bottomOffset: 10
*pb_done.labelString: "Close"
*pb_done.leftAttachment: "attach_position"
*pb_done.leftOffset: 0
*pb_done.leftPosition: 55
*pb_done.rightAttachment: "attach_form"
*pb_done.rightPosition: 65
*pb_done.topAttachment: "attach_none"
*pb_done.topOffset: 0
*pb_done.activateCallback: {\
open_window_unita = False;\
\
free(opt_menu);\
\
XtDestroyWidget(XtParent(UxGetWidget(window_unita)));\
}
*pb_done.rightOffset: 20

*separatorGadget4.class: separatorGadget
*separatorGadget4.parent: window_unita
*separatorGadget4.static: true
*separatorGadget4.name: separatorGadget4
*separatorGadget4.x: 20
*separatorGadget4.y: 370
*separatorGadget4.width: 680
*separatorGadget4.height: 10
*separatorGadget4.bottomAttachment: "attach_widget"
*separatorGadget4.bottomOffset: 10
*separatorGadget4.bottomWidget: "pb_done"
*separatorGadget4.leftAttachment: "attach_form"
*separatorGadget4.leftOffset: 5
*separatorGadget4.rightAttachment: "attach_form"
*separatorGadget4.rightOffset: 5
*separatorGadget4.topAttachment: "attach_none"
*separatorGadget4.topOffset: 0

*scrolledWindow3.class: scrolledWindow
*scrolledWindow3.parent: window_unita
*scrolledWindow3.static: true
*scrolledWindow3.name: scrolledWindow3
*scrolledWindow3.scrollingPolicy: "automatic"
*scrolledWindow3.x: 10
*scrolledWindow3.y: 60
*scrolledWindow3.width: 350
*scrolledWindow3.height: 250
*scrolledWindow3.background: "#4f9f9f"
*scrolledWindow3.bottomAttachment: "attach_widget"
*scrolledWindow3.bottomOffset: 10
*scrolledWindow3.bottomWidget: "separatorGadget4"
*scrolledWindow3.leftAttachment: "attach_form"
*scrolledWindow3.leftOffset: 10
*scrolledWindow3.rightAttachment: "attach_form"
*scrolledWindow3.rightOffset: 10
*scrolledWindow3.topAttachment: "attach_widget"
*scrolledWindow3.topOffset: 10
*scrolledWindow3.topWidget: "label6"

*bboard_unita.class: bulletinBoard
*bboard_unita.parent: scrolledWindow3
*bboard_unita.static: true
*bboard_unita.name: bboard_unita
*bboard_unita.resizePolicy: "resize_any"
*bboard_unita.x: 8
*bboard_unita.y: -2
*bboard_unita.width: 330
*bboard_unita.height: 1300
*bboard_unita.background: "#4f9f9f"

*pb_apply_unita.class: pushButton
*pb_apply_unita.parent: window_unita
*pb_apply_unita.static: true
*pb_apply_unita.name: pb_apply_unita
*pb_apply_unita.x: 20
*pb_apply_unita.y: 320
*pb_apply_unita.width: 90
*pb_apply_unita.height: 30
*pb_apply_unita.background: "#4f9f9f"
*pb_apply_unita.bottomAttachment: "attach_form"
*pb_apply_unita.bottomOffset: 10
*pb_apply_unita.leftAttachment: "attach_form"
*pb_apply_unita.leftOffset: 20
*pb_apply_unita.rightAttachment: "attach_position"
*pb_apply_unita.rightPosition: 45
*pb_apply_unita.topAttachment: "attach_none"
*pb_apply_unita.topOffset: 0
*pb_apply_unita.fontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*pb_apply_unita.labelString: "Apply"
*pb_apply_unita.activateCallback: {\
\
/* salva le modifiche nel file */\
salva_unita_misura();\
\
/* Cambia le unita di misura nelle window aperte */\
aggiorna_unita_misura();\
}

