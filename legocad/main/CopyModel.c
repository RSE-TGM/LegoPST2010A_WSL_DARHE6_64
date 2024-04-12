
/*******************************************************************************
	CopyModel.c
	(Generated from interface file CopyModel.i)
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <Xm/Xm.h>
#include <X11/Shell.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/SelectioB.h>
#include <Xm/PushB.h>
#include <Xm/FileSB.h>
#include <Xm/Label.h>
#include <Xm/Form.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME
/*
   modulo CopyModel.i
   tipo 
   release 1.10
   data 5/12/95
   reserved @(#)CopyModel.i	1.10
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
#endif

#if defined LINUX
#include <unistd.h>
#else
#include <sys/access.h>
#endif

#include "legomain.h"
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
	Widget	UxCopyModel;
	Widget	Uxlabel6;
	Widget	Uxlabel7;
	Widget	UxfileSelectionBox1;
	Widget	UxpushButton1;
	Widget	UxpushButton2;
	Widget	UxselectionBox2;
} _UxCCopyModel;

#define CopyModel               UxCopyModelContext->UxCopyModel
#define label6                  UxCopyModelContext->Uxlabel6
#define label7                  UxCopyModelContext->Uxlabel7
#define fileSelectionBox1       UxCopyModelContext->UxfileSelectionBox1
#define pushButton1             UxCopyModelContext->UxpushButton1
#define pushButton2             UxCopyModelContext->UxpushButton2
#define selectionBox2           UxCopyModelContext->UxselectionBox2

static _UxCCopyModel	*UxCopyModelContext;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_CopyModel();

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_pushButton1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCCopyModel           *UxSaveCtx, *UxContext;

	UxSaveCtx = UxCopyModelContext;
	UxCopyModelContext = UxContext =
			(_UxCCopyModel *) UxGetContext( UxWidget );
	{
	extern swidget create_question_operation();
	extern swidget create_vis_msg();
	extern char path_modello[];
	extern int set_var_env();
	char source[400],destination[400],filef01[410];
	char mesg[200],modelname[100],appo[200];
	char *cptr,comando[200];
	FILE *fp;
	char *getenv();
	
	/* recupero la selezione effettuata SOURCE */
	strcpy(source, UxGetTextString(fileSelectionBox1) );
	printf("source model directory = [%s]\n",source);
	if( strcmp(source,"") == 0)
	{
	   create_vis_msg("Invalid Selection");
	   return;
	}
	
	/* recupero il nome del modello */
	cptr = strrchr(source,'/');
	cptr++;
	strcpy(modelname,cptr);
	printf("model name = [%s]\n",modelname);
	if( strcmp(modelname,"") == 0 )
	{
	   create_vis_msg("Invalid Selection");
	   return;
	} 
	
	/* verifico che esista nella source directory almeno l'f01.dat */ 
	
	sprintf(filef01,"%s/%s",source,"f01.dat");
	if( (fp = fopen(filef01,"r")) == NULL)
	{
	   fclose(fp);
	   sprintf(mesg,"%s not found in source model directory [%s]","f01.dat",source);
	   create_vis_msg(mesg);
	   return;
	}
	fclose(fp);
	
	/* recupero la selezione effettuata DEST */
	strcpy(destination,getenv("LEGOCAD_USER"));
	strcat(destination,"/legocad/");
	strcat(destination, UxGetTextString(selectionBox2) );
	
	printf("destination model directory = [%s]\n",destination);
	if( strcmp(destination,"") == 0)
	{
	   create_vis_msg("Invalid Selection");
	   return;
	}
	
	/* non si puo copiare un modello su se stesso */
	if( strcmp(source,destination) == 0 )
	{
	   create_vis_msg("Invalid Selection\nsource and destinationa are the same");
	   return;
	} 
	
	/* se la directory destinazione non esiste la creo
	   altrimenti richiedo conferma per la overwrite
	*/
	/*
	set_var_env(source,destination);
	*/
	
	set_var_env("DIR_SOURCE_MODEL",source);
	set_var_env("DIR_DEST_MODEL",destination);
	
	if( access(destination,F_OK) != 0)
	{
	   printf("modello non esistente, --- lo creo ---\n");
	   sprintf(comando,"mkdir %s",destination);   
	   system(comando);   
	
	   system(COPY_MODELLO);
	
	}
	else
	{
	   printf("modello esistente\n");
	   printf("Q_OVERWRITE_COPY_MODEL = [%d]\n",Q_OVERWRITE_COPY_MODEL); 
	   create_question_operation( fileSelectionBox1,Q_OVERWRITE_COPY_MODEL );
	}  
	
	
	
	}
	UxCopyModelContext = UxSaveCtx;
}

static void	activateCB_pushButton2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCCopyModel           *UxSaveCtx, *UxContext;

	UxSaveCtx = UxCopyModelContext;
	UxCopyModelContext = UxContext =
			(_UxCCopyModel *) UxGetContext( UxWidget );
	{
	UxDestroyInterface(XtParent(UxWidget));
	}
	UxCopyModelContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_CopyModel()
{
	Widget	CopyModel_shell;

	CopyModel_shell = XtVaCreatePopupShell( "CopyModel_shell",
			topLevelShellWidgetClass, UxTopLevel,
			XmNx, 350,
			XmNy, 319,
			XmNwidth, 700,
			XmNheight, 440,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "CopyModel",
			XmNiconName, "CopyModel",
			NULL );

	CopyModel = XtVaCreateManagedWidget( "CopyModel",
			xmFormWidgetClass, CopyModel_shell,
			XmNheight, 440,
			XmNwidth, 700,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( CopyModel, (char *) UxCopyModelContext );

	label6 = XtVaCreateManagedWidget( "label6",
			xmLabelWidgetClass, CopyModel,
			RES_CONVERT( XmNlabelString, "SOURCE MODEL SELECTION" ),
			XmNheight, 50,
			XmNwidth, 330,
			XmNy, 10,
			XmNx, 0,
			NULL );

	UxPutContext( label6, (char *) UxCopyModelContext );

	label7 = XtVaCreateManagedWidget( "label7",
			xmLabelWidgetClass, CopyModel,
			RES_CONVERT( XmNlabelString, "DESTINATION MODEL SELECTION" ),
			XmNheight, 50,
			XmNwidth, 340,
			XmNy, 10,
			XmNx, 360,
			NULL );

	UxPutContext( label7, (char *) UxCopyModelContext );

	fileSelectionBox1 = XtVaCreateManagedWidget( "fileSelectionBox1",
			xmFileSelectionBoxWidgetClass, CopyModel,
			RES_CONVERT( XmNfileListLabelString, "Models" ),
			RES_CONVERT( XmNdirListLabelString, "Base Directory" ),
			XmNfileTypeMask, XmFILE_DIRECTORY,
			XmNheight, 270,
			XmNwidth, 330,
			XmNy, 70,
			XmNx, 10,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( fileSelectionBox1, (char *) UxCopyModelContext );

	pushButton1 = XtVaCreateManagedWidget( "pushButton1",
			xmPushButtonWidgetClass, CopyModel,
			RES_CONVERT( XmNlabelString, "Ok" ),
			XmNheight, 30,
			XmNwidth, 230,
			XmNy, 390,
			XmNx, 50,
			NULL );

	UxPutContext( pushButton1, (char *) UxCopyModelContext );

	pushButton2 = XtVaCreateManagedWidget( "pushButton2",
			xmPushButtonWidgetClass, CopyModel,
			RES_CONVERT( XmNlabelString, "Cancel" ),
			XmNheight, 30,
			XmNwidth, 230,
			XmNy, 390,
			XmNx, 390,
			NULL );

	UxPutContext( pushButton2, (char *) UxCopyModelContext );

	selectionBox2 = XtVaCreateManagedWidget( "selectionBox2",
			xmSelectionBoxWidgetClass, CopyModel,
			RES_CONVERT( XmNlistLabelString, "Models" ),
			XmNheight, 220,
			XmNwidth, 330,
			XmNy, 70,
			XmNx, 360,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( selectionBox2, (char *) UxCopyModelContext );

	XtAddCallback( CopyModel, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxCopyModelContext );

	XtAddCallback( pushButton1, XmNactivateCallback,
			activateCB_pushButton1,
			(XtPointer) UxCopyModelContext );

	XtAddCallback( pushButton2, XmNactivateCallback,
			activateCB_pushButton2,
			(XtPointer) UxCopyModelContext );



	return ( CopyModel );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_CopyModel()
{
	Widget                  rtrn;
	_UxCCopyModel           *UxContext;

	UxCopyModelContext = UxContext =
		(_UxCCopyModel *) XtMalloc( sizeof(_UxCCopyModel) );

	{
		char path_modello_dst[200];
		swidget sw;
		Widget wid;
		Arg arg[2];
		XmString *modelli;
		char **str_modelli;
		int num,i;
		rtrn = _Uxbuild_CopyModel();

		/* unmanage dei bottoni delle file selection box */
		sw = XmFileSelectionBoxGetChild(fileSelectionBox1,XmDIALOG_OK_BUTTON);
		XtUnmanageChild( sw );
		sw = XmFileSelectionBoxGetChild(fileSelectionBox1,XmDIALOG_CANCEL_BUTTON);
		XtUnmanageChild( sw );
		sw = XmFileSelectionBoxGetChild(fileSelectionBox1,XmDIALOG_HELP_BUTTON);
		XtUnmanageChild( sw );
		sw = XmFileSelectionBoxGetChild(fileSelectionBox1,XmDIALOG_SEPARATOR);
		XtUnmanageChild( sw );
		sw = XmFileSelectionBoxGetChild(fileSelectionBox1,XmDIALOG_FILTER_LABEL);
		XtUnmanageChild( sw );
		sw = XmFileSelectionBoxGetChild(fileSelectionBox1,XmDIALOG_FILTER_TEXT);
		XtUnmanageChild( sw );
		/**
		sw = XmFileSelectionBoxGetChild(fileSelectionBox1,XmDIALOG_APPLY_BUTTON);
		XtUnmanageChild( sw );
		**/
		sw = XmFileSelectionBoxGetChild(selectionBox2,XmDIALOG_OK_BUTTON);
		XtUnmanageChild( sw );
		sw = XmFileSelectionBoxGetChild(selectionBox2,XmDIALOG_CANCEL_BUTTON);
		XtUnmanageChild( sw );
		sw = XmFileSelectionBoxGetChild(selectionBox2,XmDIALOG_HELP_BUTTON);
		XtUnmanageChild( sw );
		sw = XmFileSelectionBoxGetChild(selectionBox2,XmDIALOG_SEPARATOR);
		XtUnmanageChild( sw );
		
		strcpy(path_modello_dst,getenv("LEGOCAD_USER"));
		strcat(path_modello_dst,"/legocad");
		printf("path_modello_dst=[%s]\n",path_modello_dst);
		
		genera_lista_entry(path_modello_dst, model_filter, &num, &str_modelli );
		
		modelli=(XmString *)malloc(num * sizeof(XmString));
		for(i=0;i<num;i++)
			{
			modelli[i]=XmStringCreateSimple(str_modelli[i]);
			free(str_modelli[i]);
			}
		free(str_modelli);
		XtSetArg(arg[0], XmNlistItems, modelli);
		XtSetArg(arg[1], XmNlistItemCount, num);
		XtSetValues( selectionBox2 , arg, 2);
		for(i=0;i<num;i++)
			{
			XmStringFree(modelli[i]);
			}
		
		
		
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_CopyModel()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_CopyModel();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

