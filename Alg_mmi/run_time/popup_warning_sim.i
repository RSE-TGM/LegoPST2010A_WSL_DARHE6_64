! UIMX ascii 2.5 key: 8995                                                      

*popup_warning_sim.class: warningDialog
*popup_warning_sim.gbldecl: #include <stdio.h>\
#include <string.h>\
#include <stdlib.h>\
\
#include <sys/param.h>\
\
#ifdef SCO_UNIX\
#include <Xm/MwmUtil.h>\
#else\
#include <Xm/MwmUtil.h>\
#endif\
\
#include <Xm/List.h>\
#include <time.h> \
#ifndef DESIGN_TIME\
#include <Xl/Xl.h>\
#endif\
\
\
#include <Xl/XlUtilBkg.h>\
#include <Ol/OlDatabasePunti.h>\
\
#ifndef DESIGN_TIME\
#include <Ol/OlPertP.h>\
#else\
#include <Ol/OlPert.h>\
#endif\
#include <Xm/Protocols.h>\
#include "other.h"\
#include "pagresdef.h"\
#include "legommi_icon.bmp"\
\
\
\
extern OlDatabasePuntiObject database_simulatore;\
extern Boolean topologia_on;\
extern char path_sim_correct[FILENAME_MAX];\
extern int shr_usr_key;\
extern CursorErrFree(Widget ,Cursor );\
extern creaOlDbPunti(char *,Widget);
*popup_warning_sim.ispecdecl: Widget topLevel_warning;\
XmFontList FontLabelWarning;\
Cursor cursor_warning;\
Widget Genitore;
*popup_warning_sim.ispeclist: topLevel_warning, FontLabelWarning, cursor_warning, Genitore
*popup_warning_sim.ispeclist.topLevel_warning: "Widget", "%topLevel_warning%"
*popup_warning_sim.ispeclist.FontLabelWarning: "XmFontList", "%FontLabelWarning%"
*popup_warning_sim.ispeclist.cursor_warning: "Cursor", "%cursor_warning%"
*popup_warning_sim.ispeclist.Genitore: "Widget", "%Genitore%"
*popup_warning_sim.funcdecl: swidget create_popup_warning_sim(WarningString,UxParent)\
char *WarningString;\
\
swidget UxParent;
*popup_warning_sim.funcname: create_popup_warning_sim
*popup_warning_sim.funcdef: "swidget", "<create_popup_warning_sim>(%)"
*popup_warning_sim.argdecl: unsigned char *WarningString;\
swidget UxParent;
*popup_warning_sim.arglist: WarningString, UxParent
*popup_warning_sim.arglist.WarningString: "unsigned char", "*%WarningString%"
*popup_warning_sim.arglist.UxParent: "swidget", "%UxParent%"
*popup_warning_sim.icode: Genitore=UxParent;
*popup_warning_sim.fcode: UxPopupInterface(rtrn, no_grab);\
cursor_warning=XlCreateErrCursor(popup_warning_sim);\
XlSetCursor(popup_warning_sim,cursor_warning);\
set_something(popup_warning_sim,XmNmessageString,\
		XmStringCreateLtoR(WarningString, XmSTRING_DEFAULT_CHARSET));\
\
return(rtrn);\

*popup_warning_sim.auxdecl: #ifndef DESIGN_TIME\
Widget popup_Warning_sim(char *Warning_, Widget TopWarning_)\
{\
return(create_popup_warning_sim(Warning_,TopWarning_));\
}\
#endif
*popup_warning_sim.static: true
*popup_warning_sim.name: popup_warning_sim
*popup_warning_sim.msgDialogType: "dialog_warning"
*popup_warning_sim.isCompound: "true"
*popup_warning_sim.compoundIcon: "warningD.xpm"
*popup_warning_sim.compoundName: "warning_Dialog"
*popup_warning_sim.parent: NO_PARENT
*popup_warning_sim.parentExpression: UxParent
*popup_warning_sim.defaultShell: topLevelShell
*popup_warning_sim.unitType: "pixels"
*popup_warning_sim.okCallback: {\
int database_type;\
\
CursorErrFree(popup_warning_sim,cursor_warning);\
PutPagBackground();\
creaOlDbPunti(path_sim_correct,Genitore);\
if(database_simulatore==NULL )\
   {\
    popup_errorDialog("ERROR: Connection with simulator failed",Genitore);\
    }\
}
*popup_warning_sim.helpCallback: {\
\
PutPagBackground();\
}
*popup_warning_sim.cancelCallback: {\
CursorErrFree(popup_warning_sim,cursor_warning);\
PutPagBackground();\
}
*popup_warning_sim.background.source: public
*popup_warning_sim.background: "#7e88ab"
*popup_warning_sim.allowShellResize: "true"
*popup_warning_sim.dialogStyle: "dialog_full_application_modal"
*popup_warning_sim.okLabelString: "Retry"
*popup_warning_sim.dialogTitle: "WARNING DbPunti"

