
/*******************************************************************************
	questionDB.c
	(Generated from interface file questionDB.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/MessageB.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

#ifndef DESIGN_TIME

/*
   modulo questionDB.i
   tipo 
   release 2.24
   data 3/30/95
   reserved @(#)questionDB.i	2.24
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#endif

#include "question_type.h"


QUESTION question;
extern int graphics_on;

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
	int	mumble;
} _UxCquestionDB;


static _UxCquestionDB	*UxQuestionDBContext;

Widget	questionDB;

/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_questionDB();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

questionDB_activate ( messaggio )
char *messaggio;
{

   extern swidget questionDB;
   extern swidget lg1MainWindow;

   
   switch ( question ) {

     case QST_USCITA:
     case QST_DEL_BL: 
                      break;
                    
     case QST_SALVA_MOD:
                      UxPutOkLabelString( questionDB, "Yes" );
                      UxPutCancelLabelString( questionDB, "No" );
                      break;
   }

   UxPutMessageString(questionDB,messaggio);
   UxPopupInterface(questionDB,no_grab);
/*
   set_win_cursors( "busy" );
*/
}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	unmapCB_questionDB( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCquestionDB          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxQuestionDBContext;
	UxQuestionDBContext = UxContext =
			(_UxCquestionDB *) UxGetContext( UxWidget );
	{
	extern char nome_modello[];
	extern char path_legocad[];
	extern int write_f01();
	
	/**
	reset_win_cursors ();
	**/
	                    
	printf("Unmap Callback questionDB\n");
	
	switch ( question ) {
	
	   case QST_USCITA:
	   case QST_DEL_BL: 
	                    printf("QST_USCITA oppure QST_DEL_BL\n");
	                    break;
	                    
	   case QST_SALVA_MOD: 
	                    printf("QST_SALVA_MOD\n");
	
	                    write_f01();
	                    printf("Inizializzo Il Modello %s\n",nome_modello);
	
	                    init_modello(nome_modello, path_legocad);
	                    printf("Set Bl_list\n");
	                    set_bl_list();
	
	                    set_model_name();
	
	                    printf("QST_SALVA_MOD ended /n");
	                    
	/*
	                    UxPutOkLabelString( UxThisWidget, "Ok" );
	                    UxPutCancelLabelString( UxThisWidget, "Cancel" );
	*/
	                    break;
	}
	
	
	}
	UxQuestionDBContext = UxSaveCtx;
}

static void	cancelCB_questionDB( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCquestionDB          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxQuestionDBContext;
	UxQuestionDBContext = UxContext =
			(_UxCquestionDB *) UxGetContext( UxWidget );
	{
	extern swidget lg1MainWindow;
	extern int     changes_in_F01;
	
	
	switch ( question ) {
	
	   case QST_USCITA: 
	   case QST_SALVA_MOD:
	   case QST_DEL_BL:
	                    break;
	}
	
	
	
	}
	UxQuestionDBContext = UxSaveCtx;
}

static void	okCallback_questionDB( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCquestionDB          *UxSaveCtx, *UxContext;

	UxSaveCtx = UxQuestionDBContext;
	UxQuestionDBContext = UxContext =
			(_UxCquestionDB *) UxGetContext( UxWidget );
	{
	extern swidget lg1MainWindow;
	extern int     changes_in_F01;
	extern int     write_f01();
	                  
	printf("Ok Callback questionDB\n");
	
	switch ( question ) {
	
	   case QST_USCITA: 
	                    printf(" USCITA\n");            
	                    exit(0);
	
	   case QST_DEL_BL:
	                    printf(" QST_DEL_BL\n");            
	                    bl_del_qst_cb();
	                    break;
	                    
	   case QST_DEL_CONN:
	                    printf(" QST_DEL_MOD\n");            
	                    del_conn_qst_cb();
	                    break;
	
	   case QST_SALVA_MOD:      
	                    printf(" QST_SALVA_MOD\n");            
	                    printf(" Su conferma scrivo il nuovo F01.dat \n");
	                    write_f01();
	                    if(graphics_on == True)
	                       Isalva_grafica();
	                    break;
	}
	
	
	
	}
	UxQuestionDBContext = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_questionDB()
{
	Widget	questionDB_shell;

	questionDB_shell = XtVaCreatePopupShell( "questionDB_shell",
			xmDialogShellWidgetClass, UxTopLevel,
			XmNx, 965,
			XmNy, 570,
			XmNwidth, 275,
			XmNheight, 190,
			XmNshellUnitType, XmPIXELS,
			XmNtitle, "questionDB",
			NULL );

	questionDB = XtVaCreateWidget( "questionDB",
			xmMessageBoxWidgetClass, questionDB_shell,
			XmNnoResize, TRUE,
			XmNminimizeButtons, FALSE,
			XmNdialogStyle, XmDIALOG_FULL_APPLICATION_MODAL,
			XmNheight, 190,
			XmNwidth, 275,
			XmNunitType, XmPIXELS,
			XmNdialogType, XmDIALOG_QUESTION,
			NULL );

	UxPutContext( questionDB, (char *) UxQuestionDBContext );

	XtAddCallback( questionDB, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxQuestionDBContext );

	XtAddCallback( questionDB, XmNunmapCallback,
			unmapCB_questionDB,
			(XtPointer) UxQuestionDBContext );
	XtAddCallback( questionDB, XmNcancelCallback,
			cancelCB_questionDB,
			(XtPointer) UxQuestionDBContext );
	XtAddCallback( questionDB, XmNokCallback,
			okCallback_questionDB,
			(XtPointer) UxQuestionDBContext );



	return ( questionDB );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_questionDB()
{
	Widget                  rtrn;
	_UxCquestionDB          *UxContext;

	UxQuestionDBContext = UxContext =
		(_UxCquestionDB *) XtMalloc( sizeof(_UxCquestionDB) );

	{
		Widget wid;
		rtrn = _Uxbuild_questionDB();

		wid = XmMessageBoxGetChild( UxGetWidget(rtrn), XmDIALOG_HELP_BUTTON );
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

Widget	create_questionDB()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_questionDB();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/

