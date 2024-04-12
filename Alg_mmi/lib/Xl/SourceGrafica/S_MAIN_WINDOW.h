/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
   modulo S_MAIN_WINDOW.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)S_MAIN_WINDOW.h	5.1
*/
/*
        Fine sezione per SCCS
*/
/*******************************************************************************
	S_MAIN_WINDOW.i.h
	(Generated from UIL file grafics.uil)
	This header file contains declarations of the callback procedures
	used in the widget tree of S_MAIN_WINDOW.
	It is included by grafics.i
*******************************************************************************/

#ifndef _S_MAIN_
#define _S_MAIN_

typedef struct
{
        S_XLGRAFICO *UxPXlGrafico;
        Widget  UxS_MAIN_WINDOW;
        Widget  Uxcontenitore;
        Widget  Uxtempo;
        Widget  Uxord1;
        Widget  Uxval1;
        Widget  Uxmis1;
        Widget  Uxtim1;
        Widget  Uxdraw0;
        Widget  Uxdraw1;
        Widget  Uxmenu1;
        Widget  Uxpop_file;
        Widget  Uxp_dir_button;
        Widget  Uxp_HC_button;
        Widget  Uxfile_pd;
        Widget  Uxpop_grafico;
        Widget  Uxp_zoom_control_button;
        Widget  Uxp_nozoom_control_button;
        Widget  Uxmenu1_p2_b3;
        Widget  Uxp_selgra_control_button;
        Widget  Uxp_memgra_control_button;
        Widget  Uxgrafici_pd;
        Widget  Uxpop_misure;
        Widget  Uxp_umis_control_button;
        Widget  Uxp_fsca_control_button;
        Widget  Uxmenu1_p3_b3;
        Widget  Uxp_selmis_control_button;
        Widget  Uxmisure_pd;
        Widget  Uxpop_def;
        Widget  Uxp_defumis_button;
        Widget  Uxp_collima_button;
        Widget  Uxp_zoomord_button;
        Widget  Uxp_secondi_button;
        Widget  Uxdef_pd;
} _UxCS_MAIN_WINDOW;

#define S_MAIN_WINDOW_Graf      UxS_MAIN_WINDOWContext->UxPXlGrafico
#define S_MAIN_WINDOW           UxS_MAIN_WINDOWContext->UxS_MAIN_WINDOW
#define contenitore             UxS_MAIN_WINDOWContext->Uxcontenitore
#define tempo                   UxS_MAIN_WINDOWContext->Uxtempo
#define ord1                    UxS_MAIN_WINDOWContext->Uxord1
#define val1                    UxS_MAIN_WINDOWContext->Uxval1
#define mis1                    UxS_MAIN_WINDOWContext->Uxmis1
#define tim1                    UxS_MAIN_WINDOWContext->Uxtim1
#define draw0                   UxS_MAIN_WINDOWContext->Uxdraw0
#define draw1                   UxS_MAIN_WINDOWContext->Uxdraw1
#define menu1                   UxS_MAIN_WINDOWContext->Uxmenu1
#define pop_file                UxS_MAIN_WINDOWContext->Uxpop_file
#define p_dir_button            UxS_MAIN_WINDOWContext->Uxp_dir_button
#define p_HC_button             UxS_MAIN_WINDOWContext->Uxp_HC_button
#define file_pd                 UxS_MAIN_WINDOWContext->Uxfile_pd
#define pop_grafico             UxS_MAIN_WINDOWContext->Uxpop_grafico
#define p_zoom_control_button   UxS_MAIN_WINDOWContext->Uxp_zoom_control_button
#define p_nozoom_control_button UxS_MAIN_WINDOWContext->Uxp_nozoom_control_button
#define menu1_p2_b3             UxS_MAIN_WINDOWContext->Uxmenu1_p2_b3
#define p_selgra_control_button UxS_MAIN_WINDOWContext->Uxp_selgra_control_button
#define p_memgra_control_button UxS_MAIN_WINDOWContext->Uxp_memgra_control_button
#define grafici_pd              UxS_MAIN_WINDOWContext->Uxgrafici_pd
#define pop_misure              UxS_MAIN_WINDOWContext->Uxpop_misure
#define p_umis_control_button   UxS_MAIN_WINDOWContext->Uxp_umis_control_button
#define p_fsca_control_button   UxS_MAIN_WINDOWContext->Uxp_fsca_control_button
#define menu1_p3_b3             UxS_MAIN_WINDOWContext->Uxmenu1_p3_b3
#define p_selmis_control_button UxS_MAIN_WINDOWContext->Uxp_selmis_control_button
#define misure_pd               UxS_MAIN_WINDOWContext->Uxmisure_pd
#define pop_def                 UxS_MAIN_WINDOWContext->Uxpop_def
#define p_defumis_button        UxS_MAIN_WINDOWContext->Uxp_defumis_button
#define p_collima_button        UxS_MAIN_WINDOWContext->Uxp_collima_button
#define p_zoomord_button        UxS_MAIN_WINDOWContext->Uxp_zoomord_button
#define p_secondi_button        UxS_MAIN_WINDOWContext->Uxp_secondi_button
#define def_pd                  UxS_MAIN_WINDOWContext->Uxdef_pd

void	create_proc();
void	activate_proc();
void	collima_proc();
void	memcollima_proc();
void	zoomord_proc();
void	memzoomord_proc();
void	secondi_proc();
void	memsecondi_proc();
void	zoom_proc();
void	HC_proc();
void	quit_proc();
void	draw_proc();
void    R_draw_proc();
void	resize_proc();
void	PostIt();

#endif
