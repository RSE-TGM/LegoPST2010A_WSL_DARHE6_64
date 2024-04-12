! UIMX ascii 2.5 key: 2525                                                      

*line_width_dialog.class: promptDialog
*line_width_dialog.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo line_width_dialog.i\
   tipo \
   release 5.1\
   data 11/13/95\
   reserved @(#)line_width_dialog.i	5.1\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#include <stdio.h>\

*line_width_dialog.ispecdecl:
*line_width_dialog.funcdecl: swidget create_line_width_dialog(wid_disegno)\
Widget wid_disegno;
*line_width_dialog.funcname: create_line_width_dialog
*line_width_dialog.funcdef: "swidget", "<create_line_width_dialog>(%)"
*line_width_dialog.argdecl: Widget wid_disegno;
*line_width_dialog.arglist: wid_disegno
*line_width_dialog.arglist.wid_disegno: "Widget", "%wid_disegno%"
*line_width_dialog.icode: extern int curr_line_width;\
XmString xms;\
char str_width[10];
*line_width_dialog.fcode: sprintf(str_width,"%d",get_line_width(wid_disegno));\
xms= XmStringCreateSimple(str_width);\
set_something(rtrn, XmNtextString, xms);\
return(rtrn);\

*line_width_dialog.auxdecl:  
*line_width_dialog.static: true
*line_width_dialog.name: line_width_dialog
*line_width_dialog.parent: NO_PARENT
*line_width_dialog.defaultShell: topLevelShell
*line_width_dialog.dialogType: "dialog_prompt"
*line_width_dialog.unitType: "pixels"
*line_width_dialog.x: 720
*line_width_dialog.y: 460
*line_width_dialog.width: 260
*line_width_dialog.height: 160
*line_width_dialog.textString: ""
*line_width_dialog.dialogStyle: "dialog_primary_application_modal"
*line_width_dialog.okCallback: {\
Arg args[3];\
Cardinal lnargs;\
extern char *extract_string();\
int curr_line_width;\
\
XmString xms;\
char str_line_width[10];\
\
lnargs=0;\
XtSetArg(args[lnargs],XmNtextString,&xms);lnargs++;\
XtGetValues(UxWidget,args,lnargs);\
\
strcpy(str_line_width,extract_string(xms));\
\
\
sscanf(str_line_width,"%d",&curr_line_width);\
set_line_width(wid_disegno,curr_line_width);\
\
set_current_gcs(wid_disegno);\
\
 \
}
*line_width_dialog.resizePolicy: "resize_none"
*line_width_dialog.selectionLabelString: "Line width:"
*line_width_dialog.textColumns: 5

