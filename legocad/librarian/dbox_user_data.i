! UIMX ascii 2.0 key: 6514                                                      

*dbox_user_data.class: dialogShell
*dbox_user_data.parent: NO_PARENT
*dbox_user_data.static: true
*dbox_user_data.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo dbox_user_data.i\
   tipo \
   release 2.22\
   data 5/9/95\
   reserved @(#)dbox_user_data.i	2.22\
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
extern char *str_dichI2, *str_codI2;\
\
extern Widget UxTopLevel;\
extern Dialog_geometry geom_attention;\
extern Widget attention_wdg;\
\
/****************************************************************/\
/* VARIABILI GLOBALI 						*/\
/****************************************************************/\
\
Boolean dbox_userdata_managed = False;
*dbox_user_data.ispecdecl:
*dbox_user_data.funcdecl: swidget create_dbox_userdata()\

*dbox_user_data.funcname: create_dbox_userdata
*dbox_user_data.funcdef: "swidget", "<create_dbox_userdata>(%)"
*dbox_user_data.icode:
*dbox_user_data.fcode: UxPopupInterface (rtrn, no_grab);\
dbox_userdata_managed = True;\
\
/* aggiorna i text-widget (dichiarazione e codice) */\
if ( str_dichI2 != NULL)\
   XmTextSetString(UxGetWidget(data_decl_scrolledText), str_dichI2);\
\
if ( str_codI2 != NULL)\
   XmTextSetString(UxGetWidget(data_code_scrolledText), str_codI2);\
\
return(rtrn);\

*dbox_user_data.auxdecl: /*** memo_textI2(flag)\
 ***   Parametri:\
 ***     Boolean flag : indica se la window deve sparire o meno.\
 ***\
 ***   Descrizione:\
 ***     memorizza il contenuto dei text-widget della window dei dati nelle\
 ***     variabili globali str_dichI2 e str_codI2 \
 ***/\
memo_textI2(flag)\
Boolean flag;\
{\
\
   non_salvato = True;\
\
/* Dealloca la memoria precedentemente allocata da XmTextGetString() */\
   if ( str_dichI2 != NULL )\
      XtFree( str_dichI2 );\
\
   if ( str_codI2 != NULL )\
      XtFree( str_codI2 );\
\
   str_dichI2 = XmTextGetString(UxGetWidget(data_decl_scrolledText));\
   str_codI2 = XmTextGetString(UxGetWidget(data_code_scrolledText));\
\
   if (flag)\
   {\
      UxDestroySwidget(dbox_user_data);\
      dbox_userdata_managed = False;\
   }\
}
*dbox_user_data.name: dbox_user_data
*dbox_user_data.x: 540
*dbox_user_data.y: 440
*dbox_user_data.width: 700
*dbox_user_data.height: 500
*dbox_user_data.title: "I2 DATA SECTION - NEWMOD "
*dbox_user_data.geometry: "+190+250"

*data_pane.class: panedWindow
*data_pane.parent: dbox_user_data
*data_pane.static: true
*data_pane.name: data_pane
*data_pane.unitType: "pixels"
*data_pane.x: 0
*data_pane.y: 0
*data_pane.width: 694
*data_pane.height: 450

*form8.class: form
*form8.parent: data_pane
*form8.static: true
*form8.name: form8
*form8.unitType: "pixels"
*form8.x: 3
*form8.y: 0
*form8.width: 690
*form8.height: 200

*labelGadget9.class: labelGadget
*labelGadget9.parent: form8
*labelGadget9.static: true
*labelGadget9.name: labelGadget9
*labelGadget9.x: 20
*labelGadget9.y: 0
*labelGadget9.width: 150
*labelGadget9.height: 20
*labelGadget9.alignment: "alignment_beginning"
*labelGadget9.labelString: "Declarations"
*labelGadget9.bottomAttachment: "attach_none"
*labelGadget9.leftAttachment: "attach_form"
*labelGadget9.leftOffset: 20
*labelGadget9.rightAttachment: "attach_none"
*labelGadget9.topAttachment: "attach_form"
*labelGadget9.topOffset: 10

*scrolledWindow5.class: scrolledWindow
*scrolledWindow5.parent: form8
*scrolledWindow5.static: true
*scrolledWindow5.name: scrolledWindow5
*scrolledWindow5.scrollingPolicy: "application_defined"
*scrolledWindow5.unitType: "pixels"
*scrolledWindow5.x: 10
*scrolledWindow5.y: 30
*scrolledWindow5.visualPolicy: "variable"
*scrolledWindow5.scrollBarDisplayPolicy: "static"
*scrolledWindow5.shadowThickness: 0
*scrolledWindow5.bottomAttachment: "attach_form"
*scrolledWindow5.leftAttachment: "attach_form"
*scrolledWindow5.leftOffset: 20
*scrolledWindow5.rightAttachment: "attach_form"
*scrolledWindow5.rightOffset: 20
*scrolledWindow5.topAttachment: "attach_widget"
*scrolledWindow5.topOffset: 10
*scrolledWindow5.topWidget: "labelGadget9"
*scrolledWindow5.bottomOffset: 10

*data_decl_scrolledText.class: scrolledText
*data_decl_scrolledText.parent: scrolledWindow5
*data_decl_scrolledText.static: false
*data_decl_scrolledText.name: data_decl_scrolledText
*data_decl_scrolledText.width: 680
*data_decl_scrolledText.height: 160
*data_decl_scrolledText.x: 0
*data_decl_scrolledText.y: 0
*data_decl_scrolledText.columns: 80
*data_decl_scrolledText.editMode: "multi_line_edit"
*data_decl_scrolledText.resizeHeight: "true"
*data_decl_scrolledText.resizeWidth: "true"
*data_decl_scrolledText.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*data_decl_scrolledText.modifyVerifyCallback.source: public
*data_decl_scrolledText.modifyVerifyCallback: text_maius_callback

*form9.class: form
*form9.parent: data_pane
*form9.static: true
*form9.name: form9
*form9.unitType: "pixels"
*form9.x: 10
*form9.y: 210
*form9.width: 690
*form9.height: 300

*labelGadget10.class: labelGadget
*labelGadget10.parent: form9
*labelGadget10.static: true
*labelGadget10.name: labelGadget10
*labelGadget10.x: 20
*labelGadget10.y: 10
*labelGadget10.width: 160
*labelGadget10.height: 20
*labelGadget10.alignment: "alignment_beginning"
*labelGadget10.bottomAttachment: "attach_none"
*labelGadget10.labelString: "User code"
*labelGadget10.leftAttachment: "attach_form"
*labelGadget10.leftOffset: 20
*labelGadget10.rightAttachment: "attach_none"
*labelGadget10.topAttachment: "attach_form"
*labelGadget10.topOffset: 10

*ok_data_pb.class: pushButton
*ok_data_pb.parent: form9
*ok_data_pb.static: true
*ok_data_pb.name: ok_data_pb
*ok_data_pb.x: 20
*ok_data_pb.y: 300
*ok_data_pb.width: 100
*ok_data_pb.height: 30
*ok_data_pb.bottomAttachment: "attach_form"
*ok_data_pb.bottomOffset: 10
*ok_data_pb.leftAttachment: "attach_form"
*ok_data_pb.leftOffset: 20
*ok_data_pb.rightAttachment: "attach_none"
*ok_data_pb.rightOffset: 0
*ok_data_pb.topAttachment: "attach_none"
*ok_data_pb.topOffset: 0
*ok_data_pb.labelString: "Ok"
*ok_data_pb.activateCallback: {\
memo_textI2(True);\
}

*scrolledWindow6.class: scrolledWindow
*scrolledWindow6.parent: form9
*scrolledWindow6.static: true
*scrolledWindow6.name: scrolledWindow6
*scrolledWindow6.scrollingPolicy: "application_defined"
*scrolledWindow6.unitType: "pixels"
*scrolledWindow6.x: 10
*scrolledWindow6.y: 40
*scrolledWindow6.visualPolicy: "variable"
*scrolledWindow6.scrollBarDisplayPolicy: "static"
*scrolledWindow6.shadowThickness: 0
*scrolledWindow6.bottomAttachment: "attach_widget"
*scrolledWindow6.bottomOffset: 10
*scrolledWindow6.bottomWidget: "ok_data_pb"
*scrolledWindow6.leftAttachment: "attach_form"
*scrolledWindow6.leftOffset: 20
*scrolledWindow6.rightAttachment: "attach_form"
*scrolledWindow6.rightOffset: 20
*scrolledWindow6.topAttachment: "attach_widget"
*scrolledWindow6.topOffset: 10
*scrolledWindow6.topWidget: "labelGadget10"

*data_code_scrolledText.class: scrolledText
*data_code_scrolledText.parent: scrolledWindow6
*data_code_scrolledText.static: false
*data_code_scrolledText.name: data_code_scrolledText
*data_code_scrolledText.width: 690
*data_code_scrolledText.height: 220
*data_code_scrolledText.x: 0
*data_code_scrolledText.y: 0
*data_code_scrolledText.columns: 80
*data_code_scrolledText.editMode: "multi_line_edit"
*data_code_scrolledText.resizeHeight: "true"
*data_code_scrolledText.resizeWidth: "true"
*data_code_scrolledText.fontList: "-Adobe-Courier-Bold-R-Normal--14-140-75-75-M-90-ISO8859-1"
*data_code_scrolledText.modifyVerifyCallback.source: public
*data_code_scrolledText.modifyVerifyCallback: text_maius_callback

*apply_data_pb.class: pushButton
*apply_data_pb.parent: form9
*apply_data_pb.static: true
*apply_data_pb.name: apply_data_pb
*apply_data_pb.x: 140
*apply_data_pb.y: 300
*apply_data_pb.width: 90
*apply_data_pb.height: 28
*apply_data_pb.labelString: "Apply"
*apply_data_pb.bottomAttachment: "attach_form"
*apply_data_pb.bottomOffset: 10
*apply_data_pb.leftAttachment: "attach_widget"
*apply_data_pb.leftOffset: 20
*apply_data_pb.leftWidget: "ok_data_pb"
*apply_data_pb.rightAttachment: "attach_none"
*apply_data_pb.topAttachment: "attach_none"
*apply_data_pb.topOffset: 0
*apply_data_pb.activateCallback: {\
memo_textI2(False);\
}

*cancel_data_pb.class: pushButton
*cancel_data_pb.parent: form9
*cancel_data_pb.static: true
*cancel_data_pb.name: cancel_data_pb
*cancel_data_pb.x: 250
*cancel_data_pb.y: 300
*cancel_data_pb.width: 90
*cancel_data_pb.height: 28
*cancel_data_pb.labelString: "Cancel"
*cancel_data_pb.bottomAttachment: "attach_form"
*cancel_data_pb.bottomOffset: 10
*cancel_data_pb.leftAttachment: "attach_widget"
*cancel_data_pb.leftOffset: 20
*cancel_data_pb.leftWidget: "apply_data_pb"
*cancel_data_pb.rightAttachment: "attach_none"
*cancel_data_pb.topAttachment: "attach_none"
*cancel_data_pb.topOffset: 0
*cancel_data_pb.activateCallback: {\
UxDestroySwidget (dbox_user_data);\
dbox_userdata_managed = False;\
}

