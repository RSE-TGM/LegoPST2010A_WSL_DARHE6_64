/**********************************************************************
*
*       C Source:               dati_selectionD.c
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Tue Apr 30 11:48:11 1996 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: dati_selectionD.c,2 %  (%full_filespec: 1,csrc,dati_selectionD.c,2 %)";
#endif

/*******************************************************************************
	dati_selectionD.c

*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/FileSB.h>
#include <Xm/DialogS.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo dati_selectionD.c
   tipo 
   release 2.15
   data 4/26/95
   reserved @(#)dati_selectionD.c	2.15
*/
/*
        Variabile per identificazione della versione
*/
static char SccsID[] = "@(#)dati_selectionD.c	2.15\t4/26/95";
/*
        Fine sezione per SCCS
*/
#endif 

#include <malloc.h>
#include <string.h>
#include <f03.h>
#include <libuimleg.h>
#include "dati.h"
Boolean  saving;
extern Boolean graphics_on;

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
	swidget	Uxparent;
} _UxCdati_selectionD;

#define parent                  UxDati_selectionDContext->Uxparent

static _UxCdati_selectionD	*UxDati_selectionDContext;

Widget	dati_selectionD;
Widget	fileSelectionBox;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_dati_selectionD();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	okCallback_fileSelectionBox( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdati_selectionD     *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDati_selectionDContext;
	UxDati_selectionDContext = UxContext =
			(_UxCdati_selectionD *) UxGetContext( UxWidget );
	{
	FILE *fp_write;
	int i;
	extern swidget labelModelDati;
	extern Widget topwidget;
	extern swidget listaBlocchi;
	extern swidget create_vis_msg();
	extern char *estr_nome_modello();
	extern char *str_toupper();
	extern int stato;
	char *nome_modello;
	char str[120];
	char str2[120];
	char *path;
	path=str;
	  
	if (saving)
		{
		printf("Save file: %s\n", UxGetTextString(fileSelectionBox));
	        path=UxGetTextString(fileSelectionBox);
		fp_write=fopen(path,"w");
		if(fp_write)
			{
			write_file_f14(fp_write);
			fclose(fp_write);
			}
	  	else
			{
			sprintf(str2,"Cannot write on file %s",path);
			create_vis_msg(str2);
			}
	   	}
	else
	    {
	
	    path=UxGetDirSpec(fileSelectionBox);
	
	    printf("Open file: %s\n",path );
	/*
	  Si posiziona nel direttorio selezionato dall'utente
	*/
	    if(chdir(path))
		{
	    	sprintf(str2,"Cannot open model %s",path);
	   	create_vis_msg(str2);
		}
	/*
	  Legge il file f03 da cui ricava tutte le informazioni relative
	  a blocchi e variabili
	*/
	    else if(read_file_f03())
		{
	 	sprintf(str2,"Cannot open file f03");
		create_vis_msg(str2);
		}
	/*
	  Legge il file f14 da cui ricava i valori delle variabili
	*/
	    else if(read_file_f14(neqsis,nu))
		{
		sprintf(str2,"Cannot open file f14");
		create_vis_msg(str2);
		}
	    else
		{
		nome_modello=estr_nome_modello(path);
		str_toupper(nome_modello);
		sprintf(str2,"Model name: %s",nome_modello);
		UxPutLabelString(labelModelDati,str2);
	/*
	 Il modello e' stato scelto: aggiorna lo stato di abilitazione
	 dei bottoni del pulldown menu
	*/
		stato=SCELTO;
		update_pulldown();
	/*
	 Costruisce la lista dei blocchi appartenenti al modello
	*/
		for(i=0;i<nbl;i++)
			{
			aggiungi_item_n(listaBlocchi,nom_bloc[i],80);
			}
	/*
	  aggiorna i valori dei contatori numero eqz. e variabili
	  in main window
	*/
		update_contatori();
		
	/*
	 lancia l'applicativo grafico
	*/
	        if(graphics_on)
		   lancia_macro(topwidget,UxGetWidget(listaBlocchi));	
		}
	    }
	UxPopdownInterface(dati_selectionD);
	}
	UxDati_selectionDContext = UxSaveCtx;
}

static void	cancelCB_fileSelectionBox( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCdati_selectionD     *UxSaveCtx, *UxContext;

	UxSaveCtx = UxDati_selectionDContext;
	UxDati_selectionDContext = UxContext =
			(_UxCdati_selectionD *) UxGetContext( UxWidget );
	{
	  UxPopdownInterface(dati_selectionD);
	}
	UxDati_selectionDContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_dati_selectionD()
{

	dati_selectionD = XtVaCreatePopupShell( "dati_selectionD",
			xmDialogShellWidgetClass, parent,
			RES_CONVERT( XmNbackground, "#79cdcd" ),
			NULL );

	UxPutContext( dati_selectionD, (char *) UxDati_selectionDContext );

	fileSelectionBox = XtVaCreateWidget( "fileSelectionBox",
			xmFileSelectionBoxWidgetClass, dati_selectionD,
			RES_CONVERT( XmNdirListLabelString, "Path names" ),
			RES_CONVERT( XmNfileListLabelString, "Directories" ),
			XmNfileTypeMask, XmFILE_DIRECTORY,
			XmNdialogStyle, XmDIALOG_PRIMARY_APPLICATION_MODAL,
			NULL );

	UxPutContext( fileSelectionBox, (char *) UxDati_selectionDContext );

	XtAddCallback( dati_selectionD, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxDati_selectionDContext );

	XtAddCallback( fileSelectionBox, XmNokCallback,
			okCallback_fileSelectionBox,
			(XtPointer) UxDati_selectionDContext );
	XtAddCallback( fileSelectionBox, XmNcancelCallback,
			cancelCB_fileSelectionBox,
			(XtPointer) UxDati_selectionDContext );



	return ( dati_selectionD );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_dati_selectionD( _Uxparent )
	swidget	_Uxparent;
{
	Widget                  rtrn;
	_UxCdati_selectionD     *UxContext;

	UxDati_selectionDContext = UxContext =
		(_UxCdati_selectionD *) XtMalloc( sizeof(_UxCdati_selectionD) );

	parent = _Uxparent;
	rtrn = _Uxbuild_dati_selectionD();

	XtUnmanageChild(XmFileSelectionBoxGetChild(UxGetWidget(fileSelectionBox), XmDIALOG_HELP_BUTTON));
	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_dati_selectionD( _Uxparent )
	swidget	_Uxparent;
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_dati_selectionD( _Uxparent );

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

