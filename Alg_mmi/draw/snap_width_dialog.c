
/*******************************************************************************
       snap_width_dialog.c
       (Generated from interface file snap_width_dialog.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"
#include "draw.h"
#include "libutilx.h"
extern  void *		UxNewContext();

#include <Xm/SelectioB.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo snap_width_dialog.i
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)snap_width_dialog.i	5.1
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
	Widget	Uxsnap_width_dialog;
	Widget	Uxwidget_disegno;
} _UxCsnap_width_dialog;

static _UxCsnap_width_dialog   *UxSnap_width_dialogContext;
#define snap_width_dialog       UxSnap_width_dialogContext->Uxsnap_width_dialog
#define widget_disegno          UxSnap_width_dialogContext->Uxwidget_disegno



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_snap_width_dialog();
void DrawSetSnap(Widget,int);
extern int set_line_width(Widget  , int );

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	okCallback_snap_width_dialog( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCsnap_width_dialog   *UxSaveCtx, *UxContext;

	UxSaveCtx = UxSnap_width_dialogContext;
	UxSnap_width_dialogContext = UxContext =
			(_UxCsnap_width_dialog *) UxGetContext( UxWidget );
	{
	Arg args[3];
	Cardinal lnargs;
	extern char *extract_string();
	int step;
	 
	XmString xms;
	char str_snap_width[10];
	
	lnargs=0;
	XtSetArg(args[lnargs],XmNtextString,&xms);lnargs++;
	XtGetValues(UxWidget,args,lnargs);
	
	strcpy(str_snap_width,extract_string(xms));
	
	sscanf(str_snap_width,"%d",&step);
	DrawSetSnap(widget_disegno,step);
	
	}
	UxSnap_width_dialogContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_snap_width_dialog()
{
	Widget		_UxParent;


	/* Creation of snap_width_dialog */
	_UxParent = XtVaCreatePopupShell( "snap_width_dialog_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 720,
			XmNy, 460,
			XmNwidth, 260,
			XmNheight, 160,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "snap_width_dialog",
			NULL );

	snap_width_dialog = XtVaCreateWidget( "snap_width_dialog",
			xmSelectionBoxWidgetClass,
			_UxParent,
			XmNdialogType, XmDIALOG_PROMPT,
			XmNunitType, XmPIXELS,
			XmNwidth, 260,
			XmNheight, 160,
			RES_CONVERT( XmNtextString, "" ),
			XmNdialogStyle, XmDIALOG_PRIMARY_APPLICATION_MODAL,
			XmNresizePolicy, XmRESIZE_NONE,
			RES_CONVERT( XmNselectionLabelString, "Snap width:" ),
			XmNtextColumns, 5,
			NULL );
	XtAddCallback( snap_width_dialog, XmNokCallback,
		(XtCallbackProc) okCallback_snap_width_dialog,
		(XtPointer) UxSnap_width_dialogContext );

	UxPutContext( snap_width_dialog, (char *) UxSnap_width_dialogContext );


	XtAddCallback( snap_width_dialog, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxSnap_width_dialogContext);


	return ( snap_width_dialog );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_snap_width_dialog( _Uxwidget_disegno )
	Widget	_Uxwidget_disegno;
{
	Widget                  rtrn;
	_UxCsnap_width_dialog   *UxContext;

	UxSnap_width_dialogContext = UxContext =
		(_UxCsnap_width_dialog *) UxNewContext( sizeof(_UxCsnap_width_dialog), False );

	widget_disegno = _Uxwidget_disegno;

	{
		XmString xms;
		char str_width[10];
		rtrn = _Uxbuild_snap_width_dialog();

		sprintf(str_width,"%d",get_step(widget_disegno));
		xms= XmStringCreateSimple(str_width);
		set_something_val(rtrn, XmNtextString, (XtArgVal)xms);
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

