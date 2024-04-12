! UIMX ascii 2.0 key: 601                                                       

*dati_selectionD.class: dialogShell
*dati_selectionD.parent: NO_PARENT
*dati_selectionD.parentExpression: parent
*dati_selectionD.static: false
*dati_selectionD.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo dati_selDialog.i\
   tipo \
   release 2.15\
   data 4/26/95\
   reserved @(#)dati_selDialog.i	2.15\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
#endif \
\
#include <stdio.h>\
#include <malloc.h>\
#include <string.h>\
#include <f03.h>\
#include <libuimleg.h>\
#include "dati.h"\
Boolean  saving;\
extern Boolean graphics_on;
*dati_selectionD.ispecdecl:
*dati_selectionD.funcdecl: swidget create_dati_selectionD(parent)\
swidget  parent;
*dati_selectionD.funcname: create_dati_selectionD
*dati_selectionD.funcdef: "swidget", "<create_dati_selectionD>(%)"
*dati_selectionD.argdecl: swidget parent;
*dati_selectionD.arglist: parent
*dati_selectionD.arglist.parent: "swidget", "%parent%"
*dati_selectionD.icode:
*dati_selectionD.fcode: XtUnmanageChild(XmFileSelectionBoxGetChild(UxGetWidget(fileSelectionBox), XmDIALOG_HELP_BUTTON));\
return(rtrn);
*dati_selectionD.auxdecl:
*dati_selectionD.name: dati_selectionD
*dati_selectionD.background: "#79cdcd"

*fileSelectionBox.class: fileSelectionBox
*fileSelectionBox.parent: dati_selectionD
*fileSelectionBox.static: false
*fileSelectionBox.name: fileSelectionBox
*fileSelectionBox.dialogStyle: "dialog_primary_application_modal"
*fileSelectionBox.cancelCallback: {\
  UxPopdownInterface(dati_selectionD);\
}
*fileSelectionBox.okCallback: {\
FILE *fp_write;\
int i;\
extern swidget labelModelDati;\
extern Widget topwidget;\
extern swidget listaBlocchi;\
extern swidget create_vis_msg();\
extern char *estr_nome_modello();\
extern char *str_toupper();\
extern int stato;\
char *nome_modello;\
char str[120];\
char str2[120];\
char *path;\
path=str;\
  \
if (saving)\
	{\
	printf("Save file: %s\n", UxGetTextString(fileSelectionBox));\
        path=UxGetTextString(fileSelectionBox);\
	fp_write=fopen(path,"w");\
	if(fp_write)\
		{\
		write_file_f14(fp_write);\
		fclose(fp_write);\
		}\
  	else\
		{\
		sprintf(str2,"Cannot write on file %s",path);\
		create_vis_msg(str2);\
		}\
   	}\
else\
    {\
\
    path=UxGetDirSpec(fileSelectionBox);\
\
    printf("Open file: %s\n",path );\
/*\
  Si posiziona nel direttorio selezionato dall'utente\
*/\
    if(chdir(path))\
	{\
    	sprintf(str2,"Cannot open model %s",path);\
   	create_vis_msg(str2);\
	}\
/*\
  Legge il file f03 da cui ricava tutte le informazioni relative\
  a blocchi e variabili\
*/\
    else if(read_file_f03())\
	{\
 	sprintf(str2,"Cannot open file f03");\
	create_vis_msg(str2);\
	}\
/*\
  Legge il file f14 da cui ricava i valori delle variabili\
*/\
    else if(read_file_f14(neqsis,nu))\
	{\
	sprintf(str2,"Cannot open file f14");\
	create_vis_msg(str2);\
	}\
    else\
	{\
	nome_modello=estr_nome_modello(path);\
	str_toupper(nome_modello);\
	sprintf(str2,"Model name: %s",nome_modello);\
	UxPutLabelString(labelModelDati,str2);\
/*\
 Il modello e' stato scelto: aggiorna lo stato di abilitazione\
 dei bottoni del pulldown menu\
*/\
	stato=SCELTO;\
	update_pulldown();\
/*\
 Costruisce la lista dei blocchi appartenenti al modello\
*/\
	for(i=0;i<nbl;i++)\
		{\
		aggiungi_item_n(listaBlocchi,nom_bloc[i],80);\
		}\
/*\
  aggiorna i valori dei contatori numero eqz. e variabili\
  in main window\
*/\
	update_contatori();\
	\
/*\
 lancia l'applicativo grafico\
*/\
        if(graphics_on)\
	   lancia_macro(topwidget,UxGetWidget(listaBlocchi));	\
	}\
    }\
UxPopdownInterface(dati_selectionD);\
}
*fileSelectionBox.fileTypeMask: "file_directory"
*fileSelectionBox.fileListLabelString: "Directories"
*fileSelectionBox.dirListLabelString: "Path names"

