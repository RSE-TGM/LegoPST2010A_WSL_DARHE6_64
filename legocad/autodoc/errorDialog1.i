! UIMX ascii 2.0 key: 9722                                                      

*errorDialog1.class: errorDialog
*errorDialog1.parent: NO_PARENT
*errorDialog1.defaultShell: topLevelShell
*errorDialog1.static: true
*errorDialog1.gbldecl: /*\
   modulo errorDialog1.i\
   tipo \
   release 1.10\
   data 3/31/95\
   reserved @(#)errorDialog1.i	1.10\
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
#ifndef DESIGN_TIME\
#define CH_SET                   XmSTRING_DEFAULT_CHARSET\
#define CREATE_CSTRING(string)  (XmStringCreateLtoR(string,CH_SET))\
#endif
*errorDialog1.ispecdecl:
*errorDialog1.funcdecl: swidget crea_errorDialog(messaggio)\
char *messaggio;\

*errorDialog1.funcname: crea_errorDialog
*errorDialog1.funcdef: "swidget", "<crea_errorDialog>(%)"
*errorDialog1.argdecl: unsigned char *messaggio;
*errorDialog1.arglist: messaggio
*errorDialog1.arglist.messaggio: "unsigned char", "*%messaggio%"
*errorDialog1.icode: XmString cstring;
*errorDialog1.fcode: XtUnmanageChild(XmMessageBoxGetChild(UxGetWidget(errorDialog1), XmDIALOG_CANCEL_BUTTON));\
XtUnmanageChild(XmMessageBoxGetChild(UxGetWidget(errorDialog1), XmDIALOG_HELP_BUTTON));\
\
cstring = CREATE_CSTRING(messaggio);\
XtVaSetValues(UxGetWidget(errorDialog1), XmNmessageString, cstring, NULL);\
XmStringFree(cstring);\
\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*errorDialog1.auxdecl:
*errorDialog1.name: errorDialog1
*errorDialog1.dialogType: "dialog_error"
*errorDialog1.unitType: "pixels"
*errorDialog1.x: 110
*errorDialog1.y: 630
*errorDialog1.width: 450
*errorDialog1.height: 250
*errorDialog1.cancelLabelString: ""
*errorDialog1.dialogStyle: "dialog_full_application_modal"
*errorDialog1.helpLabelString: ""
*errorDialog1.textFontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*errorDialog1.buttonFontList: "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
*errorDialog1.resizePolicy: "resize_any"
*errorDialog1.noResize: "true"
*errorDialog1.background: "#4f9f9f"
*errorDialog1.dialogTitle: "Error!"
*errorDialog1.okCallback: {\
UxDestroySwidget(errorDialog1);\
}

