
/*******************************************************************************
	TrainingModels.c
	(Generated from interface file TrainingModels.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/CascadeB.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/SelectioB.h>
#include <Xm/MainW.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo TrainingModels.i
   tipo 
   release 1.10
   data 5/12/95
   reserved @(#)TrainingModels.i	1.10
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif

#include <linfo.h>
#include <string.h>
#include <unistd.h>
#include "legomain.h"

char path_modello_training[200];
extern int model_filter(char *);

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
	Widget	UxTrainingModels;
	Widget	UxselectionBox1;
	Widget	Uxmenu2;
	Widget	UxFilePane;
	Widget	UxViewDescr;
	Widget	UxPrintDescr;
	Widget	UxCopyAll;
	Widget	Uxmenu2_top_b1;
} _UxCTrainingModels;

#define TrainingModels          UxTrainingModelsContext->UxTrainingModels
#define selectionBox1           UxTrainingModelsContext->UxselectionBox1
#define menu2                   UxTrainingModelsContext->Uxmenu2
#define FilePane                UxTrainingModelsContext->UxFilePane
#define ViewDescr               UxTrainingModelsContext->UxViewDescr
#define PrintDescr              UxTrainingModelsContext->UxPrintDescr
#define CopyAll                 UxTrainingModelsContext->UxCopyAll
#define menu2_top_b1            UxTrainingModelsContext->Uxmenu2_top_b1

static _UxCTrainingModels	*UxTrainingModelsContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_TrainingModels();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

get_selection(char *selezione)
{
  char appo[200];

  strcpy(appo,UxGetTextString( selectionBox1 ));
  if( strcmp(appo,"") )
     sprintf(selezione,"%s/%s",path_modello_training,appo);
  else
    strcpy(selezione,"");

  printf("selezione=%s",selezione);

}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	cancelCB_selectionBox1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCTrainingModels      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTrainingModelsContext;
	UxTrainingModelsContext = UxContext =
			(_UxCTrainingModels *) UxGetContext( UxWidget );
	{
	UxDestroyInterface(XtParent(UxWidget));
	}
	UxTrainingModelsContext = UxSaveCtx;
}

static void	activateCB_ViewDescr( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCTrainingModels      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTrainingModelsContext;
	UxTrainingModelsContext = UxContext =
			(_UxCTrainingModels *) UxGetContext( UxWidget );
	{
	char selezionato[200],comando[200],appo[200];
	FILE *fp;
	
	get_selection(selezionato);
	printf("selection made %s\n",selezionato);
	 
	if( !strcmp(selezionato,"") )
	{
	   create_vis_msg("Error on training model path");
	   return;
	}
	
	sprintf(appo,"%s/%s",selezionato,FNAME_DESCR);
	if( (fp =fopen(appo,"r")) == NULL)
	{
	   fclose(fp);
	   sprintf(appo,"%s not found",FNAME_DESCR);
	   create_vis_msg(appo);
	   return;
	}
	fclose(fp);
	
	sprintf(comando,"linfo %s 1 0",selezionato); 
	system(comando);
	}
	UxTrainingModelsContext = UxSaveCtx;
}

static void	activateCB_PrintDescr( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCTrainingModels      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTrainingModelsContext;
	UxTrainingModelsContext = UxContext =
			(_UxCTrainingModels *) UxGetContext( UxWidget );
	{
	extern int print_file();
	char selezionato[200],comando[200],appo[200];
	FILE *fp;
	
	get_selection(selezionato);
	printf("selection made %s\n",selezionato);
	 
	if( !strcmp(selezionato,"") )
	{
	   create_vis_msg("Error on training model path");
	   return;
	}
	
	sprintf(appo,"%s/%s",selezionato,FNAME_DESCR);
	if( (fp =fopen(appo,"r")) == NULL)
	{
	   fclose(fp);
	   sprintf(appo,"%s not found",FNAME_DESCR);
	   create_vis_msg(appo);
	   return;
	}
	fclose(fp);
	
	print_file(FNAME_DESCR);
	
	}
	UxTrainingModelsContext = UxSaveCtx;
}

static void	activateCB_CopyAll( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCTrainingModels      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTrainingModelsContext;
	UxTrainingModelsContext = UxContext =
			(_UxCTrainingModels *) UxGetContext( UxWidget );
	{
	extern int set_var_env();
	char selezionato[200],comando[200],dest[200];
	FILE *fp;
	
	get_selection(selezionato);
	printf("\n\nselection made %s\n",selezionato);
	 
	if( !strcmp(selezionato,"") )
	{
	   create_vis_msg("Error on training model path");
	   return;
	}
	
	sprintf(dest,"%s/legocad/%s",getenv("LEGOCAD_USER"),UxGetTextString(selectionBox1));
	
	printf("source = %s\n,dest = %s\n",selezionato,dest);
	
	set_var_env("DIR_SOURCE_MODEL",selezionato);
	set_var_env("DIR_DEST_MODEL",dest);
	
	if( access(dest,F_OK) != 0)
	{
	   printf("modello non esistente, --- lo creo ---\n");
	   sprintf(comando,"mkdir %s",dest);   
	   system(comando);   
	
	   system(COPY_MODELLO);
	
	}
	else
	{
	   printf("modello esistente\n");
	   printf("Q_OVERWRITE_COPY_MODEL = [%d]\n",Q_OVERWRITE_COPY_MODEL); 
	   create_question_operation(selectionBox1, Q_OVERWRITE_COPY_MODEL );
	}  
	
	
	
	}
	UxTrainingModelsContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_TrainingModels()
{
	Widget	TrainingModels_shell;
	Widget	FilePane_shell;

	TrainingModels_shell = XtVaCreatePopupShell( "TrainingModels_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 540,
			XmNy, 160,
			XmNwidth, 430,
			XmNheight, 420,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "TrainingModels",
			XmNiconName, "TrainingModels",
			NULL );

	TrainingModels = XtVaCreateManagedWidget( "TrainingModels",
			xmMainWindowWidgetClass, TrainingModels_shell,
			XmNheight, 420,
			XmNwidth, 430,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( TrainingModels, (char *) UxTrainingModelsContext );

	selectionBox1 = XtVaCreateManagedWidget( "selectionBox1",
			xmSelectionBoxWidgetClass, TrainingModels,
			NULL );

	UxPutContext( selectionBox1, (char *) UxTrainingModelsContext );

	menu2 = XtVaCreateManagedWidget( "menu2",
			xmRowColumnWidgetClass, TrainingModels,
			XmNmenuAccelerator, "<KeyUp>F10",
			XmNrowColumnType, XmMENU_BAR,
			NULL );

	UxPutContext( menu2, (char *) UxTrainingModelsContext );

	FilePane_shell = XtVaCreatePopupShell ("FilePane_shell",
			xmMenuShellWidgetClass, menu2,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	FilePane = XtVaCreateWidget( "FilePane",
			xmRowColumnWidgetClass, FilePane_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( FilePane, (char *) UxTrainingModelsContext );

	ViewDescr = XtVaCreateManagedWidget( "ViewDescr",
			xmPushButtonWidgetClass, FilePane,
			RES_CONVERT( XmNlabelString, "View description" ),
			NULL );

	UxPutContext( ViewDescr, (char *) UxTrainingModelsContext );

	PrintDescr = XtVaCreateManagedWidget( "PrintDescr",
			xmPushButtonWidgetClass, FilePane,
			RES_CONVERT( XmNlabelString, "Print Description" ),
			NULL );

	UxPutContext( PrintDescr, (char *) UxTrainingModelsContext );

	CopyAll = XtVaCreateManagedWidget( "CopyAll",
			xmPushButtonWidgetClass, FilePane,
			RES_CONVERT( XmNlabelString, "Copy Training Examples" ),
			NULL );

	UxPutContext( CopyAll, (char *) UxTrainingModelsContext );

	menu2_top_b1 = XtVaCreateManagedWidget( "menu2_top_b1",
			xmCascadeButtonWidgetClass, menu2,
			XmNsubMenuId, FilePane,
			RES_CONVERT( XmNlabelString, "File" ),
			NULL );

	UxPutContext( menu2_top_b1, (char *) UxTrainingModelsContext );

	XtAddCallback( TrainingModels, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxTrainingModelsContext );

	XtAddCallback( selectionBox1, XmNcancelCallback,
			cancelCB_selectionBox1,
			(XtPointer) UxTrainingModelsContext );

	XtAddCallback( ViewDescr, XmNactivateCallback,
			activateCB_ViewDescr,
			(XtPointer) UxTrainingModelsContext );

	XtAddCallback( PrintDescr, XmNactivateCallback,
			activateCB_PrintDescr,
			(XtPointer) UxTrainingModelsContext );

	XtAddCallback( CopyAll, XmNactivateCallback,
			activateCB_CopyAll,
			(XtPointer) UxTrainingModelsContext );


	XmMainWindowSetAreas( TrainingModels, menu2, (Widget) NULL,
			(Widget) NULL, (Widget) NULL, selectionBox1 );

	return ( TrainingModels );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_TrainingModels()
{
	Widget                  rtrn;
	_UxCTrainingModels      *UxContext;

	UxTrainingModelsContext = UxContext =
		(_UxCTrainingModels *) XtMalloc( sizeof(_UxCTrainingModels) );

	{
		Widget wid;
		Arg arg[2];
		XmString *modelli;
		char **str_modelli;
		int num,i;
		
		strcpy(path_modello_training,getenv("LEGO"));
		strcat(path_modello_training,"/training");
		rtrn = _Uxbuild_TrainingModels();

		printf("path_modello_training=[%s]\n",path_modello_training);
		
		genera_lista_entry(path_modello_training, model_filter, &num, &str_modelli );
		
		modelli=(XmString *)malloc(num * sizeof(XmString));
		for(i=0;i<num;i++)
			{
			modelli[i]=XmStringCreateSimple(str_modelli[i]);
			free(str_modelli[i]);
			}
		free(str_modelli);
		XtSetArg(arg[0], XmNlistItems, modelli);
		XtSetArg(arg[1], XmNlistItemCount, num);
		XtSetValues( selectionBox1 , arg, 2);
		for(i=0;i<num;i++)
			{
			XtFree(modelli[i]);
			}
		
		
		UxPopupInterface(rtrn, no_grab);
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_TrainingModels()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_TrainingModels();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

