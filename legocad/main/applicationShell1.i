! UIMX ascii 2.0 key: 6184                                                      

*applicationShell1.class: applicationShell
*applicationShell1.parent: NO_PARENT
*applicationShell1.static: false
*applicationShell1.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo applicationShell1.i\
   tipo \
   release 2.28\
   data 5/17/95\
   reserved @(#)applicationShell1.i	2.28\
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
#include <string.h>\
#include <sys/types.h>\
#include <unistd.h>\
#include <libutilx.h>\
#ifdef HYPERHELP_USED\
#include "winhelp.h"\
#endif\
#include "legomain.h"\
#include "lc_errore.h"\
ERR_LEVEL err_level;\
char *getcwd();\
char *getenv();\
extern swidget create_dati_selectionD();\
extern swidget create_vis_msg();\
extern swidget create_questionUscitaLegocad();\
extern swidget popup_EnvironmentDialog();\
extern swidget create_question_environment();\
swidget w_selectionD;\
int stato; /* stato di selezione del modello */\
int tipo_modello; /* specifica se modello di solo processo\
		     regolazione o misto regolaz. + processo */\
Bool grafica_on=1; /* indica che si desidera lavorare anche con i diagrammi\
                     simbolici dei modelli */ \
char path_user[FILENAME_MAX]; /* path name che individua l'utente legocad */\
char path_legocad[FILENAME_MAX]; /* path_name che individua la sottodirectory\
                           legocad per l'utente */\
char path_libut[FILENAME_MAX];  /* path_name che individua la libreria dei moduli\
			  di processo */\
char path_libreg[FILENAME_MAX]; /* path_name che individua la libreria dei moduli\
                             di regolazione */\
void chiudi_prog_legocad();\
Bool ok_path_legocad;\
Bool ok_path_libut;\
Bool ok_path_libreg;\
Bool ok_libut;\
Bool ok_libreg;\
char path_modello[FILENAME_MAX]; /* path name del modello */\
char appoggio[FILENAME_MAX];\
\
char *path_icone;  /* PATH directory in cui risiedono le\
                      icone utilizzate da LEGOCAD; il direttorio\
                      e' specificato dalla variabile di ambiente\
                      LEGOCAD_ICO\
                   */\
#ifdef DESIGN_TIME\
char buf_path_icone[FILENAME_MAX];\
#endif\
/*\
 nomi (completi di path) delle icone da caricare per rappresentare\
 i bottoni con le varie fasi del progetto\
*/\
char icon[FILENAME_MAX];\
/*\
  PID relativi alle attivita' per la\
  costruzione del modello: vengono utilizzati\
  per sapere se tali attivita' sono ancora attive\
*/\
pid_t pid_topology,pid_data,pid_steady,pid_transient,pid_librarian;
*applicationShell1.ispecdecl: Widget wsel;
*applicationShell1.ispeclist: wsel
*applicationShell1.ispeclist.wsel: "Widget", "%wsel%"
*applicationShell1.funcdecl: swidget create_applicationShell1()\

*applicationShell1.funcname: create_applicationShell1
*applicationShell1.funcdef: "swidget", "<create_applicationShell1>(%)"
*applicationShell1.icode: wsel = NULL;
*applicationShell1.fcode: XSync(UxDisplay,False);\
\
/*\
 setta le icone associate ai botoni di attivazione\
*/\
set_icone();\
\
\
\
/* \
 Verifica la correttezza dell'ambiente per l'utente\
 il cui direttorio di lavoro e' specificato dalla\
 variabile di environment LEGOCAD_USER\
*/\
testa_ambiente();\
/*\
 Aggiorna le labels della main window sulle quali  \
 sono specificati i path names delle librerie dei\
 moduli utilizzate\
*/\
agg_label_ambiente();\
/*\
 a seconda delle librerie presenti vengono abilitate\
 le voci per la creazione di modelli di processo e/o\
 di regolazione\
*/\
update_pulldown();\
/*\
 aggiorna la attivazione o meno dei bottoni delle\
 utilities utilizzabili\
*/\
aggiorna_utilities();\
/*\
 si posizione nella directory di lavoro per l'utente\
 (specificata dalla variabile di environment LEGOCAD_USER)\
*/\
chdir_path_legocad();\
\
\
return(rtrn);\

*applicationShell1.auxdecl: help_not_available_msg()\
{\
   extern swidget create_vis_msg();\
   char msg[100];\
\
   sprintf(msg,"help not available for %s\n",getenv("OS") );\
   create_vis_msg(msg);\
}\
\
reset_wsel()\
{\
   wsel = NULL;\
}  \
\
/* update_pulldown()\
   a seconda della situazione dell'ambiente LEGOCAD\
   aggiorna l'attivazione delle voci del pulldown menu.\
*/\
update_pulldown()\
{\
/*\
 la libreria moduli processo esiste: posso costruire modelli\
 di processo\
*/\
if(ok_libut)\
	UxPutSensitive(ProcessoButton,"true");\
else\
	UxPutSensitive(ProcessoButton,"false");\
/*\
 la libreria moduli regolazione esiste: posso costruire modelli\
 di regolazione\
*/\
if(ok_libreg)\
{\
	UxPutSensitive(ControlloButton,"true"); \
	UxPutSensitive(MixedButton,"true"); \
}\
else\
{\
	UxPutSensitive(ControlloButton,"false");\
	UxPutSensitive(MixedButton,"false");\
}\
\
UxPutSensitive(Edi14_run,"false");\
UxPutSensitive(Edi14_save,"false");\
UxPutSensitive(Edi14_viewout,"false");\
}\
	\
\
/* aggiorna_attivi()\
   in base allo stato di avanzamento di creazione del modello lego\
   rende attivi o disattivi i bottoni relativi alle diverse fasi di\
   sviluppo.\
*/\
aggiorna_attivi()\
{\
#ifndef DESIGN_TIME\
char app[100];\
/*\
 testa se e' attivabile il calcolo del transitorio\
*/\
if(test_transient()==0)\
	{\
                UxPutSensitive(Edi14_run,"true");\
                UxPutSensitive(Edi14_save,"true");\
                UxPutSensitive(Edi14_viewout,"true");\
\
		UxPutSensitive(Transitorio_pb5,"true");\
		UxPutSensitive(Transitorio_pb6,"true");\
		UxPutBackground(Transitorio_rc,"LightBlue");\
		UxPutBackground(Transitorio_pb6,"LightBlue");\
\
		UxPutSensitive(Stazionario_pb5,"true");\
		UxPutSensitive(Stazionario_pb6,"true");\
		UxPutBackground(Stazionario_rc, "LightBlue");\
		UxPutBackground(Stazionario_pb6, "LightBlue");\
\
		UxPutSensitive(Dati_pb5,"true");\
		UxPutSensitive(Dati_pb6,"true");\
		UxPutBackground(Dati_rc,"LightBlue");\
		UxPutBackground(Dati_pb6,"LightBlue");\
\
		UxPutSensitive(Topologia_pb5,"true");\
		UxPutSensitive(Topologia_pb6,"true");\
		UxPutBackground(Topologia_rc,"LightBlue");\
		UxPutBackground(Topologia_pb6,"LightBlue");\
		\
	}\
else if (test_steady()==0)\
	{\
                UxPutSensitive(Edi14_run,"true");\
                UxPutSensitive(Edi14_save,"true");\
                UxPutSensitive(Edi14_viewout,"true");\
\
		UxPutSensitive(Transitorio_pb5,"false");\
		UxPutSensitive(Transitorio_pb6,"false");\
		UxPutBackground(Transitorio_rc,"SteelBlue");\
		UxPutBackground(Transitorio_pb6,"SteelBlue");\
		\
\
		UxPutSensitive(Stazionario_pb5,"true");\
		UxPutSensitive(Stazionario_pb6,"true");\
		UxPutBackground(Stazionario_rc,"LightBlue");\
		UxPutBackground(Stazionario_pb6,"LightBlue");\
\
		UxPutSensitive(Dati_pb5,"true");\
		UxPutSensitive(Dati_pb6,"true");\
		UxPutBackground(Dati_rc,"LightBlue");\
		UxPutBackground(Dati_pb6,"LightBlue");\
\
		UxPutSensitive(Topologia_pb5,"true");\
		UxPutSensitive(Topologia_pb6,"true");\
		UxPutBackground(Topologia_rc,"LightBlue");\
		UxPutBackground(Topologia_pb6,"LightBlue");\
	}\
/*\
 Testa la possibilta' di eseguire l'attivita' dati\
*/\
else if (test_data_editor()==0) \
	{\
                UxPutSensitive(Edi14_run,"true");\
                UxPutSensitive(Edi14_save,"true");\
                UxPutSensitive(Edi14_viewout,"true");\
\
		UxPutSensitive(Transitorio_pb5,"false");\
		UxPutSensitive(Transitorio_pb6,"false");\
		UxPutBackground(Transitorio_rc,"SteelBlue");\
		UxPutBackground(Transitorio_pb6,"SteelBlue");\
		\
\
		UxPutSensitive(Stazionario_pb5,"false");\
		UxPutSensitive(Stazionario_pb6,"false");\
		UxPutBackground(Stazionario_rc,"SteelBlue");\
		UxPutBackground(Stazionario_pb6,"SteelBlue");\
\
		UxPutSensitive(Dati_pb5,"true");\
		UxPutSensitive(Dati_pb6,"true");\
		UxPutBackground(Dati_rc,"LightBlue");\
		UxPutBackground(Dati_pb6,"LightBlue");\
\
		UxPutSensitive(Topologia_pb5,"true");\
		UxPutSensitive(Topologia_pb6,"true");\
		UxPutBackground(Topologia_rc,"LightBlue");\
		UxPutBackground(Topologia_pb6,"LightBlue");\
	}\
else if (test_topologia()==0)\
        {\
                UxPutSensitive(Edi14_run,"false");\
                UxPutSensitive(Edi14_save,"false");\
                UxPutSensitive(Edi14_viewout,"false");\
\
                UxPutSensitive(Transitorio_pb5,"false");\
                UxPutSensitive(Transitorio_pb6,"false");\
                UxPutBackground(Transitorio_rc,"SteelBlue");\
                UxPutBackground(Transitorio_pb6,"SteelBlue");\
\
\
                UxPutSensitive(Stazionario_pb5,"false");\
                UxPutSensitive(Stazionario_pb6,"false");\
                UxPutBackground(Stazionario_rc,"SteelBlue");\
                UxPutBackground(Stazionario_pb6,"SteelBlue");\
\
\
                UxPutSensitive(Dati_pb5,"false");\
                UxPutSensitive(Dati_pb6,"false");\
                UxPutBackground(Dati_rc,"SteelBlue");\
                UxPutBackground(Dati_pb6,"SteelBlue");\
\
\
                UxPutSensitive(Topologia_pb5,"true");\
                UxPutSensitive(Topologia_pb6,"true");\
                UxPutBackground(Topologia_rc,"LightBlue");\
                UxPutBackground(Topologia_pb6,"LightBlue");\
\
        }\
else \
	{\
                UxPutSensitive(Edi14_run,"false");\
                UxPutSensitive(Edi14_save,"false");\
                UxPutSensitive(Edi14_viewout,"false");\
\
		UxPutSensitive(Transitorio_pb5,"false");\
		UxPutSensitive(Transitorio_pb6,"false");\
		UxPutBackground(Transitorio_rc,"SteelBlue");\
		UxPutBackground(Transitorio_pb6,"SteelBlue");\
		\
\
		UxPutSensitive(Stazionario_pb5,"false");\
		UxPutSensitive(Stazionario_pb6,"false");\
		UxPutBackground(Stazionario_rc,"SteelBlue");\
		UxPutBackground(Stazionario_pb6,"SteelBlue");\
		\
\
		UxPutSensitive(Dati_pb5,"false");\
		UxPutSensitive(Dati_pb6,"false");\
		UxPutBackground(Dati_rc,"SteelBlue");\
		UxPutBackground(Dati_pb6,"SteelBlue");\
		\
\
		UxPutSensitive(Topologia_pb5,"false");\
		UxPutSensitive(Topologia_pb6,"false");\
		UxPutBackground(Topologia_rc,"SteelBlue");\
		UxPutBackground(Topologia_pb6,"SteelBlue");\
\
        \
        strcpy(app,path_libut);\
        strcat(app,"   Not Compiled");\
        UxPutLabelString(ModuliLibLabel,app);\
        UxPutForeground(ModuliLibLabel,"Red");\
		\
	}\
/*\
 Rende attiva l'attivita' di documentazione automatica del modello\
*/\
\
UxPutSensitive(Documentazione_pb1,"true");\
UxPutSensitive(Documentazione_pb2,"true");\
UxPutBackground(Documentazione_rc,"LightBlue");\
UxPutBackground(Documentazione_pb2,"LightBlue");\
\
#endif\
}\
\
/*\
 aggiorna la possibilita' di accesso alle routines di utilita'\
*/\
aggiorna_utilities()\
{\
UxPutSensitive(Librarian_pb1,"true");\
UxPutSensitive(Librarian_pb2,"true");\
UxPutBackground(Librarian_pb2,"CadetBlue");\
UxPutBackground(Librarian_rc,"CadetBlue");\
\
if(ok_path_libut)\
	{\
		\
	}\
}\
\
\
agg_label_ambiente()\
{\
char app[FILENAME_MAX];\
if(ok_path_legocad)\
	{\
	UxPutLabelString(LegocadPathLabel,path_legocad);\
	UxPutForeground(LegocadPathLabel,"Black");\
	}\
else\
	{\
	UxPutLabelString(LegocadPathLabel,"Not Defined");\
	UxPutForeground(LegocadPathLabel,"Red");\
	}\
if(ok_libut)\
	{\
	app[0]=0;\
	strcpy(app,path_libut);\
	strcat(app,"   Exist");\
	UxPutLabelString(ModuliLibLabel,app);\
	UxPutForeground(ModuliLibLabel,"Black");\
	}\
else if (ok_path_libut)\
	{\
	app[0]=0;\
	strcpy(app,path_libut);\
	strcat(app," - Not Present");\
	UxPutLabelString(ModuliLibLabel,app);\
	UxPutForeground(ModuliLibLabel,"Red");\
	}\
else\
	{\
	UxPutLabelString(ModuliLibLabel,"Not Defined");\
	UxPutForeground(ModuliLibLabel,"Red");\
	}\
if(ok_libreg)\
	{\
	app[0]=0;\
	strcpy(app,path_libreg);\
	strcat(app,"   Exist");\
	UxPutLabelString(RegLibLabel,app);\
	UxPutForeground(RegLibLabel,"Black");\
	}\
else if (ok_path_libreg)\
	{\
	app[0]=0;\
	strcpy(app,path_libreg);\
	strcat(app,"   Not Present");\
	UxPutLabelString(RegLibLabel,app);\
	UxPutForeground(RegLibLabel,"Red");\
	}\
else\
	{ \
	UxPutLabelString(RegLibLabel,"Not Defined");\
	UxPutForeground(RegLibLabel,"Red");\
	}\
return(0);\
}\
\
\
\
\
\
show_warning(mess)\
char *mess;\
{\
  char   *str, *new_str;\
  extern swidget messageST;\
\
  str = UxGetText( messageST );\
  new_str = (char*) malloc ( sizeof(char*) * ( strlen(mess)+strlen(str)+1 ) );\
  strcpy( new_str, str );\
\
  strcat( new_str, mess );\
  UxPutText( messageST, new_str );\
  XmTextShowPosition(UxGetWidget(messageST),strlen(new_str)-1);\
  free( str );\
  free( new_str );\
}\
\
\
\
show_error(mess)\
char *mess;\
{\
create_vis_msg(mess);\
}\
\
set_icone()\
{\
#ifndef DESIGN_TIME\
path_icone=getenv("LEGOCAD_ICO");\
if(path_icone==NULL)\
	{\
	printf("\n Environment variable LEGOCAD_ICO\n is not defined");\
	exit(1);\
	}\
#else\
strcpy((char *)buf_path_icone,"./icons");\
path_icone=buf_path_icone;\
#endif\
\
strcpy(icon,path_icone);\
strcat(icon,"/topology.bm");\
UxPutLabelInsensitivePixmap(Topologia_pb5,icon);\
UxPutLabelPixmap(Topologia_pb5,icon);\
\
strcpy(icon,path_icone);\
strcat(icon,"/dati.bm");\
UxPutLabelInsensitivePixmap(Dati_pb5,icon);\
UxPutLabelPixmap(Dati_pb5,icon);\
\
strcpy(icon,path_icone);\
strcat(icon,"/stazionario.bm");\
UxPutLabelInsensitivePixmap(Stazionario_pb5,icon);\
UxPutLabelPixmap(Stazionario_pb5,icon);\
\
strcpy(icon,path_icone);\
strcat(icon,"/transitorio.bm");\
UxPutLabelInsensitivePixmap(Transitorio_pb5,icon);\
UxPutLabelPixmap(Transitorio_pb5,icon);\
\
strcpy(icon,path_icone);\
strcat(icon,"/librarian.bm");\
UxPutLabelInsensitivePixmap(Librarian_pb1,icon);\
UxPutLabelPixmap(Librarian_pb1,icon);\
\
strcpy(icon,path_icone);\
strcat(icon,"/grafica.bm");\
UxPutLabelInsensitivePixmap(Grafica_pb1,icon);\
UxPutLabelPixmap(Grafica_pb1,icon);\
\
strcpy(icon,path_icone);\
strcat(icon,"/tavole.bm");\
UxPutLabelInsensitivePixmap(Tavole_pb1,icon);\
UxPutLabelPixmap(Tavole_pb1,icon);\
\
strcpy(icon,path_icone);\
strcat(icon,"/documentazione.bm");\
UxPutLabelInsensitivePixmap(Documentazione_pb1,icon);\
UxPutLabelPixmap(Documentazione_pb1,icon);\
}\
\
set_win_cursor(cursore)\
char *cursore;\
{\
\
set_pixmap_cursor(UxGetWidget(applicationShell1), cursore );\
\
}\
\
reset_win_cursor()\
{\
\
undef_cursore(UxGetWidget(applicationShell1));\
}
*applicationShell1.name: applicationShell1
*applicationShell1.x: 248
*applicationShell1.y: 218
*applicationShell1.width: 640
*applicationShell1.height: 600
*applicationShell1.iconName: "Legocad"
*applicationShell1.title: "Legocad"
*applicationShell1.popupCallback: {\
\
}

*mainWindow1.class: mainWindow
*mainWindow1.parent: applicationShell1
*mainWindow1.static: true
*mainWindow1.name: mainWindow1
*mainWindow1.unitType: "pixels"
*mainWindow1.x: 10
*mainWindow1.y: 15
*mainWindow1.width: 640
*mainWindow1.height: 600

*Edit.class: rowColumn
*Edit.parent: mainWindow1
*Edit.static: true
*Edit.name: Edit
*Edit.rowColumnType: "menu_bar"
*Edit.menuAccelerator: "<KeyUp>F10"
*Edit.menuHelpWidget: "Edit_top_b3"

*menu1_p1.class: rowColumn
*menu1_p1.parent: Edit
*menu1_p1.static: true
*menu1_p1.name: menu1_p1
*menu1_p1.rowColumnType: "menu_pulldown"

*ProcessoButton.class: pushButton
*ProcessoButton.parent: menu1_p1
*ProcessoButton.static: true
*ProcessoButton.name: ProcessoButton
*ProcessoButton.labelString: "Process modelling..."
*ProcessoButton.mnemonic: "P"
*ProcessoButton.activateCallback: {\
\
extern swidget SelModelsActivate();\
\
tipo_modello= TIPO_PROCESSO;\
\
if( wsel == NULL )\
   wsel = SelModelsActivate(SELECT_MODEL);\
\
}

*ControlloButton.class: pushButton
*ControlloButton.parent: menu1_p1
*ControlloButton.static: true
*ControlloButton.name: ControlloButton
*ControlloButton.labelString: "Control system modelling"
*ControlloButton.mnemonic: "C"
*ControlloButton.activateCallback: {\
extern swidget SelModelsActivate();\
tipo_modello= TIPO_REGOLAZIONE;\
/*\
SelModelsActivate();\
*/\
\
   SelModelsActivate(SELECT_MODEL);\
}\


*MixedButton.class: pushButton
*MixedButton.parent: menu1_p1
*MixedButton.static: true
*MixedButton.name: MixedButton
*MixedButton.labelString: "Mixed system modelling"
*MixedButton.activateCallback: {\
extern swidget SelModelsActivate();\
tipo_modello= TIPO_MIX;\
/*\
SelModelsActivate();\
*/\
   SelModelsActivate(SELECT_MODEL);\
}\

*MixedButton.mnemonic: "X"

*sep1.class: separatorGadget
*sep1.parent: menu1_p1
*sep1.static: true
*sep1.name: sep1

*OrderingButton.class: pushButton
*OrderingButton.parent: menu1_p1
*OrderingButton.static: true
*OrderingButton.name: OrderingButton
*OrderingButton.labelString: "Models Management"
*OrderingButton.activateCallback: {\
extern swidget SelModelsActivate();\
\
tipo_modello = TIPO_PROCESSO;\
if( wsel == NULL)\
   wsel = SelModelsActivate( REORDER_MODEL );	\
\
}

*sep2.class: separatorGadget
*sep2.parent: menu1_p1
*sep2.static: true
*sep2.name: sep2

*ExitButton.class: pushButton
*ExitButton.parent: menu1_p1
*ExitButton.static: true
*ExitButton.name: ExitButton
*ExitButton.labelString: "Quit"
*ExitButton.mnemonic: "Q"
*ExitButton.activateCallback: {\
char messaggio[FILENAME_MAX];\
swidget w;\
/* testa se vi sono processi legocad attivi */\
if(proc_legocad_attivi())\
	w=create_questionUscitaLegocad("Legocad subprocesses already active\n Do You really want to exit LEGOCAD ?");\
else\
	w=create_questionUscitaLegocad("Exit LEGOCAD?");\
UxPopupInterface(w,no_grab);\
	\
}

*EditModels.class: rowColumn
*EditModels.parent: Edit
*EditModels.static: true
*EditModels.name: EditModels
*EditModels.rowColumnType: "menu_pulldown"

*CopyModelButton.class: pushButtonGadget
*CopyModelButton.parent: EditModels
*CopyModelButton.static: true
*CopyModelButton.name: CopyModelButton
*CopyModelButton.labelString: "Copy Model..."
*CopyModelButton.activateCallback: {\
/*\
   extern swidget create_CopyModel();\
\
   create_CopyModel();\
\
   extern swidget create_form6();\
   swidget sw;\
\
   sw =create_form6();\
**/\
 \
   extern swidget create_CopyModel();\
   swidget sw;\
\
   sw = create_CopyModel();\
   UxPopupInterface(sw,no_grab);\
}

*ExamplesButton.class: cascadeButton
*ExamplesButton.parent: EditModels
*ExamplesButton.static: true
*ExamplesButton.name: ExamplesButton
*ExamplesButton.labelString: "Training Examples"
*ExamplesButton.subMenuId: "Training"

*Training.class: rowColumn
*Training.parent: EditModels
*Training.static: true
*Training.name: Training
*Training.rowColumnType: "menu_pulldown"

*Training_b1.class: pushButton
*Training_b1.parent: Training
*Training_b1.static: true
*Training_b1.name: Training_b1
*Training_b1.labelString: "Select..."
*Training_b1.activateCallback: {\
/*\
   extern swidget create_vis_msg();\
   create_vis_msg("Function not yet implemented");\
*/\
extern swidget create_TrainingModels();\
\
create_TrainingModels();\
}

*menu_p4.class: rowColumn
*menu_p4.parent: Edit
*menu_p4.static: true
*menu_p4.name: menu_p4
*menu_p4.rowColumnType: "menu_pulldown"

*menu_p4_b2.class: cascadeButton
*menu_p4_b2.parent: menu_p4
*menu_p4_b2.static: true
*menu_p4_b2.name: menu_p4_b2
*menu_p4_b2.labelString: "Display"
*menu_p4_b2.subMenuId: "Option_pane"

*Option_pane.class: rowColumn
*Option_pane.parent: menu_p4
*Option_pane.static: true
*Option_pane.name: Option_pane
*Option_pane.rowColumnType: "menu_pulldown"
*Option_pane.radioBehavior: "true"

*Grafica.class: toggleButton
*Grafica.parent: Option_pane
*Grafica.static: true
*Grafica.name: Grafica
*Grafica.labelString: "Symbolic Diagram"
*Grafica.valueChangedCallback: {\
grafica_on=1;\
}
*Grafica.set: "true"

*ListeButton.class: toggleButton
*ListeButton.parent: Option_pane
*ListeButton.static: true
*ListeButton.name: ListeButton
*ListeButton.labelString: "Only by lists"
*ListeButton.valueChangedCallback: {\
grafica_on=0;\
}

*Utilities.class: rowColumn
*Utilities.parent: Edit
*Utilities.static: true
*Utilities.name: Utilities
*Utilities.rowColumnType: "menu_pulldown"

*Utilities_b1.class: cascadeButton
*Utilities_b1.parent: Utilities
*Utilities_b1.static: true
*Utilities_b1.name: Utilities_b1
*Utilities_b1.labelString: "Edi14"
*Utilities_b1.subMenuId: "Edi14_utils"

*Utilities_b2.class: cascadeButton
*Utilities_b2.parent: Utilities
*Utilities_b2.static: true
*Utilities_b2.name: Utilities_b2
*Utilities_b2.labelString: "Snaf14"
*Utilities_b2.subMenuId: "Snaf14_utils"

*Utilities_b3.class: cascadeButton
*Utilities_b3.parent: Utilities
*Utilities_b3.static: true
*Utilities_b3.name: Utilities_b3
*Utilities_b3.labelString: "Foraus"
*Utilities_b3.subMenuId: "Foraus_utils"

*Edi14_utils.class: rowColumn
*Edi14_utils.parent: Utilities
*Edi14_utils.static: true
*Edi14_utils.name: Edi14_utils
*Edi14_utils.rowColumnType: "menu_pulldown"
*Edi14_utils.mapCallback: {\
FILE *fp;\
\
if( (fp = fopen("f14.dat","r")) == NULL)\
{\
   UxPutSensitive(Edi14_run,"false");\
   UxPutSensitive(Edi14_save,"false");\
   UxPutSensitive(Edi14_viewout,"false");\
}\
else\
{\
   UxPutSensitive(Edi14_run,"true");\
   UxPutSensitive(Edi14_save,"true");\
   UxPutSensitive(Edi14_viewout,"true");\
}   \
\
fclose(fp);\
\
\
}

*Edi14_run.class: pushButton
*Edi14_run.parent: Edi14_utils
*Edi14_run.static: true
*Edi14_run.name: Edi14_run
*Edi14_run.labelString: "run Edi14"
*Edi14_run.activateCallback: {\
/*\
   questa callback deve attivare\
   l'edi 14 dopo avere selezionato\
   il file14 da utilizzare \
\
	create_vis_msg("Function development in progress");\
*/\
   extern swidget create_edi14FileSelection();\
   swidget filesel;\
   filesel = create_edi14FileSelection(EDI14_INPUT_SELECTION);\
   UxPopupInterface(filesel,no_grab);\
\
}\


*Edi14_save.class: pushButton
*Edi14_save.parent: Edi14_utils
*Edi14_save.static: true
*Edi14_save.name: Edi14_save
*Edi14_save.labelString: "Save Result Edi14"
*Edi14_save.activateCallback: {\
extern swidget create_selectionBoxDialog1();\
swidget wid;\
\
wid = create_selectionBoxDialog1();\
UxPopupInterface(wid,no_grab);\
\
}

*Edi14_viewout.class: pushButton
*Edi14_viewout.parent: Edi14_utils
*Edi14_viewout.static: true
*Edi14_viewout.name: Edi14_viewout
*Edi14_viewout.labelString: "View Edi14 results"
*Edi14_viewout.activateCallback: {\
   system("edit_f01 edi14.out 0");\
}

*Snaf14_utils.class: rowColumn
*Snaf14_utils.parent: Utilities
*Snaf14_utils.static: true
*Snaf14_utils.name: Snaf14_utils
*Snaf14_utils.rowColumnType: "menu_pulldown"
*Snaf14_utils.mapCallback: {\
FILE *fp;\
\
if( (fp = fopen("snapshot.dat","r")) == NULL)\
   UxPutSensitive(Snaf14_run,"false");\
else\
   UxPutSensitive(Snaf14_run,"true");\
fclose(fp);\
\
if( (fp = fopen("f14.s","r")) == NULL)\
{\
   UxPutSensitive(Snaf14_view,"false");\
   UxPutSensitive(Snaf14_print,"false");\
}\
else\
{\
   UxPutSensitive(Snaf14_view,"true");\
   UxPutSensitive(Snaf14_print,"true");\
}\
fclose(fp);\
\
\
}

*Snaf14_run.class: pushButton
*Snaf14_run.parent: Snaf14_utils
*Snaf14_run.static: true
*Snaf14_run.name: Snaf14_run
*Snaf14_run.labelString: "run Snaf14"
*Snaf14_run.activateCallback: {\
system("xterm -T SNAF14 -sb -e snaf14 &");\
}

*Snaf14_view.class: pushButton
*Snaf14_view.parent: Snaf14_utils
*Snaf14_view.static: true
*Snaf14_view.name: Snaf14_view
*Snaf14_view.labelString: "View Results"
*Snaf14_view.activateCallback: {\
  char comando[200];\
\
  sprintf(comando,"%s","edit_f01 f14.s 0");\
  system(comando);\
\
}

*Snaf14_print.class: pushButton
*Snaf14_print.parent: Snaf14_utils
*Snaf14_print.static: true
*Snaf14_print.name: Snaf14_print
*Snaf14_print.labelString: "Print Results "
*Snaf14_print.activateCallback: {\
   extern int print_file();\
\
   print_file("f14.s");\
}

*Foraus_utils.class: rowColumn
*Foraus_utils.parent: Utilities
*Foraus_utils.static: true
*Foraus_utils.name: Foraus_utils
*Foraus_utils.rowColumnType: "menu_pulldown"
*Foraus_utils.mapCallback: {\
extern char path_modello[];\
FILE *fp;\
char pathfile[FILENAME_MAX];\
\
sprintf(pathfile,"%s/%s",path_modello,FILE_FORAUS);\
\
if( (fp = fopen(pathfile,"r")) == NULL)\
{\
   UxPutSensitive(Foraus_print,"false");\
   UxPutSensitive(Foraus_delete,"false");\
}\
else\
{\
   fclose(fp);\
   UxPutSensitive(Foraus_print,"true");\
   UxPutSensitive(Foraus_delete,"true");\
}\
}

*Foraus_edit.class: cascadeButton
*Foraus_edit.parent: Foraus_utils
*Foraus_edit.static: true
*Foraus_edit.name: Foraus_edit
*Foraus_edit.labelString: "Edit"
*Foraus_edit.subMenuId: "Edit_foraus"

*Foraus_print.class: pushButton
*Foraus_print.parent: Foraus_utils
*Foraus_print.static: true
*Foraus_print.name: Foraus_print
*Foraus_print.labelString: "Print foraus"
*Foraus_print.activateCallback: {\
   extern int print_file();\
\
   print_file(FILE_FORAUS);\
}

*Foraus_delete.class: pushButton
*Foraus_delete.parent: Foraus_utils
*Foraus_delete.static: true
*Foraus_delete.name: Foraus_delete
*Foraus_delete.labelString: "Delete foraus"
*Foraus_delete.activateCallback: {\
/***\
extern swidget create_vis_msg();\
create_vis_msg("Function not yet implemented");\
***/\
extern swidget create_question_operation();\
create_question_operation(NULL,DELETE_FORAUS);\
}

*Edit_foraus.class: rowColumn
*Edit_foraus.parent: Foraus_utils
*Edit_foraus.static: true
*Edit_foraus.name: Edit_foraus
*Edit_foraus.rowColumnType: "menu_pulldown"
*Edit_foraus.mapCallback: {\
extern char path_modello[];\
FILE *fp;\
char pathfile[FILENAME_MAX];\
\
sprintf(pathfile,"%s/%s",path_modello,FILE_FORAUS);\
\
if( (fp = fopen(pathfile,"r")) == NULL)\
{\
   UxPutSensitive(foraus_copy,"false");\
   UxPutSensitive(foraus_manage,"false");\
}\
else\
{\
   fclose(fp);\
   UxPutSensitive(foraus_copy,"true");\
   UxPutSensitive(foraus_manage,"true");\
}\
}

*foraus_copy.class: pushButton
*foraus_copy.parent: Edit_foraus
*foraus_copy.static: true
*foraus_copy.name: foraus_copy
*foraus_copy.labelString: "Copy from ..."
*foraus_copy.activateCallback: {\
swidget swid;\
extern swidget create_CopyForaus();\
\
swid = create_CopyForaus();\
UxPopupInterface(swid,no_grab);\
\
}

*foraus_manage.class: pushButton
*foraus_manage.parent: Edit_foraus
*foraus_manage.static: true
*foraus_manage.name: foraus_manage
*foraus_manage.labelString: "Manage ..."
*foraus_manage.activateCallback: {\
   extern swidget create_vis_msg();\
   extern swidget create_Foraus();\
   swidget wfor;\
/*\
   create_vis_msg("Function not yet implemented");\
   return;\
*/\
   wfor = create_Foraus();\
   UxPopupInterface(wfor,no_grab);\
}

*help_pane.class: rowColumn
*help_pane.parent: Edit
*help_pane.static: true
*help_pane.name: help_pane
*help_pane.rowColumnType: "menu_pulldown"

*help_contents.class: pushButton
*help_contents.parent: help_pane
*help_contents.static: true
*help_contents.name: help_contents
*help_contents.labelString: "Contents"
*help_contents.mnemonic: "C"
*help_contents.activateCallback: {\
#ifdef HYPERHELP_USED\
char *path_hyper;\
printf("PRIMA DI GETENV!!!\n");\
path_hyper = getenv("HLPPATH");\
if(path_hyper == NULL) {\
	printf("SONO QUI!!!!!!\n");\
	create_vis_msg("Environment variable HLPPATH not defined!");\
}	\
else {\
	WinHelp(UxDisplay,"legohelp.hlp",HELP_CONTENTS,0);\
}\
#else\
help_not_available_msg();\
#endif\
}

*help_search.class: pushButton
*help_search.parent: help_pane
*help_search.static: true
*help_search.name: help_search
*help_search.labelString: "Search..."
*help_search.mnemonic: "S"
*help_search.activateCallback: {\
#ifdef HYPERHELP_USED\
/*char help_file[200];\
sprintf(help_file,"%s/legohelp/legohelp.hlp",getenv("LEGOROOT")); */\
WinHelp(UxDisplay,"legohelp.hlp",HELP_COMMAND,(unsigned long) "TextSearch()");\
#else\
help_not_available_msg();\
#endif\
}

*help_on.class: pushButton
*help_on.parent: help_pane
*help_on.static: true
*help_on.name: help_on
*help_on.labelString: "Help On..."
*help_on.activateCallback: {\
#ifndef HYPERHELP_USED\
help_not_available_msg();\
#endif\
}

*Edit_p11_b4.class: separator
*Edit_p11_b4.parent: help_pane
*Edit_p11_b4.static: true
*Edit_p11_b4.name: Edit_p11_b4

*help_on_help.class: pushButton
*help_on_help.parent: help_pane
*help_on_help.static: true
*help_on_help.name: help_on_help
*help_on_help.labelString: "How to Use Help"
*help_on_help.mnemonic: "H"
*help_on_help.activateCallback: {\
#ifdef HYPERHELP_USED\
WinHelp(UxDisplay,"",HELP_HELPONHELP, 0);\
#else\
help_not_available_msg();\
#endif\
}

*Edit_p11_b6.class: separator
*Edit_p11_b6.parent: help_pane
*Edit_p11_b6.static: true
*Edit_p11_b6.name: Edit_p11_b6

*help_about.class: pushButton
*help_about.parent: help_pane
*help_about.static: true
*help_about.name: help_about
*help_about.labelString: "About Legocad..."
*help_about.activateCallback: {\
#ifndef DESIGN_TIME\
{\
extern swidget create_vis_msg();\
static char *msg="Version 1.0\nLEGOCAD model builder\n\nProperty of ENEL";\
\
create_vis_msg(msg);\
}\
#endif\
}

*menu1_top_b1.class: cascadeButton
*menu1_top_b1.parent: Edit
*menu1_top_b1.static: true
*menu1_top_b1.name: menu1_top_b1
*menu1_top_b1.labelString: "File"
*menu1_top_b1.mnemonic: "F"
*menu1_top_b1.subMenuId: "menu1_p1"
*menu1_top_b1.sensitive: "true"

*menu1_top_b2.class: cascadeButton
*menu1_top_b2.parent: Edit
*menu1_top_b2.static: true
*menu1_top_b2.name: menu1_top_b2
*menu1_top_b2.labelString: "Edit"
*menu1_top_b2.mnemonic: "E"
*menu1_top_b2.subMenuId: "EditModels"

*Edit_top_b1.class: cascadeButtonGadget
*Edit_top_b1.parent: Edit
*Edit_top_b1.static: true
*Edit_top_b1.name: Edit_top_b1
*Edit_top_b1.labelString: "Options"
*Edit_top_b1.subMenuId: "menu_p4"

*Edit_top_b2.class: cascadeButton
*Edit_top_b2.parent: Edit
*Edit_top_b2.static: true
*Edit_top_b2.name: Edit_top_b2
*Edit_top_b2.labelString: "Utilities"
*Edit_top_b2.subMenuId: "Utilities"

*Edit_top_b3.class: cascadeButtonGadget
*Edit_top_b3.parent: Edit
*Edit_top_b3.static: true
*Edit_top_b3.name: Edit_top_b3
*Edit_top_b3.labelString: "Help"
*Edit_top_b3.mnemonic: "H"
*Edit_top_b3.subMenuId: "help_pane"
*Edit_top_b3.alignment: "alignment_beginning"

*panedWindow1.class: panedWindow
*panedWindow1.parent: mainWindow1
*panedWindow1.static: true
*panedWindow1.name: panedWindow1
*panedWindow1.width: 755
*panedWindow1.height: 300

*form2.class: form
*form2.parent: panedWindow1
*form2.static: true
*form2.name: form2
*form2.unitType: "pixels"
*form2.x: 3
*form2.y: 3
*form2.width: 627
*form2.height: 112
*form2.allowResize: "true"

*label1.class: label
*label1.parent: form2
*label1.static: true
*label1.name: label1
*label1.x: 10
*label1.y: 5
*label1.width: 170
*label1.height: 20
*label1.labelString: "Legocad Environment:"

*label2.class: label
*label2.parent: form2
*label2.static: true
*label2.name: label2
*label2.x: 25
*label2.y: 55
*label2.width: 160
*label2.height: 20
*label2.labelString: "Process Modules Library:"
*label2.fontList: "-adobe-helvetica-medium-r-normal--12-120-75-75-p-67-iso8859-1"
*label2.alignment: "alignment_beginning"

*LegocadPathLabel.class: label
*LegocadPathLabel.parent: form2
*LegocadPathLabel.static: true
*LegocadPathLabel.name: LegocadPathLabel
*LegocadPathLabel.x: 190
*LegocadPathLabel.y: 35
*LegocadPathLabel.width: 435
*LegocadPathLabel.height: 20
*LegocadPathLabel.alignment: "alignment_beginning"
*LegocadPathLabel.fontList: "-adobe-helvetica-medium-o-normal--14-140-75-75-p-78-iso8859-1"
*LegocadPathLabel.labelString: "Not defined"

*label4.class: label
*label4.parent: form2
*label4.static: true
*label4.name: label4
*label4.x: 25
*label4.y: 75
*label4.width: 155
*label4.height: 20
*label4.labelString: "Control Modules Library:"
*label4.fontList: "-adobe-helvetica-medium-r-normal--12-120-75-75-p-67-iso8859-1"
*label4.alignment: "alignment_beginning"

*label5.class: label
*label5.parent: form2
*label5.static: true
*label5.name: label5
*label5.x: 25
*label5.y: 35
*label5.width: 165
*label5.height: 20
*label5.labelString: "Legocad Development Root:"
*label5.fontList: "-adobe-helvetica-medium-r-normal--12-120-75-75-p-67-iso8859-1"
*label5.alignment: "alignment_beginning"

*ModuliLibLabel.class: label
*ModuliLibLabel.parent: form2
*ModuliLibLabel.static: true
*ModuliLibLabel.name: ModuliLibLabel
*ModuliLibLabel.x: 190
*ModuliLibLabel.y: 55
*ModuliLibLabel.width: 435
*ModuliLibLabel.height: 20
*ModuliLibLabel.alignment: "alignment_beginning"
*ModuliLibLabel.fontList: "-adobe-helvetica-medium-o-normal--14-140-75-75-p-78-iso8859-1"

*RegLibLabel.class: label
*RegLibLabel.parent: form2
*RegLibLabel.static: true
*RegLibLabel.name: RegLibLabel
*RegLibLabel.x: 190
*RegLibLabel.y: 75
*RegLibLabel.width: 440
*RegLibLabel.height: 20
*RegLibLabel.alignment: "alignment_beginning"
*RegLibLabel.fontList: "-adobe-helvetica-medium-o-normal--14-140-75-75-p-78-iso8859-1"

*form1.class: form
*form1.parent: panedWindow1
*form1.static: true
*form1.name: form1
*form1.unitType: "pixels"
*form1.x: 3
*form1.y: 120
*form1.width: 642
*form1.height: 175
*form1.paneMinimum: 170
*form1.mapCallback: {\
\
}

*labelCostruzione.class: labelGadget
*labelCostruzione.parent: form1
*labelCostruzione.static: true
*labelCostruzione.name: labelCostruzione
*labelCostruzione.x: 5
*labelCostruzione.y: 30
*labelCostruzione.width: 160
*labelCostruzione.height: 25
*labelCostruzione.labelString: "Model construction:"
*labelCostruzione.alignment: "alignment_beginning"
*labelCostruzione.rightAttachment: "attach_none"
*labelCostruzione.leftOffset: 5
*labelCostruzione.leftAttachment: "attach_form"

*rowColumn5.class: rowColumn
*rowColumn5.parent: form1
*rowColumn5.static: true
*rowColumn5.name: rowColumn5
*rowColumn5.unitType: "pixels"
*rowColumn5.x: 44
*rowColumn5.y: 53
*rowColumn5.width: 544
*rowColumn5.height: 107
*rowColumn5.orientation: "horizontal"
*rowColumn5.topAttachment: "attach_widget"
*rowColumn5.topWidget: "labelCostruzione"

*Topologia_frame3.class: frame
*Topologia_frame3.parent: rowColumn5
*Topologia_frame3.static: true
*Topologia_frame3.name: Topologia_frame3
*Topologia_frame3.x: 2
*Topologia_frame3.y: 3
*Topologia_frame3.width: 77
*Topologia_frame3.height: 101
*Topologia_frame3.shadowType: "shadow_out"

*Topologia_rc.class: rowColumn
*Topologia_rc.parent: Topologia_frame3
*Topologia_rc.static: false
*Topologia_rc.name: Topologia_rc
*Topologia_rc.x: 2
*Topologia_rc.y: 2
*Topologia_rc.width: 74
*Topologia_rc.height: 97
*Topologia_rc.borderWidth: 0
*Topologia_rc.foreground: "darkslategrey"
*Topologia_rc.entryAlignment: "alignment_center"
*Topologia_rc.background: "SteelBlue"

*Topologia_pb5.class: pushButton
*Topologia_pb5.parent: Topologia_rc
*Topologia_pb5.static: true
*Topologia_pb5.name: Topologia_pb5
*Topologia_pb5.x: 3
*Topologia_pb5.y: 3
*Topologia_pb5.width: 68
*Topologia_pb5.height: 10
*Topologia_pb5.labelType: "pixmap"
*Topologia_pb5.sensitive: "false"
*Topologia_pb5.shadowThickness: 1
*Topologia_pb5.background: "#b0c4de"
*Topologia_pb5.activateCallback: {\
attiva_topology();\
}

*Topologia_pb6.class: pushButton
*Topologia_pb6.parent: Topologia_rc
*Topologia_pb6.static: false
*Topologia_pb6.name: Topologia_pb6
*Topologia_pb6.x: 3
*Topologia_pb6.y: 16
*Topologia_pb6.width: 68
*Topologia_pb6.height: 29
*Topologia_pb6.labelString: "Topology"
*Topologia_pb6.background: "SteelBlue"
*Topologia_pb6.sensitive: "false"
*Topologia_pb6.activateCallback: {\
attiva_topology();\
\
}

*arrowButtonGadget10.class: arrowButtonGadget
*arrowButtonGadget10.parent: rowColumn5
*arrowButtonGadget10.static: true
*arrowButtonGadget10.name: arrowButtonGadget10
*arrowButtonGadget10.x: 83
*arrowButtonGadget10.y: 3
*arrowButtonGadget10.width: 33
*arrowButtonGadget10.height: 101
*arrowButtonGadget10.arrowDirection: "arrow_right"
*arrowButtonGadget10.shadowThickness: 0
*arrowButtonGadget10.sensitive: "true"
*arrowButtonGadget10.activateCallback: {\
esegui_crealg1();\
}

*Dati_frame3.class: frame
*Dati_frame3.parent: rowColumn5
*Dati_frame3.static: true
*Dati_frame3.name: Dati_frame3
*Dati_frame3.x: 120
*Dati_frame3.y: 3
*Dati_frame3.width: 88
*Dati_frame3.height: 101
*Dati_frame3.shadowType: "shadow_out"

*Dati_rc.class: rowColumn
*Dati_rc.parent: Dati_frame3
*Dati_rc.static: false
*Dati_rc.name: Dati_rc
*Dati_rc.x: 2
*Dati_rc.y: 2
*Dati_rc.width: 84
*Dati_rc.height: 97
*Dati_rc.borderWidth: 0
*Dati_rc.foreground: "darkslategrey"
*Dati_rc.entryAlignment: "alignment_center"
*Dati_rc.background: "SteelBlue"

*Dati_pb5.class: pushButton
*Dati_pb5.parent: Dati_rc
*Dati_pb5.static: true
*Dati_pb5.name: Dati_pb5
*Dati_pb5.x: 2
*Dati_pb5.y: 3
*Dati_pb5.width: 78
*Dati_pb5.height: 10
*Dati_pb5.activateCallback: { attiva_data(); }
*Dati_pb5.labelType: "pixmap"
*Dati_pb5.shadowThickness: 1
*Dati_pb5.background: "#b0c4de"

*Dati_pb6.class: pushButton
*Dati_pb6.parent: Dati_rc
*Dati_pb6.static: false
*Dati_pb6.name: Dati_pb6
*Dati_pb6.x: 2
*Dati_pb6.y: 16
*Dati_pb6.width: 78
*Dati_pb6.height: 29
*Dati_pb6.labelString: "Data Editor"
*Dati_pb6.sensitive: "false"
*Dati_pb6.background: "SteelBlue"
*Dati_pb6.activateCallback: { attiva_data(); }

*arrowButtonGadget11.class: arrowButtonGadget
*arrowButtonGadget11.parent: rowColumn5
*arrowButtonGadget11.static: true
*arrowButtonGadget11.name: arrowButtonGadget11
*arrowButtonGadget11.x: 211
*arrowButtonGadget11.y: 3
*arrowButtonGadget11.width: 33
*arrowButtonGadget11.height: 101
*arrowButtonGadget11.arrowDirection: "arrow_right"
*arrowButtonGadget11.shadowThickness: 0
*arrowButtonGadget11.sensitive: "true"
*arrowButtonGadget11.activateCallback: {\
esegui_crealg3();\
}

*Stazionario_frame3.class: frame
*Stazionario_frame3.parent: rowColumn5
*Stazionario_frame3.static: true
*Stazionario_frame3.name: Stazionario_frame3
*Stazionario_frame3.x: 248
*Stazionario_frame3.y: 3
*Stazionario_frame3.width: 99
*Stazionario_frame3.height: 101
*Stazionario_frame3.shadowType: "shadow_out"

*Stazionario_rc.class: rowColumn
*Stazionario_rc.parent: Stazionario_frame3
*Stazionario_rc.static: false
*Stazionario_rc.name: Stazionario_rc
*Stazionario_rc.x: 1
*Stazionario_rc.y: 2
*Stazionario_rc.width: 95
*Stazionario_rc.height: 97
*Stazionario_rc.borderWidth: 0
*Stazionario_rc.foreground: "darkslategrey"
*Stazionario_rc.entryAlignment: "alignment_center"
*Stazionario_rc.background: "SteelBlue"

*Stazionario_pb5.class: pushButton
*Stazionario_pb5.parent: Stazionario_rc
*Stazionario_pb5.static: true
*Stazionario_pb5.name: Stazionario_pb5
*Stazionario_pb5.x: 3
*Stazionario_pb5.y: 3
*Stazionario_pb5.width: 90
*Stazionario_pb5.height: 10
*Stazionario_pb5.labelType: "pixmap"
*Stazionario_pb5.shadowThickness: 1
*Stazionario_pb5.activateCallback: { attiva_steady(); }
*Stazionario_pb5.background: "#b0c4de"

*Stazionario_pb6.class: pushButton
*Stazionario_pb6.parent: Stazionario_rc
*Stazionario_pb6.static: false
*Stazionario_pb6.name: Stazionario_pb6
*Stazionario_pb6.x: 3
*Stazionario_pb6.y: 16
*Stazionario_pb6.width: 90
*Stazionario_pb6.height: 29
*Stazionario_pb6.background: "SteelBlue"
*Stazionario_pb6.labelString: "Steady State"
*Stazionario_pb6.sensitive: "false"
*Stazionario_pb6.activateCallback: { attiva_steady();}

*arrowButtonGadget12.class: arrowButtonGadget
*arrowButtonGadget12.parent: rowColumn5
*arrowButtonGadget12.static: true
*arrowButtonGadget12.name: arrowButtonGadget12
*arrowButtonGadget12.x: 350
*arrowButtonGadget12.y: 3
*arrowButtonGadget12.width: 33
*arrowButtonGadget12.height: 101
*arrowButtonGadget12.arrowDirection: "arrow_right"
*arrowButtonGadget12.shadowThickness: 0
*arrowButtonGadget12.sensitive: "true"
*arrowButtonGadget12.activateCallback: {\
esegui_crealg5sk();\
}

*Transitorio_frame3.class: frame
*Transitorio_frame3.parent: rowColumn5
*Transitorio_frame3.static: true
*Transitorio_frame3.name: Transitorio_frame3
*Transitorio_frame3.x: 387
*Transitorio_frame3.y: 3
*Transitorio_frame3.width: 111
*Transitorio_frame3.height: 101
*Transitorio_frame3.shadowType: "shadow_out"

*Transitorio_rc.class: rowColumn
*Transitorio_rc.parent: Transitorio_frame3
*Transitorio_rc.static: false
*Transitorio_rc.name: Transitorio_rc
*Transitorio_rc.x: 1
*Transitorio_rc.y: 2
*Transitorio_rc.width: 108
*Transitorio_rc.height: 97
*Transitorio_rc.borderWidth: 0
*Transitorio_rc.foreground: "darkslategrey"
*Transitorio_rc.entryAlignment: "alignment_center"
*Transitorio_rc.background: "SteelBlue"

*Transitorio_pb5.class: pushButton
*Transitorio_pb5.parent: Transitorio_rc
*Transitorio_pb5.static: true
*Transitorio_pb5.name: Transitorio_pb5
*Transitorio_pb5.x: 3
*Transitorio_pb5.y: 3
*Transitorio_pb5.width: 102
*Transitorio_pb5.height: 10
*Transitorio_pb5.labelType: "pixmap"
*Transitorio_pb5.shadowThickness: 1
*Transitorio_pb5.background: "#b0c4de"
*Transitorio_pb5.activateCallback: { attiva_transient();}

*Transitorio_pb6.class: pushButton
*Transitorio_pb6.parent: Transitorio_rc
*Transitorio_pb6.static: false
*Transitorio_pb6.name: Transitorio_pb6
*Transitorio_pb6.x: 3
*Transitorio_pb6.y: 16
*Transitorio_pb6.width: 102
*Transitorio_pb6.height: 29
*Transitorio_pb6.background: "SteelBlue"
*Transitorio_pb6.labelString: "Transient Calc."
*Transitorio_pb6.sensitive: "false"
*Transitorio_pb6.activateCallback: {\
attiva_transient();\
}

*labelNomeModello.class: labelGadget
*labelNomeModello.parent: form1
*labelNomeModello.static: false
*labelNomeModello.name: labelNomeModello
*labelNomeModello.x: 150
*labelNomeModello.y: 10
*labelNomeModello.width: 320
*labelNomeModello.height: 20
*labelNomeModello.alignment: "alignment_center"
*labelNomeModello.labelString: "Model not selected"
*labelNomeModello.fontList: "-adobe-helvetica-medium-r-normal--18-180-75-75-p-98-iso8859-1"
*labelNomeModello.leftAttachment: "attach_form"
*labelNomeModello.leftOffset: 150
*labelNomeModello.topOffset: 20
*labelNomeModello.topPosition: 0

*form3.class: form
*form3.parent: panedWindow1
*form3.static: true
*form3.name: form3
*form3.unitType: "pixels"
*form3.x: 3
*form3.y: 303
*form3.width: 626
*form3.height: 127
*form3.paneMinimum: 135

*labelUtilita.class: labelGadget
*labelUtilita.parent: form3
*labelUtilita.static: true
*labelUtilita.name: labelUtilita
*labelUtilita.x: 0
*labelUtilita.y: 0
*labelUtilita.width: 724
*labelUtilita.height: 25
*labelUtilita.labelString: "Utilities:"
*labelUtilita.topAttachment: "attach_form"
*labelUtilita.topOffset: 0
*labelUtilita.topWidget: ""
*labelUtilita.alignment: "alignment_beginning"

*rowColumn2.class: rowColumn
*rowColumn2.parent: form3
*rowColumn2.static: true
*rowColumn2.name: rowColumn2
*rowColumn2.unitType: "pixels"
*rowColumn2.x: 40
*rowColumn2.y: 25
*rowColumn2.width: 442
*rowColumn2.height: 110
*rowColumn2.orientation: "horizontal"
*rowColumn2.topAttachment: "attach_widget"
*rowColumn2.topWidget: "labelUtilita"
*rowColumn2.spacing: 20
*rowColumn2.leftOffset: 40
*rowColumn2.resizeHeight: "false"

*Librarian_frame3.class: frame
*Librarian_frame3.parent: rowColumn2
*Librarian_frame3.static: true
*Librarian_frame3.name: Librarian_frame3
*Librarian_frame3.x: 3
*Librarian_frame3.y: 3
*Librarian_frame3.width: 85
*Librarian_frame3.height: 97
*Librarian_frame3.shadowType: "shadow_out"

*Librarian_rc.class: rowColumn
*Librarian_rc.parent: Librarian_frame3
*Librarian_rc.static: true
*Librarian_rc.name: Librarian_rc
*Librarian_rc.x: 2
*Librarian_rc.y: 2
*Librarian_rc.width: 83
*Librarian_rc.height: 98
*Librarian_rc.borderWidth: 0
*Librarian_rc.foreground: "darkslategrey"
*Librarian_rc.entryAlignment: "alignment_center"
*Librarian_rc.background: "Steel Blue"

*Librarian_pb1.class: pushButton
*Librarian_pb1.parent: Librarian_rc
*Librarian_pb1.static: true
*Librarian_pb1.name: Librarian_pb1
*Librarian_pb1.x: 5
*Librarian_pb1.y: 0
*Librarian_pb1.width: 75
*Librarian_pb1.height: 10
*Librarian_pb1.labelType: "pixmap"
*Librarian_pb1.shadowThickness: 1
*Librarian_pb1.background: "#b0c4de"
*Librarian_pb1.activateCallback: {\
attiva_librarian();\
}

*Librarian_pb2.class: pushButton
*Librarian_pb2.parent: Librarian_rc
*Librarian_pb2.static: true
*Librarian_pb2.name: Librarian_pb2
*Librarian_pb2.x: 5
*Librarian_pb2.y: 15
*Librarian_pb2.width: 75
*Librarian_pb2.height: 25
*Librarian_pb2.labelString: "Librarian"
*Librarian_pb2.background: "Steel Blue"
*Librarian_pb2.activateCallback: {\
attiva_librarian();\
}

*Grafica_frame.class: frame
*Grafica_frame.parent: rowColumn2
*Grafica_frame.static: true
*Grafica_frame.name: Grafica_frame
*Grafica_frame.x: 3
*Grafica_frame.y: 3
*Grafica_frame.width: 77
*Grafica_frame.height: 94
*Grafica_frame.shadowType: "shadow_out"

*Grafica_rc.class: rowColumn
*Grafica_rc.parent: Grafica_frame
*Grafica_rc.static: true
*Grafica_rc.name: Grafica_rc
*Grafica_rc.x: 2
*Grafica_rc.y: 2
*Grafica_rc.width: 94
*Grafica_rc.height: 103
*Grafica_rc.borderWidth: 0
*Grafica_rc.foreground: "darkslategrey"
*Grafica_rc.entryAlignment: "alignment_center"
*Grafica_rc.background: "#50a0a0"

*Grafica_pb1.class: pushButton
*Grafica_pb1.parent: Grafica_rc
*Grafica_pb1.static: true
*Grafica_pb1.name: Grafica_pb1
*Grafica_pb1.x: 13
*Grafica_pb1.y: 13
*Grafica_pb1.width: 75
*Grafica_pb1.height: 10
*Grafica_pb1.labelType: "pixmap"
*Grafica_pb1.shadowThickness: 1
*Grafica_pb1.background: "#b0c4de"
*Grafica_pb1.activateCallback: {\
attiva_graphics();\
}

*Grafica_pb2.class: pushButton
*Grafica_pb2.parent: Grafica_rc
*Grafica_pb2.static: true
*Grafica_pb2.name: Grafica_pb2
*Grafica_pb2.x: 10
*Grafica_pb2.y: 15
*Grafica_pb2.width: 75
*Grafica_pb2.height: 25
*Grafica_pb2.labelString: "Graph"
*Grafica_pb2.activateCallback: {\
attiva_graphics();\
}
*Grafica_pb2.background: "Cadet Blue"

*Tavole_frame.class: frame
*Tavole_frame.parent: rowColumn2
*Tavole_frame.static: true
*Tavole_frame.name: Tavole_frame
*Tavole_frame.x: 3
*Tavole_frame.y: 3
*Tavole_frame.width: 77
*Tavole_frame.height: 94
*Tavole_frame.shadowType: "shadow_out"

*Tavole_rc.class: rowColumn
*Tavole_rc.parent: Tavole_frame
*Tavole_rc.static: true
*Tavole_rc.name: Tavole_rc
*Tavole_rc.x: 2
*Tavole_rc.y: 2
*Tavole_rc.width: 73
*Tavole_rc.height: 91
*Tavole_rc.borderWidth: 0
*Tavole_rc.foreground: "darkslategrey"
*Tavole_rc.entryAlignment: "alignment_center"
*Tavole_rc.background: "#50a0a0"

*Tavole_pb1.class: pushButton
*Tavole_pb1.parent: Tavole_rc
*Tavole_pb1.static: true
*Tavole_pb1.name: Tavole_pb1
*Tavole_pb1.x: 13
*Tavole_pb1.y: 13
*Tavole_pb1.width: 75
*Tavole_pb1.height: 10
*Tavole_pb1.labelType: "pixmap"
*Tavole_pb1.shadowThickness: 1
*Tavole_pb1.background: "#b0c4de"
*Tavole_pb1.activateCallback: {\
attiva_tables();\
}

*Tavole_pb2.class: pushButton
*Tavole_pb2.parent: Tavole_rc
*Tavole_pb2.static: true
*Tavole_pb2.name: Tavole_pb2
*Tavole_pb2.x: 260
*Tavole_pb2.y: 90
*Tavole_pb2.width: 85
*Tavole_pb2.height: 25
*Tavole_pb2.labelString: "Tables"
*Tavole_pb2.activateCallback: {\
attiva_tables();\
}
*Tavole_pb2.background: "Cadet Blue"

*Documentazione_frame.class: frame
*Documentazione_frame.parent: rowColumn2
*Documentazione_frame.static: true
*Documentazione_frame.name: Documentazione_frame
*Documentazione_frame.x: 3
*Documentazione_frame.y: 3
*Documentazione_frame.width: 77
*Documentazione_frame.height: 94
*Documentazione_frame.shadowType: "shadow_out"

*Documentazione_rc.class: rowColumn
*Documentazione_rc.parent: Documentazione_frame
*Documentazione_rc.static: true
*Documentazione_rc.name: Documentazione_rc
*Documentazione_rc.x: 120
*Documentazione_rc.y: 60
*Documentazione_rc.width: 150
*Documentazione_rc.height: 150
*Documentazione_rc.borderWidth: 0
*Documentazione_rc.foreground: "darkslategrey"
*Documentazione_rc.entryAlignment: "alignment_center"
*Documentazione_rc.background: "Steel Blue"

*Documentazione_pb1.class: pushButton
*Documentazione_pb1.parent: Documentazione_rc
*Documentazione_pb1.static: true
*Documentazione_pb1.name: Documentazione_pb1
*Documentazione_pb1.x: 13
*Documentazione_pb1.y: 13
*Documentazione_pb1.width: 75
*Documentazione_pb1.height: 10
*Documentazione_pb1.labelType: "pixmap"
*Documentazione_pb1.shadowThickness: 1
*Documentazione_pb1.background: "#b0c4de"
*Documentazione_pb1.activateCallback: {\
attiva_autodoc();\
}

*Documentazione_pb2.class: pushButton
*Documentazione_pb2.parent: Documentazione_rc
*Documentazione_pb2.static: true
*Documentazione_pb2.name: Documentazione_pb2
*Documentazione_pb2.x: 365
*Documentazione_pb2.y: 90
*Documentazione_pb2.width: 115
*Documentazione_pb2.height: 25
*Documentazione_pb2.labelString: "Doc"
*Documentazione_pb2.background: "Steel Blue"
*Documentazione_pb2.activateCallback: {\
attiva_autodoc();\
}

*form5.class: form
*form5.parent: panedWindow1
*form5.static: true
*form5.name: form5
*form5.unitType: "pixels"
*form5.x: 3
*form5.y: 435
*form5.width: 629
*form5.height: 200
*form5.allowResize: "true"

*labelMessaggi.class: labelGadget
*labelMessaggi.parent: form5
*labelMessaggi.static: true
*labelMessaggi.name: labelMessaggi
*labelMessaggi.x: 5
*labelMessaggi.y: 1
*labelMessaggi.width: 619
*labelMessaggi.height: 20
*labelMessaggi.labelString: "Messages:"
*labelMessaggi.alignment: "alignment_beginning"

*scrolledWindow3.class: scrolledWindow
*scrolledWindow3.parent: form5
*scrolledWindow3.static: true
*scrolledWindow3.name: scrolledWindow3
*scrolledWindow3.scrollingPolicy: "application_defined"
*scrolledWindow3.unitType: "pixels"
*scrolledWindow3.x: 0
*scrolledWindow3.y: 21
*scrolledWindow3.visualPolicy: "variable"
*scrolledWindow3.scrollBarDisplayPolicy: "static"
*scrolledWindow3.shadowThickness: 0
*scrolledWindow3.bottomAttachment: "attach_form"
*scrolledWindow3.leftOffset: 0
*scrolledWindow3.topAttachment: "attach_widget"
*scrolledWindow3.topOffset: 0
*scrolledWindow3.topWidget: "labelMessaggi"
*scrolledWindow3.width: 250
*scrolledWindow3.height: 150
*scrolledWindow3.rightAttachment: "attach_form"
*scrolledWindow3.leftAttachment: "attach_form"
*scrolledWindow3.rightOffset: 0
*scrolledWindow3.spacing: 2
*scrolledWindow3.resizable: "true"

*messageST.class: scrolledText
*messageST.parent: scrolledWindow3
*messageST.static: false
*messageST.name: messageST
*messageST.width: 612
*messageST.height: 60
*messageST.x: 0
*messageST.y: 0
*messageST.cursorPositionVisible: "false"
*messageST.editable: "false"
*messageST.scrollHorizontal: "true"
*messageST.scrollVertical: "true"
*messageST.resizeHeight: "true"
*messageST.resizeWidth: "true"
*messageST.scrollTopSide: "false"
*messageST.columns: 500
*messageST.editMode: "multi_line_edit"
*messageST.navigationType: "none"

*message_menu.class: rowColumn
*message_menu.parent: messageST
*message_menu.static: true
*message_menu.name: message_menu
*message_menu.rowColumnType: "menu_popup"
*message_menu.menuAccelerator: "<KeyUp>F4"

*menu1_p3_title.class: label
*menu1_p3_title.parent: message_menu
*menu1_p3_title.static: true
*menu1_p3_title.name: menu1_p3_title
*menu1_p3_title.labelString: "MESSAGE"

*message_menu_p1_b2.class: separator
*message_menu_p1_b2.parent: message_menu
*message_menu_p1_b2.static: true
*message_menu_p1_b2.name: message_menu_p1_b2

*menu1_p3_b1.class: pushButton
*menu1_p3_b1.parent: message_menu
*menu1_p3_b1.static: true
*menu1_p3_b1.name: menu1_p3_b1
*menu1_p3_b1.labelString: "Clear Window"
*menu1_p3_b1.mnemonic: "C"
*menu1_p3_b1.activateCallback: {\
extern swidget messageST;\
UxPutText( messageST,"");\
}

