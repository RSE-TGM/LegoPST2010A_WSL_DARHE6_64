! UIMX ascii 2.0 key: 6563                                                      

*Overwrite.class: formDialog
*Overwrite.parent: NO_PARENT
*Overwrite.defaultShell: topLevelShell
*Overwrite.static: false
*Overwrite.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo Overwrite.i\
   tipo \
   release 1.10\
   data 3/28/95\
   reserved @(#)Overwrite.i	1.10\
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
#include "menu_graf.h"\
\
extern swidget File_Save;\
extern int nome_valido;\
extern int Modifica,Salvato;\
extern int pid;\
extern FILE *fpAPPO,*fpDAT;
*Overwrite.ispecdecl: char *Sorgente,*Destinatario;\
int Fl;
*Overwrite.ispeclist: Sorgente, Destinatario, Fl
*Overwrite.ispeclist.Sorgente: "unsigned char", "*%Sorgente%"
*Overwrite.ispeclist.Destinatario: "unsigned char", "*%Destinatario%"
*Overwrite.ispeclist.Fl: "int", "%Fl%"
*Overwrite.funcdecl: swidget create_Overwrite(int fl,char *Sorg,char *Destin)\

*Overwrite.funcname: create_Overwrite
*Overwrite.funcdef: "swidget", "<create_Overwrite>(%)"
*Overwrite.argdecl: int fl;\
unsigned char *Sorg;\
unsigned char *Destin;
*Overwrite.arglist: fl, Sorg, Destin
*Overwrite.arglist.fl: "int", "%fl%"
*Overwrite.arglist.Sorg: "unsigned char", "*%Sorg%"
*Overwrite.arglist.Destin: "unsigned char", "*%Destin%"
*Overwrite.icode: char stringa[100];\
XmString Messaggio;\
\
Sorgente = XtNewString (Sorg);\
Destinatario = XtNewString (Destin);\
Fl = fl;
*Overwrite.fcode: strcpy (stringa,"File exist; overwrite it?\0");\
Messaggio = XmStringCreate (stringa, XmSTRING_DEFAULT_CHARSET);\
set_something (label_overwrite, XmNlabelString, Messaggio);\
return(rtrn);\

*Overwrite.auxdecl:
*Overwrite.name: Overwrite
*Overwrite.unitType: "pixels"
*Overwrite.x: 711
*Overwrite.y: 743
*Overwrite.width: 288
*Overwrite.height: 121
*Overwrite.dialogStyle: "dialog_full_application_modal"

*separator3.class: separator
*separator3.parent: Overwrite
*separator3.static: true
*separator3.name: separator3
*separator3.x: 5
*separator3.y: 55
*separator3.width: 285
*separator3.height: 15

*label_overwrite.class: label
*label_overwrite.parent: Overwrite
*label_overwrite.static: false
*label_overwrite.name: label_overwrite
*label_overwrite.x: 5
*label_overwrite.y: 5
*label_overwrite.width: 280
*label_overwrite.height: 45
*label_overwrite.labelString: ""
*label_overwrite.recomputeSize: "false"

*pushButton5.class: pushButton
*pushButton5.parent: Overwrite
*pushButton5.static: true
*pushButton5.name: pushButton5
*pushButton5.x: 5
*pushButton5.y: 70
*pushButton5.width: 90
*pushButton5.height: 45
*pushButton5.labelString: "OK"
*pushButton5.activateCallback: {\
extern char *appo;\
\
char cdo[100];\
\
Uccidi_grafics ();\
fclose (fpAPPO);\
fclose (fpDAT);\
strcpy (cdo,"cp ");\
strcat (cdo,Sorgente);\
strcat (cdo," ");\
strcat (cdo,Destinatario);\
system (cdo);\
nome_valido = 1;\
Modifica = 0;\
Salvato = 1;\
if (Fl == ASCII_SAVE) \
	{\
	strcpy (cdo,"rm ");\
	strcat (cdo, Sorgente);\
	system (cdo);\
	}\
UxDestroyInterface (File_Save);\
UxDestroyInterface (Overwrite);\
}

*pushButton6.class: pushButton
*pushButton6.parent: Overwrite
*pushButton6.static: true
*pushButton6.name: pushButton6
*pushButton6.x: 190
*pushButton6.y: 70
*pushButton6.width: 90
*pushButton6.height: 45
*pushButton6.labelString: "CANCEL"
*pushButton6.activateCallback: {\
UxDestroyInterface (Overwrite);\
}

