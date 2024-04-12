! UIMX ascii 2.5 key: 9732                                                      

*SaveSelection.class: promptDialog
*SaveSelection.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo SaveSelection.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)SaveSelection.i	5.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#include <stdio.h>\
\
#ifndef ON_PAGEDIT\
extern char *nome_file_draw;\
#endif
*SaveSelection.ispecdecl: Widget Parent;
*SaveSelection.ispeclist: Parent
*SaveSelection.ispeclist.Parent: "Widget", "%Parent%"
*SaveSelection.funcdecl: swidget create_SaveSelection(Widget Padre)\

*SaveSelection.funcname: create_SaveSelection
*SaveSelection.funcdef: "swidget", "<create_SaveSelection>(%)"
*SaveSelection.argdecl: Widget Padre;
*SaveSelection.arglist: Padre
*SaveSelection.arglist.Padre: "Widget", "%Padre%"
*SaveSelection.icode: char *NomeFile;\
XmString XmTesto;\
\
Parent=Padre;
*SaveSelection.fcode: #ifndef ON_PAGEDIT\
NomeFile = XtNewString (nome_file_draw);\
XmTesto = XmStringCreateSimple (NomeFile);\
set_something (SaveSelection, XmNtextString, XmTesto);\
XtFree (NomeFile);\
#endif\
return(rtrn);\

*SaveSelection.auxdecl:  
*SaveSelection.static: true
*SaveSelection.name: SaveSelection
*SaveSelection.parent: NO_PARENT
*SaveSelection.parentExpression: Parent
*SaveSelection.defaultShell: topLevelShell
*SaveSelection.dialogType: "dialog_prompt"
*SaveSelection.unitType: "pixels"
*SaveSelection.x: 600
*SaveSelection.y: 270
*SaveSelection.width: 200
*SaveSelection.height: 190
*SaveSelection.selectionLabelString: "New File Name:"
*SaveSelection.okCallback: {\
extern swidget create_MessageBox();\
#ifndef ON_PAGEDIT\
extern Widget FinestraDraw;\
extern char *extract_string();\
 \
Arg args[3];\
XmString XmStr;\
char *NomeFile;\
FILE *PuntFile;\
\
XtSetArg(args[0],XmNtextString,&XmStr);\
XtGetValues(UxWidget,args,1);\
\
NomeFile = extract_string (XmStr);\
\
PuntFile = fopen (NomeFile,"r");\
if (PuntFile == NULL)\
  {\
  /*  Il file non esiste e quindi puo' essere salvato  */\
  WriteBackground (FinestraDraw,NomeFile);\
  XtDestroyWidget (XtParent(SaveSelection));\
  }\
else\
  {\
  /* Il file esiste e quindi viene chiesta una conferma  */ \
  UxPopupInterface ( create_MessageBox(XtParent(SaveSelection),NomeFile),no_grab);\
  }\
#endif\
}
*SaveSelection.dialogStyle: "dialog_primary_application_modal"
*SaveSelection.autoUnmanage: "false"
*SaveSelection.cancelCallback: {\
XtDestroyWidget (XtParent(SaveSelection));\
}

