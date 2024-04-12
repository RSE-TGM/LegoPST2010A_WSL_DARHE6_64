! UIMX ascii 2.0 key: 2324                                                      

*EnvironmentDialog.class: bulletinBoardDialog
*EnvironmentDialog.parent: NO_PARENT
*EnvironmentDialog.defaultShell: applicationShell
*EnvironmentDialog.static: true
*EnvironmentDialog.gbldecl: #include <stdio.h>\
#include "legomain.h"
*EnvironmentDialog.ispecdecl:
*EnvironmentDialog.funcdecl: swidget popup_EnvironmentDialog()\

*EnvironmentDialog.funcname: popup_EnvironmentDialog
*EnvironmentDialog.funcdef: "swidget", "<popup_EnvironmentDialog>(%)"
*EnvironmentDialog.icode:
*EnvironmentDialog.fcode: UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*EnvironmentDialog.auxdecl:
*EnvironmentDialog.name: EnvironmentDialog
*EnvironmentDialog.unitType: "pixels"
*EnvironmentDialog.x: 235
*EnvironmentDialog.y: 282
*EnvironmentDialog.width: 531
*EnvironmentDialog.height: 225
*EnvironmentDialog.dialogTitle: "CREATE/MODIFY ENVIRONMENT"
*EnvironmentDialog.defaultButton: "OK_EnvironmentDialog"

*CopyLibutButton.class: toggleButton
*CopyLibutButton.parent: EnvironmentDialog
*CopyLibutButton.static: false
*CopyLibutButton.name: CopyLibutButton
*CopyLibutButton.x: 40
*CopyLibutButton.y: 20
*CopyLibutButton.width: 445
*CopyLibutButton.height: 25
*CopyLibutButton.labelString: "Copy Default Process Modules Libraries"
*CopyLibutButton.alignment: "alignment_beginning"

*CopyLibregButton.class: toggleButton
*CopyLibregButton.parent: EnvironmentDialog
*CopyLibregButton.static: false
*CopyLibregButton.name: CopyLibregButton
*CopyLibregButton.x: 40
*CopyLibregButton.y: 90
*CopyLibregButton.width: 445
*CopyLibregButton.height: 25
*CopyLibregButton.alignment: "alignment_beginning"
*CopyLibregButton.labelString: "Copy Default Control Modules Library"

*CreaLibutButton.class: toggleButton
*CreaLibutButton.parent: EnvironmentDialog
*CreaLibutButton.static: false
*CreaLibutButton.name: CreaLibutButton
*CreaLibutButton.x: 40
*CreaLibutButton.y: 50
*CreaLibutButton.width: 445
*CreaLibutButton.height: 25
*CreaLibutButton.alignment: "alignment_beginning"
*CreaLibutButton.labelString: "Create Process Modules Library"

*CreaLibregButton.class: toggleButton
*CreaLibregButton.parent: EnvironmentDialog
*CreaLibregButton.static: false
*CreaLibregButton.name: CreaLibregButton
*CreaLibregButton.x: 40
*CreaLibregButton.y: 120
*CreaLibregButton.width: 445
*CreaLibregButton.height: 25
*CreaLibregButton.alignment: "alignment_beginning"
*CreaLibregButton.labelString: "Create Control Modules Library"

*separator1.class: separator
*separator1.parent: EnvironmentDialog
*separator1.static: true
*separator1.name: separator1
*separator1.x: 20
*separator1.y: 75
*separator1.width: 500
*separator1.height: 15

*OK_EnvironmentDialog.class: pushButton
*OK_EnvironmentDialog.parent: EnvironmentDialog
*OK_EnvironmentDialog.static: true
*OK_EnvironmentDialog.name: OK_EnvironmentDialog
*OK_EnvironmentDialog.x: 55
*OK_EnvironmentDialog.y: 165
*OK_EnvironmentDialog.width: 105
*OK_EnvironmentDialog.height: 35
*OK_EnvironmentDialog.labelString: "OK"
*OK_EnvironmentDialog.showAsDefault: 1
*OK_EnvironmentDialog.activateCallback: {\
extern swidget create_question_environment();\
int mask=0;\
/*\
 esamina quali richieste sono state fatte dallo\
 utente nella dialog box\
*/\
if(strcmp(UxGetSet(CopyLibutButton),"true")==0)\
	mask=mask|K_COPY_LEGOCAD_LIBUT;\
if(strcmp(UxGetSet(CopyLibregButton),"true")==0)\
	mask=mask|K_COPY_LEGOCAD_LIBREG;\
if(strcmp(UxGetSet(CreaLibutButton),"true")==0)\
	mask=mask|K_CREATE_LEGOCAD_LIBUT;\
if(strcmp(UxGetSet(CreaLibregButton),"true")==0)\
	mask=mask|K_CREATE_LEGOCAD_LIBREG;\
/*\
 distrugge la dialog box\
*/\
UxDestroyInterface(EnvironmentDialog);\
\
/*\
 richiede conferma ed attua la richiesta\
*/\
create_question_environment(mask);\
\
}

*pushButton2.class: pushButton
*pushButton2.parent: EnvironmentDialog
*pushButton2.static: true
*pushButton2.name: pushButton2
*pushButton2.x: 305
*pushButton2.y: 165
*pushButton2.width: 105
*pushButton2.height: 35
*pushButton2.labelString: "Cancel"
*pushButton2.activateCallback: {\
UxDestroyInterface(EnvironmentDialog);\
}

