! UIMX ascii 2.0 key: 4983                                                      

*nmod_dialog_config.class: dialogShell
*nmod_dialog_config.parent: NO_PARENT
*nmod_dialog_config.static: true
*nmod_dialog_config.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo nmod_dialog_config.i\
   tipo \
   release 2.22\
   data 5/9/95\
   reserved @(#)nmod_dialog_config.i	2.22\
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
/* INCLUDE FILES                                                */\
/****************************************************************/\
\
#include <stdio.h>\
#include <Xm/Xm.h>\
\
\
#ifndef LIBUTILX\
#include <libutilx.h>\
#define LIBUTILX\
#endif\
\
#include "definizioni.h"\
\
/****************************************************************/\
/* VARIABILI GLOBALI ESTERNE                                    */\
/****************************************************************/\
\
/* variabili esterne */\
extern int num_var_stato, num_var_algebriche;\
extern int num_var_ingresso, num_dati_geometrici;\
\
extern Boolean bool_dialog_config;\
extern Boolean nmod_def_initialized;\
\
extern int option_scelto;\
\
extern int jac_rows, jac_cols;\
\
extern swidget pb_nmod_save,pb_nmod_jactopology,nmod_bboard,pb_nmod_JC,\
               pb_nmod_residual, pb_nmod_D1;\
\
extern Dialog_geometry geom_attention;\
extern Widget attention_wdg;\
\
extern char message[];\
\
/********************************************************************/\
/* VARIABILI GLOBALI 		                                    */\
/********************************************************************/\
\
byte jacobian_type;
*nmod_dialog_config.ispecdecl:
*nmod_dialog_config.funcdecl: swidget create_nmod_dialog_config()\

*nmod_dialog_config.funcname: create_nmod_dialog_config
*nmod_dialog_config.funcdef: "swidget", "<create_nmod_dialog_config>(%)"
*nmod_dialog_config.icode: char value[10];\
\
if (nmod_def_initialized)\
{\
   set_something(UxGetWidget(pb_nmod_jactopology),XmNsensitive,False);\
   set_something(UxGetWidget(pb_nmod_JC),XmNsensitive,False);\
   set_something(UxGetWidget(pb_nmod_residual),XmNsensitive,False);\
   set_something(UxGetWidget(pb_nmod_D1),XmNsensitive,False);\
}
*nmod_dialog_config.fcode: sprintf(value,"%-3d",num_var_stato);\
XmTextSetString(UxGetWidget(nmod_dialog_text1), value);\
\
sprintf(value,"%-3d",num_var_algebriche);\
XmTextSetString(UxGetWidget(nmod_dialog_text2), value);\
\
sprintf(value,"%-3d",num_var_ingresso);\
XmTextSetString(UxGetWidget(nmod_dialog_text3), value);\
\
sprintf(value,"%-3d",num_dati_geometrici);\
XmTextSetString(UxGetWidget(nmod_dialog_text4), value);\
\
bool_dialog_config = False;\
\
printf("jacobian_type=%d\n",jacobian_type);\
if(jacobian_type)\
   set_something(jac_optMenu,XmNmenuHistory,num_jacMenu_pb);\
\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*nmod_dialog_config.auxdecl: /*** test_input_setup(text_swdg)\
 ***   Parametri:\
 ***     swidget text_swdg : text input\
Controlla l'input nella window di setup. Ritorna il numero positivo se\
tutto e' corretto, altrimenti ritorna -1 */\
test_input_setup(text_swdg)\
swidget text_swdg;\
{\
   char *str_val;\
   int valore, last_pos;\
\
   str_val = XmTextGetString(UxGetWidget(text_swdg));\
   if (!IsNumeric(str_val))  \
   {\
      scrivi_messaggio("Invalid setup value. Modify to continue.");\
      last_pos = XmTextGetLastPosition (UxGetWidget(text_swdg));\
      XmTextSetSelection (UxGetWidget(text_swdg),0,last_pos,CurrentTime);\
      return(-1);\
   }\
   sscanf(str_val,"%3d",&valore);\
   XmStringFree(str_val);\
\
   if (valore < 0)\
   {\
      scrivi_messaggio("Negative input value. Modify to continue.");\
      last_pos = XmTextGetLastPosition (UxGetWidget(text_swdg));\
      XmTextSetSelection (UxGetWidget(text_swdg),0,last_pos,CurrentTime);\
      return(-1);\
   }\
   return(valore);\
}\
\
/*** chiudi_dlg_config()\
 *** chiude la window di configurazione delle variabili (OK e CANCEL) ***/\
chiudi_dlg_config()\
{\
/* cancella la window */\
   UxDestroySwidget(nmod_dialog_config);\
\
/* riabilita le voci di menu se e' il caso */\
   if (nmod_def_initialized)\
   {\
      set_something(UxGetWidget(pb_nmod_jactopology),XmNsensitive,True);\
      set_something(UxGetWidget(pb_nmod_JC),XmNsensitive,True);\
      set_something(UxGetWidget(pb_nmod_residual),XmNsensitive,True);\
      set_something(UxGetWidget(pb_nmod_D1),XmNsensitive,True);\
   }\
\
   bool_dialog_config = True;\
}
*nmod_dialog_config.name: nmod_dialog_config
*nmod_dialog_config.x: 180
*nmod_dialog_config.y: 680
*nmod_dialog_config.width: 100
*nmod_dialog_config.height: 100
*nmod_dialog_config.title: "NEWMOD - INPUT/OUTPUT VARIABLES SETUP"
*nmod_dialog_config.geometry: "+785+145"
*nmod_dialog_config.keyboardFocusPolicy: "explicit"

*nmod_dialog_form1.class: form
*nmod_dialog_form1.parent: nmod_dialog_config
*nmod_dialog_form1.static: true
*nmod_dialog_form1.name: nmod_dialog_form1
*nmod_dialog_form1.unitType: "pixels"
*nmod_dialog_form1.x: 585
*nmod_dialog_form1.y: 195
*nmod_dialog_form1.width: 370
*nmod_dialog_form1.height: 310
*nmod_dialog_form1.autoUnmanage: "false"

*nmod_dialog_label1.class: label
*nmod_dialog_label1.parent: nmod_dialog_form1
*nmod_dialog_label1.static: true
*nmod_dialog_label1.name: nmod_dialog_label1
*nmod_dialog_label1.x: 10
*nmod_dialog_label1.y: 30
*nmod_dialog_label1.width: 190
*nmod_dialog_label1.height: 35
*nmod_dialog_label1.alignment: "alignment_beginning"
*nmod_dialog_label1.labelString: "Number of state output variables:"
*nmod_dialog_label1.leftAttachment: "attach_form"
*nmod_dialog_label1.leftOffset: 10
*nmod_dialog_label1.topOffset: 15
*nmod_dialog_label1.rightAttachment: "attach_position"
*nmod_dialog_label1.rightPosition: 78
*nmod_dialog_label1.topAttachment: "attach_form"

*nmod_dialog_label2.class: label
*nmod_dialog_label2.parent: nmod_dialog_form1
*nmod_dialog_label2.static: true
*nmod_dialog_label2.name: nmod_dialog_label2
*nmod_dialog_label2.x: 10
*nmod_dialog_label2.y: 75
*nmod_dialog_label2.width: 190
*nmod_dialog_label2.height: 35
*nmod_dialog_label2.alignment: "alignment_beginning"
*nmod_dialog_label2.topAttachment: "attach_widget"
*nmod_dialog_label2.topOffset: 15
*nmod_dialog_label2.topWidget: "nmod_dialog_label1"
*nmod_dialog_label2.labelString: "Number of algebraic output variables:"
*nmod_dialog_label2.rightAttachment: "attach_position"
*nmod_dialog_label2.rightPosition: 78
*nmod_dialog_label2.leftAttachment: "attach_form"
*nmod_dialog_label2.leftOffset: 10

*nmod_dialog_label3.class: label
*nmod_dialog_label3.parent: nmod_dialog_form1
*nmod_dialog_label3.static: true
*nmod_dialog_label3.name: nmod_dialog_label3
*nmod_dialog_label3.x: 10
*nmod_dialog_label3.y: 120
*nmod_dialog_label3.width: 190
*nmod_dialog_label3.height: 35
*nmod_dialog_label3.alignment: "alignment_beginning"
*nmod_dialog_label3.labelString: "Number of input variables:"
*nmod_dialog_label3.topAttachment: "attach_widget"
*nmod_dialog_label3.topOffset: 15
*nmod_dialog_label3.topWidget: "nmod_dialog_label2"
*nmod_dialog_label3.rightAttachment: "attach_position"
*nmod_dialog_label3.rightPosition: 78
*nmod_dialog_label3.leftAttachment: "attach_form"
*nmod_dialog_label3.leftOffset: 10

*nmod_dialog_label4.class: label
*nmod_dialog_label4.parent: nmod_dialog_form1
*nmod_dialog_label4.static: true
*nmod_dialog_label4.name: nmod_dialog_label4
*nmod_dialog_label4.x: 10
*nmod_dialog_label4.y: 160
*nmod_dialog_label4.width: 220
*nmod_dialog_label4.height: 35
*nmod_dialog_label4.alignment: "alignment_beginning"
*nmod_dialog_label4.labelString: "Number of geometrical data:"
*nmod_dialog_label4.topAttachment: "attach_widget"
*nmod_dialog_label4.topOffset: 15
*nmod_dialog_label4.topWidget: "nmod_dialog_label3"
*nmod_dialog_label4.rightAttachment: "attach_position"
*nmod_dialog_label4.rightPosition: 78
*nmod_dialog_label4.leftAttachment: "attach_form"
*nmod_dialog_label4.leftOffset: 10

*nmod_dialog_text1.class: text
*nmod_dialog_text1.parent: nmod_dialog_form1
*nmod_dialog_text1.static: true
*nmod_dialog_text1.name: nmod_dialog_text1
*nmod_dialog_text1.x: 240
*nmod_dialog_text1.y: 20
*nmod_dialog_text1.width: 60
*nmod_dialog_text1.height: 35
*nmod_dialog_text1.leftAttachment: "attach_position"
*nmod_dialog_text1.leftOffset: 0
*nmod_dialog_text1.leftPosition: 80
*nmod_dialog_text1.rightAttachment: "attach_form"
*nmod_dialog_text1.rightOffset: 10
*nmod_dialog_text1.topOffset: 15
*nmod_dialog_text1.topAttachment: "attach_form"
*nmod_dialog_text1.columns: 2
*nmod_dialog_text1.maxLength: 3
*nmod_dialog_text1.fontList: "*Courier-Bold-R-Normal--14-140-*"

*nmod_dialog_text2.class: text
*nmod_dialog_text2.parent: nmod_dialog_form1
*nmod_dialog_text2.static: true
*nmod_dialog_text2.name: nmod_dialog_text2
*nmod_dialog_text2.x: 240
*nmod_dialog_text2.y: 70
*nmod_dialog_text2.width: 60
*nmod_dialog_text2.height: 35
*nmod_dialog_text2.leftAttachment: "attach_position"
*nmod_dialog_text2.leftOffset: 0
*nmod_dialog_text2.leftPosition: 80
*nmod_dialog_text2.topAttachment: "attach_widget"
*nmod_dialog_text2.topOffset: 15
*nmod_dialog_text2.topWidget: "nmod_dialog_text1"
*nmod_dialog_text2.rightAttachment: "attach_form"
*nmod_dialog_text2.rightOffset: 10
*nmod_dialog_text2.columns: 2
*nmod_dialog_text2.maxLength: 3

*nmod_dialog_text3.class: text
*nmod_dialog_text3.parent: nmod_dialog_form1
*nmod_dialog_text3.static: true
*nmod_dialog_text3.name: nmod_dialog_text3
*nmod_dialog_text3.x: 240
*nmod_dialog_text3.y: 120
*nmod_dialog_text3.width: 60
*nmod_dialog_text3.height: 35
*nmod_dialog_text3.leftAttachment: "attach_position"
*nmod_dialog_text3.leftOffset: 0
*nmod_dialog_text3.leftPosition: 80
*nmod_dialog_text3.rightAttachment: "attach_form"
*nmod_dialog_text3.rightOffset: 10
*nmod_dialog_text3.topAttachment: "attach_widget"
*nmod_dialog_text3.topPosition: 0
*nmod_dialog_text3.topWidget: "nmod_dialog_text2"
*nmod_dialog_text3.topOffset: 15
*nmod_dialog_text3.columns: 2
*nmod_dialog_text3.maxLength: 3

*nmod_dialog_text4.class: text
*nmod_dialog_text4.parent: nmod_dialog_form1
*nmod_dialog_text4.static: true
*nmod_dialog_text4.name: nmod_dialog_text4
*nmod_dialog_text4.x: 240
*nmod_dialog_text4.y: 180
*nmod_dialog_text4.width: 60
*nmod_dialog_text4.height: 35
*nmod_dialog_text4.leftAttachment: "attach_position"
*nmod_dialog_text4.leftOffset: 0
*nmod_dialog_text4.leftPosition: 80
*nmod_dialog_text4.rightAttachment: "attach_form"
*nmod_dialog_text4.rightOffset: 10
*nmod_dialog_text4.topOffset: 15
*nmod_dialog_text4.topWidget: "nmod_dialog_text3"
*nmod_dialog_text4.topAttachment: "attach_widget"
*nmod_dialog_text4.columns: 2
*nmod_dialog_text4.maxLength: 3

*nmod_dialog_ok.class: pushButton
*nmod_dialog_ok.parent: nmod_dialog_form1
*nmod_dialog_ok.static: true
*nmod_dialog_ok.name: nmod_dialog_ok
*nmod_dialog_ok.x: 20
*nmod_dialog_ok.y: 260
*nmod_dialog_ok.width: 90
*nmod_dialog_ok.height: 30
*nmod_dialog_ok.bottomAttachment: "attach_form"
*nmod_dialog_ok.bottomOffset: 10
*nmod_dialog_ok.labelString: "Ok"
*nmod_dialog_ok.leftOffset: 10
*nmod_dialog_ok.activateCallback: {\
char *value;\
int num_st, num_alg, num_in, num_dati;\
int last_pos;\
\
if ( (num_st = test_input_setup(nmod_dialog_text1)) == -1)\
   return;\
\
if ( (num_alg = test_input_setup(nmod_dialog_text2)) == -1)\
   return;\
\
if ( (num_in = test_input_setup(nmod_dialog_text3)) == -1)\
   return;\
\
if ( (num_dati = test_input_setup(nmod_dialog_text4)) == -1)\
   return;\
\
if ( num_st + num_alg > MAX_VARIABILI_USCITA )\
{\
   sprintf(message,\
           "The number of output variable must be less or equal than %d. Modify to continue.",\
           MAX_VARIABILI_USCITA);\
   scrivi_messaggio(message);\
   attention_wdg = (Widget) attention(UxTopLevel,message,MAPPA,geom_attention);\
   last_pos = XmTextGetLastPosition (UxGetWidget(nmod_dialog_text1));\
   XmTextSetSelection (UxGetWidget(nmod_dialog_text1),0,last_pos,CurrentTime);\
   return;\
}\
\
if ( num_in > MAX_VARIABILI_INGRESSO )\
{\
   sprintf(message,\
           "The number of input variable must be less or equal than %d. Modify to continue.",\
            MAX_VARIABILI_INGRESSO);\
   scrivi_messaggio(message);\
   attention_wdg = (Widget) attention(UxTopLevel,message,MAPPA,geom_attention);\
   last_pos = XmTextGetLastPosition (UxGetWidget(nmod_dialog_text3));\
   XmTextSetSelection (UxGetWidget(nmod_dialog_text3),0,last_pos,CurrentTime);\
   return;\
}\
\
if ( num_dati > MAX_DATI_GEOMETRICI )\
{\
   sprintf(message,\
           "The number of geometrical data must be less or equal than %d. Modify to continue.",\
           MAX_DATI_GEOMETRICI);\
   scrivi_messaggio(message);\
   attention_wdg = (Widget) attention(UxTopLevel,message,MAPPA,geom_attention);\
   last_pos = XmTextGetLastPosition (UxGetWidget(nmod_dialog_text4));\
   XmTextSetSelection (UxGetWidget(nmod_dialog_text4),0,last_pos,CurrentTime);\
   return;\
}\
chiudi_dlg_config();\
\
/* Adesso l'utente deve confermare le nuove informazioni. Quindi le voci di */\
/* menu (jacobiano, residui, ecc..) sono disabilitate */\
menu_newmod_init();\
\
alloca_text_widget(UxGetWidget(nmod_bboard),num_st, num_alg, num_in, num_dati);\
}
*nmod_dialog_ok.leftAttachment: "attach_form"

*nmod_dialog_cancel.class: pushButton
*nmod_dialog_cancel.parent: nmod_dialog_form1
*nmod_dialog_cancel.static: true
*nmod_dialog_cancel.name: nmod_dialog_cancel
*nmod_dialog_cancel.x: 140
*nmod_dialog_cancel.y: 260
*nmod_dialog_cancel.width: 80
*nmod_dialog_cancel.height: 30
*nmod_dialog_cancel.bottomAttachment: "attach_form"
*nmod_dialog_cancel.bottomOffset: 10
*nmod_dialog_cancel.labelString: "Cancel"
*nmod_dialog_cancel.leftAttachment: "attach_widget"
*nmod_dialog_cancel.leftOffset: 15
*nmod_dialog_cancel.leftWidget: "nmod_dialog_ok"
*nmod_dialog_cancel.topAttachment: "attach_none"
*nmod_dialog_cancel.topOffset: 0
*nmod_dialog_cancel.activateCallback: {\
chiudi_dlg_config();\
}

*separator1.class: separator
*separator1.parent: nmod_dialog_form1
*separator1.static: true
*separator1.name: separator1
*separator1.x: 20
*separator1.y: 230
*separator1.width: 440
*separator1.height: 10
*separator1.bottomOffset: 10
*separator1.leftAttachment: "attach_form"
*separator1.leftOffset: 10
*separator1.rightAttachment: "attach_form"
*separator1.rightOffset: 10
*separator1.topAttachment: "attach_none"
*separator1.topOffset: 0
*separator1.topWidget: ""
*separator1.bottomAttachment: "attach_widget"
*separator1.bottomWidget: "nmod_dialog_ok"

*nmod_dialog_label5.class: label
*nmod_dialog_label5.parent: nmod_dialog_form1
*nmod_dialog_label5.static: true
*nmod_dialog_label5.name: nmod_dialog_label5
*nmod_dialog_label5.x: 10
*nmod_dialog_label5.y: 210
*nmod_dialog_label5.width: 260
*nmod_dialog_label5.height: 35
*nmod_dialog_label5.bottomAttachment: "attach_none"
*nmod_dialog_label5.bottomOffset: 0
*nmod_dialog_label5.leftAttachment: "attach_form"
*nmod_dialog_label5.leftOffset: 10
*nmod_dialog_label5.rightAttachment: "attach_position"
*nmod_dialog_label5.rightPosition: 60
*nmod_dialog_label5.topAttachment: "attach_widget"
*nmod_dialog_label5.topOffset: 15
*nmod_dialog_label5.topWidget: "nmod_dialog_label4"
*nmod_dialog_label5.alignment: "alignment_beginning"
*nmod_dialog_label5.labelString: "Jacobian computation:"

*jac_optMenu.class: rowColumn
*jac_optMenu.parent: nmod_dialog_form1
*jac_optMenu.static: true
*jac_optMenu.name: jac_optMenu
*jac_optMenu.rowColumnType: "menu_option"
*jac_optMenu.subMenuId: "jac_optMenu_pane"
*jac_optMenu.x: 252
*jac_optMenu.y: 225
*jac_optMenu.bottomAttachment: "attach_none"
*jac_optMenu.leftAttachment: "attach_none"
*jac_optMenu.leftOffset: 0
*jac_optMenu.rightAttachment: "attach_form"
*jac_optMenu.rightOffset: 10
*jac_optMenu.topAttachment: "attach_widget"
*jac_optMenu.topOffset: 15
*jac_optMenu.topWidget: "nmod_dialog_text4"

*jac_optMenu_pane.class: rowColumn
*jac_optMenu_pane.parent: jac_optMenu
*jac_optMenu_pane.static: true
*jac_optMenu_pane.name: jac_optMenu_pane
*jac_optMenu_pane.rowColumnType: "menu_pulldown"

*anal_jacMenu_pb.class: pushButton
*anal_jacMenu_pb.parent: jac_optMenu_pane
*anal_jacMenu_pb.static: true
*anal_jacMenu_pb.name: anal_jacMenu_pb
*anal_jacMenu_pb.labelString: "Analytical"
*anal_jacMenu_pb.mnemonic: "A"
*anal_jacMenu_pb.activateCallback: {jacobian_type = ANALYTICAL;}

*num_jacMenu_pb.class: pushButton
*num_jacMenu_pb.parent: jac_optMenu_pane
*num_jacMenu_pb.static: true
*num_jacMenu_pb.name: num_jacMenu_pb
*num_jacMenu_pb.labelString: "Numerical"
*num_jacMenu_pb.mnemonic: "N"
*num_jacMenu_pb.activateCallback: {jacobian_type = NUMERICAL;}

