! UIMX ascii 2.5 key: 5283                                                      

*password.class: promptDialog
*password.gbldecl: #include <stdio.h>\
#include "other.h"\
\
int password_ok;\

*password.ispecdecl:
*password.funcdecl: swidget popup_password(Widget PadrePassword)\

*password.funcname: popup_password
*password.funcdef: "swidget", "<popup_password>(%)"
*password.argdecl: Widget PadrePassword;
*password.arglist: PadrePassword
*password.arglist.PadrePassword: "Widget", "%PadrePassword%"
*password.icode: XmFontList FontLabel;\
\
\
#ifndef DESIGN_TIME\
if(!LoadFont(FONT_LABEL,&FontLabel,XtDisplay(PadrePassword)))\
	exit(0);\
#endif\
\
password_ok = 0;
*password.fcode: set_something(XmSelectionBoxGetChild(rtrn,XmDIALOG_CANCEL_BUTTON),XmNfontList,FontLabel);\
set_something(XmSelectionBoxGetChild(rtrn,XmDIALOG_HELP_BUTTON),XmNfontList,FontLabel);\
set_something(XmSelectionBoxGetChild(rtrn,XmDIALOG_OK_BUTTON),XmNfontList,FontLabel);\
set_something(XmSelectionBoxGetChild(rtrn,XmDIALOG_SELECTION_LABEL),XmNfontList,FontLabel);\
set_something(XmSelectionBoxGetChild(rtrn,XmDIALOG_TEXT),XmNfontList,FontLabel);\
#ifndef DESIGN_TIME\
XtVaSetValues(XmSelectionBoxGetChild(rtrn,XmDIALOG_TEXT),\
	RES_CONVERT( XmNbackground, "white" ),\
        RES_CONVERT( XmNforeground, "white" ),NULL);\
#endif\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*password.auxdecl:
*password.static: true
*password.name: password
*password.parent: NO_PARENT
*password.defaultShell: topLevelShell
*password.dialogType: "dialog_prompt"
*password.unitType: "pixels"
*password.x: 170
*password.y: 110
*password.width: 310
*password.height: 200
*password.foreground: "#000000"
*password.background: "#50a050"
*password.dialogStyle: "dialog_full_application_modal"
*password.selectionLabelString: "Insert password"
*password.cancelCallback: {\
password_ok = 0;\
}
*password.helpCallback: {\
password_ok = 0;\
}
*password.okCallback: {\
XmString ret;\
char * pass;\
extern char *extract_string();\
\
/* definizioni per uscita da teleperm \
   in questo caso questa callback effettua la chiusura\
   di mmi ma se siamo in debug (cioe' la risorsa della\
   applicazione decorazioni e' a 1) fa solo la chiusura della\
   pagina. \
*/\
int decorOn=0;\
char *tipo;\
XrmValue value;\
char risorsa[50];\
char appo[50];\
\
extern void quit_proc();\
extern void telep_chiudi_pag();\
\
get_something(password,XmNtextString,&ret);\
pass=extract_string(ret);\
\
/* GESTIONE TELEPERM\
   esco direttamente da mmi senza neanche controllare la pwd\
   mi baso solo sul fatto che il parent e' teleperm.\
   Se sono in debug (decorazioni = 1) chiudo la pagina.\
*/\
if( strcmp(XtName(PadrePassword),"teleperm") == 0)\
{\
   sprintf(risorsa,"teleperm.decorazioni");\
   XrmGetResource(UxDisplay->db,risorsa,(char*)NULL,&tipo,&value);\
   strncpy(appo,value.addr,(int)value.size);\
   decorOn = atoi(appo);\
\
   password_ok = 1;\
  \
   if( decorOn != 0)\
      telep_chiudi_pag(PadrePassword);\
   else \
      quit_proc();\
     \
   return;\
}\
 \
#ifndef DESIGN_TIME\
if(strcmp(pass,PASSWORD)==0)\
	{\
	password_ok = 1;\
	}\
else\
	{\
	popup_errorDialog("Error in password",PadrePassword);\
	password_ok = 0;\
	}\
#endif\
\
}
*password.textColumns: 10

