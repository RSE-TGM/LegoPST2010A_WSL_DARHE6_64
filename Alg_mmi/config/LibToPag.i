! UIMX ascii 2.5 key: 1124                                                      

*LibToPag.class: selectionBoxDialog
*LibToPag.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo LibToPag.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)LibToPag.i	5.1\
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
#include <Xm/Xm.h>\
#include "config.h"
*LibToPag.ispecdecl:
*LibToPag.funcdecl: swidget create_LibToPag()\

*LibToPag.funcname: create_LibToPag
*LibToPag.funcdef: "swidget", "<create_LibToPag>(%)"
*LibToPag.icode:
*LibToPag.fcode: return(rtrn);\

*LibToPag.auxdecl:
*LibToPag.name.source: public
*LibToPag.static: false
*LibToPag.name: LibToPag
*LibToPag.parent: NO_PARENT
*LibToPag.defaultShell: topLevelShell
*LibToPag.unitType: "pixels"
*LibToPag.x: 570
*LibToPag.y: 220
*LibToPag.width: 340
*LibToPag.height: 250
*LibToPag.listLabelString: "Object Library List"
*LibToPag.mapCallback: {\
\
}
*LibToPag.createCallback: {\
extern PAGEDIT_CONTEXT *pagedit;\
XmString stringItem;\
Widget Lista;\
int i;\
\
Lista = XmSelectionBoxGetChild(UxGetWidget(LibToPag),XmDIALOG_LIST);\
for(i=0;i<pagedit->iconlib_num;i++)\
{\
   stringItem = XmStringCreateSimple(pagedit->iconlib_list[i]);\
   XmListAddItem(Lista,stringItem,0);\
   XmStringFree(stringItem);\
}\
\
}
*LibToPag.okCallback: {\
/*\
   muovo il file con il nome selezionato \
   dalla directory della libreria alla directory\
   delle pagine. Le directory le ricavo dalle \
   variabili di enviroment e le estensioni dei file\
   sono prestabilite (librerie .lib e pagine .pag e .bkg)\
*/  \
\
extern PAGEDIT_CONTEXT *pagedit;\
extern char *extract_string();\
extern void add_item();\
XmString Slib;\
Widget text;\
char pathlib[MAXLENFILENAME],pathpag[MAXLENFILENAME];\
char *lib,comando[200],filelib[MAXLENFILENAME],filepag[MAXLENFILENAME];\
int i,j;\
FILE *fp;\
\
/* recupero la il nome della libreria selezionata */\
 \
text = XmSelectionBoxGetChild(UxGetWidget(LibToPag),XmDIALOG_TEXT);\
get_something(text,XmNvalue,&lib);\
\
/* costriusco i nomi dei file */ \
if( getenv(ENVPAG) == NULL)\
   return;\
if( getenv(ENVLIB) == NULL)\
   return;\
\
strcpy(pathpag,getenv(ENVPAG));\
strcpy(pathlib,getenv(ENVLIB));\
\
printf("Path delle pagine %s\n",pathpag);\
printf("Path delle librerie %s\n",pathlib);\
\
strcpy(filelib,pathlib);\
strcat(filelib,"/");\
strcat(filelib,lib);\
strcat(filelib,LIB_EXT);\
\
strcpy(filepag,pathpag);\
strcat(filepag,"/");\
strcat(filepag,lib);\
strcat(filepag,PAG_EXT);\
\
printf("file libreria da convertire %s\n",filelib);\
printf("file pagina da convertire %s\n",filepag);\
\
/* effettuo la system */\
strcpy(comando,"mv ");\
strcat(comando,filelib);\
strcat(comando," ");\
strcat(comando,filepag);\
\
if(system(NULL) == 0)\
{\
   printf("Unix Shell Command Interpeter Not Accessible\n");\
   return;\
}\
\
system(comando);\
\
\
/* compatto la lista delle librerie */\
for(i=0;i<pagedit->iconlib_num;i++)\
{\
   if(!strcmp(pagedit->iconlib_list[i],lib))\
   {\
      for(j=i;j<(pagedit->iconlib_num-1);j++)\
      {\
         strcpy(pagedit->iconlib_list[j],pagedit->iconlib_list[j+1]);   \
         strcpy(pagedit->iconlib_label[j],pagedit->iconlib_label[j+1]);   \
      }\
   }\
}      \
\
pagedit->iconlib_num--;\
\
\
/* aggiungo la pagina nelle liste interne */\
if(pagedit->pag_num > 0)\
{\
   pagedit->page_list = realloc(pagedit->page_list,sizeof(char *)*(pagedit->pag_num+1));\
\
   if( pagedit->page_list == NULL )\
      return;\
    \
}\
else\
{\
   if( (pagedit->page_list = alloca_memoria(1,sizeof(char *))) == NULL)\
      return;\
}\
\
if( (pagedit->page_list[pagedit->pag_num] = alloca_memoria(strlen(lib)+1,sizeof(char))) == NULL) \
   return;\
\
strcpy(pagedit->page_list[pagedit->pag_num],lib);\
pagedit->pag_num++;\
\
\
/* aggiorno la scrolled list delle pagine */\
\
Slib = XmStringCreateSimple(lib);\
add_item(Slib,0);\
\
}

