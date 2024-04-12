! UIMX ascii 2.0 key: 2473                                                      

*dati_mainWS.class: applicationShell
*dati_mainWS.parent: NO_PARENT
*dati_mainWS.static: false
*dati_mainWS.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo dati_mainWin.i\
   tipo \
   release 2.15\
   data 4/26/95\
   reserved @(#)dati_mainWin.i	2.15\
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
#include "dati.h"\
/* #include "UxFsBox.h" */\
#include <Xm/Protocols.h>\
#include "f03.h"\
extern int num_note;\
Boolean glob_modified=False;\
int n_editors=0; /* numero di editors aperti */\
/* Include for UxPut calls on the fileSelectionBox */\
\
void CreateWindowManagerProtocols();\
void ExitCB(); \
void CreateSessionManagerProtocols();\
void SaveSessionCB();\
\
extern Boolean saving;  /* declared in file selection box declarations */\
extern Boolean graphics_on;\
extern int stato;\
extern Widget topwidget;\
extern swidget dati_selectionD;\
extern swidget fileSelectionBox;\
extern swidget create_dati_selectionD();\
extern swidget openButton;\
extern swidget saveButton;\
extern swidget exitButton;\
extern swidget variables;\
extern swidget data;\
extern swidget listaBlocchi;\
\
\
#define SEARCH_DOWN  0\
#define SEARCH_UP    1\
#define NO_SEARCH    2
*dati_mainWS.ispecdecl: /* found_item e' utilizzata nella find \
   ed inizializzata nella create\
*/\
int i,found_item,direction;
*dati_mainWS.ispeclist: i, found_item, direction
*dati_mainWS.ispeclist.i: "int", "%i%"
*dati_mainWS.ispeclist.found_item: "int", "%found_item%"
*dati_mainWS.ispeclist.direction: "int", "%direction%"
*dati_mainWS.funcdecl: swidget popup_dati_mainWS()\

*dati_mainWS.funcname: popup_dati_mainWS
*dati_mainWS.funcdef: "swidget", "<popup_dati_mainWS>(%)"
*dati_mainWS.icode:
*dati_mainWS.fcode: create_dati_selectionD(rtrn);\
if(stato==SCELTO)\
	{	\
	update_contatori();\
/*\
 Costruisce la lista dei blocchi appartenenti al modello\
*/\
	for(i=0;i<nbl;i++)\
		{\
		ricostruisci_nome_blocco(nom_bloc[i]);\
		aggiungi_item_n(listaBlocchi,nom_bloc[i],80);\
		}\
        if(graphics_on)\
	   lancia_macro(topwidget,UxGetWidget(listaBlocchi));\
	}\
\
\
\
CreateWindowManagerProtocols(UxGetWidget(rtrn));\
CreateSessionManagerProtocols();\
\
update_pulldown();\
\
found_item =0;\
direction = NO_SEARCH;\
\
UxPopupInterface(rtrn, no_grab);\
return(rtrn);
*dati_mainWS.auxdecl: /******************************************************************\
   This function establishes a protocol callback that detects \
   the window manager Close command.  */\
\
void CreateWindowManagerProtocols(shell)\
     Widget shell;\
{\
  Atom  xa_WM_DELETE_WINDOW;\
\
  xa_WM_DELETE_WINDOW = XInternAtom (UxDisplay, "WM_DELETE_WINDOW", False);\
  XmAddWMProtocolCallback (shell, xa_WM_DELETE_WINDOW, ExitCB, NULL);\
}\
\
\
\
confirm_exit(w,which_button,call_data)\
Widget w;\
int which_button;\
XmAnyCallbackStruct *call_data;\
{\
/*\
 L'utente ha richiesto di uscire dall'applicativo\
*/\
if (which_button == 0)\
	{\
	exit(0);\
	}\
/* Chiudi la window di conferma */\
XtDestroyWidget(w);\
}\
\
\
\
/* This function pops up the Exit dialog box. */\
void ExitCB(w, client_data, call_data)\
     Widget  w;\
     caddr_t client_data;\
     caddr_t call_data;\
{\
extern Widget conferma();\
static Elenco_callback data_agg_callback = {\
        {"Continue", confirm_exit , 0 },\
        {"Cancel", confirm_exit , 1 },\
        {NULL,NULL, 0 }};\
if(glob_modified) /* ci sono state modifiche ed il\
                      file non e' mai stato salvato */\
	conferma(dati_mainWS,\
                 "You have modified Variables values\n but NOT SAVED F14 file !!.\nAll changes WILL BE LOST!!\nContinue?",\
                 data_agg_callback);\
\
else if (n_editors > 0)\
	conferma(dati_mainWS,\
		"Variable and Data editors are already opened\n not applied data shold be LOST !!\n Continue? ",\
		data_agg_callback);\
        	\
else\
	conferma(dati_mainWS,\
		"Do You really want to exit Data Editor?",\
		data_agg_callback);\
\
}\
\
\
/****************************************************************** \
   This function establishes a protocol callback to detect a "save \
   yourself" message from the session manager. */\
\
void CreateSessionManagerProtocols()\
{\
  Atom  xa_WM_SAVE_YOURSELF;\
  \
  xa_WM_SAVE_YOURSELF = XInternAtom (UxDisplay, "WM_SAVE_YOURSELF", False);\
  XmAddWMProtocolCallback (UxTopLevel, xa_WM_SAVE_YOURSELF, SaveSessionCB, NULL);\
}\
\
\
/*****************************************************************\
   This callback function is executed whenever this application \
   receives a "save yourself" callback from the session manager. */\
\
void SaveSessionCB()\
{\
\
  printf("The session manager is saving a session ...\n");\
  printf(" ... (New Application) should save itself now!\n");\
\
}\
\
/*\
 update_pulldown\
	abilita e/o disabilita i bottoni costituenti il\
	pulldown menu a seconda dello stato del programma\
*/\
update_pulldown()\
{\
if(stato == NON_SCELTO)\
	{\
	UxPutSensitive(openButton,"true");\
	UxPutSensitive(saveButton,"false");\
	UxPutSensitive(saveAsButton,"false");\
	UxPutSensitive(exitButton,"true");\
\
	UxPutSensitive(variables,"false");\
	UxPutSensitive(data,"false");\
	UxPutSensitive(normal,"false");\
	}\
else if(stato == SCELTO)\
	{\
	UxPutSensitive(openButton,"false");\
	UxPutSensitive(saveButton,"true");\
	UxPutSensitive(saveAsButton,"true");\
	UxPutSensitive(exitButton,"true");\
\
	UxPutSensitive(variables,"true");\
	UxPutSensitive(data,"true");\
	UxPutSensitive(normal,"true");\
	}\
}\
\
/*\
 update_contatori\
	aggiorna i valori dei contatori di numero di\
	eqz.,numero variabili note, numero var non\
        note,numero variabili in ingresso.\
*/\
update_contatori()\
{\
char app[10];\
sprintf(app,"%d",neqsis);\
UxPutLabelString(label_equation,app);\
sprintf(app,"%d",nu);\
UxPutLabelString(label_input,app);\
sprintf(app,"%d",num_note);\
UxPutLabelString(label_known,app);\
sprintf(app,"%d",(neqsis+nu-num_note));\
UxPutLabelString(label_unknown,app);\
}\
\

*dati_mainWS.name: dati_mainWS
*dati_mainWS.x: 768
*dati_mainWS.y: 205
*dati_mainWS.width: 490
*dati_mainWS.height: 470
*dati_mainWS.title: "Data Editing"
*dati_mainWS.deleteResponse: "do_nothing"
*dati_mainWS.keyboardFocusPolicy.source: public
*dati_mainWS.keyboardFocusPolicy: "explicit"
*dati_mainWS.iconName: "Data Editing"
*dati_mainWS.minHeight: 340
*dati_mainWS.minWidth: 490

*mainWindow.class: mainWindow
*mainWindow.parent: dati_mainWS
*mainWindow.static: true
*mainWindow.name: mainWindow
*mainWindow.x: 200
*mainWindow.y: 180
*mainWindow.width: 490
*mainWindow.height: 470

*workAreaForm.class: form
*workAreaForm.parent: mainWindow
*workAreaForm.static: true
*workAreaForm.name: workAreaForm
*workAreaForm.width: 490
*workAreaForm.height: 340
*workAreaForm.borderWidth: 0

*FindText.class: textField
*FindText.parent: workAreaForm
*FindText.static: false
*FindText.name: FindText
*FindText.x: 10
*FindText.y: 570
*FindText.width: 200
*FindText.height: 41
*FindText.bottomAttachment: "attach_form"
*FindText.bottomOffset: 10
*FindText.leftOffset: 45
*FindText.columns: 15

*workAreaFrame.class: frame
*workAreaFrame.parent: workAreaForm
*workAreaFrame.static: true
*workAreaFrame.name: workAreaFrame
*workAreaFrame.x: 50
*workAreaFrame.y: 30
*workAreaFrame.width: 390
*workAreaFrame.height: 230
*workAreaFrame.bottomAttachment: "attach_widget"
*workAreaFrame.bottomOffset: 10
*workAreaFrame.leftAttachment: "attach_form"
*workAreaFrame.leftOffset.source: public
*workAreaFrame.leftOffset: 10
*workAreaFrame.rightAttachment: "attach_form"
*workAreaFrame.rightOffset.source: public
*workAreaFrame.rightOffset: 10
*workAreaFrame.topAttachment: "attach_form"
*workAreaFrame.topOffset.source: public
*workAreaFrame.topOffset: 10
*workAreaFrame.bottomWidget: "FindText"

*workArea.class: form
*workArea.parent: workAreaFrame
*workArea.static: true
*workArea.name: workArea
*workArea.x: 10
*workArea.y: 2
*workArea.width: 542
*workArea.height: 518
*workArea.borderWidth: 0

*labelModelDati.class: labelGadget
*labelModelDati.parent: workArea
*labelModelDati.static: false
*labelModelDati.name: labelModelDati
*labelModelDati.x: 120
*labelModelDati.y: 10
*labelModelDati.width: 260
*labelModelDati.height: 30
*labelModelDati.fontList: "-adobe-helvetica-medium-r-normal--18-180-75-75-p-98-iso8859-1"
*labelModelDati.labelString: "Model not selected"
*labelModelDati.borderWidth: 4
*labelModelDati.shadowThickness: 0
*labelModelDati.rightAttachment: "attach_form"
*labelModelDati.rightOffset: 10
*labelModelDati.leftAttachment: "attach_form"
*labelModelDati.leftOffset: 10
*labelModelDati.createCallback: {\
/* Commento */\
extern char *estr_nome_modello();\
extern char *str_toupper();\
extern int stato;\
char path[120];\
char str2[120];\
char *nome_modello;\
if(stato==SCELTO)\
	{\
	getwd(path);\
	nome_modello=estr_nome_modello(path);\
	str_toupper(nome_modello);\
	sprintf(str2,"Model name: %s",nome_modello);\
	UxPutLabelString(UxWidget,str2);\
	}\
}

*form1.class: form
*form1.parent: workArea
*form1.static: true
*form1.name: form1
*form1.resizePolicy: "resize_none"
*form1.x: 20
*form1.y: 50
*form1.width: 630
*form1.height: 70
*form1.allowOverlap: "false"
*form1.rightAttachment: "attach_form"
*form1.rightOffset: 20
*form1.leftAttachment: "attach_form"
*form1.leftOffset: 20

*n_eqz_label.class: label
*n_eqz_label.parent: form1
*n_eqz_label.static: true
*n_eqz_label.name: n_eqz_label
*n_eqz_label.x: 0
*n_eqz_label.y: 0
*n_eqz_label.width: 116
*n_eqz_label.height: 36
*n_eqz_label.leftOffset: 0
*n_eqz_label.rightAttachment: "attach_position"
*n_eqz_label.rightPosition: 25
*n_eqz_label.leftAttachment: "attach_form"
*n_eqz_label.labelString: "equations"

*n_ing_label.class: label
*n_ing_label.parent: form1
*n_ing_label.static: true
*n_ing_label.name: n_ing_label
*n_ing_label.x: 270
*n_ing_label.y: 0
*n_ing_label.width: 175
*n_ing_label.height: 35
*n_ing_label.leftAttachment: "attach_position"
*n_ing_label.leftOffset: 0
*n_ing_label.leftPosition: 50
*n_ing_label.rightAttachment: "attach_position"
*n_ing_label.rightPosition: 75
*n_ing_label.labelString: "input var."

*n_note_label.class: label
*n_note_label.parent: form1
*n_note_label.static: true
*n_note_label.name: n_note_label
*n_note_label.x: 480
*n_note_label.y: 0
*n_note_label.width: 120
*n_note_label.height: 36
*n_note_label.leftAttachment: "attach_position"
*n_note_label.leftOffset: 0
*n_note_label.leftPosition: 75
*n_note_label.rightAttachment: "attach_form"
*n_note_label.labelString: "known var."

*n_inc_label.class: label
*n_inc_label.parent: form1
*n_inc_label.static: true
*n_inc_label.name: n_inc_label
*n_inc_label.x: 180
*n_inc_label.y: 0
*n_inc_label.width: 140
*n_inc_label.height: 36
*n_inc_label.leftAttachment: "attach_position"
*n_inc_label.leftOffset: 0
*n_inc_label.leftPosition: 25
*n_inc_label.rightAttachment: "attach_position"
*n_inc_label.rightPosition: 50
*n_inc_label.labelString: "unknown var."

*label_equation.class: label
*label_equation.parent: form1
*label_equation.static: false
*label_equation.name: label_equation
*label_equation.x: 10
*label_equation.y: 30
*label_equation.width: 80
*label_equation.height: 30
*label_equation.borderWidth: 2
*label_equation.leftOffset: 2
*label_equation.rightAttachment: "attach_position"
*label_equation.rightOffset: 0
*label_equation.topAttachment: "attach_widget"
*label_equation.topOffset: 0
*label_equation.topWidget: "n_eqz_label"
*label_equation.rightPosition: 23
*label_equation.leftAttachment: "attach_position"
*label_equation.labelString: "0"
*label_equation.bottomAttachment: "attach_form"

*label_unknown.class: label
*label_unknown.parent: form1
*label_unknown.static: false
*label_unknown.name: label_unknown
*label_unknown.x: 110
*label_unknown.y: 30
*label_unknown.width: 80
*label_unknown.height: 30
*label_unknown.borderWidth: 2
*label_unknown.bottomAttachment: "attach_form"
*label_unknown.topAttachment: "attach_widget"
*label_unknown.topOffset: 0
*label_unknown.topWidget: "n_eqz_label"
*label_unknown.leftAttachment: "attach_position"
*label_unknown.leftOffset: 0
*label_unknown.leftPosition: 27
*label_unknown.rightAttachment: "attach_position"
*label_unknown.rightPosition: 48
*label_unknown.labelString: "0"

*label_input.class: label
*label_input.parent: form1
*label_input.static: false
*label_input.name: label_input
*label_input.x: 210
*label_input.y: 30
*label_input.width: 80
*label_input.height: 30
*label_input.borderWidth: 2
*label_input.bottomAttachment: "attach_form"
*label_input.topAttachment: "attach_widget"
*label_input.topOffset: 0
*label_input.topWidget: "n_eqz_label"
*label_input.leftAttachment: "attach_position"
*label_input.leftOffset: 0
*label_input.leftPosition: 52
*label_input.rightAttachment: "attach_position"
*label_input.rightPosition: 73
*label_input.labelString: "0"

*label_known.class: label
*label_known.parent: form1
*label_known.static: false
*label_known.name: label_known
*label_known.x: 300
*label_known.y: 30
*label_known.width: 80
*label_known.height: 30
*label_known.borderWidth: 2
*label_known.bottomAttachment: "attach_form"
*label_known.topAttachment: "attach_widget"
*label_known.topOffset: 0
*label_known.topWidget: "n_eqz_label"
*label_known.leftAttachment: "attach_position"
*label_known.leftOffset: 0
*label_known.leftPosition: 77
*label_known.rightAttachment: "attach_position"
*label_known.rightPosition: 98
*label_known.labelString: "0"

*scrolledWindow3.class: scrolledWindow
*scrolledWindow3.parent: workArea
*scrolledWindow3.static: true
*scrolledWindow3.name: scrolledWindow3
*scrolledWindow3.scrollingPolicy: "application_defined"
*scrolledWindow3.x: 40
*scrolledWindow3.y: 160
*scrolledWindow3.visualPolicy: "variable"
*scrolledWindow3.scrollBarDisplayPolicy: "static"
*scrolledWindow3.shadowThickness: 0
*scrolledWindow3.rightAttachment: "attach_form"
*scrolledWindow3.rightOffset: 40
*scrolledWindow3.bottomAttachment: "attach_form"
*scrolledWindow3.bottomOffset: 20
*scrolledWindow3.leftAttachment: "attach_form"
*scrolledWindow3.leftOffset: 40
*scrolledWindow3.topAttachment: "attach_widget"
*scrolledWindow3.topWidget: "form1"
*scrolledWindow3.topOffset: 40

*listaBlocchi.class: scrolledList
*listaBlocchi.parent: scrolledWindow3
*listaBlocchi.static: false
*listaBlocchi.name: listaBlocchi
*listaBlocchi.width: 386
*listaBlocchi.height: 100
*listaBlocchi.selectionPolicy: "extended_select"
*listaBlocchi.scrollBarDisplayPolicy: "as_needed"
*listaBlocchi.visibleItemCount: 30
*listaBlocchi.listSizePolicy: "constant"
*listaBlocchi.singleSelectionCallback: {\
\
}
*listaBlocchi.multipleSelectionCallback: {\
\
}
*listaBlocchi.extendedSelectionCallback: {\
int j;\
extern char *extract_string();\
extern Boolean graphics_on;\
char *nome_blocco;\
XmListCallbackStruct *s_lista;\
/*\
 Se non e' selezionata la grafica esce\
*/\
if(graphics_on == False)\
	return;\
/*\
 Seleziona sullo schema grafico i blocchi corrispondenti\
 a quelli selezionati in lista\
*/\
\
s_lista=(XmListCallbackStruct *)UxCallbackArg;\
/*\
 Deseleziona tutti i blocchi in tutte le pagine \
 solo se la pagina grafica e' aperta\
*/\
/* test aggiunto 21-4-95 (Micheletti) */\
if( macro_is_open() )\
	{\
	deselez_all_graf();\
	for(j=0;j<s_lista->selected_item_count;j++)\
		{\
		nome_blocco=extract_string(s_lista->selected_items[j]);\
		nome_blocco[8]='\0';\
		selgraf_blocco(nome_blocco,True);\
		XtFree(nome_blocco);\
		}\
	}\
\
}

*label1.class: label
*label1.parent: workArea
*label1.static: true
*label1.name: label1
*label1.x: 40
*label1.y: 80
*label1.width: 380
*label1.height: 20
*label1.bottomAttachment: "attach_widget"
*label1.bottomWidget: "scrolledWindow3"
*label1.labelString: "Blocks in model"
*label1.rightAttachment: "attach_form"
*label1.rightOffset: 40
*label1.topAttachment: "attach_none"
*label1.leftAttachment: "attach_form"
*label1.leftOffset: 40

*FindDownButton.class: arrowButton
*FindDownButton.parent: workAreaForm
*FindDownButton.static: true
*FindDownButton.name: FindDownButton
*FindDownButton.x: 220
*FindDownButton.y: 570
*FindDownButton.width: 30
*FindDownButton.height: 30
*FindDownButton.activateCallback: {\
/* search down */\
\
extern char **nom_bloc;\
char **lista;\
int num_item,inizio;\
char textsearch[85];\
\
/* stringa da ricercare */\
strcpy(textsearch,UxGetText(FindText));\
tominus( trim_blank(textsearch) );\
\
if( strlen(textsearch)  )   \
{\
   printf("search for text %s\n",textsearch);\
   \
/* costruisco la lista di riferimento */\
\
   get_something(UxGetWidget(listaBlocchi),XmNitemCount,&num_item);\
   lista    = (char **) calloc( num_item, sizeof(char *));\
   for(i=0;i<num_item;i++)\
   {\
      lista[i] = (char *) calloc( nbl, (sizeof(char) * 80) );\
      memcpy(lista[i],nom_bloc[i],80);\
      tominus( trim_blank(lista[i]) );\
   }\
\
/* effettuo la ricerca */\
\
   if(direction == SEARCH_UP)\
       inizio = found_item+1;\
   else\
       inizio = found_item;\
\
   direction = SEARCH_DOWN;\
   \
   for( i=inizio; i<num_item; i++)\
   {\
      if( strstr(lista[i],textsearch) != NULL)\
      {\
         printf("found text in item %d\n",i+1);\
/* seleziono il blocco e incremento il contatore */\
         found_item = i+1;\
         XmListSelectPos(UxGetWidget(listaBlocchi),found_item,True);\
         XmListSetPos(UxGetWidget(listaBlocchi),found_item);\
         UxPutLabelString(foundLabel,"         ");\
         break;\
      }\
      else\
      {\
         printf("text not found\n");\
         UxPutLabelString(foundLabel,"Not Found");\
      }\
   }\
}                    \
   \
\
}
*FindDownButton.bottomAttachment: "attach_form"
*FindDownButton.bottomOffset: 10
*FindDownButton.topAttachment: "attach_widget"
*FindDownButton.topOffset: 10
*FindDownButton.topWidget: "workAreaFrame"
*FindDownButton.leftAttachment: "attach_widget"
*FindDownButton.leftOffset: 5
*FindDownButton.leftWidget: "FindText"
*FindDownButton.arrowDirection: "arrow_down"

*FindUpButton.class: arrowButton
*FindUpButton.parent: workAreaForm
*FindUpButton.static: true
*FindUpButton.name: FindUpButton
*FindUpButton.x: 250
*FindUpButton.y: 570
*FindUpButton.width: 30
*FindUpButton.height: 30
*FindUpButton.arrowDirection: "arrow_up"
*FindUpButton.bottomAttachment: "attach_form"
*FindUpButton.bottomOffset: 10
*FindUpButton.topAttachment: "attach_widget"
*FindUpButton.topOffset: 10
*FindUpButton.topWidget: "workAreaFrame"
*FindUpButton.leftAttachment: "attach_widget"
*FindUpButton.leftOffset: 1
*FindUpButton.leftWidget: "FindDownButton"
*FindUpButton.activateCallback: {\
/*search up */\
\
extern char **nom_bloc;\
char **lista;\
int num_item,inizio;\
char textsearch[85];\
\
/* stringa da ricercare */\
strcpy(textsearch,UxGetText(FindText));\
tominus( trim_blank(textsearch) );\
\
if( strlen(textsearch)  )   \
{\
   printf("search for text %s\n",textsearch);\
\
/* acquisisco il numero di item in lista */\
 \
   get_something(UxGetWidget(listaBlocchi),XmNitemCount,&num_item);   \
   lista = (char **) calloc( num_item, sizeof(char *));\
   for(i=0;i<num_item;i++)\
   {\
      lista[i] = (char *) calloc( nbl, (sizeof(char) * 80) );\
      memcpy(lista[i],nom_bloc[i],80);\
      tominus( trim_blank(lista[i]) );\
   }\
\
/* effettuo la ricerca */\
\
  \
   if(direction == SEARCH_DOWN)\
      inizio = found_item -1;\
   else\
      inizio = found_item;\
\
   direction = SEARCH_UP;\
   \
   for( i=inizio; i > 0; i--)\
   {\
      int ind;\
      ind = i-1;\
\
      if( strstr(lista[ind],textsearch) != NULL)\
      {\
         printf("found text in item %d\n",i);\
         found_item=ind;\
         XmListSelectPos(UxGetWidget(listaBlocchi),i,True);\
         XmListSetPos(UxGetWidget(listaBlocchi),i);\
         UxPutLabelString(foundLabel,"         ");\
         break;     \
      }\
      else\
      {\
         printf("text not found\n");\
         UxPutLabelString(foundLabel,"Not Found");\
      } \
   }\
}                    \
 \
 \
}

*foundLabel.class: label
*foundLabel.parent: workAreaForm
*foundLabel.static: false
*foundLabel.name: foundLabel
*foundLabel.x: 290
*foundLabel.y: 260
*foundLabel.width: 100
*foundLabel.height: 30
*foundLabel.bottomAttachment: "attach_form"
*foundLabel.bottomOffset: 10
*foundLabel.leftAttachment: "attach_widget"
*foundLabel.leftOffset: 10
*foundLabel.leftWidget: "FindUpButton"
*foundLabel.topAttachment: "attach_widget"
*foundLabel.topOffset: 10
*foundLabel.topWidget: "workAreaFrame"
*foundLabel.labelString: ""

*pullDownMenu.class: rowColumn
*pullDownMenu.parent: mainWindow
*pullDownMenu.static: true
*pullDownMenu.name: pullDownMenu
*pullDownMenu.borderWidth: 0
*pullDownMenu.menuHelpWidget: "helpCascade"
*pullDownMenu.rowColumnType: "menu_bar"
*pullDownMenu.menuAccelerator: "<KeyUp>F10"

*filePane.class: rowColumn
*filePane.parent: pullDownMenu
*filePane.static: true
*filePane.name: filePane
*filePane.rowColumnType: "menu_pulldown"

*openButton.class: pushButtonGadget
*openButton.parent: filePane
*openButton.static: true
*openButton.name: openButton
*openButton.labelString: "Open ..."
*openButton.mnemonic: "O"
*openButton.activateCallback: {\
   /* Clear "saving" flag, then display file selection box. */\
   saving = False; \
   UxPutTitle(dati_selectionD, "Data editor - Open");\
   UxPutSelectionLabelString(fileSelectionBox, "Model to Open");\
   UxPopupInterface(dati_selectionD, no_grab); \
}

*filePane_b7.class: separatorGadget
*filePane_b7.parent: filePane
*filePane_b7.static: true
*filePane_b7.name: filePane_b7

*saveButton.class: pushButtonGadget
*saveButton.parent: filePane
*saveButton.static: true
*saveButton.name: saveButton
*saveButton.labelString: "Save"
*saveButton.mnemonic: "S"
*saveButton.activateCallback: {\
extern swidget create_vis_msg();\
char str[50];\
FILE *fp_f14;\
fp_f14=fopen("f14.dat","w");\
if(fp_f14)\
	{\
	write_file_f14(fp_f14);\
	fclose(fp_f14);\
	sprintf(str,"file F14 successfully saved");\
	glob_modified=False;\
	}\
else\
	{\
	sprintf(str,"Cannot write file F14");\
	}\
create_vis_msg(str);\
}

*saveAsButton.class: pushButtonGadget
*saveAsButton.parent: filePane
*saveAsButton.static: true
*saveAsButton.name: saveAsButton
*saveAsButton.labelString: "Save As ..."
*saveAsButton.mnemonic: "A"
*saveAsButton.activateCallback: {\
/* Set "saving" flag, then display file selection box. */\
saving = True;\
UxPutTitle(dati_selectionD, "Data editor - Save As");\
UxPutSelectionLabelString(fileSelectionBox, "File to Save");\
UxPutFileTypeMask(fileSelectionBox,"file_regular");\
UxPutFileListLabelString(fileSelectionBox,"Files");\
UxPutPattern(fileSelectionBox,"*.dat");\
   \
UxPopupInterface(dati_selectionD, no_grab); \
}

*filePane_b8.class: separatorGadget
*filePane_b8.parent: filePane
*filePane_b8.static: true
*filePane_b8.name: filePane_b8

*exitButton.class: pushButtonGadget
*exitButton.parent: filePane
*exitButton.static: true
*exitButton.name: exitButton
*exitButton.labelString: "Exit"
*exitButton.mnemonic: "E"
*exitButton.activateCallback: {\
extern Widget conferma();\
static Elenco_callback data_agg_callback = {\
        {"Continue", confirm_exit , 0 },\
        {"Cancel", confirm_exit , 1 },\
        {NULL,NULL, 0 }};\
if(glob_modified) /* ci sono state modifiche ed il\
                      file non e' mai stato salvato */\
	conferma(dati_mainWS,\
                 "You have modified Variables values\n but NOT SAVED F14 file !!.\nAll changes WILL BE LOST!!\nContinue?",\
                 data_agg_callback);\
\
else if (n_editors > 0)\
	conferma(dati_mainWS,\
		"Variable and Data editors are already opened\n not applied data shold be LOST !!\n Continue? ",\
		data_agg_callback);\
        	\
else\
	conferma(dati_mainWS,\
		"Do You really want to exit Data Editor?",\
		data_agg_callback);\
}

*editPane.class: rowColumn
*editPane.parent: pullDownMenu
*editPane.static: true
*editPane.name: editPane
*editPane.rowColumnType: "menu_pulldown"

*variables.class: pushButtonGadget
*variables.parent: editPane
*variables.static: true
*variables.name: variables
*variables.labelString: "Variables..."
*variables.mnemonic: "V"
*variables.activateCallback: {\
/* prepara la form dialog di editing per le variabili */\
extern swidget popup_vardata();\
n_editors++;\
popup_vardata(ALL_VAR);\
  printf("Edit variabili\n");\
}

*data.class: pushButtonGadget
*data.parent: editPane
*data.static: true
*data.name: data
*data.labelString: "Data..."
*data.mnemonic: "D"
*data.activateCallback: {\
printf("visualizzazione dati \n");\
/* prepara la form per la visualizzazione dei dati geometrici e\
   fisici dei blocchi */\
n_editors++;\
popup_vardata(ALL_DATA);\
}

*editPane_b6.class: separatorGadget
*editPane_b6.parent: editPane
*editPane_b6.static: true
*editPane_b6.name: editPane_b6

*normal.class: pushButtonGadget
*normal.parent: editPane
*normal.static: true
*normal.name: normal
*normal.labelString: "Normalization..."
*normal.mnemonic: "N"
*normal.activateCallback: {\
extern swidget popup_NormParamDialog();  \
popup_NormParamDialog(); \
}

*helpPane.class: rowColumn
*helpPane.parent: pullDownMenu
*helpPane.static: true
*helpPane.name: helpPane
*helpPane.rowColumnType: "menu_pulldown"

*onContextButton.class: pushButtonGadget
*onContextButton.parent: helpPane
*onContextButton.static: true
*onContextButton.name: onContextButton
*onContextButton.labelString: "On Dati application ..."
*onContextButton.mnemonic: "C"
*onContextButton.activateCallback.source: public
*onContextButton.activateCallback: 

*helpPane_b9.class: separatorGadget
*helpPane_b9.parent: helpPane
*helpPane_b9.static: true
*helpPane_b9.name: helpPane_b9

*onVersionButton.class: pushButtonGadget
*onVersionButton.parent: helpPane
*onVersionButton.static: true
*onVersionButton.name: onVersionButton
*onVersionButton.labelString: "On Version ..."
*onVersionButton.mnemonic: "V"
*onVersionButton.activateCallback.source: public
*onVersionButton.activateCallback: 

*fileCascade.class: cascadeButton
*fileCascade.parent: pullDownMenu
*fileCascade.static: true
*fileCascade.name: fileCascade
*fileCascade.labelString: "File"
*fileCascade.mnemonic: "F"
*fileCascade.subMenuId: "filePane"

*editCascade.class: cascadeButton
*editCascade.parent: pullDownMenu
*editCascade.static: true
*editCascade.name: editCascade
*editCascade.labelString: "Edit"
*editCascade.mnemonic: "E"
*editCascade.subMenuId: "editPane"

*helpCascade.class: cascadeButton
*helpCascade.parent: pullDownMenu
*helpCascade.static: true
*helpCascade.name: helpCascade
*helpCascade.labelString: "Help"
*helpCascade.mnemonic: "H"
*helpCascade.subMenuId: "helpPane"

