
/*******************************************************************************
       line_width_dialog.c
       (Generated from interface file line_width_dialog.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/SelectioB.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo line_width_dialog.i
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)line_width_dialog.i	5.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/


/*******************************************************************************
       The definition of the context structure:
       If you create multiple copies of your interface, the context
       structure ensures that your callbacks use the variables for the
       correct copy.

       For each swidget in the interface, each argument to the Interface
       function, and each variable in the Interface Specific section of the
       Declarations Editor, there is an entry in the context structure.
       and a #define.  The #define makes the variable name refer to the
       corresponding entry in the context structure.
*******************************************************************************/

typedef	struct
{
	Widget	Uxline_width_dialog;
	Widget	Uxwid_disegno;
} _UxCline_width_dialog;

static _UxCline_width_dialog   *UxLine_width_dialogContext;
#define line_width_dialog       UxLine_width_dialogContext->Uxline_width_dialog
#define wid_disegno             UxLine_width_dialogContext->Uxwid_disegno



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_line_width_dialog();

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	okCallback_line_width_dialog( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCline_width_dialog   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxLine_width_dialogContext;
	UxLine_width_dialogContext = UxContext =
			(_UxCline_width_dialog *) UxGetContext( UxWidget );
	{
	Arg args[3];
	Cardinal lnargs;
	extern char *extract_string();
	int curr_line_width;
	
	XmString xms;
	char str_line_width[10];
	
	lnargs=0;
	XtSetArg(args[lnargs],XmNtextString,&xms);lnargs++;
	XtGetValues(UxWidget,args,lnargs);
	
	strcpy(str_line_width,extract_string(xms));
	
	
	sscanf(str_line_width,"%d",&curr_line_width);
	set_line_width(wid_disegno,curr_line_width);
	
	set_current_gcs(wid_disegno);
	
	 
	}
	UxLine_width_dialogContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_line_width_dialog()
{
	Widget		_UxParent;


	/* Creation of line_width_dialog */
	_UxParent = XtVaCreatePopupShell( "line_width_dialog_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 720,
			XmNy, 460,
			XmNwidth, 260,
			XmNheight, 160,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "line_width_dialog",
			NULL );

	line_width_dialog = XtVaCreateWidget( "line_width_dialog",
			xmSelectionBoxWidgetClass,
			_UxParent,
			XmNdialogType, XmDIALOG_PROMPT,
			XmNunitType, XmPIXELS,
			XmNwidth, 260,
			XmNheight, 160,
			RES_CONVERT( XmNtextString, "" ),
			XmNdialogStyle, XmDIALOG_PRIMARY_APPLICATION_MODAL,
			XmNresizePolicy, XmRESIZE_NONE,
			RES_CONVERT( XmNselectionLabelString, "Line width:" ),
			XmNtextColumns, 5,
			NULL );
	XtAddCallback( line_width_dialog, XmNokCallback,
		(XtCallbackProc) okCallback_line_width_dialog,
		(XtPointer) UxLine_width_dialogContext );

	UxPutContext( line_width_dialog, (char *) UxLine_width_dialogContext );


	XtAddCallback( line_width_dialog, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxLine_width_dialogContext);


	return ( line_width_dialog );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_line_width_dialog( _Uxwid_disegno )
	Widget	_Uxwid_disegno;
{
	Widget                  rtrn;
	_UxCline_width_dialog   *UxContext;

	UxLine_width_dialogContext = UxContext =
		(_UxCline_width_dialog *) UxNewContext( sizeof(_UxCline_width_dialog), False );

	wid_disegno = _Uxwid_disegno;

	{
		extern int curr_line_width;
		XmString xms;
		char str_width[10];
		rtrn = _Uxbuild_line_width_dialog();

		sprintf(str_width,"%d",get_line_width(wid_disegno));
		xms= XmStringCreateSimple(str_width);
		set_something(rtrn, XmNtextString, (void*) xms);
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

