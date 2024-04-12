! UIMX ascii 2.5 key: 3184                                                      

*questionDialogQuit.class: questionDialog
*questionDialogQuit.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo questionDialogQuit.i\
   tipo \
   release 5.2\
   data 1/22/96\
   reserved @(#)questionDialogQuit.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#include <stdio.h>\
\
\
\
#include "other.h"\
\
extern int password_ok;\

*questionDialogQuit.ispecdecl: Widget PadreDialogQuit;\

*questionDialogQuit.ispeclist: PadreDialogQuit
*questionDialogQuit.ispeclist.PadreDialogQuit: "Widget", "%PadreDialogQuit%"
*questionDialogQuit.funcdecl: swidget create_questionDialogQuit(Widget _PadreDialogQuit,Boolean scada_on)\

*questionDialogQuit.funcname: create_questionDialogQuit
*questionDialogQuit.funcdef: "swidget", "<create_questionDialogQuit>(%)"
*questionDialogQuit.argdecl: Widget _PadreDialogQuit;\
Boolean scada_on;
*questionDialogQuit.arglist: _PadreDialogQuit, scada_on
*questionDialogQuit.arglist._PadreDialogQuit: "Widget", "%_PadreDialogQuit%"
*questionDialogQuit.arglist.scada_on: "Boolean", "%scada_on%"
*questionDialogQuit.icode: extern swidget popup_password();\
XmFontList FontLabel;\
\
PadreDialogQuit= _PadreDialogQuit;\
\
#ifndef DESIGN_TIME\
if(!LoadFont(FONT_LABEL,&FontLabel,XtDisplay(PadreDialogQuit)))\
	exit(0);\
#endif
*questionDialogQuit.fcode: set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_CANCEL_BUTTON),XmNfontList,FontLabel);\
set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_HELP_BUTTON),XmNfontList,FontLabel);\
set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_OK_BUTTON),XmNfontList,FontLabel);\
set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_MESSAGE_LABEL),XmNfontList,FontLabel);\
UxPopupInterface(rtrn, no_grab);\
\
if(scada_on)\
	{\
	password_ok = 0;\
	popup_password(PadreDialogQuit);\
	}\
else\
	password_ok = 1;\
\
\
return(rtrn);\

*questionDialogQuit.auxdecl:
*questionDialogQuit.static: true
*questionDialogQuit.name: questionDialogQuit
*questionDialogQuit.parent: NO_PARENT
*questionDialogQuit.parentExpression: PadreDialogQuit
*questionDialogQuit.defaultShell: topLevelShell
*questionDialogQuit.msgDialogType: "dialog_question"
*questionDialogQuit.unitType: "pixels"
*questionDialogQuit.x: 442
*questionDialogQuit.y: 150
*questionDialogQuit.width: 288
*questionDialogQuit.height: 222
*questionDialogQuit.background: "#50a050"
*questionDialogQuit.messageString: "Exit LegoMMI ?"
*questionDialogQuit.dialogTitle: "Exit"
*questionDialogQuit.dialogStyle: "dialog_full_application_modal"
*questionDialogQuit.okCallback: {\
extern void quit_proc();\
\
if(password_ok == 1)\
	quit_proc();\
}
*questionDialogQuit.messageAlignment: "alignment_center"
*questionDialogQuit.noResize: "false"
*questionDialogQuit.resizePolicy: "resize_any"

