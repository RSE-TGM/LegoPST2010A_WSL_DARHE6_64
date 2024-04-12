! UIMX ascii 2.0 key: 1685                                                      

*Resampling.class: formDialog
*Resampling.parent: NO_PARENT
*Resampling.defaultShell: topLevelShell
*Resampling.static: false
*Resampling.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo Resampling.i\
   tipo \
   release 1.10\
   data 3/28/95\
   reserved @(#)Resampling.i	1.10\
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
#ifndef DESIGN_TIME\
#include <stdlib.h>\
#endif\
\
extern float t_iniziale;\
extern float t_finale;\
extern float New_delta;\
extern swidget Message;\
extern int numero_campioni;\
\
char *New_Delta_stringa;
*Resampling.ispecdecl:
*Resampling.funcdecl: swidget create_Resampling()\

*Resampling.funcname: create_Resampling
*Resampling.funcdef: "swidget", "<create_Resampling>(%)"
*Resampling.icode:
*Resampling.fcode: return(rtrn);\

*Resampling.auxdecl:
*Resampling.name: Resampling
*Resampling.unitType: "pixels"
*Resampling.x: 410
*Resampling.y: 374
*Resampling.width: 223
*Resampling.height: 136
*Resampling.dialogStyle: "dialog_full_application_modal"

*label7.class: label
*label7.parent: Resampling
*label7.static: true
*label7.name: label7
*label7.x: 5
*label7.y: 5
*label7.width: 215
*label7.height: 45
*label7.labelString: "SAMPLING INTERVAL"
*label7.fontList: "-adobe-new century schoolbook-bold-r-normal--14-140-75-75-p-87-iso8859-1"

*text_New_Delta.class: textField
*text_New_Delta.parent: Resampling
*text_New_Delta.static: true
*text_New_Delta.name: text_New_Delta
*text_New_Delta.x: 50
*text_New_Delta.y: 55
*text_New_Delta.width: 120
*text_New_Delta.height: 30
*text_New_Delta.fontList: "-adobe-new century schoolbook-medium-r-normal--12-120-75-75-p-70-iso8859-1"

*pushButton9.class: pushButton
*pushButton9.parent: Resampling
*pushButton9.static: true
*pushButton9.name: pushButton9
*pushButton9.x: 10
*pushButton9.y: 95
*pushButton9.width: 80
*pushButton9.height: 35
*pushButton9.labelString: "OK"
*pushButton9.activateCallback: {\
char stringa[100];\
XmString Messaggio;\
\
New_Delta_stringa = XmTextFieldGetString (text_New_Delta);\
New_delta = atof (New_Delta_stringa);\
 \
if ((New_delta <= 0) || (New_delta >= numero_campioni/2))\
	{\
	strcpy (stringa, "Input value is not valid\0");\
	Messaggio = XmStringCreate (stringa, XmSTRING_DEFAULT_CHARSET);\
	set_something (Message, XmNdialogType, XmDIALOG_ERROR);\
	set_something (Message, XmNmessageString, Messaggio);\
	UxPopupInterface (Message, no_grab);\
	XmStringFree (Messaggio);\
	}\
else\
	{\
	UxPopdownInterface (Resampling);\
	F22_resampling ();\
	}\
}

*pushButton10.class: pushButton
*pushButton10.parent: Resampling
*pushButton10.static: true
*pushButton10.name: pushButton10
*pushButton10.x: 130
*pushButton10.y: 95
*pushButton10.width: 80
*pushButton10.height: 35
*pushButton10.labelString: "CANCEL"
*pushButton10.activateCallback: {\
UxPopdownInterface (Resampling);\
}

