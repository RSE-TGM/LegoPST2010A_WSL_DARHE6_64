
/*******************************************************************************
       previewSnap.h
       This header file is included by previewSnap.c

*******************************************************************************/

#ifndef	_PREVIEWSNAP_INCLUDED
#define	_PREVIEWSNAP_INCLUDED


#include <stdio.h>
#include <Xm/Xm.h>
#include <Xm/MwmUtil.h>
#include <Xm/DialogS.h>
#include <Xm/MenuShell.h>
#include "UxXt.h"

#include <Xm/ScrolledW.h>
#include <Xm/CascadeB.h>
#include <Xm/SeparatoG.h>
#include <Xm/Separator.h>
#include <Xm/RowColumn.h>
#include <Xm/PushB.h>
#include <Xm/Form.h>
#include <Xm/Frame.h>
#include <Xm/Form.h>

#ifndef previewSnap_readFile
#define previewSnap_readFile( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, UxpreviewSnap_readFile_Id,\
			UxpreviewSnap_readFile_Name)) \
		( UxThis, pEnv )
#endif

#ifndef previewSnap_displayVal
#define previewSnap_displayVal( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, UxpreviewSnap_displayVal_Id,\
			UxpreviewSnap_displayVal_Name)) \
		( UxThis, pEnv )
#endif

#ifndef previewSnap_crea_entry
#define previewSnap_crea_entry( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, UxpreviewSnap_crea_entry_Id,\
			UxpreviewSnap_crea_entry_Name)) \
		( UxThis, pEnv )
#endif

#ifndef previewSnap_readVal
#define previewSnap_readVal( UxThis, pEnv ) \
	((int(*)())UxMethodLookup(UxThis, UxpreviewSnap_readVal_Id,\
			UxpreviewSnap_readVal_Name)) \
		( UxThis, pEnv )
#endif


extern int	UxpreviewSnap_readFile_Id;
extern char*	UxpreviewSnap_readFile_Name;
extern int	UxpreviewSnap_displayVal_Id;
extern char*	UxpreviewSnap_displayVal_Name;
extern int	UxpreviewSnap_crea_entry_Id;
extern char*	UxpreviewSnap_crea_entry_Name;
extern int	UxpreviewSnap_readVal_Id;
extern char*	UxpreviewSnap_readVal_Name;

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
	Widget	UxpreviewSnap;
	Widget	Uxframe13;
	Widget	Uxform23;
	Widget	UxpreviewQuitpb;
	Widget	UxpreviewMenu;
	Widget	UxpreviewMenuFile;
	Widget	UxpreviewMenuFileOpenDefpb;
	Widget	UxpreviewMenuFileOpenpb;
	Widget	UxpreviewMenuFile_b7;
	Widget	UxpreviewMenuFileSavepb;
	Widget	UxpreviewMenuFileSaveaspb;
	Widget	UxpreviewMenuFileSep1;
	Widget	UxpreviewMenuFileQuitpb;
	Widget	UxpreviewMenuFilecb;
	Widget	UxpreviewMenuEdit;
	Widget	UxpreviewMenuEditSelpb;
	Widget	UxpreviewMenuEditSep1;
	Widget	UxpreviewMenuEditDelete;
	Widget	UxpreviewMenuEditClearAllpb;
	Widget	UxpreviewMenuEditcb;
	Widget	UxpreviewMenuHelp;
	Widget	UxpreviewMenuHelpCommpb;
	Widget	UxpreviewMenuHelpcb;
	Widget	UxscrolledWindow4;
	Widget	UxviewRc;
	Widget	UxpreviewSnapPopup;
	Widget	UxpreviewSnapPopupOpenDef;
	Widget	UxpreviewSnapPopupMenuOpen;
	Widget	UxpreviewSnapPopupMenu_b3;
	Widget	UxpreviewSnapPopupMenuSaveDef;
	Widget	UxpreviewSnapPopupMenuSave;
	Widget	UxpreviewSnapPopupMenu_b6;
	Widget	UxpreviewSnapPopupMenuQuit;
	Widget	UxViewScrollForm[10];
	Widget	UxViewScrollTb[10];
	Widget	UxViewScrollText[10];
	Widget	UxViewScrollLabel[10];
	Widget	UxselVarWidg;
	PREVIEW_DATA	Uxpreview_data;
	LISTA_VAR	Uxlista_var;
	unsigned char	*Uxtestata;
	int	Uxwhich;
	int	Uxn;
	unsigned char	*Uxs;
} _UxCpreviewSnap;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCpreviewSnap         *UxPreviewSnapContext;
#define previewSnap             UxPreviewSnapContext->UxpreviewSnap
#define frame13                 UxPreviewSnapContext->Uxframe13
#define form23                  UxPreviewSnapContext->Uxform23
#define previewQuitpb           UxPreviewSnapContext->UxpreviewQuitpb
#define previewMenu             UxPreviewSnapContext->UxpreviewMenu
#define previewMenuFile         UxPreviewSnapContext->UxpreviewMenuFile
#define previewMenuFileOpenDefpb UxPreviewSnapContext->UxpreviewMenuFileOpenDefpb
#define previewMenuFileOpenpb   UxPreviewSnapContext->UxpreviewMenuFileOpenpb
#define previewMenuFile_b7      UxPreviewSnapContext->UxpreviewMenuFile_b7
#define previewMenuFileSavepb   UxPreviewSnapContext->UxpreviewMenuFileSavepb
#define previewMenuFileSaveaspb UxPreviewSnapContext->UxpreviewMenuFileSaveaspb
#define previewMenuFileSep1     UxPreviewSnapContext->UxpreviewMenuFileSep1
#define previewMenuFileQuitpb   UxPreviewSnapContext->UxpreviewMenuFileQuitpb
#define previewMenuFilecb       UxPreviewSnapContext->UxpreviewMenuFilecb
#define previewMenuEdit         UxPreviewSnapContext->UxpreviewMenuEdit
#define previewMenuEditSelpb    UxPreviewSnapContext->UxpreviewMenuEditSelpb
#define previewMenuEditSep1     UxPreviewSnapContext->UxpreviewMenuEditSep1
#define previewMenuEditDelete   UxPreviewSnapContext->UxpreviewMenuEditDelete
#define previewMenuEditClearAllpb UxPreviewSnapContext->UxpreviewMenuEditClearAllpb
#define previewMenuEditcb       UxPreviewSnapContext->UxpreviewMenuEditcb
#define previewMenuHelp         UxPreviewSnapContext->UxpreviewMenuHelp
#define previewMenuHelpCommpb   UxPreviewSnapContext->UxpreviewMenuHelpCommpb
#define previewMenuHelpcb       UxPreviewSnapContext->UxpreviewMenuHelpcb
#define scrolledWindow4         UxPreviewSnapContext->UxscrolledWindow4
#define viewRc                  UxPreviewSnapContext->UxviewRc
#define previewSnapPopup        UxPreviewSnapContext->UxpreviewSnapPopup
#define previewSnapPopupOpenDef UxPreviewSnapContext->UxpreviewSnapPopupOpenDef
#define previewSnapPopupMenuOpen UxPreviewSnapContext->UxpreviewSnapPopupMenuOpen
#define previewSnapPopupMenu_b3 UxPreviewSnapContext->UxpreviewSnapPopupMenu_b3
#define previewSnapPopupMenuSaveDef UxPreviewSnapContext->UxpreviewSnapPopupMenuSaveDef
#define previewSnapPopupMenuSave UxPreviewSnapContext->UxpreviewSnapPopupMenuSave
#define previewSnapPopupMenu_b6 UxPreviewSnapContext->UxpreviewSnapPopupMenu_b6
#define previewSnapPopupMenuQuit UxPreviewSnapContext->UxpreviewSnapPopupMenuQuit
#define ViewScrollForm          UxPreviewSnapContext->UxViewScrollForm
#define ViewScrollTb            UxPreviewSnapContext->UxViewScrollTb
#define ViewScrollText          UxPreviewSnapContext->UxViewScrollText
#define ViewScrollLabel         UxPreviewSnapContext->UxViewScrollLabel
#define selVarWidg              UxPreviewSnapContext->UxselVarWidg
#define preview_data            UxPreviewSnapContext->Uxpreview_data
#define lista_var               UxPreviewSnapContext->Uxlista_var
#define testata                 UxPreviewSnapContext->Uxtestata
#define which                   UxPreviewSnapContext->Uxwhich
#define n                       UxPreviewSnapContext->Uxn
#define s                       UxPreviewSnapContext->Uxs

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_previewSnap( int _Uxwhich, int _Uxn, unsigned char *_Uxs );

#endif	/* _PREVIEWSNAP_INCLUDED */
