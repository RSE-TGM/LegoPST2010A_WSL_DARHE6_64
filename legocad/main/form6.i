! UIMX ascii 2.0 key: 4096                                                      

*CopyModel.class: form
*CopyModel.parent: NO_PARENT
*CopyModel.defaultShell: topLevelShell
*CopyModel.static: true
*CopyModel.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo form6.i\
   tipo \
   release 1.10\
   data 5/12/95\
   reserved @(#)form6.i	1.10\
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
#include <sys/access.h>\
#include "legomain.h"\
extern int model_filter(char *);\

*CopyModel.ispecdecl:
*CopyModel.funcdecl: swidget create_CopyModel()\

*CopyModel.funcname: create_CopyModel
*CopyModel.funcdef: "swidget", "<create_CopyModel>(%)"
*CopyModel.icode: char path_modello_dst[200];\
swidget sw;\
Widget wid;\
Arg arg[2];\
XmString *modelli;\
char **str_modelli;\
int num,i;\
\
\

*CopyModel.fcode: /* unmanage dei bottoni delle file selection box */\
sw = XmFileSelectionBoxGetChild(fileSelectionBox1,XmDIALOG_OK_BUTTON);\
XtUnmanageChild( sw );\
sw = XmFileSelectionBoxGetChild(fileSelectionBox1,XmDIALOG_CANCEL_BUTTON);\
XtUnmanageChild( sw );\
sw = XmFileSelectionBoxGetChild(fileSelectionBox1,XmDIALOG_HELP_BUTTON);\
XtUnmanageChild( sw );\
sw = XmFileSelectionBoxGetChild(fileSelectionBox1,XmDIALOG_SEPARATOR);\
XtUnmanageChild( sw );\
sw = XmFileSelectionBoxGetChild(fileSelectionBox1,XmDIALOG_FILTER_LABEL);\
XtUnmanageChild( sw );\
sw = XmFileSelectionBoxGetChild(fileSelectionBox1,XmDIALOG_FILTER_TEXT);\
XtUnmanageChild( sw );\
/**\
sw = XmFileSelectionBoxGetChild(fileSelectionBox1,XmDIALOG_APPLY_BUTTON);\
XtUnmanageChild( sw );\
**/\
sw = XmFileSelectionBoxGetChild(selectionBox2,XmDIALOG_OK_BUTTON);\
XtUnmanageChild( sw );\
sw = XmFileSelectionBoxGetChild(selectionBox2,XmDIALOG_CANCEL_BUTTON);\
XtUnmanageChild( sw );\
sw = XmFileSelectionBoxGetChild(selectionBox2,XmDIALOG_HELP_BUTTON);\
XtUnmanageChild( sw );\
sw = XmFileSelectionBoxGetChild(selectionBox2,XmDIALOG_SEPARATOR);\
XtUnmanageChild( sw );\
\
strcpy(path_modello_dst,getenv("LEGOCAD_USER"));\
strcat(path_modello_dst,"/legocad");\
printf("path_modello_dst=[%s]\n",path_modello_dst);\
\
genera_lista_entry(path_modello_dst, model_filter, &num, &str_modelli );\
\
modelli=(XmString *)malloc(num * sizeof(XmString));\
for(i=0;i<num;i++)\
	{\
	modelli[i]=XmStringCreateSimple(str_modelli[i]);\
	free(str_modelli[i]);\
	}\
free(str_modelli);\
XtSetArg(arg[0], XmNlistItems, modelli);\
XtSetArg(arg[1], XmNlistItemCount, num);\
XtSetValues( selectionBox2 , arg, 2);\
for(i=0;i<num;i++)\
	{\
	XtFree(modelli[i]);\
	}\
\
\
\
return(rtrn);\

*CopyModel.auxdecl:
*CopyModel.name: CopyModel
*CopyModel.resizePolicy: "resize_none"
*CopyModel.unitType: "pixels"
*CopyModel.x: 350
*CopyModel.y: 319
*CopyModel.width: 700
*CopyModel.height: 440

*label6.class: label
*label6.parent: CopyModel
*label6.static: true
*label6.name: label6
*label6.x: 0
*label6.y: 10
*label6.width: 330
*label6.height: 50
*label6.labelString: "SOURCE MODEL SELECTION"

*label7.class: label
*label7.parent: CopyModel
*label7.static: true
*label7.name: label7
*label7.x: 360
*label7.y: 10
*label7.width: 340
*label7.height: 50
*label7.labelString: "DESTINATION MODEL SELECTION"

*fileSelectionBox1.class: fileSelectionBox
*fileSelectionBox1.parent: CopyModel
*fileSelectionBox1.static: true
*fileSelectionBox1.name: fileSelectionBox1
*fileSelectionBox1.resizePolicy: "resize_none"
*fileSelectionBox1.x: 10
*fileSelectionBox1.y: 70
*fileSelectionBox1.width: 330
*fileSelectionBox1.height: 270
*fileSelectionBox1.fileTypeMask: "file_directory"
*fileSelectionBox1.dirListLabelString: "Base Directory"
*fileSelectionBox1.fileListLabelString: "Models"

*pushButton1.class: pushButton
*pushButton1.parent: CopyModel
*pushButton1.static: true
*pushButton1.name: pushButton1
*pushButton1.x: 50
*pushButton1.y: 390
*pushButton1.width: 230
*pushButton1.height: 30
*pushButton1.labelString: "Ok"
*pushButton1.activateCallback: {\
extern swidget create_question_operation();\
extern swidget create_vis_msg();\
extern char path_modello[];\
extern int set_var_env();\
char source[400],destination[400],filef01[410];\
char mesg[200],modelname[100],appo[200];\
char *cptr,comando[200];\
FILE *fp;\
char *getenv();\
\
/* recupero la selezione effettuata SOURCE */\
strcpy(source, UxGetTextString(fileSelectionBox1) );\
printf("source model directory = [%s]\n",source);\
if( strcmp(source,"") == 0)\
{\
   create_vis_msg("Invalid Selection");\
   return;\
}\
\
/* recupero il nome del modello */\
cptr = strrchr(source,'/');\
cptr++;\
strcpy(modelname,cptr);\
printf("model name = [%s]\n",modelname);\
if( strcmp(modelname,"") == 0 )\
{\
   create_vis_msg("Invalid Selection");\
   return;\
} \
\
/* verifico che esista nella source directory almeno l'f01.dat */ \
\
sprintf(filef01,"%s/%s",source,"f01.dat");\
if( (fp = fopen(filef01,"r")) == NULL)\
{\
   fclose(fp);\
   sprintf(mesg,"%s not found in source model directory [%s]","f01.dat",source);\
   create_vis_msg(mesg);\
   return;\
}\
fclose(fp);\
\
/* recupero la selezione effettuata DEST */\
strcpy(destination,getenv("LEGOCAD_USER"));\
strcat(destination,"/legocad/");\
strcat(destination, UxGetTextString(selectionBox2) );\
\
printf("destination model directory = [%s]\n",destination);\
if( strcmp(destination,"") == 0)\
{\
   create_vis_msg("Invalid Selection");\
   return;\
}\
\
/* non si puo copiare un modello su se stesso */\
if( strcmp(source,destination) == 0 )\
{\
   create_vis_msg("Invalid Selection\nsource and destinationa are the same");\
   return;\
} \
\
/* se la directory destinazione non esiste la creo\
   altrimenti richiedo conferma per la overwrite\
*/\
/*\
set_var_env(source,destination);\
*/\
\
set_var_env("DIR_SOURCE_MODEL",source);\
set_var_env("DIR_DEST_MODEL",destination);\
\
if( access(destination,F_OK) != 0)\
{\
   printf("modello non esistente, --- lo creo ---\n");\
   sprintf(comando,"mkdir %s",destination);   \
   system(comando);   \
\
   system(COPY_MODELLO);\
\
}\
else\
{\
   printf("modello esistente\n");\
   printf("Q_OVERWRITE_COPY_MODEL = [%d]\n",Q_OVERWRITE_COPY_MODEL); \
   create_question_operation( fileSelectionBox1,Q_OVERWRITE_COPY_MODEL );\
}  \
\
\
\
}

*pushButton2.class: pushButton
*pushButton2.parent: CopyModel
*pushButton2.static: true
*pushButton2.name: pushButton2
*pushButton2.x: 390
*pushButton2.y: 390
*pushButton2.width: 230
*pushButton2.height: 30
*pushButton2.labelString: "Cancel"
*pushButton2.activateCallback: {\
UxDestroyInterface(form6);\
}

*selectionBox2.class: selectionBox
*selectionBox2.parent: CopyModel
*selectionBox2.static: true
*selectionBox2.name: selectionBox2
*selectionBox2.resizePolicy: "resize_none"
*selectionBox2.x: 360
*selectionBox2.y: 70
*selectionBox2.width: 330
*selectionBox2.height: 220
*selectionBox2.listLabelString: "Models"

