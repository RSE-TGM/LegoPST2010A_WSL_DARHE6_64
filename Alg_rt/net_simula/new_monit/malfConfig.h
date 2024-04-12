
/*******************************************************************************
       malfConfig.h
       This header file is included by malfConfig.c

*******************************************************************************/

#ifndef	_MALFCONFIG_INCLUDED
#define	_MALFCONFIG_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/Separator.h>
#include <Xm/Label.h>
#include <Xm/Text.h>
#include <Xm/CascadeB.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/Form.h>
#include <Xm/Frame.h>
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
	Widget	UxmalfConfig;
	Widget	Uxframe30;
	Widget	Uxform56;
	Widget	UxapplyMalfConfigpb;
	Widget	Uxmenu10;
	Widget	UxmalfConfigFile;
	Widget	UxmalfConfigFileQuitpb;
	Widget	Uxmenu10_top_b3;
	Widget	Uxform58;
	Widget	UxsecVar;
	Widget	UxsecVarRc;
	Widget	Uxmenu11;
	Widget	UxmalfConfigPopupQuit;
	Widget	UxmalfParam;
	Widget	UxdurationTf;
	Widget	UxrampTf;
	Widget	Uxlabel26;
	Widget	Uxlabel27;
	Widget	Uxlabel28;
	Widget	Uxseparator4;
	Widget	UxdelayTf;
	float	Uxdelay;
	float	Uxduration;
	float	Uxramp;
	float	UxsecVal1;
	float	UxsecVal2;
	float	UxsecVal3;
	float	UxsecVal4;
	XtIntervalId	Uxtimer_malfConfig;
	int	UxdelayModified;
	int	UxrampModified;
	int	UxdurataModified;
	int	UxvalSec1Modified;
	int	UxvalSec2Modified;
	int	UxvalSec3Modified;
	int	UxvalSec4Modified;
	unsigned int	Uxsfondo;
	unsigned int	UxcolorTesto;
	Widget	UxSecVar1;
	Widget	UxSecVar2;
	Widget	UxSecVar3;
	Widget	UxSecVar4;
	Widget	UxsecVar1Label;
	Widget	UxsecVar2Label;
	Widget	UxsecVar3Label;
	Widget	UxsecVar4Label;
	Widget	UxsecVar1Descr;
	Widget	UxsecVar2Descr;
	Widget	UxsecVar3Descr;
	Widget	UxsecVar4Descr;
	Widget	UxsecVar1ValTf;
	Widget	UxsecVar2ValTf;
	Widget	UxsecVar3ValTf;
	Widget	UxsecVar4ValTf;
	Widget	UxsecVar1Tb;
	Widget	UxsecVar2Tb;
	Widget	UxsecVar3Tb;
	Widget	UxsecVar4Tb;
	Widget	UxsecVar1Mod;
	Widget	UxsecVar2Mod;
	Widget	UxsecVar3Mod;
	Widget	UxsecVar4Mod;
	Widget	UxsecVar1ValActLab;
	Widget	UxsecVar2ValActLab;
	Widget	UxsecVar3ValActLab;
	Widget	UxsecVar4ValActLab;
	Widget	UxsecVar1ValAct;
	Widget	UxsecVar2ValAct;
	Widget	UxsecVar3ValAct;
	Widget	UxsecVar4ValAct;
	int	UxpertToggle1;
	int	UxpertToggle2;
	int	UxpertToggle3;
	int	UxpertToggle4;
	int	UxvarSecExist1;
	int	UxvarSecExist2;
	int	UxvarSecExist3;
	int	UxvarSecExist4;
	float	UxvalPrec1;
	float	UxvalPrec2;
	float	UxvalPrec3;
	float	UxvalPrec4;
	swidget	UxUxParent;
	int	Uxindx;
	int	Uxtipo;
} _UxCmalfConfig;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCmalfConfig          *UxMalfConfigContext;
#define malfConfig              UxMalfConfigContext->UxmalfConfig
#define frame30                 UxMalfConfigContext->Uxframe30
#define form56                  UxMalfConfigContext->Uxform56
#define applyMalfConfigpb       UxMalfConfigContext->UxapplyMalfConfigpb
#define menu10                  UxMalfConfigContext->Uxmenu10
#define malfConfigFile          UxMalfConfigContext->UxmalfConfigFile
#define malfConfigFileQuitpb    UxMalfConfigContext->UxmalfConfigFileQuitpb
#define menu10_top_b3           UxMalfConfigContext->Uxmenu10_top_b3
#define form58                  UxMalfConfigContext->Uxform58
#define secVar                  UxMalfConfigContext->UxsecVar
#define secVarRc                UxMalfConfigContext->UxsecVarRc
#define menu11                  UxMalfConfigContext->Uxmenu11
#define malfConfigPopupQuit     UxMalfConfigContext->UxmalfConfigPopupQuit
#define malfParam               UxMalfConfigContext->UxmalfParam
#define durationTf              UxMalfConfigContext->UxdurationTf
#define rampTf                  UxMalfConfigContext->UxrampTf
#define label26                 UxMalfConfigContext->Uxlabel26
#define label27                 UxMalfConfigContext->Uxlabel27
#define label28                 UxMalfConfigContext->Uxlabel28
#define separator4              UxMalfConfigContext->Uxseparator4
#define delayTf                 UxMalfConfigContext->UxdelayTf
#define delay                   UxMalfConfigContext->Uxdelay
#define duration                UxMalfConfigContext->Uxduration
#define ramp                    UxMalfConfigContext->Uxramp
#define secVal1                 UxMalfConfigContext->UxsecVal1
#define secVal2                 UxMalfConfigContext->UxsecVal2
#define secVal3                 UxMalfConfigContext->UxsecVal3
#define secVal4                 UxMalfConfigContext->UxsecVal4
#define timer_malfConfig        UxMalfConfigContext->Uxtimer_malfConfig
#define delayModified           UxMalfConfigContext->UxdelayModified
#define rampModified            UxMalfConfigContext->UxrampModified
#define durataModified          UxMalfConfigContext->UxdurataModified
#define valSec1Modified         UxMalfConfigContext->UxvalSec1Modified
#define valSec2Modified         UxMalfConfigContext->UxvalSec2Modified
#define valSec3Modified         UxMalfConfigContext->UxvalSec3Modified
#define valSec4Modified         UxMalfConfigContext->UxvalSec4Modified
#define sfondo                  UxMalfConfigContext->Uxsfondo
#define colorTesto              UxMalfConfigContext->UxcolorTesto
#define SecVar1                 UxMalfConfigContext->UxSecVar1
#define SecVar2                 UxMalfConfigContext->UxSecVar2
#define SecVar3                 UxMalfConfigContext->UxSecVar3
#define SecVar4                 UxMalfConfigContext->UxSecVar4
#define secVar1Label            UxMalfConfigContext->UxsecVar1Label
#define secVar2Label            UxMalfConfigContext->UxsecVar2Label
#define secVar3Label            UxMalfConfigContext->UxsecVar3Label
#define secVar4Label            UxMalfConfigContext->UxsecVar4Label
#define secVar1Descr            UxMalfConfigContext->UxsecVar1Descr
#define secVar2Descr            UxMalfConfigContext->UxsecVar2Descr
#define secVar3Descr            UxMalfConfigContext->UxsecVar3Descr
#define secVar4Descr            UxMalfConfigContext->UxsecVar4Descr
#define secVar1ValTf            UxMalfConfigContext->UxsecVar1ValTf
#define secVar2ValTf            UxMalfConfigContext->UxsecVar2ValTf
#define secVar3ValTf            UxMalfConfigContext->UxsecVar3ValTf
#define secVar4ValTf            UxMalfConfigContext->UxsecVar4ValTf
#define secVar1Tb               UxMalfConfigContext->UxsecVar1Tb
#define secVar2Tb               UxMalfConfigContext->UxsecVar2Tb
#define secVar3Tb               UxMalfConfigContext->UxsecVar3Tb
#define secVar4Tb               UxMalfConfigContext->UxsecVar4Tb
#define secVar1Mod              UxMalfConfigContext->UxsecVar1Mod
#define secVar2Mod              UxMalfConfigContext->UxsecVar2Mod
#define secVar3Mod              UxMalfConfigContext->UxsecVar3Mod
#define secVar4Mod              UxMalfConfigContext->UxsecVar4Mod
#define secVar1ValActLab        UxMalfConfigContext->UxsecVar1ValActLab
#define secVar2ValActLab        UxMalfConfigContext->UxsecVar2ValActLab
#define secVar3ValActLab        UxMalfConfigContext->UxsecVar3ValActLab
#define secVar4ValActLab        UxMalfConfigContext->UxsecVar4ValActLab
#define secVar1ValAct           UxMalfConfigContext->UxsecVar1ValAct
#define secVar2ValAct           UxMalfConfigContext->UxsecVar2ValAct
#define secVar3ValAct           UxMalfConfigContext->UxsecVar3ValAct
#define secVar4ValAct           UxMalfConfigContext->UxsecVar4ValAct
#define pertToggle1             UxMalfConfigContext->UxpertToggle1
#define pertToggle2             UxMalfConfigContext->UxpertToggle2
#define pertToggle3             UxMalfConfigContext->UxpertToggle3
#define pertToggle4             UxMalfConfigContext->UxpertToggle4
#define varSecExist1            UxMalfConfigContext->UxvarSecExist1
#define varSecExist2            UxMalfConfigContext->UxvarSecExist2
#define varSecExist3            UxMalfConfigContext->UxvarSecExist3
#define varSecExist4            UxMalfConfigContext->UxvarSecExist4
#define valPrec1                UxMalfConfigContext->UxvalPrec1
#define valPrec2                UxMalfConfigContext->UxvalPrec2
#define valPrec3                UxMalfConfigContext->UxvalPrec3
#define valPrec4                UxMalfConfigContext->UxvalPrec4
#define UxParent                UxMalfConfigContext->UxUxParent
#define indx                    UxMalfConfigContext->Uxindx
#define tipo                    UxMalfConfigContext->Uxtipo

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_malfConfig( swidget _UxUxParent, int _Uxindx, int _Uxtipo );

#endif	/* _MALFCONFIG_INCLUDED */
