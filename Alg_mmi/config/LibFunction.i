! UIMX ascii 2.5 key: 1335                                                      

*LibFunction.class: topLevelShell
*LibFunction.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo LibFunction.i\
   tipo \
   release 5.2\
   data 3/18/96\
   reserved @(#)LibFunction.i	5.2\
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
\
extern swidget topLevelShell;\
extern PAGEDIT_CONTEXT *pagedit;\
\
int library_wrstd( );\
void library_gen( );\
\

*LibFunction.ispecdecl:
*LibFunction.funcdecl: swidget create_LibFunction(int PaginaSel)\

*LibFunction.funcname: create_LibFunction
*LibFunction.funcdef: "swidget", "<create_LibFunction>(%)"
*LibFunction.argdecl: int PaginaSel;
*LibFunction.arglist: PaginaSel
*LibFunction.arglist.PaginaSel: "int", "%PaginaSel%"
*LibFunction.icode:
*LibFunction.fcode: /* se c'e' una pagina selezionata nella lista setto quella */  \
\
if(PaginaSel)\
{\
   XmTextFieldSetString(FPagName,pagedit->page_list[PaginaSel-1]);\
}  \
return(rtrn);\

*LibFunction.auxdecl: /*-----------------------------------\
 *\
 * scrittura standard icon library \
 *\
 *-----------------------------------*/\
\
int library_wrstd(char *libname)\
{\
   extern PAGEDIT_CONTEXT *pagedit;\
   FILE *fp;\
   Boolean heregen=False,already_exists=False;\
   char libfile[MAXLENFILENAME];\
   extern void WriteTemplateStdLib();\
\
   strcpy(libfile,pagedit->objectLibrary);\
   strcat(libfile,"/");\
   strcat(libfile,libname);   \
   strcat(libfile,LIB_EXT);\
   strcpy(libfile,XlConvPathVms(libfile)); \
\
\
   if( file_exist(libfile) )\
      already_exists = True;\
\
   if( (fp = fopen(libfile,"w")) == NULL)\
   {\
      SetMsg(topLevelShell,NULL,ERRMSG,"ConfigError","Standard Library File Not Available For Write",NULL,False,NULL,False,NULL);\
      fclose(fp);\
      return(SEVERE);    \
   }\
\
   WriteTemplateStdLib(fp);  \
\
   fclose(fp);\
\
   return(already_exists);\
}\
\
/*--------------------------------------------------\
 * \
 * library_gen\
 *\
 * routine di generazione icon library\
 *\
 *---------------------------------------------------*/\
\
void library_gen(char *nmlib,char *label)\
{\
   extern Boolean ContextModified;\
   extern void removefromlist();\
   extern PAGEDIT_CONTEXT *pagedit;\
   char filelib[MAXLENFILENAME];\
   FILE *fp;\
   XmString cstring;\
   int i;\
   if( (XlGetenv(ENVLIB) == NULL) )\
      return;\
   if(nmlib == NULL)\
      return;\
/* costruisco la path file name */\
   strcpy(filelib,getenv(ENVLIB));\
   strcat(filelib,"/");\
   strcat(filelib,nmlib);\
   strcat(filelib,LIB_EXT);\
   strcpy(filelib,XlConvPathVms(filelib));\
\
\
printf("stai cercando di creare la libreria %s\n",filelib);\
/* verifico se e' gia' nel context */\
   for(i=0;i<pagedit->iconlib_num;i++)\
   {\
/* se c'e' deve esserci anche il file */\
      if(!strcmp(pagedit->iconlib_list[i],nmlib))\
      {\
/* se non c'e' il file associato mi inc... */\
         if( !file_exist(filelib) )\
         {\
printf("ed e' nel context ma non esiste, no good thing \n");\
            SetMsg(topLevelShell,NULL,ERRMSG,"ConfigError","Error, File Not Found But Is Into Context Library List",NULL,False,NULL,False,NULL);\
            return;\
         }\
         else\
         {\
/* se c'e' ti dico che cosa la riscrivi a fare */\
printf("ed e' nel context ma gia' esiste, no good thing \n");\
           SetMsg(topLevelShell,NULL,ERRMSG,"ConfigError","Proposed Library Already Exist",NULL,False,NULL,False,NULL);\
           return;\
         }\
      }\
   }\
/* stai creando una libreria che non e' nel context, OK */\
/* devi creare il file della libreria e appicciarlo nel context */\
/* la libreria da creare non deve proprio esistere */\
   if( !file_exist(filelib) )\
   {\
       printf("il file giustamente non esiste\n");\
   }\
   else\
   {\
      SetMsg(topLevelShell,NULL,ERRMSG,"ConfigError","Proposed Library Already Exist",NULL,False,NULL,False,NULL);\
printf("e questo file gia' esiste, no good thing \n");\
      return;\
   }\
/* ti concedo di scrivere la stdlib */\
   if( !strcmp(nmlib,STD_LIB_NAME) )\
      library_wrstd(STD_LIB_NAME);\
   else\
   {\
/* e ti concedo pure di scrivere una libreria (vuota naturalmente */\
      if( (fp = fopen(filelib,"w")) == NULL)\
      {\
         SetMsg(topLevelShell,NULL,ERRMSG,"ConfigError","Sorry, Cannot Write Library",NULL,False,NULL,False,NULL);\
         fclose(fp);\
         return;\
      }\
      fclose(fp);\
   }\
/* aggiorno il context */\
   pagedit->iconlib_num++;\
   pagedit->iconlib_list = realloc(pagedit->iconlib_list,(sizeof(char *)*pagedit->iconlib_num));\
   if( (pagedit->iconlib_list[pagedit->iconlib_num-1] = alloca_memoria(strlen(nmlib)+1,sizeof(char) )) == NULL )\
      return;\
   strcpy(pagedit->iconlib_list[pagedit->iconlib_num-1],nmlib);\
   pagedit->iconlib_label = realloc(pagedit->iconlib_label,(sizeof(char *)*pagedit->iconlib_num ));\
   if( (pagedit->iconlib_label[pagedit->iconlib_num-1] = alloca_memoria(strlen(label)+1,sizeof(char) )) == NULL )\
      return;\
   strcpy(pagedit->iconlib_label[pagedit->iconlib_num-1],label);\
\
/* aggiusto le liste */\
   SetItemString(&cstring,pagedit->iconlib_label[pagedit->iconlib_num-1],"Library","Standard Library",0,NULL);\
   add_library_item(cstring,0);\
\
   if( new_save_context(pagedit) != True )\
   {\
      show_message("Error on save context\n"); \
      ContextModified = True;\
   }\
}
*LibFunction.name.source: public
*LibFunction.static: false
*LibFunction.name: LibFunction
*LibFunction.parent: NO_PARENT
*LibFunction.x: 450
*LibFunction.y: 320
*LibFunction.width: 400
*LibFunction.height: 250

*form6.class: form
*form6.static: true
*form6.name: form6
*form6.parent: LibFunction
*form6.resizePolicy: "resize_none"
*form6.unitType: "pixels"
*form6.x: 10
*form6.y: 20
*form6.width: 230
*form6.height: 150

*pushButton2.class: pushButton
*pushButton2.static: true
*pushButton2.name: pushButton2
*pushButton2.parent: form6
*pushButton2.x: 30
*pushButton2.y: 200
*pushButton2.width: 80
*pushButton2.height: 30
*pushButton2.labelString: "Ok"
*pushButton2.activateCallback: {\
extern Boolean ContextModified;\
char *pname,*lname,*label,comando[300];\
\
 \
pname = XmTextFieldGetString(FPagName);\
lname = XmTextFieldGetString(FLibName);\
label = XmTextFieldGetString(FLabName);\
\
library_gen(lname,label);\
ContextModified = True;\
UxDestroyInterface(LibFunction);\
\
\
}

*pushButton3.class: pushButton
*pushButton3.static: true
*pushButton3.name: pushButton3
*pushButton3.parent: form6
*pushButton3.x: 160
*pushButton3.y: 200
*pushButton3.width: 80
*pushButton3.height: 30
*pushButton3.labelString: "Cancel"
*pushButton3.activateCallback: {\
UxDestroyInterface(LibFunction);\
}

*pushButton4.class: pushButton
*pushButton4.static: true
*pushButton4.name: pushButton4
*pushButton4.parent: form6
*pushButton4.x: 280
*pushButton4.y: 200
*pushButton4.width: 80
*pushButton4.height: 30
*pushButton4.labelString: "Help"

*label1.class: label
*label1.static: true
*label1.name: label1
*label1.parent: form6
*label1.x: 30
*label1.y: 30
*label1.width: 90
*label1.height: 30
*label1.labelString: "Page Name"
*label1.alignment: "alignment_beginning"

*label2.class: label
*label2.static: true
*label2.name: label2
*label2.parent: form6
*label2.x: 30
*label2.y: 80
*label2.width: 91
*label2.height: 30
*label2.labelString: "Library Name"
*label2.alignment: "alignment_beginning"

*label3.class: label
*label3.static: true
*label3.name: label3
*label3.parent: form6
*label3.x: 31
*label3.y: 130
*label3.width: 81
*label3.height: 30
*label3.labelString: "Label Name"
*label3.alignment: "alignment_beginning"

*FPagName.class: textField
*FPagName.static: true
*FPagName.name: FPagName
*FPagName.parent: form6
*FPagName.x: 140
*FPagName.y: 30
*FPagName.width: 181
*FPagName.height: 30
*FPagName.valueChangedCallback: {\
XmTextFieldSetString(FLibName,"");\
XmTextFieldSetString(FLabName,"");\
}

*FLibName.class: textField
*FLibName.static: true
*FLibName.name: FLibName
*FLibName.parent: form6
*FLibName.x: 140
*FLibName.y: 80
*FLibName.width: 181
*FLibName.height: 30
*FLibName.text: "std"

*FLabName.class: textField
*FLabName.static: true
*FLabName.name: FLabName
*FLabName.parent: form6
*FLabName.x: 140
*FLabName.y: 130
*FLabName.width: 181
*FLabName.height: 30
*FLabName.text: "Std"

*separator1.class: separator
*separator1.static: true
*separator1.name: separator1
*separator1.parent: form6
*separator1.x: 0
*separator1.y: 180
*separator1.width: 400
*separator1.height: 10

