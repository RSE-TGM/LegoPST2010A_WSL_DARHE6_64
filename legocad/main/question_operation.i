! UIMX ascii 2.0 key: 5777                                                      

*question_operation.class: questionDialog
*question_operation.parent: NO_PARENT
*question_operation.defaultShell: topLevelShell
*question_operation.static: true
*question_operation.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo question_operation.i\
   tipo \
   release 1.22\
   data 5/16/95\
   reserved @(#)question_operation.i	1.22\
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
\
extern swidget applicationShell1;\
extern char path_legocad[];\
extern swidget create_vis_msg();\
\
/* 04/07/97 Carlo\
*/\
extern char *get_select_model_new();
*question_operation.ispecdecl: char appo[300];\
char pathmodel[300];\
Widget wchiamante;
*question_operation.ispeclist: appo, pathmodel, wchiamante
*question_operation.ispeclist.appo: "unsigned char", "%appo%[300]"
*question_operation.ispeclist.pathmodel: "unsigned char", "%pathmodel%[300]"
*question_operation.ispeclist.wchiamante: "Widget", "%wchiamante%"
*question_operation.funcdecl: swidget create_question_operation(swidget wgt_call,int tip_q)\

*question_operation.funcname: create_question_operation
*question_operation.funcdef: "swidget", "<create_question_operation>(%)"
*question_operation.argdecl: swidget wgt_call;\
int tip_q;
*question_operation.arglist: wgt_call, tip_q
*question_operation.arglist.wgt_call: "swidget", "%wgt_call%"
*question_operation.arglist.tip_q: "int", "%tip_q%"
*question_operation.icode: char *nome_ret;\
\
wchiamante = wgt_call;\
\
printf("ricevo il parametro %d\n",tip_q);\
if(tip_q == Q_DELETE_MODEL)\
{\
strcpy(pathmodel,path_legocad);\
strcat(pathmodel,"/");\
\
nome_ret = get_select_model_new();\
if( (nome_ret == NULL) || (!strlen(nome_ret)) )\
{\
   create_vis_msg("Invalid model name selected");\
   return(0);\
}\
 \
strcat(pathmodel,get_select_model_new());\
}
*question_operation.fcode: switch( tip_q )\
{\
   case Q_DELETE_MODEL:\
\
   strcpy(appo,"Do You Really Want Delete ");	\
   sprintf(&appo[strlen(appo)],"%s ?\n",\
                pathmodel);\
   break;\
   case Q_OVERWRITE_FILEOUTEDI14:\
\
   strcpy(appo,"Proposed File Already Exist. Do You Want Overwrite? ");	\
   break;\
   case Q_OVERWRITE_COPY_MODEL:\
\
   strcpy(appo,"Proposed Model Already Exist or Already Used. Do You Want Overwrite? ");	\
   break;\
   case SAVE_FORAUS:\
   strcpy(appo,"Do You Want Overwrite foraus.for? ");	\
   break;\
   case REMOVE_FORAUS:\
   strcpy(appo,"Do You Want delete selected foraus section? ");	\
   break; \
   case DELETE_FORAUS:\
   strcpy(appo,"Do You Want delete auxiliary fortran file foraus.for? ");	\
   break;\
   default:\
   strcpy(appo,"?? No Message is Set for This Interface ??");\
   break;\
}\
\
UxPutMessageString(rtrn,appo);\
\
XtUnmanageChild(XmMessageBoxGetChild(UxGetWidget(rtrn), XmDIALOG_HELP_BUTTON));\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*question_operation.auxdecl: delete_model(char *path)\
{\
  extern swidget create_vis_msg();\
  extern char path_modello[];\
  extern refresh_lista();\
  char comando[256];\
\
  strcpy(comando,"rm -r ");\
  strcat(comando,path);\
\
if( !strcmp(path,path_modello) )\
{\
   create_vis_msg("It's impossibile delete actual Loaded model \n");\
   return(-1);\
}\
\
  printf("invio il comando %s\n",comando);\
\
  if( (system(comando)) != 0)\
     create_vis_msg("Cannot remove selected Model");\
  else\
     refresh_lista(wchiamante);\
\
}\

*question_operation.name: question_operation
*question_operation.dialogType: "dialog_question"
*question_operation.unitType: "pixels"
*question_operation.x: 300
*question_operation.y: 350
*question_operation.width: 260
*question_operation.height: 140
*question_operation.dialogStyle: "dialog_full_application_modal"
*question_operation.messageAlignment: "alignment_center"
*question_operation.cancelCallback: {\
UxDestroyInterface(UxWidget);\
}
*question_operation.okCallback: {\
extern void overwrite_fileoutedi14();\
\
switch(tip_q)\
	{\
	case Q_DELETE_MODEL:\
\
           delete_model(pathmodel);\
\
	break;\
        case Q_OVERWRITE_FILEOUTEDI14:\
            copy_fileoutedi14();\
        break;\
        case Q_OVERWRITE_COPY_MODEL:\
            system(COPY_MODELLO);\
        break;\
        case SAVE_FORAUS:\
           save_foraus(SAVE_FORAUS);\
           close_interface(wchiamante);\
        break; \
        case REMOVE_FORAUS:\
           rimuovi_moduli_foraus(wchiamante); \
        break;\
        case DELETE_FORAUS:\
            delete_foraus(wchiamante);  \
        break;\
	}\
UxDestroyInterface(UxWidget);\
}

