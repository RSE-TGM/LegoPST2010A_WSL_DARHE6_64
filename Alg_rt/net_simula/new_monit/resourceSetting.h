
/*******************************************************************************
       resourceSetting.h
       This header file is included by resourceSetting.c

*******************************************************************************/

#ifndef	_RESOURCESETTING_INCLUDED
#define	_RESOURCESETTING_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/ScrolledW.h>
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
	Widget	UxresourceSetting;
	Widget	UxapplyFrame;
	Widget	Uxform33;
	Widget	UxapplyResourceSetting;
	Widget	UxresourceSettingMenu;
	Widget	UxresourceSettingFile;
	Widget	UxresourceSettingFileQuit;
	Widget	Uxmenu15_top_b1;
	Widget	Uxform57;
	Widget	UxresourceSettingCategSelectForm;
	Widget	UxResSetForm;
	Widget	UxscrollWindResSet;
	Widget	UxresourceSettingResRc;
	int	Uxn_entries;
	int	UxselectedCategory;
	Widget	UxoptMenuForm;
	Widget	UxoptMenuShell;
	Widget	UxoptMenuRc;
	Widget	*UxoptMenuItem;
	Widget	UxoptMenu;
	int	*Uxindx;
	Widget	*UxresForm;
	Widget	*UxresLabel;
	Widget	*UxresText;
	Widget	*UxresMoreButton;
	swidget	UxUxParent;
} _UxCresourceSetting;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCresourceSetting     *UxResourceSettingContext;
#define resourceSetting         UxResourceSettingContext->UxresourceSetting
#define applyFrame              UxResourceSettingContext->UxapplyFrame
#define form33                  UxResourceSettingContext->Uxform33
#define applyResourceSetting    UxResourceSettingContext->UxapplyResourceSetting
#define resourceSettingMenu     UxResourceSettingContext->UxresourceSettingMenu
#define resourceSettingFile     UxResourceSettingContext->UxresourceSettingFile
#define resourceSettingFileQuit UxResourceSettingContext->UxresourceSettingFileQuit
#define menu15_top_b1           UxResourceSettingContext->Uxmenu15_top_b1
#define form57                  UxResourceSettingContext->Uxform57
#define resourceSettingCategSelectForm UxResourceSettingContext->UxresourceSettingCategSelectForm
#define ResSetForm              UxResourceSettingContext->UxResSetForm
#define scrollWindResSet        UxResourceSettingContext->UxscrollWindResSet
#define resourceSettingResRc    UxResourceSettingContext->UxresourceSettingResRc
#define n_entries               UxResourceSettingContext->Uxn_entries
#define selectedCategory        UxResourceSettingContext->UxselectedCategory
#define optMenuForm             UxResourceSettingContext->UxoptMenuForm
#define optMenuShell            UxResourceSettingContext->UxoptMenuShell
#define optMenuRc               UxResourceSettingContext->UxoptMenuRc
#define optMenuItem             UxResourceSettingContext->UxoptMenuItem
#define optMenu                 UxResourceSettingContext->UxoptMenu
#define indx                    UxResourceSettingContext->Uxindx
#define resForm                 UxResourceSettingContext->UxresForm
#define resLabel                UxResourceSettingContext->UxresLabel
#define resText                 UxResourceSettingContext->UxresText
#define resMoreButton           UxResourceSettingContext->UxresMoreButton
#define UxParent                UxResourceSettingContext->UxUxParent

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_resourceSetting( swidget _UxUxParent );

#endif	/* _RESOURCESETTING_INCLUDED */
