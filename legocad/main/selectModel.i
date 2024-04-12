! UIMX ascii 2.0 key: 3398                                                      

*SelectModelBox.class: selectionBox
*SelectModelBox.parent: NO_PARENT
*SelectModelBox.defaultShell: topLevelShell
*SelectModelBox.static: true
*SelectModelBox.gbldecl: #include <stdio.h>\
#include <sys/types.h>\
#include <sys/stat.h>\
#include "legomain.h"\
extern int model_filter(char *);\
extern char path_legocad[];
*SelectModelBox.ispecdecl:
*SelectModelBox.funcdecl: swidget SelModelsActivate()\

*SelectModelBox.funcname: SelModelsActivate
*SelectModelBox.funcdef: "swidget", "<SelModelsActivate>(%)"
*SelectModelBox.icode: Widget wid;\
Arg arg[2];\
XmString *modelli;\
char **str_modelli;\
int num,i;\

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
XtSetValues(UxGetWidget(rtrn), arg, 2);\
for(i=0;i<num;i++)\
	{\
	XtFree(modelli[i]);\
	}\
\
wid = XmSelectionBoxGetChild( UxGetWidget(rtrn), XmDIALOG_HELP_BUTTON );\
XtUnmanageChild( wid );\
\
UxPopupInterface(rtrn, no_grab);\
\
return(rtrn);\

*SelectModelBox.auxdecl:
*SelectModelBox.name: SelectModelBox
*SelectModelBox.resizePolicy: "resize_none"
*SelectModelBox.unitType: "pixels"
*SelectModelBox.x: 639
*SelectModelBox.y: 351
*SelectModelBox.width: 216
*SelectModelBox.height: 287
*SelectModelBox.okCallback: {\
extern char path_legocad[];\
extern char path_modello[];\
extern swidget labelNomeModello;\
extern swidget create_vis_msg();\
extern char *estr_nome_modello();\
extern char *str_toupper();\
extern int tipo_modello;\
char app[100];\
char str2[150];\
extern int stato;\
char *nome_modello;\
FILE *fp;\
mode_t modo = (S_IRWXG | S_IRWXO | S_IRUSR | S_IWUSR | S_IXUSR);\
\
strcpy( app, path_legocad );\
strcat( app, "/" );\
strcat( app, UxGetTextString(UxWidget) );\
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
    	\
UxDestroyInterface(UxWidget);\
\
}
*SelectModelBox.cancelCallback: {\
UxDestroyInterface( UxWidget );\
\
}
*SelectModelBox.foreground: "#183958"
*SelectModelBox.background: "#4f9f9f"
*SelectModelBox.highlightColor: "#ad053d"
*SelectModelBox.listLabelString: "Models"
*SelectModelBox.selectionLabelString: "Selected Model"

