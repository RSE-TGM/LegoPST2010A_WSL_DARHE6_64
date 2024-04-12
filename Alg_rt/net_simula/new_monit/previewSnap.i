! UIMX ascii 2.5 key: 6255                                                      

*previewSnap.class: formDialog
*previewSnap.gbldecl: #include <stdio.h>\
#include <Xm/Text.h>\
#include <Xm/Label.h>\
#include <malloc.h>\
\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
#include "parametri.h" \
#include "bistrutt.h"\
#include "preview.h"\
#include "file_selection.h"\
#include "filtri.h"\
#include "messaggi.h"\
#ifndef MAX_VIEW_ENTRY\
#define MAX_VIEW_ENTRY 10\
#endif\
extern Widget create_selVar ();
*previewSnap.ispecdecl: Widget ViewScrollForm[MAX_VIEW_ENTRY];\
Widget ViewScrollTb[MAX_VIEW_ENTRY];\
Widget ViewScrollText[MAX_VIEW_ENTRY];\
Widget ViewScrollLabel[MAX_VIEW_ENTRY];\
Widget selVarWidg;\
\
PREVIEW_DATA preview_data;\
LISTA_VAR lista_var;\
char *testata;
*previewSnap.ispeclist: ViewScrollForm, ViewScrollTb, ViewScrollText, ViewScrollLabel, selVarWidg, preview_data, lista_var, testata
*previewSnap.ispeclist.ViewScrollForm: "Widget", "%ViewScrollForm%[10]"
*previewSnap.ispeclist.ViewScrollTb: "Widget", "%ViewScrollTb%[10]"
*previewSnap.ispeclist.ViewScrollText: "Widget", "%ViewScrollText%[10]"
*previewSnap.ispeclist.ViewScrollLabel: "Widget", "%ViewScrollLabel%[10]"
*previewSnap.ispeclist.selVarWidg: "Widget", "%selVarWidg%"
*previewSnap.ispeclist.preview_data: "PREVIEW_DATA", "%preview_data%"
*previewSnap.ispeclist.lista_var: "LISTA_VAR", "%lista_var%"
*previewSnap.ispeclist.testata: "unsigned char", "*%testata%"
*previewSnap.funcdecl: swidget create_previewSnap(which, n, s)\
int which;    /* snap or bt       */\
int n;        /* numero di record */\
char *s;      /* commento         */\

*previewSnap.funcname: create_previewSnap
*previewSnap.funcdef: "swidget", "<create_previewSnap>(%)"
*previewSnap.argdecl: int which;\
int n;\
unsigned char *s;
*previewSnap.arglist: which, n, s
*previewSnap.arglist.which: "int", "%which%"
*previewSnap.arglist.n: "int", "%n%"
*previewSnap.arglist.s: "unsigned char", "*%s%"
*previewSnap.icode: printf ("chiamata da %d rec = %d\n",which,n);\
selVarWidg =  (Widget)NULL;\
testata = (char *) malloc (strlen (s) + 1);\
strcpy (testata,s);
*previewSnap.fcode: previewSnap_crea_entry (rtrn, &UxEnv);\
previewSnap_readFile (rtrn, &UxEnv);\
previewSnap_readVal (rtrn, &UxEnv);\
previewSnap_displayVal (rtrn, &UxEnv);\
XtVaSetValues (XtParent(UxGetWidget(rtrn)),\
   XmNtitle, s, XmNiconName, s, NULL);\
UxPopupInterface (rtrn, no_grab);\
return(rtrn);\

*previewSnap.auxdecl:
*previewSnap_crea_entry.class: method
*previewSnap_crea_entry.name: crea_entry
*previewSnap_crea_entry.parent: previewSnap
*previewSnap_crea_entry.methodType: int
*previewSnap_crea_entry.methodArgs: 
*previewSnap_crea_entry.methodBody: crea_preview_entry (UxGetWidget(UxThis));

*previewSnap_readFile.class: method
*previewSnap_readFile.name: readFile
*previewSnap_readFile.parent: previewSnap
*previewSnap_readFile.methodType: int
*previewSnap_readFile.methodArgs: 
*previewSnap_readFile.methodBody: get_file_view (UxGetWidget(UxThis));

*previewSnap_readVal.class: method
*previewSnap_readVal.name: readVal
*previewSnap_readVal.parent: previewSnap
*previewSnap_readVal.methodType: int
*previewSnap_readVal.methodArgs: 
*previewSnap_readVal.methodBody: get_val_view (UxGetWidget(UxThis));

*previewSnap_displayVal.class: method
*previewSnap_displayVal.name: displayVal
*previewSnap_displayVal.parent: previewSnap
*previewSnap_displayVal.methodType: int
*previewSnap_displayVal.methodArgs: 
*previewSnap_displayVal.methodBody: display_view (UxGetWidget(UxThis));

*previewSnap.static: true
*previewSnap.name: previewSnap
*previewSnap.parent: NO_PARENT
*previewSnap.defaultShell: topLevelShell
*previewSnap.unitType: "pixels"
*previewSnap.x: 725
*previewSnap.y: 165
*previewSnap.width: 650
*previewSnap.height: 400

*frame13.class: frame
*frame13.static: true
*frame13.name: frame13
*frame13.parent: previewSnap
*frame13.x: 10
*frame13.y: 405
*frame13.width: 600
*frame13.height: 80
*frame13.bottomAttachment: "attach_form"
*frame13.leftOffset: 0
*frame13.rightAttachment: "attach_form"
*frame13.leftAttachment: "attach_form"

*form23.class: form
*form23.static: true
*form23.name: form23
*form23.parent: frame13
*form23.resizePolicy: "resize_none"
*form23.x: 2
*form23.y: -20
*form23.width: 600
*form23.height: 68
*form23.defaultButton: "previewQuitpb"

*previewQuitpb.class: pushButton
*previewQuitpb.static: true
*previewQuitpb.name: previewQuitpb
*previewQuitpb.parent: form23
*previewQuitpb.x: 493
*previewQuitpb.y: 35
*previewQuitpb.width: 100
*previewQuitpb.height: 30
*previewQuitpb.labelString: QUITLABEL
*previewQuitpb.bottomAttachment: "attach_form"
*previewQuitpb.leftAttachment: "attach_position"
*previewQuitpb.rightAttachment: "attach_position"
*previewQuitpb.bottomOffset: 15
*previewQuitpb.rightOffset: 0
*previewQuitpb.leftPosition: 40
*previewQuitpb.leftOffset: 0
*previewQuitpb.topAttachment: "attach_form"
*previewQuitpb.topOffset: 15
*previewQuitpb.activateCallback: {\
DistruggiInterfaccia (XtParent((Widget)UxClientData));\
}
*previewQuitpb.activateCallbackClientData: UxGetWidget(previewSnap)
*previewQuitpb.rightPosition: 60

*previewMenu.class: rowColumn
*previewMenu.static: true
*previewMenu.name: previewMenu
*previewMenu.parent: previewSnap
*previewMenu.rowColumnType: "menu_bar"
*previewMenu.rightAttachment: "attach_form"
*previewMenu.leftAttachment: "attach_form"
*previewMenu.menuHelpWidget: "previewMenuHelpcb"
*previewMenu.menuAccelerator: "<KeyUp>F10"

*previewMenuFile.class: rowColumn
*previewMenuFile.static: true
*previewMenuFile.name: previewMenuFile
*previewMenuFile.parent: previewMenu
*previewMenuFile.rowColumnType: "menu_pulldown"

*previewMenuFileOpenDefpb.class: pushButton
*previewMenuFileOpenDefpb.static: true
*previewMenuFileOpenDefpb.name: previewMenuFileOpenDefpb
*previewMenuFileOpenDefpb.parent: previewMenuFile
*previewMenuFileOpenDefpb.labelString: LoadDefaultLabel
*previewMenuFileOpenDefpb.activateCallback: {\
#ifndef DESIGN_TIME\
load_preview (UxWidget,VIEW_FILE);\
#endif\
}

*previewMenuFileOpenpb.class: pushButton
*previewMenuFileOpenpb.static: true
*previewMenuFileOpenpb.name: previewMenuFileOpenpb
*previewMenuFileOpenpb.parent: previewMenuFile
*previewMenuFileOpenpb.labelString: OpenMenuLabel2
*previewMenuFileOpenpb.activateCallback: {\
#ifndef DESIGN_TIME\
loadas_preview (previewSnap,1,PREVIEW_FILE); /* 1 = lettura */\
#endif\
}

*previewMenuFile_b7.class: separator
*previewMenuFile_b7.static: true
*previewMenuFile_b7.name: previewMenuFile_b7
*previewMenuFile_b7.parent: previewMenuFile

*previewMenuFileSavepb.class: pushButton
*previewMenuFileSavepb.static: true
*previewMenuFileSavepb.name: previewMenuFileSavepb
*previewMenuFileSavepb.parent: previewMenuFile
*previewMenuFileSavepb.labelString: SaveMenuLabel
*previewMenuFileSavepb.activateCallback: {\
#ifndef DESIGN_TIME\
salva_preview_list (UxWidget, VIEW_FILE);\
#endif\
}

*previewMenuFileSaveaspb.class: pushButton
*previewMenuFileSaveaspb.static: true
*previewMenuFileSaveaspb.name: previewMenuFileSaveaspb
*previewMenuFileSaveaspb.parent: previewMenuFile
*previewMenuFileSaveaspb.labelString: SaveMenuLabel2
*previewMenuFileSaveaspb.activateCallback: {\
#ifndef DESIGN_TIME\
saveas_preview (previewSnap,2,PREVIEW_FILE); /* 2 = in scrittura */\
#endif\
}

*previewMenuFileSep1.class: separatorGadget
*previewMenuFileSep1.static: true
*previewMenuFileSep1.name: previewMenuFileSep1
*previewMenuFileSep1.parent: previewMenuFile

*previewMenuFileQuitpb.class: pushButton
*previewMenuFileQuitpb.static: true
*previewMenuFileQuitpb.name: previewMenuFileQuitpb
*previewMenuFileQuitpb.parent: previewMenuFile
*previewMenuFileQuitpb.labelString: QuitMenuLabel
*previewMenuFileQuitpb.activateCallback: {\
DistruggiInterfaccia (XtParent(previewSnap));\
}

*previewMenuEdit.class: rowColumn
*previewMenuEdit.static: true
*previewMenuEdit.name: previewMenuEdit
*previewMenuEdit.parent: previewMenu
*previewMenuEdit.rowColumnType: "menu_pulldown"

*previewMenuEditSelpb.class: pushButton
*previewMenuEditSelpb.static: true
*previewMenuEditSelpb.name: previewMenuEditSelpb
*previewMenuEditSelpb.parent: previewMenuEdit
*previewMenuEditSelpb.labelString: SelectNewLabel
*previewMenuEditSelpb.activateCallback: {\
if (!exist_Widget (selVarWidg))\
   selVarWidg = create_selVar (UxGetWidget(previewSnap), &preview_data,PREVIEW_CALLING,testata);\
printf (" chiamata da preview [%s]\n",testata);\
}

*previewMenuEditSep1.class: separator
*previewMenuEditSep1.static: true
*previewMenuEditSep1.name: previewMenuEditSep1
*previewMenuEditSep1.parent: previewMenuEdit

*previewMenuEditDelete.class: pushButton
*previewMenuEditDelete.static: true
*previewMenuEditDelete.name: previewMenuEditDelete
*previewMenuEditDelete.parent: previewMenuEdit
*previewMenuEditDelete.labelString: CutMenuLabel
*previewMenuEditDelete.activateCallback: {\
#ifndef DESIGN_TIME\
delete_preview_entry (&preview_data,UxWidget);\
#endif\
}

*previewMenuEditClearAllpb.class: pushButton
*previewMenuEditClearAllpb.static: true
*previewMenuEditClearAllpb.name: previewMenuEditClearAllpb
*previewMenuEditClearAllpb.parent: previewMenuEdit
*previewMenuEditClearAllpb.labelString: ClearAllLabel
*previewMenuEditClearAllpb.activateCallback: {\
#ifndef DESIGN_TIME\
   int i;\
      for (i=0; i<MAX_VIEW_ENTRY; i++)\
         clear_preview_entry (&preview_data, i);\
      display_view (UxWidget);\
#endif\
}

*previewMenuHelp.class: rowColumn
*previewMenuHelp.static: true
*previewMenuHelp.name: previewMenuHelp
*previewMenuHelp.parent: previewMenu
*previewMenuHelp.rowColumnType: "menu_pulldown"

*previewMenuHelpCommpb.class: pushButton
*previewMenuHelpCommpb.static: true
*previewMenuHelpCommpb.name: previewMenuHelpCommpb
*previewMenuHelpCommpb.parent: previewMenuHelp
*previewMenuHelpCommpb.labelString: "Command"
*previewMenuHelpCommpb.activateCallback: {printf ("help\n");}

*previewMenuFilecb.class: cascadeButton
*previewMenuFilecb.static: true
*previewMenuFilecb.name: previewMenuFilecb
*previewMenuFilecb.parent: previewMenu
*previewMenuFilecb.labelString: "File"
*previewMenuFilecb.subMenuId: "previewMenuFile"

*previewMenuEditcb.class: cascadeButton
*previewMenuEditcb.static: true
*previewMenuEditcb.name: previewMenuEditcb
*previewMenuEditcb.parent: previewMenu
*previewMenuEditcb.labelString: "Edit"
*previewMenuEditcb.subMenuId: "previewMenuEdit"

*previewMenuHelpcb.class: cascadeButton
*previewMenuHelpcb.static: true
*previewMenuHelpcb.name: previewMenuHelpcb
*previewMenuHelpcb.parent: previewMenu
*previewMenuHelpcb.labelString: "Help"
*previewMenuHelpcb.subMenuId: "previewMenuHelp"

*scrolledWindow4.class: scrolledWindow
*scrolledWindow4.static: true
*scrolledWindow4.name: scrolledWindow4
*scrolledWindow4.parent: previewSnap
*scrolledWindow4.scrollingPolicy: "automatic"
*scrolledWindow4.x: 35
*scrolledWindow4.y: 55
*scrolledWindow4.width: 270
*scrolledWindow4.height: 325
*scrolledWindow4.topAttachment: "attach_widget"
*scrolledWindow4.topOffset: 20
*scrolledWindow4.topWidget: "previewMenu"
*scrolledWindow4.bottomAttachment: "attach_widget"
*scrolledWindow4.bottomOffset: 20
*scrolledWindow4.bottomWidget: "frame13"
*scrolledWindow4.leftOffset: 10
*scrolledWindow4.rightAttachment: "attach_form"
*scrolledWindow4.leftAttachment: "attach_form"
*scrolledWindow4.rightOffset: 10

*viewRc.class: rowColumn
*viewRc.static: true
*viewRc.name: viewRc
*viewRc.parent: scrolledWindow4
*viewRc.x: 2
*viewRc.y: 2
*viewRc.width: 345
*viewRc.height: 10

*previewSnapPopup.class: rowColumn
*previewSnapPopup.static: true
*previewSnapPopup.name: previewSnapPopup
*previewSnapPopup.parent: previewSnap
*previewSnapPopup.rowColumnType: "menu_popup"

*previewSnapPopupOpenDef.class: pushButton
*previewSnapPopupOpenDef.static: true
*previewSnapPopupOpenDef.name: previewSnapPopupOpenDef
*previewSnapPopupOpenDef.parent: previewSnapPopup
*previewSnapPopupOpenDef.labelString: LoadDefaultLabel
*previewSnapPopupOpenDef.activateCallback: {\
#ifndef DESIGN_TIME\
load_preview (UxWidget,VIEW_FILE);\
#endif\
}

*previewSnapPopupMenuOpen.class: pushButton
*previewSnapPopupMenuOpen.static: true
*previewSnapPopupMenuOpen.name: previewSnapPopupMenuOpen
*previewSnapPopupMenuOpen.parent: previewSnapPopup
*previewSnapPopupMenuOpen.labelString: OpenMenuLabel2
*previewSnapPopupMenuOpen.activateCallback: {\
#ifndef DESIGN_TIME\
loadas_preview (previewSnap,1,PREVIEW_FILE); /* 1 = lettura */\
#endif\
}

*previewSnapPopupMenu_b3.class: separator
*previewSnapPopupMenu_b3.static: true
*previewSnapPopupMenu_b3.name: previewSnapPopupMenu_b3
*previewSnapPopupMenu_b3.parent: previewSnapPopup

*previewSnapPopupMenuSaveDef.class: pushButton
*previewSnapPopupMenuSaveDef.static: true
*previewSnapPopupMenuSaveDef.name: previewSnapPopupMenuSaveDef
*previewSnapPopupMenuSaveDef.parent: previewSnapPopup
*previewSnapPopupMenuSaveDef.labelString: SaveMenuLabel
*previewSnapPopupMenuSaveDef.activateCallback: {\
#ifndef DESIGN_TIME\
salva_preview_list (UxWidget, VIEW_FILE);\
#endif\
}

*previewSnapPopupMenuSave.class: pushButton
*previewSnapPopupMenuSave.static: true
*previewSnapPopupMenuSave.name: previewSnapPopupMenuSave
*previewSnapPopupMenuSave.parent: previewSnapPopup
*previewSnapPopupMenuSave.labelString: SaveMenuLabel2
*previewSnapPopupMenuSave.activateCallback: {\
#ifndef DESIGN_TIME\
saveas_preview (previewSnap,2,PREVIEW_FILE); /* 2 = in scrittura */\
#endif\
}

*previewSnapPopupMenu_b6.class: separator
*previewSnapPopupMenu_b6.static: true
*previewSnapPopupMenu_b6.name: previewSnapPopupMenu_b6
*previewSnapPopupMenu_b6.parent: previewSnapPopup

*previewSnapPopupMenuQuit.class: pushButton
*previewSnapPopupMenuQuit.static: true
*previewSnapPopupMenuQuit.name: previewSnapPopupMenuQuit
*previewSnapPopupMenuQuit.parent: previewSnapPopup
*previewSnapPopupMenuQuit.labelString: QuitMenuLabel
*previewSnapPopupMenuQuit.activateCallback: {\
DistruggiInterfaccia (XtParent(previewSnap));\
}

