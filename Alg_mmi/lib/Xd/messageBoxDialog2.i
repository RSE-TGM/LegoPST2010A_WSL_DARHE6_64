! UIMX ascii 2.5 key: 762                                                       

*messageBoxDialog2.class: messageBoxDialog
*messageBoxDialog2.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo messageBoxDialog2.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)messageBoxDialog2.i	5.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <Xm/Xm.h>\
#include "message.h"\
\

*messageBoxDialog2.ispecdecl:
*messageBoxDialog2.funcdecl: swidget create_messageBoxDialog2(Widget Parent)\

*messageBoxDialog2.funcname: create_messageBoxDialog2
*messageBoxDialog2.funcdef: "swidget", "<create_messageBoxDialog2>(%)"
*messageBoxDialog2.argdecl: Widget Parent;
*messageBoxDialog2.arglist: Parent
*messageBoxDialog2.arglist.Parent: "Widget", "%Parent%"
*messageBoxDialog2.icode: if(Parent == NULL)\
	Parent = UxTopLevel;
*messageBoxDialog2.fcode: return(rtrn);\
\

*messageBoxDialog2.auxdecl: Boolean ConfiguraDialogo(MESSAGGI mes)\
{\
   Widget WCButton,WHButton;\
   XmString Titolo,Messaggio,LabOk,LabCancel,LabHelp;\
\
/* set layout interfaccia */\
   switch(mes.idType)\
   {\
      case INFMSG:\
         set_something(messageBoxDialog2,XmNdialogType,XmDIALOG_MESSAGE);\
         set_something(messageBoxDialog2,XmNdialogStyle,XmDIALOG_PRIMARY_APPLICATION_MODAL);\
      break;\
      case WRNMSG:\
         set_something(messageBoxDialog2,XmNdialogType,XmDIALOG_WARNING);\
         set_something(messageBoxDialog2,XmNdialogStyle,XmDIALOG_PRIMARY_APPLICATION_MODAL);\
      break;\
      case ERRMSG:\
         set_something(messageBoxDialog2,XmNdialogType,XmDIALOG_ERROR);\
         set_something(messageBoxDialog2,XmNdialogStyle,XmDIALOG_FULL_APPLICATION_MODAL);\
      break;      \
   }\
\
   WCButton = XmMessageBoxGetChild(messageBoxDialog2,XmDIALOG_CANCEL_BUTTON);     \
   WHButton = XmMessageBoxGetChild(messageBoxDialog2,XmDIALOG_HELP_BUTTON);     \
\
/* set Lebl dei bottoni e destroy dei bottoni non desiderati */\
\
\
   LabOk = XmStringCreateSimple(mes.LabelOk);\
   set_something(messageBoxDialog2,XmNokLabelString,LabOk);\
\
   if(!mes.CancelButton && WCButton)\
      XtDestroyWidget(WCButton);\
   else\
   {\
      LabCancel = XmStringCreateSimple(mes.LabelCancel);\
      set_something(messageBoxDialog2,XmNcancelLabelString,LabCancel);\
   }\
\
   if(!mes.HelpButton && WHButton)\
      XtDestroyWidget(WHButton);\
   else\
   {\
      LabHelp   = XmStringCreateSimple(mes.LabelHelp);\
      set_something(messageBoxDialog2,XmNhelpLabelString,LabHelp);\
   }\
\
\
/* setto il titolo e il messaggio */\
   Messaggio = XmStringCreateSimple(mes.msg);\
   Titolo   = XmStringCreateSimple(mes.titolo);\
   set_something(messageBoxDialog2,XmNdialogTitle,Titolo);\
   set_something(messageBoxDialog2,XmNmessageString,Messaggio);\
\
   return(True);\
}\
\
SetMsg(swidget WParent,int id,int err_level,char *shtitle,char *msg,char *lOk,Boolean Cancel,char *lCancel,Boolean Help,char *lHelp)\
{\
   swidget ShMsg;\
   MESSAGGI mesg;\
\
   mesg.idOp = id;\
   mesg.idType = err_level;\
\
   if(shtitle != NULL)\
      strcpy(mesg.titolo,shtitle);\
  \
\
   strcpy(mesg.msg,msg);\
\
   if(lOk != NULL)\
      strcpy(mesg.LabelOk,lOk);\
   else\
      strcpy(mesg.LabelOk,"Ok");\
\
   mesg.CancelButton = Cancel;\
\
   if(lCancel != NULL)\
      strcpy(mesg.LabelCancel,lCancel);\
   else\
      strcpy(mesg.LabelCancel,"Cancel");\
\
   mesg.HelpButton = Help;\
\
   if(lHelp != NULL)\
      strcpy(mesg.LabelHelp,lHelp); \
   else\
      strcpy(mesg.LabelHelp,"Help"); \
\
   if(WParent == NULL)\
      WParent = UxTopLevel;\
 \
#ifndef DESIGN_TIME\
   ShMsg = create_messageBoxDialog2(WParent);\
   if( ConfiguraDialogo(mesg) == True)\
      UxPopupInterface(ShMsg,no_grab);\
#endif\
} 
*messageBoxDialog2.static: true
*messageBoxDialog2.name: messageBoxDialog2
*messageBoxDialog2.parent: NO_PARENT
*messageBoxDialog2.parentExpression: Parent
*messageBoxDialog2.defaultShell: topLevelShell
*messageBoxDialog2.unitType: "pixels"
*messageBoxDialog2.width: 440
*messageBoxDialog2.height: 180
*messageBoxDialog2.allowOverlap: "false"
*messageBoxDialog2.messageAlignment: "alignment_center"

