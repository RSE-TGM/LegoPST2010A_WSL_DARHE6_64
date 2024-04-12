
/*******************************************************************************
	formDialog1.c

*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/CascadeB.h>
#include <Xm/Separator.h>
#include <Xm/SeparatoG.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/Form.h>
#include <Xm/Form.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#include "sim_param.h"
#include "sim_types.h"
#include "dispatcher.h"

#ifndef NO_PARENT
#define NO_PARENT ((swidget)0)
#endif
extern swidget topLevelShell1;
extern int inizializzazione;
extern swidget sessionName;
extern swidget promptDialog1;
extern swidget create_sessionName();
extern int inizializzazione;
extern char titolo_sessione[100];

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
	Widget	Uxform2;
	Widget	Uxmaster_menu;
	Widget	Uxinit_menu_pb;
	Widget	Uxinit_ci_menu_pb;
	Widget	Uxinit_bt_menu_pb;
	Widget	Uxinit_clear_menu_pb;
	Widget	Uxmenu1_top_b6;
	Widget	Uxsnapshot_menu_pb;
	Widget	Uxsnapshot_snap_menu_pb;
	Widget	Uxmenu1_top_b7;
	Widget	Uxrecording_menu_pb;
	Widget	Uxrecording_bt_menu_pb;
	Widget	Uxrecording_cr_menu_pb;
	Widget	Uxrecording_ITAL_menu_pb;
	Widget	Uxrecording_perform_menu_pb;
	Widget	Uxrecording_sep1_menu;
	Widget	Uxrecording_archivio_menu_pb;
	Widget	Uxmenu1_top_b8;
	Widget	Uxmffr_menu_pb;
	Widget	Uxmffr_malf_menu_pb;
	Widget	Uxmffr_sep1_menu;
	Widget	Uxmffr_frem_menu_pb;
	Widget	Uxmenu2_top_b1;
	Widget	Uxarchivio_menu_pb;
	Widget	Uxarchivio_save_menu_pb;
	Widget	Uxarchivio_sep1_menu;
	Widget	Uxarchivio_edit_menu_pb;
	Widget	Uxmenu2_top_b3;
	Widget	Uxoption_menu_pb;
	Widget	Uxoption_save_menu_pb;
	Widget	Uxoption_edit;
	Widget	Uxoption_edit_init_pb;
	Widget	Uxoption_edit_snapshot_pb;
	Widget	Uxoption_edit_recording_menu;
	Widget	Uxoption_edit_mffr_pb;
	Widget	Uxoption_edit_archivio_pb;
	Widget	Uxoption_edit_show_pb;
	Widget	Uxoption_edit_menu_cb;
	Widget	Uxmenu2_top_b4;
	Widget	Uxshow_menu_pb;
	Widget	Uxshow_statistic_menu_pb;
	Widget	Uxshow_param_menu_pb;
	Widget	Uxmaster_menu_top_b1;
	Widget	Uxhelp_menu_pb;
	Widget	Uxhelp_1_menu_pb;
	Widget	UxpushButton8;
	Widget	UxpushButton7;
	Widget	UxmasterMenuRunpb;
} _UxCmasterMenu;

#define form2                   UxMasterMenuContext->Uxform2
#define master_menu             UxMasterMenuContext->Uxmaster_menu
#define init_menu_pb            UxMasterMenuContext->Uxinit_menu_pb
#define init_ci_menu_pb         UxMasterMenuContext->Uxinit_ci_menu_pb
#define init_bt_menu_pb         UxMasterMenuContext->Uxinit_bt_menu_pb
#define init_clear_menu_pb      UxMasterMenuContext->Uxinit_clear_menu_pb
#define menu1_top_b6            UxMasterMenuContext->Uxmenu1_top_b6
#define snapshot_menu_pb        UxMasterMenuContext->Uxsnapshot_menu_pb
#define snapshot_snap_menu_pb   UxMasterMenuContext->Uxsnapshot_snap_menu_pb
#define menu1_top_b7            UxMasterMenuContext->Uxmenu1_top_b7
#define recording_menu_pb       UxMasterMenuContext->Uxrecording_menu_pb
#define recording_bt_menu_pb    UxMasterMenuContext->Uxrecording_bt_menu_pb
#define recording_cr_menu_pb    UxMasterMenuContext->Uxrecording_cr_menu_pb
#define recording_ITAL_menu_pb  UxMasterMenuContext->Uxrecording_ITAL_menu_pb
#define recording_perform_menu_pb UxMasterMenuContext->Uxrecording_perform_menu_pb
#define recording_sep1_menu     UxMasterMenuContext->Uxrecording_sep1_menu
#define recording_archivio_menu_pb UxMasterMenuContext->Uxrecording_archivio_menu_pb
#define menu1_top_b8            UxMasterMenuContext->Uxmenu1_top_b8
#define mffr_menu_pb            UxMasterMenuContext->Uxmffr_menu_pb
#define mffr_malf_menu_pb       UxMasterMenuContext->Uxmffr_malf_menu_pb
#define mffr_sep1_menu          UxMasterMenuContext->Uxmffr_sep1_menu
#define mffr_frem_menu_pb       UxMasterMenuContext->Uxmffr_frem_menu_pb
#define menu2_top_b1            UxMasterMenuContext->Uxmenu2_top_b1
#define archivio_menu_pb        UxMasterMenuContext->Uxarchivio_menu_pb
#define archivio_save_menu_pb   UxMasterMenuContext->Uxarchivio_save_menu_pb
#define archivio_sep1_menu      UxMasterMenuContext->Uxarchivio_sep1_menu
#define archivio_edit_menu_pb   UxMasterMenuContext->Uxarchivio_edit_menu_pb
#define menu2_top_b3            UxMasterMenuContext->Uxmenu2_top_b3
#define option_menu_pb          UxMasterMenuContext->Uxoption_menu_pb
#define option_save_menu_pb     UxMasterMenuContext->Uxoption_save_menu_pb
#define option_edit             UxMasterMenuContext->Uxoption_edit
#define option_edit_init_pb     UxMasterMenuContext->Uxoption_edit_init_pb
#define option_edit_snapshot_pb UxMasterMenuContext->Uxoption_edit_snapshot_pb
#define option_edit_recording_menu UxMasterMenuContext->Uxoption_edit_recording_menu
#define option_edit_mffr_pb     UxMasterMenuContext->Uxoption_edit_mffr_pb
#define option_edit_archivio_pb UxMasterMenuContext->Uxoption_edit_archivio_pb
#define option_edit_show_pb     UxMasterMenuContext->Uxoption_edit_show_pb
#define option_edit_menu_cb     UxMasterMenuContext->Uxoption_edit_menu_cb
#define menu2_top_b4            UxMasterMenuContext->Uxmenu2_top_b4
#define show_menu_pb            UxMasterMenuContext->Uxshow_menu_pb
#define show_statistic_menu_pb  UxMasterMenuContext->Uxshow_statistic_menu_pb
#define show_param_menu_pb      UxMasterMenuContext->Uxshow_param_menu_pb
#define master_menu_top_b1      UxMasterMenuContext->Uxmaster_menu_top_b1
#define help_menu_pb            UxMasterMenuContext->Uxhelp_menu_pb
#define help_1_menu_pb          UxMasterMenuContext->Uxhelp_1_menu_pb
#define pushButton8             UxMasterMenuContext->UxpushButton8
#define pushButton7             UxMasterMenuContext->UxpushButton7
#define masterMenuRunpb         UxMasterMenuContext->UxmasterMenuRunpb

static _UxCmasterMenu	*UxMasterMenuContext;

Widget	masterMenu;
Widget	menu2_top_b5;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_masterMenu();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_init_ci_menu_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{
	printf ("init da ci **********\n");
	create_initSimulator (NO_PARENT, 0);
	}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_init_bt_menu_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{
	printf ("init da backtrack ********\n");
	create_initSimulator (NO_PARENT, 1);
	}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_init_clear_menu_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("richiesta clear\n"); }
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_snapshot_snap_menu_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{
	printf ("richiesta snapshot\n");
	create_initialCondition();
	}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_recording_bt_menu_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("registrazioni di backtrack\n");}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_recording_cr_menu_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("registrazioni CR\n");}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_recording_ITAL_menu_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("I&T al\n");}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_recording_perform_menu_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("perf. analisys\n");}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_mffr_malf_menu_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("richiesta malfunzioni\n");}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_mffr_frem_menu_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("richiesta Funzioni remote\n");}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_archivio_save_menu_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{
	printf ("save archivio\n");
	create_archiveSavereq();
	}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_archivio_edit_menu_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{
	printf ("editazione archivio\n");
	create_archiveEdit();
	}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_option_save_menu_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("save Options\n");}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_option_edit_init_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("edit init\n");}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_option_edit_snapshot_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("snapshot edit\n");}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_option_edit_recording_menu( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("edit recording\n");}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_option_edit_mffr_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("edit mffr\n");}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_option_edit_archivio_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("edit archivio\n");}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_option_edit_show_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("edit show\n");}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_show_statistic_menu_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("richiesta show statistiche\n");}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_show_param_menu_pb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{printf ("richiesta show parametri\n");}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_pushButton8( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{
	printf ("richiesta di STEP\n");
	}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_pushButton7( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{
	printf ("richiesta di FREEZE\n");
	}
	UxMasterMenuContext = UxSaveCtx;
}

static void	activateCB_masterMenuRunpb( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCmasterMenu          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxMasterMenuContext;
	UxMasterMenuContext = UxContext =
			(_UxCmasterMenu *) UxGetContext( UxWidget );
	{
	printf ("RICHIESTA DI RUN\n");
	
	if (inizializzazione)
	   {
	   create_sessionName(titolo_sessione);
	   printf ("titolo sessione = :%s:\n",titolo_sessione); 
	   inizializzazione = 0;
	   UxDestroyInterface (sessionName);
	   }
	if (SD_run(BANCO) > 0)
	   {
	   sprintf (stderr,"sistema in RUN\n");
	   }
	else
	   {
	   sprintf (stderr,"commutazione in RUN fallita\n");
	   }
	
	}
	UxMasterMenuContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_masterMenu()
{
	Widget	masterMenu_shell;
	Widget	init_menu_pb_shell;
	Widget	snapshot_menu_pb_shell;
	Widget	recording_menu_pb_shell;
	Widget	mffr_menu_pb_shell;
	Widget	archivio_menu_pb_shell;
	Widget	option_menu_pb_shell;
	Widget	option_edit_shell;
	Widget	show_menu_pb_shell;
	Widget	help_menu_pb_shell;

	masterMenu_shell = XtVaCreatePopupShell( "masterMenu_shell",
			xmDialogShellWidgetClass, topLevelShell1,
			XmNx, 274,
			XmNy, 452,
			XmNwidth, 835,
			XmNheight, 120,
			XmNallowShellResize, TRUE,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "masterMenu",
			NULL );

	masterMenu = XtVaCreateWidget( "masterMenu",
			xmFormWidgetClass, masterMenu_shell,
			RES_CONVERT( XmNbackground, "#7E88AB" ),
			XmNautoUnmanage, FALSE,
			XmNshadowThickness, 2,
			XmNrubberPositioning, TRUE,
			XmNbuttonFontList, UxConvertFontList( "courr10" ),
			XmNallowOverlap, FALSE,
			XmNtextFontList, UxConvertFontList( "courb08" ),
			XmNlabelFontList, UxConvertFontList( "courb08" ),
			RES_CONVERT( XmNdialogTitle, "MENU PRINCIPALE" ),
			XmNheight, 120,
			XmNwidth, 835,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( masterMenu, (char *) UxMasterMenuContext );

	form2 = XtVaCreateManagedWidget( "form2",
			xmFormWidgetClass, masterMenu,
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomPosition, 0,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNheight, 70,
			XmNwidth, 820,
			XmNy, 40,
			XmNx, 5,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form2, (char *) UxMasterMenuContext );

	master_menu = XtVaCreateManagedWidget( "master_menu",
			xmRowColumnWidgetClass, form2,
			XmNleftAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNx, 0,
			XmNy, 0,
			XmNorientation, XmHORIZONTAL,
			RES_CONVERT( XmNlabelString, "" ),
			XmNmenuAccelerator, "<KeyUp>F10",
			XmNrowColumnType, XmMENU_BAR,
			NULL );

	UxPutContext( master_menu, (char *) UxMasterMenuContext );

	init_menu_pb_shell = XtVaCreatePopupShell ("init_menu_pb_shell",
			xmMenuShellWidgetClass, master_menu,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	init_menu_pb = XtVaCreateWidget( "init_menu_pb",
			xmRowColumnWidgetClass, init_menu_pb_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( init_menu_pb, (char *) UxMasterMenuContext );

	init_ci_menu_pb = XtVaCreateManagedWidget( "init_ci_menu_pb",
			xmPushButtonWidgetClass, init_menu_pb,
			RES_CONVERT( XmNmnemonic, "I" ),
			RES_CONVERT( XmNlabelString, "from I.C." ),
			NULL );

	UxPutContext( init_ci_menu_pb, (char *) UxMasterMenuContext );

	init_bt_menu_pb = XtVaCreateManagedWidget( "init_bt_menu_pb",
			xmPushButtonWidgetClass, init_menu_pb,
			RES_CONVERT( XmNmnemonic, "B" ),
			RES_CONVERT( XmNlabelString, "from Backtrack" ),
			NULL );

	UxPutContext( init_bt_menu_pb, (char *) UxMasterMenuContext );

	init_clear_menu_pb = XtVaCreateManagedWidget( "init_clear_menu_pb",
			xmPushButtonWidgetClass, init_menu_pb,
			RES_CONVERT( XmNmnemonic, "C" ),
			RES_CONVERT( XmNlabelString, "Clear" ),
			NULL );

	UxPutContext( init_clear_menu_pb, (char *) UxMasterMenuContext );

	menu1_top_b6 = XtVaCreateManagedWidget( "menu1_top_b6",
			xmCascadeButtonWidgetClass, master_menu,
			XmNsubMenuId, init_menu_pb,
			RES_CONVERT( XmNmnemonic, "I" ),
			RES_CONVERT( XmNlabelString, "Init" ),
			NULL );

	UxPutContext( menu1_top_b6, (char *) UxMasterMenuContext );

	snapshot_menu_pb_shell = XtVaCreatePopupShell ("snapshot_menu_pb_shell",
			xmMenuShellWidgetClass, master_menu,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	snapshot_menu_pb = XtVaCreateWidget( "snapshot_menu_pb",
			xmRowColumnWidgetClass, snapshot_menu_pb_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( snapshot_menu_pb, (char *) UxMasterMenuContext );

	snapshot_snap_menu_pb = XtVaCreateManagedWidget( "snapshot_snap_menu_pb",
			xmPushButtonWidgetClass, snapshot_menu_pb,
			RES_CONVERT( XmNmnemonic, "S" ),
			RES_CONVERT( XmNlabelString, "Snapshot management" ),
			NULL );

	UxPutContext( snapshot_snap_menu_pb, (char *) UxMasterMenuContext );

	menu1_top_b7 = XtVaCreateManagedWidget( "menu1_top_b7",
			xmCascadeButtonWidgetClass, master_menu,
			XmNsubMenuId, snapshot_menu_pb,
			RES_CONVERT( XmNmnemonic, "S" ),
			RES_CONVERT( XmNlabelString, "Snapshot" ),
			NULL );

	UxPutContext( menu1_top_b7, (char *) UxMasterMenuContext );

	recording_menu_pb_shell = XtVaCreatePopupShell ("recording_menu_pb_shell",
			xmMenuShellWidgetClass, master_menu,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	recording_menu_pb = XtVaCreateWidget( "recording_menu_pb",
			xmRowColumnWidgetClass, recording_menu_pb_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( recording_menu_pb, (char *) UxMasterMenuContext );

	recording_bt_menu_pb = XtVaCreateManagedWidget( "recording_bt_menu_pb",
			xmPushButtonWidgetClass, recording_menu_pb,
			RES_CONVERT( XmNmnemonic, "B" ),
			RES_CONVERT( XmNlabelString, "Backtrack management" ),
			NULL );

	UxPutContext( recording_bt_menu_pb, (char *) UxMasterMenuContext );

	recording_cr_menu_pb = XtVaCreateManagedWidget( "recording_cr_menu_pb",
			xmPushButtonWidgetClass, recording_menu_pb,
			RES_CONVERT( XmNmnemonic, "C" ),
			RES_CONVERT( XmNlabelString, "Continuos recording" ),
			NULL );

	UxPutContext( recording_cr_menu_pb, (char *) UxMasterMenuContext );

	recording_ITAL_menu_pb = XtVaCreateManagedWidget( "recording_ITAL_menu_pb",
			xmPushButtonWidgetClass, recording_menu_pb,
			RES_CONVERT( XmNmnemonic, "I" ),
			RES_CONVERT( XmNlabelString, "Instructor & Trainee A.L." ),
			NULL );

	UxPutContext( recording_ITAL_menu_pb, (char *) UxMasterMenuContext );

	recording_perform_menu_pb = XtVaCreateManagedWidget( "recording_perform_menu_pb",
			xmPushButtonWidgetClass, recording_menu_pb,
			RES_CONVERT( XmNmnemonic, "P" ),
			RES_CONVERT( XmNlabelString, "Performance analisys" ),
			NULL );

	UxPutContext( recording_perform_menu_pb, (char *) UxMasterMenuContext );

	recording_sep1_menu = XtVaCreateManagedWidget( "recording_sep1_menu",
			xmSeparatorGadgetClass, recording_menu_pb,
			NULL );

	UxPutContext( recording_sep1_menu, (char *) UxMasterMenuContext );

	recording_archivio_menu_pb = XtVaCreateManagedWidget( "recording_archivio_menu_pb",
			xmPushButtonWidgetClass, recording_menu_pb,
			RES_CONVERT( XmNmnemonic, "A" ),
			RES_CONVERT( XmNlabelString, "Archivio" ),
			NULL );

	UxPutContext( recording_archivio_menu_pb, (char *) UxMasterMenuContext );

	menu1_top_b8 = XtVaCreateManagedWidget( "menu1_top_b8",
			xmCascadeButtonWidgetClass, master_menu,
			XmNsubMenuId, recording_menu_pb,
			RES_CONVERT( XmNmnemonic, "R" ),
			RES_CONVERT( XmNlabelString, "Recording" ),
			NULL );

	UxPutContext( menu1_top_b8, (char *) UxMasterMenuContext );

	mffr_menu_pb_shell = XtVaCreatePopupShell ("mffr_menu_pb_shell",
			xmMenuShellWidgetClass, master_menu,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	mffr_menu_pb = XtVaCreateWidget( "mffr_menu_pb",
			xmRowColumnWidgetClass, mffr_menu_pb_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( mffr_menu_pb, (char *) UxMasterMenuContext );

	mffr_malf_menu_pb = XtVaCreateManagedWidget( "mffr_malf_menu_pb",
			xmPushButtonWidgetClass, mffr_menu_pb,
			RES_CONVERT( XmNmnemonic, "M" ),
			RES_CONVERT( XmNlabelString, "Malfunzioni" ),
			NULL );

	UxPutContext( mffr_malf_menu_pb, (char *) UxMasterMenuContext );

	mffr_sep1_menu = XtVaCreateManagedWidget( "mffr_sep1_menu",
			xmSeparatorGadgetClass, mffr_menu_pb,
			NULL );

	UxPutContext( mffr_sep1_menu, (char *) UxMasterMenuContext );

	mffr_frem_menu_pb = XtVaCreateManagedWidget( "mffr_frem_menu_pb",
			xmPushButtonWidgetClass, mffr_menu_pb,
			RES_CONVERT( XmNmnemonic, "F" ),
			RES_CONVERT( XmNlabelString, "Funzioni remote" ),
			NULL );

	UxPutContext( mffr_frem_menu_pb, (char *) UxMasterMenuContext );

	menu2_top_b1 = XtVaCreateManagedWidget( "menu2_top_b1",
			xmCascadeButtonWidgetClass, master_menu,
			XmNsubMenuId, mffr_menu_pb,
			RES_CONVERT( XmNmnemonic, "M" ),
			RES_CONVERT( XmNlabelString, "MF/FR" ),
			NULL );

	UxPutContext( menu2_top_b1, (char *) UxMasterMenuContext );

	archivio_menu_pb_shell = XtVaCreatePopupShell ("archivio_menu_pb_shell",
			xmMenuShellWidgetClass, master_menu,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	archivio_menu_pb = XtVaCreateWidget( "archivio_menu_pb",
			xmRowColumnWidgetClass, archivio_menu_pb_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( archivio_menu_pb, (char *) UxMasterMenuContext );

	archivio_save_menu_pb = XtVaCreateManagedWidget( "archivio_save_menu_pb",
			xmPushButtonWidgetClass, archivio_menu_pb,
			RES_CONVERT( XmNmnemonic, "S" ),
			RES_CONVERT( XmNlabelString, "Save        " ),
			NULL );

	UxPutContext( archivio_save_menu_pb, (char *) UxMasterMenuContext );

	archivio_sep1_menu = XtVaCreateManagedWidget( "archivio_sep1_menu",
			xmSeparatorWidgetClass, archivio_menu_pb,
			NULL );

	UxPutContext( archivio_sep1_menu, (char *) UxMasterMenuContext );

	archivio_edit_menu_pb = XtVaCreateManagedWidget( "archivio_edit_menu_pb",
			xmPushButtonWidgetClass, archivio_menu_pb,
			RES_CONVERT( XmNmnemonic, "E" ),
			RES_CONVERT( XmNlabelString, "Edit         " ),
			NULL );

	UxPutContext( archivio_edit_menu_pb, (char *) UxMasterMenuContext );

	menu2_top_b3 = XtVaCreateManagedWidget( "menu2_top_b3",
			xmCascadeButtonWidgetClass, master_menu,
			XmNsubMenuId, archivio_menu_pb,
			RES_CONVERT( XmNmnemonic, "A" ),
			RES_CONVERT( XmNlabelString, "Archivio" ),
			NULL );

	UxPutContext( menu2_top_b3, (char *) UxMasterMenuContext );

	option_menu_pb_shell = XtVaCreatePopupShell ("option_menu_pb_shell",
			xmMenuShellWidgetClass, master_menu,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	option_menu_pb = XtVaCreateWidget( "option_menu_pb",
			xmRowColumnWidgetClass, option_menu_pb_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( option_menu_pb, (char *) UxMasterMenuContext );

	option_save_menu_pb = XtVaCreateManagedWidget( "option_save_menu_pb",
			xmPushButtonWidgetClass, option_menu_pb,
			RES_CONVERT( XmNmnemonic, "S" ),
			RES_CONVERT( XmNlabelString, "Save" ),
			NULL );

	UxPutContext( option_save_menu_pb, (char *) UxMasterMenuContext );

	option_edit_shell = XtVaCreatePopupShell ("option_edit_shell",
			xmMenuShellWidgetClass, option_menu_pb,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	option_edit = XtVaCreateWidget( "option_edit",
			xmRowColumnWidgetClass, option_edit_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( option_edit, (char *) UxMasterMenuContext );

	option_edit_init_pb = XtVaCreateManagedWidget( "option_edit_init_pb",
			xmPushButtonWidgetClass, option_edit,
			RES_CONVERT( XmNmnemonic, "I" ),
			RES_CONVERT( XmNlabelString, "Init" ),
			NULL );

	UxPutContext( option_edit_init_pb, (char *) UxMasterMenuContext );

	option_edit_snapshot_pb = XtVaCreateManagedWidget( "option_edit_snapshot_pb",
			xmPushButtonWidgetClass, option_edit,
			RES_CONVERT( XmNmnemonic, "S" ),
			RES_CONVERT( XmNlabelString, "Snapshot" ),
			NULL );

	UxPutContext( option_edit_snapshot_pb, (char *) UxMasterMenuContext );

	option_edit_recording_menu = XtVaCreateManagedWidget( "option_edit_recording_menu",
			xmPushButtonWidgetClass, option_edit,
			RES_CONVERT( XmNmnemonic, "R" ),
			RES_CONVERT( XmNlabelString, "Recording" ),
			NULL );

	UxPutContext( option_edit_recording_menu, (char *) UxMasterMenuContext );

	option_edit_mffr_pb = XtVaCreateManagedWidget( "option_edit_mffr_pb",
			xmPushButtonWidgetClass, option_edit,
			RES_CONVERT( XmNmnemonic, "M" ),
			RES_CONVERT( XmNlabelString, "Mf/fr" ),
			NULL );

	UxPutContext( option_edit_mffr_pb, (char *) UxMasterMenuContext );

	option_edit_archivio_pb = XtVaCreateManagedWidget( "option_edit_archivio_pb",
			xmPushButtonWidgetClass, option_edit,
			RES_CONVERT( XmNmnemonic, "A" ),
			RES_CONVERT( XmNlabelString, "Archivio" ),
			NULL );

	UxPutContext( option_edit_archivio_pb, (char *) UxMasterMenuContext );

	option_edit_show_pb = XtVaCreateManagedWidget( "option_edit_show_pb",
			xmPushButtonWidgetClass, option_edit,
			RES_CONVERT( XmNmnemonic, "S" ),
			RES_CONVERT( XmNlabelString, "Show" ),
			NULL );

	UxPutContext( option_edit_show_pb, (char *) UxMasterMenuContext );

	option_edit_menu_cb = XtVaCreateManagedWidget( "option_edit_menu_cb",
			xmCascadeButtonWidgetClass, option_menu_pb,
			XmNsubMenuId, option_edit,
			RES_CONVERT( XmNmnemonic, "E" ),
			RES_CONVERT( XmNlabelString, "Edit" ),
			NULL );

	UxPutContext( option_edit_menu_cb, (char *) UxMasterMenuContext );

	menu2_top_b4 = XtVaCreateManagedWidget( "menu2_top_b4",
			xmCascadeButtonWidgetClass, master_menu,
			XmNsubMenuId, option_menu_pb,
			RES_CONVERT( XmNmnemonic, "O" ),
			RES_CONVERT( XmNlabelString, "Options" ),
			NULL );

	UxPutContext( menu2_top_b4, (char *) UxMasterMenuContext );

	show_menu_pb_shell = XtVaCreatePopupShell ("show_menu_pb_shell",
			xmMenuShellWidgetClass, master_menu,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	show_menu_pb = XtVaCreateWidget( "show_menu_pb",
			xmRowColumnWidgetClass, show_menu_pb_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( show_menu_pb, (char *) UxMasterMenuContext );

	show_statistic_menu_pb = XtVaCreateManagedWidget( "show_statistic_menu_pb",
			xmPushButtonWidgetClass, show_menu_pb,
			RES_CONVERT( XmNmnemonic, "S" ),
			RES_CONVERT( XmNlabelString, "Statistic" ),
			NULL );

	UxPutContext( show_statistic_menu_pb, (char *) UxMasterMenuContext );

	show_param_menu_pb = XtVaCreateManagedWidget( "show_param_menu_pb",
			xmPushButtonWidgetClass, show_menu_pb,
			RES_CONVERT( XmNmnemonic, "P" ),
			RES_CONVERT( XmNlabelString, "Parameters" ),
			NULL );

	UxPutContext( show_param_menu_pb, (char *) UxMasterMenuContext );

	master_menu_top_b1 = XtVaCreateManagedWidget( "master_menu_top_b1",
			xmCascadeButtonWidgetClass, master_menu,
			XmNsubMenuId, show_menu_pb,
			RES_CONVERT( XmNmnemonic, "S" ),
			RES_CONVERT( XmNlabelString, "Show" ),
			NULL );

	UxPutContext( master_menu_top_b1, (char *) UxMasterMenuContext );

	help_menu_pb_shell = XtVaCreatePopupShell ("help_menu_pb_shell",
			xmMenuShellWidgetClass, master_menu,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	help_menu_pb = XtVaCreateWidget( "help_menu_pb",
			xmRowColumnWidgetClass, help_menu_pb_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( help_menu_pb, (char *) UxMasterMenuContext );

	help_1_menu_pb = XtVaCreateManagedWidget( "help_1_menu_pb",
			xmPushButtonWidgetClass, help_menu_pb,
			RES_CONVERT( XmNlabelString, "pushButton" ),
			NULL );

	UxPutContext( help_1_menu_pb, (char *) UxMasterMenuContext );

	menu2_top_b5 = XtVaCreateManagedWidget( "menu2_top_b5",
			xmCascadeButtonWidgetClass, master_menu,
			RES_CONVERT( XmNmnemonic, "H" ),
			XmNsensitive, TRUE,
			XmNalignment, XmALIGNMENT_CENTER,
			XmNsubMenuId, help_menu_pb,
			RES_CONVERT( XmNlabelString, "Help" ),
			NULL );

	UxPutContext( menu2_top_b5, (char *) UxMasterMenuContext );

	pushButton8 = XtVaCreateManagedWidget( "pushButton8",
			xmPushButtonWidgetClass, form2,
			XmNfontList, UxConvertFontList( "courb14" ),
			RES_CONVERT( XmNlabelString, "STEP" ),
			XmNheight, 40,
			XmNwidth, 140,
			XmNy, 60,
			XmNx, 390,
			NULL );

	UxPutContext( pushButton8, (char *) UxMasterMenuContext );

	pushButton7 = XtVaCreateManagedWidget( "pushButton7",
			xmPushButtonWidgetClass, form2,
			XmNfontList, UxConvertFontList( "courb14" ),
			RES_CONVERT( XmNlabelString, "FREEZE" ),
			XmNheight, 40,
			XmNwidth, 140,
			XmNy, 60,
			XmNx, 210,
			NULL );

	UxPutContext( pushButton7, (char *) UxMasterMenuContext );

	masterMenuRunpb = XtVaCreateManagedWidget( "masterMenuRunpb",
			xmPushButtonWidgetClass, form2,
			RES_CONVERT( XmNforeground, "black" ),
			XmNfontList, UxConvertFontList( "courb14" ),
			RES_CONVERT( XmNlabelString, "RUN" ),
			XmNheight, 40,
			XmNwidth, 140,
			XmNy, 60,
			XmNx, 30,
			NULL );

	UxPutContext( masterMenuRunpb, (char *) UxMasterMenuContext );

	XtAddCallback( masterMenu, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxMasterMenuContext );

	XtVaSetValues(master_menu,
			XmNmenuHelpWidget, help_menu_pb,
			NULL );

	XtAddCallback( init_ci_menu_pb, XmNactivateCallback,
			activateCB_init_ci_menu_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( init_bt_menu_pb, XmNactivateCallback,
			activateCB_init_bt_menu_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( init_clear_menu_pb, XmNactivateCallback,
			activateCB_init_clear_menu_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( snapshot_snap_menu_pb, XmNactivateCallback,
			activateCB_snapshot_snap_menu_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( recording_bt_menu_pb, XmNactivateCallback,
			activateCB_recording_bt_menu_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( recording_cr_menu_pb, XmNactivateCallback,
			activateCB_recording_cr_menu_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( recording_ITAL_menu_pb, XmNactivateCallback,
			activateCB_recording_ITAL_menu_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( recording_perform_menu_pb, XmNactivateCallback,
			activateCB_recording_perform_menu_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( mffr_malf_menu_pb, XmNactivateCallback,
			activateCB_mffr_malf_menu_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( mffr_frem_menu_pb, XmNactivateCallback,
			activateCB_mffr_frem_menu_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( archivio_save_menu_pb, XmNactivateCallback,
			activateCB_archivio_save_menu_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( archivio_edit_menu_pb, XmNactivateCallback,
			activateCB_archivio_edit_menu_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( option_save_menu_pb, XmNactivateCallback,
			activateCB_option_save_menu_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( option_edit_init_pb, XmNactivateCallback,
			activateCB_option_edit_init_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( option_edit_snapshot_pb, XmNactivateCallback,
			activateCB_option_edit_snapshot_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( option_edit_recording_menu, XmNactivateCallback,
			activateCB_option_edit_recording_menu,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( option_edit_mffr_pb, XmNactivateCallback,
			activateCB_option_edit_mffr_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( option_edit_archivio_pb, XmNactivateCallback,
			activateCB_option_edit_archivio_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( option_edit_show_pb, XmNactivateCallback,
			activateCB_option_edit_show_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( show_statistic_menu_pb, XmNactivateCallback,
			activateCB_show_statistic_menu_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( show_param_menu_pb, XmNactivateCallback,
			activateCB_show_param_menu_pb,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( pushButton8, XmNactivateCallback,
			activateCB_pushButton8,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( pushButton7, XmNactivateCallback,
			activateCB_pushButton7,
			(XtPointer) UxMasterMenuContext );

	XtAddCallback( masterMenuRunpb, XmNactivateCallback,
			activateCB_masterMenuRunpb,
			(XtPointer) UxMasterMenuContext );



	return ( masterMenu );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_masterMenu()
{
	Widget                  rtrn;
	_UxCmasterMenu          *UxContext;

	UxMasterMenuContext = UxContext =
		(_UxCmasterMenu *) XtMalloc( sizeof(_UxCmasterMenu) );

	{
		printf ("creazione master menu (menu principale)\n");
		rtrn = _Uxbuild_masterMenu();

		UxPopupInterface(masterMenu,no_grab);
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_masterMenu()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_masterMenu();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

