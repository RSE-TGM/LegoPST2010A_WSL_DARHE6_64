! UIMX ascii 2.5 key: 3108                                                      

*errorDialog.class: errorDialog
*errorDialog.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo errorDialog.i\
   tipo \
   release 5.2\
   data 1/22/96\
   reserved @(#)errorDialog.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#include <stdio.h>\
\
#include "other.h"\
\
\
Widget PadreError;
*errorDialog.ispecdecl: Widget topLevel_error;\
XmFontList FontLabelError;\
Cursor cursor_errore;\

*errorDialog.ispeclist: topLevel_error, FontLabelError, cursor_errore
*errorDialog.ispeclist.topLevel_error: "Widget", "%topLevel_error%"
*errorDialog.ispeclist.FontLabelError: "XmFontList", "%FontLabelError%"
*errorDialog.ispeclist.cursor_errore: "Cursor", "%cursor_errore%"
*errorDialog.funcdecl: swidget create_errorDialog(char *Errore, Widget TopError)\

*errorDialog.funcname: create_errorDialog
*errorDialog.funcdef: "swidget", "<create_errorDialog>(%)"
*errorDialog.argdecl: unsigned char *Errore;\
Widget TopError;
*errorDialog.arglist: Errore, TopError
*errorDialog.arglist.Errore: "unsigned char", "*%Errore%"
*errorDialog.arglist.TopError: "Widget", "%TopError%"
*errorDialog.icode: char message[200];\
\
PadreError=TopError;\
topLevel_error=TopError;\
\
/*\
	risalgo alla topLevel\
*/\
PadreError=ToTopLevel(PadreError);\
\
printf("ERRORE - %s\n",Errore);\
#ifndef DESIGN_TIME\
if(!LoadFont(FONT_LABEL,&FontLabelError,XtDisplay(topLevel_error)))\
	exit(0);\
#endif
*errorDialog.fcode: UxPopupInterface(rtrn, no_grab);\
cursor_errore=XlCreateErrCursor(errorDialog);\
XlSetCursor(errorDialog,cursor_errore);\
set_something(errorDialog,XmNmessageString,\
		XmStringCreateLtoR(Errore, XmSTRING_DEFAULT_CHARSET));\
set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_CANCEL_BUTTON),XmNfontList,FontLabelError);\
set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_HELP_BUTTON),XmNfontList,FontLabelError);\
set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_OK_BUTTON),XmNfontList,FontLabelError);\
set_something(XmMessageBoxGetChild(rtrn,XmDIALOG_MESSAGE_LABEL),XmNfontList,FontLabelError);\
sprintf(message,"%s\n",Errore);\
show_warning(message);\
return(rtrn);\

*errorDialog.auxdecl: CursorErrFree(Widget wid,Cursor cur)\
{\
XlUnsetCursor(wid);\
XlFreeCursor(wid,cur);\
}\
\
#ifndef DESIGN_TIME\
Widget popup_errorDialog(char *Errore_, Widget TopError_)\
{\
return(create_errorDialog(Errore_,TopError_));\
}\
#endif
*errorDialog.static: true
*errorDialog.name: errorDialog
*errorDialog.parent: NO_PARENT
*errorDialog.parentExpression: PadreError
*errorDialog.defaultShell: topLevelShell
*errorDialog.msgDialogType: "dialog_error"
*errorDialog.unitType: "pixels"
*errorDialog.x: 220
*errorDialog.y: 600
*errorDialog.width: 450
*errorDialog.height: 300
*errorDialog.background: "#50a050"
*errorDialog.dialogTitle: "Error"
*errorDialog.messageString: "Error !!!"
*errorDialog.dialogStyle: "dialog_full_application_modal"
*errorDialog.messageAlignment: "alignment_center"
*errorDialog.allowShellResize: "true"
*errorDialog.okCallback: {\
CursorErrFree(errorDialog,cursor_errore);\
PutPagBackground();\
}
*errorDialog.cancelCallback: {\
CursorErrFree(errorDialog,cursor_errore);\
PutPagBackground();\
}
*errorDialog.helpCallback: {\
\
PutPagBackground();\
}

