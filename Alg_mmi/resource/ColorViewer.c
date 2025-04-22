
/*******************************************************************************
       ColorViewer.c
       (Generated from interface file ColorViewer.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/CascadeB.h>
#include <Xm/RowColumn.h>
#include <Xm/TextF.h>
#include <Xm/DrawnB.h>
#include <Xm/Separator.h>
#include <Xm/PushB.h>
#include <Xm/Label.h>
#include <Xm/Form.h>
#include <Xm/MainW.h>
#include <X11/Shell.h>

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo ColorViewer.i
   tipo 
   release 5.2
   data 2/13/96
   reserved @(#)ColorViewer.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <string.h>
#include <Xm/Xm.h>
#include "res_edit.h"


extern Display *UxDisplay;
extern swidget create_ColorEditor();
extern swidget create_ColorMapViewer();


static	int _UxIfClassId;
int	UxColorViewer_disableBlinkRate_Id = -1;
char*	UxColorViewer_disableBlinkRate_Name = "disableBlinkRate";
int	UxColorViewer_displayBlinkRate_Id = -1;
char*	UxColorViewer_displayBlinkRate_Name = "displayBlinkRate";
int	UxColorViewer_enableBlinkRate_Id = -1;
char*	UxColorViewer_enableBlinkRate_Name = "enableBlinkRate";

#ifndef ColorViewer_disableBlinkRate
#define ColorViewer_disableBlinkRate( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, UxColorViewer_disableBlinkRate_Id,\
			UxColorViewer_disableBlinkRate_Name)) \
		( UxThis, pEnv )
#endif

#ifndef ColorViewer_displayBlinkRate
#define ColorViewer_displayBlinkRate( UxThis, pEnv ) \
	((void(*)())UxMethodLookup(UxThis, UxColorViewer_displayBlinkRate_Id,\
			UxColorViewer_displayBlinkRate_Name)) \
		( UxThis, pEnv )
#endif

#ifndef ColorViewer_enableBlinkRate
#define ColorViewer_enableBlinkRate( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, UxColorViewer_enableBlinkRate_Id,\
			UxColorViewer_enableBlinkRate_Name)) \
		( UxThis, pEnv )
#endif


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
	Widget	UxColorViewer;
	Widget	UxmainWindow2;
	Widget	Uxform3;
	Widget	Uxlabel2;
	Widget	UxpushButton3;
	Widget	UxpushButton4;
	Widget	UxpushButton2;
	Widget	Uxseparator3;
	Widget	UxButtNomeColore;
	Widget	UxTextNomeColore;
	Widget	Uxseparator2;
	Widget	Uxlabel3;
	Widget	Uxseparator1;
	Widget	UxlabelColorRes;
	Widget	UxdrawnButton12;
	Widget	UxdrawnButton6;
	Widget	UxdrawnButton11;
	Widget	UxdrawnButton5;
	Widget	UxdrawnButton10;
	Widget	UxdrawnButton9;
	Widget	UxdrawnButton8;
	Widget	UxdrawnButton7;
	Widget	UxdrawnButton4;
	Widget	UxdrawnButton3;
	Widget	UxdrawnButton2;
	Widget	UxdrawnButton1;
	Widget	UxBlinkRate;
	Widget	Uxblink_frequency;
	Widget	UxtransparentLabel;
	Widget	UxtransparentPane;
	Widget	UxtransparentNo;
	Widget	UxtransparentYes;
	Widget	UxtrasparentMenu;
	Widget	Uxmenu3;
	Widget	UxEditColorPane;
	Widget	UxEditItem;
	Widget	UxGrabItem;
	Widget	UxColorItem;
	Widget	Uxmenu3_top_b1;
	swidget	UxVettoreBottoni[12];
	XrmDatabase	UxRisDbColori;
	int	UxflagINP;
	Widget	*UxFigliRC;
	Colormap	UxCmap;
	int	UxPress;
	Boolean	Uxtransparent;
	float	UxblinkFreq;
	unsigned char	UxStrColor[200];
	int	UxFlag;
	unsigned char	*UxStrInput;
	XmString	UxLabButt;
	XrmDatabase	UxPdb;
	Widget	*UxFigliINP;
	Widget	UxChiamCol;
} _UxCColorViewer;

static _UxCColorViewer         *UxColorViewerContext;
#define ColorViewer             UxColorViewerContext->UxColorViewer
#define mainWindow2             UxColorViewerContext->UxmainWindow2
#define form3                   UxColorViewerContext->Uxform3
#define label2                  UxColorViewerContext->Uxlabel2
#define pushButton3             UxColorViewerContext->UxpushButton3
#define pushButton4             UxColorViewerContext->UxpushButton4
#define pushButton2             UxColorViewerContext->UxpushButton2
#define separator3              UxColorViewerContext->Uxseparator3
#define ButtNomeColore          UxColorViewerContext->UxButtNomeColore
#define TextNomeColore          UxColorViewerContext->UxTextNomeColore
#define separator2              UxColorViewerContext->Uxseparator2
#define label3                  UxColorViewerContext->Uxlabel3
#define separator1              UxColorViewerContext->Uxseparator1
#define labelColorRes           UxColorViewerContext->UxlabelColorRes
#define drawnButton12           UxColorViewerContext->UxdrawnButton12
#define drawnButton6            UxColorViewerContext->UxdrawnButton6
#define drawnButton11           UxColorViewerContext->UxdrawnButton11
#define drawnButton5            UxColorViewerContext->UxdrawnButton5
#define drawnButton10           UxColorViewerContext->UxdrawnButton10
#define drawnButton9            UxColorViewerContext->UxdrawnButton9
#define drawnButton8            UxColorViewerContext->UxdrawnButton8
#define drawnButton7            UxColorViewerContext->UxdrawnButton7
#define drawnButton4            UxColorViewerContext->UxdrawnButton4
#define drawnButton3            UxColorViewerContext->UxdrawnButton3
#define drawnButton2            UxColorViewerContext->UxdrawnButton2
#define drawnButton1            UxColorViewerContext->UxdrawnButton1
#define BlinkRate               UxColorViewerContext->UxBlinkRate
#define blink_frequency         UxColorViewerContext->Uxblink_frequency
#define transparentLabel        UxColorViewerContext->UxtransparentLabel
#define transparentPane         UxColorViewerContext->UxtransparentPane
#define transparentNo           UxColorViewerContext->UxtransparentNo
#define transparentYes          UxColorViewerContext->UxtransparentYes
#define trasparentMenu          UxColorViewerContext->UxtrasparentMenu
#define menu3                   UxColorViewerContext->Uxmenu3
#define EditColorPane           UxColorViewerContext->UxEditColorPane
#define EditItem                UxColorViewerContext->UxEditItem
#define GrabItem                UxColorViewerContext->UxGrabItem
#define ColorItem               UxColorViewerContext->UxColorItem
#define menu3_top_b1            UxColorViewerContext->Uxmenu3_top_b1
#define VettoreBottoni          UxColorViewerContext->UxVettoreBottoni
#define RisDbColori             UxColorViewerContext->UxRisDbColori
#define flagINP                 UxColorViewerContext->UxflagINP
#define FigliRC                 UxColorViewerContext->UxFigliRC
#define Cmap                    UxColorViewerContext->UxCmap
#define Press                   UxColorViewerContext->UxPress
#define transparent             UxColorViewerContext->Uxtransparent
#define blinkFreq               UxColorViewerContext->UxblinkFreq
#define StrColor                UxColorViewerContext->UxStrColor
#define Flag                    UxColorViewerContext->UxFlag
#define StrInput                UxColorViewerContext->UxStrInput
#define LabButt                 UxColorViewerContext->UxLabButt
#define Pdb                     UxColorViewerContext->UxPdb
#define FigliINP                UxColorViewerContext->UxFigliINP
#define ChiamCol                UxColorViewerContext->UxChiamCol



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_ColorViewer();

/*******************************************************************************
Declarations of methods
*******************************************************************************/

static int	_ColorViewer_disableBlinkRate();
static void	_ColorViewer_displayBlinkRate();
static int	_ColorViewer_enableBlinkRate();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

RilasciaDrawnButton (int IndiceSet)
{
int i;

for (i=0;i<12;i++)
	{
	set_something (VettoreBottoni [i], XmNshadowThickness, (void*) 2);
	set_something (VettoreBottoni [i], XmNshadowType, (void*) XmSHADOW_ETCHED_IN);
	}
set_something (VettoreBottoni[IndiceSet], XmNshadowThickness, (void*) 4);
set_something (VettoreBottoni[IndiceSet], XmNshadowType, (void*) XmSHADOW_IN);
}

/*******************************************************************************
       The following are method functions.
*******************************************************************************/

static int	Ux_disableBlinkRate( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	set_something(blink_frequency,XmNeditable,(void*) False );
	   set_something(blink_frequency,XmNsensitive,(void*) False );
	   set_something(BlinkRate,XmNsensitive,(void*) False );
}

static int	_ColorViewer_disableBlinkRate( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCColorViewer         *UxSaveCtx = UxColorViewerContext;

	UxColorViewerContext = (_UxCColorViewer *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_disableBlinkRate( UxThis, pEnv );
	UxColorViewerContext = UxSaveCtx;

	return ( _Uxrtrn );
}

static void	Ux_displayBlinkRate( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	char sfreq[20];
	
	sprintf(sfreq,"%f",blinkFreq);
	
	set_something(blink_frequency,XmNvalue,(void*) sfreq);
}

static void	_ColorViewer_displayBlinkRate( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	_UxCColorViewer         *UxSaveCtx = UxColorViewerContext;

	UxColorViewerContext = (_UxCColorViewer *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	Ux_displayBlinkRate( UxThis, pEnv );
	UxColorViewerContext = UxSaveCtx;
}

static int	Ux_enableBlinkRate( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	set_something(blink_frequency,XmNeditable,(void*) True );
	   set_something(blink_frequency,XmNsensitive,(void*) True );
	   set_something(BlinkRate,XmNsensitive,(void*) True );
}

static int	_ColorViewer_enableBlinkRate( UxThis, pEnv )
	swidget	UxThis;
	Environment *	pEnv;
{
	int			_Uxrtrn;
	_UxCColorViewer         *UxSaveCtx = UxColorViewerContext;

	UxColorViewerContext = (_UxCColorViewer *) UxGetContext( UxThis );
	if (pEnv)
		pEnv->_major = NO_EXCEPTION;
	_Uxrtrn = Ux_enableBlinkRate( UxThis, pEnv );
	UxColorViewerContext = UxSaveCtx;

	return ( _Uxrtrn );
}


/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_pushButton3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	Pixel Colore,PixColor;
	char *Str,*brate;
	Boolean Fatto,Result;
	char strOut[40];
	double blink_rate;
	
	Str = (char *)XmTextFieldGetString (TextNomeColore);
	Result = CvtStrToPixel (ButtNomeColore,Str,&PixColor);
	set_something (ButtNomeColore, XmNbackground, (void*) PixColor);
	brate = (char *)XmTextFieldGetString (blink_frequency);
	
	blink_rate = atof(brate);
	
	if( blink_rate > 0)
	   sprintf(strOut,"%s %s %d",Str,brate,transparent);
	else
	   sprintf(strOut,"%s",Str);
	
	/*
	printf( "strOut %s\n",strOut);
	*/
	
	if (flagINP == EDITOR_VER)
		{
		XmTextFieldSetString (FigliRC[2], strOut);
		Fatto = CvtStrToPixel (FigliRC[4],Str,&Colore);
		if (Fatto)
		  set_something (FigliRC[4],XmNbackground,(void*) Colore);
		}
	else if (flagINP == CONFIG_VER)
		XmTextFieldSetString (FigliRC[1], Str);
		
	XtFree (Str);
	XtFree (brate);
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_pushButton4( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	if (flagINP == EDITOR_VER)
		{
		/*  Ritorna a sensitive il pushbutton e il textfield chiamante  */
		set_something (FigliRC[0], XmNsensitive, (void*) True);
		set_something (FigliRC[2], XmNsensitive, (void*) True);
		}
	
	XtDestroyWidget (ColorViewer);
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_pushButton2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	int i,j;
	Boolean Fatto;
	Pixel Colore,Punto;
	char StrPix[15],*vstring;
	char *brate;
	char strOut[40];
	XColor Pix;
	double blink_rate;
	
	if (flagINP == DRAW_VER)
		{
		Fatto = False;
		j = 0;
		i = 0;
		while (Fatto==False)
			{
			get_something (VettoreBottoni[j], XmNbackground, (void*) &Punto); 
			set_something (FigliRC[i],XmNbackground, (void*) Punto);
			j++;
			i++;
			if (i==12)
				{
				j=0;
				i=16;
				}
			if (i==28) Fatto=True;
			}
		}			
	else if (flagINP == EDITOR_VER)
		{
		set_something (FigliRC[0], XmNsensitive, (void*) True);
		set_something (FigliRC[2], XmNsensitive, (void*) True);
		vstring = (char *)XmTextFieldGetString (TextNomeColore);
		Fatto = CvtStrToPixel (FigliRC[4],vstring, &Colore);
		if (Fatto)
			set_something (FigliRC[4],XmNbackground,(void*) Colore);
	
	        brate = (char *)XmTextFieldGetString (blink_frequency);
	
	        blink_rate = atof(brate);
	      
	        if( blink_rate > 0)
	           sprintf(strOut,"%s %s %d",vstring,brate,transparent);
	        else
	           sprintf(strOut,"%s",vstring);
	/* 
	        printf("strOut = %s\n",strOut);
	*/
	
		XmTextFieldSetString (FigliRC[2], strOut);
		XtFree (vstring);
	        XtFree( brate );
		}
	else if (flagINP == CONFIG_VER)
		{
		set_something (FigliRC[0], XmNsensitive, (void*) True);
		set_something (FigliRC[1], XmNsensitive, (void*) True);
		vstring = (char *)XmTextFieldGetString (TextNomeColore);
		XmTextFieldSetString (FigliRC[1], vstring);
		XtFree (vstring);
		}
	
	/*  Setta i background della palette di default nel database  */
	
	for (i=0;i<12;i++)
		{
		get_something (VettoreBottoni[i] , XmNbackground, (void*) &Pix.pixel);
		XQueryColor (UxDisplay, Cmap, &Pix);
		sprintf (StrPix,"#%04x%04x%04x",Pix.red,Pix.green,Pix.blue);
		XlSetResourceByWidget (&RisDbColori,VettoreBottoni[i],
						XmNbackground,StrPix);
		}
	
	XrmPutFileDatabase (RisDbColori,"FileColoriDefault");
	XtDestroyWidget (ColorViewer);
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_drawnButton12( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	XColor ColoreSfondo;
	char vstring[40];
	Pixel Pal;
	
	if (Press == 12)
		{
		get_something (ButtNomeColore, XmNbackground, (void*) &Pal);
		set_something (VettoreBottoni[11], XmNbackground, (void*) Pal);
		}
	else
		{
		Press = 12;
		RilasciaDrawnButton (11);
	
		get_something (VettoreBottoni[11], XmNbackground, (void*) &ColoreSfondo.pixel);
	
		set_something (ButtNomeColore, XmNbackground, (void*) ColoreSfondo.pixel);
		XQueryColor (UxDisplay, Cmap, &ColoreSfondo);
		sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,
					ColoreSfondo.blue);
		set_something (TextNomeColore, XmNvalue, (void*) vstring);
		}
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_drawnButton6( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	XColor ColoreSfondo;
	char vstring[40];
	Pixel Pal;
	
	if (Press == 6)
		{
		get_something (ButtNomeColore, XmNbackground, (void*) &Pal);
		set_something (VettoreBottoni[5], XmNbackground, (void*) Pal);
		}
	else
		{
		Press = 6;
		RilasciaDrawnButton (5);
		get_something (VettoreBottoni[5], XmNbackground, (void*) &ColoreSfondo.pixel);
	
		set_something (ButtNomeColore, XmNbackground, (void*) ColoreSfondo.pixel);
		XQueryColor (UxDisplay, Cmap, &ColoreSfondo);
		sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,
					ColoreSfondo.blue);
		set_something (TextNomeColore, XmNvalue, (void*) vstring);
		}
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_drawnButton11( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	XColor ColoreSfondo;
	char vstring[40];
	Pixel Pal;
	
	if (Press == 11)
		{
		get_something (ButtNomeColore, XmNbackground, (void*) &Pal);
		set_something (VettoreBottoni[10], XmNbackground, (void*) Pal);
		}
	else
		{
		Press = 11;
		RilasciaDrawnButton (10);
	
		get_something (VettoreBottoni[10], XmNbackground, (void*) &ColoreSfondo.pixel);
	
		set_something (ButtNomeColore, XmNbackground, (void*) ColoreSfondo.pixel);
		XQueryColor (UxDisplay, Cmap, &ColoreSfondo);
		sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,
					ColoreSfondo.blue);
		set_something (TextNomeColore, XmNvalue, (void*) vstring);
		}
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_drawnButton5( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	XColor ColoreSfondo;
	char vstring[40];
	Pixel Pal;
	
	if (Press == 5)
		{
		get_something (ButtNomeColore, XmNbackground, (void*) &Pal);
		set_something (VettoreBottoni[4], XmNbackground, (void*) Pal);
		}
	else
		{
		Press = 5;
		RilasciaDrawnButton (4);
		get_something (VettoreBottoni[4], XmNbackground, (void*) &ColoreSfondo.pixel);
	
		set_something (ButtNomeColore, XmNbackground, (void*) ColoreSfondo.pixel);
		XQueryColor (UxDisplay, Cmap, &ColoreSfondo);
		sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,
					ColoreSfondo.blue);
		set_something (TextNomeColore, XmNvalue, (void*) vstring);
		}
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_drawnButton10( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	XColor ColoreSfondo;
	char vstring[40];
	Pixel Pal;
	
	if (Press == 10)
		{
		get_something (ButtNomeColore, XmNbackground, (void*) &Pal);
		set_something (VettoreBottoni[9], XmNbackground, (void*) Pal);
		}
	else
		{
		Press = 10;
		RilasciaDrawnButton (9);
	
		get_something (VettoreBottoni[9], XmNbackground, (void*) &ColoreSfondo.pixel);
	
		set_something (ButtNomeColore, XmNbackground, (void*) ColoreSfondo.pixel);
		XQueryColor (UxDisplay, Cmap, &ColoreSfondo);
		sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,
					ColoreSfondo.blue);
		set_something (TextNomeColore, XmNvalue, (void*) vstring);
		}
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_drawnButton9( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	XColor ColoreSfondo;
	char vstring[40];
	Pixel Pal;
	
	if (Press == 9)
		{
		get_something (ButtNomeColore, XmNbackground, (void*) &Pal);
		set_something (VettoreBottoni[8], XmNbackground, (void*) Pal);
		}
	else
		{
		Press = 9;
		RilasciaDrawnButton (8);
		get_something (VettoreBottoni[8], XmNbackground, (void*) &ColoreSfondo.pixel);
	
		set_something (ButtNomeColore, XmNbackground, (void*) ColoreSfondo.pixel);
		XQueryColor (UxDisplay, Cmap, &ColoreSfondo);
		sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,
					ColoreSfondo.blue);
		set_something (TextNomeColore, XmNvalue, (void*) vstring);
		}
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_drawnButton8( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	XColor ColoreSfondo;
	char vstring[40];
	Pixel Pal;
	
	if (Press == 8)
		{
		get_something (ButtNomeColore, XmNbackground, (void*) &Pal);
		set_something (VettoreBottoni[7], XmNbackground, (void*) Pal);
		}
	else
		{
		Press = 8;
		RilasciaDrawnButton (7);
		get_something (VettoreBottoni[7], XmNbackground, (void*) &ColoreSfondo.pixel);
	
		set_something (ButtNomeColore, XmNbackground, (void*) ColoreSfondo.pixel);
		XQueryColor (UxDisplay, Cmap, &ColoreSfondo);
		sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,
					ColoreSfondo.blue);
		set_something (TextNomeColore, XmNvalue, (void*) vstring);
		}
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_drawnButton7( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	XColor ColoreSfondo;
	char vstring[40];
	Pixel Pal;
	
	if (Press == 7)
		{
		get_something (ButtNomeColore, XmNbackground, (void*) &Pal);
		set_something (VettoreBottoni[6], XmNbackground, (void*) Pal);
		}
	else
		{
		Press = 7;
		RilasciaDrawnButton (6);
		get_something (VettoreBottoni[6], XmNbackground, (void*) &ColoreSfondo.pixel);
	
		set_something (ButtNomeColore, XmNbackground, (void*) ColoreSfondo.pixel);
		XQueryColor (UxDisplay, Cmap, &ColoreSfondo);
		sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,
					ColoreSfondo.blue);
		set_something (TextNomeColore, XmNvalue, (void*) vstring);
		}
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_drawnButton4( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	XColor ColoreSfondo;
	char vstring[40];
	Pixel Pal;
	
	if (Press == 4)
		{
		get_something (ButtNomeColore, XmNbackground, (void*) &Pal);
		set_something (VettoreBottoni[3], XmNbackground, (void*) Pal);
		}
	else
		{
		Press = 4;
		RilasciaDrawnButton (3);
		get_something (VettoreBottoni[3], XmNbackground, (void*) &ColoreSfondo.pixel);
	
		set_something (ButtNomeColore, XmNbackground, (void*) ColoreSfondo.pixel);
		XQueryColor (UxDisplay, Cmap, &ColoreSfondo);
		sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,
					ColoreSfondo.blue);
		set_something (TextNomeColore, XmNvalue, (void*) vstring);
		}
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_drawnButton3( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	XColor ColoreSfondo;
	char vstring[40];
	Pixel Pal;
	
	if (Press == 3)
		{
		get_something (ButtNomeColore, XmNbackground, (void*) &Pal);
		set_something (VettoreBottoni[2], XmNbackground, (void*) Pal);
		}
	else
		{
		Press = 3;
		RilasciaDrawnButton (2);
	
		get_something (VettoreBottoni[2], XmNbackground, (void*) &ColoreSfondo.pixel);
	 
		set_something (ButtNomeColore, XmNbackground, (void*) ColoreSfondo.pixel);
		XQueryColor (UxDisplay, Cmap, &ColoreSfondo);
		sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,
					ColoreSfondo.blue);
		set_something (TextNomeColore, XmNvalue, (void*) vstring);
		}
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_drawnButton2( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	XColor ColoreSfondo;
	char vstring[40];
	Pixel Pal;
	
	if (Press == 2)
		{
		get_something (ButtNomeColore, XmNbackground, (void*) &Pal);
		set_something (VettoreBottoni[1], XmNbackground, (void*) Pal);
		}
	else
		{
		Press = 2;
		RilasciaDrawnButton (1);
		get_something (VettoreBottoni[1], XmNbackground, (void*) &ColoreSfondo.pixel);
	
		set_something (ButtNomeColore, XmNbackground, (void*) ColoreSfondo.pixel);
		XQueryColor (UxDisplay, Cmap, &ColoreSfondo);
		sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,
					ColoreSfondo.blue);
		set_something (TextNomeColore, XmNvalue, (void*) vstring);
		}
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_drawnButton1( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	XColor ColoreSfondo;
	Pixel Pal;
	char vstring[40];
	
	if (Press == 1)
		{
		get_something (ButtNomeColore, XmNbackground, (void*) &Pal);
		set_something (VettoreBottoni[0], XmNbackground, (void*) Pal);
		}
	else
		{
		Press = 1;
		RilasciaDrawnButton (0);
	
		get_something (VettoreBottoni[0], XmNbackground, (void*) &ColoreSfondo.pixel);
		set_something (ButtNomeColore, XmNbackground, (void*) ColoreSfondo.pixel);
		XQueryColor (UxDisplay, Cmap, &ColoreSfondo);
		sprintf (vstring,"#%04x%04x%04x",ColoreSfondo.red,ColoreSfondo.green,
					ColoreSfondo.blue);
		set_something (TextNomeColore, XmNvalue, (void*) vstring);
		}
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_transparentNo( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	transparent = False;
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_transparentYes( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	transparent = True;
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_EditItem( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	Pixel Colore;
	Widget Creato;
	
	get_something (ButtNomeColore, XmNbackground, (void*) &Colore);
	
	Creato = (Widget )create_ColorEditor(&Colore,TextNomeColore,ColorViewer);
	UxPopupInterface (Creato , no_grab);
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_GrabItem( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	Colormap cmap;
	XImage *Immagine;
	XEvent report;
	int cicla;
	XColor Pix;
	char Str[15];
	
	cicla = 1;
	cmap = DefaultColormap (UxDisplay, DefaultScreen (UxDisplay) );
	
	/*  Ciclo di attivazione della lettura della pressione del bottone del mouse */
	while ( cicla )
		{
		XNextEvent (UxDisplay, &report);
		switch (report.type)
			{
			case Expose:
				XtDispatchEvent (&report);
			break;
			case ButtonPress:
				/*  Crea l'immagine del punto dove e stato premuto 
					il bottone del mouse  */
				Immagine = XGetImage (UxDisplay, report.xbutton.window,
					report.xbutton.x,report.xbutton.y,1,1,
					AllPlanes,XYPixmap);
				/*  Se e' stata caricata l'immagine prende il pixel 
					del punto dove e' avvenuta la pressione
					del bottone del mouse   */
				if (Immagine == NULL)
					printf ("Image non caricata!!\n");
				else
					{
					Pix.pixel = XGetPixel (Immagine,0,0);
					/*  Setta il pixel come sfondo del bottone */
					set_something (ButtNomeColore,XmNbackground, (void*) Pix.pixel);
					/*  Trova le informazioni RGB relative al pixel */
					XQueryColor (UxDisplay, cmap, &Pix);
					/*  Crea la stringa con il nome del colore  */
					sprintf (Str,"#%04x%04x%04x",Pix.red,Pix.green,
						Pix.blue);
					XmTextFieldSetString (TextNomeColore,Str);
					cicla = 0;
					}
			break;
			}
		}
	}
	UxColorViewerContext = UxSaveCtx;
}

static	void	activateCB_ColorItem( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCColorViewer         *UxSaveCtx, *UxContext;

	UxSaveCtx = UxColorViewerContext;
	UxColorViewerContext = UxContext =
			(_UxCColorViewer *) UxGetContext( UxWidget );
	{
	Widget Creato;
	
	Creato = (Widget)create_ColorMapViewer(ColorViewer);
	UxPopupInterface (Creato ,no_grab);
	}
	UxColorViewerContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_ColorViewer()
{
	Widget		_UxParent;
	Widget		transparentPane_shell;
	Widget		EditColorPane_shell;


	/* Creation of ColorViewer */
	_UxParent = ChiamCol;
	if ( _UxParent == NULL )
	{
		_UxParent = UxTopLevel;
	}

	ColorViewer = XtVaCreatePopupShell( "ColorViewer",
			topLevelShellWidgetClass,
			_UxParent,
			XmNx, 583,
			XmNy, 15,
			XmNwidth, 420,
			XmNheight, 400,
			XmNiconName, "Color Viewer",
			XmNtitle, "Resource Color Viewer",
			XmNallowShellResize, FALSE,
			NULL );
	UxPutContext( ColorViewer, (char *) UxColorViewerContext );


	/* Creation of mainWindow2 */
	mainWindow2 = XtVaCreateManagedWidget( "mainWindow2",
			xmMainWindowWidgetClass,
			ColorViewer,
			XmNunitType, XmPIXELS,
			XmNx, 0,
			XmNy, 0,
			XmNwidth, 405,
			XmNheight, 360,
			NULL );
	UxPutContext( mainWindow2, (char *) UxColorViewerContext );


	/* Creation of form3 */
	form3 = XtVaCreateManagedWidget( "form3",
			xmFormWidgetClass,
			mainWindow2,
			XmNresizePolicy, XmRESIZE_ANY,
			NULL );
	UxPutContext( form3, (char *) UxColorViewerContext );


	/* Creation of label2 */
	label2 = XtVaCreateManagedWidget( "label2",
			xmLabelWidgetClass,
			form3,
			XmNx, 10,
			XmNy, 5,
			XmNwidth, 110,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "Defaults:" ),
			XmNtopOffset, 0,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 12,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 5,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 30,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopPosition, 2,
			NULL );
	UxPutContext( label2, (char *) UxColorViewerContext );


	/* Creation of pushButton3 */
	pushButton3 = XtVaCreateManagedWidget( "pushButton3",
			xmPushButtonWidgetClass,
			form3,
			XmNx, 110,
			XmNy, 255,
			XmNwidth, 85,
			XmNheight, 35,
			RES_CONVERT( XmNlabelString, "APPLY" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNbottomPosition, 96,
			XmNtopPosition, 83,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 25,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 45,
			NULL );
	XtAddCallback( pushButton3, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton3,
		(XtPointer) UxColorViewerContext );

	UxPutContext( pushButton3, (char *) UxColorViewerContext );


	/* Creation of pushButton4 */
	pushButton4 = XtVaCreateManagedWidget( "pushButton4",
			xmPushButtonWidgetClass,
			form3,
			XmNx, 205,
			XmNy, 255,
			XmNwidth, 85,
			XmNheight, 35,
			RES_CONVERT( XmNlabelString, "CANCEL" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNbottomPosition, 96,
			XmNtopPosition, 83,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 47,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 67,
			NULL );
	XtAddCallback( pushButton4, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton4,
		(XtPointer) UxColorViewerContext );

	UxPutContext( pushButton4, (char *) UxColorViewerContext );


	/* Creation of pushButton2 */
	pushButton2 = XtVaCreateManagedWidget( "pushButton2",
			xmPushButtonWidgetClass,
			form3,
			XmNx, 15,
			XmNy, 255,
			XmNwidth, 85,
			XmNheight, 35,
			RES_CONVERT( XmNlabelString, "OK" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNbottomPosition, 96,
			XmNtopPosition, 83,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 3,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 23,
			NULL );
	XtAddCallback( pushButton2, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton2,
		(XtPointer) UxColorViewerContext );

	UxPutContext( pushButton2, (char *) UxColorViewerContext );


	/* Creation of separator3 */
	separator3 = XtVaCreateManagedWidget( "separator3",
			xmSeparatorWidgetClass,
			form3,
			XmNx, 5,
			XmNy, 235,
			XmNwidth, 395,
			XmNheight, 15,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNleftPosition, 1,
			XmNrightPosition, 99,
			XmNbottomPosition, 83,
			XmNtopPosition, 80,
			NULL );
	UxPutContext( separator3, (char *) UxColorViewerContext );


	/* Creation of ButtNomeColore */
	ButtNomeColore = XtVaCreateManagedWidget( "ButtNomeColore",
			xmDrawnButtonWidgetClass,
			form3,
			XmNx, 15,
			XmNy, 196,
			XmNwidth, 140,
			XmNheight, 44,
			XmNleftAttachment, XmATTACH_FORM,
			XmNleftOffset, 15,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNsensitive, FALSE,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNbottomPosition, 63,
			XmNtopPosition, 53,
			NULL );
	UxPutContext( ButtNomeColore, (char *) UxColorViewerContext );


	/* Creation of TextNomeColore */
	TextNomeColore = XtVaCreateManagedWidget( "TextNomeColore",
			xmTextFieldWidgetClass,
			form3,
			XmNx, 165,
			XmNy, 185,
			XmNwidth, 225,
			XmNheight, 45,
			XmNmaxLength, 50,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 10,
			XmNleftWidget, ButtNomeColore,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 15,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNbottomPosition, 63,
			XmNtopPosition, 53,
			NULL );
	UxPutContext( TextNomeColore, (char *) UxColorViewerContext );


	/* Creation of separator2 */
	separator2 = XtVaCreateManagedWidget( "separator2",
			xmSeparatorWidgetClass,
			form3,
			XmNx, 0,
			XmNy, 150,
			XmNwidth, 380,
			XmNheight, 20,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNleftPosition, 1,
			XmNrightPosition, 99,
			XmNbottomPosition, 52,
			XmNtopPosition, 50,
			NULL );
	UxPutContext( separator2, (char *) UxColorViewerContext );


	/* Creation of label3 */
	label3 = XtVaCreateManagedWidget( "label3",
			xmLabelWidgetClass,
			form3,
			XmNx, 5,
			XmNy, 125,
			XmNwidth, 120,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "Resource name:" ),
			XmNalignment, XmALIGNMENT_END,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNbottomPosition, 50,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 5,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 35,
			XmNtopPosition, 35,
			NULL );
	UxPutContext( label3, (char *) UxColorViewerContext );


	/* Creation of separator1 */
	separator1 = XtVaCreateManagedWidget( "separator1",
			xmSeparatorWidgetClass,
			form3,
			XmNx, 10,
			XmNy, 100,
			XmNwidth, 380,
			XmNheight, 20,
			XmNleftOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNresizable, FALSE,
			XmNbottomPosition, 33,
			XmNleftPosition, 1,
			XmNrightPosition, 99,
			XmNtopPosition, 30,
			NULL );
	UxPutContext( separator1, (char *) UxColorViewerContext );


	/* Creation of labelColorRes */
	labelColorRes = XtVaCreateManagedWidget( "labelColorRes",
			xmLabelWidgetClass,
			form3,
			XmNx, 135,
			XmNy, 95,
			XmNwidth, 250,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "" ),
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopWidget, NULL,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftWidget, NULL,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNalignment, XmALIGNMENT_CENTER,
			XmNbottomPosition, 50,
			XmNleftPosition, 36,
			XmNrightPosition, 97,
			XmNtopPosition, 35,
			NULL );
	UxPutContext( labelColorRes, (char *) UxColorViewerContext );


	/* Creation of drawnButton12 */
	drawnButton12 = XtVaCreateManagedWidget( "drawnButton12",
			xmDrawnButtonWidgetClass,
			form3,
			XmNwidth, 60,
			XmNheight, 20,
			XmNhighlightOnEnter, TRUE,
			XmNpushButtonEnabled, FALSE,
			XmNhighlightThickness, 2,
			XmNshadowType, XmSHADOW_ETCHED_IN,
			XmNshadowThickness, 2,
			XmNrecomputeSize, FALSE,
			XmNx, 240,
			XmNy, 70,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNresizable, FALSE,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNbottomPosition, 28,
			XmNtopPosition, 22,
			XmNleftPosition, 83,
			XmNrightPosition, 97,
			NULL );
	XtAddCallback( drawnButton12, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButton12,
		(XtPointer) UxColorViewerContext );

	UxPutContext( drawnButton12, (char *) UxColorViewerContext );


	/* Creation of drawnButton6 */
	drawnButton6 = XtVaCreateManagedWidget( "drawnButton6",
			xmDrawnButtonWidgetClass,
			form3,
			XmNwidth, 60,
			XmNheight, 20,
			XmNhighlightOnEnter, TRUE,
			XmNpushButtonEnabled, FALSE,
			XmNhighlightThickness, 2,
			XmNshadowType, XmSHADOW_ETCHED_IN,
			XmNshadowThickness, 2,
			XmNrecomputeSize, FALSE,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, drawnButton12,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNtopOffset, 0,
			XmNresizable, FALSE,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightWidget, NULL,
			XmNbottomPosition, 21,
			XmNtopPosition, 15,
			XmNleftPosition, 83,
			XmNrightPosition, 97,
			NULL );
	XtAddCallback( drawnButton6, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButton6,
		(XtPointer) UxColorViewerContext );

	UxPutContext( drawnButton6, (char *) UxColorViewerContext );


	/* Creation of drawnButton11 */
	drawnButton11 = XtVaCreateManagedWidget( "drawnButton11",
			xmDrawnButtonWidgetClass,
			form3,
			XmNwidth, 60,
			XmNheight, 20,
			XmNhighlightOnEnter, TRUE,
			XmNpushButtonEnabled, FALSE,
			XmNhighlightThickness, 2,
			XmNshadowType, XmSHADOW_ETCHED_IN,
			XmNshadowThickness, 2,
			XmNrecomputeSize, FALSE,
			XmNx, 220,
			XmNy, 80,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNresizable, FALSE,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNrightWidget, drawnButton12,
			XmNbottomPosition, 28,
			XmNtopPosition, 22,
			XmNleftPosition, 67,
			XmNrightPosition, 81,
			NULL );
	XtAddCallback( drawnButton11, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButton11,
		(XtPointer) UxColorViewerContext );

	UxPutContext( drawnButton11, (char *) UxColorViewerContext );


	/* Creation of drawnButton5 */
	drawnButton5 = XtVaCreateManagedWidget( "drawnButton5",
			xmDrawnButtonWidgetClass,
			form3,
			XmNwidth, 60,
			XmNheight, 20,
			XmNhighlightOnEnter, TRUE,
			XmNpushButtonEnabled, FALSE,
			XmNhighlightThickness, 2,
			XmNshadowType, XmSHADOW_ETCHED_IN,
			XmNshadowThickness, 2,
			XmNrecomputeSize, FALSE,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, drawnButton11,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNresizable, FALSE,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightWidget, drawnButton6,
			XmNbottomPosition, 21,
			XmNtopPosition, 15,
			XmNleftPosition, 67,
			XmNrightPosition, 81,
			NULL );
	XtAddCallback( drawnButton5, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButton5,
		(XtPointer) UxColorViewerContext );

	UxPutContext( drawnButton5, (char *) UxColorViewerContext );


	/* Creation of drawnButton10 */
	drawnButton10 = XtVaCreateManagedWidget( "drawnButton10",
			xmDrawnButtonWidgetClass,
			form3,
			XmNwidth, 60,
			XmNheight, 20,
			XmNhighlightOnEnter, TRUE,
			XmNpushButtonEnabled, FALSE,
			XmNhighlightThickness, 2,
			XmNshadowType, XmSHADOW_ETCHED_IN,
			XmNshadowThickness, 2,
			XmNrecomputeSize, FALSE,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNrightWidget, drawnButton11,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNresizable, FALSE,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNbottomPosition, 28,
			XmNtopPosition, 22,
			XmNleftPosition, 51,
			XmNrightPosition, 65,
			NULL );
	XtAddCallback( drawnButton10, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButton10,
		(XtPointer) UxColorViewerContext );

	UxPutContext( drawnButton10, (char *) UxColorViewerContext );


	/* Creation of drawnButton9 */
	drawnButton9 = XtVaCreateManagedWidget( "drawnButton9",
			xmDrawnButtonWidgetClass,
			form3,
			XmNwidth, 60,
			XmNheight, 20,
			XmNhighlightOnEnter, TRUE,
			XmNpushButtonEnabled, FALSE,
			XmNhighlightThickness, 2,
			XmNshadowType, XmSHADOW_ETCHED_IN,
			XmNshadowThickness, 2,
			XmNrecomputeSize, FALSE,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNrightWidget, drawnButton10,
			XmNresizable, FALSE,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNleftOffset, 0,
			XmNbottomPosition, 28,
			XmNtopPosition, 22,
			XmNleftPosition, 35,
			XmNrightPosition, 49,
			NULL );
	XtAddCallback( drawnButton9, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButton9,
		(XtPointer) UxColorViewerContext );

	UxPutContext( drawnButton9, (char *) UxColorViewerContext );


	/* Creation of drawnButton8 */
	drawnButton8 = XtVaCreateManagedWidget( "drawnButton8",
			xmDrawnButtonWidgetClass,
			form3,
			XmNwidth, 60,
			XmNheight, 20,
			XmNhighlightOnEnter, TRUE,
			XmNpushButtonEnabled, FALSE,
			XmNhighlightThickness, 2,
			XmNshadowType, XmSHADOW_ETCHED_IN,
			XmNshadowThickness, 2,
			XmNrecomputeSize, FALSE,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNrightWidget, drawnButton9,
			XmNresizable, FALSE,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNleftOffset, 0,
			XmNbottomPosition, 28,
			XmNtopPosition, 22,
			XmNleftPosition, 19,
			XmNrightPosition, 33,
			NULL );
	XtAddCallback( drawnButton8, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButton8,
		(XtPointer) UxColorViewerContext );

	UxPutContext( drawnButton8, (char *) UxColorViewerContext );


	/* Creation of drawnButton7 */
	drawnButton7 = XtVaCreateManagedWidget( "drawnButton7",
			xmDrawnButtonWidgetClass,
			form3,
			XmNwidth, 60,
			XmNheight, 20,
			XmNhighlightOnEnter, TRUE,
			XmNpushButtonEnabled, FALSE,
			XmNhighlightThickness, 2,
			XmNshadowType, XmSHADOW_ETCHED_IN,
			XmNshadowThickness, 2,
			XmNrecomputeSize, FALSE,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, NULL,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNrightWidget, drawnButton8,
			XmNresizable, FALSE,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNleftOffset, 0,
			XmNbottomPosition, 28,
			XmNtopPosition, 22,
			XmNleftPosition, 3,
			XmNrightPosition, 17,
			NULL );
	XtAddCallback( drawnButton7, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButton7,
		(XtPointer) UxColorViewerContext );

	UxPutContext( drawnButton7, (char *) UxColorViewerContext );


	/* Creation of drawnButton4 */
	drawnButton4 = XtVaCreateManagedWidget( "drawnButton4",
			xmDrawnButtonWidgetClass,
			form3,
			XmNwidth, 60,
			XmNheight, 20,
			XmNhighlightOnEnter, TRUE,
			XmNpushButtonEnabled, FALSE,
			XmNhighlightThickness, 2,
			XmNshadowType, XmSHADOW_ETCHED_IN,
			XmNshadowThickness, 2,
			XmNrecomputeSize, FALSE,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNrightWidget, drawnButton5,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, drawnButton10,
			XmNresizable, FALSE,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNbottomPosition, 21,
			XmNtopPosition, 15,
			XmNleftPosition, 51,
			XmNrightPosition, 65,
			NULL );
	XtAddCallback( drawnButton4, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButton4,
		(XtPointer) UxColorViewerContext );

	UxPutContext( drawnButton4, (char *) UxColorViewerContext );


	/* Creation of drawnButton3 */
	drawnButton3 = XtVaCreateManagedWidget( "drawnButton3",
			xmDrawnButtonWidgetClass,
			form3,
			XmNwidth, 60,
			XmNheight, 20,
			XmNhighlightOnEnter, TRUE,
			XmNpushButtonEnabled, FALSE,
			XmNhighlightThickness, 2,
			XmNshadowType, XmSHADOW_ETCHED_IN,
			XmNshadowThickness, 2,
			XmNrecomputeSize, FALSE,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNrightWidget, drawnButton4,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, drawnButton9,
			XmNresizable, FALSE,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNbottomPosition, 21,
			XmNtopPosition, 15,
			XmNleftPosition, 35,
			XmNrightPosition, 49,
			NULL );
	XtAddCallback( drawnButton3, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButton3,
		(XtPointer) UxColorViewerContext );

	UxPutContext( drawnButton3, (char *) UxColorViewerContext );


	/* Creation of drawnButton2 */
	drawnButton2 = XtVaCreateManagedWidget( "drawnButton2",
			xmDrawnButtonWidgetClass,
			form3,
			XmNwidth, 60,
			XmNheight, 20,
			XmNhighlightOnEnter, TRUE,
			XmNpushButtonEnabled, FALSE,
			XmNhighlightThickness, 2,
			XmNshadowType, XmSHADOW_ETCHED_IN,
			XmNshadowThickness, 2,
			XmNrecomputeSize, FALSE,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, drawnButton8,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNrightWidget, drawnButton3,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNresizable, FALSE,
			XmNbottomPosition, 21,
			XmNtopPosition, 15,
			XmNleftPosition, 19,
			XmNrightPosition, 33,
			NULL );
	XtAddCallback( drawnButton2, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButton2,
		(XtPointer) UxColorViewerContext );

	UxPutContext( drawnButton2, (char *) UxColorViewerContext );


	/* Creation of drawnButton1 */
	drawnButton1 = XtVaCreateManagedWidget( "drawnButton1",
			xmDrawnButtonWidgetClass,
			form3,
			XmNwidth, 60,
			XmNheight, 20,
			XmNhighlightOnEnter, TRUE,
			XmNpushButtonEnabled, FALSE,
			XmNhighlightThickness, 2,
			XmNshadowType, XmSHADOW_ETCHED_IN,
			XmNshadowThickness, 2,
			XmNrecomputeSize, FALSE,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightOffset, 0,
			XmNrightWidget, drawnButton2,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomOffset, 0,
			XmNbottomWidget, drawnButton7,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNresizable, FALSE,
			XmNbottomPosition, 21,
			XmNtopPosition, 15,
			XmNleftPosition, 3,
			XmNrightPosition, 17,
			NULL );
	XtAddCallback( drawnButton1, XmNactivateCallback,
		(XtCallbackProc) activateCB_drawnButton1,
		(XtPointer) UxColorViewerContext );

	UxPutContext( drawnButton1, (char *) UxColorViewerContext );


	/* Creation of BlinkRate */
	BlinkRate = XtVaCreateManagedWidget( "BlinkRate",
			xmLabelWidgetClass,
			form3,
			XmNx, 15,
			XmNy, 240,
			XmNwidth, 140,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "Blink freq. (Hz):" ),
			XmNalignment, XmALIGNMENT_END,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 80,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopPosition, 71,
			NULL );
	UxPutContext( BlinkRate, (char *) UxColorViewerContext );


	/* Creation of blink_frequency */
	blink_frequency = XtVaCreateManagedWidget( "blink_frequency",
			xmTextFieldWidgetClass,
			form3,
			XmNx, 170,
			XmNy, 239,
			XmNwidth, 70,
			XmNheight, 32,
			XmNmaxLength, 50,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 80,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopPosition, 71,
			XmNleftAttachment, XmATTACH_WIDGET,
			XmNleftOffset, 10,
			XmNleftWidget, BlinkRate,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 15,
			NULL );
	UxPutContext( blink_frequency, (char *) UxColorViewerContext );


	/* Creation of transparentLabel */
	transparentLabel = XtVaCreateManagedWidget( "transparentLabel",
			xmLabelWidgetClass,
			form3,
			XmNx, 20,
			XmNy, 232,
			XmNwidth, 130,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "Transparent:" ),
			XmNalignment, XmALIGNMENT_END,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 71,
			XmNleftOffset, 15,
			XmNtopOffset, 0,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopPosition, 63,
			NULL );
	UxPutContext( transparentLabel, (char *) UxColorViewerContext );


	/* Creation of transparentPane */
	transparentPane_shell = XtVaCreatePopupShell ("transparentPane_shell",
			xmMenuShellWidgetClass, form3,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	transparentPane = XtVaCreateWidget( "transparentPane",
			xmRowColumnWidgetClass,
			transparentPane_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );
	UxPutContext( transparentPane, (char *) UxColorViewerContext );


	/* Creation of transparentNo */
	transparentNo = XtVaCreateManagedWidget( "transparentNo",
			xmPushButtonWidgetClass,
			transparentPane,
			RES_CONVERT( XmNlabelString, "No" ),
			NULL );
	XtAddCallback( transparentNo, XmNactivateCallback,
		(XtCallbackProc) activateCB_transparentNo,
		(XtPointer) UxColorViewerContext );

	UxPutContext( transparentNo, (char *) UxColorViewerContext );


	/* Creation of transparentYes */
	transparentYes = XtVaCreateManagedWidget( "transparentYes",
			xmPushButtonWidgetClass,
			transparentPane,
			RES_CONVERT( XmNlabelString, "Yes" ),
			NULL );
	XtAddCallback( transparentYes, XmNactivateCallback,
		(XtCallbackProc) activateCB_transparentYes,
		(XtPointer) UxColorViewerContext );

	UxPutContext( transparentYes, (char *) UxColorViewerContext );


	/* Creation of trasparentMenu */
	trasparentMenu = XtVaCreateManagedWidget( "trasparentMenu",
			xmRowColumnWidgetClass,
			form3,
			XmNrowColumnType, XmMENU_OPTION,
			XmNsubMenuId, transparentPane,
			XmNx, 170,
			XmNy, 230,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 71,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopPosition, 63,
			XmNrightAttachment, XmATTACH_FORM,
			XmNrightOffset, 180,
			XmNmarginHeight, 0,
			NULL );
	UxPutContext( trasparentMenu, (char *) UxColorViewerContext );


	/* Creation of menu3 */
	menu3 = XtVaCreateManagedWidget( "menu3",
			xmRowColumnWidgetClass,
			mainWindow2,
			XmNrowColumnType, XmMENU_BAR,
			XmNmenuAccelerator, "<KeyUp>F10",
			NULL );
	UxPutContext( menu3, (char *) UxColorViewerContext );


	/* Creation of EditColorPane */
	EditColorPane_shell = XtVaCreatePopupShell ("EditColorPane_shell",
			xmMenuShellWidgetClass, menu3,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	EditColorPane = XtVaCreateWidget( "EditColorPane",
			xmRowColumnWidgetClass,
			EditColorPane_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			NULL );
	UxPutContext( EditColorPane, (char *) UxColorViewerContext );


	/* Creation of EditItem */
	EditItem = XtVaCreateManagedWidget( "EditItem",
			xmPushButtonWidgetClass,
			EditColorPane,
			RES_CONVERT( XmNlabelString, "Edit Color" ),
			RES_CONVERT( XmNmnemonic, "E" ),
			NULL );
	XtAddCallback( EditItem, XmNactivateCallback,
		(XtCallbackProc) activateCB_EditItem,
		(XtPointer) UxColorViewerContext );

	UxPutContext( EditItem, (char *) UxColorViewerContext );


	/* Creation of GrabItem */
	GrabItem = XtVaCreateManagedWidget( "GrabItem",
			xmPushButtonWidgetClass,
			EditColorPane,
			RES_CONVERT( XmNlabelString, "Grab Color" ),
			RES_CONVERT( XmNmnemonic, "G" ),
			NULL );
	XtAddCallback( GrabItem, XmNactivateCallback,
		(XtCallbackProc) activateCB_GrabItem,
		(XtPointer) UxColorViewerContext );

	UxPutContext( GrabItem, (char *) UxColorViewerContext );


	/* Creation of ColorItem */
	ColorItem = XtVaCreateManagedWidget( "ColorItem",
			xmPushButtonWidgetClass,
			EditColorPane,
			RES_CONVERT( XmNlabelString, "Color Map" ),
			RES_CONVERT( XmNmnemonic, "C" ),
			NULL );
	XtAddCallback( ColorItem, XmNactivateCallback,
		(XtCallbackProc) activateCB_ColorItem,
		(XtPointer) UxColorViewerContext );

	UxPutContext( ColorItem, (char *) UxColorViewerContext );


	/* Creation of menu3_top_b1 */
	menu3_top_b1 = XtVaCreateManagedWidget( "menu3_top_b1",
			xmCascadeButtonWidgetClass,
			menu3,
			RES_CONVERT( XmNlabelString, "Edit" ),
			RES_CONVERT( XmNmnemonic, "E" ),
			XmNsubMenuId, EditColorPane,
			NULL );
	UxPutContext( menu3_top_b1, (char *) UxColorViewerContext );

	XtVaSetValues(BlinkRate,
			RES_CONVERT( XmNlabelInsensitivePixmap, "/usr/include/X11/bitmaps/dimple1" ),
			NULL );

	XtVaSetValues(transparentLabel,
			RES_CONVERT( XmNlabelInsensitivePixmap, "/usr/include/X11/bitmaps/dimple1" ),
			NULL );


	XtAddCallback( ColorViewer, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxColorViewerContext);

	XmMainWindowSetAreas( mainWindow2, menu3, (Widget) NULL,
			(Widget) NULL, (Widget) NULL, form3 );

	return ( ColorViewer );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_ColorViewer( _UxFlag, _UxStrInput, _UxLabButt, _UxPdb, _UxFigliINP, _UxChiamCol )
	int	_UxFlag;
	unsigned char	*_UxStrInput;
	XmString	_UxLabButt;
	XrmDatabase	_UxPdb;
	Widget	*_UxFigliINP;
	Widget	_UxChiamCol;
{
	Widget                  rtrn;
	_UxCColorViewer         *UxContext;
	static int		_Uxinit = 0;

	UxColorViewerContext = UxContext =
		(_UxCColorViewer *) UxNewContext( sizeof(_UxCColorViewer), False );

	Flag = _UxFlag;
	StrInput = _UxStrInput;
	LabButt = _UxLabButt;
	Pdb = _UxPdb;
	FigliINP = _UxFigliINP;
	ChiamCol = _UxChiamCol;

	if ( ! _Uxinit )
	{
		_UxIfClassId = UxNewClassId();
		UxColorViewer_disableBlinkRate_Id = UxMethodRegister( _UxIfClassId,
					UxColorViewer_disableBlinkRate_Name,
					_ColorViewer_disableBlinkRate );
		UxColorViewer_displayBlinkRate_Id = UxMethodRegister( _UxIfClassId,
					UxColorViewer_displayBlinkRate_Name,
					_ColorViewer_displayBlinkRate );
		UxColorViewer_enableBlinkRate_Id = UxMethodRegister( _UxIfClassId,
					UxColorViewer_enableBlinkRate_Name,
					_ColorViewer_enableBlinkRate );
		_Uxinit = 1;
	}

	{
		Pixel PixColor;
		Boolean Result;
		int nStrRead=0;
		
		flagINP = Flag;
		FigliRC = FigliINP;
		RisDbColori = XrmGetFileDatabase("FileColoriDefault");
		XrmSetDatabase (UxDisplay,RisDbColori);
		
		Press  = 0;
		Cmap = DefaultColormap (UxDisplay, DefaultScreen (UxDisplay) );
		
		strcpy(StrColor,"");
		blinkFreq=0;
		nStrRead = sscanf(StrInput,"%s %f %d",StrColor,&blinkFreq,&transparent);
		
		printf("nStrRead = %d\n",nStrRead);
		
		if( nStrRead < 1)
		{
		   printf("Invalid input string");
		   blinkFreq = 0;
		   transparent = 0;
		}
		else if( nStrRead == 1)
		{
		   blinkFreq = 0;
		   transparent = 0;
		}
		
		/*
		printf("color %s  blink (Hz) %f transparent=%d\n",StrColor,blinkFreq,transparent);
		*/
		rtrn = _Uxbuild_ColorViewer();
		UxPutClassCode( ColorViewer, _UxIfClassId );

		if ( !CvtStrToPixel (TextNomeColore,StrColor,&PixColor) )
			set_something (EditItem,XmNsensitive,(void*) False);
		else	set_something (EditItem,XmNsensitive,(void*) True);
		
		VettoreBottoni [0] = drawnButton1;
		VettoreBottoni [1] = drawnButton2;
		VettoreBottoni [2] = drawnButton3;
		VettoreBottoni [3] = drawnButton4;
		VettoreBottoni [4] = drawnButton5;
		VettoreBottoni [5] = drawnButton6;
		VettoreBottoni [6] = drawnButton7;
		VettoreBottoni [7] = drawnButton8;
		VettoreBottoni [8] = drawnButton9;
		VettoreBottoni [9] = drawnButton10;
		VettoreBottoni[10] = drawnButton11;
		VettoreBottoni[11] = drawnButton12;
			
		XmTextFieldSetString (TextNomeColore,StrColor);
		set_something (ButtNomeColore, XmNbackground, (void*) PixColor);
		set_something (labelColorRes, XmNlabelString, (void*) LabButt);
		XrmSetDatabase (UxDisplay,Pdb);
		
		/*  Setta la posizione dell'interfaccia rispetto al Parent  */
		InterfaceSetPos (ColorViewer,ChiamCol);
		
		if (flagINP == CONFIG_VER)
		  {
		  set_something (FigliRC[0], XmNsensitive, (void*) False);
		  set_something (FigliRC[1], XmNsensitive, (void*) False);
		  }
		
		/* rendo insensitive la label e il Text Field della blink rate
		   se in origine la blink rate non era presente
		*/
		if( nStrRead >= 2)
		   ColorViewer_displayBlinkRate(ColorViewer,&UxEnv);
		else
		   ColorViewer_disableBlinkRate(ColorViewer,&UxEnv);
		
		/* set del menu trasparent in base al valore del XlAnimatedColor
		*/
		if( transparent )
		   set_something(trasparentMenu,XmNmenuHistory,(void*) transparentYes);
		else
		   set_something(trasparentMenu,XmNmenuHistory,(void*) transparentNo);
		
		
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

