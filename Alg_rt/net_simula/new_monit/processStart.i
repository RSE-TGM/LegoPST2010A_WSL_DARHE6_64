! UIMX ascii 2.8 key: 612                                                       

*processStart.class: formDialog
*processStart.gbldecl: #include <stdio.h>\
#include "sim_param.h"\
#include "messaggi.h"\
#include "option.h"\
extern OPTIONS_FLAGS options;\

*processStart.ispecdecl: /* widgets per selezione display */\
Widget MenuShellDisplay;\
Widget menu8_p1;\
Widget displayMenu;\
Widget displaySelectionButton[MAX_DISPLAY];\
int closeRequest;\
char selectedDisplay[MAX_DISPLAY_NAME];
*processStart.ispeclist: MenuShellDisplay, menu8_p1, displayMenu, displaySelectionButton, closeRequest, selectedDisplay
*processStart.ispeclist.MenuShellDisplay: "Widget", "%MenuShellDisplay%"
*processStart.ispeclist.menu8_p1: "Widget", "%menu8_p1%"
*processStart.ispeclist.displayMenu: "Widget", "%displayMenu%"
*processStart.ispeclist.displaySelectionButton: "Widget", "%displaySelectionButton%[5]"
*processStart.ispeclist.closeRequest: "int", "%closeRequest%"
*processStart.ispeclist.selectedDisplay: "char", "%selectedDisplay%[100]"
*processStart.funcdecl: char *create_processStart(UxParent,testo)\
swidget UxParent;\
char *testo;     /* processo da attivare  */
*processStart.funcname: create_processStart
*processStart.funcdef: "char", "*<create_processStart>(%)"
*processStart.argdecl: swidget UxParent;\
char *testo;
*processStart.arglist: UxParent, testo
*processStart.arglist.UxParent: "swidget", "%UxParent%"
*processStart.arglist.testo: "char", "*%testo%"
*processStart.icode: closeRequest = 0;\
strcpy (selectedDisplay,"");
*processStart.fcode: crea_display_selection (displaySelectForm,options);\
UxPopupInterface (rtrn);\
while (closeRequest == 0)\
   {\
   XtAppProcessEvent (UxAppContext,XtIMAll);\
   XSync (UxDisplay,0);\
   }\
closeRequest = 0;\
printf ("chiusura processStar; display [%s]\n",\
              selectedDisplay);\
return(selectedDisplay);\

*processStart.auxdecl:
*processStart.static: true
*processStart.name: processStart
*processStart.parent: NO_PARENT
*processStart.parentExpression: UxParent
*processStart.defaultShell: topLevelShell
*processStart.unitType: "pixels"
*processStart.x: 560
*processStart.y: 400
*processStart.width: 360
*processStart.height: 210

*frame21.class: frame
*frame21.static: true
*frame21.name: frame21
*frame21.parent: processStart
*frame21.x: 0
*frame21.y: 150
*frame21.width: 360
*frame21.height: 60
*frame21.bottomAttachment: "attach_form"
*frame21.rightAttachment: "attach_form"
*frame21.leftAttachment: "attach_form"

*form48.class: form
*form48.static: true
*form48.name: form48
*form48.parent: frame21
*form48.resizePolicy: "resize_none"
*form48.x: 90
*form48.y: 10
*form48.width: 200
*form48.height: 40

*processStartOkpb.class: pushButton
*processStartOkpb.static: true
*processStartOkpb.name: processStartOkpb
*processStartOkpb.parent: form48
*processStartOkpb.x: 20
*processStartOkpb.y: 10
*processStartOkpb.width: 100
*processStartOkpb.height: 30
*processStartOkpb.bottomAttachment: "attach_form"
*processStartOkpb.bottomOffset: 15
*processStartOkpb.rightAttachment: "attach_position"
*processStartOkpb.rightPosition: 30
*processStartOkpb.leftAttachment: "attach_form"
*processStartOkpb.leftOffset: 20
*processStartOkpb.labelString: PROC_START_OK ? PROC_START_OK : "OK"
*processStartOkpb.activateCallback: {\
closeRequest = 1;\
DistruggiInterfaccia (XtParent((Widget)UxClientData));\
}
*processStartOkpb.activateCallbackClientData: processStart

*processStartQuitpb.class: pushButton
*processStartQuitpb.static: true
*processStartQuitpb.name: processStartQuitpb
*processStartQuitpb.parent: form48
*processStartQuitpb.x: 220
*processStartQuitpb.y: 10
*processStartQuitpb.width: 100
*processStartQuitpb.height: 30
*processStartQuitpb.bottomAttachment: "attach_form"
*processStartQuitpb.bottomOffset: 15
*processStartQuitpb.leftAttachment: "attach_position"
*processStartQuitpb.leftPosition: 70
*processStartQuitpb.rightAttachment: "attach_form"
*processStartQuitpb.rightOffset: 20
*processStartQuitpb.labelString: PROC_START_Quit ? PROC_START_Quit : "Quit"
*processStartQuitpb.activateCallback: {\
strcpy (selectedDisplay,"NO");\
closeRequest = 1;\
DistruggiInterfaccia (XtParent((Widget)UxClientData));\
}
*processStartQuitpb.activateCallbackClientData: processStart

*displaySelectForm.class: form
*displaySelectForm.static: true
*displaySelectForm.name: displaySelectForm
*displaySelectForm.parent: processStart
*displaySelectForm.resizePolicy: "resize_none"
*displaySelectForm.x: 0
*displaySelectForm.y: 10
*displaySelectForm.width: 360
*displaySelectForm.height: 130
*displaySelectForm.bottomAttachment: "attach_widget"
*displaySelectForm.bottomWidget: "frame21"
*displaySelectForm.rightAttachment: "attach_form"
*displaySelectForm.leftAttachment: "attach_form"
*displaySelectForm.topAttachment: "attach_form"

*label1.class: label
*label1.static: true
*label1.name: label1
*label1.parent: displaySelectForm
*label1.x: 20
*label1.y: 10
*label1.width: 330
*label1.height: 30
*label1.labelString: PROC_START_LABEL ? PROC_START_LABEL : "Process:"

*startProcessLabel.class: label
*startProcessLabel.static: true
*startProcessLabel.name: startProcessLabel
*startProcessLabel.parent: displaySelectForm
*startProcessLabel.x: 20
*startProcessLabel.y: 50
*startProcessLabel.width: 330
*startProcessLabel.height: 30
*startProcessLabel.labelString: testo ? testo : "NO TASK"

