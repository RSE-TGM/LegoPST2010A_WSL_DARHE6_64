! UIMX ascii 2.5 key: 1795                                                      

*programLauncher.class: formDialog
*programLauncher.gbldecl: #include <stdio.h>\
#include "sim_param.h"\
#include "option.h"\
char selectedCommand[MAX_USERPROG_LUN];\

*programLauncher.ispecdecl: Widget progLaunchText[MAX_USERPROG];\
char comandi[MAX_USERPROG][MAX_USERPROG_LUN];\

*programLauncher.ispeclist: progLaunchText, comandi
*programLauncher.ispeclist.progLaunchText: "Widget", "%progLaunchText%[8]"
*programLauncher.ispeclist.comandi: "unsigned char", "%comandi%[8][100]"
*programLauncher.funcdecl: swidget create_programLauncher(UxParent)\
swidget UxParent;
*programLauncher.funcname: create_programLauncher
*programLauncher.funcdef: "swidget", "<create_programLauncher>(%)"
*programLauncher.argdecl: swidget UxParent;
*programLauncher.arglist: UxParent
*programLauncher.arglist.UxParent: "swidget", "%UxParent%"
*programLauncher.icode: strcpy (selectedCommand,"");
*programLauncher.fcode: creaBottoniLauncher (programLauncher);\
loadPrograms (programLauncher);\
UxPopupInterface (rtrn);\
return(rtrn);\

*programLauncher.auxdecl:
*programLauncher.static: true
*programLauncher.name: programLauncher
*programLauncher.parent: NO_PARENT
*programLauncher.defaultShell: topLevelShell
*programLauncher.unitType: "pixels"
*programLauncher.x: 270
*programLauncher.y: 390
*programLauncher.width: 330
*programLauncher.height: 310

*menu8.class: rowColumn
*menu8.static: true
*menu8.name: menu8
*menu8.parent: programLauncher
*menu8.rowColumnType: "menu_bar"
*menu8.rightAttachment: "attach_form"
*menu8.leftAttachment: "attach_form"

*menu8_p1.class: rowColumn
*menu8_p1.static: true
*menu8_p1.name: menu8_p1
*menu8_p1.parent: menu8
*menu8_p1.rowColumnType: "menu_pulldown"

*progLaunchFileQuitpb.class: pushButton
*progLaunchFileQuitpb.static: true
*progLaunchFileQuitpb.name: progLaunchFileQuitpb
*progLaunchFileQuitpb.parent: menu8_p1
*progLaunchFileQuitpb.labelString: "Quit"
*progLaunchFileQuitpb.activateCallback: {\
DistruggiInterfaccia (XtParent((Widget)UxClientData));\
}
*progLaunchFileQuitpb.activateCallbackClientData: programLauncher

*menu8_top_b1.class: cascadeButton
*menu8_top_b1.static: true
*menu8_top_b1.name: menu8_top_b1
*menu8_top_b1.parent: menu8
*menu8_top_b1.labelString: "File"
*menu8_top_b1.subMenuId: "menu8_p1"

*frame22.class: frame
*frame22.static: true
*frame22.name: frame22
*frame22.parent: programLauncher
*frame22.x: 0
*frame22.y: 150
*frame22.width: 360
*frame22.height: 60
*frame22.bottomAttachment: "attach_form"
*frame22.rightAttachment: "attach_form"
*frame22.leftAttachment: "attach_form"

*form29.class: form
*form29.static: true
*form29.name: form29
*form29.parent: frame22
*form29.resizePolicy: "resize_none"
*form29.x: 90
*form29.y: 10
*form29.width: 200
*form29.height: 40

*progLaunchExecpb.class: pushButton
*progLaunchExecpb.static: true
*progLaunchExecpb.name: progLaunchExecpb
*progLaunchExecpb.parent: form29
*progLaunchExecpb.x: 20
*progLaunchExecpb.y: 10
*progLaunchExecpb.width: 100
*progLaunchExecpb.height: 30
*progLaunchExecpb.bottomAttachment: "attach_form"
*progLaunchExecpb.bottomOffset: 15
*progLaunchExecpb.rightAttachment: "attach_position"
*progLaunchExecpb.rightPosition: 30
*progLaunchExecpb.leftAttachment: "attach_form"
*progLaunchExecpb.leftOffset: 20
*progLaunchExecpb.labelString: "Execute"
*progLaunchExecpb.activateCallback: {\
system (selectedCommand);\
DistruggiInterfaccia (XtParent((Widget)UxClientData));\
}
*progLaunchExecpb.activateCallbackClientData: programLauncher

*progLaunchQuitpb.class: pushButton
*progLaunchQuitpb.static: true
*progLaunchQuitpb.name: progLaunchQuitpb
*progLaunchQuitpb.parent: form29
*progLaunchQuitpb.x: 220
*progLaunchQuitpb.y: 10
*progLaunchQuitpb.width: 100
*progLaunchQuitpb.height: 30
*progLaunchQuitpb.bottomAttachment: "attach_form"
*progLaunchQuitpb.bottomOffset: 15
*progLaunchQuitpb.leftAttachment: "attach_position"
*progLaunchQuitpb.leftPosition: 70
*progLaunchQuitpb.rightAttachment: "attach_form"
*progLaunchQuitpb.rightOffset: 20
*progLaunchQuitpb.labelString: "Quit"
*progLaunchQuitpb.activateCallback: {\
DistruggiInterfaccia (XtParent((Widget)UxClientData));\
}
*progLaunchQuitpb.activateCallbackClientData: programLauncher

*rowColumn4.class: rowColumn
*rowColumn4.static: true
*rowColumn4.name: rowColumn4
*rowColumn4.parent: programLauncher
*rowColumn4.x: 10
*rowColumn4.y: 40
*rowColumn4.width: 320
*rowColumn4.height: 300
*rowColumn4.bottomAttachment: "attach_widget"
*rowColumn4.bottomWidget: "frame22"
*rowColumn4.rightAttachment: "attach_form"
*rowColumn4.rightOffset: 10
*rowColumn4.leftAttachment: "attach_form"
*rowColumn4.leftOffset: 10
*rowColumn4.topAttachment: "attach_widget"
*rowColumn4.topWidget: "menu8"
*rowColumn4.numColumns: 1
*rowColumn4.radioBehavior: "true"

