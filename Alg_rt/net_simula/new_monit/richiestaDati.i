! UIMX ascii 2.5 key: 3051                                                      

*richiestaDati.class: promptDialog
*richiestaDati.gbldecl: #include <stdio.h>\
#ifndef DESIGN_TIME\
#include "sim_param.h"\
#include "sim_types.h"\
#include "dispatcher.h"\
\
#include "bistrutt.h"\
#endif
*richiestaDati.ispecdecl: int r;\
int uscita;
*richiestaDati.ispeclist: r, uscita
*richiestaDati.ispeclist.r: "int", "%r%"
*richiestaDati.ispeclist.uscita: "int", "%uscita%"
*richiestaDati.funcdecl: int create_richiestaDati(w,label_string,act,new)\
Widget w;\
char *label_string;\
char *act;\
char *new;\

*richiestaDati.funcname: create_richiestaDati
*richiestaDati.funcdef: "int", "<create_richiestaDati>(%)"
*richiestaDati.argdecl: Widget w;\
unsigned char *label_string;\
unsigned char *act;\
unsigned char *new;
*richiestaDati.arglist: w, label_string, act, new
*richiestaDati.arglist.w: "Widget", "%w%"
*richiestaDati.arglist.label_string: "unsigned char", "*%label_string%"
*richiestaDati.arglist.act: "unsigned char", "*%act%"
*richiestaDati.arglist.new: "unsigned char", "*%new%"
*richiestaDati.icode: r = -1;\
uscita = -1;
*richiestaDati.fcode: XtUnmanageChild (\
    XmSelectionBoxGetChild(UxGetWidget(rtrn),XmDIALOG_HELP_BUTTON));\
UxPopupInterface (rtrn,no_grab);\
r = -1;\
while (r != 1)\
   {\
   XtAppProcessEvent (UxAppContext,XtIMAll);\
   XSync (UxDisplay,0);\
   }\
printf ("chiusura richiesta\n");\
\
return(uscita);\

*richiestaDati.auxdecl:
*richiestaDati.static: true
*richiestaDati.name: richiestaDati
*richiestaDati.parent: NO_PARENT
*richiestaDati.parentExpression: w
*richiestaDati.defaultShell: topLevelShell
*richiestaDati.dialogType: "dialog_prompt"
*richiestaDati.width: 360
*richiestaDati.height: 160
*richiestaDati.isCompound: "true"
*richiestaDati.compoundIcon: "promptD.xpm"
*richiestaDati.compoundName: "prompt_Dialog"
*richiestaDati.x: 880
*richiestaDati.y: 170
*richiestaDati.unitType: "pixels"
*richiestaDati.cancelLabelString: "Quit"
*richiestaDati.createManaged: "false"
*richiestaDati.selectionLabelString: label_string
*richiestaDati.textString: act
*richiestaDati.okCallbackClientData: richiestaDati
*richiestaDati.okCallback: {\
#ifndef DESIGN_TIME\
Widget campo_testo; \
Widget padre; \
char t[MAX_LUN_COMMENTO];\
\
   padre = (Widget)UxClientData;\
   campo_testo = XmSelectionBoxGetChild(padre,XmDIALOG_TEXT);\
\
   if (read_txt(campo_testo,t))\
      {\
      printf ("entry non corretta \n");\
      strcpy (t,act);\
      write_txt (campo_testo,t);\
      r = False;\
      return; \
      }\
\
   strcpy (new,t);\
   DistruggiInterfaccia (XtParent(padre));\
   r = True;\
   uscita = 1;\
#endif\
}
*richiestaDati.autoUnmanage: "false"
*richiestaDati.cancelCallback: {\
#ifndef DESIGN_TIME\
Widget campo_testo; \
Widget padre; \
char t[MAX_LUN_COMMENTO];\
\
   padre = (Widget)UxClientData;\
   campo_testo = XmSelectionBoxGetChild(padre,XmDIALOG_TEXT);\
\
   strcpy (t,act);\
   write_txt (campo_testo,t);\
   strcpy (new,t);\
   DistruggiInterfaccia (XtParent(padre));\
   r = True;\
   uscita = -1;\
   return;\
#endif\
}
*richiestaDati.cancelCallbackClientData: richiestaDati
*richiestaDati.childPlacement: "place_above_selection"

