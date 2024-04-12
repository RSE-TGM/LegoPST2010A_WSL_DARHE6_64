! UIMX ascii 2.0 key: 4979                                                      

*Sampling.class: formDialog
*Sampling.parent: NO_PARENT
*Sampling.defaultShell: topLevelShell
*Sampling.static: false
*Sampling.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo Sampling.i\
   tipo \
   release 1.10\
   data 3/28/95\
   reserved @(#)Sampling.i	1.10\
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
extern swidget Message;\
extern int New_Sampl;\
extern int numero_campioni;\
\
char *New_Sampl_stringa;
*Sampling.ispecdecl:
*Sampling.funcdecl: swidget create_Sampling()\

*Sampling.funcname: create_Sampling
*Sampling.funcdef: "swidget", "<create_Sampling>(%)"
*Sampling.icode:
*Sampling.fcode: return(rtrn);\

*Sampling.auxdecl:
*Sampling.name: Sampling
*Sampling.unitType: "pixels"
*Sampling.x: 386
*Sampling.y: 333
*Sampling.width: 223
*Sampling.height: 136
*Sampling.dialogStyle: "dialog_full_application_modal"

*label6.class: label
*label6.parent: Sampling
*label6.static: true
*label6.name: label6
*label6.x: 5
*label6.y: 5
*label6.width: 215
*label6.height: 45
*label6.labelString: "SAMPLING NUMBER"
*label6.fontList: "-adobe-new century schoolbook-bold-r-normal--14-140-75-75-p-87-iso8859-1"

*text_New_Sampl.class: textField
*text_New_Sampl.parent: Sampling
*text_New_Sampl.static: true
*text_New_Sampl.name: text_New_Sampl
*text_New_Sampl.x: 65
*text_New_Sampl.y: 55
*text_New_Sampl.width: 90
*text_New_Sampl.height: 30
*text_New_Sampl.fontList: "-adobe-new century schoolbook-medium-r-normal--12-120-75-75-p-70-iso8859-1"

*arrowButtonGadget1.class: arrowButtonGadget
*arrowButtonGadget1.parent: Sampling
*arrowButtonGadget1.static: true
*arrowButtonGadget1.name: arrowButtonGadget1
*arrowButtonGadget1.x: 155
*arrowButtonGadget1.y: 55
*arrowButtonGadget1.width: 30
*arrowButtonGadget1.height: 30
*arrowButtonGadget1.arrowDirection: "arrow_down"
*arrowButtonGadget1.activateCallback: {\
get_something (text_New_Sampl, XmNvalue, &New_Sampl_stringa);\
New_Sampl = atoi (New_Sampl_stringa);\
if (New_Sampl > 1) \
{\
	New_Sampl--;\
	sprintf (New_Sampl_stringa,"%d",New_Sampl);\
}\
set_something (text_New_Sampl, XmNvalue, New_Sampl_stringa);\
}

*arrowButtonGadget2.class: arrowButtonGadget
*arrowButtonGadget2.parent: Sampling
*arrowButtonGadget2.static: true
*arrowButtonGadget2.name: arrowButtonGadget2
*arrowButtonGadget2.x: 35
*arrowButtonGadget2.y: 55
*arrowButtonGadget2.width: 30
*arrowButtonGadget2.height: 30
*arrowButtonGadget2.activateCallback: {\
get_something (text_New_Sampl, XmNvalue, &New_Sampl_stringa);\
New_Sampl = atoi (New_Sampl_stringa);\
if (New_Sampl < (numero_campioni/4))\
{\
	New_Sampl ++;\
	sprintf (New_Sampl_stringa,"%d",New_Sampl);\
}\
set_something (text_New_Sampl, XmNvalue, New_Sampl_stringa);\
}

*pushButton7.class: pushButton
*pushButton7.parent: Sampling
*pushButton7.static: true
*pushButton7.name: pushButton7
*pushButton7.x: 10
*pushButton7.y: 95
*pushButton7.width: 80
*pushButton7.height: 35
*pushButton7.labelString: "OK"
*pushButton7.activateCallback: {\
char stringa[100];\
XmString Messaggio;\
\
New_Sampl_stringa = XmTextFieldGetString (text_New_Sampl);\
New_Sampl = atoi (New_Sampl_stringa);\
if ((New_Sampl == 0) || (New_Sampl > (numero_campioni/4)) || (New_Sampl <= 0))\
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
	UxPopdownInterface (Sampling);\
	F22_sampling ();\
	}\
}

*pushButton8.class: pushButton
*pushButton8.parent: Sampling
*pushButton8.static: true
*pushButton8.name: pushButton8
*pushButton8.x: 130
*pushButton8.y: 95
*pushButton8.width: 80
*pushButton8.height: 35
*pushButton8.labelString: "CANCEL"
*pushButton8.activateCallback: {\
UxPopdownInterface (Sampling);\
}

