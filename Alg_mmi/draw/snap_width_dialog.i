! UIMX ascii 2.5 key: 764                                                       

*snap_width_dialog.class: promptDialog
*snap_width_dialog.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo snap_width_dialog.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)snap_width_dialog.i	5.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#include <stdio.h>\

*snap_width_dialog.ispecdecl:
*snap_width_dialog.funcdecl: swidget create_snap_width_dialog(widget_disegno)\
Widget widget_disegno;
*snap_width_dialog.funcname: create_snap_width_dialog
*snap_width_dialog.funcdef: "swidget", "<create_snap_width_dialog>(%)"
*snap_width_dialog.argdecl: Widget widget_disegno;
*snap_width_dialog.arglist: widget_disegno
*snap_width_dialog.arglist.widget_disegno: "Widget", "%widget_disegno%"
*snap_width_dialog.icode: XmString xms;\
char str_width[10];
*snap_width_dialog.fcode: sprintf(str_width,"%d",get_step(widget_disegno));\
xms= XmStringCreateSimple(str_width);\
set_something(rtrn, XmNtextString, xms);\
return(rtrn);\

*snap_width_dialog.auxdecl:  
*snap_width_dialog.static: true
*snap_width_dialog.name: snap_width_dialog
*snap_width_dialog.parent: NO_PARENT
*snap_width_dialog.defaultShell: topLevelShell
*snap_width_dialog.dialogType: "dialog_prompt"
*snap_width_dialog.unitType: "pixels"
*snap_width_dialog.x: 720
*snap_width_dialog.y: 460
*snap_width_dialog.width: 260
*snap_width_dialog.height: 160
*snap_width_dialog.textString: ""
*snap_width_dialog.dialogStyle: "dialog_primary_application_modal"
*snap_width_dialog.okCallback: {\
Arg args[3];\
Cardinal lnargs;\
extern char *extract_string();\
int step;\
 \
XmString xms;\
char str_snap_width[10];\
\
lnargs=0;\
XtSetArg(args[lnargs],XmNtextString,&xms);lnargs++;\
XtGetValues(UxWidget,args,lnargs);\
\
strcpy(str_snap_width,extract_string(xms));\
\
sscanf(str_snap_width,"%d",&step);\
DrawSetSnap(widget_disegno,step);\
\
}
*snap_width_dialog.resizePolicy: "resize_none"
*snap_width_dialog.selectionLabelString: "Snap width:"
*snap_width_dialog.textColumns: 5

