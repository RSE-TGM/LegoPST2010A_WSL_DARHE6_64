! UIMX ascii 2.0 key: 4341                                                      

*messageDialog.class: questionDialog
*messageDialog.parent: NO_PARENT
*messageDialog.defaultShell: topLevelShell
*messageDialog.static: true
*messageDialog.gbldecl: /*\
   modulo messageDialog.i\
   tipo \
   release 1.24\
   data 8/29/95\
   reserved @(#)messageDialog.i	1.24\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include "questionMsgDb.h"\

*messageDialog.ispecdecl:
*messageDialog.funcdecl: /* parameter \
	swidget wcaller; id widget chimanate;\
        TIPO_OP miidop;  id tipo operazione;\
*/  \
swidget create_messageDialog(swidget wcaller,TIPO_OP midop)\

*messageDialog.funcname: create_messageDialog
*messageDialog.funcdef: "swidget", "<create_messageDialog>(%)"
*messageDialog.argdecl: swidget wcaller;\
TIPO_OP midop;
*messageDialog.arglist: wcaller, midop
*messageDialog.arglist.wcaller: "swidget", "%wcaller%"
*messageDialog.arglist.midop: "TIPO_OP", "%midop%"
*messageDialog.icode:
*messageDialog.fcode: melimina_help_button();\
\
switch( midop)\
{\
   case BYEBYE:\
   case CREASIM:\
   case OPENSIM:\
   case REMOVESIM:\
   case ADDTASK:\
     mset_message(message[midop]);\
   break;\
   default:\
     mset_message("Operazione non riconosciuta. Chiedere assistenza tecnica");\
   break;  \
}\
\
return(rtrn);\

*messageDialog.auxdecl: /* elimina_help_button\
   \
   elimina il bottone di help \
*/\
melimina_help_button()\
{\
   Widget hb;\
  \
   hb = XmMessageBoxGetChild(messageDialog,XmDIALOG_HELP_BUTTON);\
   XtDestroyWidget(hb);\
}\
\
/* set_message \
 \
 set del messaggio sulla message box\
*/\
\
mset_message(char *mess)\
{\
   Arg args[1];\
   Cardinal nargs;\
   XmString mesg;\
\
   mesg = XmStringCreateSimple(mess);\
   nargs=0;\
   XtSetArg(args[nargs],XmNmessageString,mesg);nargs++;\
   XtSetValues(messageDialog,args,nargs);\
}
*messageDialog.name: messageDialog
*messageDialog.dialogType: "dialog_message"
*messageDialog.unitType: "pixels"
*messageDialog.x: 973
*messageDialog.y: 146
*messageDialog.width: 280
*messageDialog.height: 140
*messageDialog.messageString: " Message on operation" 
*messageDialog.okCallback: {\
UxDestroyInterface(UxWidget);\
}
*messageDialog.helpLabelString: "Help"
*messageDialog.messageAlignment: "alignment_center"

