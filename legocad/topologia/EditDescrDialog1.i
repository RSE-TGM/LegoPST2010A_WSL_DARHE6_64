! UIMX ascii 2.0 key: 6935                                                      

*EditDescrDialog1.class: promptDialog
*EditDescrDialog1.parent: NO_PARENT
*EditDescrDialog1.defaultShell: topLevelShell
*EditDescrDialog1.static: false
*EditDescrDialog1.gbldecl: #ifndef DESIGN_TIME\
\
/*\
   modulo EditDescrDialog1.i\
   tipo \
   release 2.24\
   data 3/30/95\
   reserved @(#)EditDescrDialog1.i	2.24\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#endif\
#include <stdio.h>\

*EditDescrDialog1.ispecdecl:
*EditDescrDialog1.funcdecl: swidget create_EditDescrDialog1()\

*EditDescrDialog1.funcname: create_EditDescrDialog1
*EditDescrDialog1.funcdef: "swidget", "<create_EditDescrDialog1>(%)"
*EditDescrDialog1.icode: Widget wdescr;\
Arg arg[3];\
Cardinal narg;
*EditDescrDialog1.fcode: /* limito la length della descrizione a 55 char */\
wdescr = XmSelectionBoxGetChild(rtrn,XmDIALOG_TEXT);\
\
narg = 0;\
XtSetArg(arg[narg],XmNcolumns,50);narg++;\
XtSetArg(arg[narg],XmNmaxLength, 50);narg++;\
XtSetValues(wdescr,arg,narg);\
return(rtrn);\

*EditDescrDialog1.auxdecl:
*EditDescrDialog1.name: EditDescrDialog1
*EditDescrDialog1.dialogType: "dialog_prompt"
*EditDescrDialog1.unitType: "pixels"
*EditDescrDialog1.x: 409
*EditDescrDialog1.y: 319
*EditDescrDialog1.width: 440
*EditDescrDialog1.height: 226
*EditDescrDialog1.dialogStyle: "dialog_full_application_modal"
*EditDescrDialog1.dialogTitle: "Edit Description"
*EditDescrDialog1.selectionLabelString: ""
*EditDescrDialog1.textColumns: 50
*EditDescrDialog1.okCallback: {\
extern void set_new_descr(); \
\
char descr[100],bname[10];\
\
strcpy(descr,UxGetTextString(UxWidget));\
strcpy(bname,UxGetText(BlocName));\
tomaius(bname);\
if( strcmp(bname,"") )\
{\
   strncat(bname,"    ",(4-strlen(bname)) );\
   printf("blocco %s descrizione  %s\n",bname,descr);\
   set_new_descr(bname,descr);\
}\
else\
   printf("Operazione Errata -> Nome Blocco nullo %s \n",bname);\
}
*EditDescrDialog1.shadowType: "shadow_in"

*form1.class: form
*form1.parent: EditDescrDialog1
*form1.static: true
*form1.name: form1
*form1.resizePolicy: "resize_none"
*form1.x: 10
*form1.y: 20
*form1.width: 424
*form1.height: 32

*label1.class: label
*label1.parent: form1
*label1.static: true
*label1.name: label1
*label1.x: 0
*label1.y: 0
*label1.width: 90
*label1.height: 30
*label1.labelString: "Nome Blocco"

*BlocName.class: textField
*BlocName.parent: form1
*BlocName.static: false
*BlocName.name: BlocName
*BlocName.x: 160
*BlocName.y: 0
*BlocName.width: 70
*BlocName.height: 30
*BlocName.editable: "true"
*BlocName.highlightColor: "#7E88AB"
*BlocName.columns: 4
*BlocName.maxLength: 4

*ModuleName.class: label
*ModuleName.parent: form1
*ModuleName.static: false
*ModuleName.name: ModuleName
*ModuleName.x: 100
*ModuleName.y: 0
*ModuleName.width: 60
*ModuleName.height: 30
*ModuleName.labelString: "ModField"

