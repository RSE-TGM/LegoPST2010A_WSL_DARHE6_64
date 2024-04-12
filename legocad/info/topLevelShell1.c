
/*******************************************************************************
	topLevelShell1.c
	(Generated from interface file topLevelShell1.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/CascadeB.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/List.h>
#include <Xm/ScrolledW.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/PanedW.h>
#include <Xm/MainW.h>
#include <X11/Shell.h>

/*******************************************************************************
	Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
   modulo topLevelShell1.i
   tipo 
   release 1.12
   data 5/4/95
   reserved @(#)topLevelShell1.i	1.12
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <sys/stat.h>
#include <Xm/TextF.h>
#include "linfo.h"

#if defined LINUX
#define TRUE 1
#define FALSE 0
#endif

extern int whatConfiguration;
extern Boolean editabile;

Arg arg[20];
Cardinal narg;

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
	Widget	UxtopLevelShell1;
	Widget	UxmainWindow1;
	Widget	UxpanedWindow1;
	Widget	Uxform1;
	Widget	Uxlabel1;
	Widget	Uxform2;
	Widget	Uxlabel2;
	Widget	UxscrolledWindow1;
	Widget	UxscrolledList2;
	Widget	Uxform3;
	Widget	Uxlabel3;
	Widget	Uxmenu1;
	Widget	UxFile;
	Widget	UxFileSave;
	Widget	UxFileQuit;
	Widget	Uxmenu1_top_b1;
	DESCRMODELLO	Uxdescrmod;
	LTM	*Uxltm;
	FORAUS	Uxdforaus;
	int	Uxnrighedescr;
	int	Uxnmoduli;
	WidgetList	UxLWidDescr;
	Cardinal	UxnLWidDescr;
	Widget	Uxtesto_descr;
} _UxCtopLevelShell1;

#define topLevelShell1          UxTopLevelShell1Context->UxtopLevelShell1
#define mainWindow1             UxTopLevelShell1Context->UxmainWindow1
#define panedWindow1            UxTopLevelShell1Context->UxpanedWindow1
#define form1                   UxTopLevelShell1Context->Uxform1
#define label1                  UxTopLevelShell1Context->Uxlabel1
#define form2                   UxTopLevelShell1Context->Uxform2
#define label2                  UxTopLevelShell1Context->Uxlabel2
#define scrolledWindow1         UxTopLevelShell1Context->UxscrolledWindow1
#define scrolledList2           UxTopLevelShell1Context->UxscrolledList2
#define form3                   UxTopLevelShell1Context->Uxform3
#define label3                  UxTopLevelShell1Context->Uxlabel3
#define menu1                   UxTopLevelShell1Context->Uxmenu1
#define File                    UxTopLevelShell1Context->UxFile
#define FileSave                UxTopLevelShell1Context->UxFileSave
#define FileQuit                UxTopLevelShell1Context->UxFileQuit
#define menu1_top_b1            UxTopLevelShell1Context->Uxmenu1_top_b1
#define descrmod                UxTopLevelShell1Context->Uxdescrmod
#define ltm                     UxTopLevelShell1Context->Uxltm
#define dforaus                 UxTopLevelShell1Context->Uxdforaus
#define nrighedescr             UxTopLevelShell1Context->Uxnrighedescr
#define nmoduli                 UxTopLevelShell1Context->Uxnmoduli
#define LWidDescr               UxTopLevelShell1Context->UxLWidDescr
#define nLWidDescr              UxTopLevelShell1Context->UxnLWidDescr
#define testo_descr             UxTopLevelShell1Context->Uxtesto_descr

static _UxCtopLevelShell1	*UxTopLevelShell1Context;


/*******************************************************************************
	Forward declarations of functions that are defined later in this file.
*******************************************************************************/

Widget	create_topLevelShell1();

/*******************************************************************************
	Auxiliary code from the Declarations Editor:
*******************************************************************************/

save_descr()
{
   FILE *fp;

   AllocaDescrmodello(&descrmod,strlen( XmTextGetString(testo_descr) ) );
   strcpy(descrmod.descrizione,XmTextGetString (testo_descr) );
   printf("Salvo la descrizione \n\n %s\n\n",descrmod.descrizione);

   if( (fp = fopen(FNAME_DESCR,"w")) != NULL)
      fprintf(fp,"%s",descrmod.descrizione);

   fclose(fp); 

}

void DisplayDescriz()
{
   char *stringa=NULL;

   if( FileExist( FNAME_DESCR) == False)
      return;
      
   read_file(FNAME_DESCR,&stringa);
   if( stringa != NULL) 
   {
      AllocaDescrmodello(&descrmod,strlen(stringa));
      strcpy( descrmod.descrizione, stringa );
      XtFree( stringa );
   }


/* Creazione del Text widget  */
   narg=0;

/*
   XtSetArg(arg[narg],XmNrightAttachment,XmATTACH_FORM); narg++;
*/
   XtSetArg(arg[narg],XmNtopAttachment,XmATTACH_FORM); narg++;
   XtSetArg(arg[narg],XmNleftAttachment,XmATTACH_FORM); narg++;
   XtSetArg(arg[narg],XmNbottomAttachment,XmATTACH_FORM); narg++;
   XtSetArg(arg[narg],XmNbottomOffset,5); narg++;
   XtSetArg(arg[narg],XmNrightOffset,5); narg++;
   XtSetArg(arg[narg],XmNleftOffset,5); narg++;
   XtSetArg(arg[narg],XmNtopOffset,50); narg++;
   XtSetArg(arg[narg],XmNcolumns,70); narg++;
   XtSetArg(arg[narg],XmNmaxLength,400); narg++;

   XtSetArg(arg[narg],XmNrows,60); narg++;
   if( editabile == True )
   { 
      XtSetArg(arg[narg],XmNeditable,True); narg++;
   }
   else
   { 
      XtSetArg(arg[narg],XmNeditable,False); narg++;
   } 

   XtSetArg(arg[narg],XmNeditMode,XmMULTI_LINE_EDIT); narg++;
   XtSetArg(arg[narg],XmNscrollingPolicy,XmAUTOMATIC); narg++;
   XtSetArg(arg[narg],XmNvisualPolicy,XmCONSTANT); narg++;   

   XtSetArg(arg[narg],XmNscrollHorizontal,False); narg++;       
   XtSetArg(arg[narg],XmNwordWrap,True); narg++;      
   XtSetArg(arg[narg],XmNmarginWidth,10); narg++;       

   testo_descr=XmCreateScrolledText(form1,"testo_descr",arg,narg);
   XtManageChild (testo_descr);

   XmTextSetString (testo_descr,descrmod.descrizione);

}

void DisplayListaMod()
{
   extern char pathmodel[];
   XmString item;
   Widget Lista;
   int i,position = 0;
   char cstring[L_NOMEMODULO+L_DESCRMODELLO+2];

   Lista = scrolledList2; 


   if( ReadCrealtm(pathmodel,&ltm,&nmoduli) == FALSE)
      return;

   for(i=0;i<nmoduli;i++)
   {
      if(ltm[i].rout_std)
         sprintf(cstring,"%s *  %s",ltm[i].nome_modulo, ltm[i].descr_modulo);
      else
         sprintf(cstring,"%s    %s",ltm[i].nome_modulo, ltm[i].descr_modulo);
      item = XmStringCreateSimple(cstring);
      XmListAddItem(Lista,item,position);
   }
}


void DisplayForaus()
{
   extern char pathmodel[];
   char filename[256];
   Widget testo;
   char *stringa = NULL;

   strcpy(filename,pathmodel);
   strcat(filename,"/"); 
   strcat(filename,FNAME_FORAUS_USER);
 
   if( FileExist( filename ) == False)
      return;

/* legge il file foraus.for e 
   lo bufferrizza nella stringa 
   che viene allocata dalla routine 
   di lettura del file
*/
   

   read_file(filename,&stringa);
   AllocaForaus(&dforaus,strlen(stringa));

   strcpy( dforaus.foraus, stringa );

/* Dealloca la memoria utilizzata*/
   XtFree(stringa); 

/* Creazione del Text widget  */
   narg=0;

   XtSetArg(arg[narg],XmNtopAttachment,XmATTACH_FORM); narg++;
   XtSetArg(arg[narg],XmNrightAttachment,XmATTACH_FORM); narg++;
   XtSetArg(arg[narg],XmNleftAttachment,XmATTACH_FORM); narg++;
   XtSetArg(arg[narg],XmNbottomAttachment,XmATTACH_FORM); narg++;
   XtSetArg(arg[narg],XmNbottomOffset,5); narg++;
   XtSetArg(arg[narg],XmNrightOffset,5); narg++;
   XtSetArg(arg[narg],XmNleftOffset,5); narg++;
   XtSetArg(arg[narg],XmNtopOffset,50); narg++;
   XtSetArg(arg[narg],XmNcolumns,110); narg++;

   XtSetArg(arg[narg],XmNrows,60); narg++;
   XtSetArg(arg[narg],XmNeditable,False); narg++;
   XtSetArg(arg[narg],XmNeditMode,XmMULTI_LINE_EDIT); narg++;
   XtSetArg(arg[narg],XmNscrollingPolicy,XmAUTOMATIC); narg++;
   XtSetArg(arg[narg],XmNvisualPolicy,XmCONSTANT); narg++;

   testo=XmCreateScrolledText(form3,"testo",arg,narg);
   XtManageChild (testo);

   XmTextSetString (testo,dforaus.foraus);

}

/*******************************************************************************
	The following are callback functions.
*******************************************************************************/

static void	activateCB_FileSave( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	{
	
	   printf("viene salvato il file descr.dat \n");
	/* se editabile == True */
	
	   if(editabile == True)
	      save_descr();
	}
	UxTopLevelShell1Context = UxSaveCtx;
}

static void	activateCB_FileQuit( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;
{
	_UxCtopLevelShell1      *UxSaveCtx, *UxContext;

	UxSaveCtx = UxTopLevelShell1Context;
	UxTopLevelShell1Context = UxContext =
			(_UxCtopLevelShell1 *) UxGetContext( UxWidget );
	exit(0);
	UxTopLevelShell1Context = UxSaveCtx;
}

/*******************************************************************************
	The 'build_' function creates all the widgets
	using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_topLevelShell1()
{
	Widget	File_shell;

	topLevelShell1 = XtVaCreatePopupShell( "topLevelShell1",
			topLevelShellWidgetClass, UxTopLevel,
			XmNtitle, "Model Info",
			XmNheight, 670,
			XmNwidth, 520,
			XmNy, 150,
			XmNx, 140,
			NULL );

	UxPutContext( topLevelShell1, (char *) UxTopLevelShell1Context );

	mainWindow1 = XtVaCreateManagedWidget( "mainWindow1",
			xmMainWindowWidgetClass, topLevelShell1,
			XmNheight, 620,
			XmNwidth, 460,
			XmNy, 20,
			XmNx, 20,
			XmNunitType, XmPIXELS,
			NULL );

	UxPutContext( mainWindow1, (char *) UxTopLevelShell1Context );

	panedWindow1 = XtVaCreateManagedWidget( "panedWindow1",
			xmPanedWindowWidgetClass, mainWindow1,
			NULL );

	UxPutContext( panedWindow1, (char *) UxTopLevelShell1Context );

	form1 = XtVaCreateManagedWidget( "form1",
			xmFormWidgetClass, panedWindow1,
			XmNpaneMinimum, 100,
			XmNskipAdjust, TRUE,
			XmNallowResize, TRUE,
			XmNheight, 177,
			XmNwidth, 507,
			XmNy, 3,
			XmNx, 3,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form1, (char *) UxTopLevelShell1Context );

	label1 = XtVaCreateManagedWidget( "label1",
			xmLabelWidgetClass, form1,
			RES_CONVERT( XmNlabelString, "Description and Note" ),
			XmNheight, 30,
			XmNwidth, 190,
			XmNy, 0,
			XmNx, 160,
			NULL );

	UxPutContext( label1, (char *) UxTopLevelShell1Context );

	form2 = XtVaCreateManagedWidget( "form2",
			xmFormWidgetClass, panedWindow1,
			XmNpaneMinimum, 200,
			XmNskipAdjust, TRUE,
			XmNallowResize, TRUE,
			XmNheight, 192,
			XmNwidth, 517,
			XmNy, 248,
			XmNx, 3,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form2, (char *) UxTopLevelShell1Context );

	label2 = XtVaCreateManagedWidget( "label2",
			xmLabelWidgetClass, form2,
			RES_CONVERT( XmNlabelString, "Module List" ),
			XmNheight, 30,
			XmNwidth, 170,
			XmNy, 0,
			XmNx, 170,
			NULL );

	UxPutContext( label2, (char *) UxTopLevelShell1Context );

	scrolledWindow1 = XtVaCreateManagedWidget( "scrolledWindow1",
			xmScrolledWindowWidgetClass, form2,
			XmNtopOffset, 50,
			XmNrightOffset, 5,
			XmNleftOffset, 5,
			XmNbottomOffset, 5,
			XmNtopAttachment, XmATTACH_FORM,
			XmNrightAttachment, XmATTACH_FORM,
			XmNleftAttachment, XmATTACH_FORM,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNshadowThickness, 0,
			XmNscrollBarDisplayPolicy, XmSTATIC,
			XmNvisualPolicy, XmVARIABLE,
			XmNy, 40,
			XmNx, 20,
			XmNscrollingPolicy, XmAPPLICATION_DEFINED,
			NULL );

	UxPutContext( scrolledWindow1, (char *) UxTopLevelShell1Context );

	scrolledList2 = XtVaCreateManagedWidget( "scrolledList2",
			xmListWidgetClass, scrolledWindow1,
			XmNlistSizePolicy, XmCONSTANT,
			XmNtraversalOn, FALSE,
			XmNscrollBarDisplayPolicy, XmAS_NEEDED,
			XmNselectionPolicy, XmSINGLE_SELECT,
			XmNwidth, 470,
			NULL );

	UxPutContext( scrolledList2, (char *) UxTopLevelShell1Context );

	form3 = XtVaCreateManagedWidget( "form3",
			xmFormWidgetClass, panedWindow1,
			XmNpaneMinimum, 200,
			XmNheight, 116,
			XmNwidth, 517,
			XmNy, 520,
			XmNx, 3,
			XmNresizePolicy, XmRESIZE_NONE,
			NULL );

	UxPutContext( form3, (char *) UxTopLevelShell1Context );

	label3 = XtVaCreateManagedWidget( "label3",
			xmLabelWidgetClass, form3,
			RES_CONVERT( XmNlabelString, "foraus.for" ),
			XmNheight, 30,
			XmNwidth, 180,
			XmNy, 0,
			XmNx, 170,
			NULL );

	UxPutContext( label3, (char *) UxTopLevelShell1Context );

	menu1 = XtVaCreateManagedWidget( "menu1",
			xmRowColumnWidgetClass, mainWindow1,
			XmNmenuAccelerator, "<KeyUp>F10",
			XmNrowColumnType, XmMENU_BAR,
			NULL );

	UxPutContext( menu1, (char *) UxTopLevelShell1Context );

	File_shell = XtVaCreatePopupShell ("File_shell",
			xmMenuShellWidgetClass, menu1,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	File = XtVaCreateWidget( "File",
			xmRowColumnWidgetClass, File_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );

	UxPutContext( File, (char *) UxTopLevelShell1Context );

	FileSave = XtVaCreateManagedWidget( "FileSave",
			xmPushButtonWidgetClass, File,
			RES_CONVERT( XmNlabelString, "Save" ),
			NULL );

	UxPutContext( FileSave, (char *) UxTopLevelShell1Context );

	FileQuit = XtVaCreateManagedWidget( "FileQuit",
			xmPushButtonWidgetClass, File,
			RES_CONVERT( XmNlabelString, "Quit" ),
			NULL );

	UxPutContext( FileQuit, (char *) UxTopLevelShell1Context );

	menu1_top_b1 = XtVaCreateManagedWidget( "menu1_top_b1",
			xmCascadeButtonWidgetClass, menu1,
			XmNsubMenuId, File,
			RES_CONVERT( XmNlabelString, "File" ),
			NULL );

	UxPutContext( menu1_top_b1, (char *) UxTopLevelShell1Context );

	XtAddCallback( topLevelShell1, XmNdestroyCallback,
			UxFreeClientDataCB,
			(XtPointer) UxTopLevelShell1Context );

	XtAddCallback( FileSave, XmNactivateCallback,
			activateCB_FileSave,
			(XtPointer) UxTopLevelShell1Context );

	XtAddCallback( FileQuit, XmNactivateCallback,
			activateCB_FileQuit,
			(XtPointer) UxTopLevelShell1Context );


	XmMainWindowSetAreas( mainWindow1, menu1, (Widget) NULL,
			(Widget) NULL, (Widget) NULL, panedWindow1 );

	return ( topLevelShell1 );
}

/*******************************************************************************
	The following function includes the code that was entered
	in the 'Initial Code' and 'Final Code' sections of the
	Declarations Editor. This function is called from the
	'Interface function' below.
*******************************************************************************/

static Widget	_Ux_create_topLevelShell1()
{
	Widget                  rtrn;
	_UxCtopLevelShell1      *UxContext;

	UxTopLevelShell1Context = UxContext =
		(_UxCtopLevelShell1 *) XtMalloc( sizeof(_UxCtopLevelShell1) );

	rtrn = _Uxbuild_topLevelShell1();

	if( editabile == False)
	   UxPutSensitive(FileSave,"false");
	
	
	{
	   if(whatConfiguration == 2)
	   {
	      DisplayDescriz(); 
	      DisplayListaMod();
	      DisplayForaus();
	   }
	   else
	   {
	      XtResizeWidget(topLevelShell1,520,250,0);
	      DisplayDescriz(); 
	      XtDestroyWidget(form2);
	      XtDestroyWidget(form3);
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

Widget	create_topLevelShell1()
{
	Widget			_Uxrtrn;

	_Uxrtrn = _Ux_create_topLevelShell1();

	return ( _Uxrtrn );
}

/*******************************************************************************
	END OF FILE
*******************************************************************************/
