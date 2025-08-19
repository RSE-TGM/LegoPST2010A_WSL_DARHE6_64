
/*******************************************************************************
	applicationShell1.c
	(Generated from interface file applicationShell1.i)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/FileSB.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo applicationShell1.i
   tipo 
   release 2.6
   data 3/20/95
   reserved @(#)applicationShell1.i	2.6
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <Xm/MainW.h>
#include <libutilx.h>
/*
   #include <UxMainW.h>
*/

char filename[FILENAME_MAX];
char font[100];
Widget texto;
int editare;
Dialog_geometry geom;
Elenco_callback funz;
extern Widget editor();

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
	Widget	UxapplEditf01;
	Widget	UxfileBox1;
} _UxCapplEditf01;

#define applEditf01             UxApplEditf01Context->UxapplEditf01
#define fileBox1                UxApplEditf01Context->UxfileBox1

static _UxCapplEditf01	*UxApplEditf01Context;

Widget	form1;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_applEditf01();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

void OkCB()
{
   exit(0);
}

void lancia_edit(char *fname,int edit)
{
   Arg args[20];
   int narg;
   char butt_label[10];
   swidget gost;

   geom.default_pos = False;   
   geom.x = 20;
   geom.y = 100;
   geom.width = 750;
   geom.height = 650;


   strcpy(font,"8x13");

   strcpy(butt_label,"Ok");
   funz[0].button_label = butt_label;
   funz[0].callback = OkCB;




   narg = 0;
   XtSetArg(args[narg],XmNminWidth,500); narg++;
   XtSetArg(args[narg],XmNminHeight,400); narg++;   
/**
   gost = UxCreateMainWindow("Main",UxTopLevel);
   UxCreateWidget(gost);
**/
  
  gost = lcCreateMainWindow("Main",UxTopLevel);
  editor(gost,&texto,fname,edit,font,funz,geom);

   

}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	cancelCB_fileBox1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCapplEditf01         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxApplEditf01Context;
	UxApplEditf01Context = UxContext =
			(_UxCapplEditf01 *) UxGetContext( UxWidget );
	{
	exit(0);
	}
	UxApplEditf01Context = UxSaveCtx;
}

static void	okCallback_fileBox1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCapplEditf01         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxApplEditf01Context;
	UxApplEditf01Context = UxContext =
			(_UxCapplEditf01 *) UxGetContext( UxWidget );
	{
	char butt_label[10];
	
	geom.default_pos = True;
	geom.x = 200;
	geom.y = 100;
	geom.width = 10;
	geom.height = 20;
	
	editare = False;
	
	strcpy(filename,UxGetTextString(fileBox1));
	
	strcpy(font,"8x13");
	
	strcpy(butt_label,"Ok");
	funz[0].button_label = butt_label;
	funz[0].callback = OkCB;
	
	
	editor(UxGetWidget(form1),&texto,filename,editare,font,funz,geom);
	
	}
	UxApplEditf01Context = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_applEditf01()
{

	applEditf01 = XtVaCreatePopupShell( "applEditf01",
			applicationShellWidgetClass, UxTopLevel,
			XmNheight, 320,
			XmNwidth, 320,
			XmNy, 109,
			XmNx, 139,
			NULL );

	UxPutContext( applEditf01, (char *) UxApplEditf01Context );

	form1 = XtVaCreateManagedWidget( "form1",
			xmFormWidgetClass, applEditf01,
			XmNheight, 270,
			XmNwidth, 290,
			XmNy, 40,
			XmNx, 50,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form1, (char *) UxApplEditf01Context );

	fileBox1 = XtVaCreateManagedWidget( "fileBox1",
			xmFileSelectionBoxWidgetClass, form1,
			XmNheight, 300,
			XmNwidth, 300,
			XmNy, 10,
			XmNx, 10,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( fileBox1, (char *) UxApplEditf01Context );

	XtAddCallback( applEditf01, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxApplEditf01Context );

	XtAddCallback( fileBox1, XmNcancelCallback,
			cancelCB_fileBox1,
			(XtPointer) UxApplEditf01Context );
	XtAddCallback( fileBox1, XmNokCallback,
			okCallback_fileBox1,
			(XtPointer) UxApplEditf01Context );



	return ( applEditf01 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_applEditf01()
{
	Widget                  rtrn;
	_UxCapplEditf01         *UxContext;

	UxApplEditf01Context = UxContext =
		(_UxCapplEditf01 *) XtMalloc( sizeof(_UxCapplEditf01) );

	rtrn = _Uxbuild_applEditf01();

	return(rtrn);
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_applEditf01()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_applEditf01();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

