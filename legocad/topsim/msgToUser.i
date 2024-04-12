! UIMX ascii 2.0 key: 3575                                                      

*msgToUser.class: messageBoxDialog
*msgToUser.parent: NO_PARENT
*msgToUser.defaultShell: topLevelShell
*msgToUser.static: false
*msgToUser.gbldecl: /*\
   modulo msgToUser.i\
   tipo \
   release 1.17\
   data 8/29/95\
   reserved @(#)msgToUser.i	1.17\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\

*msgToUser.ispecdecl:
*msgToUser.funcdecl: swidget create_msgToUser(int level,char *msg)\

*msgToUser.funcname: create_msgToUser
*msgToUser.funcdef: "swidget", "<create_msgToUser>(%)"
*msgToUser.argdecl: int level;\
unsigned char *msg;
*msgToUser.arglist: level, msg
*msgToUser.arglist.level: "int", "%level%"
*msgToUser.arglist.msg: "unsigned char", "*%msg%"
*msgToUser.icode: Arg arg[2];\
Cardinal narg;\
XmString xmsg;
*msgToUser.fcode: xmsg=XmStringCreateSimple(msg);\
\
set_something(rtrn,XmNmessageString,xmsg);\
\
XtDestroyWidget(XmMessageBoxGetChild(rtrn,XmDIALOG_CANCEL_BUTTON));\
XtDestroyWidget(XmMessageBoxGetChild(rtrn,XmDIALOG_HELP_BUTTON));\
UxPopupInterface(rtrn,no_grab);\
return(rtrn);\

*msgToUser.auxdecl:
*msgToUser.name: msgToUser
*msgToUser.unitType: "pixels"
*msgToUser.x: 448
*msgToUser.y: 353
*msgToUser.width: 494
*msgToUser.height: 225
*msgToUser.dialogStyle: "dialog_full_application_modal"
*msgToUser.dialogType: "dialog_message"
*msgToUser.messageAlignment: "alignment_center"
*msgToUser.messageString: "Message To User"
*msgToUser.symbolPixmap: "/usr/include/X11/bitmaps/xdt_m_large/warning.px"
*msgToUser.okCallback: {\
UxDestroyInterface(UxWidget);\
}

