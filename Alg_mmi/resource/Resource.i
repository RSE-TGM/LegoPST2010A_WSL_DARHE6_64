! UIMX ascii 2.5 key: 3859                                                      

*Resource.class: topLevelShell
*Resource.gbldecl: /*\
        Inizio sezione per SCCS\
*/\
/*\
   modulo Resource.i\
   tipo \
   release 5.2\
   data 2/13/96\
   reserved @(#)Resource.i	5.2\
*/\
/*\
        Variabile per identificazione della versione\
*/\
/*\
        Fine sezione per SCCS\
*/\
\
#include <stdio.h>\
#include <ctype.h>\
#include <X11/Intrinsic.h>\
#include <Xm/Xm.h>\
#include <Xl/Xl.h>\
/*\
#include <Xl/XlCoreP.h>\
*/\
#include <Xl/XlIconReg.h>\
#include <Xl/XlPictograph.h>\
#include <Xl/XlOperableKeys.h>\
#include <Xl/XlPixvar.h>\
#include <Ol/OlDatabaseTopologia.h>\
#include <Ol/OlForm.h>\
#include "res_edit.h"\
#include "config.h"\
\
extern Display *UxDisplay;\
extern swidget create_FontsViewer();\
extern swidget create_ColorViewer();\
extern swidget create_AnimateIconSelection();\
extern swidget create_VariableEditor();\
extern swidget create_DatabaseSelection();\
extern swidget create_FormSelection();\
extern swidget create_ValueSelection();\
extern swidget create_VariablesSelection(); \
extern char *Gruppi_resource[];\
extern Widget GetPadre();\
extern int Usato();\
extern char *WidGetName();\
extern Display *GetDisplay();\
extern WidgetClass GetClass();\
\
void CreaRowColumnRisorse ( );\
int EseguiLoadResources();
*Resource.ispecdecl: Widget OggettoS;  /*  Widget attualmente selezionato  */\
swidget PaginaDrawing; /*  Pagina degli oggetti */\
XrmDatabase PuntDB; /* Puntatore al database delle risorse  */\
Widget *RigaPerVar; /* Lista widget per VariableEditor  */\
Widget VariabEdit; /* ID dell'interfaccia del variable editor  */\
int *TipoVariabile;\
PAGINA *PagConf;  /* Pagina aperte della config  */\
OlDatabaseTopologiaObject DataBaseTo; /* Database della topologia del modello */
*Resource.ispeclist: OggettoS, PaginaDrawing, PuntDB, RigaPerVar, VariabEdit, TipoVariabile, PagConf, DataBaseTo
*Resource.ispeclist.OggettoS: "Widget", "%OggettoS%"
*Resource.ispeclist.PaginaDrawing: "swidget", "%PaginaDrawing%"
*Resource.ispeclist.PuntDB: "XrmDatabase", "%PuntDB%"
*Resource.ispeclist.RigaPerVar: "Widget", "*%RigaPerVar%"
*Resource.ispeclist.VariabEdit: "Widget", "%VariabEdit%"
*Resource.ispeclist.TipoVariabile: "int", "*%TipoVariabile%"
*Resource.ispeclist.PagConf: "PAGINA", "*%PagConf%"
*Resource.ispeclist.DataBaseTo: "OlDatabaseTopologiaObject", "%DataBaseTo%"
*Resource.funcdecl: swidget create_Resource(Strutture,Dbase)\
PAGINA *Strutture;  /* struttura pagina corrente */\
OlDatabaseTopologiaObject Dbase; /* database topologia in uso */
*Resource.funcname: create_Resource
*Resource.funcdef: "swidget", "<create_Resource>(%)"
*Resource.argdecl: PAGINA *Strutture;\
OlDatabaseTopologiaObject Dbase;
*Resource.arglist: Strutture, Dbase
*Resource.arglist.Strutture: "PAGINA", "*%Strutture%"
*Resource.arglist.Dbase: "OlDatabaseTopologiaObject", "%Dbase%"
*Resource.icode: int iret;\
Boolean selezionato,Occupato;\
XmString StrLab; \
char *Appoggio2,appoggio[100];\
WidgetClass classe_oggetto;\
\
char TitoloPag[120];\
Arg arg[3];\
Widget WdgAppoggio;\
\
OggettoS = NULL;\
\
DataBaseTo = Dbase;\
PagConf = Strutture;\
PaginaDrawing = (swidget )PagConf->drawing;\
PuntDB = PagConf->db;\
\
Occupato = False;\
OggettoS = NULL;
*Resource.fcode: strcpy (TitoloPag,"Widget Resource Editor on page: ");\
strcat (TitoloPag,PagConf->nomepag);\
set_something (Resource, XmNtitle, TitoloPag);\
\
/*  Creazione dei rowcolumn di pagina  */\
CreaRowColumnRisorse (Widres_rc);\
\
/* Cerca nella drawing area l'oggetto selezionato */\
OggettoS = (Widget )XlGetSelectedWidget (PaginaDrawing);\
\
/*  Inserisce nella lista degli oggetti selezionati il nome dell\
	oggetto selezionato e prepara i rowcolumn con le liste delle\
	risorse  */\
\
if ( OggettoS != NULL )\
	{\
	/* Setta l'attributo dell'oggetto selezionato in editazione  */\
	XtSetArg (arg[0], XlNinEdit, True);\
	XtSetArg (arg[1], XlNwEdit, Resource);\
	XtSetValues (OggettoS, arg, 2);\
	/*  Setta l'attributo sensitive */\
	set_something (pushButton1, XmNsensitive, True);\
	set_something (ResetItem, XmNsensitive, True);\
	PrepListaRes (Geometric_RC, OggettoS, XlRGrGeom, DataBaseTo,\
					PagGetType(PagConf));\
	PrepListaRes (Specific_RC, OggettoS, XlRGrIo, DataBaseTo,\
					PagGetType(PagConf));\
	PrepListaRes (Color_RC, OggettoS, XlRGrColor, DataBaseTo,\
					PagGetType(PagConf));\
	PrepListaRes (VarCC1_rc, OggettoS, XlRGrVCC1, DataBaseTo,\
					PagGetType(PagConf));\
	PrepListaRes (VarCC2_rc, OggettoS, XlRGrVCC2, DataBaseTo,\
					PagGetType(PagConf));\
	PrepListaRes (VarCC3_rc, OggettoS, XlRGrVCC3, DataBaseTo,\
					PagGetType(PagConf));\
	PrepListaRes (VarCC4_rc, OggettoS, XlRGrVCC4, DataBaseTo,\
					PagGetType(PagConf));\
	strcpy (appoggio,WidGetName(OggettoS));\
	strcat (appoggio,"  ----  ");\
\
        classe_oggetto = GetClass (OggettoS);\
        Appoggio2 = XtNewString( XlGetClassName(classe_oggetto) );\
	strcat (appoggio,Appoggio2);\
	XtFree (Appoggio2);\
	}\
else\
	{\
	strcpy (appoggio,"No Widget selected");\
	set_something (ResetItem, XmNsensitive, False);\
	set_something (pushButton1, XmNsensitive, False);\
	}\
\
/*  Crea l'OptionMenu che contiene le voci dei gruppi\
	da visualizzare nella lista delle risorse   */\
\
iret = CreaOptionMenu (menu2,GruppiPane);\
if (iret == NON_ALLOCATA) printf ("Manca spazio per allocare OptMenu!\n");\
if (iret == OK) printf ("Option Menu creato correttamente\n");\
\
/*   Visualizza il rwocolumn che contiene le risorse di specific  */\
XtManageChild (Specific_RC);\
XtManageChild (Widres_rc);\
\
StrLab = XmStringCreateSimple (appoggio);\
XmListAddItemUnselected (scrolledList1, StrLab, 0);\
XmStringFree (StrLab);\
\
/*  Crea l'interfaccia del variable editor */\
RigaPerVar = (Widget *)XtCalloc ( 4 , sizeof(Widget) );\
TipoVariabile = (int *)XtCalloc ( 1 , sizeof(int) );\
\
VariabEdit = (Widget )create_VariableEditor (PaginaDrawing,RigaPerVar,Resource,\
					TipoVariabile,Dbase);\
\
/*  Setta la posizione della interfaccia rispetto al parent  */\
InterfaceSetPos (Resource,PagConf->topwidget);\
\
return(rtrn);
*Resource.auxdecl: /************************************************************\
	Controlla se sono state fatte delle modifiche \
	alle risorse di un oggetto che non sono state\
	salvate \
************************************************************/\
\
Boolean ControllaModifiche (swidget Ogg)\
{\
int Numero;\
Widget *Riga,*Figli;\
int i;\
char str[5];\
XmString Stringa,Confronto;\
\
strcpy (str,"|");\
Confronto = XmStringCreateSimple (str);\
\
get_something (Ogg, XmNnumChildren, &Numero);\
get_something (Ogg, XmNchildren, &Figli);\
\
for (i=0;i<Numero;i++)\
	{\
	get_something (Figli[i], XmNchildren, &Riga);\
	get_something (Riga[1], XmNlabelString, &Stringa);\
	if (XmStringCompare(Stringa,Confronto)) return (True);\
	XmStringFree (Stringa);\
	}\
return (False);\
}\
\
/**************************************************************\
	Routine che crea tutti i rowcolumn per la visualizzazione\
	e la gestione delle risorse\
**************************************************************/\
\
void CreaRowColumnRisorse (Widget Wdg)\
{\
XtDestroyWidget (Widres_rc);\
\
/*  Creazione di un rowcol che conterra' i rowcol\
	 relativi ad un gruppo di risorse da visualizzare  */\
Widres_rc = (swidget )XtVaCreateWidget ("Widres_rc",\
		xmRowColumnWidgetClass, scrolledWindow2,\
		XmNnumColumns, 100,\
		XmNisAligned, False,\
		XmNspacing, 0,\
		XmNmarginHeight, 0,\
		XmNmarginTop, 0,\
		XmNmarginBottom, 0,\
		XmNnavigationType, XmTAB_GROUP,\
		NULL);\
#ifndef DESIGN_TIME\
	UxPutContext (Widres_rc ,   (char *) UxResourceContext); \
#endif\
\
/*  Creazione del rowcol per le risorse relative a core  */\
Geometric_RC = (swidget )XtVaCreateWidget ("Geometric_RC",\
		xmRowColumnWidgetClass, Widres_rc,\
		XmNnumColumns, 100,\
		XmNisAligned, False,\
		XmNspacing, 0,\
		XmNmarginHeight, 0,\
		XmNmarginTop, 0,\
		XmNmarginBottom, 0,\
		NULL);\
#ifndef DESIGN_TIME\
	UxPutContext (Geometric_RC ,(char *) UxResourceContext); \
#endif\
\
/*  Creazione del rowcol per le risorse relative al tipo di variabile  */\
Specific_RC = (swidget )XtVaCreateWidget ("Specific_RC",\
		xmRowColumnWidgetClass, Widres_rc,\
		XmNnumColumns, 100,\
		XmNisAligned, False,\
		XmNspacing, 0,\
		XmNmarginHeight, 0,\
		XmNmarginTop, 0,\
		XmNmarginBottom, 0,\
		NULL);\
#ifndef DESIGN_TIME\
	UxPutContext (Specific_RC , (char *) UxResourceContext); \
#endif\
\
/*  Creazione del rowcol per le risorse relative ai colori  */\
Color_RC = (swidget )XtVaCreateWidget ("Color_RC",\
		xmRowColumnWidgetClass, Widres_rc,\
		XmNnumColumns, 100,\
		XmNisAligned, False,\
		XmNspacing, 0,\
		XmNmarginHeight, 0,\
		XmNmarginTop, 0,\
		XmNmarginBottom, 0,\
		NULL);\
#ifndef DESIGN_TIME\
	UxPutContext (Color_RC ,    (char *) UxResourceContext); \
#endif\
\
/*  Creazione del rowcol per le risorse relative alle\
	variabile 1 di cambio colori  */\
VarCC1_rc = (swidget )XtVaCreateWidget ("VarCC1_rc",\
		xmRowColumnWidgetClass, Widres_rc,\
		XmNnumColumns, 100,\
		XmNisAligned, False,\
		XmNspacing, 0,\
		XmNmarginHeight, 0,\
		XmNmarginTop, 0,\
		XmNmarginBottom, 0,\
		NULL);\
#ifndef DESIGN_TIME\
	UxPutContext (VarCC1_rc ,   (char *) UxResourceContext); \
#endif\
\
/*  Creazione del rowcol per le risorse relative alla\
	variabile 2 di cambio colori  */\
VarCC2_rc = (swidget )XtVaCreateWidget ("VarCC2_rc",\
		xmRowColumnWidgetClass, Widres_rc,\
		XmNnumColumns, 100,\
		XmNisAligned, False,\
		XmNspacing, 0,\
		XmNmarginHeight, 0,\
		XmNmarginTop, 0,\
		XmNmarginBottom, 0,\
		NULL);\
#ifndef DESIGN_TIME\
	UxPutContext (VarCC2_rc ,   (char *) UxResourceContext); \
#endif\
\
/*  Creazione del rowcol per le risorse relative alla\
	variabile 3 di cambio colori  */\
VarCC3_rc = (swidget )XtVaCreateWidget ("VarCC3_rc",\
		xmRowColumnWidgetClass, Widres_rc,\
		XmNnumColumns, 100,\
		XmNisAligned, False,\
		XmNspacing, 0,\
		XmNmarginHeight, 0,\
		XmNmarginTop, 0,\
		XmNmarginBottom, 0,\
		NULL);\
#ifndef DESIGN_TIME\
	UxPutContext (VarCC3_rc ,   (char *) UxResourceContext); \
#endif\
\
/*  Creazione del rowcol per le risorse relative alla\
	variabile 4 di cambio colori  */\
VarCC4_rc = (swidget )XtVaCreateWidget ("VarCC4_rc",\
		xmRowColumnWidgetClass, Widres_rc,\
		XmNnumColumns, 100,\
		XmNisAligned, False,\
		XmNspacing, 0,\
		XmNmarginHeight, 0,\
		XmNmarginTop, 0,\
		XmNmarginBottom, 0,\
		NULL);\
#ifndef DESIGN_TIME\
	UxPutContext (VarCC4_rc ,   (char *) UxResourceContext); \
#endif\
}\
\
/**********************************************************\
	Rilegge tutte le risorse del nuovo oggetto selezionato\
	e ne visualizza le risorse, se del vecchio oggetto \
	sono presenti delle modifiche che non sono state salvate\
	viene comunicato con una finestra di dialogo\
**********************************************************/\
\
int EseguiLoadResources()\
{\
Widget WdgAppoggio,OthRes;\
/*\
XlCoreClassRec *classe_oggetto;\
*/\
WidgetClass classe_oggetto;\
\
Boolean Occupato,selezionato;\
char *Appoggio2,appoggio[100];\
int indice;\
XmString StrLab;\
Arg arg[3];\
\
/* Cerca nella drawing area l'oggetto selezionato */\
WdgAppoggio = (Widget )XlGetSelectedWidget (PaginaDrawing);\
\
/*  Mette a False l'attributo InEdit dell'oggetto che si sta per abbandonare */\
if ( (OggettoS != NULL) && (OggettoS != WdgAppoggio) )\
  {\
  XtSetArg (arg[0], XlNinEdit, False);\
  XtSetArg (arg[1], XlNwEdit, NULL);\
  XtSetValues (OggettoS, arg, 2);\
  }\
\
/*  Controlla se l'oggetto selezionato trovato e' gia in edit in un altro\
      Resource Editor  */\
if (WdgAppoggio != NULL)\
  {\
  XtSetArg (arg[0], XlNinEdit, &Occupato);\
  XtGetValues (WdgAppoggio, arg, 1);\
  if (WdgAppoggio == OggettoS) Occupato=False;\
  if (!Occupato) OggettoS = WdgAppoggio;\
  else\
    {\
    XtSetArg (arg[0], XlNwEdit, &OthRes);\
    XtGetValues (WdgAppoggio, arg, 1);\
#ifndef DESIGN_TIME\
    XRaiseWindow (XtDisplay(OthRes),XtWindow(OthRes));\
#endif\
    }\
  }\
\
if ( (OggettoS != NULL) && (!Occupato) )\
	{\
	/*  Setta il valore dell'oggetto selezionato in editazione  */\
	XtSetArg (arg[0], XlNinEdit, True);\
	XtSetArg (arg[1], XlNwEdit, Resource);\
	XtSetValues (OggettoS, arg, 2);\
	set_something (ResetItem, XmNsensitive, True);\
	set_something (pushButton1, XmNsensitive, True);\
	/*  Carico il nome e la classe dell'oggetto selezionato  */\
	strcpy (appoggio,WidGetName(OggettoS));\
	strcat (appoggio,"  ----  ");\
\
\
        classe_oggetto = GetClass (OggettoS);\
	Appoggio2 = XtNewString ( XlGetClassName(classe_oggetto) );\
	strcat (appoggio,Appoggio2);\
	XtFree (Appoggio2);\
	StrLab = XmStringCreateSimple (appoggio);\
	/*  Salvo l'indice del rowcolumn attualmente visualizzato */\
	if (Usato(Geometric_RC)) indice = 0;\
	if (Usato(Specific_RC)) indice = 1;\
	if (Usato(Color_RC)) indice = 2;\
	if (Usato(VarCC1_rc)) indice = 3;\
	if (Usato(VarCC2_rc)) indice = 4;\
	if (Usato(VarCC3_rc)) indice = 5;\
	if (Usato(VarCC4_rc)) indice = 6;\
	/*  Ricreo i rowcolumn delle risorse  */\
	CreaRowColumnRisorse (Widres_rc);\
	PrepListaRes (Geometric_RC, OggettoS, XlRGrGeom, DataBaseTo,\
				PagGetType(PagConf));\
	PrepListaRes (Specific_RC, OggettoS, XlRGrIo, DataBaseTo,\
				PagGetType(PagConf));\
	PrepListaRes (Color_RC, OggettoS, XlRGrColor, DataBaseTo,\
				PagGetType(PagConf));\
	PrepListaRes (VarCC1_rc, OggettoS, XlRGrVCC1, DataBaseTo,\
				PagGetType(PagConf));\
	PrepListaRes (VarCC2_rc, OggettoS, XlRGrVCC2, DataBaseTo,\
				PagGetType(PagConf));\
	PrepListaRes (VarCC3_rc, OggettoS, XlRGrVCC3, DataBaseTo,\
				PagGetType(PagConf));\
	PrepListaRes (VarCC4_rc, OggettoS, XlRGrVCC4, DataBaseTo,\
				PagGetType(PagConf));\
\
	if (indice == 0) XtManageChild (Geometric_RC);\
	if (indice == 1) XtManageChild (Specific_RC);\
	if (indice == 2) XtManageChild (Color_RC);\
	if (indice == 3) XtManageChild (VarCC1_rc);\
	if (indice == 4) XtManageChild (VarCC2_rc);\
	if (indice == 5) XtManageChild (VarCC3_rc);\
	if (indice == 6) XtManageChild (VarCC4_rc);\
	XtManageChild (Widres_rc);\
	/*  Elimino dalla lista il nome del vecchio oggetto\
		ed aggiungo il nome di quello nuovo  */\
	XmListDeleteAllItems (scrolledList1);\
	XmListAddItemUnselected (scrolledList1,StrLab,0);\
	}\
else\
	{\
	if (!Occupato)\
	  {\
	  XmListDeleteAllItems (scrolledList1);\
	  set_something (ResetItem, XmNsensitive, False);\
	  set_something (pushButton1, XmNsensitive, False);\
	  strcpy (appoggio,"No Widget selected");\
	  StrLab = XmStringCreateSimple (appoggio);\
	  XmListAddItemUnselected (scrolledList1, StrLab, 0);\
	  }\
	}\
XmStringFree (StrLab);\
}\
\
/************************************************\
	Setta nella label per la segnalazione degli\
	errori o delle modifiche il segno di errore\
************************************************/\
\
void SettaErrore (Widget Wid)\
{\
XmString Errore;\
char stringa[3];\
\
strcpy (stringa,"X");\
Errore = XmStringCreateSimple (stringa);\
set_something (Wid , XmNlabelString, Errore);\
XmStringFree (Errore);\
}\
\
/*********************************************************\
	Salva tutte le risorse del rowcolumn Riga nel database\
	facendo i controlli che i valori letti dal rowcolumn siano\
	coerenti con i tipi\
*********************************************************/\
\
int EseguiApply (Widget *Riga,int NumFigli,XlConfInfo *confinfo)\
{\
Widget *Ogget,Padre;\
XmString StrLab;\
int i;\
\
int NumeroErrori;\
int index;                   /*  Indice relativo alla confinfo   */\
char *StrIndex;              /*  Stringa dell'indice relativo alla confinfo   */\
\
NumeroErrori = 0;\
Padre = GetPadre (OggettoS);\
StrLab = XmStringCreateSimple (" ");\
for ( i = 0 ; i < NumFigli ; i++ )\
{\
	/*  Legge dal rowcolumn di riga la lista dei suoi figli  */\
	get_something (Riga[i], XmNchildren, &Ogget);\
\
	/*  Azzera la stringa delle modifiche effettuate  */\
	set_something (Ogget[1], XmNlabelString, StrLab);\
\
	/*  Legge l'indice della confinfo relativa alla risorsa \
            memorizzata come nome dell'oggetto nascosto */\
/**************************************************/\
#ifndef DESIGN_TIME\
	StrIndex = XtName(Ogget[3]);\
#endif\
/***************************************************/\
	/*  Converte la stringa dell'indice della confinfo letta\
		in un intero per poter essere utilizzato come indice  */\
	index = atoi (StrIndex);\
	\
\
	NumeroErrori += EseguiControlliInput (confinfo[index],PuntDB,\
						OggettoS,Ogget);\
}\
XmStringFree (StrLab);\
return (NumeroErrori);\
}\
\
/*************************************************************\
   Funzione di callback associata al pushButton presente\
	nella lista delle risorse creata runtime   \
*************************************************************/\
\
int PushColorCB (swidget wid,int ind_res, XmAnyCallbackStruct *call_data)\
{\
	XmString StrLab;\
	char *s;\
	Widget *RCOgget,padre;\
	Widget Creato;\
\
#ifndef DESIGN_TIME\
        _UxCResource *UxSaveCtx,*UxContext;\
\
        UxSaveCtx = UxResourceContext;\
        UxResourceContext = UxContext =\
                        (_UxCResource *)UxGetContext(wid);\
#endif\
\
	/*  Legge i figli del rowcolumn piu' grande  */\
	padre = GetPadre (wid);\
	get_something (padre, XmNchildren, &RCOgget);\
\
	/*  Setta a False l'attributo sensitive del textfield\
		che sta per essere aggiornato     */\
	set_something (RCOgget[2], XmNsensitive, False);\
	set_something (RCOgget[0], XmNsensitive, False);\
\
	/*  Legge la label del bottone  */\
	get_something (RCOgget[0], XmNlabelString, &StrLab);\
	s = XmTextFieldGetString (RCOgget[2]);\
\
	Creato = (Widget )create_ColorViewer(EDITOR_VER,s,StrLab,PuntDB,RCOgget,\
				Resource);\
	UxPopupInterface (Creato , no_grab);\
\
#ifndef DESIGN_TIME\
        UxResourceContext = UxSaveCtx;\
#endif\
\
	XtFree (s);\
return (OK);\
}\
\
/*******************************************************\
   Funzione di callback associata al pushButton presente\
	nella lista delle risorse creata runtime   \
*******************************************************/\
\
int PushVarInpCB (swidget wid,int ind_res, XmAnyCallbackStruct *call_data)\
{\
	Widget *RCOgget,padre;\
	char *StrIndex;\
	int index;\
\
        WidgetClass WidClassSel;\
	XlConfInfo *conf;\
\
#ifndef DESIGN_TIME\
        _UxCResource *UxSaveCtx,*UxContext;\
\
        UxSaveCtx = UxResourceContext;\
        UxResourceContext = UxContext =\
                        (_UxCResource *)UxGetContext(wid);\
#endif\
\
	/*  Legge i figli del rowcolumn piu' grande  */\
	padre = GetPadre (wid);\
	get_something (padre, XmNchildren, &RCOgget);\
\
	/*  Setta a False l'attributo sensitive del textfield\
		che sta per essere aggiornato     */\
	set_something (RCOgget[2], XmNsensitive, False);\
	set_something (RCOgget[0], XmNsensitive, False);\
\
	/*  Legge l'indice della confinfo dal textField nascosto */\
/************************************************/\
#ifndef DESIGN_TIME\
	StrIndex = XtName(RCOgget[3]);\
#endif\
/***************************************************/\
	index = atoi (StrIndex);\
\
	/*  Legge la confinfo dell'oggetto selezionato  */\
\
        WidClassSel = GetClass (OggettoS);  \
	conf = XlGetConfinfoWid (OggettoS);\
	TipoVariabile[0] = conf[index].db_type;\
\
	RigaPerVar [0] = RCOgget [0];\
	RigaPerVar [1] = RCOgget [1];\
	RigaPerVar [2] = RCOgget [2];\
	RigaPerVar [3] = RCOgget [3];\
	UxPopupInterface (VariabEdit, no_grab);\
\
#ifndef DESIGN_TIME\
        UxResourceContext = UxSaveCtx;\
#endif\
\
return (OK);\
}\
\
/*******************************************************\
   Funzione di callback associata al pushButton presente\
	nella lista delle risorse creata runtime   \
*******************************************************/\
\
int PushVarOutCB (swidget wid,int ind_res, XmAnyCallbackStruct *call_data)\
{\
	Widget *RCOgget,padre;\
	char *StrIndex;\
	int index;\
\
        WidgetClass WidClassSel;\
	XlConfInfo *conf;\
\
#ifndef DESIGN_TIME\
        _UxCResource *UxSaveCtx,*UxContext;\
\
        UxSaveCtx = UxResourceContext;\
        UxResourceContext = UxContext =\
                        (_UxCResource *)UxGetContext(wid);\
#endif\
\
	/*  Legge i figli del rowcolumn piu' grande  */\
	padre = GetPadre (wid);\
	get_something (padre, XmNchildren, &RCOgget);\
\
	/*  Setta a False l'attributo sensitive del textfield\
		che sta per essere aggiornato     */\
	set_something (RCOgget[2], XmNsensitive, False);\
	set_something (RCOgget[0], XmNsensitive, False);\
\
	/*  Legge l'indice della confinfo dal textField nascosto */\
/***********************************/\
#ifndef DESIGN_TIME\
	StrIndex = XtName(RCOgget[3]);\
#endif\
/*******************************/\
	index = atoi (StrIndex);\
\
	/*  Legge la confinfo dell'oggetto selezionato  */\
\
	WidClassSel = GetClass (OggettoS);\
	conf = XlGetConfinfoWid (OggettoS);\
	TipoVariabile[0] = conf[index].db_type;\
\
	RigaPerVar [0] = RCOgget [0];\
	RigaPerVar [1] = RCOgget [1];\
	RigaPerVar [2] = RCOgget [2];\
	RigaPerVar [3] = RCOgget [3];\
	UxPopupInterface (VariabEdit, no_grab);\
\
#ifndef DESIGN_TIME\
        UxResourceContext = UxSaveCtx;\
#endif\
\
return (OK);\
}\
\
/*******************************************************\
   Funzione di callback associata al pushButton presente\
	nella lista delle risorse creata runtime   \
*******************************************************/\
\
int PushFontCB (swidget wid,int ind_res, XmAnyCallbackStruct *call_data)\
{\
	char *s;\
	Widget *RCOgget,padre;\
	Widget Creato;\
\
#ifndef DESIGN_TIME\
        _UxCResource *UxSaveCtx,*UxContext;\
\
        UxSaveCtx = UxResourceContext;\
        UxResourceContext = UxContext =\
                        (_UxCResource *)UxGetContext(wid);\
#endif\
\
	/*  Legge i figli del rowcolumn piu' grande  */\
	padre = GetPadre (wid);\
	get_something (padre, XmNchildren, &RCOgget);\
\
	/*  Setta a False l'attributo sensitive del textfield\
		che sta per essere aggiornato     */\
	set_something (RCOgget[2], XmNsensitive, False);\
	set_something (RCOgget[0], XmNsensitive, False);\
\
	/*  Legge la label del bottone  */\
	s = (char *)XmTextFieldGetString (RCOgget[2]);\
	Creato = (Widget )create_FontsViewer(s,RCOgget,Resource);\
\
	UxPopupInterface (Creato , no_grab);\
\
#ifndef DESIGN_TIME\
        UxResourceContext = UxSaveCtx;\
#endif\
\
	XtFree (s);\
return (OK);\
}\
\
/*******************************************************\
   Funzione di callback associata al pushButton presente\
	nella lista delle risorse creata runtime   \
*******************************************************/\
\
int PushIconCB (swidget wid,int ind_res, XmAnyCallbackStruct *call_data)\
{\
	char *BitmapWid="Bitmap";\
        char *ChangeWid="ChangePage";\
	char *IconWid="Icon";\
	char *IconRegWid="IconReg";\
	WidgetClass ClassWidSel;\
	char *NomeClasseSel;\
	Widget *RCOgget,padre;\
	Widget Creato;\
	char *Stringa;\
\
#ifndef DESIGN_TIME\
        _UxCResource *UxSaveCtx,*UxContext;\
\
        UxSaveCtx = UxResourceContext;\
        UxResourceContext = UxContext =\
                        (_UxCResource *)UxGetContext(wid);\
#endif\
\
	ClassWidSel = (WidgetClass)GetClass (OggettoS);\
	NomeClasseSel = XlGetClassName (ClassWidSel);\
\
	/*  Legge i figli del rowcolumn piu' grande  */\
	padre = GetPadre (wid);\
	get_something (padre, XmNchildren, &RCOgget);\
\
	/*  Setta a False l'attributo sensitive del textfield\
		che sta per essere aggiornato     */\
	set_something (RCOgget[2], XmNsensitive, False);\
	set_something (RCOgget[0], XmNsensitive, False);\
\
	Stringa = (char *)CvtPixToStr (OggettoS,XmNbackground);\
/*\
Aggiunta per bitmap su ChangePage\
*/\
	if ( (strcmp(NomeClasseSel,ChangeWid)) == 0 ) \
		Creato = (Widget )create_AnimateIconSelection(SEL_BITMAP,\
					Resource,RCOgget,OggettoS,Stringa);\
\
/* carlo 7/7/97\
*/\
        if( XlIsOperableKeys(OggettoS) ||\
            XlIsPixvar(OggettoS) ||\
            ( strcmp(NomeClasseSel,BitmapWid) == 0) )\
		Creato = (Widget )create_AnimateIconSelection(SEL_BITMAP,\
					Resource,RCOgget,OggettoS,Stringa);\
/*       \
	if ( (strcmp(NomeClasseSel,BitmapWid)) == 0 ) \
		Creato = (Widget )create_AnimateIconSelection(SEL_BITMAP,\
					Resource,RCOgget,OggettoS,Stringa);\
*/\
	else if ( (strcmp(NomeClasseSel,IconWid) == 0) ||\
		(strcmp(NomeClasseSel,IconRegWid)== 0) ||\
                (strcmp(NomeClasseSel,XlCPictograph)==0) )\
		Creato = (Widget )create_AnimateIconSelection (SEL_ICONA,\
					Resource,RCOgget,OggettoS,Stringa);\
\
	UxPopupInterface (Creato , no_grab);\
\
#ifndef DESIGN_TIME\
        UxResourceContext = UxSaveCtx;\
#endif\
	XtFree (Stringa);\
return (OK);\
}\
\
/*******************************************************\
   Funzione di callback associata al pushButton presente\
	nella lista delle risorse creata runtime   \
*******************************************************/\
\
int PushFormCB (swidget wid,int ind_res, XmAnyCallbackStruct *call_data)\
{\
	Widget *RCOgget,padre;\
	Widget Creato;\
\
#ifndef DESIGN_TIME\
        _UxCResource *UxSaveCtx,*UxContext;\
\
        UxSaveCtx = UxResourceContext;\
        UxResourceContext = UxContext =\
                        (_UxCResource *)UxGetContext(wid);\
#endif\
\
	/*  Legge i figli del rowcolumn piu' grande  */\
	padre = GetPadre (wid);\
	get_something (padre, XmNchildren, &RCOgget);\
\
	/*  Setta a False l'attributo sensitive del textfield\
		che sta per essere aggiornato     */\
	set_something (RCOgget[2], XmNsensitive, False);\
	set_something (RCOgget[0], XmNsensitive, False);\
\
	Creato = (Widget )create_FormSelection(Resource,RCOgget);\
\
	UxPopupInterface (Creato , no_grab);\
\
#ifndef DESIGN_TIME\
        UxResourceContext = UxSaveCtx;\
#endif\
return (OK);\
}\
\
/*******************************************************\
   Funzione di callback associata al pushButton presente\
	nella lista delle risorse creata runtime   \
*******************************************************/\
\
int PushVarRegCB (swidget wid,int ind_res, XmAnyCallbackStruct *call_data)\
{\
	Widget *RCOgget,padre;\
	Widget Creato;\
\
#ifndef DESIGN_TIME\
        _UxCResource *UxSaveCtx,*UxContext;\
\
        UxSaveCtx = UxResourceContext;\
        UxResourceContext = UxContext =\
                        (_UxCResource *)UxGetContext(wid);\
#endif\
\
	/*  Legge i figli del rowcolumn piu' grande  */\
	padre = GetPadre (wid);\
	get_something (padre, XmNchildren, &RCOgget);\
\
	/*  Setta a False l'attributo sensitive del textfield\
		che sta per essere aggiornato     */\
	set_something (RCOgget[2], XmNsensitive, False);\
	set_something (RCOgget[0], XmNsensitive, False);\
\
	Creato = (Widget )create_VariablesSelection(Resource,RCOgget,\
		OggettoS);\
\
	UxPopupInterface (Creato , no_grab);\
\
#ifndef DESIGN_TIME\
        UxResourceContext = UxSaveCtx;\
#endif\
return (OK);\
}\
\
/*******************************************************\
   Funzione di callback associata al pushButton presente\
	nella lista delle risorse creata runtime   \
*******************************************************/\
\
int PushInputCB (swidget wid,int ind_res, XmAnyCallbackStruct *call_data)\
{\
	char Messaggio[100];\
	Widget *RCOgget,padre;\
	Widget Creato;\
	OlFormObject PuntatoreForm;\
\
#ifndef DESIGN_TIME\
        _UxCResource *UxSaveCtx,*UxContext;\
\
        UxSaveCtx = UxResourceContext;\
        UxResourceContext = UxContext =\
                        (_UxCResource *)UxGetContext(wid);\
#endif\
	/*  Controlla se e' stata precedentemente caricata la form  */\
	get_something (OggettoS, XlNobjectForm, &PuntatoreForm);\
   	if (PuntatoreForm == NULL)\
	  {\
	  strcpy (Messaggio,"Form file not loaded!");\
	  VisualizzaMessageBox(GENERICA,Resource,Messaggio,OggettoS);\
	  } \
	else\
	  {\
	  /*  Legge i figli del rowcolumn piu' grande  */\
	  padre = GetPadre (wid);\
	  get_something (padre, XmNchildren, &RCOgget);\
\
	  /*  Setta a False l'attributo sensitive del textfield\
		che sta per essere aggiornato     */\
	  set_something (RCOgget[2], XmNsensitive, False);\
	  set_something (RCOgget[0], XmNsensitive, False);\
\
	  Creato = (Widget )create_ValueSelection (Resource,RCOgget,OggettoS,PuntatoreForm);\
	  UxPopupInterface (Creato, no_grab);\
	  }\
\
#ifndef DESIGN_TIME\
        UxResourceContext = UxSaveCtx;\
#endif\
return (OK);\
}\
\
/**************************************************************\
   Funzione di callback associata al pushButton dell'OptionMenu\
	presente nella lista delle risorse creata runtime   \
**************************************************************/\
\
int OptResCB (swidget wid,int ind_res, XmAnyCallbackStruct *call_data)\
{\
	Widget *Riga;\
	Widget Parent;\
\
	Parent = GetPadre (wid);\
	Parent = GetPadre (Parent);\
	Parent = GetPadre (Parent);\
	get_something (Parent, XmNchildren, &Riga);\
	SettaModifica (Riga[1]);	\
\
return (OK);\
}\
\
/*******************************************************\
   Funzione di callback associata al pushButton presente\
	nella lista delle risorse creata runtime   \
*******************************************************/\
\
int PushCompCB (swidget wid,int ind_res, XmAnyCallbackStruct *call_data)\
{\
	Widget *RCOgget,padre;\
	Widget Creato;\
\
#ifndef DESIGN_TIME\
        _UxCResource *UxSaveCtx,*UxContext;\
\
        UxSaveCtx = UxResourceContext;\
        UxResourceContext = UxContext =\
                        (_UxCResource *)UxGetContext(wid);\
#endif\
\
        /*  Legge i figli del rowcolumn piu' grande  */\
	padre = GetPadre (wid);\
	get_something (padre, XmNchildren, &RCOgget);\
\
	/*  Setta a False l'attributo sensitive del textfield\
		che sta per essere aggiornato     */\
	set_something (RCOgget[2], XmNsensitive, False);\
	set_something (RCOgget[0], XmNsensitive, False);\
\
	Creato = (Widget )create_DatabaseSelection(Resource,SEL_COMP,RCOgget,\
					DataBaseTo);\
	UxPopupInterface (Creato , no_grab);\
\
#ifndef DESIGN_TIME\
        UxResourceContext = UxSaveCtx;\
#endif\
\
return (OK);\
}\
\
/*******************************************************\
   Funzione di callback associata al pushButton presente\
	nella lista delle risorse creata runtime   \
*******************************************************/\
\
int PushSubSCB (swidget wid,int ind_res, XmAnyCallbackStruct *call_data)\
{\
	Widget *RCOgget,padre;\
	Widget Creato;\
\
#ifndef DESIGN_TIME\
        _UxCResource *UxSaveCtx,*UxContext;\
\
        UxSaveCtx = UxResourceContext;\
        UxResourceContext = UxContext =\
                        (_UxCResource *)UxGetContext(wid);\
#endif\
\
        /*  Legge i figli del rowcolumn piu' grande  */\
	padre = GetPadre (wid);\
	get_something (padre, XmNchildren, &RCOgget);\
\
	/*  Setta a False l'attributo sensitive del textfield\
		che sta per essere aggiornato     */\
	set_something (RCOgget[2], XmNsensitive, False);\
	set_something (RCOgget[0], XmNsensitive, False);\
\
	Creato = (Widget )create_DatabaseSelection(Resource,SEL_SUBS,RCOgget,\
					DataBaseTo);\
	UxPopupInterface (Creato , no_grab);\
\
#ifndef DESIGN_TIME\
        UxResourceContext = UxSaveCtx;\
#endif\
\
return (OK);\
}\
\
/**************************************************************\
   Funzione di callback associata alla modifica della stringa\
	presente nel textfield della lista delle risorse   \
**************************************************************/\
\
int TextResCB (swidget wid,int ind_res, XmAnyCallbackStruct *call_data)\
{\
	Widget *Riga;\
	Widget Parent;\
\
#ifndef DESIGN_TIME\
        _UxCResource *UxSaveCtx,*UxContext;\
\
        UxSaveCtx = UxResourceContext;\
        UxResourceContext = UxContext =\
                        (_UxCResource *)UxGetContext(wid);\
#endif\
\
	Parent = GetPadre (wid);\
	get_something (Parent, XmNchildren, &Riga);\
	SettaModifica (Riga[1]);	\
\
#ifndef DESIGN_TIME\
        UxResourceContext = UxSaveCtx;\
#endif\
\
return (OK);\
}\
\
/*************************************************************\
    Funzione di callback associata al pushButton dell'OptionMenu \
	per la selezione dei gruppi di risorse da visualizzare  \
*************************************************************/\
\
int OptMenuCB (swidget wid,int ind_voce, XmAnyCallbackStruct *call_data)\
{\
#ifndef DESIGN_TIME\
        _UxCResource *UxSaveCtx,*UxContext;\
\
        UxSaveCtx = UxResourceContext;\
        UxResourceContext = UxContext =\
                        (_UxCResource *)UxGetContext(wid);\
#endif\
\
	if (Usato (Geometric_RC)) XtUnmanageChild (Geometric_RC);\
	if (Usato (Specific_RC))  XtUnmanageChild (Specific_RC);\
	if (Usato (Color_RC))     XtUnmanageChild (Color_RC);\
	if (Usato (VarCC1_rc))    XtUnmanageChild (VarCC1_rc);\
	if (Usato (VarCC2_rc))    XtUnmanageChild (VarCC2_rc);\
	if (Usato (VarCC3_rc))    XtUnmanageChild (VarCC3_rc);\
	if (Usato (VarCC4_rc))    XtUnmanageChild (VarCC4_rc);\
\
	switch (ind_voce)\
	{\
	case 0:\
		XtManageChild (Geometric_RC);\
	break;\
	case 1:\
		XtManageChild (Specific_RC);\
	break;\
	case 2:\
		XtManageChild (Color_RC);\
	break;\
	case 3:\
		XtManageChild (VarCC1_rc);\
	break;\
	case 4:\
		XtManageChild (VarCC2_rc);\
	break;\
	case 5:\
		XtManageChild (VarCC3_rc);\
	break;\
	case 6:\
		XtManageChild (VarCC4_rc);\
	break;\
	}		\
\
#ifndef DESIGN_TIME\
        UxResourceContext = UxSaveCtx;\
#endif\
return (OK);\
}\
\
/**************************************************************\
	Creazione di un pushButton\
**************************************************************/\
\
Widget CreaPushButton (parent, nome, label, width)\
Widget parent;\
char *nome;\
XmString label;\
Dimension width;\
{\
        Widget appo;\
        Arg args[6];\
        int narg;\
\
        narg = 0;\
        XtSetArg (args[narg], XmNmarginHeight, 0); narg++;\
        XtSetArg (args[narg], XmNmarginTop, 0); narg++;\
        XtSetArg (args[narg], XmNmarginBottom, 0); narg++;\
        if (width != NULL)\
        {\
                XtSetArg (args[narg], XmNrecomputeSize, FALSE ); narg++;\
                XtSetArg (args[narg], XmNwidth, width ); narg++;\
        }\
        XtSetArg (args[narg], XmNlabelString, label); narg++;\
        appo = XmCreatePushButton (parent, nome, args, narg);\
        XtManageChild (appo);\
\
#ifndef DESIGN_TIME\
		UxPutContext(appo,(char *) UxResourceContext);\
#endif\
\
        return (appo);\
}\
\
/*****************************************************************\
	Creazione dell'option menu dei gruppi \
*****************************************************************/\
\
int CreaOptionMenu (Widget Padre,Widget ogg)\
{\
        Widget  *ButtGruppi;\
        char  *label_butt;\
	extern int NumGruppi;\
        int i;\
        XmString StrLab;\
\
        XtDestroyWidget (CoreItem);\
        ButtGruppi = (Widget *)XtCalloc (NumGruppi, sizeof(Widget));\
        if (ButtGruppi == NULL) return (NON_ALLOCATA);\
        for ( i = 0 ; i < NumGruppi ; i++ )\
        {\
                label_butt = XtNewString ( Gruppi_resource[i] );\
                StrLab = XmStringCreateSimple (label_butt);\
                ButtGruppi[i] = (Widget )CreaPushButton (ogg, "optbt",\
					StrLab, NULL);\
                XtAddCallback (ButtGruppi[i],XmNactivateCallback, OptMenuCB,i);\
		XtFree (label_butt);\
		XmStringFree (StrLab);\
        }\
        set_something (Padre, XmNmenuHistory, ButtGruppi[1]);\
        return (OK);\
}\
\
/***********************************************************\
	Creazione di un TextField\
***********************************************************/\
\
Widget CreaTextField (parent, nome, label, width)\
Widget parent;\
char *nome,*label;\
Dimension width;\
\
{\
        Widget appo;\
        Arg args[10];\
        int narg;\
\
        narg = 0;\
        XtSetArg (args[narg], XmNmarginHeight, 0); narg++;\
        XtSetArg (args[narg], XmNmarginTop, 0); narg++;\
        XtSetArg (args[narg], XmNmarginBottom, 0); narg++;\
        if (width != NULL)\
        {\
                XtSetArg (args[narg], XmNrecomputeSize, FALSE ); narg++;\
                XtSetArg (args[narg], XmNwidth, width ); narg++;\
        }\
        XtSetArg (args[narg], XmNvalue, label); narg++;\
        appo = (Widget )XmCreateTextField (parent, nome, args, narg);\
        XtManageChild (appo);\
\
#ifndef DESIGN_TIME\
		UxPutContext(appo,(char *) UxResourceContext);\
#endif\
\
       return (appo);\
}\
\
/*********************************************\
  disabilita i bottoni di load,close,reset\
  del resource editor quando e' stato lanciato \
  il draw o il bitmap editor\
**********************************************/   \
void disableButton()\
{\
   set_something(pushButton15,XmNsensitive,False); /* load button*/\
   set_something(LoadItem,XmNsensitive,False);     /* load item menu */ \
   set_something(CloseItem,XmNsensitive,False);    /* close item menu */\
   set_something(ResetItem,XmNsensitive,False);    /* reset item menu */ \
}\
\
/*********************************************\
  riabilita i bottoni di load,close,reset\
  del resource editor quando viene chiusi  \
  il draw o il bitmap editor\
**********************************************/   \
void riableButton()\
{\
   set_something(pushButton15,XmNsensitive,True); /* load button*/\
   set_something(LoadItem,XmNsensitive,True);     /* load item menu */ \
   set_something(CloseItem,XmNsensitive,True);    /* close item menu */\
   set_something(ResetItem,XmNsensitive,True);    /* reset item menu */ \
}\

*Resource.static: true
*Resource.name: Resource
*Resource.parent: NO_PARENT
*Resource.parentExpression: PagConf->topwidget
*Resource.x: 424
*Resource.y: 5
*Resource.width: 550
*Resource.height: 600
*Resource.iconName: "Resource Editor"
*Resource.title: "Widget Resource Editor"
*Resource.allowShellResize: "true"
*Resource.deleteResponse: "do_nothing"

*mainWindow1.class: mainWindow
*mainWindow1.static: true
*mainWindow1.name: mainWindow1
*mainWindow1.parent: Resource
*mainWindow1.unitType: "pixels"
*mainWindow1.x: 15
*mainWindow1.y: 25
*mainWindow1.width: 545
*mainWindow1.height: 480

*panedWindow1.class: panedWindow
*panedWindow1.static: true
*panedWindow1.name: panedWindow1
*panedWindow1.parent: mainWindow1

*form1.class: form
*form1.static: true
*form1.name: form1
*form1.parent: panedWindow1
*form1.resizePolicy: "resize_none"
*form1.x: 3
*form1.y: 3
*form1.width: 539
*form1.height: 87
*form1.paneMaximum: 1000
*form1.paneMinimum: 80

*scrolledWindow1.class: scrolledWindow
*scrolledWindow1.static: true
*scrolledWindow1.name: scrolledWindow1
*scrolledWindow1.parent: form1
*scrolledWindow1.scrollingPolicy: "application_defined"
*scrolledWindow1.x: 20
*scrolledWindow1.y: 30
*scrolledWindow1.visualPolicy: "variable"
*scrolledWindow1.scrollBarDisplayPolicy: "static"
*scrolledWindow1.shadowThickness: 0
*scrolledWindow1.bottomAttachment: "attach_position"
*scrolledWindow1.bottomOffset: 0
*scrolledWindow1.leftOffset: 0
*scrolledWindow1.rightAttachment: "attach_position"
*scrolledWindow1.rightOffset: 0
*scrolledWindow1.leftAttachment: "attach_position"
*scrolledWindow1.topAttachment: "attach_position"
*scrolledWindow1.topOffset: 0
*scrolledWindow1.bottomPosition: 90
*scrolledWindow1.leftPosition: 3
*scrolledWindow1.rightPosition: 97
*scrolledWindow1.topPosition: 45

*scrolledList1.class: scrolledList
*scrolledList1.static: true
*scrolledList1.name: scrolledList1
*scrolledList1.parent: scrolledWindow1
*scrolledList1.width: 435
*scrolledList1.height: 50

*label1.class: label
*label1.static: true
*label1.name: label1
*label1.parent: form1
*label1.x: 15
*label1.y: 10
*label1.width: 135
*label1.height: 25
*label1.leftOffset: 0
*label1.topAttachment: "attach_position"
*label1.topOffset: 0
*label1.labelString: "Selected widget:"
*label1.bottomAttachment: "attach_position"
*label1.bottomOffset: 0
*label1.bottomWidget: ""
*label1.bottomPosition: 40
*label1.leftAttachment: "attach_position"
*label1.leftPosition: 3
*label1.rightAttachment: "attach_position"
*label1.rightPosition: 25
*label1.topPosition: 2

*form2.class: form
*form2.static: true
*form2.name: form2
*form2.parent: panedWindow1
*form2.resizePolicy: "resize_none"
*form2.x: 3
*form2.y: 91
*form2.width: 557
*form2.height: 317
*form2.paneMinimum: 150
*form2.paneMaximum: 1000

*scrolledWindow2.class: scrolledWindow
*scrolledWindow2.static: true
*scrolledWindow2.name: scrolledWindow2
*scrolledWindow2.parent: form2
*scrolledWindow2.scrollingPolicy: "automatic"
*scrolledWindow2.x: 10
*scrolledWindow2.y: 50
*scrolledWindow2.width: 510
*scrolledWindow2.height: 120
*scrolledWindow2.bottomAttachment: "attach_position"
*scrolledWindow2.bottomOffset: 0
*scrolledWindow2.leftOffset: 0
*scrolledWindow2.rightAttachment: "attach_position"
*scrolledWindow2.rightOffset: 0
*scrolledWindow2.topAttachment: "attach_position"
*scrolledWindow2.topOffset: 0
*scrolledWindow2.leftAttachment: "attach_position"
*scrolledWindow2.bottomPosition: 90
*scrolledWindow2.leftPosition: 3
*scrolledWindow2.rightPosition: 97
*scrolledWindow2.topPosition: 10

*Widres_rc.class: rowColumn
*Widres_rc.static: true
*Widres_rc.name: Widres_rc
*Widres_rc.parent: scrolledWindow2
*Widres_rc.x: 2
*Widres_rc.y: 2
*Widres_rc.width: 128
*Widres_rc.height: 180
*Widres_rc.navigationType: "tab_group"
*Widres_rc.isAligned: "false"
*Widres_rc.numColumns: 100
*Widres_rc.resizeHeight: "false"
*Widres_rc.resizeWidth: "false"

*Geometric_RC.class: rowColumn
*Geometric_RC.static: true
*Geometric_RC.name: Geometric_RC
*Geometric_RC.parent: Widres_rc
*Geometric_RC.x: 3
*Geometric_RC.y: 3
*Geometric_RC.width: 122
*Geometric_RC.height: 16
*Geometric_RC.isAligned: "false"
*Geometric_RC.numColumns: 100
*Geometric_RC.resizeWidth: "false"
*Geometric_RC.resizeHeight: "false"
*Geometric_RC.spacing: 10

*Specific_RC.class: rowColumn
*Specific_RC.static: true
*Specific_RC.name: Specific_RC
*Specific_RC.parent: Widres_rc
*Specific_RC.x: 5
*Specific_RC.y: 25
*Specific_RC.width: 120
*Specific_RC.height: 30

*Color_RC.class: rowColumn
*Color_RC.static: true
*Color_RC.name: Color_RC
*Color_RC.parent: Widres_rc
*Color_RC.x: 5
*Color_RC.y: 40
*Color_RC.width: 120
*Color_RC.height: 30

*VarCC1_rc.class: rowColumn
*VarCC1_rc.static: true
*VarCC1_rc.name: VarCC1_rc
*VarCC1_rc.parent: Widres_rc
*VarCC1_rc.x: 10
*VarCC1_rc.y: 70
*VarCC1_rc.width: 110
*VarCC1_rc.height: 20

*VarCC2_rc.class: rowColumn
*VarCC2_rc.static: true
*VarCC2_rc.name: VarCC2_rc
*VarCC2_rc.parent: Widres_rc
*VarCC2_rc.x: 10
*VarCC2_rc.y: 100
*VarCC2_rc.width: 110
*VarCC2_rc.height: 10

*VarCC3_rc.class: rowColumn
*VarCC3_rc.static: true
*VarCC3_rc.name: VarCC3_rc
*VarCC3_rc.parent: Widres_rc
*VarCC3_rc.x: 10
*VarCC3_rc.y: 100
*VarCC3_rc.width: 80
*VarCC3_rc.height: 10

*VarCC4_rc.class: rowColumn
*VarCC4_rc.static: true
*VarCC4_rc.name: VarCC4_rc
*VarCC4_rc.parent: Widres_rc
*VarCC4_rc.x: 10
*VarCC4_rc.y: 160
*VarCC4_rc.width: 110
*VarCC4_rc.height: 20

*menu2.class: rowColumn
*menu2.static: true
*menu2.name: menu2
*menu2.parent: form2
*menu2.rowColumnType: "menu_option"
*menu2.subMenuId: "GruppiPane"
*menu2.topOffset: 0
*menu2.leftOffset: 0
*menu2.topAttachment: "attach_position"
*menu2.bottomAttachment: "attach_position"
*menu2.bottomOffset: 0
*menu2.bottomWidget: ""
*menu2.bottomPosition: 8
*menu2.leftAttachment: "attach_position"
*menu2.leftPosition: 3
*menu2.rightAttachment: "attach_position"
*menu2.rightPosition: 40
*menu2.topPosition: 2

*GruppiPane.class: rowColumn
*GruppiPane.static: true
*GruppiPane.name: GruppiPane
*GruppiPane.parent: menu2
*GruppiPane.rowColumnType: "menu_pulldown"

*CoreItem.class: pushButton
*CoreItem.name.source: public
*CoreItem.static: false
*CoreItem.name: CoreItem
*CoreItem.parent: GruppiPane
*CoreItem.labelString: "Core"
*CoreItem.mappedWhenManaged: "false"

*pushButton1.class: pushButton
*pushButton1.static: true
*pushButton1.name: pushButton1
*pushButton1.parent: form2
*pushButton1.x: 220
*pushButton1.y: 430
*pushButton1.width: 125
*pushButton1.height: 30
*pushButton1.bottomAttachment: "attach_position"
*pushButton1.bottomOffset: 0
*pushButton1.leftAttachment: "attach_position"
*pushButton1.leftOffset: 0
*pushButton1.labelString: "Apply"
*pushButton1.activateCallback: {\
#ifdef ON_PAGEDIT  \
	extern void AddTransWid ();\
        extern Boolean PagGetConnectMode();\
	extern float get_def_zoom();\
#endif\
int perc_zoom;\
/*\
XlCoreClassRec *WidClassSel; \
*/\
WidgetClass WidClassSel;\
XlConfInfo *confinfo;\
XmString Errore;\
char *NomeOggetto,appo[100];\
Widget PaginaGrafica,*Riga;\
int NumFigli;\
int NumErr;\
XrmDatabase DefDB;\
\
/***\
	Salva il database del display\
***/\
DefDB = (XrmDatabase )XrmGetDatabase (UxDisplay);\
\
NumErr = 0;\
/*  Ricava la classe dell'oggetto selezionato  */\
/*\
WidClassSel = (XlCoreClassRec *) GetClass(OggettoS);\
*/\
WidClassSel = GetClass(OggettoS);\
\
/*  Esegue apply delle risorse del gruppo Geometric  */\
get_something (Geometric_RC, XmNchildren, &Riga);\
get_something (Geometric_RC, XmNnumChildren, &NumFigli);\
confinfo = XlGetConfinfoCore (OggettoS);\
NumErr += EseguiApply (Riga , NumFigli, confinfo);\
\
/*  Esegue apply delle risorse del gruppo IO Variable  */\
get_something (Specific_RC, XmNchildren, &Riga);\
get_something (Specific_RC, XmNnumChildren, &NumFigli);\
confinfo = XlGetConfinfoWid (OggettoS);\
NumErr += EseguiApply (Riga, NumFigli, confinfo);\
\
/*  Esegue apply delle risorse del gruppo Color   */\
get_something (Color_RC, XmNchildren, &Riga);\
get_something (Color_RC, XmNnumChildren, &NumFigli);\
NumErr += EseguiApply (Riga, NumFigli, confinfo);\
\
/*  Esegue apply delle risorse del gruppo VCC1   */\
get_something (VarCC1_rc, XmNchildren, &Riga);\
get_something (VarCC1_rc, XmNnumChildren, &NumFigli);\
NumErr += EseguiApply (Riga, NumFigli, confinfo);\
\
/*  Esegue apply delle risorse del gruppo VCC2   */\
get_something (VarCC2_rc, XmNchildren, &Riga);\
get_something (VarCC2_rc, XmNnumChildren, &NumFigli);\
NumErr += EseguiApply (Riga, NumFigli, confinfo);\
\
/*  Esegue apply delle risorse del gruppo VCC3   */\
get_something (VarCC3_rc, XmNchildren, &Riga);\
get_something (VarCC3_rc, XmNnumChildren, &NumFigli);\
NumErr += EseguiApply (Riga, NumFigli, confinfo);\
\
/*  Esegue apply delle risorse del gruppo VCC4   */\
get_something (VarCC4_rc, XmNchildren, &Riga);\
get_something (VarCC4_rc, XmNnumChildren, &NumFigli);\
NumErr += EseguiApply (Riga, NumFigli, confinfo);\
\
/*  Distrugge e ricrea l'oggetto selezionato per leggere \
	le nuove risorse dal database   */\
if (NumErr != 0)\
	{\
	strcpy (appo,"An error detected in input!");\
	VisualizzaMessageBox (GENERICA, Resource, appo, OggettoS); \
	}\
else\
	{\
	PaginaGrafica = GetPadre (OggettoS);\
	NomeOggetto = XtNewString (WidGetName(OggettoS));\
/*\
 Nel caso icona di regolazione gestisce gli eventuali spostamenti\
 di connessioni legate all'icona\
*/\
#ifdef ON_PAGEDIT\
	if(XlIsIconReg(OggettoS))\
        	apply_gest_conn1(OggettoS);\
#endif        \
\
	XtDestroyWidget (OggettoS);\
/***\
	Setta per la ricreazione dell'oggetto modificato il display\
	relativo alla pagina\
***/\
	XrmSetDatabase (UxDisplay,PuntDB);\
\
	OggettoS = (Widget )XtVaCreateManagedWidget ( NomeOggetto,\
		WidClassSel, PaginaGrafica,\
		XlNselected, True,\
		XlNinEdit, True,\
		XlNwEdit, Resource,\
		NULL);\
#ifdef ON_PAGEDIT\
/*\
 se e' settato lo zoom di pagina bisogna tenerne conto\
 nel ricreare l'oggetto (se l'oggetto non e' figlio\
 di XlComposite\
*/\
	\
	if(XlIsXlComposite(XtParent(OggettoS))==False)\
		{\
		perc_zoom=100.0 * get_def_zoom(PagConf->drawing);\
		set_something(OggettoS,XlNfattZoom,perc_zoom);\
		}\
\
	if(XlIsIconReg(OggettoS))\
/*\
 gestisce eventuali spostamenti delle connessioni\
*/\
		apply_gest_conn2(OggettoS);\
#endif	\
	XtFree (NomeOggetto);\
\
/***\
	Ricarica nella struttura di UxDisplay il database di default\
***/\
	XrmSetDatabase (UxDisplay,DefDB);\
	}\
\
#ifdef ON_PAGEDIT \
	AddTransWid (PagConf,OggettoS);\
/*\
 Se la pagina e' di regolazione puo' darsi che\
 sia in connect mode: in tal caso deve essere\
 nuovamente settato il flag di connect mode sulle\
 porte dell'oggetto ricreato\
*/\
	if(PagGetConnectMode(PagConf->drawing))\
		{\
		set_connect(PaginaGrafica ,True);\
		}\
\
/*\
	se l'oggetto e' una icona di regolazione, una porta, un dispReg\
	e' neccessario settare il display mode attivo sulla pagina\
*/\
	SetSetMode(OggettoS);\
\
#endif\
\
}
*pushButton1.leftPosition: 30
*pushButton1.rightAttachment: "attach_position"
*pushButton1.rightPosition: 70
*pushButton1.rightOffset: 0
*pushButton1.topAttachment: "attach_position"
*pushButton1.topOffset: 0
*pushButton1.topWidget: ""
*pushButton1.bottomPosition: 98
*pushButton1.topPosition: 92

*pushButton15.class: pushButton
*pushButton15.static: true
*pushButton15.name: pushButton15
*pushButton15.parent: form2
*pushButton15.x: 130
*pushButton15.y: 430
*pushButton15.width: 125
*pushButton15.height: 30
*pushButton15.labelString: "Load"
*pushButton15.bottomAttachment: "attach_position"
*pushButton15.bottomOffset: 0
*pushButton15.leftOffset: 0
*pushButton15.rightAttachment: "attach_position"
*pushButton15.rightOffset: 0
*pushButton15.rightWidget: ""
*pushButton15.topOffset: 0
*pushButton15.activateCallback: {\
Boolean ModificheGeometric; /*  Variabile identificazione modifiche apportate\
				alle risorse di geometric  */\
Boolean ModificheSpecific;  /*  Variabile identificazione modifiche apportate\
				alle risorse di specific   */\
Boolean ModificheColor;     /*  Variabile identificazione modifiche apportate\
				alle risorse di color      */\
Boolean ModificheVCC1;	    /*  Variabile identificazione modifiche apportate\
				alle risorse della variabile cambio colore 1 */\
Boolean ModificheVCC2;	    /*  Variabile identificazione modifiche apportate\
				alle risorse della variabile cambio colore 2 */\
Boolean ModificheVCC3;	    /*  Variabile identificazione modifiche apportate\
				alle risorse della variabile cambio colore 3 */\
Boolean ModificheVCC4;	    /*  Variabile identificazione modifiche apportate\
				alle risorse della variabile cambio colore 4 */\
\
char Str[100];\
\
/*\
	Controllo se sono state fatte modifiche che non \
	sono state applicate     \
*/\
ModificheGeometric = ControllaModifiche (Geometric_RC);\
ModificheSpecific = ControllaModifiche (Specific_RC);\
ModificheColor = ControllaModifiche (Color_RC);\
ModificheVCC1 = ControllaModifiche (VarCC1_rc);\
ModificheVCC2 = ControllaModifiche (VarCC2_rc);\
ModificheVCC3 = ControllaModifiche (VarCC3_rc);\
ModificheVCC4 = ControllaModifiche (VarCC4_rc);\
\
if (ModificheGeometric || ModificheSpecific || ModificheColor \
	|| ModificheVCC1 || ModificheVCC2 || ModificheVCC3 || ModificheVCC4)\
	{\
	strcpy (Str,"You have not applied new modific,continue?");\
	VisualizzaMessageBox (LOAD,Resource,Str,OggettoS);\
	}\
else EseguiLoadResources();\
\
}
*pushButton15.leftAttachment: "attach_position"
*pushButton15.bottomPosition: 98
*pushButton15.leftPosition: 80
*pushButton15.rightPosition: 97
*pushButton15.topAttachment: "attach_position"
*pushButton15.topPosition: 92

*menu1.class: rowColumn
*menu1.static: true
*menu1.name: menu1
*menu1.parent: mainWindow1
*menu1.rowColumnType: "menu_bar"
*menu1.menuAccelerator: "<KeyUp>F10"

*FilePane.class: rowColumn
*FilePane.static: true
*FilePane.name: FilePane
*FilePane.parent: menu1
*FilePane.rowColumnType: "menu_pulldown"

*LoadItem.class: pushButton
*LoadItem.static: true
*LoadItem.name: LoadItem
*LoadItem.parent: FilePane
*LoadItem.labelString: "Load Resources"
*LoadItem.mnemonic: "L"
*LoadItem.activateCallback: {\
Boolean ModificheGeometric; /*  Variabile identificazione modifiche apportate\
				alle risorse di geometric  */\
Boolean ModificheSpecific;  /*  Variabile identificazione modifiche apportate\
				alle risorse di specific   */\
Boolean ModificheColor;     /*  Variabile identificazione modifiche apportate\
				alle risorse di color      */\
Boolean ModificheVCC1;	    /*  Variabile identificazione modifiche apportate\
				alle risorse della variabile cambio colore 1 */\
Boolean ModificheVCC2;	    /*  Variabile identificazione modifiche apportate\
				alle risorse della variabile cambio colore 2 */\
Boolean ModificheVCC3;	    /*  Variabile identificazione modifiche apportate\
				alle risorse della variabile cambio colore 3 */\
Boolean ModificheVCC4;	    /*  Variabile identificazione modifiche apportate\
				alle risorse della variabile cambio colore 4 */\
\
char Str[100];\
\
/*\
	Controllo se sono state fatte modifiche che non \
	sono state applicate     \
*/\
ModificheGeometric = ControllaModifiche (Geometric_RC);\
ModificheSpecific = ControllaModifiche (Specific_RC);\
ModificheColor = ControllaModifiche (Color_RC);\
ModificheVCC1 = ControllaModifiche (VarCC1_rc);\
ModificheVCC2 = ControllaModifiche (VarCC2_rc);\
ModificheVCC3 = ControllaModifiche (VarCC3_rc);\
ModificheVCC4 = ControllaModifiche (VarCC4_rc);\
\
if (ModificheGeometric || ModificheSpecific || ModificheColor \
	|| ModificheVCC1 || ModificheVCC2 || ModificheVCC3 || ModificheVCC4)\
	{\
	strcpy (Str,"You have not applied new modific,continue?");\
	VisualizzaMessageBox (LOAD,Resource,Str,OggettoS);\
	}\
else EseguiLoadResources();\
}

*ResetItem.class: pushButton
*ResetItem.static: true
*ResetItem.name: ResetItem
*ResetItem.parent: FilePane
*ResetItem.labelString: "Reset Resources"
*ResetItem.mnemonic: "R"
*ResetItem.activateCallback: {\
int indice;\
\
if (Usato(Geometric_RC)) indice = 0;\
if (Usato(Specific_RC)) indice = 1;\
if (Usato(Color_RC)) indice = 2;\
if (Usato(VarCC1_rc)) indice = 3;\
if (Usato(VarCC2_rc)) indice = 4;\
if (Usato(VarCC3_rc)) indice = 5;\
if (Usato(VarCC4_rc)) indice = 6;\
\
CreaRowColumnRisorse (Widres_rc);\
\
PrepListaRes (Geometric_RC, OggettoS, XlRGrGeom, DataBaseTo,\
				PagGetType(PagConf));\
PrepListaRes (Specific_RC, OggettoS, XlRGrIo, DataBaseTo,\
				PagGetType(PagConf));\
PrepListaRes (Color_RC, OggettoS, XlRGrColor, DataBaseTo,\
				PagGetType(PagConf));\
PrepListaRes (VarCC1_rc, OggettoS, XlRGrVCC1, DataBaseTo,\
				PagGetType(PagConf));\
PrepListaRes (VarCC2_rc, OggettoS, XlRGrVCC2, DataBaseTo,\
				PagGetType(PagConf));\
PrepListaRes (VarCC3_rc, OggettoS, XlRGrVCC3, DataBaseTo,\
				PagGetType(PagConf));\
PrepListaRes (VarCC4_rc, OggettoS, XlRGrVCC4, DataBaseTo,\
				PagGetType(PagConf));\
\
if (indice == 0) XtManageChild (Geometric_RC);\
if (indice == 1) XtManageChild (Specific_RC);\
if (indice == 2) XtManageChild (Color_RC);\
if (indice == 3) XtManageChild (VarCC1_rc);\
if (indice == 4) XtManageChild (VarCC2_rc);\
if (indice == 5) XtManageChild (VarCC3_rc);\
if (indice == 6) XtManageChild (VarCC4_rc);\
XtManageChild (Widres_rc);\
}

*CloseItem.class: pushButton
*CloseItem.static: true
*CloseItem.name: CloseItem
*CloseItem.parent: FilePane
*CloseItem.labelString: "Close"
*CloseItem.mnemonic: "C"
*CloseItem.activateCallback: {\
Boolean ModificheGeometric; /*  Variabile identificazione modifiche apportate\
				alle risorse di geometric  */\
Boolean ModificheSpecific;  /*  Variabile identificazione modifiche apportate\
				alle risorse di specific   */\
Boolean ModificheColor;     /*  Variabile identificazione modifiche apportate\
				alle risorse di color      */\
Boolean ModificheVCC1;	    /*  Variabile identificazione modifiche apportate\
				alle risorse della variabile cambio colore 1 */\
Boolean ModificheVCC2;	    /*  Variabile identificazione modifiche apportate\
				alle risorse della variabile cambio colore 2 */\
Boolean ModificheVCC3;	    /*  Variabile identificazione modifiche apportate\
				alle risorse della variabile cambio colore 3 */\
Boolean ModificheVCC4;	    /*  Variabile identificazione modifiche apportate\
				alle risorse della variabile cambio colore 4 */\
\
char Str[100];\
Arg arg[3];\
\
/*\
	Controllo se sono state fatte modifiche che non \
	sono state applicate     \
*/\
ModificheGeometric = ControllaModifiche (Geometric_RC);\
ModificheSpecific = ControllaModifiche (Specific_RC);\
ModificheColor = ControllaModifiche (Color_RC);\
ModificheVCC1 = ControllaModifiche (VarCC1_rc);\
ModificheVCC2 = ControllaModifiche (VarCC2_rc);\
ModificheVCC3 = ControllaModifiche (VarCC3_rc);\
ModificheVCC4 = ControllaModifiche (VarCC4_rc);\
\
if (ModificheGeometric || ModificheSpecific || ModificheColor \
	|| ModificheVCC1 || ModificheVCC2 || ModificheVCC3 || ModificheVCC4)\
	{\
	strcpy (Str,"You have not applied new modific,continue?");\
 	VisualizzaMessageBox (CLOSE,Resource,Str,OggettoS);\
	}\
else\
	{\
	if (OggettoS)\
		{\
		XtSetArg (arg[0], XlNinEdit, False);\
		XtSetArg (arg[1], XlNwEdit, NULL);\
		XtSetValues (OggettoS, arg, 2);\
		}\
	XtDestroyWidget (Resource);\
	}\
}

*menu1_top_b1.class: cascadeButton
*menu1_top_b1.static: true
*menu1_top_b1.name: menu1_top_b1
*menu1_top_b1.parent: menu1
*menu1_top_b1.labelString: "File"
*menu1_top_b1.mnemonic: "F"
*menu1_top_b1.subMenuId: "FilePane"

