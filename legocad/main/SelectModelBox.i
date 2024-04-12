! UIMX ascii 2.0 key: 7527                                                      

*SelectModelBox.class: mainWindow
*SelectModelBox.parent: NO_PARENT
*SelectModelBox.defaultShell: topLevelShell
*SelectModelBox.static: true
*SelectModelBox.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo SelectModelBox.i\
   tipo \
   release 1.21\
   data 5/12/95\
   reserved @(#)SelectModelBox.i	1.21\
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
#include <sys/types.h>\
#include <sys/stat.h>\
#include "legomain.h"\
#include "lc_errore.h"\
extern int model_filter(char *);\
extern char path_legocad[];\
Boolean attesa_oknew;\
char *strret;
*SelectModelBox.ispecdecl: Widget WDescr;\

*SelectModelBox.ispeclist: WDescr
*SelectModelBox.ispeclist.WDescr: "Widget", "%WDescr%"
*SelectModelBox.funcdecl: swidget SelModelsActivate(int tipo_op)\

*SelectModelBox.funcname: SelModelsActivate
*SelectModelBox.funcdef: "swidget", "<SelModelsActivate>(%)"
*SelectModelBox.argdecl: int tipo_op;
*SelectModelBox.arglist: tipo_op
*SelectModelBox.arglist.tipo_op: "int", "%tipo_op%"
*SelectModelBox.icode: Widget wid;\
Arg arg[2];\
XmString *modelli;\
char **str_modelli;\
int num,i;\
\
attesa_oknew = False;\
WDescr =  NULL;
*SelectModelBox.fcode: genera_lista_entry(path_legocad, model_filter, &num, &str_modelli );\
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
XtSetValues( SelectModel , arg, 2);\
for(i=0;i<num;i++)\
	{\
	XtFree(modelli[i]);\
	}\
\
if(tipo_op == SELECT_MODEL)\
{\
   XtUnmanageChild( menu1 );\
}\
else if(tipo_op == REORDER_MODEL)\
{\
   set_something( XtParent(SelectModelBox),XmNtitle,"DeleteModelBox");\
   wid = XmSelectionBoxGetChild( SelectModel, XmDIALOG_OK_BUTTON );\
   XtUnmanageChild( wid );\
}\
\
if( proc_legocad_attivi())\
{\
  lc_errore(MODEL_IN_PROGRESS_ERR,"Main");\
  wid = XmSelectionBoxGetChild( SelectModel, XmDIALOG_OK_BUTTON );\
  XtUnmanageChild( wid ); \
}\
\
UxPopupInterface(rtrn, no_grab);\
\
return(rtrn);\

*SelectModelBox.auxdecl: salva_descrizione()\
{\
   extern int save_descr();\
   char path[200];\
\
   sprintf(path,"%s/%s",path_legocad,UxGetTextString(SelectModel));\
   save_descr(path,strret);\
}\
\
refresh_lista(swidget w)\
{\
Arg arg[2];\
XmString *modelli;\
char **str_modelli;\
int num,i;\
Widget lista;\
\
#ifndef DESIGN_TIME\
_UxCSelectModelBox      *UxSaveCtx, *UxContext;\
        UxSaveCtx = UxSelectModelBoxContext;\
        UxSelectModelBoxContext = UxContext =\
                        (_UxCSelectModelBox *) UxGetContext( w );\
#endif\
\
lista = XmFileSelectionBoxGetChild( SelectModel ,XmDIALOG_LIST);\
\
\
XmListDeleteAllItems( lista );\
\
genera_lista_entry(path_legocad, model_filter, &num, &str_modelli );\
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
XtSetValues( SelectModel, arg, 2);\
for(i=0;i<num;i++)\
	{\
	XtFree(modelli[i]);\
	}\
\
#ifndef DESIGN_TIME\
   UxSelectModelBoxContext = UxSaveCtx;\
#endif\
}\
\
char  *get_select_model_new()\
{    \
   return(UxGetTextString( SelectModel ));\
}\
\
modifi()\
{\
}\
\
/*** Boolean predproc(display, event, arg)\
 ***\
 ***    Descrizione:\
 ***       Accetta qualsiasi tipo di evento.\
 ***/\
Boolean predproc(display, event, arg)\
Display *display;\
XEvent *event;\
char *arg;\
{\
    return(True);\
}
*SelectModelBox.name: SelectModelBox
*SelectModelBox.unitType: "pixels"
*SelectModelBox.x: 680
*SelectModelBox.y: 250
*SelectModelBox.width: 330
*SelectModelBox.height: 420

*SelectModel.class: selectionBox
*SelectModel.parent: SelectModelBox
*SelectModel.static: true
*SelectModel.name: SelectModel
*SelectModel.listLabelString: "Models"
*SelectModel.selectionLabelString: "Selected Model"
*SelectModel.cancelCallback: {\
extern int reset_wsel();\
/*::\
if( (WDescr != NULL) )\
{\
   XtDestroyWidget(WDescr);\
   WDescr = NULL;\
}\
::*/\
reset_wsel();\
\
UxDestroyInterface( XtParent(UxWidget) );\
\
}
*SelectModel.okCallback: {\
extern char path_legocad[];\
extern int reset_wsel();\
extern char path_modello[];\
extern swidget labelNomeModello;\
extern swidget create_vis_msg();\
extern char *estr_nome_modello();\
extern char *str_toupper();\
extern int tipo_modello;\
\
\
extern swidget create_editText();\
\
char app[FILENAME_MAX];\
char str2[FILENAME_MAX];\
extern int stato;\
char *nome_modello;\
FILE *fp;\
XEvent evento;\
extern Boolean predproc();\
\
mode_t modo = (S_IRWXG | S_IRWXO | S_IRUSR | S_IWUSR | S_IXUSR);\
\
strcpy( app, path_legocad );\
strcat( app, "/" );\
strcpy(str2,UxGetTextString( SelectModel ) );\
if(strlen(str2)==0)\
	return;\
strcat( app, str2 );\
\
/*  Si posiziona nel direttorio selezionato dall'utente\
*/\
\
if(chdir(app) == -1)\
{\
   printf("Creazione directory nuovo modello\n");\
   if(mkdir(app,modo) == -1)\
   {\
        printf("SORRY CANNOT CREATE NEW MODEL\n");\
        return;\
   } \
   if(chdir(app) == -1) \
   {\
        printf("SORRY CANNOT CREATE NEW MODEL\n");\
        return;\
   }\
/* creo la interfaccia per le introduzione della descrizione */\
\
   WDescr = create_editText(UxWidget,EDIT_DESCR,NULL,&strret,salva_descrizione);\
   attesa_oknew = True; \
}\
\
\
	\
/* Verifica che il path selezionato sia accettabile per essere considerato\
   direttorio utilizzabile per la costruzione del modello\
*/\
\
if(is_path_modello(app))\
{\
   strcpy(path_modello,app);\
   nome_modello=estr_nome_modello(app);\
   str_toupper(nome_modello);\
   switch(tipo_modello)\
	{\
	case TIPO_PROCESSO:\
	sprintf(str2,"Model name: %s (process)",nome_modello);\
	break;\
	case TIPO_REGOLAZIONE:\
	sprintf(str2,"Model name: %s (control)",nome_modello);\
	break;\
	case TIPO_MIX:\
	sprintf(str2,"Model name: %s (mixed)",nome_modello);\
	break;\
	}\
\
	  \
   UxPutLabelString(labelNomeModello,str2);\
\
/* Il modello e' stato scelto: aggiorna lo stato di abilitazione\
   dei bottoni del pulldown menu\
*/\
\
   stato=SCELTO;\
\
/*  update_pulldown();\
*/\
\
   aggiorna_attivi();\
}\
	\
if( attesa_oknew == False)    	\
{\
   reset_wsel();\
   UxDestroyInterface( XtParent(UxWidget) );\
}\
\
\
reset_wsel();\
\
/*\
UxDestroyInterface( XtParent(UxWidget) );\
*/\
}
*SelectModel.helpLabelString: "View"
*SelectModel.helpCallback: {\
extern char path_legocad[];\
extern char path_modello[];\
char app[100];\
char comando[200];\
\
strcpy( app, path_legocad );\
strcat( app, "/" );\
strcat( app, UxGetTextString( SelectModel ) );\
\
/* chiamo adesso info passandogli la path del modello */\
\
strcpy(comando,"linfo ");\
strcat(comando,app);\
strcat(comando," 2 0");\
\
printf("invio il comando %s\n",comando);\
\
system(comando);\
\
}

*menu1.class: rowColumn
*menu1.parent: SelectModelBox
*menu1.static: true
*menu1.name: menu1
*menu1.rowColumnType: "menu_bar"
*menu1.menuAccelerator: "<KeyUp>F10"

*menu1_p3.class: rowColumn
*menu1_p3.parent: menu1
*menu1_p3.static: true
*menu1_p3.name: menu1_p3
*menu1_p3.rowColumnType: "menu_pulldown"

*menu1_p3_b2.class: pushButton
*menu1_p3_b2.parent: menu1_p3
*menu1_p3_b2.static: true
*menu1_p3_b2.name: menu1_p3_b2
*menu1_p3_b2.labelString: "Edit Description"
*menu1_p3_b2.activateCallback: {\
extern char path_legocad[];\
extern char path_modello[];\
extern swidget create_editText();\
extern swidget create_vis_msg();\
char app[100];\
char comando[200];\
char *appo;\
\
char path[200];\
\
sprintf(path,"%s/%s",path_legocad,UxGetTextString(SelectModel));\
printf("path descrizione %s\n",path);\
if( read_descr(path,&appo) == True )\
{\
    create_editText(menu1_p3_b2,EDIT_DESCR,appo,&strret,salva_descrizione );\
}\
else\
   create_vis_msg("Cannot open description file descr.dat!");\
\
#ifdef PIPPO\
\
strcpy( app, path_legocad );\
strcat( app, "/" );\
strcat( app, UxGetTextString( SelectModel ) );\
\
/* chiamo adesso info passandogli la path del modello */\
\
strcpy(comando,"linfo ");\
strcat(comando,app);\
strcat(comando," 1 1");\
\
\
system(comando);\
#endif\
}

*menu1_p3_b3.class: pushButton
*menu1_p3_b3.parent: menu1_p3
*menu1_p3_b3.static: true
*menu1_p3_b3.name: menu1_p3_b3
*menu1_p3_b3.labelString: "Delete Model"
*menu1_p3_b3.activateCallback: {\
extern swidget create_question_operation();\
swidget wid;\
\
wid = create_question_operation(SelectModel,Q_DELETE_MODEL);\
}

*menu1_top_b3.class: cascadeButton
*menu1_top_b3.parent: menu1
*menu1_top_b3.static: true
*menu1_top_b3.name: menu1_top_b3
*menu1_top_b3.labelString: "Edit"
*menu1_top_b3.subMenuId: "menu1_p3"

