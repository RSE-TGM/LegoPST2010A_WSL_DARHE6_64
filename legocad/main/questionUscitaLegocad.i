! UIMX ascii 2.0 key: 6163                                                      

*questionUscitaLegocad.class: questionDialog
*questionUscitaLegocad.parent: NO_PARENT
*questionUscitaLegocad.defaultShell: applicationShell
*questionUscitaLegocad.static: true
*questionUscitaLegocad.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo questionUscitaLegocad.i\
   tipo \
   release 2.25\
   data 5/12/95\
   reserved @(#)questionUscitaLegocad.i	2.25\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#endif\
\
#include <stdio.h>\
#ifdef HYPERHELP_USED\
#include "winhelp.h"\
#endif
*questionUscitaLegocad.ispecdecl:
*questionUscitaLegocad.funcdecl: swidget create_questionUscitaLegocad(mess)\
char *mess;
*questionUscitaLegocad.funcname: create_questionUscitaLegocad
*questionUscitaLegocad.funcdef: "swidget", "<create_questionUscitaLegocad>(%)"
*questionUscitaLegocad.argdecl: unsigned char *mess;
*questionUscitaLegocad.arglist: mess
*questionUscitaLegocad.arglist.mess: "unsigned char", "*%mess%"
*questionUscitaLegocad.icode:
*questionUscitaLegocad.fcode: XtUnmanageChild(XmMessageBoxGetChild(UxGetWidget(rtrn), XmDIALOG_HELP_BUTTON));\
return(rtrn);\

*questionUscitaLegocad.auxdecl:
*questionUscitaLegocad.name: questionUscitaLegocad
*questionUscitaLegocad.dialogType: "dialog_question"
*questionUscitaLegocad.unitType: "pixels"
*questionUscitaLegocad.x: 575
*questionUscitaLegocad.y: 70
*questionUscitaLegocad.width: 305
*questionUscitaLegocad.height: 150
*questionUscitaLegocad.defaultButtonType: "dialog_cancel_button"
*questionUscitaLegocad.dialogStyle: "dialog_full_application_modal"
*questionUscitaLegocad.messageString: mess
*questionUscitaLegocad.cancelCallback: {\
UxDestroyInterface(questionUscitaLegocad);\
}
*questionUscitaLegocad.dialogTitle: "EXIT LEGOCAD"
*questionUscitaLegocad.okCallback: {\
/* uccide eventuali processi ancora attivi */\
kill_proc_legocad();\
UxDestroyInterface(questionUscitaLegocad);\
#ifdef HYPERHELP_USED\
WinHelp(UxDisplay,"",HELP_QUIT,0);\
#endif\
exit(0);\
}

