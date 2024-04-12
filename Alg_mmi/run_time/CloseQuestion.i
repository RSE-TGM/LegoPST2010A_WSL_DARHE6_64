! UIMX ascii 2.5 key: 1242                                                      

*CloseQuestion.class: questionDialog
*CloseQuestion.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo CloseQuestion.i\
   tipo \
   release 5.2\
   data 1/22/96\
   reserved @(#)CloseQuestion.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
\
#include "other.h"\
\
#include <Rt/RtMemory.h>\
\
Widget PadreClose;
*CloseQuestion.ispecdecl: Widget PaginaSinottico, PaginaDrawing;\
XmFontList FontLabelClose;\

*CloseQuestion.ispeclist: PaginaSinottico, PaginaDrawing, FontLabelClose
*CloseQuestion.ispeclist.PaginaSinottico: "Widget", "%PaginaSinottico%"
*CloseQuestion.ispeclist.PaginaDrawing: "Widget", "%PaginaDrawing%"
*CloseQuestion.ispeclist.FontLabelClose: "XmFontList", "%FontLabelClose%"
*CloseQuestion.funcdecl: swidget popup_CloseQuestion(Widget Top, Widget Drawing,XtIntervalId *timer, int key)
*CloseQuestion.funcname: popup_CloseQuestion
*CloseQuestion.funcdef: "swidget", "<popup_CloseQuestion>(%)"
*CloseQuestion.argdecl: Widget Top;\
Widget Drawing;\
XtIntervalId *timer;\
int key;
*CloseQuestion.arglist: Top, Drawing, timer, key
*CloseQuestion.arglist.Top: "Widget", "%Top%"
*CloseQuestion.arglist.Drawing: "Widget", "%Drawing%"
*CloseQuestion.arglist.timer: "XtIntervalId", "*%timer%"
*CloseQuestion.arglist.key: "int", "%key%"
*CloseQuestion.icode: PaginaSinottico= Top;\
PaginaDrawing=Drawing;\
\
PadreClose= Top;\
\
#if defined SCADA_MMI\
#ifndef DESIGN_TIME\
DelElencoPagine(key, PaginaDrawing);\
#endif\
XtRemoveTimeOut(*timer);\
XtDestroyWidget(PaginaSinottico);\
return(NULL);\
#endif\
\
#ifndef DESIGN_TIME\
if(!LoadFont(FONT_LABEL,&FontLabelClose,XtDisplay(PadreClose)))\
	exit(0);\
#endif
*CloseQuestion.fcode: UxPopupInterface(rtrn, no_grab);\
set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_CANCEL_BUTTON),XmNfontList,FontLabelClose);\
set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_HELP_BUTTON),XmNfontList,FontLabelClose);\
set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_OK_BUTTON),XmNfontList,FontLabelClose);\
set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_MESSAGE_LABEL),XmNfontList,FontLabelClose);\
return(rtrn);\

*CloseQuestion.auxdecl:
*CloseQuestion.static: true
*CloseQuestion.name: CloseQuestion
*CloseQuestion.parent: NO_PARENT
*CloseQuestion.parentExpression: PadreClose
*CloseQuestion.defaultShell: topLevelShell
*CloseQuestion.msgDialogType: "dialog_question"
*CloseQuestion.unitType: "pixels"
*CloseQuestion.x: 381
*CloseQuestion.y: 135
*CloseQuestion.width: 544
*CloseQuestion.height: 149
*CloseQuestion.background: "#50a050"
*CloseQuestion.messageString: "Close the page ?"
*CloseQuestion.okCallback: {\
#ifndef DESIGN_TIME\
DelElencoPagine(key, PaginaDrawing);\
XSync(XtDisplay(UxWidget),False);\
#endif\
XtRemoveTimeOut(*timer);\
XtDestroyWidget(PaginaSinottico);\
}
*CloseQuestion.helpLabelString: "Help"
*CloseQuestion.messageAlignment: "alignment_center"
*CloseQuestion.okLabelString: "Ok"
*CloseQuestion.dialogStyle: "dialog_full_application_modal"
*CloseQuestion.allowShellResize: "true"
*CloseQuestion.destroyCallback: {\
\
}

