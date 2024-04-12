! UIMX ascii 2.5 key: 6519                                                      

*statisticsDisplay.class: formDialog
*statisticsDisplay.gbldecl: #include <stdio.h>\
\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
\
#include "sked.h"\
#include "messaggi.h"\
#include "bistrutt.h"\
#include "refresh.h"\
#ifndef DESIGN_TIME\
#include "masterMenu.h"\
#endif\
\
extern VAL val;   /* dati consolidati       */\
extern int nmod;  /* numero modelli attivi  */\
XtIntervalId timer_statisticsDisplay;
*statisticsDisplay.ispecdecl: Window dwg;\

*statisticsDisplay.ispeclist: dwg
*statisticsDisplay.ispeclist.dwg: "Window", "%dwg%"
*statisticsDisplay.funcdecl: Widget create_statisticsDisplay(UxParent)\
Widget UxParent;
*statisticsDisplay.funcname: create_statisticsDisplay
*statisticsDisplay.funcdef: "Widget", "<create_statisticsDisplay>(%)"
*statisticsDisplay.argdecl: Widget UxParent;
*statisticsDisplay.arglist: UxParent
*statisticsDisplay.arglist.UxParent: "Widget", "%UxParent%"
*statisticsDisplay.icode:
*statisticsDisplay.fcode: XtVaSetValues (drawingArea1,XmNheight,25*nmod,NULL);\
XtVaSetValues (statisticsDisplay,XmNheight,(25*nmod)+80+40,NULL);\
UxPopupInterface (rtrn, no_grab);\
attiva_timer_statistiche (UxGetWidget(drawingArea1));\
return(UxGetWidget(rtrn));\

*statisticsDisplay.auxdecl:
*statisticsDisplay.static: true
*statisticsDisplay.name: statisticsDisplay
*statisticsDisplay.parent: NO_PARENT
*statisticsDisplay.defaultShell: topLevelShell
*statisticsDisplay.unitType: "pixels"
*statisticsDisplay.x: 230
*statisticsDisplay.y: 380
*statisticsDisplay.width: 290
*statisticsDisplay.height: 150

*drawingArea1.class: drawingArea
*drawingArea1.static: true
*drawingArea1.name: drawingArea1
*drawingArea1.parent: statisticsDisplay
*drawingArea1.resizePolicy: "resize_any"
*drawingArea1.x: 10
*drawingArea1.y: 40
*drawingArea1.width: 300
*drawingArea1.height: 270 
*drawingArea1.exposeCallback: {\
dwg = ((XmDrawingAreaCallbackStruct *)UxCallbackArg)->window;\
istogramma_tasks (UxWidget);\
\
}
*drawingArea1.helpCallback: {\
\
}
*drawingArea1.createCallback: {\
\
}
*drawingArea1.bottomAttachment: "attach_none"
*drawingArea1.bottomWidget: ""
*drawingArea1.topAttachment: "attach_none"
*drawingArea1.topWidget: ""
*drawingArea1.rightAttachment: "attach_form"
*drawingArea1.leftAttachment: "attach_form"

*menu7.class: rowColumn
*menu7.static: true
*menu7.name: menu7
*menu7.parent: statisticsDisplay
*menu7.rowColumnType: "menu_bar"
*menu7.rightAttachment: "attach_form"
*menu7.leftAttachment: "attach_form"
*menu7.menuAccelerator: "<KeyUp>F10"
*menu7.bottomAttachment: "attach_widget"
*menu7.bottomWidget: "drawingArea1"
*menu7.topAttachment: "attach_form"

*menu7_p1.class: rowColumn
*menu7_p1.static: true
*menu7_p1.name: menu7_p1
*menu7_p1.parent: menu7
*menu7_p1.rowColumnType: "menu_pulldown"

*statDisplayMenuQuitpb.class: pushButton
*statDisplayMenuQuitpb.static: true
*statDisplayMenuQuitpb.name: statDisplayMenuQuitpb
*statDisplayMenuQuitpb.parent: menu7_p1
*statDisplayMenuQuitpb.labelString: "Quit"
*statDisplayMenuQuitpb.activateCallback: {\
#ifndef DESIGN_TIME\
_UxCmasterMenu *CtxMaster;\
CtxMaster = (_UxCmasterMenu *)UxGetContext(UxParent);\
CtxMaster->UxstatisticheDisplayTask = (Widget)NULL;\
#endif\
stop_timer (timer_statisticsDisplay);\
DistruggiInterfaccia(XtParent((Widget)UxClientData));\
}
*statDisplayMenuQuitpb.activateCallbackClientData: UxGetWidget(statisticsDisplay)

*menu7_top_b1.class: cascadeButton
*menu7_top_b1.static: true
*menu7_top_b1.name: menu7_top_b1
*menu7_top_b1.parent: menu7
*menu7_top_b1.labelString: "File"
*menu7_top_b1.subMenuId: "menu7_p1"

*frame20.class: frame
*frame20.static: true
*frame20.name: frame20
*frame20.parent: statisticsDisplay
*frame20.x: 10
*frame20.y: 310
*frame20.width: 280
*frame20.height: 80
*frame20.bottomAttachment: "attach_form"
*frame20.leftOffset: 0
*frame20.rightAttachment: "attach_form"
*frame20.leftAttachment: "attach_form"
*frame20.topAttachment: "attach_widget"
*frame20.topWidget: "drawingArea1"

*form47.class: form
*form47.static: true
*form47.name: form47
*form47.parent: frame20
*form47.resizePolicy: "resize_none"
*form47.x: 2
*form47.y: -20
*form47.width: 600
*form47.height: 68
*form47.defaultButton: "previewQuitpb1"

*previewQuitpb1.class: pushButton
*previewQuitpb1.static: true
*previewQuitpb1.name: previewQuitpb1
*previewQuitpb1.parent: form47
*previewQuitpb1.x: 493
*previewQuitpb1.y: 35
*previewQuitpb1.width: 100
*previewQuitpb1.height: 30
*previewQuitpb1.labelString: "QUIT"
*previewQuitpb1.bottomAttachment: "attach_form"
*previewQuitpb1.leftAttachment: "attach_position"
*previewQuitpb1.rightAttachment: "attach_position"
*previewQuitpb1.bottomOffset: 15
*previewQuitpb1.rightOffset: 0
*previewQuitpb1.leftPosition: 40
*previewQuitpb1.leftOffset: 0
*previewQuitpb1.topAttachment: "attach_form"
*previewQuitpb1.topOffset: 15
*previewQuitpb1.activateCallback: {\
#ifndef DESIGN_TIME\
_UxCmasterMenu *CtxMaster;\
CtxMaster = (_UxCmasterMenu *)UxGetContext(UxParent);\
CtxMaster->UxstatisticheDisplayTask = (Widget)NULL;\
#endif\
stop_timer (timer_statisticsDisplay);\
DistruggiInterfaccia(XtParent((Widget)UxClientData));\
}
*previewQuitpb1.activateCallbackClientData: UxGetWidget(statisticsDisplay)
*previewQuitpb1.rightPosition: 60

