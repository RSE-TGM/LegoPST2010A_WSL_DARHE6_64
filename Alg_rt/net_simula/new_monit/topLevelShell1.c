
/*******************************************************************************
       topLevelShell1.c
       (Generated from interface file topLevelShell1.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Text.h>
#include <Xm/Label.h>
#include <Xm/BulletinB.h>
#include <Xm/CascadeB.h>
#include <Xm/RowColumn.h>
#include <Xm/Separator.h>
#include <Xm/PushB.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
#include "sim_param.h"
#include "sim_types.h"
#include "dispatcher.h"

#include "bistrutt.h"
#include "banco_globals.h"
extern int master_interface_active;
#include "option.h"
#endif
#ifndef MAX_PATH_LEN 
#define MAX_PATH_LEN 100
#endif
extern int isSuperuser;


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
	Widget	Uxform1;
	Widget	Uxform34;
	Widget	UxshutdownButton2;
	Widget	UxstartupButton;
	Widget	Uxseparator1;
	Widget	Uxmenu9;
	Widget	UxmasterMonitMenu;
	Widget	UxmasterMonitMenuQuitpb;
	Widget	Uxmenu9_top_b1;
	Widget	UxbulletinBoard1;
	Widget	UxsimulatorPathLabel;
	Widget	UxsimulatorPathText;
	Widget	UxsimulatorPathName;
	Widget	UxsimulatorNameText;
} _UxCtopLevelShell1;

static _UxCtopLevelShell1      *UxTopLevelShell1Context;
#define form1                   UxTopLevelShell1Context->Uxform1
#define form34                  UxTopLevelShell1Context->Uxform34
#define shutdownButton2         UxTopLevelShell1Context->UxshutdownButton2
#define startupButton           UxTopLevelShell1Context->UxstartupButton
#define separator1              UxTopLevelShell1Context->Uxseparator1
#define menu9                   UxTopLevelShell1Context->Uxmenu9
#define masterMonitMenu         UxTopLevelShell1Context->UxmasterMonitMenu
#define masterMonitMenuQuitpb   UxTopLevelShell1Context->UxmasterMonitMenuQuitpb
#define menu9_top_b1            UxTopLevelShell1Context->Uxmenu9_top_b1
#define bulletinBoard1          UxTopLevelShell1Context->UxbulletinBoard1
#define simulatorPathLabel      UxTopLevelShell1Context->UxsimulatorPathLabel
#define simulatorPathText       UxTopLevelShell1Context->UxsimulatorPathText
#define simulatorPathName       UxTopLevelShell1Context->UxsimulatorPathName
#define simulatorNameText       UxTopLevelShell1Context->UxsimulatorNameText


Widget	topLevelShell1;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_topLevelShell1();

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_shutdownButton2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
#ifndef DESIGN_TIME
	system ("killsim");
	if (isSuperuser)
	   system ("newsim&");
	else
	   system ("newsim&");
	
	exit (0);
#endif
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_startupButton( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
#ifndef DESIGN_TIME
	
	system ("newsim_");
	connessioni (topLevelShell1);
	
	if (master_interface_active)
	   {
	   if (!exist_Widget(UxGetWidget(masterMenu)))
	      create_masterMenu(0);
	   }
	else
	   create_masterMenu(0);
	
	XtVaSetValues (UxWidget,XmNsensitive,False,NULL);
	XtVaSetValues (topLevelShell1,XmNiconic,True,NULL);
#endif
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static	void	activateCB_masterMonitMenuQuitpb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
	system ("killsim");
	exit (0);
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_topLevelShell1()
{
	Widget		_UxParent;
	Widget		masterMonitMenu_shell;


	/* Creation of topLevelShell1 */
	_UxParent = UxWidgetToSwidget(UxTopLevel);
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	topLevelShell1 = XtVaCreatePopupShell( "topLevelShell1",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, 0,
			XmNy, 0,
			XmNwidth, 510,
			XmNheight, 210,
			XmNtitle, "MASTER MONIT",
			XmNallowShellResize, TRUE,
			XmNiconName, "MASTER INSTRUCTOR STATION",
			NULL );
	UxPutContext( topLevelShell1, (char *) UxTopLevelShell1Context );


	/* Creation of form1 */
	form1 = XtVaCreateManagedWidget( "form1",
			xmFormWidgetClass,
			topLevelShell1,
			XmNresizePolicy, XmRESIZE_ANY,
			XmNunitType, XmPIXELS,
			XmNx, 110,
			XmNy, 80,
			XmNwidth, 510,
			XmNheight, 210,
			XmNallowOverlap, TRUE,
			XmNlabelFontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--17-120-100-100-M-100-ISO8859-1" ),
			XmNrubberPositioning, TRUE,
			XmNtextFontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--17-120-100-100-M-100-ISO8859-1" ),
			XmNbuttonFontList, UxConvertFontList( "-Adobe-Courier-Bold-R-Normal--17-120-100-100-M-100-ISO8859-1" ),
			NULL );
	UxPutContext( form1, (char *) UxTopLevelShell1Context );


	/* Creation of form34 */
	form34 = XtVaCreateManagedWidget( "form34",
			xmFormWidgetClass,
			form1,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 0,
			XmNy, 140,
			XmNwidth, 520,
			XmNheight, 54,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomPosition, 0,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftPosition, 0,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_NONE,
			XmNtopWidget, NULL,
			NULL );
	UxPutContext( form34, (char *) UxTopLevelShell1Context );


	/* Creation of shutdownButton2 */
	shutdownButton2 = XtVaCreateManagedWidget( "shutdownButton2",
			xmPushButtonWidgetClass,
			form34,
			XmNx, 0,
			XmNy, 10,
			XmNwidth, 150,
			XmNheight, 50,
			RES_CONVERT( XmNlabelString, "SHUTDOWN" ),
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 20,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 10,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftPosition, 70,
			NULL );
	XtAddCallback( shutdownButton2, XmNactivateCallback,
		(XtCallbackProc) activateCB_shutdownButton2,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( shutdownButton2, (char *) UxTopLevelShell1Context );


	/* Creation of startupButton */
	startupButton = XtVaCreateManagedWidget( "startupButton",
			xmPushButtonWidgetClass,
			form34,
			XmNx, 0,
			XmNy, 10,
			XmNwidth, 150,
			XmNheight, 50,
			RES_CONVERT( XmNlabelString, "STARTUP" ),
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 10,
			XmNleftOffset, 20,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 30,
			XmNleftAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 10,
			XmNsensitive, FALSE,
			NULL );
	XtAddCallback( startupButton, XmNactivateCallback,
		(XtCallbackProc) activateCB_startupButton,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( startupButton, (char *) UxTopLevelShell1Context );


	/* Creation of separator1 */
	separator1 = XtVaCreateManagedWidget( "separator1",
			xmSeparatorWidgetClass,
			form1,
			XmNx, 0,
			XmNy, 110,
			XmNwidth, 520,
			XmNheight, 10,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomPosition, 0,
			XmNbottomWidget, form34,
			NULL );
	UxPutContext( separator1, (char *) UxTopLevelShell1Context );


	/* Creation of menu9 */
	menu9 = XtVaCreateManagedWidget( "menu9",
			xmRowColumnWidgetClass,
			form1,
			XmNrowColumnType, XmMENU_BAR,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightPosition, 0,
			XmNleftAttachment, XmATTACH_FORM,
			NULL );
	UxPutContext( menu9, (char *) UxTopLevelShell1Context );


	/* Creation of masterMonitMenu */
	masterMonitMenu_shell = XtVaCreatePopupShell ("masterMonitMenu_shell",
			xmMenuShellWidgetClass, menu9,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	masterMonitMenu = XtVaCreateWidget( "masterMonitMenu",
			xmRowColumnWidgetClass,
			masterMonitMenu_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );
	UxPutContext( masterMonitMenu, (char *) UxTopLevelShell1Context );


	/* Creation of masterMonitMenuQuitpb */
	masterMonitMenuQuitpb = XtVaCreateManagedWidget( "masterMonitMenuQuitpb",
			xmPushButtonWidgetClass,
			masterMonitMenu,
			RES_CONVERT( XmNlabelString, "Quit " ),
			NULL );
	XtAddCallback( masterMonitMenuQuitpb, XmNactivateCallback,
		(XtCallbackProc) activateCB_masterMonitMenuQuitpb,
		(XtPointer) UxTopLevelShell1Context );

	UxPutContext( masterMonitMenuQuitpb, (char *) UxTopLevelShell1Context );


	/* Creation of menu9_top_b1 */
	menu9_top_b1 = XtVaCreateManagedWidget( "menu9_top_b1",
			xmCascadeButtonWidgetClass,
			menu9,
			RES_CONVERT( XmNlabelString, "File" ),
			XmNsubMenuId, masterMonitMenu,
			NULL );
	UxPutContext( menu9_top_b1, (char *) UxTopLevelShell1Context );


	/* Creation of bulletinBoard1 */
	bulletinBoard1 = XtVaCreateManagedWidget( "bulletinBoard1",
			xmBulletinBoardWidgetClass,
			form1,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNx, 50,
			XmNy, 20,
			XmNwidth, 410,
			XmNheight, 100,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftPosition, 0,
			XmNrightAttachment, XmATTACH_FORM,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopPosition, 0,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomWidget, separator1,
			XmNtopWidget, menu9,
			NULL );
	UxPutContext( bulletinBoard1, (char *) UxTopLevelShell1Context );


	/* Creation of simulatorPathLabel */
	simulatorPathLabel = XtVaCreateManagedWidget( "simulatorPathLabel",
			xmLabelWidgetClass,
			bulletinBoard1,
			XmNx, 10,
			XmNy, 20,
			XmNwidth, 150,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "Simulator path" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			NULL );
	UxPutContext( simulatorPathLabel, (char *) UxTopLevelShell1Context );


	/* Creation of simulatorPathText */
	simulatorPathText = XtVaCreateManagedWidget( "simulatorPathText",
			xmTextWidgetClass,
			bulletinBoard1,
			XmNx, 160,
			XmNy, 20,
			XmNwidth, 350,
			XmNheight, 30,
			XmNautoShowCursorPosition, FALSE,
			XmNcursorPositionVisible, FALSE,
			XmNeditable, FALSE,
			XmNmarginHeight, 3,
			NULL );
	UxPutContext( simulatorPathText, (char *) UxTopLevelShell1Context );


	/* Creation of simulatorPathName */
	simulatorPathName = XtVaCreateManagedWidget( "simulatorPathName",
			xmLabelWidgetClass,
			bulletinBoard1,
			XmNx, 10,
			XmNy, 60,
			XmNwidth, 150,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "Simulator name" ),
			XmNalignment, XmALIGNMENT_BEGINNING,
			NULL );
	UxPutContext( simulatorPathName, (char *) UxTopLevelShell1Context );


	/* Creation of simulatorNameText */
	simulatorNameText = XtVaCreateManagedWidget( "simulatorNameText",
			xmTextWidgetClass,
			bulletinBoard1,
			XmNx, 160,
			XmNy, 60,
			XmNwidth, 350,
			XmNheight, 30,
			XmNautoShowCursorPosition, FALSE,
			XmNcursorPositionVisible, FALSE,
			XmNeditable, FALSE,
			XmNmarginHeight, 3,
			NULL );
	UxPutContext( simulatorNameText, (char *) UxTopLevelShell1Context );

	XtVaSetValues(form1,
			XmNdefaultButton, startupButton,
			XmNinitialFocus, startupButton,
			NULL );

	XtVaSetValues(form34,
			XmNdefaultButton, startupButton,
			XmNinitialFocus, startupButton,
			NULL );


	XtAddCallback( topLevelShell1, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxTopLevelShell1Context);


	return ( topLevelShell1 );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_topLevelShell1()
{
	Widget                  rtrn;
	_UxCtopLevelShell1      *UxContext;

	UxTopLevelShell1Context = UxContext =
		(_UxCtopLevelShell1 *) UxNewContext( sizeof(_UxCtopLevelShell1), False );


	{
		char path[MAX_PATH_LEN];
		char sim_name[MAX_PATH_LEN];
		rtrn = _Uxbuild_topLevelShell1();

		strcpy (path,get_pwd());
		XtVaSetValues (simulatorPathText,XmNvalue,path,NULL);
		strcpy (sim_name,read_sim_name(path));
		XtVaSetValues (simulatorNameText,XmNvalue,sim_name,NULL);
		if (strcmp(sim_name,"NO_FILE"))
		   XtVaSetValues (startupButton,XmNsensitive,True,NULL);
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

