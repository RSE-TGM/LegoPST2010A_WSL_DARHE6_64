
/*******************************************************************************
       FontsViewer.c
       (Generated from interface file FontsViewer.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/TextF.h>
#include <Xm/Label.h>
#include <Xm/ToggleB.h>
#include <Xm/Separator.h>
#include <Xm/Form.h>
#include <Xm/CascadeB.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/MainW.h>
#include <X11/Shell.h>

#include"libutilx.h"

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo FontsViewer.i
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)FontsViewer.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <Xm/Xm.h>
#include "res_edit.h"

extern swidget create_FontsEditor();
extern char *WidGetName();

char *CaricaFont ( );


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
	Widget	UxFontsViewer;
	Widget	UxmainWindow5;
	Widget	Uxmenu5;
	Widget	UxEditFontPane;
	Widget	UxEditFontItem;
	Widget	Uxmenu5_top_b1;
	Widget	Uxform5;
	Widget	Uxseparator7;
	Widget	UxFontSample5;
	Widget	UxFontSample4;
	Widget	UxFontSample3;
	Widget	UxFontSample2;
	Widget	UxFontSample1;
	Widget	Uxlabel9;
	Widget	Uxlabel10;
	Widget	UxLabelFont;
	Widget	Uxlabel12;
	Widget	Uxseparator8;
	Widget	UxpushButton10;
	Widget	UxpushButton9;
	Widget	UxpushButton11;
	Widget	UxTextNomeFont;
	XrmDatabase	UxRisDbFonts;
	unsigned char	UxVettoreFont[5][200];
	Widget	*UxListaRC;
	unsigned char	*Uxstrfont;
	Widget	*UxListaINP;
	Widget	UxChiamFon;
} _UxCFontsViewer;

static _UxCFontsViewer         *UxFontsViewerContext;
#define FontsViewer             UxFontsViewerContext->UxFontsViewer
#define mainWindow5             UxFontsViewerContext->UxmainWindow5
#define menu5                   UxFontsViewerContext->Uxmenu5
#define EditFontPane            UxFontsViewerContext->UxEditFontPane
#define EditFontItem            UxFontsViewerContext->UxEditFontItem
#define menu5_top_b1            UxFontsViewerContext->Uxmenu5_top_b1
#define form5                   UxFontsViewerContext->Uxform5
#define separator7              UxFontsViewerContext->Uxseparator7
#define FontSample5             UxFontsViewerContext->UxFontSample5
#define FontSample4             UxFontsViewerContext->UxFontSample4
#define FontSample3             UxFontsViewerContext->UxFontSample3
#define FontSample2             UxFontsViewerContext->UxFontSample2
#define FontSample1             UxFontsViewerContext->UxFontSample1
#define label9                  UxFontsViewerContext->Uxlabel9
#define label10                 UxFontsViewerContext->Uxlabel10
#define LabelFont               UxFontsViewerContext->UxLabelFont
#define label12                 UxFontsViewerContext->Uxlabel12
#define separator8              UxFontsViewerContext->Uxseparator8
#define pushButton10            UxFontsViewerContext->UxpushButton10
#define pushButton9             UxFontsViewerContext->UxpushButton9
#define pushButton11            UxFontsViewerContext->UxpushButton11
#define TextNomeFont            UxFontsViewerContext->UxTextNomeFont
#define RisDbFonts              UxFontsViewerContext->UxRisDbFonts
#define VettoreFont             UxFontsViewerContext->UxVettoreFont
#define ListaRC                 UxFontsViewerContext->UxListaRC
#define strfont                 UxFontsViewerContext->Uxstrfont
#define ListaINP                UxFontsViewerContext->UxListaINP
#define ChiamFon                UxFontsViewerContext->UxChiamFon



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_FontsViewer();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

char *CaricaFont (swidget sw)
{
XrmValue xrm_value;
char *str_type;
char str_sorg[100];
char *buffer;

buffer = XtCalloc (200, sizeof(char));

strcpy (str_sorg,WidGetName(sw));
strcat (str_sorg,".nomeFont");

if ( XrmGetResource(RisDbFonts,str_sorg,"CNomeFont",&str_type,&xrm_value) )
	strncpy (buffer, xrm_value.addr, (int)xrm_value.size);
return (buffer);
}

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_EditFontItem( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFontsViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFontsViewerContext;
	UxFontsViewerContext = UxContext =
			(_UxCFontsViewer *) UxGetContext( UxWidget );
	UxPopupInterface (create_FontsEditor(TextNomeFont,FontsViewer),no_grab);
	UxFontsViewerContext = UxSaveCtx;
}

static	void	armCB_FontSample5( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFontsViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFontsViewerContext;
	UxFontsViewerContext = UxContext =
			(_UxCFontsViewer *) UxGetContext( UxWidget );
	{
	XmFontList Fontl;
	
	set_something (FontSample1, XmNset, (void*) False);
	set_something (FontSample2, XmNset, (void*) False);
	set_something (FontSample3, XmNset, (void*) False);
	set_something (FontSample4, XmNset, (void*) False);
	
	get_something (FontSample5, XmNfontList, (void*) &Fontl);
	set_something (LabelFont , XmNfontList, (void*) Fontl);
	
	XmTextFieldSetString (TextNomeFont, VettoreFont[4]);
	}
	UxFontsViewerContext = UxSaveCtx;
}

static	void	armCB_FontSample4( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFontsViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFontsViewerContext;
	UxFontsViewerContext = UxContext =
			(_UxCFontsViewer *) UxGetContext( UxWidget );
	{
	XmFontList Fontl;
	
	set_something (FontSample1, XmNset, (void*) False);
	set_something (FontSample2, XmNset, (void*) False);
	set_something (FontSample3, XmNset, (void*) False);
	set_something (FontSample5, XmNset, (void*) False);
	
	get_something (FontSample4, XmNfontList, (void*) &Fontl);
	set_something (LabelFont, XmNfontList, (void*) Fontl);
	
	XmTextFieldSetString (TextNomeFont, VettoreFont[3]);
	}
	UxFontsViewerContext = UxSaveCtx;
}

static	void	armCB_FontSample3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFontsViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFontsViewerContext;
	UxFontsViewerContext = UxContext =
			(_UxCFontsViewer *) UxGetContext( UxWidget );
	{
	XmFontList Fontl;
	
	set_something (FontSample1, XmNset, (void*) False);
	set_something (FontSample2, XmNset, (void*) False);
	set_something (FontSample4, XmNset, (void*) False);
	set_something (FontSample5, XmNset, (void*) False);
	
	get_something (FontSample3, XmNfontList , (void*) &Fontl);
	set_something (LabelFont, XmNfontList, (void*) Fontl);
	
	XmTextFieldSetString (TextNomeFont , VettoreFont[2]);
	}
	UxFontsViewerContext = UxSaveCtx;
}

static	void	armCB_FontSample2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFontsViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFontsViewerContext;
	UxFontsViewerContext = UxContext =
			(_UxCFontsViewer *) UxGetContext( UxWidget );
	{
	XmFontList Fontl;
	
	set_something (FontSample1, XmNset, (void*) False);
	set_something (FontSample3, XmNset, (void*) False);
	set_something (FontSample4, XmNset, (void*) False);
	set_something (FontSample5, XmNset, (void*) False);
	
	get_something (FontSample2, XmNfontList, (void*) &Fontl);
	set_something (LabelFont, XmNfontList, (void*) Fontl); 
	
	XmTextFieldSetString (TextNomeFont , VettoreFont[1]);
	}
	UxFontsViewerContext = UxSaveCtx;
}

static	void	armCB_FontSample1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFontsViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFontsViewerContext;
	UxFontsViewerContext = UxContext =
			(_UxCFontsViewer *) UxGetContext( UxWidget );
	{
	XmFontList Fontl;
	
	set_something (FontSample2, XmNset, (void*) False);
	set_something (FontSample3, XmNset, (void*) False);
	set_something (FontSample4, XmNset, (void*) False);
	set_something (FontSample5, XmNset, (void*) False);
	
	get_something (FontSample1, XmNfontList , (void*) &Fontl);
	set_something (LabelFont, XmNfontList, (void*) Fontl);
	
	XmTextFieldSetString (TextNomeFont, VettoreFont[0]);
	}
	UxFontsViewerContext = UxSaveCtx;
}

static	void	activateCB_pushButton10( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFontsViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFontsViewerContext;
	UxFontsViewerContext = UxContext =
			(_UxCFontsViewer *) UxGetContext( UxWidget );
	{
	/*  Ritorna a sensitive il pushbutton e il textfield chiamante */
	set_something (ListaRC[0], XmNsensitive, (void*) True);
	set_something (ListaRC[2], XmNsensitive, (void*) True);
	
	XtDestroyWidget (FontsViewer);
	}
	UxFontsViewerContext = UxSaveCtx;
}

static	void	activateCB_pushButton9( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFontsViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFontsViewerContext;
	UxFontsViewerContext = UxContext =
			(_UxCFontsViewer *) UxGetContext( UxWidget );
	{
	XFontStruct *FontInfo;
	XmFontList FontList;
	char *StrFont;
	int SettaFont;
	Boolean Value;
	
	StrFont = (char *)XmTextFieldGetString (TextNomeFont);
	SettaFont = 0;
	if ( XmToggleButtonGetState(FontSample1) ) SettaFont = 1;
	if ( XmToggleButtonGetState(FontSample2) ) SettaFont = 2;
	if ( XmToggleButtonGetState(FontSample3) ) SettaFont = 3;
	if ( XmToggleButtonGetState(FontSample4) ) SettaFont = 4;
	if ( XmToggleButtonGetState(FontSample5) ) SettaFont = 5;
	
	if ( (FontInfo = XLoadQueryFont (UxDisplay,StrFont) ) == NULL)
		XmTextFieldSetString (TextNomeFont, "Unable to open font!");
	else
		{
		FontList = XmFontListCreate (FontInfo, XmSTRING_DEFAULT_CHARSET);
		set_something (LabelFont , XmNfontList, (void*) FontList);
		XmTextFieldSetString (ListaRC[2], StrFont);
		switch (SettaFont)
		{
		case 1:
			set_something (FontSample1,XmNfontList,(void*) FontList);
			strcpy (VettoreFont[0],StrFont);
		break;
		case 2:
			set_something (FontSample2,XmNfontList,(void*) FontList);
			strcpy (VettoreFont[1],StrFont);
		break;
		case 3:
			set_something (FontSample3,XmNfontList,(void*) FontList);
			strcpy (VettoreFont[2],StrFont);
		break;
		case 4:
			set_something (FontSample4,XmNfontList,(void*) FontList);
			strcpy (VettoreFont[3],StrFont);
		break;
		case 5:
			set_something (FontSample5,XmNfontList,(void*) FontList);
			strcpy (VettoreFont[4],StrFont);
		break;
		}
		}
	XtFree (StrFont);
	}
	UxFontsViewerContext = UxSaveCtx;
}

static	void	activateCB_pushButton11( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCFontsViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxFontsViewerContext;
	UxFontsViewerContext = UxContext =
			(_UxCFontsViewer *) UxGetContext( UxWidget );
	{
	XmFontList FontL;
	char *Stringa;
	
	Stringa = (char *)XmTextFieldGetString (TextNomeFont);
	XmTextFieldSetString (ListaRC[2], Stringa);
	
	/*  Ritorna a sensitive il pushButton e il textfield chiamante */
	set_something (ListaRC[0], XmNsensitive, (void*) True);
	set_something (ListaRC[2], XmNsensitive, (void*) True);
	
	XlSetResourceByWidget (&RisDbFonts,FontSample1,XmNfontList,VettoreFont[0]);
	XlSetResourceByWidget (&RisDbFonts,FontSample2,XmNfontList,VettoreFont[1]);
	XlSetResourceByWidget (&RisDbFonts,FontSample3,XmNfontList,VettoreFont[2]);
	XlSetResourceByWidget (&RisDbFonts,FontSample4,XmNfontList,VettoreFont[3]);
	XlSetResourceByWidget (&RisDbFonts,FontSample5,XmNfontList,VettoreFont[4]);
	
	XlSetResourceByWidget (&RisDbFonts,FontSample1,"nomeFont",VettoreFont[0]);
	XlSetResourceByWidget (&RisDbFonts,FontSample2,"nomeFont",VettoreFont[1]);
	XlSetResourceByWidget (&RisDbFonts,FontSample3,"nomeFont",VettoreFont[2]);
	XlSetResourceByWidget (&RisDbFonts,FontSample4,"nomeFont",VettoreFont[3]);
	XlSetResourceByWidget (&RisDbFonts,FontSample5,"nomeFont",VettoreFont[4]);
	
	XrmPutFileDatabase (RisDbFonts,"FileFontsDefault");
	XtFree (Stringa);
	XtDestroyWidget (FontsViewer);
	}
	UxFontsViewerContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_FontsViewer()
{
	Widget		_UxParent;
	Widget		EditFontPane_shell;


	/* Creation of FontsViewer */
	_UxParent = ChiamFon;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	FontsViewer = XtVaCreatePopupShell( "FontsViewer",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, -7,
			XmNy, -8,
			XmNwidth, 380,
			XmNheight, 500,
			XmNiconName, "Font Viewer",
			XmNtitle, "Resource Font Viewer",
			XmNallowShellResize, TRUE,
			NULL );
	UxPutContext( FontsViewer, (char *) UxFontsViewerContext );


	/* Creation of mainWindow5 */
	mainWindow5 = XtVaCreateManagedWidget( "mainWindow5",
			xmMainWindowWidgetClass,
			FontsViewer,
			XmNunitType, XmPIXELS,
			XmNx, 25,
			XmNy, 10,
			XmNwidth, 380,
			XmNheight, 500,
			NULL );
	UxPutContext( mainWindow5, (char *) UxFontsViewerContext );


	/* Creation of menu5 */
	menu5 = XtVaCreateManagedWidget( "menu5",
			xmRowColumnWidgetClass,
			mainWindow5,
			XmNrowColumnType, XmMENU_BAR,
			XmNmenuAccelerator, "<KeyUp>F10",
			NULL );
	UxPutContext( menu5, (char *) UxFontsViewerContext );


	/* Creation of EditFontPane */
	EditFontPane_shell = XtVaCreatePopupShell ("EditFontPane_shell",
			xmMenuShellWidgetClass, menu5,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	EditFontPane = XtVaCreateWidget( "EditFontPane",
			xmRowColumnWidgetClass,
			EditFontPane_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );
	UxPutContext( EditFontPane, (char *) UxFontsViewerContext );


	/* Creation of EditFontItem */
	EditFontItem = XtVaCreateManagedWidget( "EditFontItem",
			xmPushButtonWidgetClass,
			EditFontPane,
			RES_CONVERT( XmNlabelString, "Edit Font" ),
			RES_CONVERT( XmNmnemonic, "F" ),
			NULL );
	XtAddCallback( EditFontItem, XmNactivateCallback,
		(XtCallbackProc) activateCB_EditFontItem,
		(XtPointer) UxFontsViewerContext );

	UxPutContext( EditFontItem, (char *) UxFontsViewerContext );


	/* Creation of menu5_top_b1 */
	menu5_top_b1 = XtVaCreateManagedWidget( "menu5_top_b1",
			xmCascadeButtonWidgetClass,
			menu5,
			RES_CONVERT( XmNlabelString, "Edit" ),
			RES_CONVERT( XmNmnemonic, "E" ),
			XmNsubMenuId, EditFontPane,
			NULL );
	UxPutContext( menu5_top_b1, (char *) UxFontsViewerContext );


	/* Creation of form5 */
	form5 = XtVaCreateManagedWidget( "form5",
			xmFormWidgetClass,
			mainWindow5,
			NULL );
	UxPutContext( form5, (char *) UxFontsViewerContext );


	/* Creation of separator7 */
	separator7 = XtVaCreateManagedWidget( "separator7",
			xmSeparatorWidgetClass,
			form5,
			XmNx, 5,
			XmNy, 240,
			XmNwidth, 380,
			XmNheight, 20,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 5,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 5,
			XmNtopAttachment, XmATTACH_NONE,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			NULL );
	UxPutContext( separator7, (char *) UxFontsViewerContext );


	/* Creation of FontSample5 */
	FontSample5 = XtVaCreateManagedWidget( "FontSample5",
			xmToggleButtonWidgetClass,
			form5,
			XmNx, 10,
			XmNy, 220,
			XmNwidth, 360,
			XmNheight, 35,
			XmNindicatorType, XmONE_OF_MANY,
			XmNindicatorSize, 20,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "This is an example of a Font" ),
			XmNmarginLeft, 40,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 5,
			XmNbottomWidget, separator7,
			XmNtopAttachment, XmATTACH_NONE,
			XmNrecomputeSize, FALSE,
			NULL );
	XtAddCallback( FontSample5, XmNarmCallback,
		(XtCallbackProc) armCB_FontSample5,
		(XtPointer) UxFontsViewerContext );

	UxPutContext( FontSample5, (char *) UxFontsViewerContext );


	/* Creation of FontSample4 */
	FontSample4 = XtVaCreateManagedWidget( "FontSample4",
			xmToggleButtonWidgetClass,
			form5,
			XmNx, 10,
			XmNy, 175,
			XmNwidth, 360,
			XmNheight, 35,
			XmNindicatorType, XmONE_OF_MANY,
			XmNindicatorSize, 20,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "This is an example of a Font" ),
			XmNmarginLeft, 40,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 5,
			XmNbottomWidget, FontSample5,
			XmNrecomputeSize, FALSE,
			NULL );
	XtAddCallback( FontSample4, XmNarmCallback,
		(XtCallbackProc) armCB_FontSample4,
		(XtPointer) UxFontsViewerContext );

	UxPutContext( FontSample4, (char *) UxFontsViewerContext );


	/* Creation of FontSample3 */
	FontSample3 = XtVaCreateManagedWidget( "FontSample3",
			xmToggleButtonWidgetClass,
			form5,
			XmNx, 10,
			XmNy, 130,
			XmNwidth, 360,
			XmNheight, 35,
			XmNindicatorType, XmONE_OF_MANY,
			XmNindicatorSize, 20,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "This is an example of a Font" ),
			XmNmarginLeft, 40,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 5,
			XmNbottomWidget, FontSample4,
			XmNrecomputeSize, FALSE,
			NULL );
	XtAddCallback( FontSample3, XmNarmCallback,
		(XtCallbackProc) armCB_FontSample3,
		(XtPointer) UxFontsViewerContext );

	UxPutContext( FontSample3, (char *) UxFontsViewerContext );


	/* Creation of FontSample2 */
	FontSample2 = XtVaCreateManagedWidget( "FontSample2",
			xmToggleButtonWidgetClass,
			form5,
			XmNx, 10,
			XmNy, 90,
			XmNwidth, 360,
			XmNheight, 35,
			XmNindicatorType, XmONE_OF_MANY,
			XmNindicatorSize, 20,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "This is an example of a Font" ),
			XmNmarginLeft, 40,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 5,
			XmNbottomWidget, FontSample3,
			XmNrecomputeSize, FALSE,
			NULL );
	XtAddCallback( FontSample2, XmNarmCallback,
		(XtCallbackProc) armCB_FontSample2,
		(XtPointer) UxFontsViewerContext );

	UxPutContext( FontSample2, (char *) UxFontsViewerContext );


	/* Creation of FontSample1 */
	FontSample1 = XtVaCreateManagedWidget( "FontSample1",
			xmToggleButtonWidgetClass,
			form5,
			XmNx, 10,
			XmNy, 40,
			XmNwidth, 360,
			XmNheight, 35,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNtopAttachment, XmATTACH_NONE,
			XmNtopOffset, 5,
			XmNtopWidget, NULL,
			XmNindicatorType, XmONE_OF_MANY,
			XmNindicatorSize, 20,
			XmNalignment, XmALIGNMENT_BEGINNING,
			RES_CONVERT( XmNlabelString, "This is an example of a Font" ),
			XmNmarginLeft, 40,
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 5,
			XmNbottomWidget, FontSample2,
			XmNrecomputeSize, FALSE,
			NULL );
	XtAddCallback( FontSample1, XmNarmCallback,
		(XtCallbackProc) armCB_FontSample1,
		(XtPointer) UxFontsViewerContext );

	UxPutContext( FontSample1, (char *) UxFontsViewerContext );


	/* Creation of label9 */
	label9 = XtVaCreateManagedWidget( "label9",
			xmLabelWidgetClass,
			form5,
			XmNx, 5,
			XmNy, 10,
			XmNwidth, 110,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "Defaults:" ),
			XmNbottomAttachment, XmATTACH_WIDGET,
			XmNbottomOffset, 5,
			XmNbottomWidget, FontSample1,
			XmNtopAttachment, XmATTACH_FORM,
			XmNtopOffset, 5,
			NULL );
	UxPutContext( label9, (char *) UxFontsViewerContext );


	/* Creation of label10 */
	label10 = XtVaCreateManagedWidget( "label10",
			xmLabelWidgetClass,
			form5,
			XmNx, 10,
			XmNy, 260,
			XmNwidth, 110,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "Selected Font:" ),
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 5,
			XmNtopWidget, separator7,
			NULL );
	UxPutContext( label10, (char *) UxFontsViewerContext );


	/* Creation of LabelFont */
	LabelFont = XtVaCreateManagedWidget( "LabelFont",
			xmLabelWidgetClass,
			form5,
			XmNx, 10,
			XmNy, 300,
			XmNwidth, 360,
			XmNheight, 40,
			RES_CONVERT( XmNlabelString, "This is an example of a selected Font" ),
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 10,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 5,
			XmNtopWidget, label10,
			NULL );
	UxPutContext( LabelFont, (char *) UxFontsViewerContext );


	/* Creation of label12 */
	label12 = XtVaCreateManagedWidget( "label12",
			xmLabelWidgetClass,
			form5,
			XmNx, 10,
			XmNy, 345,
			XmNwidth, 80,
			XmNheight, 40,
			RES_CONVERT( XmNlabelString, "FontName:" ),
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 5,
			XmNtopWidget, LabelFont,
			NULL );
	UxPutContext( label12, (char *) UxFontsViewerContext );


	/* Creation of separator8 */
	separator8 = XtVaCreateManagedWidget( "separator8",
			xmSeparatorWidgetClass,
			form5,
			XmNx, 0,
			XmNy, 390,
			XmNwidth, 380,
			XmNheight, 20,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 5,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 5,
			NULL );
	UxPutContext( separator8, (char *) UxFontsViewerContext );


	/* Creation of pushButton10 */
	pushButton10 = XtVaCreateManagedWidget( "pushButton10",
			xmPushButtonWidgetClass,
			form5,
			XmNx, 260,
			XmNy, 420,
			XmNwidth, 85,
			XmNheight, 35,
			RES_CONVERT( XmNlabelString, "CANCEL" ),
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 5,
			XmNtopWidget, separator8,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 15,
			XmNleftPosition, 65,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 90,
			NULL );
	XtAddCallback( pushButton10, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton10,
		(XtPointer) UxFontsViewerContext );

	UxPutContext( pushButton10, (char *) UxFontsViewerContext );


	/* Creation of pushButton9 */
	pushButton9 = XtVaCreateManagedWidget( "pushButton9",
			xmPushButtonWidgetClass,
			form5,
			XmNx, 130,
			XmNy, 420,
			XmNwidth, 85,
			XmNheight, 35,
			RES_CONVERT( XmNlabelString, "APPLY" ),
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNrightWidget, NULL,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 5,
			XmNtopWidget, separator8,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 15,
			XmNleftPosition, 35,
			XmNrightPosition, 60,
			NULL );
	XtAddCallback( pushButton9, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton9,
		(XtPointer) UxFontsViewerContext );

	UxPutContext( pushButton9, (char *) UxFontsViewerContext );


	/* Creation of pushButton11 */
	pushButton11 = XtVaCreateManagedWidget( "pushButton11",
			xmPushButtonWidgetClass,
			form5,
			XmNx, 17,
			XmNy, 416,
			XmNwidth, 85,
			XmNheight, 35,
			RES_CONVERT( XmNlabelString, "OK" ),
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNrightWidget, NULL,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 5,
			XmNtopWidget, separator8,
			XmNbottomAttachment, XmATTACH_FORM,
			XmNbottomOffset, 15,
			XmNleftPosition, 5,
			XmNrightPosition, 30,
			NULL );
	XtAddCallback( pushButton11, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton11,
		(XtPointer) UxFontsViewerContext );

	UxPutContext( pushButton11, (char *) UxFontsViewerContext );


	/* Creation of TextNomeFont */
	TextNomeFont = XtVaCreateManagedWidget( "TextNomeFont",
			xmTextFieldWidgetClass,
			form5,
			XmNx, 100,
			XmNy, 350,
			XmNwidth, 270,
			XmNheight, 40,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 5,
			XmNleftWidget, label12,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 10,
			XmNtopAttachment, XmATTACH_WIDGET,
			XmNtopOffset, 5,
			XmNtopWidget, LabelFont,
			NULL );
	UxPutContext( TextNomeFont, (char *) UxFontsViewerContext );


	XtAddCallback( FontsViewer, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxFontsViewerContext);

	XmMainWindowSetAreas( mainWindow5, menu5, (Widget) NULL,
			(Widget) NULL, (Widget) NULL, form5 );

	return ( FontsViewer );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_FontsViewer( _Uxstrfont, _UxListaINP, _UxChiamFon )
	unsigned char	*_Uxstrfont;
	Widget	*_UxListaINP;
	Widget	_UxChiamFon;
{
	Widget                  rtrn;
	_UxCFontsViewer         *UxContext;

	UxFontsViewerContext = UxContext =
		(_UxCFontsViewer *) UxNewContext( sizeof(_UxCFontsViewer), False );

	strfont = _Uxstrfont;
	ListaINP = _UxListaINP;
	ChiamFon = _UxChiamFon;

	{
		char *StrFont,*Appoggio;
		XFontStruct *FontInfo;
		XmFontList FontList;
		XrmDatabase DbAppo;
		
		DbAppo = XrmGetDatabase (UxDisplay);
		ListaRC = ListaINP;
		RisDbFonts = XrmGetFileDatabase ("FileFontsDefault");
		XrmSetDatabase (UxDisplay,RisDbFonts);
		
		StrFont = (char *)strfont;
		rtrn = _Uxbuild_FontsViewer();

		/*  Legge dal database i nomi dei font di default */
		Appoggio = CaricaFont (FontSample1);
		if ( Appoggio[0] == '\0')
			strcpy (VettoreFont[0],"fixed");
		else strcpy (VettoreFont [0],Appoggio);
		XtFree (Appoggio);
		
		Appoggio = CaricaFont (FontSample2);
		if ( Appoggio[0] == '\0')
			strcpy (VettoreFont[1],"fixed");
		else strcpy (VettoreFont [1],Appoggio);
		XtFree (Appoggio);
		
		Appoggio = CaricaFont (FontSample3);
		if ( Appoggio[0] == '\0')
			strcpy (VettoreFont[2],"fixed");
		else strcpy (VettoreFont [2],Appoggio);
		XtFree (Appoggio);
		
		Appoggio = CaricaFont (FontSample4);
		if ( Appoggio[0] == '\0')
			strcpy (VettoreFont[3],"fixed");
		else strcpy (VettoreFont [3],Appoggio);
		XtFree (Appoggio);
		
		Appoggio = CaricaFont (FontSample5);
		if ( Appoggio[0] == '\0')
			strcpy (VettoreFont[4],"fixed");
		else strcpy (VettoreFont [4],Appoggio);
		XtFree (Appoggio);
		
		XrmSetDatabase (UxDisplay,DbAppo);
		
		if ( (FontInfo = XLoadQueryFont (UxDisplay,StrFont) ) == NULL)
			XmTextFieldSetString (TextNomeFont, "Unable to open font!");
		else
			{
			XmTextFieldSetString (TextNomeFont, StrFont);
			FontList = XmFontListCreate (FontInfo, XmSTRING_DEFAULT_CHARSET);
			set_something (LabelFont , XmNfontList, (void*) FontList);
			}
		
		/*  Setta la posizione dell'interfaccia rispetto al Parent  */
		InterfaceSetPos (FontsViewer,ChiamFon);
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

