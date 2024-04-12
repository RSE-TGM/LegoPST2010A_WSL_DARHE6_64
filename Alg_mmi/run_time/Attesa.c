
/*******************************************************************************
       Attesa.c
       (Generated from interface file Attesa.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Scale.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/DialogS.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/


#include <Rt/RtMemory.h>


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
	Widget	UxAttesa;
	Widget	UxformAttesa;
	Widget	UxlabelAttesa;
	Widget	UxscaleAttesa;
	int	Uxvalore;
	Widget	UxpadreAttesa;
} _UxCAttesa;

static _UxCAttesa              *UxAttesaContext;
#define Attesa                  UxAttesaContext->UxAttesa
#define formAttesa              UxAttesaContext->UxformAttesa
#define labelAttesa             UxAttesaContext->UxlabelAttesa
#define scaleAttesa             UxAttesaContext->UxscaleAttesa
#define valore                  UxAttesaContext->Uxvalore
#define padreAttesa             UxAttesaContext->UxpadreAttesa



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	popup_Attesa();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

SettaAttesa(Widget wid,int delta)
{
#ifndef DESIGN_TIME
_UxCAttesa *Context;

        Context =(_UxCAttesa *) UxGetContext(wid);
	Context->Uxvalore = Context->Uxvalore + delta;
	if(Context->Uxvalore > 100)
		Context->Uxvalore = 0;
	set_something(Context->UxscaleAttesa,XmNvalue,Context->Uxvalore);

#endif
}

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_Attesa()
{
	Widget		_UxParent;


	/* Creation of Attesa */
	_UxParent = padreAttesa;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	Attesa = XtVaCreatePopupShell( "Attesa",
			xmDialogShellWidgetClass,
			_UxParent,
			XmNx, 430,
			XmNy, 220,
			XmNwidth, 430,
			XmNheight, 200,
			NULL );
	UxPutContext( Attesa, (char *) UxAttesaContext );


	/* Creation of formAttesa */
	formAttesa = XtVaCreateWidget( "formAttesa",
			xmFormWidgetClass,
			Attesa,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNunitType, XmPIXELS,
			XmNx, 296,
			XmNy, 143,
			XmNwidth, 400,
			XmNheight, 190,
			RES_CONVERT( XmNbackground, "#50a050" ),
			NULL );
	UxPutContext( formAttesa, (char *) UxAttesaContext );


	/* Creation of labelAttesa */
	labelAttesa = XtVaCreateManagedWidget( "labelAttesa",
			xmLabelWidgetClass,
			formAttesa,
			XmNx, 50,
			XmNy, 130,
			XmNwidth, 290,
			XmNheight, 40,
			RES_CONVERT( XmNbackground, "#50a050" ),
			RES_CONVERT( XmNlabelString, "Wait" ),
			XmNshadowThickness, 0,
			RES_CONVERT( XmNtopShadowColor, "#50a0a0" ),
			RES_CONVERT( XmNbottomShadowColor, "#a05050" ),
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 20,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 20,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 20,
			XmNborderWidth, 4,
			RES_CONVERT( XmNborderColor, "#5050a0" ),
			NULL );
	UxPutContext( labelAttesa, (char *) UxAttesaContext );


	/* Creation of scaleAttesa */
	scaleAttesa = XtVaCreateManagedWidget( "scaleAttesa",
			xmScaleWidgetClass,
			formAttesa,
			XmNx, 50,
			XmNy, 40,
			XmNwidth, 320,
			XmNheight, 50,
			XmNorientation, XmHORIZONTAL,
			RES_CONVERT( XmNbackground, "#50a050" ),
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 20,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 20,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 20,
			RES_CONVERT( XmNforeground, "#50a050" ),
			NULL );
	UxPutContext( scaleAttesa, (char *) UxAttesaContext );


	XtAddCallback( Attesa, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxAttesaContext);


	return ( Attesa );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	popup_Attesa( _UxpadreAttesa )
	Widget	_UxpadreAttesa;
{
	Widget                  rtrn;
	_UxCAttesa              *UxContext;

	UxAttesaContext = UxContext =
		(_UxCAttesa *) UxNewContext( sizeof(_UxCAttesa), False );

	padreAttesa = _UxpadreAttesa;

	{
		valore =0;
		rtrn = _Uxbuild_Attesa();

		UxPopupInterface(rtrn,XtGrabExclusive );
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

