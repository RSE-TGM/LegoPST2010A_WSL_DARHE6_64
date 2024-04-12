! UIMX ascii 2.0 key: 5136                                                      

*Menu_graf.class: topLevelShell
*Menu_graf.parent: NO_PARENT
*Menu_graf.static: false
*Menu_graf.gbldecl: #ifndef DESIGN_TIME\
/*\
   modulo Menu_graf.i\
   tipo \
   release 1.10\
   data 3/28/95\
   reserved @(#)Menu_graf.i	1.10\
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
#include <Xm/Xm.h>\
#include <grsf22.h>\
#include "menu_graf.h"\
\
/* Widget della finestra per la funzione Extract,Cut,Shift del tempo */\
extern swidget Edit_Time_Win;\
extern swidget Edt_start_time;\
extern swidget Edt_stop_time;\
extern swidget textField_Stop;\
extern swidget textField_Start;\
extern swidget Titolo_edit;\
extern swidget Etichetta_start;\
extern swidget Etichetta_stop;\
/* Widget della finestra di uscita dalla Menu_graf */\
extern swidget Menu_graf_exit;\
extern swidget label_output;\
/* Widget della finestra per il cambio della descrizione della variabile  */\
extern swidget Description;\
extern swidget labelDescription;\
extern swidget labelNomevar;\
extern swidget textDescription;\
extern swidget textNomevar;\
/* Widget della finestra per il salvataggio del file */\
extern swidget create_File_Save();\
extern swidget name_save;\
/* Widget vari  */\
extern swidget create_SimulationTitle();\
extern swidget create_FilterWindow();\
extern swidget fileSelectionBox1;\
extern swidget create_fileSelectionBox1();\
extern swidget CalcWindow;\
extern swidget create_CalcWindow();\
extern swidget Message;\
extern swidget Sampling;\
extern swidget Resampling;\
\
/* Variabile per identificazione tipo di find  */\
extern int Find_sel;\
/* Variabile per identificazione salvataggio effettuato */\
extern int Salvato;\
/* Variabile per identificazione modifiche apportate */\
extern int Modifica;\
/* Variabile per identificazione nome file destinatario assegnato */\
extern int nome_valido;\
/* Funzione per la lettura della directory di lavoro */\
extern char *getcwd();\
/* Identificazione del processo di grafics */\
extern int pid;\
/* Variabili di uso vario */\
extern int Scelta;\
extern char *Nomefile;\
extern char Path_appo[];\
extern int campioni;\
extern FILE *fpAPPO,*fpDAT;\
\
extern FILE *fpELENCO;\
\
/* Stringhe delle etichette della MainWindow  */\
XmString label_start_time,label_stop_time,label_path_f22;\
XmString label_delta_campioni,label_numero_campioni,label_num_var;\
\
char nomi_var [NUM_VAR+1][LUN_NOME+1];\
\
int TypeCalc;                       /*  Tipo di operazione da eseguire\
					 sulle var  */\
int Input_Message;\
\
int trovata,i,j;\
float t_iniziale,t_finale;  	    /* Tempi della simulazione registrata\
						 su f22  */\
S_SEL_DATI bufdati[NUM_VAR];\
S_HEAD1 header1;		    /*  Primo header letto da f22  */\
S_HEAD2 header2;   		    /*  Secondo header letto da f22  */\
char *s_app,nomevariabile[9];\
char **simboli,*descriz;\
int indice,n_last,Clip_id;\
char *path_22dat,f22source[50],f22target[50],f22undo[50]; /* Path_name f22 */\
XmString *x_simboli;\
/* Dichiarazione variabili per uso Clipboard  */\
XmString nome_clip;\
char *Stringa_clip,**lista_varClip,*path_22datClip;\
float delta_nuovoClip,t_inizialeClip,t_finaleClip;\
int numeroClip;
*Menu_graf.ispecdecl:
*Menu_graf.funcdecl: swidget create_Menu_graf()\

*Menu_graf.funcname: create_Menu_graf
*Menu_graf.funcdef: "swidget", "<create_Menu_graf>(%)"
*Menu_graf.icode:
*Menu_graf.fcode: return(rtrn);\

*Menu_graf.auxdecl:
*Menu_graf.name: Menu_graf
*Menu_graf.x: 32
*Menu_graf.y: 0
*Menu_graf.width: 542
*Menu_graf.height: 645
*Menu_graf.minHeight: 400
*Menu_graf.minWidth: 500

*f22_modify.class: mainWindow
*f22_modify.parent: Menu_graf
*f22_modify.static: true
*f22_modify.name: f22_modify
*f22_modify.unitType: "pixels"
*f22_modify.width: 542
*f22_modify.height: 645
*f22_modify.x: 200
*f22_modify.y: 0

*menu1.class: rowColumn
*menu1.parent: f22_modify
*menu1.static: true
*menu1.name: menu1
*menu1.rowColumnType: "menu_bar"
*menu1.menuAccelerator: "<KeyUp>F10"

*FilePane.class: rowColumn
*FilePane.parent: menu1
*FilePane.static: true
*FilePane.name: FilePane
*FilePane.rowColumnType: "menu_pulldown"

*LoadItem.class: pushButton
*LoadItem.parent: FilePane
*LoadItem.static: false
*LoadItem.name: LoadItem
*LoadItem.labelString: "Load.."
*LoadItem.mnemonic: "L"
*LoadItem.activateCallback: {\
XmString Messaggio;\
char stringa[100];\
Position PosX,PosY;\
 \
if (Salvato == 0)\
	{\
	Input_Message = 1;\
	strcpy (stringa,"Changes not saved!Continue load?\0");\
	Messaggio = XmStringCreate (stringa,XmSTRING_DEFAULT_CHARSET);\
	set_something (Message,XmNdialogType, XmDIALOG_WARNING);\
	set_something (Message, XmNmessageString, Messaggio);\
	UxPopupInterface (Message,no_grab);\
	XmStringFree (Messaggio);\
	}\
if (Salvato == 1)\
	{\
	fileSelectionBox1 = create_fileSelectionBox1();\
	get_something (Menu_graf, XmNx, &PosX);\
	get_something (Menu_graf, XmNy, &PosY);\
	set_something (fileSelectionBox1, XmNx, PosX+10);\
	set_something (fileSelectionBox1, XmNy, PosY+10);\
	UxPopupInterface(fileSelectionBox1,no_grab);\
	}\
}

*SaveItem.class: pushButton
*SaveItem.parent: FilePane
*SaveItem.static: false
*SaveItem.name: SaveItem
*SaveItem.labelString: "Save"
*SaveItem.mnemonic: "S"
*SaveItem.sensitive: "false"
*SaveItem.activateCallback: {\
char cdo[100];\
Position PosX,PosY;\
\
if ((nome_valido == 1) && (Modifica == 1))\
	{\
	strcpy (cdo,"cp ");\
	strcat (cdo,f22source);\
	strcat (cdo," ");\
	strcat (cdo,Nomefile);\
	system (cdo);\
	Modifica = 0;\
	}\
else\
	{\
	if (nome_valido != 1) \
		{\
		get_something (Menu_graf, XmNx, &PosX);\
		get_something (Menu_graf, XmNy, &PosY);\
		UxPopupInterface (create_File_Save(NORMAL_SAVE,PosX,PosY,f22source), no_grab);\
		}\
	}\
}

*Save_asItem.class: pushButton
*Save_asItem.parent: FilePane
*Save_asItem.static: false
*Save_asItem.name: Save_asItem
*Save_asItem.labelString: "Save As.."
*Save_asItem.mnemonic: "A"
*Save_asItem.sensitive: "false"
*Save_asItem.activateCallback: {\
Position PosX,PosY;\
\
get_something (Menu_graf, XmNx, &PosX);\
get_something (Menu_graf, XmNy, &PosY);\
UxPopupInterface (create_File_Save(NORMAL_SAVE,PosX,PosY,f22source), no_grab);\
}

*Separatore1.class: separator
*Separatore1.parent: FilePane
*Separatore1.static: true
*Separatore1.name: Separatore1

*AsciiItem.class: pushButton
*AsciiItem.parent: FilePane
*AsciiItem.static: false
*AsciiItem.name: AsciiItem
*AsciiItem.labelString: "Ascii save.."
*AsciiItem.mnemonic: "s"
*AsciiItem.sensitive: "false"
*AsciiItem.activateCallback: {\
int *ListaSele,NumSele,selezione;\
XmString Messaggio;\
char stringa[100],*pathAscii;\
Position PosX,PosY;\
\
selezione = XmListGetSelectedPos (lista_var, &ListaSele, &NumSele);\
if (selezione)\
	{\
	if (NumSele > MAX_VAR_RECORDED)\
		{\
	        strcpy (stringa,"Max selectable variables superated\0");\
        	Messaggio = XmStringCreate (stringa,XmSTRING_DEFAULT_CHARSET);\
	        set_something (Message, XmNdialogType, XmDIALOG_INFORMATION);\
	        set_something (Message, XmNmessageString, Messaggio);\
	        UxPopupInterface (Message,no_grab);\
	        XmStringFree (Messaggio);\
		}\
	else\
		{\
		pathAscii = SalvaInAscii (ListaSele,NumSele);\
		get_something (Menu_graf, XmNx, &PosX);\
		get_something (Menu_graf, XmNy, &PosY);\
		UxPopupInterface (create_File_Save(ASCII_SAVE,PosX,PosY,pathAscii),\
					no_grab);\
		}\
	}\
else\
	{\
        strcpy (stringa,"Must be selected at least one item\0");\
        Messaggio = XmStringCreate (stringa,XmSTRING_DEFAULT_CHARSET);\
        set_something (Message, XmNdialogType, XmDIALOG_INFORMATION);\
        set_something (Message, XmNmessageString, Messaggio);\
        UxPopupInterface (Message,no_grab);\
        XmStringFree (Messaggio);\
	}\
}

*Separatore2.class: separator
*Separatore2.parent: FilePane
*Separatore2.static: true
*Separatore2.name: Separatore2

*UndoItem.class: pushButton
*UndoItem.parent: FilePane
*UndoItem.static: false
*UndoItem.name: UndoItem
*UndoItem.labelString: "Undo"
*UndoItem.mnemonic: "U"
*UndoItem.sensitive: "false"
*UndoItem.activateCallback: {\
char stringa[100];\
\
Uccidi_grafics (pid);\
fclose (fpAPPO);\
fclose (fpDAT);\
strcpy (stringa,"cp ");\
strcat (stringa,f22undo);\
strcat (stringa," ");\
strcat (stringa,f22source);\
strcat (stringa,"\0");\
system (stringa);\
Carica_f22 ();\
set_something (UndoItem, XmNsensitive, False);\
}

*Separatore3.class: separator
*Separatore3.parent: FilePane
*Separatore3.static: true
*Separatore3.name: Separatore3

*ExitItem.class: pushButton
*ExitItem.parent: FilePane
*ExitItem.static: false
*ExitItem.name: ExitItem
*ExitItem.labelString: "Exit"
*ExitItem.mnemonic: "x"
*ExitItem.activateCallback: {\
Position PosX,PosY;\
char stringa[100];\
XmString Messaggio;\
\
if ((Modifica == 1) && (Salvato == 0))\
	{\
	strcpy (stringa,"CHANGES NOT SAVED! EXIT?\0");\
	Messaggio = XmStringCreate (stringa, XmSTRING_DEFAULT_CHARSET);\
	}\
else\
	{\
	strcpy (stringa,"Do you really want to exit Menu Graf?\0");\
	Messaggio = XmStringCreate (stringa, XmSTRING_DEFAULT_CHARSET);\
	}\
set_something (label_output, XmNlabelString, Messaggio);\
get_something (Menu_graf, XmNx, &PosX);\
get_something (Menu_graf, XmNy, &PosY);\
set_something (Menu_graf_exit, XmNx, PosX+10);\
set_something (Menu_graf_exit, XmNy, PosY+10);\
UxPopupInterface (Menu_graf_exit, no_grab);\
XmStringFree (Messaggio);\
}

*EditVarPane.class: rowColumn
*EditVarPane.parent: menu1
*EditVarPane.static: true
*EditVarPane.name: EditVarPane
*EditVarPane.rowColumnType: "menu_pulldown"
*EditVarPane.sensitive: "true"

*CopyItem_V.class: pushButton
*CopyItem_V.parent: EditVarPane
*CopyItem_V.static: false
*CopyItem_V.name: CopyItem_V
*CopyItem_V.labelString: "Copy"
*CopyItem_V.mnemonic: "C"
*CopyItem_V.activateCallback: {\
int *lista_sele,selezione,num_sele;\
\
selezione = XmListGetSelectedPos (lista_var, &lista_sele, &num_sele);\
if (ControllaValiditaPerClip (selezione,campioni)==0)\
	{\
	set_something (PasteItem_V, XmNsensitive, True);\
	nome_clip = XmStringCreateSimple ("Mia Clipboard");\
	Stringa_clip = (char *)Prepara_stringa(lista_sele,num_sele,f22source);\
	ScriviClipboard (Stringa_clip,label13);\
	}\
XtFree (lista_sele);\
}

*CutItem_V.class: pushButton
*CutItem_V.parent: EditVarPane
*CutItem_V.static: false
*CutItem_V.name: CutItem_V
*CutItem_V.labelString: "Cut"
*CutItem_V.mnemonic: "u"
*CutItem_V.activateCallback: {\
int selezione,num_sele,*lista_sele;\
\
selezione = XmListGetSelectedPos (lista_var, &lista_sele, &num_sele);\
if (ControllaValiditaPerClip (selezione,campioni) == 0)\
	{\
	set_something (PasteItem_V, XmNsensitive, True);\
	nome_clip = XmStringCreateSimple ("Mia Clipboard");\
	Stringa_clip = (char *)Prepara_stringa(lista_sele, num_sele, f22undo);\
	ScriviClipboard (Stringa_clip,label13);\
	F22_CutVar (lista_sele,num_sele);\
	}\
XtFree (lista_sele);\
}

*PasteItem_V.class: pushButton
*PasteItem_V.parent: EditVarPane
*PasteItem_V.static: false
*PasteItem_V.name: PasteItem_V
*PasteItem_V.labelString: "Paste"
*PasteItem_V.mnemonic: "P"
*PasteItem_V.activateCallback: {\
LeggiClipboard (&Stringa_clip,label13);\
Scomponi_stringa (Stringa_clip);\
F22_PasteVar ();\
set_something (PasteItem_V, XmNsensitive, False);\
}

*DescriptionItem.class: pushButton
*DescriptionItem.parent: EditVarPane
*DescriptionItem.static: true
*DescriptionItem.name: DescriptionItem
*DescriptionItem.labelString: "Description.."
*DescriptionItem.mnemonic: "D"
*DescriptionItem.activateCallback: {\
XmString Messaggio;\
int selezione,*lista_sele,num_sele;\
char stringa[100];\
\
selezione = XmListGetSelectedPos (lista_var, &lista_sele, &num_sele);\
if ((selezione == 0) || (num_sele != 1))\
{\
	strcpy (stringa,"Must be selected one item !\0");\
	Messaggio = XmStringCreate (stringa,XmSTRING_DEFAULT_CHARSET);\
	set_something (Message, XmNdialogType, XmDIALOG_ERROR);\
	set_something (Message, XmNmessageString, Messaggio);\
	UxPopupInterface (Message, no_grab);\
}else\
{\
	set_something (PasteItem_V, XmNsensitive, False);\
	descriz = (char *)XtMalloc(LUN_SIMB+1);\
 \
	indice = lista_sele[0] - 1;\
	j=0;\
	for (i=8;i<LUN_SIMB+1;i++)\
	{\
		descriz [j] = simboli[indice][i];\
		j++;\
	}\
	strcpy (nomevariabile, nomi_var[indice]);\
	Azzera_text (textDescription);\
	XmTextFieldSetString (textDescription,descriz);\
	XmTextFieldSetString (textNomevar, nomevariabile);\
	Messaggio = XmStringCreate (nomevariabile, XmSTRING_DEFAULT_CHARSET);\
	set_something (labelNomevar, XmNlabelString, Messaggio);\
	Messaggio = XmStringCreate (descriz, XmSTRING_DEFAULT_CHARSET);\
	set_something (labelDescription, XmNlabelString, Messaggio);\
	UxPopupInterface (Description, no_grab);\
}\
XmStringFree (Messaggio);\
}

*CutUnselItem_V.class: pushButton
*CutUnselItem_V.parent: EditVarPane
*CutUnselItem_V.static: true
*CutUnselItem_V.name: CutUnselItem_V
*CutUnselItem_V.labelString: "Cut Unselected"
*CutUnselItem_V.mnemonic: "U"
*CutUnselItem_V.activateCallback: {\
int *lista_sele,num_sele,selezione;\
\
selezione = XmListGetSelectedPos (lista_var, &lista_sele, &num_sele);\
F22_CutVarUnsel (lista_sele,num_sele);\
XtFree (lista_sele);\
}

*EditTitleItem.class: pushButton
*EditTitleItem.parent: EditVarPane
*EditTitleItem.static: false
*EditTitleItem.name: EditTitleItem
*EditTitleItem.labelString: "Simulation Title"
*EditTitleItem.mnemonic: "S"
*EditTitleItem.activateCallback: UxPopupInterface (create_SimulationTitle(), no_grab);

*EditTimePane.class: rowColumn
*EditTimePane.parent: menu1
*EditTimePane.static: true
*EditTimePane.name: EditTimePane
*EditTimePane.rowColumnType: "menu_pulldown"

*ExtractItem.class: pushButton
*ExtractItem.parent: EditTimePane
*ExtractItem.static: false
*ExtractItem.name: ExtractItem
*ExtractItem.labelString: "Extract.."
*ExtractItem.mnemonic: "E"
*ExtractItem.activateCallback: {\
Position PosX,PosY;\
char stringa[100];\
XmString AppoStringa;\
\
strcpy (stringa,"EXTRACT TIME\0");\
AppoStringa = XmStringCreate (stringa,XmSTRING_DEFAULT_CHARSET);\
set_something (Titolo_edit, XmNlabelString, AppoStringa);\
XmStringFree (AppoStringa);\
\
strcpy (stringa,"New start time\0");\
AppoStringa = XmStringCreate (stringa,XmSTRING_DEFAULT_CHARSET);\
set_something (Etichetta_start, XmNlabelString, AppoStringa);\
XmStringFree (AppoStringa);\
\
strcpy (stringa,"New stop time\0");\
AppoStringa = XmStringCreate (stringa,XmSTRING_DEFAULT_CHARSET);\
set_something (Etichetta_stop, XmNlabelString, AppoStringa);\
XmStringFree (AppoStringa);\
\
set_something (textField_Start, XmNsensitive, True);\
set_something (textField_Stop, XmNsensitive, True);\
set_something (PasteItem_V, XmNsensitive, False);\
\
set_something (Edt_start_time, XmNlabelString, label_start_time);\
set_something (Edt_stop_time, XmNlabelString, label_stop_time);\
Azzera_text (textField_Start);\
Azzera_text (textField_Stop);\
get_something (Menu_graf, XmNx, &PosX);\
get_something (Menu_graf, XmNy, &PosY);\
set_something (Edit_Time_Win, XmNx, PosX+10);\
set_something (Edit_Time_Win, XmNy, PosY+10);\
UxPopupInterface (Edit_Time_Win,no_grab);\
Scelta = EXTRACT_TIME;\
}

*ShiftItem.class: pushButton
*ShiftItem.parent: EditTimePane
*ShiftItem.static: false
*ShiftItem.name: ShiftItem
*ShiftItem.labelString: "Shift.."
*ShiftItem.mnemonic: "S"
*ShiftItem.activateCallback: {\
Position PosX,PosY;\
char stringa[100];\
XmString AppoStringa;\
\
strcpy (stringa, "SHIFT TIME\0");\
AppoStringa = XmStringCreate (stringa, XmSTRING_DEFAULT_CHARSET);\
set_something (Titolo_edit, XmNlabelString, AppoStringa);\
XmStringFree (AppoStringa);\
\
strcpy (stringa, "Shift time value\0");\
AppoStringa = XmStringCreate (stringa, XmSTRING_DEFAULT_CHARSET);\
set_something (Etichetta_start, XmNlabelString, AppoStringa);\
XmStringFree (AppoStringa);\
\
strcpy (stringa, "\0");\
AppoStringa = XmStringCreate (stringa, XmSTRING_DEFAULT_CHARSET);\
set_something (Etichetta_stop, XmNlabelString, AppoStringa);\
XmStringFree (AppoStringa);\
\
set_something (textField_Start, XmNsensitive, True);\
set_something (textField_Stop, XmNsensitive, False);\
set_something (PasteItem_V, XmNsensitive, False);\
\
set_something (Edt_start_time, XmNlabelString, label_start_time);\
set_something (Edt_stop_time, XmNlabelString, label_stop_time);\
Azzera_text (textField_Start);\
Azzera_text (textField_Stop);\
get_something (Menu_graf, XmNx, &PosX);\
get_something (Menu_graf, XmNy, &PosY);\
set_something (Edit_Time_Win, XmNx, PosX+10);\
set_something (Edit_Time_Win, XmNy, PosY+10);\
UxPopupInterface (Edit_Time_Win, no_grab);\
Scelta = SHIFT_TIME;\
}

*SamplingItem.class: pushButton
*SamplingItem.parent: EditTimePane
*SamplingItem.static: false
*SamplingItem.name: SamplingItem
*SamplingItem.labelString: "Sampling.."
*SamplingItem.mnemonic: "a"
*SamplingItem.activateCallback: {\
Position PosX,PosY;\
\
get_something (Menu_graf, XmNx, &PosX);\
get_something (Menu_graf, XmNy, &PosY);\
set_something (Sampling, XmNx, PosX+10);\
set_something (Sampling, XmNy, PosY+10);\
set_something (PasteItem_V, XmNsensitive, False);\
UxPopupInterface (Sampling, no_grab);\
}

*ResamplingItem.class: pushButton
*ResamplingItem.parent: EditTimePane
*ResamplingItem.static: true
*ResamplingItem.name: ResamplingItem
*ResamplingItem.labelString: "Resampling.."
*ResamplingItem.mnemonic: "R"
*ResamplingItem.activateCallback: {\
Position PosX,PosY;\
\
get_something (Menu_graf, XmNx, &PosX);\
get_something (Menu_graf, XmNy, &PosY);\
set_something (Resampling, XmNx, PosX+10);\
set_something (Resampling, XmNy, PosY+10);\
set_something (PasteItem_V, XmNsensitive, False);\
UxPopupInterface (Resampling, no_grab);\
}

*CalculationPane.class: rowColumn
*CalculationPane.parent: menu1
*CalculationPane.static: false
*CalculationPane.name: CalculationPane
*CalculationPane.rowColumnType: "menu_pulldown"
*CalculationPane.sensitive: "true"

*FilterItem.class: pushButton
*FilterItem.parent: CalculationPane
*FilterItem.static: false
*FilterItem.name: FilterItem
*FilterItem.labelString: "Filter.."
*FilterItem.mnemonic: "F"
*FilterItem.activateCallback: {\
Position px,py;\
int selezione,*lista_sele,num_sele;\
char stringa[100];\
XmString Messaggio;\
\
selezione = XmListGetSelectedPos (lista_var, &lista_sele, &num_sele);\
if (num_sele != 1)\
	{\
	strcpy (stringa,"Must be selected one item!\0");\
	Messaggio = XmStringCreate (stringa, XmSTRING_DEFAULT_CHARSET);\
	set_something (Message, XmNdialogType, XmDIALOG_ERROR);\
	set_something (Message, XmNmessageString, Messaggio);\
	UxPopupInterface (Message, no_grab);\
	XmStringFree (Messaggio);\
	}\
else\
	{\
	get_something (Menu_graf, XmNx, &px);\
	get_something (Menu_graf, XmNy, &py);\
	UxPopupInterface (create_FilterWindow(px,py,(lista_sele[0]-1)),\
				 no_grab);\
	}\
}
*FilterItem.ancestorSensitive: "true"

*AxBItem.class: pushButton
*AxBItem.parent: CalculationPane
*AxBItem.static: true
*AxBItem.name: AxBItem
*AxBItem.labelString: "Ax+B.."
*AxBItem.mnemonic: "A"
*AxBItem.activateCallback: {\
int selezione,*lista_sele,num_sele;\
char stringa[100];\
XmString Messaggio;\
\
selezione = XmListGetSelectedPos (lista_var, &lista_sele, &num_sele);\
if (num_sele != 1)\
	{\
	strcpy (stringa,"Must be selected one item!\0");\
	Messaggio = XmStringCreate (stringa, XmSTRING_DEFAULT_CHARSET);\
	set_something (Message, XmNdialogType, XmDIALOG_ERROR);\
	set_something (Message, XmNmessageString, Messaggio);\
	UxPopupInterface (Message, no_grab);\
	XmStringFree (Messaggio);\
	}\
else\
	{\
	TypeCalc = ELAB_LINEARE;\
	CalcWindow = create_CalcWindow(lista_sele);\
	UxPopupInterface (CalcWindow, no_grab);\
	}\
XtFree (lista_sele);\
}

*xyItem.class: pushButton
*xyItem.parent: CalculationPane
*xyItem.static: true
*xyItem.name: xyItem
*xyItem.labelString: "x+y.."
*xyItem.mnemonic: "x"
*xyItem.activateCallback: {\
int selezione,*lista_sele,num_sele;\
char stringa[100];\
XmString Messaggio;\
\
selezione = XmListGetSelectedPos (lista_var, &lista_sele, &num_sele);\
if (num_sele != 2)\
	{\
	strcpy (stringa,"Must be selected two item!\0");\
	Messaggio = XmStringCreate (stringa, XmSTRING_DEFAULT_CHARSET);\
	set_something (Message, XmNdialogType, XmDIALOG_ERROR);\
	set_something (Message, XmNmessageString, Messaggio);\
	UxPopupInterface (Message, no_grab);\
	XmStringFree (Messaggio);\
	}\
else\
	{\
	TypeCalc = SOMMA_ALGEBRICA;\
	CalcWindow = create_CalcWindow (lista_sele);\
	UxPopupInterface (CalcWindow, no_grab);\
	}\
XtFree (lista_sele);\
}

*ViewPane.class: rowColumn
*ViewPane.parent: menu1
*ViewPane.static: false
*ViewPane.name: ViewPane
*ViewPane.rowColumnType: "menu_pulldown"
*ViewPane.sensitive: "true"

*GraphItem.class: pushButton
*GraphItem.parent: ViewPane
*GraphItem.static: false
*GraphItem.name: GraphItem
*GraphItem.labelString: "Graphics.."
*GraphItem.mnemonic: "G"
*GraphItem.activateCallback: {\
extern char nomi_var[NUM_VAR+1][LUN_NOME+1];\
\
int indice,indice2,indice3,indice4;\
int selezione,*lista_sele,num_sele;\
int i;\
\
rout_appo();\
 \
selezione = XmListGetSelectedPos (lista_var, &lista_sele, &num_sele);	\
\
if (selezione == 0) num_sele = 0;\
switch (num_sele)\
{\
	case 0:\
		pid = attiva_prog_par ("graphics",path_22dat,nomi_var[0],0);\
		break;\
	case 1: \
		indice = lista_sele[0] - 1;\
		pid = attiva_prog_par ("graphics",path_22dat,\
			nomi_var[indice],0);\
		break;\
	case 2:\
		indice = lista_sele[0] - 1;\
		indice2 = lista_sele [1] - 1;\
		pid = attiva_prog_par ("graphics",path_22dat,\
			nomi_var[indice],\
			nomi_var[indice2],0);\
		break;\
	case 3:\
		indice = lista_sele[0] - 1;\
		indice2 = lista_sele[1] - 1;\
		indice3 = lista_sele[2] - 1;\
		pid = attiva_prog_par ("graphics",path_22dat,\
			nomi_var[indice],\
			nomi_var[indice2],\
			nomi_var[indice3],0);\
		break;\
	default:\
		indice = lista_sele[0] - 1;\
		indice2 = lista_sele[1] - 1;\
		indice3 = lista_sele[2] - 1;\
		indice4 = lista_sele[3] - 1;\
		pid = attiva_prog_par ("graphics",path_22dat,\
			nomi_var[indice],\
			nomi_var[indice2],\
			nomi_var[indice3],\
			nomi_var[indice4],0);\
		break;\
}\
XtFree (lista_sele);\
}

*FindPane.class: rowColumn
*FindPane.parent: menu1
*FindPane.static: true
*FindPane.name: FindPane
*FindPane.rowColumnType: "menu_pulldown"

*Multiple_Find_Item.class: toggleButton
*Multiple_Find_Item.parent: FindPane
*Multiple_Find_Item.static: false
*Multiple_Find_Item.name: Multiple_Find_Item
*Multiple_Find_Item.labelString: "Multiple"
*Multiple_Find_Item.mnemonic: "M"
*Multiple_Find_Item.valueChangedCallback: {\
Find_sel = MULTIPLO;\
set_something (Multiple_Find_Item, XmNset, True);\
set_something (Single_Find_Item, XmNset, False);\
set_something (lista_var, XmNselectionPolicy, XmMULTIPLE_SELECT);\
}

*Single_Find_Item.class: toggleButton
*Single_Find_Item.parent: FindPane
*Single_Find_Item.static: false
*Single_Find_Item.name: Single_Find_Item
*Single_Find_Item.labelString: "Single"
*Single_Find_Item.mnemonic: "S"
*Single_Find_Item.valueChangedCallback: {\
Find_sel = SINGOLO;\
set_something (Single_Find_Item, XmNset, True);\
set_something (Multiple_Find_Item, XmNset, False);\
set_something (lista_var, XmNselectionPolicy, XmEXTENDED_SELECT);\
}

*File_Pane.class: cascadeButton
*File_Pane.parent: menu1
*File_Pane.static: false
*File_Pane.name: File_Pane
*File_Pane.labelString: "File"
*File_Pane.mnemonic: "F"
*File_Pane.subMenuId: "FilePane"

*Var_Pane.class: cascadeButton
*Var_Pane.parent: menu1
*Var_Pane.static: false
*Var_Pane.name: Var_Pane
*Var_Pane.labelString: "Edit Variables"
*Var_Pane.mnemonic: "E"
*Var_Pane.subMenuId: "EditVarPane"
*Var_Pane.sensitive: "false"

*Time_Pane.class: cascadeButton
*Time_Pane.parent: menu1
*Time_Pane.static: false
*Time_Pane.name: Time_Pane
*Time_Pane.labelString: "Edit Time"
*Time_Pane.mnemonic: "d"
*Time_Pane.subMenuId: "EditTimePane"
*Time_Pane.sensitive: "false"

*Calc_Pane.class: cascadeButton
*Calc_Pane.parent: menu1
*Calc_Pane.static: false
*Calc_Pane.name: Calc_Pane
*Calc_Pane.labelString: "Calc"
*Calc_Pane.mnemonic: "C"
*Calc_Pane.subMenuId: "CalculationPane"
*Calc_Pane.sensitive: "false"

*View_Pane.class: cascadeButton
*View_Pane.parent: menu1
*View_Pane.static: false
*View_Pane.name: View_Pane
*View_Pane.labelString: "View"
*View_Pane.mnemonic: "V"
*View_Pane.subMenuId: "ViewPane"
*View_Pane.sensitive: "true"

*Find_Pane.class: cascadeButton
*Find_Pane.parent: menu1
*Find_Pane.static: false
*Find_Pane.name: Find_Pane
*Find_Pane.labelString: "Find"
*Find_Pane.mnemonic: "i"
*Find_Pane.subMenuId: "FindPane"
*Find_Pane.sensitive: "false"

*form1.class: form
*form1.parent: f22_modify
*form1.static: true
*form1.name: form1
*form1.resizePolicy: "resize_any"
*form1.noResize: "false"
*form1.horizontalSpacing: 0
*form1.navigationType: "tab_group"
*form1.y: 15
*form1.x: 0

*num_var.class: label
*num_var.parent: form1
*num_var.static: false
*num_var.name: num_var
*num_var.x: 280
*num_var.y: 170
*num_var.width: 65
*num_var.height: 25
*num_var.background: "#a8afc6"
*num_var.fontList: "fixed"
*num_var.labelString: ""
*num_var.recomputeSize: "true"
*num_var.bottomShadowColor: "LightSlateGrey"
*num_var.alignment: "alignment_end"
*num_var.rightAttachment: "attach_form"
*num_var.rightOffset: 200
*num_var.topOffset: 300

*scrolledWindow1.class: scrolledWindow
*scrolledWindow1.parent: form1
*scrolledWindow1.static: true
*scrolledWindow1.name: scrolledWindow1
*scrolledWindow1.scrollingPolicy: "application_defined"
*scrolledWindow1.x: 30
*scrolledWindow1.y: 200
*scrolledWindow1.visualPolicy: "variable"
*scrolledWindow1.scrollBarDisplayPolicy: "static"
*scrolledWindow1.shadowThickness: 0
*scrolledWindow1.rightAttachment: "attach_form"
*scrolledWindow1.rightOffset: 25
*scrolledWindow1.rightPosition: 50
*scrolledWindow1.leftAttachment: "attach_form"
*scrolledWindow1.leftOffset: 25
*scrolledWindow1.bottomAttachment: "attach_form"
*scrolledWindow1.bottomOffset: 70
*scrolledWindow1.topAttachment: "attach_widget"
*scrolledWindow1.topOffset: 15
*scrolledWindow1.topWidget: "num_var"

*lista_var.class: scrolledList
*lista_var.parent: scrolledWindow1
*lista_var.static: false
*lista_var.name: lista_var
*lista_var.width: 473
*lista_var.height: 146
*lista_var.listSizePolicy: "constant"
*lista_var.fontList: "fixed"
*lista_var.background: "#a8afc6"
*lista_var.scrollBarDisplayPolicy: "static"
*lista_var.selectionPolicy: "extended_select"
*lista_var.multipleSelectionCallback: {\
\
}

*textField_find.class: textField
*textField_find.parent: form1
*textField_find.static: false
*textField_find.name: textField_find
*textField_find.x: 25
*textField_find.y: 530
*textField_find.width: 190
*textField_find.height: 35
*textField_find.background: "#a8afc6"
*textField_find.fontList: "fixed"
*textField_find.bottomAttachment: "attach_form"
*textField_find.bottomOffset: 15
*textField_find.columns: 8
*textField_find.maxLength: 20
*textField_find.sensitive: "false"
*textField_find.valueChangedCallback: {\
char *controllo;\
\
controllo = XmTextFieldGetString (textField_find);\
if ((controllo[0] != '\0') && (controllo[0] != '\n'))\
	{\
	set_something (Find_Butt_Up, XmNsensitive, True);\
	set_something (Find_Butt_Down, XmNsensitive, True);\
	}\
else\
	{	\
	set_something (Find_Butt_Up, XmNsensitive, False);\
	set_something (Find_Butt_Down, XmNsensitive, False);\
	}\
}

*Find_Butt_Up.class: arrowButtonGadget
*Find_Butt_Up.parent: form1
*Find_Butt_Up.static: false
*Find_Butt_Up.name: Find_Butt_Up
*Find_Butt_Up.x: 270
*Find_Butt_Up.y: 625
*Find_Butt_Up.width: 35
*Find_Butt_Up.height: 35
*Find_Butt_Up.bottomAttachment: "attach_form"
*Find_Butt_Up.bottomOffset: 15
*Find_Butt_Up.leftAttachment: "attach_widget"
*Find_Butt_Up.leftOffset: 10
*Find_Butt_Up.leftWidget: "textField_find"
*Find_Butt_Up.leftPosition: 10
*Find_Butt_Up.resizable: "false"
*Find_Butt_Up.sensitive: "false"
*Find_Butt_Up.activateCallback: {\
int Valore;\
char *Trovare,stringa[100];\
XmString Messaggio;\
\
Trovare = XmTextFieldGetString (textField_find);\
Valore = Cerca_su (Trovare);\
if (trovata == 0)\
	{\
	strcpy (stringa,"String not found\0");\
	Messaggio = XmStringCreate (stringa, XmSTRING_DEFAULT_CHARSET);\
	set_something (Message, XmNdialogType, XmDIALOG_INFORMATION);\
	set_something (Message, XmNmessageString, Messaggio);\
	UxPopupInterface (Message,no_grab);\
	XmStringFree (Messaggio);\
	}\
else	\
	{\
	XmListSetPos (lista_var, Valore);\
	XmListSelectPos (lista_var, Valore, True);\
	}\
\
}

*Find_Butt_Down.class: arrowButtonGadget
*Find_Butt_Down.parent: form1
*Find_Butt_Down.static: false
*Find_Butt_Down.name: Find_Butt_Down
*Find_Butt_Down.x: 325
*Find_Butt_Down.y: 625
*Find_Butt_Down.width: 35
*Find_Butt_Down.height: 35
*Find_Butt_Down.bottomAttachment: "attach_form"
*Find_Butt_Down.bottomOffset: 15
*Find_Butt_Down.leftAttachment: "attach_widget"
*Find_Butt_Down.leftOffset: 10
*Find_Butt_Down.leftWidget: "Find_Butt_Up"
*Find_Butt_Down.arrowDirection: "arrow_down"
*Find_Butt_Down.ancestorSensitive: "true"
*Find_Butt_Down.sensitive: "false"
*Find_Butt_Down.activateCallback: {\
int Valore;\
char stringa[100],*Trovare;\
XmString Messaggio;\
\
Trovare = XmTextFieldGetString (textField_find);\
Valore = Cerca_giu (Trovare);\
if (trovata == 0)\
	{\
	strcpy (stringa,"String not found\0");\
	Messaggio = XmStringCreate (stringa, XmSTRING_DEFAULT_CHARSET);\
	set_something (Message, XmNdialogType, XmDIALOG_INFORMATION);\
	set_something (Message, XmNmessageString, Messaggio);\
	UxPopupInterface (Message, no_grab);\
	XmStringFree (Messaggio);\
	}\
else\
 	{\
	XmListSetPos (lista_var,Valore);\
	XmListSelectPos (lista_var, Valore, True);\
	}\
}

*l_path_name.class: label
*l_path_name.parent: form1
*l_path_name.static: true
*l_path_name.name: l_path_name
*l_path_name.x: 40
*l_path_name.y: 15
*l_path_name.width: 85
*l_path_name.height: 25
*l_path_name.alignment: "alignment_end"
*l_path_name.labelString: "Input file:"
*l_path_name.recomputeSize: "false"
*l_path_name.rightOffset: 0
*l_path_name.rightWidget: ""
*l_path_name.rightAttachment: "attach_none"
*l_path_name.leftOffset: 30

*path_f22.class: label
*path_f22.parent: form1
*path_f22.static: false
*path_f22.name: path_f22
*path_f22.x: 130
*path_f22.y: 10
*path_f22.width: 375
*path_f22.height: 25
*path_f22.background: "#a8afc6"
*path_f22.fontList: "fixed"
*path_f22.labelString: ""
*path_f22.recomputeSize: "false"
*path_f22.bottomShadowColor: "LightSlateGrey"
*path_f22.alignment: "alignment_beginning"
*path_f22.rightAttachment: "attach_form"
*path_f22.rightOffset: 72
*path_f22.leftAttachment: "attach_widget"
*path_f22.leftOffset: 10
*path_f22.leftWidget: "l_path_name"

*l_num_var.class: label
*l_num_var.parent: form1
*l_num_var.static: true
*l_num_var.name: l_num_var
*l_num_var.x: 130
*l_num_var.y: 170
*l_num_var.width: 135
*l_num_var.height: 25
*l_num_var.alignment: "alignment_end"
*l_num_var.labelString: "Variables number:"
*l_num_var.recomputeSize: "false"
*l_num_var.rightAttachment: "attach_widget"
*l_num_var.rightOffset: 10
*l_num_var.rightWidget: "num_var"
*l_num_var.topOffset: 200

*l_stop_time.class: label
*l_stop_time.parent: form1
*l_stop_time.static: true
*l_stop_time.name: l_stop_time
*l_stop_time.x: 310
*l_stop_time.y: 55
*l_stop_time.width: 85
*l_stop_time.height: 25
*l_stop_time.alignment: "alignment_end"
*l_stop_time.labelString: "Stop time:"
*l_stop_time.recomputeSize: "false"
*l_stop_time.rightAttachment: "attach_none"
*l_stop_time.rightOffset: 0
*l_stop_time.rightWidget: ""
*l_stop_time.leftAttachment: "attach_none"
*l_stop_time.resizable: "false"
*l_stop_time.leftOffset: 0

*l1_sec.class: label
*l1_sec.parent: form1
*l1_sec.static: true
*l1_sec.name: l1_sec
*l1_sec.x: 210
*l1_sec.y: 55
*l1_sec.width: 40
*l1_sec.height: 25
*l1_sec.fontList: "-adobe-times-medium-r-normal--14-140-75-75-p-74-iso8859-1"
*l1_sec.labelString: "sec."
*l1_sec.alignment: "alignment_beginning"
*l1_sec.rightAttachment: "attach_none"
*l1_sec.rightOffset: 0
*l1_sec.rightWidget: ""

*start_time.class: label
*start_time.parent: form1
*start_time.static: false
*start_time.name: start_time
*start_time.x: 150
*start_time.y: 50
*start_time.width: 65
*start_time.height: 25
*start_time.background: "#a8afc6"
*start_time.fontList: "fixed"
*start_time.recomputeSize: "false"
*start_time.bottomShadowColor: "LightSlateGrey"
*start_time.alignment: "alignment_end"
*start_time.labelString: ""
*start_time.rightAttachment: "attach_widget"
*start_time.rightOffset: 10
*start_time.rightWidget: "l1_sec"
*start_time.topOffset: 45

*l_start_time.class: label
*l_start_time.parent: form1
*l_start_time.static: true
*l_start_time.name: l_start_time
*l_start_time.x: 45
*l_start_time.y: 55
*l_start_time.width: 70
*l_start_time.height: 25
*l_start_time.alignment: "alignment_end"
*l_start_time.labelString: "Start time:"
*l_start_time.recomputeSize: "false"
*l_start_time.rightAttachment: "attach_widget"
*l_start_time.rightOffset: 10
*l_start_time.rightWidget: "start_time"
*l_start_time.leftAttachment: "attach_form"
*l_start_time.leftOffset: 40
*l_start_time.topOffset: 50

*Push_Select.class: pushButton
*Push_Select.parent: form1
*Push_Select.static: false
*Push_Select.name: Push_Select
*Push_Select.x: 315
*Push_Select.y: 560
*Push_Select.width: 90
*Push_Select.height: 35
*Push_Select.labelString: "Select all"
*Push_Select.sensitive: "false"
*Push_Select.activateCallback: {\
int j,i,selezione,*lista_sele,num_sele;\
\
selezione = XmListGetSelectedPos (lista_var, &lista_sele, &num_sele);\
set_something (lista_var, XmNselectionPolicy, XmMULTIPLE_SELECT);\
if (num_sele != header1.nvar)\
	{\
	if (selezione)\
		{\
		for (i=1;i<=header1.nvar+1;i++)\
			{\
			for (j=0;j<num_sele;j++)\
			if (lista_sele[j]!=i) XmListSelectPos (lista_var,i,1);\
			}\
		}\
	else\
		{\
		for (i=1;i<=header1.nvar+1;i++)\
		 	XmListSelectPos (lista_var,i,1);\
		}\
	}\
set_something (lista_var, XmNselectionPolicy, XmEXTENDED_SELECT);\
}
*Push_Select.bottomAttachment: "attach_form"
*Push_Select.bottomOffset: 15
*Push_Select.leftAttachment: "attach_widget"
*Push_Select.leftOffset: 10
*Push_Select.leftWidget: "Find_Butt_Down"

*Push_Deselect.class: pushButton
*Push_Deselect.parent: form1
*Push_Deselect.static: false
*Push_Deselect.name: Push_Deselect
*Push_Deselect.x: 415
*Push_Deselect.y: 560
*Push_Deselect.width: 90
*Push_Deselect.height: 35
*Push_Deselect.labelString: "Deselect all"
*Push_Deselect.sensitive: "false"
*Push_Deselect.activateCallback: XmListDeselectAllItems (lista_var);
*Push_Deselect.leftAttachment: "attach_widget"
*Push_Deselect.leftOffset: 10
*Push_Deselect.leftWidget: "Push_Select"
*Push_Deselect.bottomAttachment: "attach_form"
*Push_Deselect.bottomOffset: 15

*delta_campioni.class: label
*delta_campioni.parent: form1
*delta_campioni.static: false
*delta_campioni.name: delta_campioni
*delta_campioni.x: 135
*delta_campioni.y: 90
*delta_campioni.width: 65
*delta_campioni.height: 25
*delta_campioni.background: "#a8afc6"
*delta_campioni.fontList: "fixed"
*delta_campioni.recomputeSize: "false"
*delta_campioni.bottomShadowColor: "LightSlateGrey"
*delta_campioni.alignment: "alignment_end"
*delta_campioni.labelString: ""
*delta_campioni.leftOffset: 120

*l_start_time2.class: label
*l_start_time2.parent: form1
*l_start_time2.static: true
*l_start_time2.name: l_start_time2
*l_start_time2.x: 305
*l_start_time2.y: 95
*l_start_time2.width: 90
*l_start_time2.height: 25
*l_start_time2.alignment: "alignment_end"
*l_start_time2.labelString: "Sampl. Num.:"
*l_start_time2.recomputeSize: "false"
*l_start_time2.leftAttachment: "attach_none"
*l_start_time2.leftOffset: 0

*num_campioni.class: label
*num_campioni.parent: form1
*num_campioni.static: false
*num_campioni.name: num_campioni
*num_campioni.x: 405
*num_campioni.y: 90
*num_campioni.width: 65
*num_campioni.height: 25
*num_campioni.background: "#a8afc6"
*num_campioni.fontList: "fixed"
*num_campioni.recomputeSize: "false"
*num_campioni.bottomShadowColor: "LightSlateGrey"
*num_campioni.alignment: "alignment_end"
*num_campioni.labelString: ""
*num_campioni.leftAttachment: "attach_widget"
*num_campioni.leftOffset: 10
*num_campioni.leftWidget: "l_start_time2"
*num_campioni.resizable: "false"
*num_campioni.rightAttachment: "attach_form"
*num_campioni.rightOffset: 72

*l_start_time1.class: label
*l_start_time1.parent: form1
*l_start_time1.static: true
*l_start_time1.name: l_start_time1
*l_start_time1.x: 30
*l_start_time1.y: 95
*l_start_time1.width: 95
*l_start_time1.height: 25
*l_start_time1.alignment: "alignment_end"
*l_start_time1.labelString: "Sampl. Int.:"
*l_start_time1.recomputeSize: "false"
*l_start_time1.leftOffset: 30
*l_start_time1.rightAttachment: "attach_widget"
*l_start_time1.rightOffset: 10
*l_start_time1.rightWidget: "delta_campioni"

*l1_sec1.class: label
*l1_sec1.parent: form1
*l1_sec1.static: true
*l1_sec1.name: l1_sec1
*l1_sec1.x: 210
*l1_sec1.y: 95
*l1_sec1.width: 40
*l1_sec1.height: 25
*l1_sec1.fontList: "-adobe-times-medium-r-normal--14-140-75-75-p-74-iso8859-1"
*l1_sec1.labelString: "sec."
*l1_sec1.alignment: "alignment_beginning"

*stop_time.class: label
*stop_time.parent: form1
*stop_time.static: false
*stop_time.name: stop_time
*stop_time.x: 405
*stop_time.y: 50
*stop_time.width: 65
*stop_time.height: 25
*stop_time.background: "#a8afc6"
*stop_time.fontList: "fixed"
*stop_time.labelString: ""
*stop_time.recomputeSize: "false"
*stop_time.bottomShadowColor: "LightSlateGrey"
*stop_time.alignment: "alignment_end"
*stop_time.rightAttachment: "attach_none"
*stop_time.rightOffset: 0
*stop_time.rightWidget: ""
*stop_time.leftAttachment: "attach_widget"
*stop_time.leftOffset: 10
*stop_time.leftWidget: "l_stop_time"

*l2_sec.class: label
*l2_sec.parent: form1
*l2_sec.static: true
*l2_sec.name: l2_sec
*l2_sec.x: 485
*l2_sec.y: 55
*l2_sec.width: 37
*l2_sec.height: 25
*l2_sec.fontList: "-adobe-times-medium-r-normal--14-140-75-75-p-74-iso8859-1"
*l2_sec.labelString: "sec."
*l2_sec.alignment: "alignment_beginning"
*l2_sec.rightAttachment: "attach_form"
*l2_sec.rightOffset: 20
*l2_sec.leftAttachment: "attach_widget"
*l2_sec.leftOffset: 10
*l2_sec.leftWidget: "stop_time"
*l2_sec.resizable: "false"

*MAX_Int.class: label
*MAX_Int.parent: form1
*MAX_Int.static: false
*MAX_Int.name: MAX_Int
*MAX_Int.x: 350
*MAX_Int.y: 130
*MAX_Int.width: 65
*MAX_Int.height: 25
*MAX_Int.background: "#a8afc6"
*MAX_Int.fontList: "fixed"
*MAX_Int.labelString: ""
*MAX_Int.recomputeSize: "true"
*MAX_Int.bottomShadowColor: "LightSlateGrey"
*MAX_Int.alignment: "alignment_end"
*MAX_Int.leftAttachment: "attach_none"
*MAX_Int.leftOffset: 0
*MAX_Int.rightAttachment: "attach_form"
*MAX_Int.rightOffset: 120

*MIN_Int.class: label
*MIN_Int.parent: form1
*MIN_Int.static: false
*MIN_Int.name: MIN_Int
*MIN_Int.x: 290
*MIN_Int.y: 130
*MIN_Int.width: 65
*MIN_Int.height: 25
*MIN_Int.background: "#a8afc6"
*MIN_Int.fontList: "fixed"
*MIN_Int.labelString: ""
*MIN_Int.recomputeSize: "true"
*MIN_Int.bottomShadowColor: "LightSlateGrey"
*MIN_Int.alignment: "alignment_end"
*MIN_Int.leftAttachment: "attach_none"
*MIN_Int.leftOffset: 0
*MIN_Int.rightAttachment: "attach_widget"
*MIN_Int.rightOffset: 15
*MIN_Int.rightWidget: "MAX_Int"

*label13.class: label
*label13.parent: form1
*label13.static: true
*label13.name: label13
*label13.x: 95
*label13.y: 130
*label13.width: 175
*label13.height: 25
*label13.alignment: "alignment_end"
*label13.labelString: "MIN/MAX Samples Interval:"
*label13.recomputeSize: "false"
*label13.leftAttachment: "attach_none"
*label13.leftOffset: 0
*label13.rightAttachment: "attach_widget"
*label13.rightOffset: 10
*label13.rightWidget: "MIN_Int"

*l1_sec2.class: label
*l1_sec2.parent: form1
*l1_sec2.static: true
*l1_sec2.name: l1_sec2
*l1_sec2.x: 430
*l1_sec2.y: 130
*l1_sec2.width: 40
*l1_sec2.height: 25
*l1_sec2.fontList: "-adobe-times-medium-r-normal--14-140-75-75-p-74-iso8859-1"
*l1_sec2.labelString: "sec."
*l1_sec2.alignment: "alignment_beginning"

