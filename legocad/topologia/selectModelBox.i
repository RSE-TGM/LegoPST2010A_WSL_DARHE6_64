! UIMX ascii 2.0 key: 851                                                       

*selectModelBox.class: selectionBoxDialog
*selectModelBox.parent: NO_PARENT
*selectModelBox.defaultShell: transientShell
*selectModelBox.static: false
*selectModelBox.gbldecl: #ifndef DESIGN_TIME\
\
/*\
   modulo selectModelBox.i\
   tipo \
   release 2.24\
   data 3/30/95\
   reserved @(#)selectModelBox.i	2.24\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#endif\
\
#include <stdio.h>\
#ifndef DESIGN_TIME\
#include <stdlib.h>\
#endif\
#include "errore.h"\
#include "lg1.h"\
#include "question_type.h"\
#include <sys/types.h>\
#include <sys/stat.h>\

*selectModelBox.ispecdecl:
*selectModelBox.funcdecl: swidget create_selectModelBox()
*selectModelBox.funcname: create_selectModelBox
*selectModelBox.funcdef: "swidget", "<create_selectModelBox>(%)"
*selectModelBox.icode: Widget wid;\
\
extern char path_legocad[];\
extern swidget user_pathTF; \
char *path;\
\
path = getenv("LEGOCAD_USER");\
\
if( path == NULL)\
{\
   printf("\nenviroment varable not found LEGOCAD_USER\n");\
   printf("\nset default path /usr/users/legoroot/esempi/utente\n");\
   strcpy(path_legocad,"/usr/users/legoroot/esempi/utente");\
}\
else\
{\
   strcpy(path_legocad,path);\
   strcat(path_legocad,"/legocad");\
}
*selectModelBox.fcode: wid = XmSelectionBoxGetChild( UxGetWidget(rtrn), XmDIALOG_HELP_BUTTON );\
XtUnmanageChild( wid );\
\
return(rtrn);\

*selectModelBox.auxdecl: selModelActivate()\
{\
     extern char      path_legocad[];\
     extern ERR_LEVEL err_level;\
     extern swidget   lg1MainWindow;\
\
     UxPutText( user_pathTF, path_legocad );\
     sel_model_fill(path_legocad);\
     UxPopupInterface(selectModelBox, no_grab);\
/*     set_win_cursors( "busy" );\
*/\
\
}\
\
\
\
\
\
\
sel_model_fill(path)\
char *path;\
{\
\
   Arg      arg[2];\
   XmString *modelli;\
   char     **str_modelli;\
   int      num,i;\
    \
   extern swidget   selectModelBox;\
   extern int       model_filter( char * );\
   extern ERR_LEVEL err_level;\
\
\
\
   genera_lista_entry(path, model_filter, &num, &str_modelli );\
\
   if ( num )\
   {\
     modelli=(XmString *)malloc(num * sizeof(XmString));\
\
     for(i=0;i<num;i++)\
     {\
       modelli[i]=XmStringCreateSimple(str_modelli[i]);\
       free(str_modelli[i]);\
     }\
     free(str_modelli);\
\
     XtSetArg(arg[0], XmNlistItems, modelli);\
     XtSetArg(arg[1], XmNlistItemCount, num);\
     XtSetValues(UxGetWidget(selectModelBox), arg, 2);\
\
     for(i=0;i<num;i++)\
       XtFree(modelli[i]);\
   }\
   else\
   {\
     XtSetArg(arg[0], XmNlistItems, NULL);\
     XtSetArg(arg[1], XmNlistItemCount, 0);\
     XtSetValues(UxGetWidget(selectModelBox), arg, 2);\
   }\
\
\
}\
\
\
\
\

*selectModelBox.name: selectModelBox
*selectModelBox.resizePolicy: "resize_none"
*selectModelBox.unitType: "pixels"
*selectModelBox.x: 483
*selectModelBox.y: 302
*selectModelBox.width: 291
*selectModelBox.height: 426
*selectModelBox.okCallback: {\
extern MODELLO  modello;\
extern swidget user_pathTF;\
extern swidget lg1MainWindow;\
\
extern ERR_LEVEL err_level;\
extern char path_legocad[];\
extern char nome_modello[];\
\
extern QUESTION question;\
extern int      changes_in_F01;\
\
\
char appmod[150];\
char *p_nome, *path;\
char app[300];\
mode_t modo = (S_IRWXG | S_IRWXO | S_IRUSR | S_IWUSR | S_IXUSR);\
\
/**\
reset_win_cursors();\
**/\
\
p_nome = UxGetTextString(UxWidget);\
\
if ( !(*p_nome) )\
{\
   err_level = ERROR;\
   errore("No model selected");\
   UxPopdownInterface(UxWidget);\
   return;\
}\
\
strcpy( nome_modello, p_nome );\
\
\
path = UxGetText( user_pathTF );\
strcpy( path_legocad, path );\
\
if ( changes_in_F01 )\
{\
  question = QST_SALVA_MOD;\
  sprintf( app, "The model %s has been modified\nDo you want to save it?",modello.nome );\
 \
  questionDB_activate( app ); /* salva se risposta a question == OK */\
  \
}\
else\
{\
  strcpy(appmod,path);\
  strcat(appmod,"/");\
  strcat(appmod,nome_modello);\
  \
  printf("Richiesta apertura modello %s\n",appmod);\
/*\
  if(chdir(appmod) == -1)\
  {\
     printf("Cannot open model/n CREATE NEW ONE\n");\
     if(mkdir(appmod,modo) == -1)\
        printf("SORRY CANNOT CREATE NEW MODEL\n");\
     else\
        init_new_modello(nome_modello,path);\
  }  \
  else\
  {\
     init_modello(nome_modello, path);\
  }\
*/\
\
  init_modello(nome_modello, path);\
  set_bl_list();\
  set_model_name();\
}\
\
UxPopdownInterface(UxWidget);\
\
\
}
*selectModelBox.cancelCallback: {\
extern swidget lg1MainWindow;\
\
/**\
reset_win_cursors ();\
**/\
UxPopdownInterface( UxWidget );\
\
}
*selectModelBox.listLabelString: "Models"
*selectModelBox.selectionLabelString: "Selected Model"
*selectModelBox.dialogStyle: "dialog_full_application_modal"
*selectModelBox.applyLabelString: "Filter"
*selectModelBox.dialogTitle: "Model selection"
*selectModelBox.applyCallback: {\
extern char    path_legocad[];\
extern swidget user_pathTF; \
\
char *path;\
\
\
path = UxGetText(user_pathTF);\
sel_model_fill(path);\
}
*selectModelBox.autoUnmanage: "false"
*selectModelBox.textString: ""
*selectModelBox.unmapCallback: {\
\
}

*user_pathRC.class: rowColumn
*user_pathRC.parent: selectModelBox
*user_pathRC.static: true
*user_pathRC.name: user_pathRC
*user_pathRC.x: 24
*user_pathRC.y: 114
*user_pathRC.width: 205
*user_pathRC.height: 40
*user_pathRC.marginWidth: 0
*user_pathRC.spacing: 0

*user_pathLb.class: label
*user_pathLb.parent: user_pathRC
*user_pathLb.static: true
*user_pathLb.name: user_pathLb
*user_pathLb.x: 30
*user_pathLb.y: 3
*user_pathLb.width: 239
*user_pathLb.height: 21
*user_pathLb.labelString: "User path"

*user_pathTF.class: textField
*user_pathTF.parent: user_pathRC
*user_pathTF.static: false
*user_pathTF.name: user_pathTF
*user_pathTF.x: 0
*user_pathTF.y: 24
*user_pathTF.width: 130
*user_pathTF.height: 35

