! UIMX ascii 2.8 key: 3294                                                      

*initialCondition.class: form
*initialCondition.gbldecl: #include <stdio.h>\
#include <Xm/Xm.h>\
#include <Xm/Text.h>\
#include <Xm/Label.h>\
#include <malloc.h>\
#include <X11/Intrinsic.h>\
\
#ifndef DESIGN_TIME\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
\
extern int _MAX_SNAP_SHOT;\
 \
#include "init_ci.h"\
#include "cursore.h"\
\
XtIntervalId timer_initialCondition;\
int tasto_initic_attivabile = False;\
\
#include "parametri.h" \
#include "bistrutt.h"\
#include "preview.h"\
#include "option.h"\
extern OPTIONS_FLAGS options;\
extern Boolean *IcProt;\
\
extern int snap_interface_active;\
SNTAB *snap_header;\
int colore_sfondo;\
#endif\
\
extern int inizializzazione;\
extern int isSuperuser;\
\
extern int get_colors();\
extern int get_colore_sfondo();\
extern int set_colore_riga_snap();\
extern int read_lista_snap();\
extern int carica_ci();\
extern int carica_bt();\
extern int esegui_snap();\
Boolean cutCopyCiBuffer; /* 1 = pieno */\
extern swidget masterMenu;\
extern swidget icCommentReqform;\
extern swidget create_icCommentReqform();\
extern swidget previewSnap;\
extern swidget create_previewSnap();\
int nuova_attivazione;\
#include "messaggi.h"
*initialCondition.ispecdecl:
*initialCondition.funcdecl: swidget create_initialCondition(padre)\
Widget padre;
*initialCondition.funcname: create_initialCondition
*initialCondition.funcdef: "swidget", "<create_initialCondition>(%)"
*initialCondition.argdecl: Widget padre;
*initialCondition.arglist: padre
*initialCondition.arglist.padre: "Widget", "%padre%"
*initialCondition.icode: #ifndef DESIGN_TIME\
set_cursor (padre,CLOCK);\
#endif\
cutCopyCiBuffer = False;
*initialCondition.fcode: #ifndef DESIGN_TIME\
XtManageChild (UxGetWidget(icMenu));\
AllocaAreeSnapshot ();\
aggiorna_opt_snap (UxGetWidget(IcRc), &options);\
add_item_initial_condition(UxGetWidget(IcRc));\
snap_header = (SNTAB*)malloc(sizeof(SNTAB)*_MAX_SNAP_SHOT);\
read_lista_snap (snap_header);\
display_header_snap (snap_header);\
\
colore_sfondo = read_background_color (rtrn);\
UxPopupInterface (initialCondition, no_grab);\
snap_interface_active = 1; /* memoria di interfaccia attiva */\
set_cursor (padre,NORMALE);\
tasto_initic_attivabile = False;\
nuova_attivazione = 1; /* per refresh */\
attiva_timer_initialCondition(initialCondition);\
#endif\
\
return(rtrn);\

*initialCondition.auxdecl: /************************************************************************/\
int add_item_initial_condition(parent)\
Widget parent;\
{\
\
   crea_snapshot_entry(parent);	\
 	   \
}\
/******************************************************************/\
void IcSelActivate (parent, dati, reason)\
Widget parent;\
char *dati;\
XmAnyCallbackStruct *reason;\
{\
#ifndef DESIGN_TIME\
 \
int tipo_entry;\
static int prec_sel = 0;\
Boolean permissivo;\
Boolean permissivo_paste;\
   \
   ic_sel = atoi(dati);\
	\
   tipo_entry = reason->reason;\
\
   switch (tipo_entry)\
      {\
      case XmCR_FOCUS:\
	if ((prec_sel > 0) && (prec_sel != ic_sel))\
	   set_colore_riga_snap(prec_sel-1, colore_sfondo);\
        set_colore_riga_snap(ic_sel-1, colore_app[0]); \
	break;       	   \
      case XmCR_LOSING_FOCUS:\
      default:\
         break; \
      }\
   \
/*   printf ("selezionato ic %d\n",ic_sel);   */\
/*\
 * abilitazione superuser\
 */\
   if (!isSuperuser)       /* se non siamo superuser     */ \
      {\
      if (*(IcProt+ic_sel-1)) /* e la ic e' protetta */\
         permissivo = False;\
      else\
         permissivo = True;\
      }\
   else                    /* se siamo superuser          */\
      permissivo = True;\
/* \
 * abilitazione tasto check\
 */\
   if (isSuperuser)       /* se siamo superuser     */\
     {\
     if ((snap_header+(ic_sel-1))->mod == 1)    /* se e' marcata mofificata da net_compi */\
         {\
         XtVaSetValues (icMenuEditCheck, XmNsensitive, True, NULL);\
         }\
     else\
         {\
         XtVaSetValues (icMenuEditCheck, XmNsensitive, False, NULL);\
         }\
     }\
/*\
 * per cut/copy and paste\
 */\
   permissivo_paste = cutCopyCiBuffer & permissivo;\
\
   if (((snap_header+(ic_sel-1))->stat == 1) && /* snap occupato  */\
       ((snap_header+(ic_sel-1))->mod == 0))     /* congruente con il simulatore */\
      {\
      tasto_initic_attivabile = True;\
      XtVaSetValues (UxGetWidget(icSavepb), XmNsensitive, True & permissivo, NULL);\
      XtVaSetValues (UxGetWidget(icViewpb), XmNsensitive, True, NULL);\
      XtVaSetValues (UxGetWidget(icMenuEditCutPb), XmNsensitive, True &  permissivo, NULL);\
      XtVaSetValues (UxGetWidget(icMenuEditCopy), XmNsensitive, True, NULL); \
\
      XtVaSetValues (UxGetWidget(IcRcPopupSave), XmNsensitive, True & permissivo, NULL);\
      XtVaSetValues (UxGetWidget(IcRcPopupView), XmNsensitive, True, NULL);\
      }\
   else\
      {\
      tasto_initic_attivabile = False;\
      XtVaSetValues (UxGetWidget(icSavepb), XmNsensitive, True & permissivo, NULL);\
      XtVaSetValues (UxGetWidget(icViewpb), XmNsensitive, False, NULL);\
\
      if ((snap_header+(ic_sel-1))->mod == 1) /* incongruente col simulatore */\
          XtVaSetValues (UxGetWidget(icMenuEditCutPb), XmNsensitive, True, NULL);\
      else\
          XtVaSetValues (UxGetWidget(icMenuEditCutPb), XmNsensitive, False, NULL);\
\
      XtVaSetValues (UxGetWidget(icMenuEditCopy), XmNsensitive, False, NULL); \
\
      XtVaSetValues (UxGetWidget(IcRcPopupView), XmNsensitive,False, NULL);\
      XtVaSetValues (UxGetWidget(IcRcPopupSave), XmNsensitive, True & permissivo, NULL);\
      }\
\
   XtVaSetValues (UxGetWidget(icMenuEditPaste), XmNsensitive, permissivo_paste, NULL);\
\
   prec_sel = ic_sel;\
   return;\
\
#endif\
}\
/******************************************************************/\
#ifndef DESIGN_TIME\
int aggiorna_opt_snap (w,p)\
Widget w;\
OPTIONS_FLAGS *p;\
{\
   if (! p->options_snapshot.save)\
      XtUnmanageChild (UxGetWidget(icSavepb));\
   else\
      XtManageChild (UxGetWidget(icSavepb));\
\
   if (! p->options_snapshot.delete)\
      XtUnmanageChild (UxGetWidget(icMenuEditCutPb));\
   else\
      XtManageChild (UxGetWidget(icMenuEditCutPb));\
\
   if (! p->options_snapshot.copy_and_paste)\
      {\
      XtUnmanageChild (UxGetWidget(icMenuEditCopy));\
      XtUnmanageChild (UxGetWidget(icMenuEditPaste));\
      }\
   else\
      {\
      XtManageChild (UxGetWidget(icMenuEditCopy));\
      XtManageChild (UxGetWidget(icMenuEditPaste));\
      }\
   return (0);   \
}\
#endif
*initialCondition.name.source: public
*initialCondition.static: false
*initialCondition.name: initialCondition
*initialCondition.parent: NO_PARENT
*initialCondition.defaultShell: topLevelShell
*initialCondition.resizePolicy: "resize_none"
*initialCondition.unitType: "pixels"
*initialCondition.x: 324
*initialCondition.y: 90
*initialCondition.width: 650
*initialCondition.height: 433
*initialCondition.buttonFontList: "9x15bold"
*initialCondition.destroyCallback: {\
#ifndef DESIGN_TIME\
set_cursor (padre,CLOCK);\
snap_interface_active = 0;\
tasto_initic_attivabile = False;\
free (snap_header);\
stop_timer (timer_initialCondition);\
set_cursor (padre,NORMALE);\
#endif\
}

*icMenu.class: rowColumn
*icMenu.static: true
*icMenu.name: icMenu
*icMenu.parent: initialCondition
*icMenu.rowColumnType: "menu_bar"
*icMenu.menuAccelerator: "<KeyUp>F10"
*icMenu.rightAttachment: "attach_form"
*icMenu.leftAttachment: "attach_form"
*icMenu.packing: "pack_tight"
*icMenu.menuHelpWidget: "ic_menu_help"
*icMenu.createManaged: "false"

*icMenuFile.class: rowColumn
*icMenuFile.static: true
*icMenuFile.name: icMenuFile
*icMenuFile.parent: icMenu
*icMenuFile.rowColumnType: "menu_pulldown"

*icMenuFilePrint.class: pushButton
*icMenuFilePrint.static: true
*icMenuFilePrint.name: icMenuFilePrint
*icMenuFilePrint.parent: icMenuFile
*icMenuFilePrint.labelString: "Print"
*icMenuFilePrint.activateCallback: {\
stampa_ci (initialCondition);\
}

*icMenuFile_b2.class: separator
*icMenuFile_b2.static: true
*icMenuFile_b2.name: icMenuFile_b2
*icMenuFile_b2.parent: icMenuFile

*icMenuFileQuitpb.class: pushButton
*icMenuFileQuitpb.static: true
*icMenuFileQuitpb.name: icMenuFileQuitpb
*icMenuFileQuitpb.parent: icMenuFile
*icMenuFileQuitpb.labelString: QuitMenuLabel
*icMenuFileQuitpb.mnemonic: "Q"
*icMenuFileQuitpb.activateCallback: {\
/****\
#ifndef DESIGN_TIME\
set_cursor (padre,CLOCK);\
snap_interface_active = 0;\
tasto_initic_attivabile = False;\
XtDestroyWidget (XtParent(UxGetWidget(initialCondition)));\
free (snap_header);\
stop_timer (timer_initialCondition);\
set_cursor (padre,NORMALE);\
#endif\
**********/\
DistruggiInterfaccia (XtParent(initialCondition));\
}

*icMenuEdit.class: rowColumn
*icMenuEdit.static: true
*icMenuEdit.name: icMenuEdit
*icMenuEdit.parent: icMenu
*icMenuEdit.rowColumnType: "menu_pulldown"

*icMenuEditCutPb.class: pushButton
*icMenuEditCutPb.name.source: public
*icMenuEditCutPb.static: false
*icMenuEditCutPb.name: icMenuEditCutPb
*icMenuEditCutPb.parent: icMenuEdit
*icMenuEditCutPb.labelString: CutMenuLabel
*icMenuEditCutPb.mnemonic: "C"
*icMenuEditCutPb.activateCallback: {\
#ifndef DESIGN_TIME\
int n;\
n = ic_sel;\
   cancella_ci (UxGetWidget(initialCondition),n);\
#endif\
}
*icMenuEditCutPb.sensitive: "false"

*icMenuEditSep1.class: separator
*icMenuEditSep1.static: true
*icMenuEditSep1.name: icMenuEditSep1
*icMenuEditSep1.parent: icMenuEdit
*icMenuEditSep1.separatorType: "shadow_etched_in"

*icMenuEditCopy.class: pushButton
*icMenuEditCopy.name.source: public
*icMenuEditCopy.static: false
*icMenuEditCopy.name: icMenuEditCopy
*icMenuEditCopy.parent: icMenuEdit
*icMenuEditCopy.labelString: "Copy"
*icMenuEditCopy.mnemonic: "p"
*icMenuEditCopy.activateCallback: {\
#ifndef DESIGN_TIME \
int n;\
n = ic_sel;\
copia_ci (UxGetWidget(initialCondition),\
          UxGetWidget(icMenuEditPaste),\
          n);\
#endif\
}
*icMenuEditCopy.sensitive: "false"

*icMenuEditPaste.class: pushButton
*icMenuEditPaste.name.source: public
*icMenuEditPaste.static: false
*icMenuEditPaste.name: icMenuEditPaste
*icMenuEditPaste.parent: icMenuEdit
*icMenuEditPaste.labelString: "Paste"
*icMenuEditPaste.mnemonic: "P"
*icMenuEditPaste.activateCallback: {\
#ifndef DESIGN_TIME\
int n;\
n = ic_sel;\
paste_ci (UxWidget, n);\
#endif\
}
*icMenuEditPaste.sensitive: "false"

*icMenuEdit_b5.class: separator
*icMenuEdit_b5.static: true
*icMenuEdit_b5.name: icMenuEdit_b5
*icMenuEdit_b5.parent: icMenuEdit

*icMenuEditCheck.class: pushButton
*icMenuEditCheck.static: true
*icMenuEditCheck.name: icMenuEditCheck
*icMenuEditCheck.parent: icMenuEdit
*icMenuEditCheck.labelString: "Check"
*icMenuEditCheck.sensitive: "false"
*icMenuEditCheck.activateCallback: {\
#ifndef DESIGN_TIME\
int n;\
n = ic_sel;\
accetta_ci (UxGetWidget(initialCondition),n);\
#endif\
}

*icMenuEditCheckAll.class: pushButton
*icMenuEditCheckAll.static: true
*icMenuEditCheckAll.name: icMenuEditCheckAll
*icMenuEditCheckAll.parent: icMenuEdit
*icMenuEditCheckAll.labelString: CheckAllLabel
*icMenuEditCheckAll.activateCallback: {\
#ifndef DESIGN_TIME\
int i;\
for (i=0; i<_MAX_SNAP_SHOT; i++)\
   {\
   if ((snap_header+i)->mod == 1) /* modificato simulatore */\
      {\
      accetta_ci (UxGetWidget(initialCondition),i+1);\
      }\
   }\
#endif\
}

*icMenuHelp.class: rowColumn
*icMenuHelp.static: true
*icMenuHelp.name: icMenuHelp
*icMenuHelp.parent: icMenu
*icMenuHelp.rowColumnType: "menu_pulldown"

*icMenuHelpCommand.class: pushButton
*icMenuHelpCommand.static: true
*icMenuHelpCommand.name: icMenuHelpCommand
*icMenuHelpCommand.parent: icMenuHelp
*icMenuHelpCommand.labelString: "Commands"
*icMenuHelpCommand.mnemonic: "C"
*icMenuHelpCommand.activateCallback: {printf ("help comandi\n");}

*ic_menu_file.class: cascadeButton
*ic_menu_file.static: true
*ic_menu_file.name: ic_menu_file
*ic_menu_file.parent: icMenu
*ic_menu_file.labelString: FileMenuLabel
*ic_menu_file.mnemonic: "F"
*ic_menu_file.subMenuId: "icMenuFile"

*ic_menu_edit.class: cascadeButton
*ic_menu_edit.static: true
*ic_menu_edit.name: ic_menu_edit
*ic_menu_edit.parent: icMenu
*ic_menu_edit.labelString: EditMenuLabel
*ic_menu_edit.mnemonic: "E"
*ic_menu_edit.subMenuId: "icMenuEdit"

*ic_menu_help.class: cascadeButton
*ic_menu_help.static: true
*ic_menu_help.name: ic_menu_help
*ic_menu_help.parent: icMenu
*ic_menu_help.labelString: HelpMenuLabel
*ic_menu_help.mnemonic: "H"
*ic_menu_help.subMenuId: "icMenuHelp"

*frame8.class: frame
*frame8.static: true
*frame8.name: frame8
*frame8.parent: initialCondition
*frame8.x: 0
*frame8.y: 0
*frame8.width: 690
*frame8.height: 80
*frame8.topAttachment: "attach_none"
*frame8.rightAttachment: "attach_form"
*frame8.leftAttachment: "attach_form"
*frame8.bottomAttachment: "attach_form"

*form27.class: form
*form27.static: true
*form27.name: form27
*form27.parent: frame8
*form27.resizePolicy: "resize_none"
*form27.x: 2
*form27.y: 20
*form27.width: 851
*form27.height: 82
*form27.defaultButton: "icViewpb"

*icQuitpb.class: pushButton
*icQuitpb.static: true
*icQuitpb.name: icQuitpb
*icQuitpb.parent: form27
*icQuitpb.x: 715
*icQuitpb.y: 15
*icQuitpb.width: 100
*icQuitpb.height: 52
*icQuitpb.labelString: "QUIT"
*icQuitpb.bottomAttachment: "attach_form"
*icQuitpb.leftAttachment: "attach_self"
*icQuitpb.rightAttachment: "attach_form"
*icQuitpb.rightOffset: 20
*icQuitpb.topAttachment: "attach_form"
*icQuitpb.topOffset: 15
*icQuitpb.bottomOffset: 15
*icQuitpb.activateCallback: {\
/****** in destroy callback di initialCondition\
#ifndef DESIGN_TIME\
set_cursor (padre,CLOCK);\
snap_interface_active = 0;\
tasto_initic_attivabile = False;\
free (snap_header);\
stop_timer (timer_initialCondition);\
set_cursor (padre,NORMALE);\
#endif\
***************/\
DistruggiInterfaccia (XtParent((Widget)UxClientData));\
}
*icQuitpb.activateCallbackClientData: UxGetWidget(initialCondition)

*icInitpb.class: pushButton
*icInitpb.static: true
*icInitpb.name: icInitpb
*icInitpb.parent: form27
*icInitpb.x: 20
*icInitpb.y: 15
*icInitpb.width: 100
*icInitpb.height: 52
*icInitpb.labelString: "LOAD"
*icInitpb.bottomAttachment: "attach_form"
*icInitpb.bottomOffset: 15
*icInitpb.rightAttachment: "attach_self"
*icInitpb.rightPosition: 0
*icInitpb.rightOffset: 0
*icInitpb.leftAttachment: "attach_form"
*icInitpb.leftOffset: 20
*icInitpb.topAttachment: "attach_form"
*icInitpb.topOffset: 15
*icInitpb.sensitive: "false"
*icInitpb.activateCallback: {\
#ifndef DESIGN_TIME\
carica_ci ((Widget)UxClientData, ic_sel);\
#endif\
\
}
*icInitpb.activateCallbackClientData: initialCondition

*icSavepb.class: pushButton
*icSavepb.static: true
*icSavepb.name: icSavepb
*icSavepb.parent: form27
*icSavepb.x: 148
*icSavepb.y: 15
*icSavepb.width: 100
*icSavepb.height: 52
*icSavepb.labelString: "SAVE"
*icSavepb.bottomAttachment: "attach_form"
*icSavepb.bottomOffset: 15
*icSavepb.leftAttachment: "attach_widget"
*icSavepb.leftOffset: 20
*icSavepb.leftWidget: "icInitpb"
*icSavepb.rightAttachment: "attach_self"
*icSavepb.topAttachment: "attach_form"
*icSavepb.topOffset: 15
*icSavepb.sensitive: "false"
*icSavepb.activateCallback: {\
#ifndef DESIGN_TIME\
salva_ci (UxGetWidget(initialCondition), ic_sel);\
#endif\
}

*icViewpb.class: pushButton
*icViewpb.static: true
*icViewpb.name: icViewpb
*icViewpb.parent: form27
*icViewpb.x: 275
*icViewpb.y: 15
*icViewpb.width: 100
*icViewpb.height: 52
*icViewpb.labelString: "VIEW"
*icViewpb.sensitive: "false"
*icViewpb.bottomAttachment: "attach_form"
*icViewpb.bottomOffset: 15
*icViewpb.leftAttachment: "attach_widget"
*icViewpb.leftOffset: 20
*icViewpb.leftWidget: "icSavepb"
*icViewpb.rightAttachment: "attach_self"
*icViewpb.topAttachment: "attach_form"
*icViewpb.topOffset: 15
*icViewpb.activateCallback: {\
char testo[20];\
#ifndef DESIGN_TIME\
printf ("preview ic n. %d \n",ic_sel);\
sprintf (testo,"I.C. %d",ic_sel);\
create_previewSnap(CI_VIEW,ic_sel,testo);\
#endif\
}

*initialConditionScrollW.class: scrolledWindow
*initialConditionScrollW.static: true
*initialConditionScrollW.name: initialConditionScrollW
*initialConditionScrollW.parent: initialCondition
*initialConditionScrollW.scrollingPolicy: "automatic"
*initialConditionScrollW.x: 15
*initialConditionScrollW.y: 60
*initialConditionScrollW.width: 700
*initialConditionScrollW.height: 255
*initialConditionScrollW.bottomAttachment: "attach_widget"
*initialConditionScrollW.bottomOffset: 10
*initialConditionScrollW.bottomWidget: "frame8"
*initialConditionScrollW.rightAttachment: "attach_form"
*initialConditionScrollW.rightOffset: 15
*initialConditionScrollW.leftAttachment: "attach_form"
*initialConditionScrollW.leftOffset: 15
*initialConditionScrollW.topAttachment: "attach_widget"
*initialConditionScrollW.topOffset: 20
*initialConditionScrollW.topWidget: "icMenu"

*IcRc.class: rowColumn
*IcRc.static: true
*IcRc.name: IcRc
*IcRc.parent: initialConditionScrollW
*IcRc.x: 2
*IcRc.y: 2
*IcRc.width: 600
*IcRc.height: 280
*IcRc.background: "#c2bab5"

*IcRcPopupMenu.class: rowColumn
*IcRcPopupMenu.static: true
*IcRcPopupMenu.name: IcRcPopupMenu
*IcRcPopupMenu.parent: IcRc
*IcRcPopupMenu.rowColumnType: "menu_popup"
*IcRcPopupMenu.menuAccelerator: "Shift <KeyUp>F10"

*IcRcPopupView.class: pushButton
*IcRcPopupView.static: true
*IcRcPopupView.name: IcRcPopupView
*IcRcPopupView.parent: IcRcPopupMenu
*IcRcPopupView.labelString: "View "
*IcRcPopupView.activateCallback: {\
char testo[20];\
#ifndef DESIGN_TIME\
printf ("preview ic n. %d \n",ic_sel);\
sprintf (testo,"I.C. %d",ic_sel);\
create_previewSnap(CI_VIEW,ic_sel,testo);\
#endif\
}
*IcRcPopupView.sensitive: "false"

*IcRcPopupMenu_p1_b2.class: separator
*IcRcPopupMenu_p1_b2.static: true
*IcRcPopupMenu_p1_b2.name: IcRcPopupMenu_p1_b2
*IcRcPopupMenu_p1_b2.parent: IcRcPopupMenu

*IcRcPopupLoad.class: pushButton
*IcRcPopupLoad.static: true
*IcRcPopupLoad.name: IcRcPopupLoad
*IcRcPopupLoad.parent: IcRcPopupMenu
*IcRcPopupLoad.labelString: "Load"
*IcRcPopupLoad.activateCallback: {\
#ifndef DESIGN_TIME\
carica_ci ((Widget)UxClientData, ic_sel);\
#endif\
}
*IcRcPopupLoad.activateCallbackClientData: initialCondition

*IcRcPopupSave.class: pushButton
*IcRcPopupSave.static: true
*IcRcPopupSave.name: IcRcPopupSave
*IcRcPopupSave.parent: IcRcPopupMenu
*IcRcPopupSave.labelString: SaveMenuLabel
*IcRcPopupSave.activateCallback: {\
#ifndef DESIGN_TIME\
salva_ci (UxGetWidget(initialCondition), ic_sel);\
#endif\
}

*IcRcPopupMenu_p1_b5.class: separator
*IcRcPopupMenu_p1_b5.static: true
*IcRcPopupMenu_p1_b5.name: IcRcPopupMenu_p1_b5
*IcRcPopupMenu_p1_b5.parent: IcRcPopupMenu

*IcRcPopupMenuPrint.class: pushButton
*IcRcPopupMenuPrint.static: true
*IcRcPopupMenuPrint.name: IcRcPopupMenuPrint
*IcRcPopupMenuPrint.parent: IcRcPopupMenu
*IcRcPopupMenuPrint.labelString: "Print"
*IcRcPopupMenuPrint.activateCallback: {\
stampa_ci (initialCondition);\
}

*IcRcPopupMenu_p1_b7.class: separator
*IcRcPopupMenu_p1_b7.static: true
*IcRcPopupMenu_p1_b7.name: IcRcPopupMenu_p1_b7
*IcRcPopupMenu_p1_b7.parent: IcRcPopupMenu

*IcRcPopupQuit.class: pushButton
*IcRcPopupQuit.static: true
*IcRcPopupQuit.name: IcRcPopupQuit
*IcRcPopupQuit.parent: IcRcPopupMenu
*IcRcPopupQuit.labelString: QuitMenuLabel
*IcRcPopupQuit.activateCallback: {\
/************\
#ifndef DESIGN_TIME\
set_cursor (padre,CLOCK);\
snap_interface_active = 0;\
tasto_initic_attivabile = False;\
free (snap_header);\
stop_timer (timer_initialCondition);\
set_cursor (padre,NORMALE);\
#endif\
***********/\
DistruggiInterfaccia (XtParent((Widget)UxClientData));\
}
*IcRcPopupQuit.activateCallbackClientData: UxGetWidget(initialCondition)

