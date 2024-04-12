! UIMX ascii 2.5 key: 6328                                                      

*Set_Snap.class: promptDialog
*Set_Snap.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo Set_Snap.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)Set_Snap.i	5.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <Xm/Text.h>\
#include "config.h"\
\
extern swidget topLevelShell;\

*Set_Snap.ispecdecl:
*Set_Snap.funcdecl: swidget create_Set_Snap(PAGINA *pag, Widget parent_wid)\

*Set_Snap.funcname: create_Set_Snap
*Set_Snap.funcdef: "swidget", "<create_Set_Snap>(%)"
*Set_Snap.argdecl: PAGINA *pag;\
Widget parent_wid;
*Set_Snap.arglist: pag, parent_wid
*Set_Snap.arglist.pag: "PAGINA", "*%pag%"
*Set_Snap.arglist.parent_wid: "Widget", "%parent_wid%"
*Set_Snap.icode: Widget wtext;\
Widget whelp;\
char str_snap[100];
*Set_Snap.fcode: wtext=XmSelectionBoxGetChild(rtrn,XmDIALOG_TEXT);\
sprintf(str_snap,"%d",pag->snap_pag);\
XmTextSetString(wtext,str_snap);\
whelp=XmSelectionBoxGetChild(rtrn,XmDIALOG_HELP_BUTTON);\
XtDestroyWidget(whelp);\
return(rtrn);\

*Set_Snap.auxdecl:
*Set_Snap.static: true
*Set_Snap.name: Set_Snap
*Set_Snap.parent: NO_PARENT
*Set_Snap.parentExpression: parent_wid
*Set_Snap.defaultShell: topLevelShell
*Set_Snap.dialogType: "dialog_prompt"
*Set_Snap.unitType: "pixels"
*Set_Snap.x: 551
*Set_Snap.y: 425
*Set_Snap.width: 177
*Set_Snap.height: 140
*Set_Snap.dialogStyle: "dialog_full_application_modal"
*Set_Snap.selectionLabelString: "Snap Value"
*Set_Snap.okCallback: {\
char *str_snap;\
Widget wtext;\
int Snap;\
\
\
wtext=XmSelectionBoxGetChild(UxThisWidget,XmDIALOG_TEXT);\
str_snap=XmTextGetString(wtext);\
sscanf(str_snap,"%d",&Snap);\
DrawSetSnap(pag->drawing,Snap);\
pag->snap_pag= Snap;\
XtFree(str_snap);\
\
XtDestroyWidget(UxWidget);\
\
\
}
*Set_Snap.cancelCallback: {\
UxDestroyInterface(UxWidget);\
\
}
*Set_Snap.minimizeButtons: "false"
*Set_Snap.noResize: "true"

