
/*******************************************************************************
       selVar.h
       This header file is included by selVar.c

*******************************************************************************/

#ifndef	_SELVAR_INCLUDED
#define	_SELVAR_INCLUDED


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
#include <Xm/Separator.h>
#include <Xm/ToggleB.h>
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
	Widget	UxselVar;
	Widget	Uxframe2;
	Widget	Uxform42;
	Widget	UxselOkpb;
	Widget	UxselQuitpb;
	Widget	Uxmenu4;
	Widget	UxselVarCrMenu1;
	Widget	UxselVarCrMenuFilepb1;
	Widget	Uxmenu3_top_b3;
	Widget	UxselVarMenuFilter1;
	Widget	UxselVarMenuOtherPane1;
	Widget	UxselByAllVariablestb1;
	Widget	UxselByModeltb1;
	Widget	UxselByModelOnlytb1;
	Widget	UxselVarMenuOtherPane_b1;
	Widget	UxselVarMenuKkstb1;
	Widget	UxselVarMenuOtherPane_b2;
	Widget	UxselVarMenuTipotb1;
	Widget	UxselVarMenuFilter_b1;
	Widget	Uxmenu3_top_b4;
	Widget	Uxframe27;
	Widget	UxselVarCrFilterForm1;
	Widget	Uxframe28;
	Widget	Uxform51;
	Widget	UxselVarCrAllVartb1;
	Widget	UxselVarCrModBlocktb1;
	Widget	UxselVarCrModtb1;
	Widget	Uxframe29;
	Widget	Uxform52;
	Widget	UxselVarCrKkstb1;
	Widget	UxselVarCrTypetb1;
	Widget	UxselVarCrSaveFilterpb1;
	Widget	UxselVarCrApplyFilterpb1;
	Widget	UxpanedWindow2;
	Widget	UxselByModelForm1;
	Widget	Uxlabel8;
	Widget	Uxlabel9;
	Widget	Uxform43;
	Widget	UxselVarModFindDown;
	Widget	UxselVarText2;
	Widget	UxselVarModFindUp;
	Widget	UxscrolledWindow10;
	Widget	UxselVarListaSistemi1;
	Widget	UxscrolledWindow11;
	Widget	UxselVarListaBlocchi1;
	Widget	UxselVarCrKksForm2;
	Widget	UxselVarCrKksBullBoard2;
	Widget	UxselVarCrKksText22;
	Widget	UxselVarCrKksSistemaLabel2;
	Widget	UxselVarCrKksSottosistLabel2;
	Widget	UxselVarCrKksComponentLabel2;
	Widget	UxselVarCrKksText23;
	Widget	UxselVarCrKksText24;
	Widget	UxselVarCrKksText25;
	Widget	UxselVarCrKksText26;
	Widget	UxselVarCrKksText27;
	Widget	UxselVarCrKksText28;
	Widget	UxselVarCrKksText29;
	Widget	UxselVarCrKksProgressLabel2;
	Widget	UxselVarCrKksText30;
	Widget	UxselVarCrKksText31;
	Widget	UxselVarCrKksText32;
	Widget	UxselVarCrKksNimpLabel2;
	Widget	UxpushButton4;
	Widget	UxselVarCrTipoForm1;
	Widget	UxselVarCrTipoPressionetb1;
	Widget	UxselVarCrTipoEntalpiatb1;
	Widget	UxselVarCrTipoPortatatb1;
	Widget	UxselVarCrTipoGiritb1;
	Widget	UxselVarCrTipoTemperaturatb1;
	Widget	UxselVarCrTipoAlzvalvtb1;
	Widget	UxselVarCrTipoPotenzatb1;
	Widget	UxpushButton5;
	Widget	UxselVarCrTipoAingable;
	Widget	UxselVarCrTipoInput;
	Widget	UxselVarCrTipoOutput;
	Widget	Uxform40;
	Widget	Uxlabel10;
	Widget	Uxform41;
	Widget	UxselVarFindUp1;
	Widget	UxselVarText1;
	Widget	UxselVarFindDown1;
	Widget	UxscrolledWindow12;
	Widget	UxselVarToSelect1;
	Widget	Uxmenu13;
	Widget	UxselVarMenuPopupSaveFilter;
	Widget	UxselVarMenuPopupApplyFilter;
	Widget	UxselVarMenuPopup_b3;
	Widget	UxselVarMenuPopupSelect;
	Widget	UxselVarMenuPopup_b5;
	Widget	UxselVarMenuPopupQuit;
	int	Uxmod_sel;
	int	Uxblocco_sel;
	int	Uxkks_filter_act;
	int	Uxtipo_filter_act;
	unsigned char	Uxstringa_kks[12];
	FILTRO_TIPI	Uxfiltro_tipo;
	int	*Uxpunt_var;
	int	*Uxpunt_var_kks;
	int	*Uxpunt_var_tipo;
	int	*Uxpunt_var_lista;
	int	Uxn_varlist;
	int	Uxn_varlist_kks;
	int	Uxn_varlist_tipo;
	int	Uxn_varlist_lista;
	int	Uxn_blocchi;
	int	Uxfirst_time;
	int	Uxsel_mod;
	Boolean	*Uxmatch;
	int	Uxlast_match;
	int	Uxnmatch;
	int	Uxfirst_time_find;
	unsigned char	*Uxstringa_match;
	unsigned char	*Uxold_stringa_match;
	int	Uxfirst_time_b;
	int	Uxsel_mod_b;
	Boolean	*Uxmatch_b;
	int	Uxlast_match_b;
	int	Uxnmatch_b;
	int	Uxfirst_time_find_b;
	unsigned char	*Uxstringa_match_b;
	unsigned char	*Uxold_stringa_match_b;
	int	*Uxpunt_conf_malf;
	int	Uxn_conf_malf;
	int	*Uxpunt_malf_kks;
	int	Uxn_conf_malf_kks;
	int	*Uxpunt_malf_tipo;
	int	Uxn_conf_malf_tipo;
	int	*Uxpunt_malf_lista;
	int	Uxn_conf_malf_lista;
	int	Uxfiltro_kks_malf_conf;
	unsigned char	Uxfilter_kks_malf_conf[12];
	int	Uxfiltro_tipo_malf_conf;
	FILTRO_TIPI	Uxfiltro_tipi_malf_conf;
	int	Uxconf_malf_select;
	int	Uxprimo_giro;
	Widget	Uxw;
	unsigned char	*Uxp;
	int	Uxchi;
	unsigned char	*Uxheader;
} _UxCselVar;

#ifdef CONTEXT_MACRO_ACCESS
static _UxCselVar              *UxSelVarContext;
#define selVar                  UxSelVarContext->UxselVar
#define frame2                  UxSelVarContext->Uxframe2
#define form42                  UxSelVarContext->Uxform42
#define selOkpb                 UxSelVarContext->UxselOkpb
#define selQuitpb               UxSelVarContext->UxselQuitpb
#define menu4                   UxSelVarContext->Uxmenu4
#define selVarCrMenu1           UxSelVarContext->UxselVarCrMenu1
#define selVarCrMenuFilepb1     UxSelVarContext->UxselVarCrMenuFilepb1
#define menu3_top_b3            UxSelVarContext->Uxmenu3_top_b3
#define selVarMenuFilter1       UxSelVarContext->UxselVarMenuFilter1
#define selVarMenuOtherPane1    UxSelVarContext->UxselVarMenuOtherPane1
#define selByAllVariablestb1    UxSelVarContext->UxselByAllVariablestb1
#define selByModeltb1           UxSelVarContext->UxselByModeltb1
#define selByModelOnlytb1       UxSelVarContext->UxselByModelOnlytb1
#define selVarMenuOtherPane_b1  UxSelVarContext->UxselVarMenuOtherPane_b1
#define selVarMenuKkstb1        UxSelVarContext->UxselVarMenuKkstb1
#define selVarMenuOtherPane_b2  UxSelVarContext->UxselVarMenuOtherPane_b2
#define selVarMenuTipotb1       UxSelVarContext->UxselVarMenuTipotb1
#define selVarMenuFilter_b1     UxSelVarContext->UxselVarMenuFilter_b1
#define menu3_top_b4            UxSelVarContext->Uxmenu3_top_b4
#define frame27                 UxSelVarContext->Uxframe27
#define selVarCrFilterForm1     UxSelVarContext->UxselVarCrFilterForm1
#define frame28                 UxSelVarContext->Uxframe28
#define form51                  UxSelVarContext->Uxform51
#define selVarCrAllVartb1       UxSelVarContext->UxselVarCrAllVartb1
#define selVarCrModBlocktb1     UxSelVarContext->UxselVarCrModBlocktb1
#define selVarCrModtb1          UxSelVarContext->UxselVarCrModtb1
#define frame29                 UxSelVarContext->Uxframe29
#define form52                  UxSelVarContext->Uxform52
#define selVarCrKkstb1          UxSelVarContext->UxselVarCrKkstb1
#define selVarCrTypetb1         UxSelVarContext->UxselVarCrTypetb1
#define selVarCrSaveFilterpb1   UxSelVarContext->UxselVarCrSaveFilterpb1
#define selVarCrApplyFilterpb1  UxSelVarContext->UxselVarCrApplyFilterpb1
#define panedWindow2            UxSelVarContext->UxpanedWindow2
#define selByModelForm1         UxSelVarContext->UxselByModelForm1
#define label8                  UxSelVarContext->Uxlabel8
#define label9                  UxSelVarContext->Uxlabel9
#define form43                  UxSelVarContext->Uxform43
#define selVarModFindDown       UxSelVarContext->UxselVarModFindDown
#define selVarText2             UxSelVarContext->UxselVarText2
#define selVarModFindUp         UxSelVarContext->UxselVarModFindUp
#define scrolledWindow10        UxSelVarContext->UxscrolledWindow10
#define selVarListaSistemi1     UxSelVarContext->UxselVarListaSistemi1
#define scrolledWindow11        UxSelVarContext->UxscrolledWindow11
#define selVarListaBlocchi1     UxSelVarContext->UxselVarListaBlocchi1
#define selVarCrKksForm2        UxSelVarContext->UxselVarCrKksForm2
#define selVarCrKksBullBoard2   UxSelVarContext->UxselVarCrKksBullBoard2
#define selVarCrKksText22       UxSelVarContext->UxselVarCrKksText22
#define selVarCrKksSistemaLabel2 UxSelVarContext->UxselVarCrKksSistemaLabel2
#define selVarCrKksSottosistLabel2 UxSelVarContext->UxselVarCrKksSottosistLabel2
#define selVarCrKksComponentLabel2 UxSelVarContext->UxselVarCrKksComponentLabel2
#define selVarCrKksText23       UxSelVarContext->UxselVarCrKksText23
#define selVarCrKksText24       UxSelVarContext->UxselVarCrKksText24
#define selVarCrKksText25       UxSelVarContext->UxselVarCrKksText25
#define selVarCrKksText26       UxSelVarContext->UxselVarCrKksText26
#define selVarCrKksText27       UxSelVarContext->UxselVarCrKksText27
#define selVarCrKksText28       UxSelVarContext->UxselVarCrKksText28
#define selVarCrKksText29       UxSelVarContext->UxselVarCrKksText29
#define selVarCrKksProgressLabel2 UxSelVarContext->UxselVarCrKksProgressLabel2
#define selVarCrKksText30       UxSelVarContext->UxselVarCrKksText30
#define selVarCrKksText31       UxSelVarContext->UxselVarCrKksText31
#define selVarCrKksText32       UxSelVarContext->UxselVarCrKksText32
#define selVarCrKksNimpLabel2   UxSelVarContext->UxselVarCrKksNimpLabel2
#define pushButton4             UxSelVarContext->UxpushButton4
#define selVarCrTipoForm1       UxSelVarContext->UxselVarCrTipoForm1
#define selVarCrTipoPressionetb1 UxSelVarContext->UxselVarCrTipoPressionetb1
#define selVarCrTipoEntalpiatb1 UxSelVarContext->UxselVarCrTipoEntalpiatb1
#define selVarCrTipoPortatatb1  UxSelVarContext->UxselVarCrTipoPortatatb1
#define selVarCrTipoGiritb1     UxSelVarContext->UxselVarCrTipoGiritb1
#define selVarCrTipoTemperaturatb1 UxSelVarContext->UxselVarCrTipoTemperaturatb1
#define selVarCrTipoAlzvalvtb1  UxSelVarContext->UxselVarCrTipoAlzvalvtb1
#define selVarCrTipoPotenzatb1  UxSelVarContext->UxselVarCrTipoPotenzatb1
#define pushButton5             UxSelVarContext->UxpushButton5
#define selVarCrTipoAingable    UxSelVarContext->UxselVarCrTipoAingable
#define selVarCrTipoInput       UxSelVarContext->UxselVarCrTipoInput
#define selVarCrTipoOutput      UxSelVarContext->UxselVarCrTipoOutput
#define form40                  UxSelVarContext->Uxform40
#define label10                 UxSelVarContext->Uxlabel10
#define form41                  UxSelVarContext->Uxform41
#define selVarFindUp1           UxSelVarContext->UxselVarFindUp1
#define selVarText1             UxSelVarContext->UxselVarText1
#define selVarFindDown1         UxSelVarContext->UxselVarFindDown1
#define scrolledWindow12        UxSelVarContext->UxscrolledWindow12
#define selVarToSelect1         UxSelVarContext->UxselVarToSelect1
#define menu13                  UxSelVarContext->Uxmenu13
#define selVarMenuPopupSaveFilter UxSelVarContext->UxselVarMenuPopupSaveFilter
#define selVarMenuPopupApplyFilter UxSelVarContext->UxselVarMenuPopupApplyFilter
#define selVarMenuPopup_b3      UxSelVarContext->UxselVarMenuPopup_b3
#define selVarMenuPopupSelect   UxSelVarContext->UxselVarMenuPopupSelect
#define selVarMenuPopup_b5      UxSelVarContext->UxselVarMenuPopup_b5
#define selVarMenuPopupQuit     UxSelVarContext->UxselVarMenuPopupQuit
#define mod_sel                 UxSelVarContext->Uxmod_sel
#define blocco_sel              UxSelVarContext->Uxblocco_sel
#define kks_filter_act          UxSelVarContext->Uxkks_filter_act
#define tipo_filter_act         UxSelVarContext->Uxtipo_filter_act
#define stringa_kks             UxSelVarContext->Uxstringa_kks
#define filtro_tipo             UxSelVarContext->Uxfiltro_tipo
#define punt_var                UxSelVarContext->Uxpunt_var
#define punt_var_kks            UxSelVarContext->Uxpunt_var_kks
#define punt_var_tipo           UxSelVarContext->Uxpunt_var_tipo
#define punt_var_lista          UxSelVarContext->Uxpunt_var_lista
#define n_varlist               UxSelVarContext->Uxn_varlist
#define n_varlist_kks           UxSelVarContext->Uxn_varlist_kks
#define n_varlist_tipo          UxSelVarContext->Uxn_varlist_tipo
#define n_varlist_lista         UxSelVarContext->Uxn_varlist_lista
#define n_blocchi               UxSelVarContext->Uxn_blocchi
#define first_time              UxSelVarContext->Uxfirst_time
#define sel_mod                 UxSelVarContext->Uxsel_mod
#define match                   UxSelVarContext->Uxmatch
#define last_match              UxSelVarContext->Uxlast_match
#define nmatch                  UxSelVarContext->Uxnmatch
#define first_time_find         UxSelVarContext->Uxfirst_time_find
#define stringa_match           UxSelVarContext->Uxstringa_match
#define old_stringa_match       UxSelVarContext->Uxold_stringa_match
#define first_time_b            UxSelVarContext->Uxfirst_time_b
#define sel_mod_b               UxSelVarContext->Uxsel_mod_b
#define match_b                 UxSelVarContext->Uxmatch_b
#define last_match_b            UxSelVarContext->Uxlast_match_b
#define nmatch_b                UxSelVarContext->Uxnmatch_b
#define first_time_find_b       UxSelVarContext->Uxfirst_time_find_b
#define stringa_match_b         UxSelVarContext->Uxstringa_match_b
#define old_stringa_match_b     UxSelVarContext->Uxold_stringa_match_b
#define punt_conf_malf          UxSelVarContext->Uxpunt_conf_malf
#define n_conf_malf             UxSelVarContext->Uxn_conf_malf
#define punt_malf_kks           UxSelVarContext->Uxpunt_malf_kks
#define n_conf_malf_kks         UxSelVarContext->Uxn_conf_malf_kks
#define punt_malf_tipo          UxSelVarContext->Uxpunt_malf_tipo
#define n_conf_malf_tipo        UxSelVarContext->Uxn_conf_malf_tipo
#define punt_malf_lista         UxSelVarContext->Uxpunt_malf_lista
#define n_conf_malf_lista       UxSelVarContext->Uxn_conf_malf_lista
#define filtro_kks_malf_conf    UxSelVarContext->Uxfiltro_kks_malf_conf
#define filter_kks_malf_conf    UxSelVarContext->Uxfilter_kks_malf_conf
#define filtro_tipo_malf_conf   UxSelVarContext->Uxfiltro_tipo_malf_conf
#define filtro_tipi_malf_conf   UxSelVarContext->Uxfiltro_tipi_malf_conf
#define conf_malf_select        UxSelVarContext->Uxconf_malf_select
#define primo_giro              UxSelVarContext->Uxprimo_giro
#define w                       UxSelVarContext->Uxw
#define p                       UxSelVarContext->Uxp
#define chi                     UxSelVarContext->Uxchi
#define header                  UxSelVarContext->Uxheader

#endif /* CONTEXT_MACRO_ACCESS */


/*******************************************************************************
       Declarations of global functions.
*******************************************************************************/

Widget	create_selVar( Widget _Uxw, unsigned char *_Uxp, int _Uxchi, unsigned char *_Uxheader );

#endif	/* _SELVAR_INCLUDED */
