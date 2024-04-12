! UIMX ascii 2.0 key: 6095                                                      

*form4.class: form
*form4.parent: NO_PARENT
*form4.defaultShell: topLevelShell
*form4.static: true
*form4.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo form4.i\
   tipo \
   release 1.21\
   data 5/12/95\
   reserved @(#)form4.i	1.21\
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
#include <sys/stat.h>\
#include "legomain.h"\
\
extern Boolean attesa_oknew;
*form4.ispecdecl:
*form4.funcdecl: swidget create_form4()\

*form4.funcname: create_form4
*form4.funcdef: "swidget", "<create_form4>(%)"
*form4.icode:
*form4.fcode: return(rtrn);\

*form4.auxdecl: set_editable(Boolean edi)\
{\
   if( edi == True)\
      set_something(scrolledText1,XmNeditable,True);\
   else\
      set_something(scrolledText1,XmNeditable,False);\
}\
\
set_title_label(char *title)\
{\
  UxPutLabelString(label3,title);\
}\
\
/********\
Boolean save_descrizione(char *descr)\
{\
   FILE *fp;\
   if( (fp = fopen(FILEDESCR,"w")) != NULL)\
   {\
      fprintf(fp,"%s\n",descr); \
      printf("salvo la descrizione sul file descr.dat\n");\
      fclose(fp);\
      return(True);\
   }\
   fclose(fp);\
   return(False);\
}\
**********/\
\
Boolean read_descr(char *filename,char **out_text)\
{\
   extern swidget create_vis_msg();\
   FILE *fp;\
   struct stat info_file;\
   char *stringa = NULL;\
   char *ptr2 = NULL;\
\
   if( (fp = fopen (FILEDESCR,"r")) ==  NULL)\
      create_vis_msg("Can't open file DESCR.dat");\
   else\
   {\
 /* Recupera la dimensione del file */\
 /* Lettura del file */\
      if ( !fstat(fileno(fp),&info_file))\
         stringa = (char *) XtMalloc ((unsigned) info_file.st_size+1);\
      else\
         stringa = (char *) XtMalloc (sizeof(char) * 100000);\
\
      ptr2 = stringa;\
      while (fgets(ptr2,140,fp) != NULL)\
         ptr2 = ptr2+strlen(ptr2);\
   }\
   (*out_text) = stringa;\
   fclose(fp);\
}\
\
void set_descr(char *descr)\
{\
   XmTextSetString(scrolledText1,descr);\
}
*form4.name: form4
*form4.resizePolicy: "resize_none"
*form4.unitType: "pixels"
*form4.x: 230
*form4.y: 260
*form4.width: 510
*form4.height: 250

*label3.class: label
*label3.parent: form4
*label3.static: true
*label3.name: label3
*label3.x: 150
*label3.y: 10
*label3.width: 200
*label3.height: 30
*label3.labelString: "Model Description"
*label3.leftAttachment: "attach_form"
*label3.leftOffset: 10
*label3.rightAttachment: "attach_form"
*label3.rightOffset: 10
*label3.topAttachment: "attach_form"
*label3.topOffset: 10

*OkButton.class: pushButton
*OkButton.parent: form4
*OkButton.static: true
*OkButton.name: OkButton
*OkButton.x: 10
*OkButton.y: 260
*OkButton.width: 60
*OkButton.height: 30
*OkButton.labelString: "Ok"
*OkButton.bottomAttachment: "attach_form"
*OkButton.bottomOffset: 10
*OkButton.activateCallback: {\
\
char *descrizione;\
\
descrizione = XmTextGetString(scrolledText1);\
if(descrizione != NULL)\
   if( save_descrizione(descrizione) != True)\
      printf("Save descrizione non andato a buon fine\n");\
\
attesa_oknew = False;\
\
UxDestroyInterface(form4);\
\
\
}

*CancelButton.class: pushButton
*CancelButton.parent: form4
*CancelButton.static: true
*CancelButton.name: CancelButton
*CancelButton.x: 80
*CancelButton.y: 260
*CancelButton.width: 60
*CancelButton.height: 30
*CancelButton.activateCallback: {\
attesa_oknew = False;\
UxDestroyInterface(form4);\
}
*CancelButton.bottomAttachment: "attach_form"
*CancelButton.bottomOffset: 10
*CancelButton.leftAttachment.source: public
*CancelButton.leftAttachment: "attach_none"
*CancelButton.leftOffset: 10
*CancelButton.leftWidget: "OkButton"
*CancelButton.labelString: "Cancel"
*CancelButton.rightAttachment: "attach_form"
*CancelButton.rightOffset: 30

*scrolledWindow1.class: scrolledWindow
*scrolledWindow1.parent: form4
*scrolledWindow1.static: true
*scrolledWindow1.name: scrolledWindow1
*scrolledWindow1.scrollingPolicy: "application_defined"
*scrolledWindow1.x: 10
*scrolledWindow1.y: 50
*scrolledWindow1.visualPolicy: "variable"
*scrolledWindow1.scrollBarDisplayPolicy: "static"
*scrolledWindow1.shadowThickness: 0
*scrolledWindow1.bottomAttachment: "attach_widget"
*scrolledWindow1.bottomOffset: 10
*scrolledWindow1.bottomWidget: "OkButton"
*scrolledWindow1.topAttachment: "attach_widget"
*scrolledWindow1.topWidget: "label3"
*scrolledWindow1.rightAttachment: "attach_form"
*scrolledWindow1.rightOffset: 10
*scrolledWindow1.leftAttachment: "attach_form"
*scrolledWindow1.leftOffset: 10

*scrolledText1.class: scrolledText
*scrolledText1.parent: scrolledWindow1
*scrolledText1.static: true
*scrolledText1.name: scrolledText1
*scrolledText1.width: 490
*scrolledText1.height: 190
*scrolledText1.scrollHorizontal: "false"
*scrolledText1.wordWrap: "true"
*scrolledText1.marginHeight: 5
*scrolledText1.marginWidth: 5
*scrolledText1.maxLength: 500
*scrolledText1.editMode: "multi_line_edit"
*scrolledText1.columns: 70
*scrolledText1.cursorPositionVisible: "true"

