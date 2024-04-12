
/*******************************************************************************
       selVarCr.h
       This header file is included by selVarCr.c

*******************************************************************************/

#ifndef	_SELVARCR_INCLUDED
#define	_SELVARCR_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Text.h>
#include <Xm/BulletinB.h>
#include <Xm/List.h>
#include <Xm/ScrolledW.h>
#include <Xm/TextF.h>
#include <Xm/ArrowB.h>
#include <Xm/Label.h>
#include <Xm/PanedW.h>
#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/ToggleB.h>
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
	Widget	Uxmenu3;
	Widget	UxselVarCrMenu;
	Widget	UxselVarCrMenu_b4;
	Widget	UxselVarCrMenu_b3;
	Widget	UxselVarCrMenu_b2;
	Widget	UxselVarCrMenuFilepb;
	Widget	Uxmenu3_top_b1;
	Widget	UxselVarCrMenuEdit;
	Widget	UxSelVarCrMenuEditTimer;
	Widget	Uxmenu3_top_b5;
	Widget	UxselVarMenuFilter;
	Widget	UxselVarMenuOtherPane;
	Widget	UxselByAllVariablestb;
	Widget	UxselByModeltb;
	Widget	UxselByModelOnlytb;
	Widget	UxselVarMenuOtherPane_b6;
	Widget	UxselVarMenuKkstb;
	Widget	UxselVarMenuOtherPane_b3;
	Widget	UxselVarMenuTipotb;
	Widget	UxselVarMenuFilter_b8;
	Widget	UxselVarMenuFilter_b2;
	Widget	Uxmenu3_top_b2;
	Widget	Uxframe1;
	Widget	Uxform39;
	Widget	UxselVarOkpb;
	Widget	UxselVarQuitpb;
	Widget	Uxframe24;
	Widget	UxselVarCrFilterForm;
	Widget	Uxframe26;
	Widget	Uxform50;
	Widget	UxselVarCrAllVartb;
	Widget	UxselVarCrModBlocktb;
	Widget	UxselVarCrModtb;
	Widget	Uxframe25;
	Widget	Uxform49;
	Widget	UxselVarCrKkstb;
	Widget	UxselVarCrTypetb;
	Widget	UxselVarCrSaveFilterpb;
	Widget	UxselVarCrApplyFilterpb;
	Widget	UxpanedWindow1;
	Widget	UxselByModelForm;
	Widget	Uxlabel5;
	Widget	Uxlabel7;
	Widget	Uxform44;
	Widget	UxselVarFindDown2;
	Widget	UxselVarText3;
	Widget	UxselVarFindUp2;
	Widget	UxscrolledWindow6;
	Widget	UxselVarListaSistemi;
	Widget	UxscrolledWindow7;
	Widget	UxselVarListaBlocchi;
	Widget	UxselVarCrKksForm;
	Widget	UxselVarCrKksBullBoard;
	Widget	UxselVarCrKksText1;
	Widget	UxselVarCrKksSistemaLabel;
	Widget	UxselVarCrKksSottosistLabel;
	Widget	UxselVarCrKksComponentLabel;
	Widget	UxselVarCrKksText2;
	Widget	UxselVarCrKksText3;
	Widget	UxselVarCrKksText4;
	Widget	UxselVarCrKksText5;
	Widget	UxselVarCrKksText6;
	Widget	UxselVarCrKksText7;
	Widget	UxselVarCrKksText8;
	Widget	UxselVarCrKksProgressLabel;
	Widget	UxselVarCrKksText9;
	Widget	UxselVarCrKksText10;
	Widget	UxselVarCrKksText0;
	Widget	UxselVarCrKksNimpLabel;
	Widget	UxpushButton1;
	Widget	UxselVarCrTipoForm;
	Widget	UxselVarCrTipoPressionetb;
	Widget	UxselVarCrTipoEntalpiatb;
	Widget	UxselVarCrTipoPortatatb;
	Widget	UxselVarCrTipoGiritb;
	Widget	UxselVarCrTipoTemperaturatb;
	Widget	UxselVarCrTipoAlzvalvtb;
	Widget	UxselVarCrTipoPotenzatb;
	Widget	UxpushButton2;
	Widget	UxselVarCrTipoAingable1;
	Widget	UxselVarCrTipoInput1;
	Widget	UxselVarCrTipoOutput1;
	Widget	Uxform36;
	Widget	Uxlabel6;
	Widget	Uxform38;
	Widget	UxselVarFindUp;
	Widget	UxselVarText;
	Widget	UxselVarFindDown;
	Widget	UxaggiungiVarSelpb;
	Widget	UxselezionaAllpb;
	Widget	UxscrolledWindow8;
	Widget	UxselVarToSelect;
	Widget	Uxform37;
	Widget	Uxform35;
	Widget	UxdeleteVarSelpb;
	Widget	UxunselVarFindUp;
	Widget	UxunselVarText;
	Widget	UxunselVarFindDown;
	Widget	UxdeselezionaAllpb;
	Widget	Uxlabel4;
	Widget	UxscrolledWindow9;
	Widget	UxselVarToUnselect;
	Widget	UxselVarCrPopup;
	Widget	UxselVarCrPopupSaveFilter;
	Widget	UxselVarCrPopupApply;
	Widget	Uxmenu9_p1_b3;
	Widget	UxselVarCrPopupSave;
	Widget	Uxmenu9_p1_b5;
	Widget	UxselVarCrPopupQuit;
	Widget	Uxpadre;
} _UxCselVarCr;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCselVarCr            *UxSelVarCrContext;
#define menu3                   UxSelVarCrContext->Uxmenu3
#define selVarCrMenu            UxSelVarCrContext->UxselVarCrMenu
#define selVarCrMenu_b4         UxSelVarCrContext->UxselVarCrMenu_b4
#define selVarCrMenu_b3         UxSelVarCrContext->UxselVarCrMenu_b3
#define selVarCrMenu_b2         UxSelVarCrContext->UxselVarCrMenu_b2
#define selVarCrMenuFilepb      UxSelVarCrContext->UxselVarCrMenuFilepb
#define menu3_top_b1            UxSelVarCrContext->Uxmenu3_top_b1
#define selVarCrMenuEdit        UxSelVarCrContext->UxselVarCrMenuEdit
#define SelVarCrMenuEditTimer   UxSelVarCrContext->UxSelVarCrMenuEditTimer
#define menu3_top_b5            UxSelVarCrContext->Uxmenu3_top_b5
#define selVarMenuFilter        UxSelVarCrContext->UxselVarMenuFilter
#define selVarMenuOtherPane     UxSelVarCrContext->UxselVarMenuOtherPane
#define selByAllVariablestb     UxSelVarCrContext->UxselByAllVariablestb
#define selByModeltb            UxSelVarCrContext->UxselByModeltb
#define selByModelOnlytb        UxSelVarCrContext->UxselByModelOnlytb
#define selVarMenuOtherPane_b6  UxSelVarCrContext->UxselVarMenuOtherPane_b6
#define selVarMenuKkstb         UxSelVarCrContext->UxselVarMenuKkstb
#define selVarMenuOtherPane_b3  UxSelVarCrContext->UxselVarMenuOtherPane_b3
#define selVarMenuTipotb        UxSelVarCrContext->UxselVarMenuTipotb
#define selVarMenuFilter_b8     UxSelVarCrContext->UxselVarMenuFilter_b8
#define selVarMenuFilter_b2     UxSelVarCrContext->UxselVarMenuFilter_b2
#define menu3_top_b2            UxSelVarCrContext->Uxmenu3_top_b2
#define frame1                  UxSelVarCrContext->Uxframe1
#define form39                  UxSelVarCrContext->Uxform39
#define selVarOkpb              UxSelVarCrContext->UxselVarOkpb
#define selVarQuitpb            UxSelVarCrContext->UxselVarQuitpb
#define frame24                 UxSelVarCrContext->Uxframe24
#define selVarCrFilterForm      UxSelVarCrContext->UxselVarCrFilterForm
#define frame26                 UxSelVarCrContext->Uxframe26
#define form50                  UxSelVarCrContext->Uxform50
#define selVarCrAllVartb        UxSelVarCrContext->UxselVarCrAllVartb
#define selVarCrModBlocktb      UxSelVarCrContext->UxselVarCrModBlocktb
#define selVarCrModtb           UxSelVarCrContext->UxselVarCrModtb
#define frame25                 UxSelVarCrContext->Uxframe25
#define form49                  UxSelVarCrContext->Uxform49
#define selVarCrKkstb           UxSelVarCrContext->UxselVarCrKkstb
#define selVarCrTypetb          UxSelVarCrContext->UxselVarCrTypetb
#define selVarCrSaveFilterpb    UxSelVarCrContext->UxselVarCrSaveFilterpb
#define selVarCrApplyFilterpb   UxSelVarCrContext->UxselVarCrApplyFilterpb
#define panedWindow1            UxSelVarCrContext->UxpanedWindow1
#define selByModelForm          UxSelVarCrContext->UxselByModelForm
#define label5                  UxSelVarCrContext->Uxlabel5
#define label7                  UxSelVarCrContext->Uxlabel7
#define form44                  UxSelVarCrContext->Uxform44
#define selVarFindDown2         UxSelVarCrContext->UxselVarFindDown2
#define selVarText3             UxSelVarCrContext->UxselVarText3
#define selVarFindUp2           UxSelVarCrContext->UxselVarFindUp2
#define scrolledWindow6         UxSelVarCrContext->UxscrolledWindow6
#define selVarListaSistemi      UxSelVarCrContext->UxselVarListaSistemi
#define scrolledWindow7         UxSelVarCrContext->UxscrolledWindow7
#define selVarListaBlocchi      UxSelVarCrContext->UxselVarListaBlocchi
#define selVarCrKksForm         UxSelVarCrContext->UxselVarCrKksForm
#define selVarCrKksBullBoard    UxSelVarCrContext->UxselVarCrKksBullBoard
#define selVarCrKksText1        UxSelVarCrContext->UxselVarCrKksText1
#define selVarCrKksSistemaLabel UxSelVarCrContext->UxselVarCrKksSistemaLabel
#define selVarCrKksSottosistLabel UxSelVarCrContext->UxselVarCrKksSottosistLabel
#define selVarCrKksComponentLabel UxSelVarCrContext->UxselVarCrKksComponentLabel
#define selVarCrKksText2        UxSelVarCrContext->UxselVarCrKksText2
#define selVarCrKksText3        UxSelVarCrContext->UxselVarCrKksText3
#define selVarCrKksText4        UxSelVarCrContext->UxselVarCrKksText4
#define selVarCrKksText5        UxSelVarCrContext->UxselVarCrKksText5
#define selVarCrKksText6        UxSelVarCrContext->UxselVarCrKksText6
#define selVarCrKksText7        UxSelVarCrContext->UxselVarCrKksText7
#define selVarCrKksText8        UxSelVarCrContext->UxselVarCrKksText8
#define selVarCrKksProgressLabel UxSelVarCrContext->UxselVarCrKksProgressLabel
#define selVarCrKksText9        UxSelVarCrContext->UxselVarCrKksText9
#define selVarCrKksText10       UxSelVarCrContext->UxselVarCrKksText10
#define selVarCrKksText0        UxSelVarCrContext->UxselVarCrKksText0
#define selVarCrKksNimpLabel    UxSelVarCrContext->UxselVarCrKksNimpLabel
#define pushButton1             UxSelVarCrContext->UxpushButton1
#define selVarCrTipoForm        UxSelVarCrContext->UxselVarCrTipoForm
#define selVarCrTipoPressionetb UxSelVarCrContext->UxselVarCrTipoPressionetb
#define selVarCrTipoEntalpiatb  UxSelVarCrContext->UxselVarCrTipoEntalpiatb
#define selVarCrTipoPortatatb   UxSelVarCrContext->UxselVarCrTipoPortatatb
#define selVarCrTipoGiritb      UxSelVarCrContext->UxselVarCrTipoGiritb
#define selVarCrTipoTemperaturatb UxSelVarCrContext->UxselVarCrTipoTemperaturatb
#define selVarCrTipoAlzvalvtb   UxSelVarCrContext->UxselVarCrTipoAlzvalvtb
#define selVarCrTipoPotenzatb   UxSelVarCrContext->UxselVarCrTipoPotenzatb
#define pushButton2             UxSelVarCrContext->UxpushButton2
#define selVarCrTipoAingable1   UxSelVarCrContext->UxselVarCrTipoAingable1
#define selVarCrTipoInput1      UxSelVarCrContext->UxselVarCrTipoInput1
#define selVarCrTipoOutput1     UxSelVarCrContext->UxselVarCrTipoOutput1
#define form36                  UxSelVarCrContext->Uxform36
#define label6                  UxSelVarCrContext->Uxlabel6
#define form38                  UxSelVarCrContext->Uxform38
#define selVarFindUp            UxSelVarCrContext->UxselVarFindUp
#define selVarText              UxSelVarCrContext->UxselVarText
#define selVarFindDown          UxSelVarCrContext->UxselVarFindDown
#define aggiungiVarSelpb        UxSelVarCrContext->UxaggiungiVarSelpb
#define selezionaAllpb          UxSelVarCrContext->UxselezionaAllpb
#define scrolledWindow8         UxSelVarCrContext->UxscrolledWindow8
#define selVarToSelect          UxSelVarCrContext->UxselVarToSelect
#define form37                  UxSelVarCrContext->Uxform37
#define form35                  UxSelVarCrContext->Uxform35
#define deleteVarSelpb          UxSelVarCrContext->UxdeleteVarSelpb
#define unselVarFindUp          UxSelVarCrContext->UxunselVarFindUp
#define unselVarText            UxSelVarCrContext->UxunselVarText
#define unselVarFindDown        UxSelVarCrContext->UxunselVarFindDown
#define deselezionaAllpb        UxSelVarCrContext->UxdeselezionaAllpb
#define label4                  UxSelVarCrContext->Uxlabel4
#define scrolledWindow9         UxSelVarCrContext->UxscrolledWindow9
#define selVarToUnselect        UxSelVarCrContext->UxselVarToUnselect
#define selVarCrPopup           UxSelVarCrContext->UxselVarCrPopup
#define selVarCrPopupSaveFilter UxSelVarCrContext->UxselVarCrPopupSaveFilter
#define selVarCrPopupApply      UxSelVarCrContext->UxselVarCrPopupApply
#define menu9_p1_b3             UxSelVarCrContext->Uxmenu9_p1_b3
#define selVarCrPopupSave       UxSelVarCrContext->UxselVarCrPopupSave
#define menu9_p1_b5             UxSelVarCrContext->Uxmenu9_p1_b5
#define selVarCrPopupQuit       UxSelVarCrContext->UxselVarCrPopupQuit
#define padre                   UxSelVarCrContext->Uxpadre

#endif /* CONTEXT_MACRO_ACCESS */

extern Widget	selVarCr;

/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_selVarCr( Widget _Uxpadre );

#endif	/* _SELVARCR_INCLUDED */
