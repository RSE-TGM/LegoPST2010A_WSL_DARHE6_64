! UIMX ascii 2.5 key: 990                                                       

*errorDialog.class: errorDialog
*errorDialog.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo errorDialog.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)errorDialog.i	5.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include "config.h"
*errorDialog.ispecdecl:
*errorDialog.funcdecl: swidget create_errorDialog()\

*errorDialog.funcname: create_errorDialog
*errorDialog.funcdef: "swidget", "<create_errorDialog>(%)"
*errorDialog.icode:
*errorDialog.fcode: XtDestroyWidget(XmMessageBoxGetChild(rtrn,XmDIALOG_CANCEL_BUTTON));\
XtDestroyWidget(XmMessageBoxGetChild(rtrn,XmDIALOG_HELP_BUTTON));\
return(rtrn);\

*errorDialog.auxdecl:
*errorDialog.name.source: public
*errorDialog.static: false
*errorDialog.name: errorDialog
*errorDialog.parent: NO_PARENT
*errorDialog.defaultShell: topLevelShell
*errorDialog.msgDialogType: "dialog_error"
*errorDialog.unitType: "pixels"
*errorDialog.x: 500
*errorDialog.y: 400
*errorDialog.dialogStyle: "dialog_primary_application_modal"
*errorDialog.allowOverlap: "true"
*errorDialog.height.source: public
*errorDialog.height: 113
*errorDialog.width.source: public
*errorDialog.width: 500
*errorDialog.okCallback: {\
\
if(error_level == SEVERE)\
   exit(1);\
\
\
}
*errorDialog.allowShellResize: "true"

