
/*******************************************************************************
       scenarioMalf.h
       This header file is included by scenarioMalf.c

*******************************************************************************/

#ifndef	_SCENARIOMALF_INCLUDED
#define	_SCENARIOMALF_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/ScrolledW.h>
#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/CascadeB.h>
#include <Xm/Separator.h>
#include <Xm/PushB.h>
#include <Xm/RowColumn.h>
#include <Xm/Form.h>

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
	Widget	UxscenarioMalf;
	Widget	UxscenMalfMenu;
	Widget	UxscenMalfMenuFile1;
	Widget	UxscenMalfMenuFileSaveDef;
	Widget	UxscenMalfMenuFileSep1;
	Widget	UxscenMalfMenuFileQuitpb;
	Widget	UxmalfMenu_top_File;
	Widget	UxscenMalfMenuEdit;
	Widget	UxscenMalfEditAdd;
	Widget	UxscenMalfMenuEdit_b3;
	Widget	UxscenMalfEditDel;
	Widget	UxmalfMenu_top_Edit;
	Widget	UxscenMalfMenuHelp;
	Widget	UxscenMalfMenuHelppb;
	Widget	UxmalfMenu_top_b3;
	Widget	UxscenMalfMenuShow;
	Widget	UxscenMalfMenuShowSummaryMalf;
	Widget	UxmalfMenu_top_Show;
	Widget	Uxframe16;
	Widget	Uxform32;
	Widget	UxquitMalfScenpb;
	Widget	UxdeactMalfScenpb;
	Widget	UxscenarioMalfScrollWin;
	Widget	UxscenMalfRc;
	Widget	UxscenMalfRcPopupMenu;
	Widget	UxscenMfPopupSave;
	Widget	UxscenMfPopupSep1;
	Widget	UxscenMalfRcPopupAdd;
	Widget	UxscenMalfPopupDel;
	Widget	UxscenMfPopupSep2;
	Widget	UxscenMfPopupSummary;
	Widget	UxscenMfPopupSep3;
	Widget	UxscenMalfRcPopupQuit;
	Widget	UxscenMalfEntryForm[30];
	Widget	Uxmenu6_p2_shell[30];
	Widget	Uxmenu6_p2[30];
	Widget	UxscenMalfMenuTarget[10][30];
	Widget	Uxmenu6[30];
	Widget	UxscenMalfTb[30];
	Widget	UxscenMalfMainLabel[30];
	Widget	UxscenMalfTipoComp[30];
	Widget	UxscenMalfDescr[30];
	Widget	UxscenMalfValAtt[30];
	Widget	UxscenMalfMoreData[30];
	Widget	UxscenMalfConfig[30];
	Widget	UxscenMalfDelay[30];
	Widget	UxscenMalfDurata[30];
	Widget	UxscenMalfRampa[30];
	int	Uxscen_malf_select;
	int	Uxmalf_select[30];
	int	UxitemExpand[30];
	int	Uxcol_sfondo_scenMalf;
	SCENARIO	Uxscenario;
	XtIntervalId	Uxtimer_scenarioMalf;
	float	Uxtempo_old[30];
	int	Uxprimo_giro[30];
	int	UxmoreDataAperto[30];
	float	UxvalorePrec[30];
	XtIntervalId	Uxtimer_sommarioMalf;
	int	UxnuovoSnapAggiornamento[30];
	Widget	UxParent;
	int	Uxtipo;
	int	Uxnum_scen;
} _UxCscenarioMalf;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCscenarioMalf        *UxScenarioMalfContext;
#define scenarioMalf            UxScenarioMalfContext->UxscenarioMalf
#define scenMalfMenu            UxScenarioMalfContext->UxscenMalfMenu
#define scenMalfMenuFile1       UxScenarioMalfContext->UxscenMalfMenuFile1
#define scenMalfMenuFileSaveDef UxScenarioMalfContext->UxscenMalfMenuFileSaveDef
#define scenMalfMenuFileSep1    UxScenarioMalfContext->UxscenMalfMenuFileSep1
#define scenMalfMenuFileQuitpb  UxScenarioMalfContext->UxscenMalfMenuFileQuitpb
#define malfMenu_top_File       UxScenarioMalfContext->UxmalfMenu_top_File
#define scenMalfMenuEdit        UxScenarioMalfContext->UxscenMalfMenuEdit
#define scenMalfEditAdd         UxScenarioMalfContext->UxscenMalfEditAdd
#define scenMalfMenuEdit_b3     UxScenarioMalfContext->UxscenMalfMenuEdit_b3
#define scenMalfEditDel         UxScenarioMalfContext->UxscenMalfEditDel
#define malfMenu_top_Edit       UxScenarioMalfContext->UxmalfMenu_top_Edit
#define scenMalfMenuHelp        UxScenarioMalfContext->UxscenMalfMenuHelp
#define scenMalfMenuHelppb      UxScenarioMalfContext->UxscenMalfMenuHelppb
#define malfMenu_top_b3         UxScenarioMalfContext->UxmalfMenu_top_b3
#define scenMalfMenuShow        UxScenarioMalfContext->UxscenMalfMenuShow
#define scenMalfMenuShowSummaryMalf UxScenarioMalfContext->UxscenMalfMenuShowSummaryMalf
#define malfMenu_top_Show       UxScenarioMalfContext->UxmalfMenu_top_Show
#define frame16                 UxScenarioMalfContext->Uxframe16
#define form32                  UxScenarioMalfContext->Uxform32
#define quitMalfScenpb          UxScenarioMalfContext->UxquitMalfScenpb
#define deactMalfScenpb         UxScenarioMalfContext->UxdeactMalfScenpb
#define scenarioMalfScrollWin   UxScenarioMalfContext->UxscenarioMalfScrollWin
#define scenMalfRc              UxScenarioMalfContext->UxscenMalfRc
#define scenMalfRcPopupMenu     UxScenarioMalfContext->UxscenMalfRcPopupMenu
#define scenMfPopupSave         UxScenarioMalfContext->UxscenMfPopupSave
#define scenMfPopupSep1         UxScenarioMalfContext->UxscenMfPopupSep1
#define scenMalfRcPopupAdd      UxScenarioMalfContext->UxscenMalfRcPopupAdd
#define scenMalfPopupDel        UxScenarioMalfContext->UxscenMalfPopupDel
#define scenMfPopupSep2         UxScenarioMalfContext->UxscenMfPopupSep2
#define scenMfPopupSummary      UxScenarioMalfContext->UxscenMfPopupSummary
#define scenMfPopupSep3         UxScenarioMalfContext->UxscenMfPopupSep3
#define scenMalfRcPopupQuit     UxScenarioMalfContext->UxscenMalfRcPopupQuit
#define scenMalfEntryForm       UxScenarioMalfContext->UxscenMalfEntryForm
#define menu6_p2_shell          UxScenarioMalfContext->Uxmenu6_p2_shell
#define menu6_p2                UxScenarioMalfContext->Uxmenu6_p2
#define scenMalfMenuTarget      UxScenarioMalfContext->UxscenMalfMenuTarget
#define menu6                   UxScenarioMalfContext->Uxmenu6
#define scenMalfTb              UxScenarioMalfContext->UxscenMalfTb
#define scenMalfMainLabel       UxScenarioMalfContext->UxscenMalfMainLabel
#define scenMalfTipoComp        UxScenarioMalfContext->UxscenMalfTipoComp
#define scenMalfDescr           UxScenarioMalfContext->UxscenMalfDescr
#define scenMalfValAtt          UxScenarioMalfContext->UxscenMalfValAtt
#define scenMalfMoreData        UxScenarioMalfContext->UxscenMalfMoreData
#define scenMalfConfig          UxScenarioMalfContext->UxscenMalfConfig
#define scenMalfDelay           UxScenarioMalfContext->UxscenMalfDelay
#define scenMalfDurata          UxScenarioMalfContext->UxscenMalfDurata
#define scenMalfRampa           UxScenarioMalfContext->UxscenMalfRampa
#define scen_malf_select        UxScenarioMalfContext->Uxscen_malf_select
#define malf_select             UxScenarioMalfContext->Uxmalf_select
#define itemExpand              UxScenarioMalfContext->UxitemExpand
#define col_sfondo_scenMalf     UxScenarioMalfContext->Uxcol_sfondo_scenMalf
#define scenario                UxScenarioMalfContext->Uxscenario
#define timer_scenarioMalf      UxScenarioMalfContext->Uxtimer_scenarioMalf
#define tempo_old               UxScenarioMalfContext->Uxtempo_old
#define primo_giro              UxScenarioMalfContext->Uxprimo_giro
#define moreDataAperto          UxScenarioMalfContext->UxmoreDataAperto
#define valorePrec              UxScenarioMalfContext->UxvalorePrec
#define timer_sommarioMalf      UxScenarioMalfContext->Uxtimer_sommarioMalf
#define nuovoSnapAggiornamento  UxScenarioMalfContext->UxnuovoSnapAggiornamento
#define Parent                  UxScenarioMalfContext->UxParent
#define tipo                    UxScenarioMalfContext->Uxtipo
#define num_scen                UxScenarioMalfContext->Uxnum_scen

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	actMalfScenpb;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_scenarioMalf( Widget _UxParent, int _Uxtipo, int _Uxnum_scen );

#endif	/* _SCENARIOMALF_INCLUDED */
