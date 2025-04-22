! UIMX ascii 2.5 key: 7491                                                      

*ContextSelection1.class: fileSelectionBox
*ContextSelection1.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo ContextSelection1.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)ContextSelection1.i	5.1\
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
#include "config.h"
*ContextSelection1.ispecdecl: int id_ope;
*ContextSelection1.ispeclist: id_ope
*ContextSelection1.ispeclist.id_ope: "int", "%id_ope%"
*ContextSelection1.funcdecl: swidget create_ContextSelection1(int iop)\

*ContextSelection1.funcname: create_ContextSelection1
*ContextSelection1.funcdef: "swidget", "<create_ContextSelection1>(%)"
*ContextSelection1.argdecl: int iop;
*ContextSelection1.arglist: iop
*ContextSelection1.arglist.iop: "int", "%iop%"
*ContextSelection1.icode: id_ope = iop;
*ContextSelection1.fcode: /* queste righe servono ad individuare un path iniziale \
   che corrisponde a quella dell'ultimo context utilizzato\
*/\
\
if( getenv(ENVCTX) != NULL)\
   set_something(ContextSelection1,XmNdirSpec,getenv(ENVCTX));\
if(iop = 3131)\
   set_something(ContextSelection1,XmNdirSpec,getenv(ENVICO));\
\
\
return(rtrn);\

*ContextSelection1.auxdecl: /*------------------------------------------------\
 * GetSelectedContextName\
 * \
 * restituisce il nome del context Selezionato\
 * che puo' essere conpleto di path o meno\
 * che puo' essere di un file esistente oppure no\
 *-----------------------------------------------*/ \
\
Boolean GetSelectedContextName(char *nomeCtxSel)\
{\
   Widget WidName; \
   char *nomeSel,*appo;\
 \
   WidName = XmSelectionBoxGetChild(ContextSelection1,XmDIALOG_TEXT);\
   get_something(WidName,XmNvalue,(char*)&nomeSel);\
\
   if(nomeSel != NULL)\
   {\
      strcpy(nomeCtxSel,nomeSel);\
\
#ifdef VMS\
      if( (appo = strstr(nomeCtxSel,";")) != NULL)\
         *appo = 0;\
#endif      \
      return(True);\
   }\
   else\
      return(False); \
}
*ContextSelection1.name.source: public
*ContextSelection1.static: false
*ContextSelection1.name: ContextSelection1
*ContextSelection1.parent: NO_PARENT
*ContextSelection1.defaultShell: topLevelShell
*ContextSelection1.resizePolicy: "resize_none"
*ContextSelection1.unitType: "pixels"
*ContextSelection1.x: 669
*ContextSelection1.y: 65
*ContextSelection1.width: 304
*ContextSelection1.height: 429
*ContextSelection1.okCallback: {\
/* \
   devo gestire la load di un Context\
   prima verifico se il context esiste\
\
   nella LOAD \
   se esiste if file richiedo di salvare il context attualmente attivo (se c'e')\
   poi faccio la load vera e propria.\
   se non esiste richiedo di salvare il context attualmente attivo (se c'e')\
   e poi richiamo la maschera di definizione (e sara' quindi lei a desidere\
   se effettuare la load o meno).\
\
*/\
\
extern Boolean ContextLoaded;    /* True se c'e' un context caricato */\
extern Boolean ContextModified;  /* True se c'e' un context non salvato */\
extern int ContextLoad();\
extern int display_resources();\
extern PAGEDIT_CONTEXT *pagedit;\
extern void TopMenuSetInsensitive();\
extern void TopMenuSetSensitive();\
extern void richiedi_change_database();\
extern swidget create_messageBoxDialog1();\
extern swidget creat_DefineContext();\
\
\
char ContextName[MAXLENFILENAME];\
Boolean ContextNuovo = False;\
Widget Intf;\
\
if(id_ope == 3131)\
{\
   printf("Operazione non ancora abilitata\n");\
}\
\
if( GetSelectedContextName(ContextName) == False )\
{\
   printf("Nessun Context Selezionato, non facio nulla\n"); \
   return;\
}\
\
if( fopen(ContextName,"r") == NULL)\
   ContextNuovo = True;\
else\
   ContextNuovo = False;\
\
printf("Context Selezionato %s e' nuovo? %d\n",ContextName,ContextNuovo);\
\
\
if(ContextNuovo)\
{\
   if(ContextLoaded && ContextModified)\
   {\
   printf("Vado a definire un nuovo Context salvando il precedente\n ");\
             /* vuoi salvare il Context attivo ? \
               chiama la maschera di save con parametro SAVE_AND_LOAD_NEWCTX \
               la quale poi su Ok salva il vecchio context\
               chiama la maschera per definire il nuovo context\
               ed effettua la load del context e setta la variabile globale\
               ContextLoaded = True;\
             */\
      Intf=create_messageBoxDialog1(SAVE_AND_LOAD_NEWCTX,"Do you want save Context?",ContextName);   \
      UxPopupInterface(Intf,no_grab);\
              \
   }\
   else\
   {\
    printf("Vado a definire un nuovo Context senza salvare il precedente\n ");\
            /* chiama la maschera di definizione del context che poi \
                su Ok effettua la LOAD load del nuovo context  e \
                setta le variabili globali ContextLoaded = True\
                ContextModified = True\
              */\
      UxPopupInterface( creat_DefineContext(ContextName,DEF_CONTEXT), no_grab);\
   }\
}\
else /* load di un vecchio context */\
{\
   if(ContextLoaded && ContextModified)\
   {                \
             /* vuoi salvare il Context attivo ? \
               chiama la maschera di save con parametro SAVE_AND_LOAD_OLDCTX\
               la quale poi su Ok salva il vecchio context\
               ed effettua la load del context e setta la variabile globale\
               ContextLoaded = True;\
             */ \
      Intf=create_messageBoxDialog1(SAVE_AND_LOAD_OLDCTX,"Do you want save previous Context?",ContextName);   \
      UxPopupInterface(Intf,no_grab);\
   }\
   else\
   {\
      /* effettua la load del context e setta la variabile globale\
         ContextLoaded = True;\
      */\
      if(ContextLoad(ContextName,&pagedit) ) \
      {     \
         display_resources(pagedit); \
         TopMenuSetSensitive();\
         richiedi_change_database(); \
         UxDestroyInterface(UxWidget);\
      }\
      else\
      {\
         clear_topLevel(); \
      } \
    } \
   \
}         \
\
\
}
*ContextSelection1.cancelCallback: {\
UxDestroyInterface(UxWidget);\
}
*ContextSelection1.pattern: "*.ctx"

