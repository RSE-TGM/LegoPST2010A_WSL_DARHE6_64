! UIMX ascii 2.0 key: 6990                                                      

*editText.class: form
*editText.parent: NO_PARENT
*editText.defaultShell: topLevelShell
*editText.static: true
*editText.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo editText.i\
   tipo \
   release 1.8\
   data 7/7/95\
   reserved @(#)editText.i	1.8\
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
\
/* interfaccia per gestione scrolled_text\
   descrizione,foraus...etc\
*/\
#include <stdio.h>\
#include "legomain.h"\
\
extern Boolean attesa_oknew;\
\
extern int save_descrizione();\

*editText.ispecdecl: Widget wcaller;\
int id_oper;\
char *text_input; \
char *text_out;
*editText.ispeclist: wcaller, id_oper, text_input, text_out
*editText.ispeclist.wcaller: "Widget", "%wcaller%"
*editText.ispeclist.id_oper: "int", "%id_oper%"
*editText.ispeclist.text_input: "unsigned char", "*%text_input%"
*editText.ispeclist.text_out: "unsigned char", "*%text_out%"
*editText.funcdecl: swidget create_editText(Widget call,int t_ope,char *text,char **outtext,int *(OkCB)() )\

*editText.funcname: create_editText
*editText.funcdef: "swidget", "<create_editText>(%)"
*editText.argdecl: Widget call;\
int t_ope;\
unsigned char *text;\
unsigned char **outtext;\
int *(*OkCB)();
*editText.arglist: call, t_ope, text, outtext, OkCB
*editText.arglist.call: "Widget", "%call%"
*editText.arglist.t_ope: "int", "%t_ope%"
*editText.arglist.text: "unsigned char", "*%text%"
*editText.arglist.outtext: "unsigned char", "**%outtext%"
*editText.arglist.OkCB: "int", "*(*%OkCB%)()"
*editText.icode: wcaller = call;\
id_oper = t_ope;\
text_input = text;\

*editText.fcode: switch(id_oper)\
{\
   case VIEW_DESCR:\
      set_titolo("Model Description View");\
      set_editabile(False);\
   break;\
   case EDIT_DESCR:\
      set_titolo("Model Description Edit");\
      set_editabile(True);\
   break;\
   case EDIT_FORAUS:\
      set_titolo("Model Auxiliary Fortran Edit");\
      set_editabile(True);\
   break;\
   case VIEW_FORAUS:\
      set_titolo("Model Auxiliary Fortran View");\
      set_editabile(False);\
   break;\
}\
\
set_text(text_input);\
\
\
UxPopupInterface(rtrn,no_grab);\
return(rtrn);\

*editText.auxdecl: set_titolo(char *title)\
{\
  UxPutLabelString(label11,title);\
}\
\
set_editabile(Boolean edi)\
{\
   if( edi == True)\
      set_something(scrolledText2,XmNeditable,True);\
   else\
      set_something(scrolledText2,XmNeditable,False);\
}\
\
set_text(char *stringa)\
{\
   XmTextSetString(scrolledText2,stringa);\
}\
\
get_text(char **text_output)\
{\
   char *appo;\
   appo = XmTextGetString(scrolledText2);\
\
     (*text_output) = malloc(strlen(appo)+2);\
     strcpy((*text_output),appo);\
}
*editText.name: editText
*editText.resizePolicy: "resize_none"
*editText.unitType: "pixels"
*editText.x: 220
*editText.y: 350
*editText.width: 680
*editText.height: 430

*label11.class: label
*label11.parent: editText
*label11.static: true
*label11.name: label11
*label11.x: 20
*label11.y: 10
*label11.width: 630
*label11.height: 30
*label11.topAttachment: "attach_form"
*label11.topOffset: 10
*label11.rightAttachment: "attach_form"
*label11.rightOffset: 10
*label11.leftAttachment: "attach_form"
*label11.leftOffset: 10

*pushButton12.class: pushButton
*pushButton12.parent: editText
*pushButton12.static: true
*pushButton12.name: pushButton12
*pushButton12.x: 30
*pushButton12.y: 390
*pushButton12.width: 130
*pushButton12.height: 30
*pushButton12.activateCallback: {\
char *appo;\
\
switch(id_oper)\
{\
   case VIEW_DESCR:\
   case VIEW_FORAUS:\
   break;\
   case EDIT_FORAUS:\
    get_text(&text_out);\
    *outtext = text_out;\
   break;\
   case EDIT_DESCR:\
     get_text(&text_out);\
     *outtext = text_out;\
     if( (OkCB) != NULL)\
        OkCB();\
   break;\
}\
\
attesa_oknew = False;\
\
UxDestroyInterface(XtParent(UxWidget));\
\
}
*pushButton12.labelString: "Ok"
*pushButton12.bottomAttachment: "attach_form"
*pushButton12.bottomOffset: 10

*pushButton13.class: pushButton
*pushButton13.parent: editText
*pushButton13.static: true
*pushButton13.name: pushButton13
*pushButton13.x: 530
*pushButton13.y: 390
*pushButton13.width: 130
*pushButton13.height: 30
*pushButton13.activateCallback: {\
attesa_oknew = False;\
UxDestroyInterface(XtParent(UxWidget));\
}
*pushButton13.labelString: "Cancel"
*pushButton13.bottomAttachment: "attach_form"
*pushButton13.bottomOffset: 10

*scrolledWindow6.class: scrolledWindow
*scrolledWindow6.parent: editText
*scrolledWindow6.static: true
*scrolledWindow6.name: scrolledWindow6
*scrolledWindow6.scrollingPolicy: "application_defined"
*scrolledWindow6.x: 20
*scrolledWindow6.y: 60
*scrolledWindow6.visualPolicy: "variable"
*scrolledWindow6.scrollBarDisplayPolicy: "static"
*scrolledWindow6.shadowThickness: 0
*scrolledWindow6.bottomAttachment: "attach_widget"
*scrolledWindow6.bottomOffset: 20
*scrolledWindow6.bottomWidget: "pushButton12"
*scrolledWindow6.leftAttachment: "attach_form"
*scrolledWindow6.leftOffset: 10
*scrolledWindow6.rightAttachment: "attach_form"
*scrolledWindow6.rightOffset: 10
*scrolledWindow6.topAttachment: "attach_widget"
*scrolledWindow6.topOffset: 10
*scrolledWindow6.topWidget: "label11"

*scrolledText2.class: scrolledText
*scrolledText2.parent: scrolledWindow6
*scrolledText2.static: true
*scrolledText2.name: scrolledText2
*scrolledText2.width: 640
*scrolledText2.height: 300
*scrolledText2.columns: 80
*scrolledText2.editMode: "multi_line_edit"
*scrolledText2.editable: "false"
*scrolledText2.wordWrap: "true"

