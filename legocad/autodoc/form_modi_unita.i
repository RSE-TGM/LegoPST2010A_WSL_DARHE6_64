! UIMX ascii 2.0 key: 92                                                        

*form_modi_unita.class: formDialog
*form_modi_unita.parent: NO_PARENT
*form_modi_unita.defaultShell: topLevelShell
*form_modi_unita.static: true
*form_modi_unita.gbldecl: #include <stdio.h>\
\
#ifndef DESIGN_TIME\
#include "autodoc.h"\
#include "unita.h"\
#endif\
extern void free_array_XmString( XmString, int );\
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
/* TextField-widget delle unita di misura */\
extern Widget *text_unita;\
\
/************************************************************************/\
/* VARIABILI GLOBALI 							*/\
/************************************************************************/\
\

*form_modi_unita.ispecdecl: short int item_sele;\

*form_modi_unita.ispeclist: item_sele
*form_modi_unita.ispeclist.item_sele: "short", "%item_sele%"
*form_modi_unita.funcdecl: swidget create_form_modi_unita(indice, flag_window)\
int indice; /* indice array text_unita[] e unimis[] */\
Boolean *flag_window;
*form_modi_unita.funcname: create_form_modi_unita
*form_modi_unita.funcdef: "swidget", "<create_form_modi_unita>(%)"
*form_modi_unita.argdecl: int indice;\
Boolean *flag_window;
*form_modi_unita.arglist: indice, flag_window
*form_modi_unita.arglist.indice: "int", "%indice%"
*form_modi_unita.arglist.flag_window: "Boolean", "*%flag_window%"
*form_modi_unita.icode: int i, ind;\
\
XmString acstring[5];
*form_modi_unita.fcode: *flag_window = True;\
\
item_sele = unimis[indice].ind_selez;\
\
UxPutLabelString(label_unita, unimis[indice].nome_tipo);\
\
for ( i = 0 ; i < 5 ; i++ )\
   if ( Empty(unimis[indice].dim[i].codice) )\
      break;\
   else\
      acstring[i] = CREATE_CSTRING(unimis[indice].dim[i].codice);\
\
XmListAddItems(UxGetWidget(list_dim_unita), acstring, i, 0);\
XmListSelectPos(UxGetWidget(list_dim_unita), item_sele+1, False);\
free_array_XmString(acstring, i);\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*form_modi_unita.auxdecl:
*form_modi_unita.name: form_modi_unita
*form_modi_unita.unitType: "pixels"
*form_modi_unita.x: 300
*form_modi_unita.y: 260
*form_modi_unita.width: 380
*form_modi_unita.height: 350
*form_modi_unita.background: "#4f9f9f"
*form_modi_unita.dialogTitle: "Modify dimension"
*form_modi_unita.labelFontList: "-adobe-helvetica-Bold-r-normal--14-140-75-75-p-82-iso8859-1"
*form_modi_unita.dialogStyle: "dialog_modeless"

*label8.class: label
*label8.parent: form_modi_unita
*label8.static: true
*label8.name: label8
*label8.x: 10
*label8.y: 10
*label8.width: 100
*label8.height: 30
*label8.background: "#4f9f9f"
*label8.labelString: "Measure unit:"

*frame1.class: frame
*frame1.parent: form_modi_unita
*frame1.static: true
*frame1.name: frame1
*frame1.x: 120
*frame1.y: 10
*frame1.width: 100
*frame1.height: 30
*frame1.background: "#4f9f9f"
*frame1.leftAttachment: "attach_widget"
*frame1.leftPosition: 35
*frame1.rightAttachment: "attach_none"
*frame1.rightPosition: 80
*frame1.leftOffset: 10
*frame1.leftWidget: "label8"

*label_unita.class: label
*label_unita.parent: frame1
*label_unita.static: true
*label_unita.name: label_unita
*label_unita.x: 2
*label_unita.y: 2
*label_unita.width: 118
*label_unita.height: 26
*label_unita.background: "#4f9f9f"

*pushButtonOk.class: pushButton
*pushButtonOk.parent: form_modi_unita
*pushButtonOk.static: true
*pushButtonOk.name: pushButtonOk
*pushButtonOk.x: 10
*pushButtonOk.y: 310
*pushButtonOk.width: 120
*pushButtonOk.height: 30
*pushButtonOk.background: "#4f9f9f"
*pushButtonOk.topAttachment: "attach_none"
*pushButtonOk.bottomAttachment: "attach_form"
*pushButtonOk.bottomOffset: 10
*pushButtonOk.leftAttachment: "attach_form"
*pushButtonOk.leftOffset: 20
*pushButtonOk.rightAttachment: "attach_position"
*pushButtonOk.rightPosition: 40
*pushButtonOk.topOffset: 0
*pushButtonOk.fontList: "-adobe-helvetica-Bold-r-normal--14-140-75-75-p-82-iso8859-1"
*pushButtonOk.labelString: "Ok"
*pushButtonOk.activateCallback: {\
Widget w;\
\
XmTextSetString(text_unita[indice], unimis[indice].dim[item_sele].codice);\
unimis[indice].ind_selez = item_sele;\
UxDestroySwidget(form_modi_unita);\
*flag_window = False;\
}

*pushButtonCancel.class: pushButton
*pushButtonCancel.parent: form_modi_unita
*pushButtonCancel.static: true
*pushButtonCancel.name: pushButtonCancel
*pushButtonCancel.x: 260
*pushButtonCancel.y: 310
*pushButtonCancel.width: 110
*pushButtonCancel.height: 30
*pushButtonCancel.background: "#4f9f9f"
*pushButtonCancel.bottomAttachment: "attach_form"
*pushButtonCancel.bottomOffset: 10
*pushButtonCancel.fontList: "-adobe-helvetica-Bold-r-normal--14-140-75-75-p-82-iso8859-1"
*pushButtonCancel.labelString: "Cancel"
*pushButtonCancel.leftAttachment: "attach_position"
*pushButtonCancel.leftOffset: 0
*pushButtonCancel.leftPosition: 60
*pushButtonCancel.rightAttachment: "attach_form"
*pushButtonCancel.rightOffset: 20
*pushButtonCancel.topAttachment: "attach_none"
*pushButtonCancel.topOffset: 0
*pushButtonCancel.activateCallback: {\
*flag_window = False;\
UxDestroySwidget(form_modi_unita);\
}

*separatorGadget5.class: separatorGadget
*separatorGadget5.parent: form_modi_unita
*separatorGadget5.static: true
*separatorGadget5.name: separatorGadget5
*separatorGadget5.x: 10
*separatorGadget5.y: 290
*separatorGadget5.width: 360
*separatorGadget5.height: 10
*separatorGadget5.bottomAttachment: "attach_widget"
*separatorGadget5.bottomOffset: 10
*separatorGadget5.bottomWidget: "pushButtonOk"
*separatorGadget5.rightAttachment: "attach_form"
*separatorGadget5.rightOffset: 10
*separatorGadget5.topAttachment: "attach_none"
*separatorGadget5.topOffset: 0
*separatorGadget5.leftAttachment: "attach_form"
*separatorGadget5.leftOffset: 10

*scrolledWindow4.class: scrolledWindow
*scrolledWindow4.parent: form_modi_unita
*scrolledWindow4.static: true
*scrolledWindow4.name: scrolledWindow4
*scrolledWindow4.scrollingPolicy: "application_defined"
*scrolledWindow4.x: 10
*scrolledWindow4.y: 50
*scrolledWindow4.visualPolicy: "variable"
*scrolledWindow4.scrollBarDisplayPolicy: "static"
*scrolledWindow4.shadowThickness: 0
*scrolledWindow4.background: "#4f9f9f"
*scrolledWindow4.bottomAttachment: "attach_widget"
*scrolledWindow4.bottomOffset: 10
*scrolledWindow4.bottomWidget: "separatorGadget5"
*scrolledWindow4.leftAttachment: "attach_form"
*scrolledWindow4.leftOffset: 10
*scrolledWindow4.rightAttachment: "attach_form"
*scrolledWindow4.rightOffset: 10
*scrolledWindow4.topAttachment: "attach_widget"
*scrolledWindow4.topOffset: 10
*scrolledWindow4.topWidget: "frame1"

*list_dim_unita.class: scrolledList
*list_dim_unita.parent: scrolledWindow4
*list_dim_unita.static: true
*list_dim_unita.name: list_dim_unita
*list_dim_unita.width: 360
*list_dim_unita.height: 230
*list_dim_unita.background: "#4f9f9f"
*list_dim_unita.singleSelectionCallback: {\
XmListCallbackStruct *struct_list;\
\
struct_list = (XmListCallbackStruct *) UxCallbackArg;\
\
item_sele = (short int) struct_list->item_position-1;\
}
*list_dim_unita.selectionPolicy: "browse_select"
*list_dim_unita.browseSelectionCallback: {\
XmListCallbackStruct *struct_list;\
\
struct_list = (XmListCallbackStruct *) UxCallbackArg;\
\
item_sele = (short int) struct_list->item_position-1;\
}
*list_dim_unita.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"

