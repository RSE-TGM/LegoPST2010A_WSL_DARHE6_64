
/*******************************************************************************
	abox_file_selection.c
	(Generated from interface file abox_file_selection.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/FileSB.h>
#include <X11/Shell.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo abox_file_selection.i
   tipo 
   release 2.22
   data 5/9/95
   reserved @(#)abox_file_selection.i	2.22
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#endif

/****************************************************************/
/* INCLUDE FILES						*/
/****************************************************************/

#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>

#ifndef LIBICOFILE
#include <file_icone.h>
#define LIBICOFILE
#endif

#ifndef LIBUTILX
#include <libutilx.h>
#define LIBUTILX
#endif

#include "definizioni.h"

/****************************************************************/
/* VARIABILI GLOBALI ESTERNE					*/
/****************************************************************/

extern Arg args[];
extern Cardinal argcount;

/* Array di compound strings */
extern XmString cstrings[], cstring, cstring_null;

extern char message[];

/* VARIABILE GLOBALE DEL NOME DEL MODULO SELEZIONATO */
extern char nome_modulo[];
extern char descr_modulo[];

extern byte tipo_modulo;

extern Widget attention_wdg;
extern Dialog_geometry geom_attention;

extern Display *display;

/****************************************************************/
/* VARIABILI GLOBALI						*/
/****************************************************************/

char *path_altro_utente;

/* flag che indica se la file selection box e' managed */
Boolean dbox_fileselect_managed = False;

/* flag che indica se la lista dei moduli e' managed */
Boolean dbox_list_utente_managed = False;

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
	int	mumble;
} _UxCabox_file_selection;


static _UxCabox_file_selection	*UxAbox_file_selectionContext;

Widget	abox_file_selection;
Widget	fileSelectionBox1;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_file_selection();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_fileSelectionBox1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCabox_file_selection *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAbox_file_selectionContext;
	UxAbox_file_selectionContext = UxContext =
			(_UxCabox_file_selection *) UxGetContext( UxWidget );
	{
	   XmFileSelectionBoxCallbackStruct *fboxstruct;
	   char path_lista_moduli[256];
	   FILE *fp;
	   byte tipo_lib;
	
	   tipo_lib = (byte) UxClientData;
	
	   fboxstruct = (XmFileSelectionBoxCallbackStruct *) UxCallbackArg;
	
	   path_altro_utente = extract_string(fboxstruct->dir);
	   printf("directory selezionata: %s\n", path_altro_utente);
	
#ifdef VMS
	   sottodir_vms(path_lista_moduli, path_altro_utente, 
	                sottodir_utente(tipo_lib, LIB_UTENTE));
#else
	   sprintf(path_lista_moduli,"%s%s/",path_altro_utente, 
	                                   sottodir_utente(tipo_lib, LIB_UTENTE));
#endif
	
	   switch (tipo_lib)
	   {
	      case LIBUT:
	           strcat(path_lista_moduli, FILE_DATI_LIBUT);
	           break;
	
	      case LIBUTREG:
	           strcat(path_lista_moduli, FILE_DATI_LIBUTREG);
	           break;
	
	      case LIBREG:
	           strcat(path_lista_moduli, FILE_DATI_LIBREG);
	           break;
	   }
	
	   if (access(path_lista_moduli, F_OK))
	   {
	      sprintf(message,"data file %s doesn't exist.",path_lista_moduli);
	      attention_wdg =  (Widget) attention (UxTopLevel,message,MAPPA,
	                                           geom_attention);
	      scrivi_messaggio(message);
	      return;
	   }
	
	   if ((fp = fopen(path_lista_moduli,"r")) == NULL)
	   {
	      sprintf(message,"Can't open data file %s",path_lista_moduli);
	      attention_wdg =  (Widget) attention (UxTopLevel,message,MAPPA,
	                                           geom_attention);
	      scrivi_messaggio(message);
	      return;
	   }
	
	   create_lista_moduli(fp, tipo_lib, USER_MODULES_SELECTION, 
	                       &dbox_list_utente_managed);
	   fclose(fp);
	
	/* Cancellazione della FileSelectionBox */
	   dbox_fileselect_managed = False;
	   UxDestroyInterface(UxWidget);
	
	}
	UxAbox_file_selectionContext = UxSaveCtx;
}

static void	cancelCB_fileSelectionBox1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCabox_file_selection *UxSaveCtx, *UxContext;

	UxSaveCtx = UxAbox_file_selectionContext;
	UxAbox_file_selectionContext = UxContext =
			(_UxCabox_file_selection *) UxGetContext( UxWidget );
	{
	dbox_fileselect_managed = False;
	UxDestroyInterface(UxWidget);
	}
	UxAbox_file_selectionContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_abox_file_selection()
{

	abox_file_selection = XtVaCreatePopupShell( "abox_file_selection",
			applicationShellWidgetClass, UxTopLevel,
			XmNgeometry, "+140+255",
			XmNheight, 400,
			XmNwidth, 400,
			XmNy, 185,
			XmNx, 250,
			NULL );

	UxPutContext( abox_file_selection, (char *) UxAbox_file_selectionContext );

	fileSelectionBox1 = XtVaCreateManagedWidget( "fileSelectionBox1",
			xmFileSelectionBoxWidgetClass, abox_file_selection,
			RES_CONVERT( XmNtextString, "" ),
			RES_CONVERT( XmNselectionLabelString, "Select the directory of another LEGOCAD user" ),
			RES_CONVERT( XmNnoMatchString, "<NO FILES FOUND>" ),
			XmNdefaultPosition, FALSE,
			RES_CONVERT( XmNdialogTitle, "MODULE COPY" ),
			RES_CONVERT( XmNpattern, "" ),
			XmNheight, 380,
			XmNwidth, 380,
			XmNy, 185,
			XmNx, 250,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( fileSelectionBox1, (char *) UxAbox_file_selectionContext );

	XtAddCallback( abox_file_selection, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxAbox_file_selectionContext );

	XtAddCallback( fileSelectionBox1, XmNokCallback,
			okCallback_fileSelectionBox1,
			(XtPointer) tipo_modulo );
	XtAddCallback( fileSelectionBox1, XmNcancelCallback,
			cancelCB_fileSelectionBox1,
			(XtPointer) UxAbox_file_selectionContext );



	return ( abox_file_selection );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_file_selection()
{
	Widget                  rtrn;
	_UxCabox_file_selection *UxContext;

	UxAbox_file_selectionContext = UxContext =
		(_UxCabox_file_selection *) XtMalloc( sizeof(_UxCabox_file_selection) );

	{
		Widget wdg;
		   char *path_home, path[256];
		rtrn = _Uxbuild_abox_file_selection();

		/* Il push-button di 'HELP' ed il text di selezione non vengono visualizzati */
		
		   wdg = XmFileSelectionBoxGetChild(UxGetWidget(fileSelectionBox1),
		                                    XmDIALOG_HELP_BUTTON);
		   XtUnmanageChild (wdg);
		
		   wdg = XmFileSelectionBoxGetChild(UxGetWidget(fileSelectionBox1),
		                                    XmDIALOG_TEXT);
		   XtUnmanageChild (wdg);
		
		   wdg = XmFileSelectionBoxGetChild(UxGetWidget(fileSelectionBox1),
		                                    XmDIALOG_FILTER_TEXT);
		
		/***
		   XtUnmanageChild (wdg);
		***/
		
		/* la scroll-list dei files non viene abilitata per la selezione */
		/* (guardare ma non toccare ...) */
		
#ifdef CERCA_ERR
		   wdg = XmFileSelectionBoxGetChild(UxGetWidget(fileSelectionBox1),XmDIALOG_LIST);
		   XSelectInput(display, XtWindow(wdg), ExposureMask);
#endif
		
		   UxPopupInterface (rtrn, no_grab);
		   dbox_fileselect_managed = True;
		
		   return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_file_selection()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_file_selection();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

