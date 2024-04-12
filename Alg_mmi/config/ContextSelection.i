! UIMX ascii 2.5 key: 4253                                                      

*ContextSelection.class: fileSelectionBoxDialog
*ContextSelection.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo ContextSelection.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)ContextSelection.i	5.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <stdlib.h>\
#include "config.h"\
#include "message.h"\
extern swidget topLevelShell;\
int Oper; \
Boolean chiudi_simul;
*ContextSelection.ispecdecl:
*ContextSelection.funcdecl: swidget creat_ContextSelection(int idop)\

*ContextSelection.funcname: creat_ContextSelection
*ContextSelection.funcdef: "swidget", "<creat_ContextSelection>(%)"
*ContextSelection.argdecl: int idop;
*ContextSelection.arglist: idop
*ContextSelection.arglist.idop: "int", "%idop%"
*ContextSelection.icode: Oper = idop;\

*ContextSelection.fcode: if( getenv(ENVCTX) != NULL)\
   set_something(ContextSelection,XmNdirSpec,getenv(ENVCTX));\
return(rtrn);\

*ContextSelection.auxdecl:
*ContextSelection.name.source: public
*ContextSelection.static: false
*ContextSelection.name: ContextSelection
*ContextSelection.parent: NO_PARENT
*ContextSelection.parentExpression: topLevelShell
*ContextSelection.defaultShell: topLevelShell
*ContextSelection.unitType: "pixels"
*ContextSelection.x: 210
*ContextSelection.y: 180
*ContextSelection.width: 410
*ContextSelection.height: 380
*ContextSelection.okCallback: {\
extern int pagedit_context_init();\
extern int display_resources();\
extern int pagedit_context_getres();\
extern PAGEDIT_CONTEXT *pagedit; \
extern swidget ListPagine;\
extern swidget LibraryList;\
extern void removefromlist();\
extern swidget creat_DefineContext();\
extern OlDatabaseTopologiaObject dbtopologia;\
extern Boolean CompilerOk;\
extern int gest_conf_op();\
extern FILE *file_exists();\
extern void TopMenuSetSensitive();\
extern void change_database();\
char *nomeCtxSel;\
Widget text;\
swidget swid;\
int i,nitem;\
FILE *fp;\
char filertf[MAXLENFILENAME];\
char varcc[MAXLENFILENAME];\
char varsub[MAXLENFILENAME];\
char varcom[MAXLENFILENAME];\
char varrtf[MAXLENFILENAME];\
\
\
switch(Oper)\
{\
   case LOAD_CONTEXT:\
      TopMenuSetSensitive();\
      text = XmSelectionBoxGetChild(UxWidget,XmDIALOG_TEXT);\
      get_something(text,XmNvalue,&nomeCtxSel);\
\
      printf("Load file Context %s\n",nomeCtxSel);\
\
/* se il file context non esiste prima della load lo creo */\
\
      if(pagedit_context_init(nomeCtxSel,&pagedit) != False)\
      {\
         if( pagedit_context_getres(pagedit) != False )\
	 {\
/* annullo la lista delle pagina e librerie nella topLevelShell (se ce ne sono) */\
            get_something(ListPagine, XmNitemCount, &nitem);\
            if(nitem > 0)\
               XmListDeleteAllItems(ListPagine);    \
            get_something(LibraryList, XmNitemCount, &nitem);\
            if(nitem > 0)\
               XmListDeleteAllItems(LibraryList);\
    \
/* visualizzo nella topLevelShell i dati del nuovo Context */\
            display_resources(pagedit);\
         } \
      } \
      else\
      {\
        UxDestroyInterface(ContextSelection);\
        printf("Errore nella inizializzazione del context\n");\
        return;\
      }\
\
/* annullo la lista delle pagina e librerie nella topLevelShell (se ce ne sono) */\
 /* spostate sopra\
     get_something(ListPagine, XmNitemCount, &nitem);\
      if(nitem > 0)\
         XmListDeleteAllItems(ListPagine);    \
      get_something(LibraryList, XmNitemCount, &nitem);\
      if(nitem > 0)\
         XmListDeleteAllItems(LibraryList);\
*/    \
/* visualizzo nella topLevelShell i dati del nuovo Context */\
/*\
      display_resources(pagedit);\
*/\
\
/* chiedo conferma per effettuare la killsim \
   se la risposta e' negativa non la faccio\
   e non distruggo il database ma non permetto\
   di effettuare le compilazioni della pagina\
   settando il reltivo flag\
*/\
      if( getenv(ENVRTF) != NULL)\
      {\
         if( (strcmp(pagedit->simulator,getenv(ENVRTF))) )\
            gest_conf_op(KILL_SIMULATOR,"Do you want kill previous Simulator?",NULL);\
      }\
      else\
         change_database();\
 \
/* sia che il simulatore sia cambiato oppure no setto le \
   variabili del context relative al Context attuale */\
      setPageditEnv(pagedit);\
      UxDestroyInterface(ContextSelection);\
\
   break;\
   case SAVE_CONTEXT:\
      text = XmSelectionBoxGetChild(UxWidget,XmDIALOG_TEXT);\
      get_something(text,XmNvalue,&nomeCtxSel);\
      printf("Save on  file Context %s\n",nomeCtxSel);\
      strcpy(pagedit->fileContext,nomeCtxSel);\
      new_save_context(pagedit);\
      UxDestroyInterface(ContextSelection);\
   break;\
   case DEF_CONTEXT:\
      text = XmSelectionBoxGetChild(UxWidget,XmDIALOG_TEXT);\
      get_something(text,XmNvalue,&nomeCtxSel);\
      if( (fp = fopen(nomeCtxSel,"r")) == NULL)\
      {\
         printf("Define New Context\n");\
         swid = creat_DefineContext(nomeCtxSel,DEF_CONTEXT);\
         UxPopupInterface(swid,no_grab);\
      } \
      else\
      {\
         printf("Modify Context\n");\
         swid = creat_DefineContext(nomeCtxSel,MOD_CONTEXT);\
         UxPopupInterface(swid,no_grab);\
      }\
   break;\
}\
\
}
*ContextSelection.cancelCallback: {\
UxDestroyInterface(ContextSelection);\
}
*ContextSelection.pattern: "*.ctx"

