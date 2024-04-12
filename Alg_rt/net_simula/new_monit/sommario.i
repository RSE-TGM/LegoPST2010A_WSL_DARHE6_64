! UIMX ascii 2.5 key: 736                                                       

*sommario.class: formDialog
*sommario.gbldecl: #include <stdio.h>\
#include <X11/Intrinsic.h>\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
#include "malfunzioni.h"\
#include "messaggi.h"\
\
#include "cursore.h"\
#ifndef DESIGN_TIME\
/* #include "interf_attive.h" */\
extern int sommario_malf_active;\
extern int sommario_frem_active;\
\
Widget sommarioMalf;\
Widget sommarioFrem;\
#endif
*sommario.ispecdecl:
*sommario.funcdecl: swidget create_sommario(sommParent,tipo)\
Widget sommParent;\
int tipo;   /* malf or frem */
*sommario.funcname: create_sommario
*sommario.funcdef: "swidget", "<create_sommario>(%)"
*sommario.argdecl: Widget sommParent;\
int tipo;
*sommario.arglist: sommParent, tipo
*sommario.arglist.sommParent: "Widget", "%sommParent%"
*sommario.arglist.tipo: "int", "%tipo%"
*sommario.icode: #ifndef DESIGN_TIME\
set_cursor (sommParent,CLOCK);\
#endif
*sommario.fcode: #ifndef DESIGN_TIME\
switch (tipo)\
   {\
   case MALFUNZIONI:\
      sommarioMalf = rtrn;\
      sommario_malf_active = 1;\
      XtVaSetValues (XtParent(UxGetWidget(rtrn)),\
         XmNtitle, MALF_SUMMARY, XmNiconName, MALF_SUMMARY, NULL);\
      break;\
   case FUNZIONI_REMOTE:\
      sommarioFrem = rtrn;\
      sommario_frem_active = 1;\
      XtVaSetValues (XtParent(UxGetWidget(rtrn)),\
         XmNtitle, FREM_SUMMARY, XmNiconName, FREM_SUMMARY, NULL);\
      break; \
   }\
set_cursor (sommParent,NORMALE);\
#endif\
UxPopupInterface(rtrn,no_grab);\
return(rtrn);\

*sommario.auxdecl:
*sommario.name.source: public
*sommario.static: false
*sommario.name: sommario
*sommario.parent: NO_PARENT
*sommario.defaultShell: topLevelShell
*sommario.width: 500
*sommario.height: 430
*sommario.isCompound: "true"
*sommario.compoundIcon: "formD.xpm"
*sommario.compoundName: "form_Dialog"
*sommario.x: 400
*sommario.y: 80
*sommario.unitType: "pixels"

*sommMenu.class: rowColumn
*sommMenu.static: true
*sommMenu.name: sommMenu
*sommMenu.parent: sommario
*sommMenu.rowColumnType: "menu_bar"
*sommMenu.menuAccelerator: "<KeyUp>F10"
*sommMenu.packing: "pack_tight"
*sommMenu.menuHelpWidget: "sommMenu_top_b2"
*sommMenu.createManaged: "true"
*sommMenu.rightAttachment: "attach_form"
*sommMenu.leftAttachment: "attach_form"

*sommMenuFile.class: rowColumn
*sommMenuFile.static: true
*sommMenuFile.name: sommMenuFile
*sommMenuFile.parent: sommMenu
*sommMenuFile.rowColumnType: "menu_pulldown"

*sommMenuFileQuitpb.class: pushButton
*sommMenuFileQuitpb.static: true
*sommMenuFileQuitpb.name: sommMenuFileQuitpb
*sommMenuFileQuitpb.parent: sommMenuFile
*sommMenuFileQuitpb.labelString: "Quit"
*sommMenuFileQuitpb.activateCallback: {\
#ifndef DESIGN_TIME\
switch (tipo)\
   {\
   case MALFUNZIONI:\
      DistruggiInterfaccia(XtParent(sommarioMalf));\
      sommario_malf_active = 0;\
      break;\
   case FUNZIONI_REMOTE:\
      DistruggiInterfaccia(XtParent(sommarioFrem));\
      sommario_frem_active = 0;\
      break;\
   }\
#endif\
}

*sommMenuHelp.class: rowColumn
*sommMenuHelp.static: true
*sommMenuHelp.name: sommMenuHelp
*sommMenuHelp.parent: sommMenu
*sommMenuHelp.rowColumnType: "menu_pulldown"

*sommMenuHelppb.class: pushButton
*sommMenuHelppb.static: true
*sommMenuHelppb.name: sommMenuHelppb
*sommMenuHelppb.parent: sommMenuHelp
*sommMenuHelppb.labelString: "Commands"
*sommMenuHelppb.mnemonic: "C"
*sommMenuHelppb.activateCallback: {printf ("help comandi\n");}

*sommMenu_top_b1.class: cascadeButton
*sommMenu_top_b1.static: true
*sommMenu_top_b1.name: sommMenu_top_b1
*sommMenu_top_b1.parent: sommMenu
*sommMenu_top_b1.labelString: "File    "
*sommMenu_top_b1.subMenuId: "sommMenuFile"

*sommMenu_top_b2.class: cascadeButton
*sommMenu_top_b2.static: true
*sommMenu_top_b2.name: sommMenu_top_b2
*sommMenu_top_b2.parent: sommMenu
*sommMenu_top_b2.labelString: "Help"
*sommMenu_top_b2.subMenuId: "sommMenuHelp"

*frame17.class: frame
*frame17.static: true
*frame17.name: frame17
*frame17.parent: sommario
*frame17.x: 48
*frame17.y: 288
*frame17.width: 690
*frame17.height: 80
*frame17.bottomAttachment: "attach_form"
*frame17.leftOffset: 0
*frame17.rightAttachment: "attach_form"
*frame17.leftAttachment: "attach_form"

*form33.class: form
*form33.static: true
*form33.name: form33
*form33.parent: frame17
*form33.resizePolicy: "resize_none"
*form33.x: 2
*form33.y: 20
*form33.width: 851
*form33.height: 82
*form33.defaultButton: ""
*form33.unmapCallback: {\
\
}

*quitMalfSommpb.class: pushButton
*quitMalfSommpb.static: true
*quitMalfSommpb.name: quitMalfSommpb
*quitMalfSommpb.parent: form33
*quitMalfSommpb.x: 715
*quitMalfSommpb.y: 15
*quitMalfSommpb.width: 200
*quitMalfSommpb.height: 52
*quitMalfSommpb.labelString: "QUIT"
*quitMalfSommpb.bottomAttachment: "attach_form"
*quitMalfSommpb.leftAttachment: "attach_self"
*quitMalfSommpb.rightAttachment: "attach_form"
*quitMalfSommpb.rightOffset: 20
*quitMalfSommpb.topAttachment: "attach_form"
*quitMalfSommpb.topOffset: 15
*quitMalfSommpb.bottomOffset: 15
*quitMalfSommpb.activateCallback: {\
#ifndef DESIGN_TIME\
switch (tipo)\
   {\
   case MALFUNZIONI:\
      DistruggiInterfaccia(XtParent(sommarioMalf));\
      sommario_malf_active = 0;\
      break;\
   case FUNZIONI_REMOTE:\
      DistruggiInterfaccia(XtParent(sommarioFrem));\
      sommario_frem_active = 0;\
      break;\
   }\
#endif\
}
*quitMalfSommpb.activateCallbackClientData: (XtPointer) 0x0
*quitMalfSommpb.leftPosition: 0
*quitMalfSommpb.leftOffset: 120

*actMalfSommpb.class: pushButton
*actMalfSommpb.name.source: public
*actMalfSommpb.static: false
*actMalfSommpb.name: actMalfSommpb
*actMalfSommpb.parent: form33
*actMalfSommpb.x: 20
*actMalfSommpb.y: 15
*actMalfSommpb.width: 200
*actMalfSommpb.height: 52
*actMalfSommpb.labelString: "DEACTIVATE"
*actMalfSommpb.bottomAttachment: "attach_form"
*actMalfSommpb.bottomOffset: 15
*actMalfSommpb.rightAttachment: "attach_self"
*actMalfSommpb.rightPosition: 0
*actMalfSommpb.rightOffset: 0
*actMalfSommpb.leftAttachment: "attach_form"
*actMalfSommpb.leftOffset: 20
*actMalfSommpb.topAttachment: "attach_form"
*actMalfSommpb.topOffset: 15
*actMalfSommpb.sensitive: "false"
*actMalfSommpb.activateCallback: {\
\
}
*actMalfSommpb.activateCallbackClientData: (XtPointer) 0x0

*sommarioScrollWin.class: scrolledWindow
*sommarioScrollWin.static: true
*sommarioScrollWin.name: sommarioScrollWin
*sommarioScrollWin.parent: sommario
*sommarioScrollWin.scrollingPolicy: "automatic"
*sommarioScrollWin.x: 15
*sommarioScrollWin.y: 60
*sommarioScrollWin.width: 650
*sommarioScrollWin.height: 255
*sommarioScrollWin.bottomAttachment: "attach_widget"
*sommarioScrollWin.bottomOffset: 20
*sommarioScrollWin.bottomWidget: "frame17"
*sommarioScrollWin.leftOffset: 20
*sommarioScrollWin.rightAttachment: "attach_form"
*sommarioScrollWin.rightOffset: 20
*sommarioScrollWin.leftAttachment: "attach_form"
*sommarioScrollWin.topAttachment: "attach_widget"
*sommarioScrollWin.topOffset: 20
*sommarioScrollWin.topWidget: "sommMenu"

*sommRc.class: rowColumn
*sommRc.static: true
*sommRc.name: sommRc
*sommRc.parent: sommarioScrollWin
*sommRc.x: 2
*sommRc.y: 4
*sommRc.width: 429
*sommRc.height: 275

