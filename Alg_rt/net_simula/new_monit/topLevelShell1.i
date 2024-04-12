! UIMX ascii 2.5 key: 1687                                                      

*topLevelShell1.class: topLevelShell
*topLevelShell1.gbldecl: #ifndef DESIGN_TIME\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
\
#include "bistrutt.h"\
#include "banco_globals.h"\
extern int master_interface_active;\
#include "option.h"\
#endif\
#ifndef MAX_PATH_LEN \
#define MAX_PATH_LEN 100\
#endif\
extern int isSuperuser;
*topLevelShell1.ispecdecl:
*topLevelShell1.funcdecl: swidget create_topLevelShell1()\

*topLevelShell1.funcname: create_topLevelShell1
*topLevelShell1.funcdef: "swidget", "<create_topLevelShell1>(%)"
*topLevelShell1.icode: char path[MAX_PATH_LEN];\
char sim_name[MAX_PATH_LEN];
*topLevelShell1.fcode: strcpy (path,get_pwd());\
XtVaSetValues (simulatorPathText,XmNvalue,path,NULL);\
strcpy (sim_name,read_sim_name(path));\
XtVaSetValues (simulatorNameText,XmNvalue,sim_name,NULL);\
if (strcmp(sim_name,"NO_FILE"))\
   XtVaSetValues (startupButton,XmNsensitive,True,NULL);\
return(rtrn);\

*topLevelShell1.auxdecl:
*topLevelShell1.name.source: public
*topLevelShell1.static: false
*topLevelShell1.name: topLevelShell1
*topLevelShell1.parent: NO_PARENT
*topLevelShell1.parentExpression: UxWidgetToSwidget(UxTopLevel)
*topLevelShell1.x: 0
*topLevelShell1.y: 0
*topLevelShell1.width: 510
*topLevelShell1.height: 210
*topLevelShell1.title: "MASTER MONIT"
*topLevelShell1.allowShellResize: "true"
*topLevelShell1.iconName: "MASTER INSTRUCTOR STATION"

*form1.class: form
*form1.static: true
*form1.name: form1
*form1.parent: topLevelShell1
*form1.resizePolicy: "resize_any"
*form1.unitType: "pixels"
*form1.x: 110
*form1.y: 80
*form1.width: 510
*form1.height: 210
*form1.allowOverlap: "true"
*form1.labelFontList: "-Adobe-Courier-Bold-R-Normal--17-120-100-100-M-100-ISO8859-1"
*form1.rubberPositioning: "true"
*form1.textFontList: "-Adobe-Courier-Bold-R-Normal--17-120-100-100-M-100-ISO8859-1"
*form1.buttonFontList: "-Adobe-Courier-Bold-R-Normal--17-120-100-100-M-100-ISO8859-1"
*form1.defaultButton: "startupButton"
*form1.initialFocus: "startupButton"

*form34.class: form
*form34.static: true
*form34.name: form34
*form34.parent: form1
*form34.resizePolicy: "resize_none"
*form34.x: 0
*form34.y: 140
*form34.width: 520
*form34.height: 54
*form34.bottomAttachment: "attach_form"
*form34.bottomPosition: 0
*form34.leftAttachment: "attach_form"
*form34.leftPosition: 0
*form34.rightAttachment: "attach_form"
*form34.topAttachment: "attach_none"
*form34.topWidget: ""
*form34.defaultButton: "startupButton"
*form34.initialFocus: "startupButton"

*shutdownButton2.class: pushButton
*shutdownButton2.static: true
*shutdownButton2.name: shutdownButton2
*shutdownButton2.parent: form34
*shutdownButton2.x: 0
*shutdownButton2.y: 10
*shutdownButton2.width: 150
*shutdownButton2.height: 50
*shutdownButton2.labelString: "SHUTDOWN"
*shutdownButton2.activateCallback: {\
#ifndef DESIGN_TIME\
system ("killsim");\
if (isSuperuser)\
   system ("newsim&");\
else\
   system ("newsim&");\
\
exit (0);\
#endif\
}
*shutdownButton2.rightAttachment: "attach_form"
*shutdownButton2.rightOffset: 20
*shutdownButton2.bottomAttachment: "attach_form"
*shutdownButton2.bottomOffset: 10
*shutdownButton2.topAttachment: "attach_form"
*shutdownButton2.topOffset: 10
*shutdownButton2.leftAttachment: "attach_position"
*shutdownButton2.leftPosition: 70

*startupButton.class: pushButton
*startupButton.static: true
*startupButton.name: startupButton
*startupButton.parent: form34
*startupButton.x: 0
*startupButton.y: 10
*startupButton.width: 150
*startupButton.height: 50
*startupButton.labelString: "STARTUP"
*startupButton.activateCallback: {\
#ifndef DESIGN_TIME\
\
system ("newsim_");\
connessioni (topLevelShell1);\
\
if (master_interface_active)\
   {\
   if (!exist_Widget(UxGetWidget(masterMenu)))\
      create_masterMenu(0);\
   }\
else\
   create_masterMenu(0);\
\
XtVaSetValues (UxWidget,XmNsensitive,False,NULL);\
XtVaSetValues (topLevelShell1,XmNiconic,True,NULL);\
#endif\
}
*startupButton.bottomAttachment: "attach_form"
*startupButton.bottomOffset: 10
*startupButton.leftOffset: 20
*startupButton.rightAttachment: "attach_position"
*startupButton.rightPosition: 30
*startupButton.leftAttachment: "attach_form"
*startupButton.topAttachment: "attach_form"
*startupButton.topOffset: 10
*startupButton.sensitive: "false"

*separator1.class: separator
*separator1.static: true
*separator1.name: separator1
*separator1.parent: form1
*separator1.x: 0
*separator1.y: 110
*separator1.width: 520
*separator1.height: 10
*separator1.bottomAttachment: "attach_widget"
*separator1.bottomPosition: 0
*separator1.bottomWidget: "form34"

*menu9.class: rowColumn
*menu9.static: true
*menu9.name: menu9
*menu9.parent: form1
*menu9.rowColumnType: "menu_bar"
*menu9.rightAttachment: "attach_form"
*menu9.rightPosition: 0
*menu9.leftAttachment: "attach_form"

*masterMonitMenu.class: rowColumn
*masterMonitMenu.static: true
*masterMonitMenu.name: masterMonitMenu
*masterMonitMenu.parent: menu9
*masterMonitMenu.rowColumnType: "menu_pulldown"

*masterMonitMenuQuitpb.class: pushButton
*masterMonitMenuQuitpb.static: true
*masterMonitMenuQuitpb.name: masterMonitMenuQuitpb
*masterMonitMenuQuitpb.parent: masterMonitMenu
*masterMonitMenuQuitpb.labelString: "Quit "
*masterMonitMenuQuitpb.activateCallback: {\
system ("killsim");\
exit (0);\
}

*menu9_top_b1.class: cascadeButton
*menu9_top_b1.static: true
*menu9_top_b1.name: menu9_top_b1
*menu9_top_b1.parent: menu9
*menu9_top_b1.labelString: "File"
*menu9_top_b1.subMenuId: "masterMonitMenu"

*bulletinBoard1.class: bulletinBoard
*bulletinBoard1.static: true
*bulletinBoard1.name: bulletinBoard1
*bulletinBoard1.parent: form1
*bulletinBoard1.resizePolicy: "resize_none"
*bulletinBoard1.x: 50
*bulletinBoard1.y: 20
*bulletinBoard1.width: 410
*bulletinBoard1.height: 100
*bulletinBoard1.leftAttachment: "attach_form"
*bulletinBoard1.leftPosition: 0
*bulletinBoard1.rightAttachment: "attach_form"
*bulletinBoard1.topAttachment: "attach_widget"
*bulletinBoard1.topPosition: 0
*bulletinBoard1.bottomAttachment: "attach_widget"
*bulletinBoard1.bottomWidget: "separator1"
*bulletinBoard1.topWidget: "menu9"

*simulatorPathLabel.class: label
*simulatorPathLabel.static: true
*simulatorPathLabel.name: simulatorPathLabel
*simulatorPathLabel.parent: bulletinBoard1
*simulatorPathLabel.x: 10
*simulatorPathLabel.y: 20
*simulatorPathLabel.width: 150
*simulatorPathLabel.height: 30
*simulatorPathLabel.labelString: "Simulator path"
*simulatorPathLabel.alignment: "alignment_beginning"

*simulatorPathText.class: text
*simulatorPathText.static: true
*simulatorPathText.name: simulatorPathText
*simulatorPathText.parent: bulletinBoard1
*simulatorPathText.x: 160
*simulatorPathText.y: 20
*simulatorPathText.width: 350
*simulatorPathText.height: 30
*simulatorPathText.autoShowCursorPosition: "false"
*simulatorPathText.cursorPositionVisible: "false"
*simulatorPathText.editable: "false"
*simulatorPathText.marginHeight: 3

*simulatorPathName.class: label
*simulatorPathName.static: true
*simulatorPathName.name: simulatorPathName
*simulatorPathName.parent: bulletinBoard1
*simulatorPathName.x: 10
*simulatorPathName.y: 60
*simulatorPathName.width: 150
*simulatorPathName.height: 30
*simulatorPathName.labelString: "Simulator name"
*simulatorPathName.alignment: "alignment_beginning"

*simulatorNameText.class: text
*simulatorNameText.static: true
*simulatorNameText.name: simulatorNameText
*simulatorNameText.parent: bulletinBoard1
*simulatorNameText.x: 160
*simulatorNameText.y: 60
*simulatorNameText.width: 350
*simulatorNameText.height: 30
*simulatorNameText.autoShowCursorPosition: "false"
*simulatorNameText.cursorPositionVisible: "false"
*simulatorNameText.editable: "false"
*simulatorNameText.marginHeight: 3

