! UIMX ascii 2.0 key: 3677                                                      

*messageDB.class: errorDialog
*messageDB.parent: NO_PARENT
*messageDB.defaultShell: topLevelShell
*messageDB.static: false
*messageDB.gbldecl: #ifndef DESIGN_TIME\
\
/*\
   modulo messageDB.i\
   tipo \
   release 2.24\
   data 3/30/95\
   reserved @(#)messageDB.i	2.24\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#endif\
\
#include <stdio.h>\
#include "message_type.h"\
\
MESSAGE message;
*messageDB.ispecdecl:
*messageDB.funcdecl: swidget create_messageDB()\

*messageDB.funcname: create_messageDB
*messageDB.funcdef: "swidget", "<create_messageDB>(%)"
*messageDB.icode: Widget wid;
*messageDB.fcode: wid = XmMessageBoxGetChild( UxGetWidget(rtrn), XmDIALOG_HELP_BUTTON );\
XtUnmanageChild( wid );\
\
wid = XmMessageBoxGetChild( UxGetWidget(rtrn), XmDIALOG_CANCEL_BUTTON );\
XtUnmanageChild( wid );\
\
return(rtrn);\
\
\

*messageDB.auxdecl: messageDB_activate ( message )\
char *message;\
{\
\
   extern swidget messageDB;\
   extern swidget lg1MainWindow;\
\
\
   UxPutMessageString(messageDB,message);\
   UxPopupInterface(messageDB,no_grab);\
/*   set_win_cursors( "busy" );\
*/\
}\
\
\
\
show_error( mess )\
char *mess;\
{\
   extern MESSAGE message;\
\
   message = MSG_ERROR;\
\
   messageDB_activate( mess );\
}\
\
fatal_err( mess )\
char *mess;\
{\
   extern MESSAGE message;\
\
   message = MSG_FATAL_ERROR;\
\
   messageDB_activate( mess );\
}
*messageDB.name: messageDB
*messageDB.dialogType: "dialog_error"
*messageDB.unitType: "pixels"
*messageDB.x: 825
*messageDB.y: 120
*messageDB.width: 380
*messageDB.height: 260
*messageDB.dialogStyle: "dialog_full_application_modal"
*messageDB.okCallback: {\
\
/***\
reset_win_cursors();\
***/\
\
switch ( message ) {\
\
   case MSG_ERROR:\
   case MSG_MADE_CONN: \
   case MSG_WARNING_CONN: \
                    break;\
   case MSG_FATAL_ERROR:\
      exit(0);\
    break;\
}\
\
}

