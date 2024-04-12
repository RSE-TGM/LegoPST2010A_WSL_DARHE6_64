
/*******************************************************************************
	dati_mainWin.c
	(Generated from interface file dati_mainWin.i)
	Associated Resource file: dati_mainWin.rf
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/CascadeB.h>
#include <Xm/SeparatoG.h>
#include <Xm/PushBG.h>
#include <Xm/RowColumn.h>
#include <Xm/ArrowB.h>
#include <Xm/List.h>
#include <Xm/ScrolledW.h>
#include <Xm/Label.h>
#include <Xm/LabelG.h>
#include <Xm/Frame.h>
#include <Xm/TextF.h>
#include <Xm/Form.h>
#include <Xm/MainW.h>
#include <X11/Shell.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo dati_mainWin.i
   tipo 
   release 2.15
   data 4/26/95
   reserved @(#)dati_mainWin.i	2.15
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif

#include "dati.h"
/* #include "UxFsBox.h" */
#include <Xm/Protocols.h>
#include "f03.h"
extern int num_note;
Boolean glob_modified=False;
int n_editors=0; /* numero di editors aperti */
/* Include for UxPut calls on the fileSelectionBox */

void CreateWindowManagerProtocols();
void ExitCB(); 
void CreateSessionManagerProtocols();
void SaveSessionCB();

extern Boolean saving;  /* declared in file selection box declarations */
extern Boolean graphics_on;
extern int stato;
extern Widget topwidget;
extern swidget dati_selectionD;
extern swidget fileSelectionBox;
extern swidget create_dati_selectionD();
extern swidget openButton;
extern swidget saveButton;
extern swidget exitButton;
extern swidget variables;
extern swidget data;
extern swidget listaBlocchi;

extern swidget popup_vardata();


#define SEARCH_DOWN  0
#define SEARCH_UP    1
#define NO_SEARCH    2

/*******************************************************************************
	The definition of the context structure:
	If you create multiple instances of your interface, the context
	structure ensures that your callbacks use the variables for the
	correct instance.

	For each swidget in the interface, each argument to the Interface
	function, and each variable in the Instance Specific section of the
	Declarations Editor, there is an entry in the context structure.
	and a #define.  The #define makes the variable name refer to the
	corresponding entry in the context structure.
*******************************************************************************/

typedef	struct
{
	Widget	UxmainWindow;
	Widget	UxworkAreaForm;
	Widget	UxworkAreaFrame;
	Widget	UxworkArea;
	Widget	Uxform1;
	Widget	Uxn_eqz_label;
	Widget	Uxn_ing_label;
	Widget	Uxn_note_label;
	Widget	Uxn_inc_label;
	Widget	UxscrolledWindow3;
	Widget	Uxlabel1;
	Widget	UxFindDownButton;
	Widget	UxFindUpButton;
	Widget	UxpullDownMenu;
	Widget	UxfilePane;
	Widget	UxopenButton;
	Widget	UxfilePane_b7;
	Widget	UxsaveButton;
	Widget	UxsaveAsButton;
	Widget	UxfilePane_b8;
	Widget	UxexitButton;
	Widget	UxfileCascade;
	Widget	UxeditPane;
	Widget	Uxvariables;
	Widget	Uxdata;
	Widget	UxeditPane_b6;
	Widget	Uxnormal;
	Widget	UxeditCascade;
	Widget	UxhelpPane;
	Widget	UxonContextButton;
	Widget	UxhelpPane_b9;
	Widget	UxonVersionButton;
	Widget	UxhelpCascade;
	int	Uxi;
	int	Uxfound_item;
	int	Uxdirection;
} _UxCdati_mainWS;

#define mainWindow              UxDati_mainWSContext->UxmainWindow
#define workAreaForm            UxDati_mainWSContext->UxworkAreaForm
#define workAreaFrame           UxDati_mainWSContext->UxworkAreaFrame
#define workArea                UxDati_mainWSContext->UxworkArea
#define form1                   UxDati_mainWSContext->Uxform1
#define n_eqz_label             UxDati_mainWSContext->Uxn_eqz_label
#define n_ing_label             UxDati_mainWSContext->Uxn_ing_label
#define n_note_label            UxDati_mainWSContext->Uxn_note_label
#define n_inc_label             UxDati_mainWSContext->Uxn_inc_label
#define scrolledWindow3         UxDati_mainWSContext->UxscrolledWindow3
#define label1                  UxDati_mainWSContext->Uxlabel1
#define FindDownButton          UxDati_mainWSContext->UxFindDownButton
#define FindUpButton            UxDati_mainWSContext->UxFindUpButton
#define pullDownMenu            UxDati_mainWSContext->UxpullDownMenu
#define filePane                UxDati_mainWSContext->UxfilePane
#define openButton              UxDati_mainWSContext->UxopenButton
#define filePane_b7             UxDati_mainWSContext->UxfilePane_b7
#define saveButton              UxDati_mainWSContext->UxsaveButton
#define saveAsButton            UxDati_mainWSContext->UxsaveAsButton
#define filePane_b8             UxDati_mainWSContext->UxfilePane_b8
#define exitButton              UxDati_mainWSContext->UxexitButton
#define fileCascade             UxDati_mainWSContext->UxfileCascade
#define editPane                UxDati_mainWSContext->UxeditPane
#define variables               UxDati_mainWSContext->Uxvariables
#define data                    UxDati_mainWSContext->Uxdata
#define editPane_b6             UxDati_mainWSContext->UxeditPane_b6
#define normal                  UxDati_mainWSContext->Uxnormal
#define editCascade             UxDati_mainWSContext->UxeditCascade
#define helpPane                UxDati_mainWSContext->UxhelpPane
#define onContextButton         UxDati_mainWSContext->UxonContextButton
#define helpPane_b9             UxDati_mainWSContext->UxhelpPane_b9
#define onVersionButton         UxDati_mainWSContext->UxonVersionButton
#define helpCascade             UxDati_mainWSContext->UxhelpCascade
#define i                       UxDati_mainWSContext->Uxi
#define found_item              UxDati_mainWSContext->Uxfound_item
#define direction               UxDati_mainWSContext->Uxdirection

static _UxCdati_mainWS	*UxDati_mainWSContext;

Widget	dati_mainWS;
Widget	FindText;
Widget	labelModelDati;
Widget	label_equation;
Widget	label_unknown;
Widget	label_input;
Widget	label_known;
Widget	listaBlocchi;
Widget	foundLabel;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	popup_dati_mainWS();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

/******************************************************************
   This function establishes a protocol callback that detects 
   the window manager Close command.  */

void CreateWindowManagerProtocols(shell)
     Widget shell;
{
  Atom  xa_WM_DELETE_WINDOW;

  xa_WM_DELETE_WINDOW = XInternAtom (UxDisplay, "WM_DELETE_WINDOW", False);
  XmAddWMProtocolCallback (shell, xa_WM_DELETE_WINDOW, ExitCB, NULL);
}



confirm_exit(w,which_button,call_data)
Widget w;
int which_button;
XmAnyCallbackStruct *call_data;
{
/*
 L'utente ha richiesto di uscire dall'applicativo
*/
if (which_button == 0)
	{
	exit(0);
	}
/* Chiudi la window di conferma */
XtDestroyWidget(w);
}



/* This function pops up the Exit dialog box. */
void ExitCB(w, client_data, call_data)
     Widget  w;
     caddr_t client_data;
     caddr_t call_data;
{
extern Widget conferma();
static Elenco_callback data_agg_callback = {
        {"Continue", confirm_exit , 0 },
        {"Cancel", confirm_exit , 1 },
        {NULL,NULL, 0 }};
if(glob_modified) /* ci sono state modifiche ed il
                      file non e' mai stato salvato */
	conferma(dati_mainWS,
                 "You have modified Variables values\n but NOT SAVED F14 file !!.\nAll changes WILL BE LOST!!\nContinue?",
                 data_agg_callback);

else if (n_editors > 0)
	conferma(dati_mainWS,
		"Variable and Data editors are already opened\n not applied data shold be LOST !!\n Continue? ",
		data_agg_callback);
        	
else
	conferma(dati_mainWS,
		"Do You really want to exit Data Editor?",
		data_agg_callback);

}


/****************************************************************** 
   This function establishes a protocol callback to detect a "save 
   yourself" message from the session manager. */

void CreateSessionManagerProtocols()
{
  Atom  xa_WM_SAVE_YOURSELF;
  
  xa_WM_SAVE_YOURSELF = XInternAtom (UxDisplay, "WM_SAVE_YOURSELF", False);
  XmAddWMProtocolCallback (UxTopLevel, xa_WM_SAVE_YOURSELF, SaveSessionCB, NULL);
}


/*****************************************************************
   This callback function is executed whenever this application 
   receives a "save yourself" callback from the session manager. */

void SaveSessionCB()
{

  printf("The session manager is saving a session ...\n");
  printf(" ... (New Application) should save itself now!\n");

}

/*
 update_pulldown
	abilita e/o disabilita i bottoni costituenti il
	pulldown menu a seconda dello stato del programma
*/
update_pulldown()
{
if(stato == NON_SCELTO)
	{
	UxPutSensitive(openButton,"true");
	UxPutSensitive(saveButton,"false");
	UxPutSensitive(saveAsButton,"false");
	UxPutSensitive(exitButton,"true");

	UxPutSensitive(variables,"false");
	UxPutSensitive(data,"false");
	UxPutSensitive(normal,"false");
	}
else if(stato == SCELTO)
	{
	UxPutSensitive(openButton,"false");
	UxPutSensitive(saveButton,"true");
	UxPutSensitive(saveAsButton,"true");
	UxPutSensitive(exitButton,"true");

	UxPutSensitive(variables,"true");
	UxPutSensitive(data,"true");
	UxPutSensitive(normal,"true");
	}
}

/*
 update_contatori
	aggiorna i valori dei contatori di numero di
	eqz.,numero variabili note, numero var non
        note,numero variabili in ingresso.
*/
update_contatori()
{
char app[10];
sprintf(app,"%d",neqsis);
UxPutLabelString(label_equation,app);
sprintf(app,"%d",nu);
UxPutLabelString(label_input,app);
sprintf(app,"%d",num_note);
UxPutLabelString(label_known,app);
sprintf(app,"%d",(neqsis+nu-num_note));
UxPutLabelString(label_unknown,app);
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	createCB_labelModelDati( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdati_mainWS         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDati_mainWSContext;
	UxDati_mainWSContext = UxContext =
			(_UxCdati_mainWS *) UxGetContext( UxWidget );
	{
	/* Commento */
	extern char *estr_nome_modello();
	extern char *str_toupper();
	extern int stato;
	char path[120];
	char str2[120];
	char *nome_modello;
	if(stato==SCELTO)
		{
		getwd(path);
		nome_modello=estr_nome_modello(path);
		str_toupper(nome_modello);
		sprintf(str2,"Model name: %s",nome_modello);
		UxPutLabelString(UxWidget,str2);
		}
	}
	UxDati_mainWSContext = UxSaveCtx;
}

static void	extendedSelectionCB_listaBlocchi( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdati_mainWS         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDati_mainWSContext;
	UxDati_mainWSContext = UxContext =
			(_UxCdati_mainWS *) UxGetContext( UxWidget );
	{
	int j;
	extern char *extract_string();
	extern Boolean graphics_on;
	char *nome_blocco;
	XmListCallbackStruct *s_lista;
	/*
	 Se non e' selezionata la grafica esce
	*/
	if(graphics_on == False)
		return;
	/*
	 Seleziona sullo schema grafico i blocchi corrispondenti
	 a quelli selezionati in lista
	*/
	
	s_lista=(XmListCallbackStruct *)UxCallbackArg;
	/*
	 Deseleziona tutti i blocchi in tutte le pagine 
	 solo se la pagina grafica e' aperta
	*/
	/* test aggiunto 21-4-95 (Micheletti) */
	if( macro_is_open() )
		{
		deselez_all_graf();
		for(j=0;j<s_lista->selected_item_count;j++)
			{
			nome_blocco=extract_string(s_lista->selected_items[j]);
			nome_blocco[8]='\0';
			selgraf_blocco(nome_blocco,True);
			XtFree(nome_blocco);
			}
		}
	
	}
	UxDati_mainWSContext = UxSaveCtx;
}

static void	multipleSelectionCB_listaBlocchi( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdati_mainWS         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDati_mainWSContext;
	UxDati_mainWSContext = UxContext =
			(_UxCdati_mainWS *) UxGetContext( UxWidget );
	{
	
	}
	UxDati_mainWSContext = UxSaveCtx;
}

static void	singleSelectionCB_listaBlocchi( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdati_mainWS         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDati_mainWSContext;
	UxDati_mainWSContext = UxContext =
			(_UxCdati_mainWS *) UxGetContext( UxWidget );
	{
	
	}
	UxDati_mainWSContext = UxSaveCtx;
}

static void	activateCB_FindDownButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdati_mainWS         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDati_mainWSContext;
	UxDati_mainWSContext = UxContext =
			(_UxCdati_mainWS *) UxGetContext( UxWidget );
	{
	/* search down */
	
	extern char **nom_bloc;
	char **lista;
	int num_item,inizio;
	char textsearch[85];
	
	/* stringa da ricercare */
	strcpy(textsearch,UxGetText(FindText));
	tominus( trim_blank(textsearch) );
	
	if( strlen(textsearch)  )   
	{
	   printf("search for text %s\n",textsearch);
	   
	/* costruisco la lista di riferimento */
	
	   get_something(UxGetWidget(listaBlocchi),XmNitemCount,&num_item);
	   lista    = (char **) calloc( num_item, sizeof(char *));
	   for(i=0;i<num_item;i++)
	   {
	      lista[i] = (char *) calloc( nbl, (sizeof(char) * 80) );
	      memcpy(lista[i],nom_bloc[i],80);
	      tominus( trim_blank(lista[i]) );
	   }
	
	/* effettuo la ricerca */
	
	   if(direction == SEARCH_UP)
	       inizio = found_item+1;
	   else
	       inizio = found_item;
	
	   direction = SEARCH_DOWN;
	   
	   for( i=inizio; i<num_item; i++)
	   {
	      if( strstr(lista[i],textsearch) != NULL)
	      {
	         printf("found text in item %d\n",i+1);
	/* seleziono il blocco e incremento il contatore */
	         found_item = i+1;
	         XmListSelectPos(UxGetWidget(listaBlocchi),found_item,True);
	         XmListSetPos(UxGetWidget(listaBlocchi),found_item);
	         UxPutLabelString(foundLabel,"         ");
	         break;
	      }
	      else
	      {
	         printf("text not found\n");
	         UxPutLabelString(foundLabel,"Not Found");
	      }
	   }
	}                    
	   
	
	}
	UxDati_mainWSContext = UxSaveCtx;
}

static void	activateCB_FindUpButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdati_mainWS         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDati_mainWSContext;
	UxDati_mainWSContext = UxContext =
			(_UxCdati_mainWS *) UxGetContext( UxWidget );
	{
	/*search up */
	
	extern char **nom_bloc;
	char **lista;
	int num_item,inizio;
	char textsearch[85];
	
	/* stringa da ricercare */
	strcpy(textsearch,UxGetText(FindText));
	tominus( trim_blank(textsearch) );
	
	if( strlen(textsearch)  )   
	{
	   printf("search for text %s\n",textsearch);
	
	/* acquisisco il numero di item in lista */
	 
	   get_something(UxGetWidget(listaBlocchi),XmNitemCount,&num_item);   
	   lista = (char **) calloc( num_item, sizeof(char *));
	   for(i=0;i<num_item;i++)
	   {
	      lista[i] = (char *) calloc( nbl, (sizeof(char) * 80) );
	      memcpy(lista[i],nom_bloc[i],80);
	      tominus( trim_blank(lista[i]) );
	   }
	
	/* effettuo la ricerca */
	
	  
	   if(direction == SEARCH_DOWN)
	      inizio = found_item -1;
	   else
	      inizio = found_item;
	
	   direction = SEARCH_UP;
	   
	   for( i=inizio; i > 0; i--)
	   {
	      int ind;
	      ind = i-1;
	
	      if( strstr(lista[ind],textsearch) != NULL)
	      {
	         printf("found text in item %d\n",i);
	         found_item=ind;
	         XmListSelectPos(UxGetWidget(listaBlocchi),i,True);
	         XmListSetPos(UxGetWidget(listaBlocchi),i);
	         UxPutLabelString(foundLabel,"         ");
	         break;     
	      }
	      else
	      {
	         printf("text not found\n");
	         UxPutLabelString(foundLabel,"Not Found");
	      } 
	   }
	}                    
	 
	 
	}
	UxDati_mainWSContext = UxSaveCtx;
}

static void	activateCB_openButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdati_mainWS         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDati_mainWSContext;
	UxDati_mainWSContext = UxContext =
			(_UxCdati_mainWS *) UxGetContext( UxWidget );
	{
	   /* Clear "saving" flag, then display file selection box. */
	   saving = False; 
	   UxPutTitle(dati_selectionD, "Data editor - Open");
	   UxPutSelectionLabelString(fileSelectionBox, "Model to Open");
	   UxPopupInterface(dati_selectionD, no_grab); 
	}
	UxDati_mainWSContext = UxSaveCtx;
}

static void	activateCB_saveButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdati_mainWS         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDati_mainWSContext;
	UxDati_mainWSContext = UxContext =
			(_UxCdati_mainWS *) UxGetContext( UxWidget );
	{
	extern swidget create_vis_msg();
	char str[50];
	FILE *fp_f14;
	fp_f14=fopen("f14.dat","w");
	if(fp_f14)
		{
		write_file_f14(fp_f14);
		fclose(fp_f14);
		sprintf(str,"file F14 successfully saved");
		glob_modified=False;
		}
	else
		{
		sprintf(str,"Cannot write file F14");
		}
	create_vis_msg(str);
	}
	UxDati_mainWSContext = UxSaveCtx;
}

static void	activateCB_saveAsButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdati_mainWS         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDati_mainWSContext;
	UxDati_mainWSContext = UxContext =
			(_UxCdati_mainWS *) UxGetContext( UxWidget );
	{
	/* Set "saving" flag, then display file selection box. */
	saving = True;
	UxPutTitle(dati_selectionD, "Data editor - Save As");
	UxPutSelectionLabelString(fileSelectionBox, "File to Save");
	UxPutFileTypeMask(fileSelectionBox,"file_regular");
	UxPutFileListLabelString(fileSelectionBox,"Files");
	UxPutPattern(fileSelectionBox,"*.dat");
	   
	UxPopupInterface(dati_selectionD, no_grab); 
	}
	UxDati_mainWSContext = UxSaveCtx;
}

static void	activateCB_exitButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdati_mainWS         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDati_mainWSContext;
	UxDati_mainWSContext = UxContext =
			(_UxCdati_mainWS *) UxGetContext( UxWidget );
	{
	extern Widget conferma();
	static Elenco_callback data_agg_callback = {
	        {"Continue", confirm_exit , 0 },
	        {"Cancel", confirm_exit , 1 },
	        {NULL,NULL, 0 }};
	if(glob_modified) /* ci sono state modifiche ed il
	                      file non e' mai stato salvato */
		conferma(dati_mainWS,
	                 "You have modified Variables values\n but NOT SAVED F14 file !!.\nAll changes WILL BE LOST!!\nContinue?",
	                 data_agg_callback);
	
	else if (n_editors > 0)
		conferma(dati_mainWS,
			"Variable and Data editors are already opened\n not applied data shold be LOST !!\n Continue? ",
			data_agg_callback);
	        	
	else
		conferma(dati_mainWS,
			"Do You really want to exit Data Editor?",
			data_agg_callback);
	}
	UxDati_mainWSContext = UxSaveCtx;
}

static void	activateCB_variables( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdati_mainWS         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDati_mainWSContext;
	UxDati_mainWSContext = UxContext =
			(_UxCdati_mainWS *) UxGetContext( UxWidget );
	{
	/* prepara la form dialog di editing per le variabili */
//	extern swidget popup_vardata();
	n_editors++;
	popup_vardata(ALL_VAR);
	  printf("Edit variabili\n");
	}
	UxDati_mainWSContext = UxSaveCtx;
}

static void	activateCB_data( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdati_mainWS         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDati_mainWSContext;
	UxDati_mainWSContext = UxContext =
			(_UxCdati_mainWS *) UxGetContext( UxWidget );
	{
	printf("visualizzazione dati \n");
	/* prepara la form per la visualizzazione dei dati geometrici e
	   fisici dei blocchi */
	n_editors++;
	popup_vardata(ALL_DATA);
	}
	UxDati_mainWSContext = UxSaveCtx;
}

static void	activateCB_normal( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdati_mainWS         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDati_mainWSContext;
	UxDati_mainWSContext = UxContext =
			(_UxCdati_mainWS *) UxGetContext( UxWidget );
	{
	extern swidget popup_NormParamDialog();  
	popup_NormParamDialog(); 
	}
	UxDati_mainWSContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_dati_mainWS()
{
	Widget	filePane_shell;
	Widget	editPane_shell;
	Widget	helpPane_shell;

	dati_mainWS = XtVaCreatePopupShell( "dati_mainWS",
			applicationShellWidgetClass, UxTopLevel,
			XmNminWidth, 490,
			XmNminHeight, 340,
			XmNiconName, "Data Editing",
			XmNdeleteResponse, XmDO_NOTHING,
			XmNtitle, "Data Editing",
			XmNheight, 470,
			XmNwidth, 490,
			XmNy, 205,
			XmNx, 768,
			NULL );

	UxPutContext( dati_mainWS, (char *) UxDati_mainWSContext );

	mainWindow = XtVaCreateManagedWidget( "mainWindow",
			xmMainWindowWidgetClass, dati_mainWS,
			XmNheight, 470,
			XmNwidth, 490,
			XmNy, 180,
			XmNx, 200,
			NULL );

	UxPutContext( mainWindow, (char *) UxDati_mainWSContext );

	workAreaForm = XtVaCreateManagedWidget( "workAreaForm",
			xmFormWidgetClass, mainWindow,
			XmNborderWidth, 0,
			XmNheight, 340,
			XmNwidth, 490,
			NULL );

	UxPutContext( workAreaForm, (char *) UxDati_mainWSContext );

	FindText = XtVaCreateManagedWidget( "FindText",
			xmTextFieldWidgetClass, workAreaForm,
			XmNcolumns, 15,
			XmNleftOffset, 45,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNheight, 41,
			XmNwidth, 200,
			XmNy, 570,
			XmNx, 10,
			NULL );

	UxPutContext( FindText, (char *) UxDati_mainWSContext );

	workAreaFrame = XtVaCreateManagedWidget( "workAreaFrame",
			xmFrameWidgetClass, workAreaForm,
			XmNbottomWidget, FindText,
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNheight, 230,
			XmNwidth, 390,
			XmNy, 30,
			XmNx, 50,
			NULL );

	UxPutContext( workAreaFrame, (char *) UxDati_mainWSContext );

	workArea = XtVaCreateManagedWidget( "workArea",
			xmFormWidgetClass, workAreaFrame,
			XmNborderWidth, 0,
			XmNheight, 518,
			XmNwidth, 542,
			XmNy, 2,
			XmNx, 10,
			NULL );

	UxPutContext( workArea, (char *) UxDati_mainWSContext );

	labelModelDati = XtVaCreateManagedWidget( "labelModelDati",
			xmLabelGadgetClass, workArea,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNshadowThickness, 0,
			XmNborderWidth, 4,
			RES_CONVERT( XmNlabelString, "Model not selected" ),
			XmNfontList, UxConvertFontList( "-adobe-helvetica-medium-r-normal--18-180-75-75-p-98-iso8859-1" ),
			XmNheight, 30,
			XmNwidth, 260,
			XmNy, 10,
			XmNx, 120,
			NULL );

	UxPutContext( labelModelDati, (char *) UxDati_mainWSContext );

	createCB_labelModelDati( labelModelDati,
			(XtPointer) UxDati_mainWSContext, (XtPointer) NULL );

	form1 = XtVaCreateManagedWidget( "form1",
			xmFormWidgetClass, workArea,
			XmNleftOffset, 20,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightOffset, 20,
			XmNrightAttachment, XmATTACH_FORM,
			XmNallowOverlap, FALSE,
			XmNheight, 70,
			XmNwidth, 630,
			XmNy, 50,
			XmNx, 20,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form1, (char *) UxDati_mainWSContext );

	n_eqz_label = XtVaCreateManagedWidget( "n_eqz_label",
			xmLabelWidgetClass, form1,
			RES_CONVERT( XmNlabelString, "equations" ),
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightPosition, 25,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNheight, 36,
			XmNwidth, 116,
			XmNy, 0,
			XmNx, 0,
			NULL );

	UxPutContext( n_eqz_label, (char *) UxDati_mainWSContext );

	n_ing_label = XtVaCreateManagedWidget( "n_ing_label",
			xmLabelWidgetClass, form1,
			RES_CONVERT( XmNlabelString, "input var." ),
			XmNrightPosition, 75,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftPosition, 50,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNheight, 35,
			XmNwidth, 175,
			XmNy, 0,
			XmNx, 270,
			NULL );

	UxPutContext( n_ing_label, (char *) UxDati_mainWSContext );

	n_note_label = XtVaCreateManagedWidget( "n_note_label",
			xmLabelWidgetClass, form1,
			RES_CONVERT( XmNlabelString, "known var." ),
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftPosition, 75,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNheight, 36,
			XmNwidth, 120,
			XmNy, 0,
			XmNx, 480,
			NULL );

	UxPutContext( n_note_label, (char *) UxDati_mainWSContext );

	n_inc_label = XtVaCreateManagedWidget( "n_inc_label",
			xmLabelWidgetClass, form1,
			RES_CONVERT( XmNlabelString, "unknown var." ),
			XmNrightPosition, 50,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftPosition, 25,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNheight, 36,
			XmNwidth, 140,
			XmNy, 0,
			XmNx, 180,
			NULL );

	UxPutContext( n_inc_label, (char *) UxDati_mainWSContext );

	label_equation = XtVaCreateManagedWidget( "label_equation",
			xmLabelWidgetClass, form1,
			XmNbottomAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "0" ),
			XmNleftAttachment, XmATTACH_POSITION,
			XmNrightPosition, 23,
			XmNtopWidget, n_eqz_label,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNrightOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftOffset, 2,
			XmNborderWidth, 2,
			XmNheight, 30,
			XmNwidth, 80,
			XmNy, 30,
			XmNx, 10,
			NULL );

	UxPutContext( label_equation, (char *) UxDati_mainWSContext );

	label_unknown = XtVaCreateManagedWidget( "label_unknown",
			xmLabelWidgetClass, form1,
			RES_CONVERT( XmNlabelString, "0" ),
			XmNrightPosition, 48,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftPosition, 27,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNtopWidget, n_eqz_label,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNborderWidth, 2,
			XmNheight, 30,
			XmNwidth, 80,
			XmNy, 30,
			XmNx, 110,
			NULL );

	UxPutContext( label_unknown, (char *) UxDati_mainWSContext );

	label_input = XtVaCreateManagedWidget( "label_input",
			xmLabelWidgetClass, form1,
			RES_CONVERT( XmNlabelString, "0" ),
			XmNrightPosition, 73,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftPosition, 52,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNtopWidget, n_eqz_label,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNborderWidth, 2,
			XmNheight, 30,
			XmNwidth, 80,
			XmNy, 30,
			XmNx, 210,
			NULL );

	UxPutContext( label_input, (char *) UxDati_mainWSContext );

	label_known = XtVaCreateManagedWidget( "label_known",
			xmLabelWidgetClass, form1,
			RES_CONVERT( XmNlabelString, "0" ),
			XmNrightPosition, 98,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNleftPosition, 77,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNtopWidget, n_eqz_label,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNborderWidth, 2,
			XmNheight, 30,
			XmNwidth, 80,
			XmNy, 30,
			XmNx, 300,
			NULL );

	UxPutContext( label_known, (char *) UxDati_mainWSContext );

	scrolledWindow3 = XtVaCreateManagedWidget( "scrolledWindow3",
			xmScrolledWindowWidgetClass, workArea,
			XmNtopOffset, 40,
			XmNtopWidget, form1,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 40,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomOffset, 20,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNrightOffset, 40,
			XmNrightAttachment, XmATTACH_FORM,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 160,
			XmNx, 40,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( scrolledWindow3, (char *) UxDati_mainWSContext );

	listaBlocchi = XtVaCreateManagedWidget( "listaBlocchi",
			xmListWidgetClass, scrolledWindow3,
			XmNlistSizePolicy, XmCONSTANT,
			XmNvisibleItemCount, 30,
			XmNscrollBarDisplayPolicy, XmAS_NEEDED,
			XmNselectionPolicy, XmEXTENDED_SELECT,
			XmNheight, 100,
			XmNwidth, 386,
			NULL );

	UxPutContext( listaBlocchi, (char *) UxDati_mainWSContext );

	label1 = XtVaCreateManagedWidget( "label1",
			xmLabelWidgetClass, workArea,
			XmNleftOffset, 40,
			XmNleftAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_NONE,
			XmNrightOffset, 40,
			XmNrightAttachment, XmATTACH_FORM,
			RES_CONVERT( XmNlabelString, "Blocks in model" ),
			XmNbottomWidget, scrolledWindow3,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNheight, 20,
			XmNwidth, 380,
			XmNy, 80,
			XmNx, 40,
			NULL );

	UxPutContext( label1, (char *) UxDati_mainWSContext );

	FindDownButton = XtVaCreateManagedWidget( "FindDownButton",
			xmArrowButtonWidgetClass, workAreaForm,
			XmNarrowDirection, XmARROW_DOWN,
			XmNleftWidget, FindText,
			XmNleftOffset, 5,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNtopWidget, workAreaFrame,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNheight, 30,
			XmNwidth, 30,
			XmNy, 570,
			XmNx, 220,
			NULL );

	UxPutContext( FindDownButton, (char *) UxDati_mainWSContext );

	FindUpButton = XtVaCreateManagedWidget( "FindUpButton",
			xmArrowButtonWidgetClass, workAreaForm,
			XmNleftWidget, FindDownButton,
			XmNleftOffset, 1,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNtopWidget, workAreaFrame,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNarrowDirection, XmARROW_UP,
			XmNheight, 30,
			XmNwidth, 30,
			XmNy, 570,
			XmNx, 250,
			NULL );

	UxPutContext( FindUpButton, (char *) UxDati_mainWSContext );

	foundLabel = XtVaCreateManagedWidget( "foundLabel",
			xmLabelWidgetClass, workAreaForm,
			RES_CONVERT( XmNlabelString, "" ),
			XmNtopWidget, workAreaFrame,
			XmNtopOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNleftWidget, FindUpButton,
			XmNleftOffset, 10,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 10,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNheight, 30,
			XmNwidth, 100,
			XmNy, 260,
			XmNx, 290,
			NULL );

	UxPutContext( foundLabel, (char *) UxDati_mainWSContext );

	pullDownMenu = XtVaCreateManagedWidget( "pullDownMenu",
			xmRowColumnWidgetClass, mainWindow,
			XmNmenuAccelerator, "<KeyUp>F10",
			XmNrowColumnType, XmMENU_BAR,
			XmNborderWidth, 0,
			NULL );

	UxPutContext( pullDownMenu, (char *) UxDati_mainWSContext );

	filePane_shell = XtVaCreatePopupShell ("filePane_shell",
			xmMenuShellWidgetClass, pullDownMenu,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	filePane = XtVaCreateWidget( "filePane",
			xmRowColumnWidgetClass, filePane_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( filePane, (char *) UxDati_mainWSContext );

	openButton = XtVaCreateManagedWidget( "openButton",
			xmPushButtonGadgetClass, filePane,
			RES_CONVERT( XmNmnemonic, "O" ),
			RES_CONVERT( XmNlabelString, "Open ..." ),
			NULL );

	UxPutContext( openButton, (char *) UxDati_mainWSContext );

	filePane_b7 = XtVaCreateManagedWidget( "filePane_b7",
			xmSeparatorGadgetClass, filePane,
			NULL );

	UxPutContext( filePane_b7, (char *) UxDati_mainWSContext );

	saveButton = XtVaCreateManagedWidget( "saveButton",
			xmPushButtonGadgetClass, filePane,
			RES_CONVERT( XmNmnemonic, "S" ),
			RES_CONVERT( XmNlabelString, "Save" ),
			NULL );

	UxPutContext( saveButton, (char *) UxDati_mainWSContext );

	saveAsButton = XtVaCreateManagedWidget( "saveAsButton",
			xmPushButtonGadgetClass, filePane,
			RES_CONVERT( XmNmnemonic, "A" ),
			RES_CONVERT( XmNlabelString, "Save As ..." ),
			NULL );

	UxPutContext( saveAsButton, (char *) UxDati_mainWSContext );

	filePane_b8 = XtVaCreateManagedWidget( "filePane_b8",
			xmSeparatorGadgetClass, filePane,
			NULL );

	UxPutContext( filePane_b8, (char *) UxDati_mainWSContext );

	exitButton = XtVaCreateManagedWidget( "exitButton",
			xmPushButtonGadgetClass, filePane,
			RES_CONVERT( XmNmnemonic, "E" ),
			RES_CONVERT( XmNlabelString, "Exit" ),
			NULL );

	UxPutContext( exitButton, (char *) UxDati_mainWSContext );

	fileCascade = XtVaCreateManagedWidget( "fileCascade",
			xmCascadeButtonWidgetClass, pullDownMenu,
			XmNsubMenuId, filePane,
			RES_CONVERT( XmNmnemonic, "F" ),
			RES_CONVERT( XmNlabelString, "File" ),
			NULL );

	UxPutContext( fileCascade, (char *) UxDati_mainWSContext );

	editPane_shell = XtVaCreatePopupShell ("editPane_shell",
			xmMenuShellWidgetClass, pullDownMenu,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	editPane = XtVaCreateWidget( "editPane",
			xmRowColumnWidgetClass, editPane_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( editPane, (char *) UxDati_mainWSContext );

	variables = XtVaCreateManagedWidget( "variables",
			xmPushButtonGadgetClass, editPane,
			RES_CONVERT( XmNmnemonic, "V" ),
			RES_CONVERT( XmNlabelString, "Variables..." ),
			NULL );

	UxPutContext( variables, (char *) UxDati_mainWSContext );

	data = XtVaCreateManagedWidget( "data",
			xmPushButtonGadgetClass, editPane,
			RES_CONVERT( XmNmnemonic, "D" ),
			RES_CONVERT( XmNlabelString, "Data..." ),
			NULL );

	UxPutContext( data, (char *) UxDati_mainWSContext );

	editPane_b6 = XtVaCreateManagedWidget( "editPane_b6",
			xmSeparatorGadgetClass, editPane,
			NULL );

	UxPutContext( editPane_b6, (char *) UxDati_mainWSContext );

	normal = XtVaCreateManagedWidget( "normal",
			xmPushButtonGadgetClass, editPane,
			RES_CONVERT( XmNmnemonic, "N" ),
			RES_CONVERT( XmNlabelString, "Normalization..." ),
			NULL );

	UxPutContext( normal, (char *) UxDati_mainWSContext );

	editCascade = XtVaCreateManagedWidget( "editCascade",
			xmCascadeButtonWidgetClass, pullDownMenu,
			XmNsubMenuId, editPane,
			RES_CONVERT( XmNmnemonic, "E" ),
			RES_CONVERT( XmNlabelString, "Edit" ),
			NULL );

	UxPutContext( editCascade, (char *) UxDati_mainWSContext );

	helpPane_shell = XtVaCreatePopupShell ("helpPane_shell",
			xmMenuShellWidgetClass, pullDownMenu,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	helpPane = XtVaCreateWidget( "helpPane",
			xmRowColumnWidgetClass, helpPane_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( helpPane, (char *) UxDati_mainWSContext );

	onContextButton = XtVaCreateManagedWidget( "onContextButton",
			xmPushButtonGadgetClass, helpPane,
			RES_CONVERT( XmNmnemonic, "C" ),
			RES_CONVERT( XmNlabelString, "On Dati application ..." ),
			NULL );

	UxPutContext( onContextButton, (char *) UxDati_mainWSContext );

	helpPane_b9 = XtVaCreateManagedWidget( "helpPane_b9",
			xmSeparatorGadgetClass, helpPane,
			NULL );

	UxPutContext( helpPane_b9, (char *) UxDati_mainWSContext );

	onVersionButton = XtVaCreateManagedWidget( "onVersionButton",
			xmPushButtonGadgetClass, helpPane,
			RES_CONVERT( XmNmnemonic, "V" ),
			RES_CONVERT( XmNlabelString, "On Version ..." ),
			NULL );

	UxPutContext( onVersionButton, (char *) UxDati_mainWSContext );

	helpCascade = XtVaCreateManagedWidget( "helpCascade",
			xmCascadeButtonWidgetClass, pullDownMenu,
			XmNsubMenuId, helpPane,
			RES_CONVERT( XmNmnemonic, "H" ),
			RES_CONVERT( XmNlabelString, "Help" ),
			NULL );

	UxPutContext( helpCascade, (char *) UxDati_mainWSContext );

	XtAddCallback( dati_mainWS, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxDati_mainWSContext );

	XtAddCallback( listaBlocchi, XmNextendedSelectionCallback,
			extendedSelectionCB_listaBlocchi,
			(XtPointer) UxDati_mainWSContext );
	XtAddCallback( listaBlocchi, XmNmultipleSelectionCallback,
			multipleSelectionCB_listaBlocchi,
			(XtPointer) UxDati_mainWSContext );
	XtAddCallback( listaBlocchi, XmNsingleSelectionCallback,
			singleSelectionCB_listaBlocchi,
			(XtPointer) UxDati_mainWSContext );

	XtAddCallback( FindDownButton, XmNactivateCallback,
			activateCB_FindDownButton,
			(XtPointer) UxDati_mainWSContext );

	XtAddCallback( FindUpButton, XmNactivateCallback,
			activateCB_FindUpButton,
			(XtPointer) UxDati_mainWSContext );

	XtVaSetValues(pullDownMenu,
			XmNmenuHelpWidget, helpCascade,
			NULL );

	XtAddCallback( openButton, XmNactivateCallback,
			activateCB_openButton,
			(XtPointer) UxDati_mainWSContext );

	XtAddCallback( saveButton, XmNactivateCallback,
			activateCB_saveButton,
			(XtPointer) UxDati_mainWSContext );

	XtAddCallback( saveAsButton, XmNactivateCallback,
			activateCB_saveAsButton,
			(XtPointer) UxDati_mainWSContext );

	XtAddCallback( exitButton, XmNactivateCallback,
			activateCB_exitButton,
			(XtPointer) UxDati_mainWSContext );

	XtAddCallback( variables, XmNactivateCallback,
			activateCB_variables,
			(XtPointer) UxDati_mainWSContext );

	XtAddCallback( data, XmNactivateCallback,
			activateCB_data,
			(XtPointer) UxDati_mainWSContext );

	XtAddCallback( normal, XmNactivateCallback,
			activateCB_normal,
			(XtPointer) UxDati_mainWSContext );


	XmMainWindowSetAreas( mainWindow, pullDownMenu, (Widget) NULL,
			(Widget) NULL, (Widget) NULL, workAreaForm );

	return ( dati_mainWS );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_popup_dati_mainWS()
{
	Widget                  rtrn;
	_UxCdati_mainWS         *UxContext;

	UxDati_mainWSContext = UxContext =
		(_UxCdati_mainWS *) XtMalloc( sizeof(_UxCdati_mainWS) );

	rtrn = _Uxbuild_dati_mainWS();

	create_dati_selectionD(rtrn);
	if(stato==SCELTO)
		{	
		update_contatori();
	/*
	 Costruisce la lista dei blocchi appartenenti al modello
	*/
		for(i=0;i<nbl;i++)
			{
			ricostruisci_nome_blocco(nom_bloc[i]);
			aggiungi_item_n(listaBlocchi,nom_bloc[i],80);
			}
	        if(graphics_on)
		   lancia_macro(topwidget,UxGetWidget(listaBlocchi));
		}
	
	
	
	CreateWindowManagerProtocols(UxGetWidget(rtrn));
	CreateSessionManagerProtocols();
	
	update_pulldown();
	
	found_item =0;
	direction = NO_SEARCH;
	
	UxPopupInterface(rtrn, no_grab);
	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	popup_dati_mainWS()
{
	Widget			_Uxrtrn;
	static int		_Uxinit = 0;

	if ( ! _Uxinit )
	{
		UxLoadResources( "dati_mainWin.rf" );
		_Uxinit = 1;
	}

	_Uxrtrn = _Ux_popup_dati_mainWS();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

