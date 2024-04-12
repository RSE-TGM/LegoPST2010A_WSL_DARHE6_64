! UIMX ascii 2.0 key: 481                                                       

*questionDialog.class: questionDialog
*questionDialog.parent: NO_PARENT
*questionDialog.defaultShell: topLevelShell
*questionDialog.static: true
*questionDialog.gbldecl: /*\
   modulo questionDialog.i\
   tipo \
   release 1.24\
   data 8/29/95\
   reserved @(#)questionDialog.i	1.24\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include "topsim.h"\
#include "lg1_topsim.h"\
#include "questionMsgDb.h"\
\
extern SIMULATORE *simulatore;
*questionDialog.ispecdecl:
*questionDialog.funcdecl: /* parameter\
	swidget wcallers;  id widget chiamante ;\
        TIPO_OP nidop;    id tipo operazione ;\
*/\
 \
swidget create_questionDialog(swidget wcallers,TIPO_OP nidop)\

*questionDialog.funcname: create_questionDialog
*questionDialog.funcdef: "swidget", "<create_questionDialog>(%)"
*questionDialog.argdecl: swidget wcallers;\
TIPO_OP nidop;
*questionDialog.arglist: wcallers, nidop
*questionDialog.arglist.wcallers: "swidget", "%wcallers%"
*questionDialog.arglist.nidop: "TIPO_OP", "%nidop%"
*questionDialog.icode: extern Boolean simulator_changed;
*questionDialog.fcode: qelimina_help_button();\
\
switch( nidop)\
{\
   case BYEBYE:\
     if(!simulator_changed)\
        qset_message(question[nidop]);\
     else\
        qset_message("WARNING SIMULATOR MODIFIED. Do you want Really Exit?");\
   break;\
   case OPENSIM:\
   case REMOVESIM:\
   case DELTASK:        \
     qset_message(question[nidop]);\
   break;\
   case DELCONN:\
   break;\
   case DELALLCONN:\
     qset_message(question[nidop]);\
   break;    \
   default:\
     qset_message("Codice di uscita non riconosciuto.");\
   break;  \
}\
\
return(rtrn);\

*questionDialog.auxdecl: /* elimina_help_button\
   \
   elimina il bottone di help \
*/\
qelimina_help_button()\
{\
   Widget hb;\
  \
   hb = XmMessageBoxGetChild(questionDialog,XmDIALOG_HELP_BUTTON);\
   XtDestroyWidget(hb);\
}\
\
/* set_message \
 \
 set del messaggio sulla message box\
*/\
\
qset_message(char *mess)\
{\
   Arg args[1];\
   Cardinal nargs;\
   XmString mesg;\
\
   mesg = XmStringCreateSimple(mess);\
   nargs=0;\
   XtSetArg(args[nargs],XmNmessageString,mesg);nargs++;\
   XtSetValues(questionDialog,args,nargs);\
}  
*questionDialog.name: questionDialog
*questionDialog.dialogType: "dialog_question"
*questionDialog.unitType: "pixels"
*questionDialog.x: 260
*questionDialog.y: 310
*questionDialog.width: 280
*questionDialog.height: 140
*questionDialog.messageString: "Confirm Operation ?"
*questionDialog.okCallback: {\
extern void confermata_remove_simulator();\
extern Boolean simulator_changed;\
switch( nidop)\
{\
   case BYEBYE:\
     if( simulatore != NULL)\
        libera_simulatore(simulatore);\
 \
     printf("Topsim Normally Terminated\n"); \
     exit();\
   break;\
   case OPENSIM:\
      /* do nothing */\
   break;  \
   case REMOVESIM:\
      /* non  rimuovere la interfaccia di selezione */\
      confermata_remove_simulator();\
   break; \
   case DELTASK:\
      simulator_changed=True;\
      confermata_remove_task();\
   break;\
   case DELCONN:\
   break;   \
   case DELALLCONN:\
      simulator_changed=True;\
      del_all_task_conn();\
   break;\
   default:\
     printf("Operazione non riconosciuta\n");\
   break;  \
}\
}
*questionDialog.helpLabelString: "Help"
*questionDialog.dialogStyle: "dialog_full_application_modal"

