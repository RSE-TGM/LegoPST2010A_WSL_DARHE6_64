
/*******************************************************************************
       PerturbEditor.c
       (Generated from interface file PerturbEditor.i)
*******************************************************************************/

#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/TextF.h>
#include <Xm/Label.h>
#include <Xm/RowColumn.h>
#include <Xm/Separator.h>
#include <Xm/PushB.h>
#include <Xm/Form.h>
#include <X11/Shell.h>

#include "libutilx.h"

/*******************************************************************************
       Includes, Defines, and Global variables from the Declarations Editor:
*******************************************************************************/

/*
        Inizio sezione per SCCS
*/
/*
   modulo PerturbEditor.i
   tipo 
   release 5.2
   data 2/6/96
   reserved @(#)PerturbEditor.i	5.2
*/
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/

#include <string.h>
#include "res_edit.h"
#include "ImpPert.h"


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
	Widget	UxPerturbEditor;
	Widget	Uxform5;
	Widget	UxpushButton15;
	Widget	UxpushButton14;
	Widget	Uxseparator7;
	Widget	UxOptionM;
	Widget	UxOptionM_shell;
	Widget	UxFittizio;
	Widget	Uxmenu2;
	Widget	Uxlabel7;
	Widget	UxtextPar1;
	Widget	UxlabPar1;
	Widget	UxtextPar2;
	Widget	UxlabPar2;
	Widget	UxVettoreLabel[3];
	Widget	UxVettoreText[3];
	unsigned char	*UxPerturbazione;
	Widget	UxTextPerturbazione;
	int	UxIndicePerturba;
	Widget	UxParent3;
	unsigned char	*UxPert;
	Widget	UxTextPert;
} _UxCPerturbEditor;

static _UxCPerturbEditor       *UxPerturbEditorContext;
#define PerturbEditor           UxPerturbEditorContext->UxPerturbEditor
#define form5                   UxPerturbEditorContext->Uxform5
#define pushButton15            UxPerturbEditorContext->UxpushButton15
#define pushButton14            UxPerturbEditorContext->UxpushButton14
#define separator7              UxPerturbEditorContext->Uxseparator7
#define OptionM                 UxPerturbEditorContext->UxOptionM
#define OptionM_shell           UxPerturbEditorContext->UxOptionM_shell
#define Fittizio                UxPerturbEditorContext->UxFittizio
#define menu2                   UxPerturbEditorContext->Uxmenu2
#define label7                  UxPerturbEditorContext->Uxlabel7
#define textPar1                UxPerturbEditorContext->UxtextPar1
#define labPar1                 UxPerturbEditorContext->UxlabPar1
#define textPar2                UxPerturbEditorContext->UxtextPar2
#define labPar2                 UxPerturbEditorContext->UxlabPar2
#define VettoreLabel            UxPerturbEditorContext->UxVettoreLabel
#define VettoreText             UxPerturbEditorContext->UxVettoreText
#define Perturbazione           UxPerturbEditorContext->UxPerturbazione
#define TextPerturbazione       UxPerturbEditorContext->UxTextPerturbazione
#define IndicePerturba          UxPerturbEditorContext->UxIndicePerturba
#define Parent3                 UxPerturbEditorContext->UxParent3
#define Pert                    UxPerturbEditorContext->UxPert
#define TextPert                UxPerturbEditorContext->UxTextPert



/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_PerturbEditor();

/*******************************************************************************
Auxiliary code from the Declarations Editor:
*******************************************************************************/

void RiazzeraParameter (Widget *Lab,Widget *TextFi)
{
XmString XmAppo;
int i;

XmAppo = XmStringCreateSimple (" ");
for (i=0;i<2;i++)
	{
	set_something (TextFi[i], XmNsensitive, (void*) False);
	XmTextFieldSetString (TextFi[i], "");
	set_something (Lab[i], XmNlabelString, (void*) XmAppo);
	}
XmStringFree (XmAppo);
}

void LeggiPerturb (char *Defi,int *Posiz,char **A,char **B)
{
int ritorno,Indice,uguali;
char *Appo,*Conf,*pConf;

Conf = XtNewString (Defi);
pConf=Conf;
Appo = XtCalloc (20,sizeof(char));
sscanf (Conf,"%s",Appo);
Conf += strlen (Appo)+1;

Indice = 0;
*Posiz = Indice;
uguali = strcmp (Appo,PerturbDefinitions[Indice]);

while ( (uguali != 0) && (Indice < (NumPert - 1)) )
        {
        Indice++;
        uguali = strcmp (Appo,PerturbDefinitions[Indice]);
        }
XtFree (Appo);

if (uguali==0)
  {
  *Posiz = Indice;
  Appo = XtCalloc (20,sizeof(char));
  if ( (sscanf(Conf,"%s",Appo)) <= 0 )
    {
    *A = XtNewString ("");
    *B = XtNewString ("");
    }
  else
    {
    Conf += strlen (Appo)+1;
    *A = XtNewString (Appo);
    XtFree (Appo);
    Appo = XtCalloc (20,sizeof(char));
    if ( (sscanf (Conf,"%s",Appo)) <= 0)
      *B = XtNewString ("");
    else *B = XtNewString (Appo);
    XtFree (Appo);
    }
  }
else
  {
  *A = XtNewString ("");
  *B = XtNewString ("");
  }
XtFree (pConf);
}

int InizializzaParameter (Widget *Lab,Widget *TextF,char *Definiz)
{
int j,i,RigheLette;
int Posizione;
char *Par1,*Par2;
XmString XmLab;

if (Definiz[0] != '\0')
        {
	LeggiPerturb (Definiz,&Posizione,&Par1,&Par2);
        }
else
	{
	Posizione = 0;
	Par1 = XtNewString ("");
	Par2 = XtNewString ("");
	}

RigheLette = 0;
i=0;
while (RigheLette != Posizione )
	{
	if (strcmp (EditorDefinitions[i],"NULL") == 0)
		RigheLette++;
	i++;
	}

j = 0;
while (strcmp (EditorDefinitions[i],"NULL"))
	{
	XmLab = XmStringCreateSimple (EditorDefinitions[i]);
	set_something (Lab[j], XmNlabelString, (void*) XmLab);
	set_something (TextF[j], XmNsensitive, (void*) True);
	XmStringFree (XmLab);
	i++;
	j++;
	}

XmTextFieldSetString (TextF[0], Par1);
XmTextFieldSetString (TextF[1], Par2);

XtFree (Par1);
XtFree (Par2);
return (Posizione);
}

void ImpostaParameter (Widget *Lab,Widget *TextF,int Posizione)
{
int j,i,RigheLette,RigheLetteDef;
XmString XmLab;

RigheLette = 0;
i=0;
while (RigheLette != Posizione )
	{
	if (strcmp(EditorDefinitions[i],"NULL") == 0)
		RigheLette++;
	i++;
	}

j = 0;
while (strcmp (EditorDefinitions[i],"NULL"))
	{
	XmLab = XmStringCreateSimple (EditorDefinitions[i]);
	set_something (Lab[j], XmNlabelString, (void*) XmLab);
	set_something (TextF[j], XmNsensitive, (void*) True);
	XmStringFree (XmLab);
	i++;
	j++;
	}

i=0;
RigheLetteDef = 0;
while (RigheLetteDef != Posizione)
	{
	if (strcmp (PerturbDefaults[i],"NULL")==0)
		RigheLetteDef++;
	i++;
	}

XmTextFieldSetString (TextF[0],PerturbDefaults[i]);
XmTextFieldSetString (TextF[1],PerturbDefaults[i+1]);
}

int OptPertCB (Widget wid, int ind_res, XmAnyCallbackStruct *call_data)
{

#ifndef DESIGN_TIME
        _UxCPerturbEditor *UxSaveCtx,*UxContext;

        UxSaveCtx = UxPerturbEditorContext;
        UxPerturbEditorContext = UxContext =
                        (_UxCPerturbEditor *)UxGetContext(wid);
#endif

RiazzeraParameter (VettoreLabel,VettoreText);
ImpostaParameter (VettoreLabel,VettoreText,ind_res);

IndicePerturba = ind_res;

#ifndef DESIGN_TIME
        UxPerturbEditorContext = UxSaveCtx;
#endif
return (OK);
}

/*****************************************************************
        Creazione dell'option menu delle perturbazioni
*****************************************************************/

int ImpostaOptionMenu (Widget ogg,int Posizione)
{
        Widget  *ListaItem;
        int i,narg;
        XmString StrLab;
        char objName[100];
	Arg args[10];

        XtDestroyWidget (Fittizio);
        ListaItem = (Widget *)XtCalloc (NumPert, sizeof(Widget));
        if (ListaItem == NULL) return (NON_ALLOCATA);
        for ( i = 0 ; i < NumPert ; i++ )
        {
                StrLab = XmStringCreateSimple (EditorOption[i]);
	
		narg = 0;
		XtSetArg (args[narg], XmNlabelString, StrLab); narg++;
                
                sprintf(objName,"%d_",i);
                strcat(objName,"optbt");
                ListaItem[i] = (Widget )XmCreatePushButton (ogg,objName,
							args,narg);
		XtManageChild (ListaItem[i]);

#ifndef DESIGN_TIME
		UxPutContext (ListaItem[i], (char *) UxPerturbEditorContext);
#endif
                XmStringFree(StrLab);
                XtAddCallback (ListaItem[i],XmNactivateCallback, (XtCallbackProc)OptPertCB,(XtPointer)i);
        }
        set_something (menu2, XmNmenuHistory, (void*) ListaItem[Posizione]);
        return (OK);
}

/*******************************************************************************
       The following are callback functions.
*******************************************************************************/

static	void	activateCB_pushButton15( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCPerturbEditor       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxPerturbEditorContext;
	UxPerturbEditorContext = UxContext =
			(_UxCPerturbEditor *) UxGetContext( UxWidget );
	{
	Boolean Valore;
	Boolean GiustoA,GiustoB;
	char *DefPerturba,*ParA,*ParB;
	char Messag[50];
	int Lunghezza;


	Lunghezza = 0;
	ParA = XmTextFieldGetString (textPar1);
	GiustoA = NumFloVerifica (ParA);
	
	ParB = XmTextFieldGetString (textPar2);
	GiustoB = NumFloVerifica (ParB);
	
	if ( GiustoA && GiustoB )
		{
		Lunghezza = strlen (PerturbDefinitions[IndicePerturba])+1;
		Lunghezza += strlen (ParA) + 1;
		Lunghezza += strlen (ParB) + 1;
		DefPerturba = XtCalloc (Lunghezza,sizeof(char));
		strcpy (DefPerturba,PerturbDefinitions[IndicePerturba]);
		if (ParA[0] != '\0')
			{
			strcat (DefPerturba," ");
			strcat (DefPerturba,ParA);
			}
		if (ParB[0] != '\0')
			{
			strcat (DefPerturba," ");
			strcat (DefPerturba,ParB);
			}
		XmTextFieldSetString (TextPerturbazione,DefPerturba);
		XtFree (DefPerturba);
		XtDestroyWidget (PerturbEditor);
		}
	else
		{
		strcpy (Messag,"An error detected in input!");
		VisualizzaMessageBox (GENERICA,PerturbEditor,Messag,PerturbEditor);
		}
	XtFree (ParA);
	XtFree (ParB);
	}
	UxPerturbEditorContext = UxSaveCtx;
}

static	void	activateCB_pushButton14( UxWidget, UxClientData, UxCallbackArg )
	Widget		UxWidget;
	XtPointer	UxClientData, UxCallbackArg;

{
	_UxCPerturbEditor       *UxSaveCtx, *UxContext;

	UxSaveCtx = UxPerturbEditorContext;
	UxPerturbEditorContext = UxContext =
			(_UxCPerturbEditor *) UxGetContext( UxWidget );
	{
	XtDestroyWidget (PerturbEditor);
	}
	UxPerturbEditorContext = UxSaveCtx;
}

/*******************************************************************************
       The 'build_' function creates all the widgets
       using the resource values specified in the Property Editor.
*******************************************************************************/

static Widget	_Uxbuild_PerturbEditor()
{

#ifdef PROVA
	Widget		OptionM_shell;
#endif


	/* Creation of PerturbEditor */
	PerturbEditor = XtVaCreatePopupShell( "PerturbEditor",
			transientShellWidgetClass,
			UxTopLevel,
			XmNx, 260,
			XmNy, 79,
			XmNwidth, 400,
			XmNheight, 170,
			XmNiconName, "Perturb",
			XmNtitle, "Perturb. Editor",
			NULL );
	UxPutContext( PerturbEditor, (char *) UxPerturbEditorContext );


	/* Creation of form5 */
	form5 = XtVaCreateManagedWidget( "form5",
			xmFormWidgetClass,
			PerturbEditor,
			XmNresizePolicy, XmRESIZE_NONE,
			XmNunitType, XmPIXELS,
			XmNx, 0,
			XmNy, 0,
			XmNwidth, 400,
			XmNheight, 170,
			NULL );
	UxPutContext( form5, (char *) UxPerturbEditorContext );


	/* Creation of pushButton15 */
	pushButton15 = XtVaCreateManagedWidget( "pushButton15",
			xmPushButtonWidgetClass,
			form5,
			XmNx, 9,
			XmNy, 124,
			XmNwidth, 80,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "OK" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 95,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopPosition, 70,
			XmNleftPosition, 5,
			XmNrightPosition, 30,
			NULL );
	XtAddCallback( pushButton15, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton15,
		(XtPointer) UxPerturbEditorContext );

	UxPutContext( pushButton15, (char *) UxPerturbEditorContext );


	/* Creation of pushButton14 */
	pushButton14 = XtVaCreateManagedWidget( "pushButton14",
			xmPushButtonWidgetClass,
			form5,
			XmNx, 99,
			XmNy, 124,
			XmNwidth, 80,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "CANCEL" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 95,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopPosition, 70,
			XmNleftPosition, 32,
			XmNrightPosition, 57,
			NULL );
	XtAddCallback( pushButton14, XmNactivateCallback,
		(XtCallbackProc) activateCB_pushButton14,
		(XtPointer) UxPerturbEditorContext );

	UxPutContext( pushButton14, (char *) UxPerturbEditorContext );




	/* Creation of separator7 */
	separator7 = XtVaCreateManagedWidget( "separator7",
			xmSeparatorWidgetClass,
			form5,
			XmNx, 0,
			XmNy, 104,
			XmNwidth, 550,
			XmNheight, 10,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 66,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftPosition, 1,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 99,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopPosition, 62,
			NULL );
	UxPutContext( separator7, (char *) UxPerturbEditorContext );


	/* Creation of OptionM */
	OptionM_shell = XtVaCreatePopupShell ("OptionM_shell",
			xmMenuShellWidgetClass, form5,
			XmNwidth, 1,
			XmNheight, 1,
			XmNallowShellResize, TRUE,
			XmNoverrideRedirect, TRUE,
			NULL );

	OptionM = XtVaCreateWidget( "OptionM",
			xmRowColumnWidgetClass,
			OptionM_shell,
			XmNrowColumnType, XmMENU_PULLDOWN,
			XmNmarginHeight, 0,
			XmNentryAlignment, XmALIGNMENT_CENTER,
			XmNadjustMargin, FALSE,
			NULL );
	UxPutContext( OptionM, (char *) UxPerturbEditorContext );


	/* Creation of Fittizio */
	Fittizio = XtVaCreateManagedWidget( "Fittizio",
			xmPushButtonWidgetClass,
			OptionM,
			RES_CONVERT( XmNlabelString, "Fittizio" ),
			NULL );
	UxPutContext( Fittizio, (char *) UxPerturbEditorContext );


	/* Creation of menu2 */
	menu2 = XtVaCreateManagedWidget( "menu2",
			xmRowColumnWidgetClass,
			form5,
			XmNrowColumnType, XmMENU_OPTION,
			XmNsubMenuId, OptionM,
			XmNx, 30,
			XmNy, 60,
			XmNentryAlignment, XmALIGNMENT_CENTER,
			RES_CONVERT( XmNlabelString, "" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 55,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopPosition, 35,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 10,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 38,
			NULL );
	UxPutContext( menu2, (char *) UxPerturbEditorContext );


	/* Creation of label7 */
	label7 = XtVaCreateManagedWidget( "label7",
			xmLabelWidgetClass,
			form5,
			XmNx, 30,
			XmNy, 20,
			XmNwidth, 100,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "Perturb. Type" ),
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 30,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopPosition, 10,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 10,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 38,
			NULL );
	UxPutContext( label7, (char *) UxPerturbEditorContext );


	/* Creation of textPar1 */
	textPar1 = XtVaCreateManagedWidget( "textPar1",
			xmTextFieldWidgetClass,
			form5,
			XmNx, 170,
			XmNy, 60,
			XmNwidth, 80,
			XmNheight, 30,
			XmNmaxLength, 10,
			XmNancestorSensitive, TRUE,
			XmNsensitive, FALSE,
			XmNmarginHeight, 1,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 55,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopPosition, 35,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 40,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 65,
			NULL );
	UxPutContext( textPar1, (char *) UxPerturbEditorContext );


	/* Creation of labPar1 */
	labPar1 = XtVaCreateManagedWidget( "labPar1",
			xmLabelWidgetClass,
			form5,
			XmNx, 160,
			XmNy, 20,
			XmNwidth, 100,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "" ),
			XmNrecomputeSize, FALSE,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 30,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopPosition, 10,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 40,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 65,
			NULL );
	UxPutContext( labPar1, (char *) UxPerturbEditorContext );


	/* Creation of textPar2 */
	textPar2 = XtVaCreateManagedWidget( "textPar2",
			xmTextFieldWidgetClass,
			form5,
			XmNx, 290,
			XmNy, 60,
			XmNwidth, 80,
			XmNheight, 30,
			XmNmaxLength, 10,
			XmNancestorSensitive, TRUE,
			XmNsensitive, FALSE,
			XmNmarginHeight, 1,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 55,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopPosition, 35,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 68,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 93,
			NULL );
	UxPutContext( textPar2, (char *) UxPerturbEditorContext );


	/* Creation of labPar2 */
	labPar2 = XtVaCreateManagedWidget( "labPar2",
			xmLabelWidgetClass,
			form5,
			XmNx, 280,
			XmNy, 20,
			XmNwidth, 100,
			XmNheight, 30,
			RES_CONVERT( XmNlabelString, "" ),
			XmNrecomputeSize, FALSE,
			XmNbottomAttachment, XmATTACH_POSITION,
			XmNbottomPosition, 30,
			XmNtopAttachment, XmATTACH_POSITION,
			XmNtopOffset, 0,
			XmNtopPosition, 10,
			XmNleftAttachment, XmATTACH_POSITION,
			XmNleftOffset, 0,
			XmNleftPosition, 68,
			XmNrightAttachment, XmATTACH_POSITION,
			XmNrightPosition, 93,
			NULL );
	UxPutContext( labPar2, (char *) UxPerturbEditorContext );


	XtAddCallback( PerturbEditor, XmNdestroyCallback,
		(XtCallbackProc) UxDestroyContextCB,
		(XtPointer) UxPerturbEditorContext);

	return ( PerturbEditor );
}

/*******************************************************************************
       The following is the 'Interface function' which is the
       external entry point for creating this interface.
       This function should be called from your application or from
       a callback function.
*******************************************************************************/

Widget	create_PerturbEditor( _UxParent3, _UxPert, _UxTextPert )
	Widget	_UxParent3;
	unsigned char	*_UxPert;
	Widget	_UxTextPert;
{
	Widget                  rtrn;
	_UxCPerturbEditor       *UxContext;

	UxPerturbEditorContext = UxContext =
		(_UxCPerturbEditor *) UxNewContext( sizeof(_UxCPerturbEditor), False );

	Parent3 = _UxParent3;
	Pert = _UxPert;
	TextPert = _UxTextPert;

	{
		int Pos;
		Perturbazione = Pert; 
		TextPerturbazione = TextPert;
		rtrn = _Uxbuild_PerturbEditor();
		VettoreLabel[0] = (Widget )labPar1;
		VettoreLabel[1] = (Widget )labPar2;
		
		VettoreText[0] = (Widget )textPar1;
		VettoreText[1] = (Widget )textPar2;
		
		IndicePerturba = InizializzaParameter (VettoreLabel,VettoreText,(char *)Perturbazione);

		ImpostaOptionMenu (OptionM,IndicePerturba);
		
		/*  Setta la posizione dell'interfaccia secondo il Parent  */
		InterfaceSetPos (PerturbEditor,Parent3);
		return(rtrn);
	}
}

/*******************************************************************************
       END OF FILE
*******************************************************************************/

