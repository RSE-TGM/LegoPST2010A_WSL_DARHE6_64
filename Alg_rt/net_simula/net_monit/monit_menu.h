/**********************************************************************
*
*       C Header:               monit_menu.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jan 22 12:27:48 1997 %
*
**********************************************************************/
/*
   modulo monit_menu.h
   tipo 
   release 5.1
   data 11/7/95
   reserved @(#)monit_menu.h	5.1
*/

typedef struct voce_menu {
                    int ind;  /* indice in widget_array
                                 della voce menu */
                    int stato;  /* stato della voce:
                                     se attiva -> True
                                     se non attiva -> False
                                 */
                        } VOCE_MENU;

/* menu nello stato di simulazione in stop */

#define NUMERO_VOCI_MENU 	26

static VOCE_MENU voci_check[]={
         {k_initialize,False},
         {k_run,False},
         {k_freeze,False},
         {k_backtrack,False},
         {k_replay,False},
         {k_stop_replay,False},
         {k_clear,False},
         {k_stop,True},
         {k_quit,True},
         {k_timescaling,True},
         {k_stepscaling,True},
         {k_stepcr,True},
         {k_conflg,False},
         {k_confcr,False},
         {k_confcrall,False},
         {k_set_ftime,True},
         {k_load,False},
         {k_save,False},
         {k_edit,False},
         {k_statistics,True},
         {k_input,True},
         {k_staz_button,True},
         {k_inputstat,True},
	 {k_procstat,True},	/* Codice CAPPE */
         {k_editpert,True},
         {k_graphics,True},
	 {k_data_button,False}
                        };
                               
static VOCE_MENU voci_stop[]={
			{k_initialize,True},
			{k_run,False},
			{k_freeze,False},
			{k_backtrack,False},
			{k_replay,False},
                        {k_stop_replay,False},
			{k_clear,False},
			{k_stop,False},
			{k_quit,True},
			{k_timescaling,False},
			{k_stepscaling,False},
			{k_stepcr,False},
			{k_conflg,True},
			{k_confcr,True},
			{k_confcrall,True},
			{k_set_ftime,False},
			{k_load,False},
			{k_save,False},
			{k_edit,False},
			{k_statistics,False},
			{k_input,False},
			{k_staz_button,False},
			{k_inputstat,False},
			{k_procstat,False},	/* Codice CAPPE */
			{k_editpert,False},
			{k_graphics,False},
			{k_data_button,False}
			};



static VOCE_MENU voci_run[]={
			{k_initialize,False},
			{k_run,False},
			{k_freeze,True},
			{k_backtrack,False},
			{k_replay,False},
			{k_stop_replay,False},
			{k_clear,False},
			{k_stop,False},
#if defined LEGOCAD
			{k_quit,False},
#else
			{k_quit,True},
#endif
			{k_timescaling,True},
			{k_stepscaling,True},
			{k_stepcr,True},
			{k_conflg,False},
			{k_confcr,False},
			{k_confcrall,False},
			{k_set_ftime,True},
			{k_load,True},
			{k_save,True},
			{k_edit,True},
			{k_statistics,True},
			{k_input,True},
			{k_staz_button,True},
			{k_inputstat,True},
			{k_procstat,True},	/* Codice CAPPE */
			{k_editpert,True},
			{k_graphics,True},
			{k_data_button,False}
			};

static VOCE_MENU voci_freeze[]={
			{k_initialize,False},
			{k_run,True},
			{k_freeze,False},
			{k_backtrack,True},
			{k_replay,False},
			{k_stop_replay,False},
			{k_clear,True},
			{k_stop,True},
			{k_quit,False},
			{k_timescaling,True},
			{k_stepscaling,True},
			{k_stepcr,True},
			{k_conflg,False},
			{k_confcr,True},
			{k_confcrall,False},
			{k_set_ftime,True},
			{k_load,True},
			{k_save,True},
			{k_edit,True},
			{k_statistics,True},
			{k_input,True},
			{k_staz_button,True},
			{k_inputstat,True},
			{k_procstat,True}, 	/* Codice CAPPE */
			{k_editpert,True},
			{k_graphics,True},
			{k_data_button,False}
			};

static VOCE_MENU voci_errore[]={
			{k_initialize,False},
			{k_run,False},
			{k_freeze,False},
			{k_backtrack,False},
			{k_replay,False},
			{k_stop_replay,False},
			{k_clear,False},
			{k_stop,False},
			{k_quit,True},
			{k_timescaling,False},
			{k_stepscaling,False},
			{k_stepcr,False},
			{k_conflg,False},
			{k_confcr,False},
			{k_confcrall,False},
			{k_set_ftime,False},
			{k_load,False},
			{k_save,True},
			{k_edit,True},
			{k_statistics,False},
			{k_input,False},
			{k_staz_button,False},
			{k_inputstat,False},
			{k_procstat,False},	/* Codice CAPPE */
			{k_editpert,False},
			{k_graphics,True},
			{k_data_button,False}
			};

#if defined BACKTRACK
static VOCE_MENU voci_backtrack[]={
			{k_initialize,False},
			{k_run,False},
			{k_freeze,False},
			{k_backtrack,False},
			{k_replay,True},
			{k_stop_replay,True},
			{k_clear,False},
			{k_stop,False},
			{k_quit,False},
			{k_timescaling,True},
			{k_stepscaling,True},
			{k_stepcr,True},
			{k_conflg,False},
			{k_confcr,False},
			{k_confcrall,False},
			{k_set_ftime,True},
			{k_load,False},
			{k_save,False},
			{k_edit,False},
			{k_statistics,True},
			{k_input,True},
			{k_staz_button,True},
			{k_inputstat,True},
			{k_procstat,True},	/* Codice CAPPE */
			{k_editpert,True},
			{k_graphics,True},
			{k_data_button,False}
			};

static VOCE_MENU voci_replay[]={
			{k_initialize,False},
			{k_run,False},
			{k_freeze,False},
			{k_backtrack,True},
			{k_replay,False},
			{k_stop_replay,True},
			{k_clear,False},
			{k_stop,False},
			{k_quit,True},
			{k_timescaling,True},
			{k_stepscaling,True},
			{k_stepcr,True},
			{k_conflg,False},
			{k_confcr,False},
			{k_confcrall,False},
			{k_set_ftime,False},
			{k_load,True},
			{k_save,False},
			{k_edit,False},
			{k_statistics,True},
			{k_input,True},
			{k_staz_button,True},
			{k_inputstat,True},
			{k_procstat,True},	/* Codice CAPPE */
			{k_editpert,True},
			{k_graphics,True},
			{k_data_button,False}
			};

#endif
