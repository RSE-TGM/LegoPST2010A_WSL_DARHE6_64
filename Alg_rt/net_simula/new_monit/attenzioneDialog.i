! UIMX ascii 2.5 key: 1860                                                      

*attenzioneDialog.class: warningDialog
*attenzioneDialog.gbldecl: #include <stdio.h>\
#ifndef DESIGN_TIME\
#include "parametri.h"\
#endif\
int risposta;\
char *messaggio;
*attenzioneDialog.ispecdecl:
*attenzioneDialog.funcdecl: int create_attenzioneDialog(padre_warn,warning_message,modo)\
Widget padre_warn;\
char *warning_message;\
int modo;   /* tipo di interfaccia */
*attenzioneDialog.funcname: create_attenzioneDialog
*attenzioneDialog.funcdef: "int", "<create_attenzioneDialog>(%)"
*attenzioneDialog.argdecl: Widget padre_warn;\
unsigned char *warning_message;\
int modo;
*attenzioneDialog.arglist: padre_warn, warning_message, modo
*attenzioneDialog.arglist.padre_warn: "Widget", "%padre_warn%"
*attenzioneDialog.arglist.warning_message: "unsigned char", "*%warning_message%"
*attenzioneDialog.arglist.modo: "int", "%modo%"
*attenzioneDialog.icode: risposta = -1;\
messaggio = (char *)malloc (strlen(warning_message)+1);\
strcpy (messaggio,warning_message);
*attenzioneDialog.fcode: /* elimino comunque il tasto HELP */\
XtUnmanageChild (\
    XmMessageBoxGetChild(UxGetWidget(rtrn),XmDIALOG_HELP_BUTTON));\
\
#ifndef DESIGN_TIME\
\
switch (modo)\
   {\
   case DIALOG_ERROR:\
	XtVaSetValues (rtrn, \
		XmNbackground, colore_app[COLORE_DIALOG_ERROR],\
		XmNdialogType, modo, NULL);\
	XtUnmanageChild (\
    		XmMessageBoxGetChild(UxGetWidget(rtrn),\
		XmDIALOG_CANCEL_BUTTON));\
	break;\
   case DIALOG_INFORMATION:\
	XtVaSetValues (rtrn, XmNdialogType, modo, NULL);\
	XtUnmanageChild (\
    		XmMessageBoxGetChild(UxGetWidget(rtrn),\
		XmDIALOG_CANCEL_BUTTON));\
	break;\
   case DIALOG_MESSAGE:\
	XtVaSetValues (rtrn, XmNdialogType, modo, NULL);\
	break;\
   case DIALOG_QUESTION:\
	XtVaSetValues (rtrn, XmNdialogType, modo, NULL);\
	break;\
   case DIALOG_WARNING:\
	XtVaSetValues (rtrn, \
		XmNbackground, colore_app[COLORE_DIALOG_ERROR],\
		XmNdialogType, modo, NULL);\
	XtUnmanageChild (\
    		XmMessageBoxGetChild(UxGetWidget(rtrn),\
		XmDIALOG_CANCEL_BUTTON));\
	break;\
   case DIALOG_WORKING:\
	XtVaSetValues (rtrn, XmNdialogType, modo, NULL);\
	XtUnmanageChild (\
    		XmMessageBoxGetChild(UxGetWidget(rtrn),\
		XmDIALOG_CANCEL_BUTTON));\
	break;\
   default:\
	break;\
   }\
\
#endif\
\
UxPopupInterface (rtrn,no_grab);\
while (risposta == -1)\
   {\
   XtAppProcessEvent (UxAppContext,XtIMAll);\
   XSync (UxDisplay,0);\
   }\
printf ("chiusura warning\n");\
return(risposta);\

*attenzioneDialog.auxdecl:
*attenzioneDialog.name.source: public
*attenzioneDialog.static: false
*attenzioneDialog.name: attenzioneDialog
*attenzioneDialog.parent: NO_PARENT
*attenzioneDialog.parentExpression: padre_warn
*attenzioneDialog.defaultShell: topLevelShell
*attenzioneDialog.msgDialogType: "dialog_warning"
*attenzioneDialog.unitType: "pixels"
*attenzioneDialog.x: 630
*attenzioneDialog.y: 65
*attenzioneDialog.width: 440
*attenzioneDialog.height: 215
*attenzioneDialog.dialogStyle: "dialog_full_application_modal"
*attenzioneDialog.messageString: messaggio
*attenzioneDialog.cancelCallback: {\
risposta = FALSE;\
}
*attenzioneDialog.okCallback: {\
risposta = TRUE;\
}
*attenzioneDialog.allowShellResize: "true"
*attenzioneDialog.messageAlignment: "alignment_center"

