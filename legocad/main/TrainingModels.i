! UIMX ascii 2.0 key: 1358                                                      

*TrainingModels.class: mainWindow
*TrainingModels.parent: NO_PARENT
*TrainingModels.defaultShell: topLevelShell
*TrainingModels.static: true
*TrainingModels.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo TrainingModels.i\
   tipo \
   release 1.10\
   data 5/12/95\
   reserved @(#)TrainingModels.i	1.10\
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
#include <linfo.h>\
#include <string.h>\
#include <unistd.h>\
#include "legomain.h"\
\
char path_modello_training[200];\
extern int model_filter(char *);\
\

*TrainingModels.ispecdecl:
*TrainingModels.funcdecl: swidget create_TrainingModels()\

*TrainingModels.funcname: create_TrainingModels
*TrainingModels.funcdef: "swidget", "<create_TrainingModels>(%)"
*TrainingModels.icode: Widget wid;\
Arg arg[2];\
XmString *modelli;\
char **str_modelli;\
int num,i;\
\
strcpy(path_modello_training,getenv("LEGO"));\
strcat(path_modello_training,"/training");
*TrainingModels.fcode: printf("path_modello_training=[%s]\n",path_modello_training);\
\
genera_lista_entry(path_modello_training, model_filter, &num, &str_modelli );\
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
XtSetValues( selectionBox1 , arg, 2);\
for(i=0;i<num;i++)\
	{\
	XtFree(modelli[i]);\
	}\
\
\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);\

*TrainingModels.auxdecl: get_selection(char *selezione)\
{\
  char appo[200];\
\
  strcpy(appo,UxGetTextString( selectionBox1 ));\
  if( strcmp(appo,"") )\
     sprintf(selezione,"%s/%s",path_modello_training,appo);\
  else\
    strcpy(selezione,"");\
\
  printf("selezione=%s",selezione);\
\
}
*TrainingModels.name: TrainingModels
*TrainingModels.unitType: "pixels"
*TrainingModels.x: 540
*TrainingModels.y: 160
*TrainingModels.width: 430
*TrainingModels.height: 420

*selectionBox1.class: selectionBox
*selectionBox1.parent: TrainingModels
*selectionBox1.static: true
*selectionBox1.name: selectionBox1
*selectionBox1.cancelCallback: {\
UxDestroyInterface(XtParent(UxWidget));\
}

*menu2.class: rowColumn
*menu2.parent: TrainingModels
*menu2.static: true
*menu2.name: menu2
*menu2.rowColumnType: "menu_bar"
*menu2.menuAccelerator: "<KeyUp>F10"

*FilePane.class: rowColumn
*FilePane.parent: menu2
*FilePane.static: true
*FilePane.name: FilePane
*FilePane.rowColumnType: "menu_pulldown"

*ViewDescr.class: pushButton
*ViewDescr.parent: FilePane
*ViewDescr.static: true
*ViewDescr.name: ViewDescr
*ViewDescr.labelString: "View description"
*ViewDescr.activateCallback: {\
char selezionato[200],comando[200],appo[200];\
FILE *fp;\
\
get_selection(selezionato);\
printf("selection made %s\n",selezionato);\
 \
if( !strcmp(selezionato,"") )\
{\
   create_vis_msg("Error on training model path");\
   return;\
}\
\
sprintf(appo,"%s/%s",selezionato,FNAME_DESCR);\
if( (fp =fopen(appo,"r")) == NULL)\
{\
   fclose(fp);\
   sprintf(appo,"%s not found",FNAME_DESCR);\
   create_vis_msg(appo);\
   return;\
}\
fclose(fp);\
\
sprintf(comando,"linfo %s 1 0",selezionato); \
system(comando);\
}

*PrintDescr.class: pushButton
*PrintDescr.parent: FilePane
*PrintDescr.static: true
*PrintDescr.name: PrintDescr
*PrintDescr.labelString: "Print Description"
*PrintDescr.activateCallback: {\
extern int print_file();\
char selezionato[200],comando[200],appo[200];\
FILE *fp;\
\
get_selection(selezionato);\
printf("selection made %s\n",selezionato);\
 \
if( !strcmp(selezionato,"") )\
{\
   create_vis_msg("Error on training model path");\
   return;\
}\
\
sprintf(appo,"%s/%s",selezionato,FNAME_DESCR);\
if( (fp =fopen(appo,"r")) == NULL)\
{\
   fclose(fp);\
   sprintf(appo,"%s not found",FNAME_DESCR);\
   create_vis_msg(appo);\
   return;\
}\
fclose(fp);\
\
print_file(FNAME_DESCR);\
\
}

*CopyAll.class: pushButton
*CopyAll.parent: FilePane
*CopyAll.static: true
*CopyAll.name: CopyAll
*CopyAll.labelString: "Copy Training Examples"
*CopyAll.activateCallback: {\
extern int set_var_env();\
char selezionato[200],comando[200],dest[200];\
FILE *fp;\
\
get_selection(selezionato);\
printf("\n\nselection made %s\n",selezionato);\
 \
if( !strcmp(selezionato,"") )\
{\
   create_vis_msg("Error on training model path");\
   return;\
}\
\
sprintf(dest,"%s/legocad/%s",getenv("LEGOCAD_USER"),UxGetTextString(selectionBox1));\
\
printf("source = %s\n,dest = %s\n",selezionato,dest);\
\
set_var_env("DIR_SOURCE_MODEL",selezionato);\
set_var_env("DIR_DEST_MODEL",dest);\
\
if( access(dest,F_OK) != 0)\
{\
   printf("modello non esistente, --- lo creo ---\n");\
   sprintf(comando,"mkdir %s",dest);   \
   system(comando);   \
\
   system(COPY_MODELLO);\
\
}\
else\
{\
   printf("modello esistente\n");\
   printf("Q_OVERWRITE_COPY_MODEL = [%d]\n",Q_OVERWRITE_COPY_MODEL); \
   create_question_operation(selectionBox1, Q_OVERWRITE_COPY_MODEL );\
}  \
\
\
\
}

*menu2_top_b1.class: cascadeButton
*menu2_top_b1.parent: menu2
*menu2_top_b1.static: true
*menu2_top_b1.name: menu2_top_b1
*menu2_top_b1.labelString: "File"
*menu2_top_b1.subMenuId: "FilePane"

