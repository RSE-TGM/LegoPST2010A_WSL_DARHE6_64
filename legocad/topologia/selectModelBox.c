
/*******************************************************************************
	selectModelBox.c
	(Generated from interface file selectModelBox.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/TextF.h>
#include <Xm/Label.h>
#include <Xm/RowColumn.h>
#include <Xm/SelectioB.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME

/*
   modulo selectModelBox.i
   tipo 
   release 2.24
   data 3/30/95
   reserved @(#)selectModelBox.i	2.24
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#endif

#ifndef DESIGN_TIME
#include <stdlib.h>
#endif
#include "errore.h"
#include "lg1.h"
#include "question_type.h"
#include <sys/types.h>
#include <sys/stat.h>

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
	Widget	Uxuser_pathRC;
	Widget	Uxuser_pathLb;
} _UxCselectModelBox;

#define user_pathRC             UxSelectModelBoxContext->Uxuser_pathRC
#define user_pathLb             UxSelectModelBoxContext->Uxuser_pathLb

static _UxCselectModelBox	*UxSelectModelBoxContext;

Widget	selectModelBox;
Widget	user_pathTF;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_selectModelBox();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

selModelActivate()
{
     extern char      path_legocad[];
     extern ERR_LEVEL err_level;
     extern swidget   lg1MainWindow;

     UxPutText( user_pathTF, path_legocad );
     sel_model_fill(path_legocad);
     UxPopupInterface(selectModelBox, no_grab);
/*     set_win_cursors( "busy" );
*/

}






sel_model_fill(path)
char *path;
{

   Arg      arg[2];
   XmString *modelli;
   char     **str_modelli;
   int      num,i;
    
   extern swidget   selectModelBox;
   extern int       model_filter( char * );
   extern ERR_LEVEL err_level;



   genera_lista_entry(path, model_filter, &num, &str_modelli );

   if ( num )
   {
     modelli=(XmString *)malloc(num * sizeof(XmString));

     for(i=0;i<num;i++)
     {
	     printf("CMC in selectModelBox %s\n",str_modelli[i]);
       modelli[i]=XmStringCreateSimple(str_modelli[i]);
       free(str_modelli[i]);
     }
     free(str_modelli);

     XtSetArg(arg[0], XmNlistItems, modelli);
     XtSetArg(arg[1], XmNlistItemCount, num);
     XtSetValues(UxGetWidget(selectModelBox), arg, 2);

     for(i=0;i<num;i++)
       XtFree(modelli[i]);
   }
   else
   {
     XtSetArg(arg[0], XmNlistItems, NULL);
     XtSetArg(arg[1], XmNlistItemCount, 0);
     XtSetValues(UxGetWidget(selectModelBox), arg, 2);
   }


}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	unmapCB_selectModelBox( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCselectModelBox      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxSelectModelBoxContext;
	UxSelectModelBoxContext = UxContext =
			(_UxCselectModelBox *) UxGetContext( UxWidget );
	{
	
	}
	UxSelectModelBoxContext = UxSaveCtx;
}

static void	applyCB_selectModelBox( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCselectModelBox      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxSelectModelBoxContext;
	UxSelectModelBoxContext = UxContext =
			(_UxCselectModelBox *) UxGetContext( UxWidget );
	{
	extern char    path_legocad[];
	extern swidget user_pathTF; 
	
	char *path;
	
	
	path = UxGetText(user_pathTF);
	sel_model_fill(path);
	}
	UxSelectModelBoxContext = UxSaveCtx;
}

static void	cancelCB_selectModelBox( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCselectModelBox      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxSelectModelBoxContext;
	UxSelectModelBoxContext = UxContext =
			(_UxCselectModelBox *) UxGetContext( UxWidget );
	{
	extern swidget lg1MainWindow;
	
	/**
	reset_win_cursors ();
	**/
	UxPopdownInterface( UxWidget );
	
	}
	UxSelectModelBoxContext = UxSaveCtx;
}

static void	okCallback_selectModelBox( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCselectModelBox      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxSelectModelBoxContext;
	UxSelectModelBoxContext = UxContext =
			(_UxCselectModelBox *) UxGetContext( UxWidget );
	{
	extern MODELLO  modello;
	extern swidget user_pathTF;
	extern swidget lg1MainWindow;
	
	extern ERR_LEVEL err_level;
	extern char path_legocad[];
	extern char nome_modello[];
	
	extern QUESTION question;
	extern int      changes_in_F01;
	
	
	char appmod[150];
	char *p_nome, *path;
	char app[300];
	mode_t modo = (S_IRWXG | S_IRWXO | S_IRUSR | S_IWUSR | S_IXUSR);
	
	/**
	reset_win_cursors();
	**/
	
	p_nome = UxGetTextString(UxWidget);
	
	if ( !(*p_nome) )
	{
	   err_level = ERROR;
	   errore("No model selected");
	   UxPopdownInterface(UxWidget);
	   return;
	}
	
	strcpy( nome_modello, p_nome );
	
	
	path = UxGetText( user_pathTF );
	strcpy( path_legocad, path );
	
	if ( changes_in_F01 )
	{
	  question = QST_SALVA_MOD;
	  sprintf( app, "The model %s has been modified\nDo you want to save it?",modello.nome );
	 
	  questionDB_activate( app ); /* salva se risposta a question == OK */
	  
	}
	else
	{
	  strcpy(appmod,path);
	  strcat(appmod,"/");
	  strcat(appmod,nome_modello);
	  
	  printf("Richiesta apertura modello %s\n",appmod);
	/*
	  if(chdir(appmod) == -1)
	  {
	     printf("Cannot open model/n CREATE NEW ONE\n");
	     if(mkdir(appmod,modo) == -1)
	        printf("SORRY CANNOT CREATE NEW MODEL\n");
	     else
	        init_new_modello(nome_modello,path);
	  }  
	  else
	  {
	     init_modello(nome_modello, path);
	  }
	*/
	
	  init_modello(nome_modello, path);
	  set_bl_list();
	  set_model_name();
	}
	
	UxPopdownInterface(UxWidget);
	
	
	}
	UxSelectModelBoxContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_selectModelBox()
{
	Widget	selectModelBox_shell;

	selectModelBox_shell = XtVaCreatePopupShell( "selectModelBox_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 483,
			XmNy, 302,
			XmNwidth, 291,
			XmNheight, 426,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "selectModelBox",
			NULL );

	selectModelBox = XtVaCreateWidget( "selectModelBox",
			xmSelectionBoxWidgetClass, selectModelBox_shell,
			RES_CONVERT( XmNtextString, "" ),
			XmNautoUnmanage, FALSE,
			RES_CONVERT( XmNdialogTitle, "Model selection" ),
			RES_CONVERT( XmNapplyLabelString, "Filter" ),
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			RES_CONVERT( XmNselectionLabelString, "Selected Model" ),
			RES_CONVERT( XmNlistLabelString, "Models" ),
			XmNheight, 426,
			XmNwidth, 291,
			XmNunitType, XmPIXELS,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( selectModelBox, (char *) UxSelectModelBoxContext );

	user_pathRC = XtVaCreateManagedWidget( "user_pathRC",
			xmRowColumnWidgetClass, selectModelBox,
			XmNspacing, 0,
			XmNmarginWidth, 0,
			XmNheight, 40,
			XmNwidth, 205,
			XmNy, 114,
			XmNx, 24,
			NULL );

	UxPutContext( user_pathRC, (char *) UxSelectModelBoxContext );

	user_pathLb = XtVaCreateManagedWidget( "user_pathLb",
			xmLabelWidgetClass, user_pathRC,
			RES_CONVERT( XmNlabelString, "User path" ),
			XmNheight, 21,
			XmNwidth, 239,
			XmNy, 3,
			XmNx, 30,
			NULL );

	UxPutContext( user_pathLb, (char *) UxSelectModelBoxContext );

	user_pathTF = XtVaCreateManagedWidget( "user_pathTF",
			xmTextFieldWidgetClass, user_pathRC,
			XmNheight, 35,
			XmNwidth, 130,
			XmNy, 24,
			XmNx, 0,
			NULL );

	UxPutContext( user_pathTF, (char *) UxSelectModelBoxContext );

	XtAddCallback( selectModelBox, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxSelectModelBoxContext );

	XtAddCallback( selectModelBox, XmNunmapCallback,
			unmapCB_selectModelBox,
			(XtPointer) UxSelectModelBoxContext );
	XtAddCallback( selectModelBox, XmNapplyCallback,
			applyCB_selectModelBox,
			(XtPointer) UxSelectModelBoxContext );
	XtAddCallback( selectModelBox, XmNcancelCallback,
			cancelCB_selectModelBox,
			(XtPointer) UxSelectModelBoxContext );
	XtAddCallback( selectModelBox, XmNokCallback,
			okCallback_selectModelBox,
			(XtPointer) UxSelectModelBoxContext );



	return ( selectModelBox );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_selectModelBox()
{
	Widget                  rtrn;
	_UxCselectModelBox      *UxContext;

	UxSelectModelBoxContext = UxContext =
		(_UxCselectModelBox *) XtMalloc( sizeof(_UxCselectModelBox) );

	{
		Widget wid;
		
		extern char path_legocad[];
		extern swidget user_pathTF; 
		char *path;
		
		path = getenv("LEGOCAD_USER");
		
		if( path == NULL)
		{
		   printf("\nenviroment varable not found LEGOCAD_USER\n");
		   printf("\nset default path /usr/users/legoroot/esempi/utente\n");
		   strcpy(path_legocad,"/usr/users/legoroot/esempi/utente");
		}
		else
		{
		   strcpy(path_legocad,path);
		   strcat(path_legocad,"/legocad");
		}
		rtrn = _Uxbuild_selectModelBox();

		wid = XmSelectionBoxGetChild( UxGetWidget(rtrn), XmDIALOG_HELP_BUTTON );
		XtUnmanageChild( wid );
		
		return(rtrn);
	}
}

/*******************************************************************************
	The following is the 'Interface function' which is the
	external entry point for creating this interface.
	This function should be called from your application or from
	a callback function.
*******************************************************************************/

Widget	create_selectModelBox()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_selectModelBox();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

