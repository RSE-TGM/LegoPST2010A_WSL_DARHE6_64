! UIMX ascii 2.0 key: 7585                                                      

*question_environment.class: questionDialog
*question_environment.parent: NO_PARENT
*question_environment.parentExpression: applicationShell1
*question_environment.defaultShell: applicationShell
*question_environment.static: true
*question_environment.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo question_environment.i\
   tipo \
   release 2.25\
   data 5/12/95\
   reserved @(#)question_environment.i	2.25\
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
#include "legomain.h"\
extern swidget applicationShell1;\
extern char path_legocad[FILENAME_MAX]; /* path_name che individua la sottodirectory\
                           legocad per l'utente */\
extern char path_libut[FILENAME_MAX];  /* path_name che individua la libreria dei moduli\
			  di processo */\
extern char path_libreg[FILENAME_MAX]; /* path_name che individua la libreria dei moduli\
                             di regolazione */\

*question_environment.ispecdecl: char app[300];
*question_environment.ispeclist: app
*question_environment.ispeclist.app: "unsigned char", "%app%[300]"
*question_environment.funcdecl: swidget create_question_environment(tipo_q)\
int tipo_q;
*question_environment.funcname: create_question_environment
*question_environment.funcdef: "swidget", "<create_question_environment>(%)"
*question_environment.argdecl: int tipo_q;
*question_environment.arglist: tipo_q
*question_environment.arglist.tipo_q: "int", "%tipo_q%"
*question_environment.icode:
*question_environment.fcode: app[0]=0;\
if(testa_ambiente()) /* True se librerie presenti */\
		{\
		strcpy (app,"LEGOCAD ENVIRONMENT IS PROPERLY CONFIGURED:\n\\
CREATION OF NEW LEGOCAD ENVIRONMENT\n\\
MAY CAUSE MODIFICATION IN PREEXISTENT MODELS !!!\n\n");\
		}\
strcat(app,"Operations Requested:\n");	\
if(tipo_q & K_COPY_LEGOCAD_LIBUT)\
	sprintf(&app[strlen(app)],"Copy Defaults Modules Library in %s \n",\
                path_libut);\
if(tipo_q & K_COPY_LEGOCAD_LIBREG)\
	sprintf(&app[strlen(app)],"Copy Defaults Control Modules Library in %s \n",\
		path_libreg);\
if(tipo_q & K_CREATE_LEGOCAD_LIBUT)\
	strcat(app,"Create Modules Library\n");\
if(tipo_q & K_CREATE_LEGOCAD_LIBREG)\
	strcat(app,"Create Modules Library");\
UxPutMessageString(rtrn,app);\
\
XtUnmanageChild(XmMessageBoxGetChild(UxGetWidget(rtrn), XmDIALOG_HELP_BUTTON));\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*question_environment.auxdecl:
*question_environment.name: question_environment
*question_environment.dialogType: "dialog_question"
*question_environment.unitType: "pixels"
*question_environment.x: 340
*question_environment.y: 355
*question_environment.width: 325
*question_environment.height: 150
*question_environment.dialogStyle: "dialog_primary_application_modal"
*question_environment.okCallbackClientData: (XtPointer) 0x0
*question_environment.cancelCallback: {\
UxDestroyInterface(UxWidget);\
}
*question_environment.okCallback: {\
UxDestroyInterface(UxWidget);\
switch(tipo_q)\
	{\
	case K_CREATE_LEGOCAD_ENV:\
	break;\
	case K_COPY_LEGOCAD_LIBUT:\
	break;\
	case K_COPY_LEGOCAD_LIBREG:\
	break;\
	}\
}
*question_environment.messageAlignment: "alignment_beginning"

