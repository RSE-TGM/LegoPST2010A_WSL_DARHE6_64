
/*******************************************************************************
	Menu_graf_exit.c
	(Generated from interface file Menu_graf_exit.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/PushB.h>
#include <Xm/Label.h>
#include <Xm/Separator.h>
#include <Xm/Form.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo Menu_graf_exit.i
   tipo 
   release 1.10
   data 3/28/95
   reserved @(#)Menu_graf_exit.i	1.10
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif


extern char f22source[],f22target[],f22undo[];
extern int pid;

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
	Widget	Uxseparator2;
	Widget	UxpushButton3;
	Widget	UxpushButton4;
} _UxCMenu_graf_exit;

#define separator2              UxMenu_graf_exitContext->Uxseparator2
#define pushButton3             UxMenu_graf_exitContext->UxpushButton3
#define pushButton4             UxMenu_graf_exitContext->UxpushButton4

static _UxCMenu_graf_exit	*UxMenu_graf_exitContext;

Widget	Menu_graf_exit;
Widget	label_output;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_Menu_graf_exit();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

EseguiRemoveTmp()
{
   extern FILE *fpELENCO;
   extern char *elenco_filetmp; 
   char esegui_shell[200];

   fclose(fpELENCO);

   sprintf(esegui_shell,"chmod a+x %s",elenco_filetmp);
   system(esegui_shell);   


   sprintf(esegui_shell,"csh %s",elenco_filetmp);
   system(esegui_shell); 
   
   sprintf(esegui_shell,"rm %s",elenco_filetmp);
   system(esegui_shell);
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_pushButton3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCMenu_graf_exit      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMenu_graf_exitContext;
	UxMenu_graf_exitContext = UxContext =
			(_UxCMenu_graf_exit *) UxGetContext( UxWidget );
	{
	char cdo[100],strappo[50];
	
	close_22dat ();
	CancellazioneF22();
	EseguiRemoveTmp(); 
	if (pid !=0)
		{
		sprintf (strappo,"%d",pid);
		strcpy (cdo,"kill -9 ");
		strcat (cdo,strappo);
		system (cdo);
		}
	exit(0);
	}
	UxMenu_graf_exitContext = UxSaveCtx;
}

static void	activateCB_pushButton4( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCMenu_graf_exit      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMenu_graf_exitContext;
	UxMenu_graf_exitContext = UxContext =
			(_UxCMenu_graf_exit *) UxGetContext( UxWidget );
	{
	UxPopdownInterface (Menu_graf_exit);
	}
	UxMenu_graf_exitContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_Menu_graf_exit()
{
	Widget	Menu_graf_exit_shell;

	Menu_graf_exit_shell = XtVaCreatePopupShell( "Menu_graf_exit_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 361,
			XmNy, 340,
			XmNwidth, 288,
			XmNheight, 121,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "Menu_graf_exit",
			NULL );

	Menu_graf_exit = XtVaCreateWidget( "Menu_graf_exit",
			xmFormWidgetClass, Menu_graf_exit_shell,
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			XmNheight, 121,
			XmNwidth, 288,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( Menu_graf_exit, (char *) UxMenu_graf_exitContext );

	separator2 = XtVaCreateManagedWidget( "separator2",
			xmSeparatorWidgetClass, Menu_graf_exit,
			XmNheight, 15,
			XmNwidth, 280,
			XmNy, 55,
			XmNx, 5,
			NULL );

	UxPutContext( separator2, (char *) UxMenu_graf_exitContext );

	label_output = XtVaCreateManagedWidget( "label_output",
			xmLabelWidgetClass, Menu_graf_exit,
			XmNrecomputeSize, FALSE,
			RES_CONVERT( XmNlabelString, "" ),
			XmNheight, 45,
			XmNwidth, 280,
			XmNy, 5,
			XmNx, 5,
			NULL );

	UxPutContext( label_output, (char *) UxMenu_graf_exitContext );

	pushButton3 = XtVaCreateManagedWidget( "pushButton3",
			xmPushButtonWidgetClass, Menu_graf_exit,
			RES_CONVERT( XmNlabelString, "OK" ),
			XmNheight, 45,
			XmNwidth, 90,
			XmNy, 70,
			XmNx, 5,
			NULL );

	UxPutContext( pushButton3, (char *) UxMenu_graf_exitContext );

	pushButton4 = XtVaCreateManagedWidget( "pushButton4",
			xmPushButtonWidgetClass, Menu_graf_exit,
			RES_CONVERT( XmNlabelString, "CANCEL" ),
			XmNheight, 45,
			XmNwidth, 90,
			XmNy, 70,
			XmNx, 190,
			NULL );

	UxPutContext( pushButton4, (char *) UxMenu_graf_exitContext );

	XtAddCallback( Menu_graf_exit, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxMenu_graf_exitContext );

	XtAddCallback( pushButton3, XmNactivateCallback,
			activateCB_pushButton3,
			(XtPointer) UxMenu_graf_exitContext );

	XtAddCallback( pushButton4, XmNactivateCallback,
			activateCB_pushButton4,
			(XtPointer) UxMenu_graf_exitContext );



	return ( Menu_graf_exit );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_Menu_graf_exit()
{
	Widget                  rtrn;
	_UxCMenu_graf_exit      *UxContext;

	UxMenu_graf_exitContext = UxContext =
		(_UxCMenu_graf_exit *) XtMalloc( sizeof(_UxCMenu_graf_exit) );

	rtrn = _Uxbuild_Menu_graf_exit();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_Menu_graf_exit()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_Menu_graf_exit();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

