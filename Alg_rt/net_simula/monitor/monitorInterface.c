
/*******************************************************************************
	monitorInterface.c

       Associated Header file: monitorInterface.h
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

#include "sim_param.h"
#include "sim_types.h"
#include "dispatcher.h"
#define MAX_PATH_LEN 200


/*******************************************************************************
       The following header file defines the context structure.
*******************************************************************************/

#define CONTEXT_MACRO_ACCESS 1
#include "monitorInterface.h"
#undef CONTEXT_MACRO_ACCESS

Widget	monitorInterface;

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_shutdownButton2(
			Widget wgt, 
			XtPointer cd, 
			XtPointer cb)
{
	_UxCmonitorInterface    *UxSaveCtx, *UxContext;
	Widget                  UxWidget = wgt;
	XtPointer               UxClientData = cd;
	XtPointer               UxCallbackArg = cb;

	UxSaveCtx = UxMonitorInterfaceContext;
	UxMonitorInterfaceContext = UxContext =
			(_UxCmonitorInterface *) UxGetContext( UxWidget );
	{
	system ("killsim");
	
	}
	UxMonitorInterfaceContext = UxSaveCtx;
}

static	void	activateCB_startupButton(
			Widget wgt, 
			XtPointer cd, 
			XtPointer cb)
{
	_UxCmonitorInterface    *UxSaveCtx, *UxContext;
	Widget                  UxWidget = wgt;
	XtPointer               UxClientData = cd;
	XtPointer               UxCallbackArg = cb;

	UxSaveCtx = UxMonitorInterfaceContext;
	UxMonitorInterfaceContext = UxContext =
			(_UxCmonitorInterface *) UxGetContext( UxWidget );
	{
	system ("newsim");
	XtVaSetValues (UxWidget,XmNsensitive,False,NULL);
	XtVaSetValues (monitorInterface,XmNiconic,True,NULL);
	
	}
	UxMonitorInterfaceContext = UxSaveCtx;
}

static	void	activateCB_masterMonitMenuQuitpb(
			Widget wgt, 
			XtPointer cd, 
			XtPointer cb)
{
	_UxCmonitorInterface    *UxSaveCtx, *UxContext;
	Widget                  UxWidget = wgt;
	XtPointer               UxClientData = cd;
	XtPointer               UxCallbackArg = cb;

	UxSaveCtx = UxMonitorInterfaceContext;
	UxMonitorInterfaceContext = UxContext =
			(_UxCmonitorInterface *) UxGetContext( UxWidget );
	{
	system ("killsim");
	exit (0);
	}
	UxMonitorInterfaceContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_monitorInterface()
{
	Widget		_UxParent;
	Widget		masterMonitMenu_shell;


	/* Creation of monitorInterface */
	_UxParent = UxWidgetToSwidget(UxTopLevel);
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	monitorInterface = XtVaCreatePopupShell( "monitorInterface",
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
	UxPutContext( monitorInterface, (char *) UxMonitorInterfaceContext );


	/* Creation of form1 */
	form1 = XtVaCreateManagedWidget( "form1",
			xmFormWidgetClass,
			monitorInterface,
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
	UxPutContext( form1, (char *) UxMonitorInterfaceContext );


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
	UxPutContext( form34, (char *) UxMonitorInterfaceContext );


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
		(XtPointer) UxMonitorInterfaceContext );

	UxPutContext( shutdownButton2, (char *) UxMonitorInterfaceContext );


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
		(XtPointer) UxMonitorInterfaceContext );

	UxPutContext( startupButton, (char *) UxMonitorInterfaceContext );


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
	UxPutContext( separator1, (char *) UxMonitorInterfaceContext );


	/* Creation of menu9 */
	menu9 = XtVaCreateManagedWidget( "menu9",
			xmRowColumnWidgetClass,
			form1,
			XmNrowColumnType, XmMENU_BAR,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightPosition, 0,
			XmNleftAttachment, XmATTACH_FORM,
			NULL );
	UxPutContext( menu9, (char *) UxMonitorInterfaceContext );


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
	UxPutContext( masterMonitMenu, (char *) UxMonitorInterfaceContext );


	/* Creation of masterMonitMenuQuitpb */
	masterMonitMenuQuitpb = XtVaCreateManagedWidget( "masterMonitMenuQuitpb",
			xmPushButtonWidgetClass,
			masterMonitMenu,
			RES_CONVERT( XmNlabelString, "Quit " ),
			NULL );
	XtAddCallback( masterMonitMenuQuitpb, XmNactivateCallback,
		(XtCallbackProc) activateCB_masterMonitMenuQuitpb,
		(XtPointer) UxMonitorInterfaceContext );

	UxPutContext( masterMonitMenuQuitpb, (char *) UxMonitorInterfaceContext );


	/* Creation of menu9_top_b1 */
	menu9_top_b1 = XtVaCreateManagedWidget( "menu9_top_b1",
			xmCascadeButtonWidgetClass,
			menu9,
			RES_CONVERT( XmNlabelString, "File" ),
			XmNsubMenuId, masterMonitMenu,
			NULL );
	UxPutContext( menu9_top_b1, (char *) UxMonitorInterfaceContext );


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
	UxPutContext( bulletinBoard1, (char *) UxMonitorInterfaceContext );


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
	UxPutContext( simulatorPathLabel, (char *) UxMonitorInterfaceContext );


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
	UxPutContext( simulatorPathText, (char *) UxMonitorInterfaceContext );


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
	UxPutContext( simulatorPathName, (char *) UxMonitorInterfaceContext );


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
	UxPutContext( simulatorNameText, (char *) UxMonitorInterfaceContext );

	XtVaSetValues(form1,
			XmNdefaultButton, startupButton,
			XmNinitialFocus, startupButton,
			NULL );

	XtVaSetValues(form34,
			XmNdefaultButton, startupButton,
			XmNinitialFocus, startupButton,
			NULL );


	XtAddCallback( monitorInterface, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxMonitorInterfaceContext);


	return ( monitorInterface );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_monitorInterface()
{
	Widget                  rtrn;
	_UxCmonitorInterface    *UxContext;

	UxMonitorInterfaceContext = UxContext =
		(_UxCmonitorInterface *) UxNewContext( sizeof(_UxCmonitorInterface), False );


	{
		char path[MAX_PATH_LEN];
		char sim_name[MAX_PATH_LEN];
		rtrn = _Uxbuild_monitorInterface();

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

