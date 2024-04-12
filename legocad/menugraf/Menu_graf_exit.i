! UIMX ascii 2.0 key: 2819                                                      

*Menu_graf_exit.class: formDialog
*Menu_graf_exit.parent: NO_PARENT
*Menu_graf_exit.defaultShell: topLevelShell
*Menu_graf_exit.static: false
*Menu_graf_exit.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo Menu_graf_exit.i\
   tipo \
   release 1.10\
   data 3/28/95\
   reserved @(#)Menu_graf_exit.i	1.10\
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
extern char f22source[],f22target[],f22undo[];\
extern int pid;\

*Menu_graf_exit.ispecdecl:
*Menu_graf_exit.funcdecl: swidget create_Menu_graf_exit()\

*Menu_graf_exit.funcname: create_Menu_graf_exit
*Menu_graf_exit.funcdef: "swidget", "<create_Menu_graf_exit>(%)"
*Menu_graf_exit.icode:
*Menu_graf_exit.fcode: return(rtrn);\

*Menu_graf_exit.auxdecl: EseguiRemoveTmp()\
{\
   extern FILE *fpELENCO;\
   extern char *elenco_filetmp; \
   char esegui_shell[200];\
\
   fclose(fpELENCO);\
\
   sprintf(esegui_shell,"chmod a+x %s",elenco_filetmp);\
   system(esegui_shell);   \
\
\
   sprintf(esegui_shell,"csh %s",elenco_filetmp);\
   system(esegui_shell); \
   \
   sprintf(esegui_shell,"rm %s",elenco_filetmp);\
   system(esegui_shell);\
}
*Menu_graf_exit.name: Menu_graf_exit
*Menu_graf_exit.unitType: "pixels"
*Menu_graf_exit.x: 361
*Menu_graf_exit.y: 340
*Menu_graf_exit.width: 288
*Menu_graf_exit.height: 121
*Menu_graf_exit.dialogStyle: "dialog_full_application_modal"

*separator2.class: separator
*separator2.parent: Menu_graf_exit
*separator2.static: true
*separator2.name: separator2
*separator2.x: 5
*separator2.y: 55
*separator2.width: 280
*separator2.height: 15

*label_output.class: label
*label_output.parent: Menu_graf_exit
*label_output.static: false
*label_output.name: label_output
*label_output.x: 5
*label_output.y: 5
*label_output.width: 280
*label_output.height: 45
*label_output.labelString: ""
*label_output.recomputeSize: "false"

*pushButton3.class: pushButton
*pushButton3.parent: Menu_graf_exit
*pushButton3.static: true
*pushButton3.name: pushButton3
*pushButton3.x: 5
*pushButton3.y: 70
*pushButton3.width: 90
*pushButton3.height: 45
*pushButton3.labelString: "OK"
*pushButton3.activateCallback: {\
char cdo[100],strappo[50];\
\
close_22dat ();\
CancellazioneF22();\
EseguiRemoveTmp(); \
if (pid !=0)\
	{\
	sprintf (strappo,"%d",pid);\
	strcpy (cdo,"kill -9 ");\
	strcat (cdo,strappo);\
	system (cdo);\
	}\
exit(0);\
}

*pushButton4.class: pushButton
*pushButton4.parent: Menu_graf_exit
*pushButton4.static: true
*pushButton4.name: pushButton4
*pushButton4.x: 190
*pushButton4.y: 70
*pushButton4.width: 90
*pushButton4.height: 45
*pushButton4.labelString: "CANCEL"
*pushButton4.activateCallback: {\
UxPopdownInterface (Menu_graf_exit);\
}

