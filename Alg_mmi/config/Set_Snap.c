
/*******************************************************************************
       Set_Snap.c
       (Generated from interface file Set_Snap.i)
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
   modulo Set_Snap.i
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)Set_Snap.i	5.1
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <Xm/Text.h>
#include "config.h"

extern swidget topLevelShell;


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
	Widget	UxSet_Snap;
	PAGINA	*Uxpag;
	Widget	Uxparent_wid;
} _UxCSet_Snap;

static _UxCSet_Snap            *UxSet_SnapContext;
#define Set_Snap                UxSet_SnapContext->UxSet_Snap
#define pag                     UxSet_SnapContext->Uxpag
#define parent_wid              UxSet_SnapContext->Uxparent_wid



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_Set_Snap();

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	okCallback_Set_Snap( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCSet_Snap            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxSet_SnapContext;
	UxSet_SnapContext = UxContext =
			(_UxCSet_Snap *) UxGetContext( UxWidget );
	{
	char *str_snap;
	Widget wtext;
	int Snap;
	
	
	wtext=XmSelectionBoxGetChild(UxThisWidget,XmDIALOG_TEXT);
	str_snap=XmTextGetString(wtext);
	sscanf(str_snap,"%d",&Snap);
	DrawSetSnap(pag->drawing,Snap);
	pag->snap_pag= Snap;
	XtFree(str_snap);
	
	XtDestroyWidget(UxWidget);
	
	
	}
	UxSet_SnapContext = UxSaveCtx;
}

static	void	cancelCB_Set_Snap( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCSet_Snap            *UxSaveCtx, *UxContext;

	UxSaveCtx = UxSet_SnapContext;
	UxSet_SnapContext = UxContext =
			(_UxCSet_Snap *) UxGetContext( UxWidget );
	{
	UxDestroyInterface(UxWidget);
	
	}
	UxSet_SnapContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_Set_Snap()
{
	Widget		_UxParent;


	/* Creation of Set_Snap */
	_UxParent = parent_wid;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	_UxParent = XtVaCreatePopupShell( "Set_Snap_shell",
			xmDialogShellWidgetClass, _UxParent,
			XmNx, 551,
			XmNy, 425,
			XmNwidth, 177,
			XmNheight, 140,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "Set_Snap",
			NULL );

	Set_Snap = XtVaCreateWidget( "Set_Snap",
			xmSelectionBoxWidgetClass,
			_UxParent,
			XmNdialogType, XmDIALOG_PROMPT,
			XmNunitType, XmPIXELS,
			XmNwidth, 177,
			XmNheight, 140,
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			RES_CONVERT( XmNselectionLabelString, "Snap Value" ),
			XmNminimizeButtons, FALSE,
			XmNnoResize, TRUE,
			NULL );
	XtAddCallback( Set_Snap, XmNokCallback,
		(XtCallbackProc) okCallback_Set_Snap,
		(XtPointer) UxSet_SnapContext );
	XtAddCallback( Set_Snap, XmNcancelCallback,
		(XtCallbackProc) cancelCB_Set_Snap,
		(XtPointer) UxSet_SnapContext );

	UxPutContext( Set_Snap, (char *) UxSet_SnapContext );


	XtAddCallback( Set_Snap, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxSet_SnapContext);


	return ( Set_Snap );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_Set_Snap( _Uxpag, _Uxparent_wid )
	PAGINA	*_Uxpag;
	Widget	_Uxparent_wid;
{
	Widget                  rtrn;
	_UxCSet_Snap            *UxContext;

	UxSet_SnapContext = UxContext =
		(_UxCSet_Snap *) UxNewContext( sizeof(_UxCSet_Snap), False );

	pag = _Uxpag;
	parent_wid = _Uxparent_wid;

	{
		Widget wtext;
		Widget whelp;
		char str_snap[100];
		rtrn = _Uxbuild_Set_Snap();

		wtext=XmSelectionBoxGetChild(rtrn,XmDIALOG_TEXT);
		sprintf(str_snap,"%d",pag->snap_pag);
		XmTextSetString(wtext,str_snap);
		whelp=XmSelectionBoxGetChild(rtrn,XmDIALOG_HELP_BUTTON);
		XtDestroyWidget(whelp);
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

