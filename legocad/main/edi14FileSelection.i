! UIMX ascii 2.0 key: 4823                                                      

*edi14FileSelection.class: fileSelectionBoxDialog
*edi14FileSelection.parent: NO_PARENT
*edi14FileSelection.defaultShell: topLevelShell
*edi14FileSelection.static: true
*edi14FileSelection.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo edi14FileSelection.i\
   tipo \
   release 1.21\
   data 5/12/95\
   reserved @(#)edi14FileSelection.i	1.21\
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
#ifndef DESIGN_TIME\
#include <stdlib.h>\
#endif\
#include <signal.h>\
#include <string.h>\
#include <sys/types.h>\
#include <unistd.h>\
#include "legomain.h"\
\

*edi14FileSelection.ispecdecl: char input_file[256];  /* file tipo f14.dat di\
                          un altro modello con\
                          cui fare il merge con \
                          quello locale */\
char output_file[256]; /* file di output su cui\
                          copiare il risultato \
                          di edi14c che per default\
                          e' edi14.out */\
char pattern[256];   
*edi14FileSelection.ispeclist: input_file, output_file, pattern
*edi14FileSelection.ispeclist.input_file: "unsigned char", "%input_file%[256]"
*edi14FileSelection.ispeclist.output_file: "unsigned char", "%output_file%[256]"
*edi14FileSelection.ispeclist.pattern: "unsigned char", "%pattern%[256]"
*edi14FileSelection.funcdecl: swidget create_edi14FileSelection(int tipo_oper)\

*edi14FileSelection.funcname: create_edi14FileSelection
*edi14FileSelection.funcdef: "swidget", "<create_edi14FileSelection>(%)"
*edi14FileSelection.argdecl: int tipo_oper;
*edi14FileSelection.arglist: tipo_oper
*edi14FileSelection.arglist.tipo_oper: "int", "%tipo_oper%"
*edi14FileSelection.icode: Widget wid;\
Arg arg[5];\
Cardinal narg;\
XmString cstring;\
char filterstr[256]; 
*edi14FileSelection.fcode: /* unmanage help button */\
wid = XmFileSelectionBoxGetChild(edi14FileSelection,XmDIALOG_HELP_BUTTON);\
XtUnmanageChild( wid );\
\
if( tipo_oper == EDI14_INPUT_SELECTION)\
{\
   /* recupero l'id widget del textfield di Filtro e lo setto come 'f14.*' */\
   wid = XmFileSelectionBoxGetChild(edi14FileSelection,XmDIALOG_FILTER_TEXT);\
\
   strcpy(pattern,XmTextGetString(wid));\
\
\
   strcpy( &(pattern[strlen(pattern)-1]) , "f14.*");\
\
\
/* effettuo la ricerca dei file f14.* */ \
   cstring = XmStringCreateSimple(pattern);   \
   XmFileSelectionDoSearch(edi14FileSelection,cstring);\
\
   printf("setto la stringa di filtro a %s\n",pattern);\
   XmTextSetString(wid,pattern);\
}\
return(rtrn);\

*edi14FileSelection.auxdecl: fine_edi14c()\
{\
   create_vis_msg("edi14c Completed");\
   \
}\

*edi14FileSelection.name: edi14FileSelection
*edi14FileSelection.unitType: "pixels"
*edi14FileSelection.x: 520
*edi14FileSelection.y: 320
*edi14FileSelection.width: 300
*edi14FileSelection.height: 330
*edi14FileSelection.pattern: "*"
*edi14FileSelection.cancelCallback: {\
UxDestroyInterface(UxWidget);\
}
*edi14FileSelection.okCallback: {\
char fileselected[256],comando[256];\
FILE *fp;\
char *nomeappo = {"uscita.tmp"};\
\
strcpy(input_file,UxGetTextString(edi14FileSelection));\
\
printf("passo il parametro di input %s\n",input_file);\
\
/* \
fileselected = strrchr(input_file,'/');\
fileselected += 1;\
*/\
strcpy(fileselected,input_file);\
\
if( *fileselected == 0)\
{\
   create_vis_msg("Invalid Selection");\
   return;\
}\
\
printf("fileselecetd %s\n",fileselected);\
fp = fopen(nomeappo,"w");\
fprintf(fp,"%s\n",fileselected);\
fclose(fp);\
\
strcpy(comando,getenv("LEGO_BIN"));\
strcat(comando,"/edi14c < ");\
strcat(comando,nomeappo);\
strcat( comando," > output_edi14.out"); \
\
system( comando );\
\
fine_edi14c();\
   \
}

