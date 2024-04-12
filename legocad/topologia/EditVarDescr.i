! UIMX ascii 2.0 key: 365                                                       

*EditVarDescr.class: promptDialog
*EditVarDescr.parent: NO_PARENT
*EditVarDescr.parentExpression: fintavarWin
*EditVarDescr.defaultShell: topLevelShell
*EditVarDescr.static: false
*EditVarDescr.gbldecl: #ifndef DESIGN_TIME\
\
/*\
   modulo EditVarDescr.i\
   tipo \
   release 2.25\
   data 5/10/95\
   reserved @(#)EditVarDescr.i	2.25\
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
extern swidget fintavarWin;
*EditVarDescr.ispecdecl:
*EditVarDescr.funcdecl: swidget create_EditVarDescr()\

*EditVarDescr.funcname: create_EditVarDescr
*EditVarDescr.funcdef: "swidget", "<create_EditVarDescr>(%)"
*EditVarDescr.icode: Widget wdescr;\
Arg arg[3];\
Cardinal narg;
*EditVarDescr.fcode: /* limito la length della descrizione a 55 char */\
wdescr = XmSelectionBoxGetChild(rtrn,XmDIALOG_TEXT);\
\
narg = 0;\
XtSetArg(arg[narg],XmNcolumns,55);narg++;\
XtSetArg(arg[narg],XmNmaxLength, 55);narg++;\
XtSetValues(wdescr,arg,narg);\
\
return(rtrn);\

*EditVarDescr.auxdecl:
*EditVarDescr.name: EditVarDescr
*EditVarDescr.dialogType: "dialog_prompt"
*EditVarDescr.unitType: "pixels"
*EditVarDescr.x: 470
*EditVarDescr.y: 610
*EditVarDescr.width: 550
*EditVarDescr.height: 150
*EditVarDescr.selectionLabelString: "Descrizione Variabile"
*EditVarDescr.textColumns: 55
*EditVarDescr.okCallback: {\
extern void set_new_var_descr();\
XtPointer *parametri;\
union {\
         short  ind_bloc_piu_var[2];\
         char come_char[4];\
         char *parametri;\
      } param_rec;\
\
char appo[100];\
\
param_rec.parametri = UxGetUserData(UxWidget);\
\
printf("ho ricevuto indice blocco = %d\n",param_rec.ind_bloc_piu_var[0]);\
printf("ho ricevuto indice variab = %d\n",param_rec.ind_bloc_piu_var[1]);\
\
strcpy( appo,UxGetTextString(UxWidget) );\
printf("stringa cambiata %s\n",appo);\
\
set_new_var_descr(XtParent(XtParent(UxWidget)),appo);\
UxDestroyInterface(UxWidget);\
}
*EditVarDescr.dialogStyle: "dialog_full_application_modal"

