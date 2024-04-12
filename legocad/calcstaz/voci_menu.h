/**********************************************************************
*
*       C Header:               voci_menu.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:01:20 1996 %
*
**********************************************************************/
/*** include file voci_menu.h ***/

/* Calleri Nicola, Buffo Massimo 11/06/1992 */

/* Stato dei push-button 'Start' e 'Step' a seconda dello stato del calcolo */
/* caso in cui il modello non e' ancora stato selezionato */
VOCE_MENU button_senza_modello[] = {
				{K_START,False},
				{K_STEP ,False}
					  };

VOCE_MENU button_direct[] = {
				{K_START,True},
				{K_STEP ,False}
					  };

VOCE_MENU button_interactive[] = {
				{K_START,False},
				{K_STEP ,True}
					  };

/* numero di voci push-button */
short numero_voci_button = (sizeof button_interactive/
			    sizeof button_interactive[0]);

/* Stato delle voci selezionabili riferite allo stato del calcolo */
/* Stato in cui lo stazionario non e' ancora stato attivato */
VOCE_MENU voci_non_attivato[] = {
				{K_MODEL_SELECTION,True},
				{K_EXIT_PROGRAM,True},
				{K_TOLERANCE,True},
				{K_DIRECT_MODE,True},
				{K_INTERACTIVE_MODE,True},
/*				{K_FREE_DIAGNOSTICS,True}, */
/*				{K_GUIDED_DIAGNOSTICS,True}, */
				{K_SAVE_CURRENT_SETTING,True},
				{K_SET_DEFAULT_SETTING,True},
				{K_UNKNOWN_VAR_SELECTION,True},
				{K_SYSTEM_DATA_MODIFY,True},
				{K_LOAD_PREVIOUS_DATA,True},
				{K_LOAD_LAST_DATA,True},
				{K_RESULTS,False}, 
				{K_EQUATION_DIAGNOSTICS,False},
				{K_ITERATION_DIAGNOSTICS,False},
				{K_JACOBIAN_DIAGNOSTICS,False},
				{K_SYSTEM_RESULTS,False},
				{K_COMPUTING_REPORTS,False},
			  };

VOCE_MENU voci_senza_modello[] = {
				{K_MODEL_SELECTION,True},
				{K_EXIT_PROGRAM,True},
				{K_TOLERANCE,True},
				{K_DIRECT_MODE,True},
				{K_INTERACTIVE_MODE,True},
/*				{K_FREE_DIAGNOSTICS,True}, */
/*				{K_GUIDED_DIAGNOSTICS,True}, */
				{K_SAVE_CURRENT_SETTING,True},
				{K_SET_DEFAULT_SETTING,True},
				{K_UNKNOWN_VAR_SELECTION,False},
				{K_SYSTEM_DATA_MODIFY,False},
				{K_LOAD_PREVIOUS_DATA,False},
				{K_LOAD_LAST_DATA,False},
				{K_RESULTS,False},
				{K_EQUATION_DIAGNOSTICS,False},
				{K_ITERATION_DIAGNOSTICS,False},
				{K_JACOBIAN_DIAGNOSTICS,False},
				{K_SYSTEM_RESULTS,False},
				{K_COMPUTING_REPORTS,False}
			  };

/* Stato in cui lo stazionario e' in corso in modalita' diretta */
VOCE_MENU voci_diretta[] = {
				{K_MODEL_SELECTION,False},
				{K_EXIT_PROGRAM,True},
				{K_TOLERANCE,False},
				{K_DIRECT_MODE,False},
				{K_INTERACTIVE_MODE,False},
/*				{K_FREE_DIAGNOSTICS,True}, */
/*				{K_GUIDED_DIAGNOSTICS,True}, */
				{K_SAVE_CURRENT_SETTING,False},
				{K_SET_DEFAULT_SETTING,False},
				{K_UNKNOWN_VAR_SELECTION,False},
				{K_SYSTEM_DATA_MODIFY,False},
				{K_LOAD_PREVIOUS_DATA,False},
				{K_LOAD_LAST_DATA,False},
				{K_RESULTS,False},
				{K_EQUATION_DIAGNOSTICS,False},
				{K_ITERATION_DIAGNOSTICS,False},
				{K_JACOBIAN_DIAGNOSTICS,False},
				{K_SYSTEM_RESULTS,False},
				{K_COMPUTING_REPORTS,False}
			  };

/* Stato in cui lo stazionario e' in corso in modalita' interattiva */
VOCE_MENU voci_interattiva[] = {
				{K_MODEL_SELECTION,False},
				{K_EXIT_PROGRAM,True},
				{K_TOLERANCE,False},
				{K_DIRECT_MODE,False},
				{K_INTERACTIVE_MODE,False},
/*				{K_FREE_DIAGNOSTICS,True}, */
/*				{K_GUIDED_DIAGNOSTICS,True}, */
				{K_SAVE_CURRENT_SETTING,False},
				{K_SET_DEFAULT_SETTING,False},
				{K_UNKNOWN_VAR_SELECTION,True},
				{K_SYSTEM_DATA_MODIFY,True},
				{K_LOAD_PREVIOUS_DATA,True},
				{K_LOAD_LAST_DATA,True},
				{K_RESULTS,True},
				{K_EQUATION_DIAGNOSTICS,True},
				{K_ITERATION_DIAGNOSTICS,True},
				{K_JACOBIAN_DIAGNOSTICS,True},
				{K_SYSTEM_RESULTS,False},
				{K_COMPUTING_REPORTS,False}
			  };

/* Stato in cui lo stazionario e' comunque terminato */
VOCE_MENU voci_terminato[] = {
				{K_MODEL_SELECTION,True},
				{K_EXIT_PROGRAM,True},
				{K_TOLERANCE,True},
				{K_DIRECT_MODE,True},
				{K_INTERACTIVE_MODE,True},
/*				{K_FREE_DIAGNOSTICS,True}, */
/*				{K_GUIDED_DIAGNOSTICS,True}, */
				{K_SAVE_CURRENT_SETTING,True},
				{K_SET_DEFAULT_SETTING,True},
				{K_UNKNOWN_VAR_SELECTION,True},
				{K_SYSTEM_DATA_MODIFY,True},
				{K_LOAD_PREVIOUS_DATA,True},
				{K_LOAD_LAST_DATA,True},
				{K_RESULTS,True},
				{K_EQUATION_DIAGNOSTICS,True},
				{K_ITERATION_DIAGNOSTICS,True},
				{K_JACOBIAN_DIAGNOSTICS,True},
				{K_SYSTEM_RESULTS,True},
				{K_COMPUTING_REPORTS,True}
			  };

/* numero di voci che compongono il menu */
short numero_voci_menu = (sizeof voci_terminato/
			    sizeof voci_terminato[0]);

/*********************************/
/* ANALISI DELLA MATRICE JACOBIANA  */
/* se NON e' stata selezionata un'iterazione */
VOCE_MENU analisi_jacobiano_no[] = {
				{K_DISPLAY_VARIABLES,False},
				{K_DISPLAY_BLOCKS,False},
				{K_INFO_BUTTON,False},
				{K_ROW_BUTTON,False},
				{K_COLUMN_BUTTON,False}
					  };

VOCE_MENU jacobiano_non_sing[] = {
				{K_DISPLAY_VARIABLES,True},
				{K_DISPLAY_BLOCKS,True},
				{K_INFO_BUTTON,False},
				{K_ROW_BUTTON,False},
				{K_COLUMN_BUTTON,False}
					  };

VOCE_MENU jacobiano_solo_sing[] = {
				{K_DISPLAY_VARIABLES,True},
				{K_DISPLAY_BLOCKS,True},
				{K_INFO_BUTTON,True},
				{K_ROW_BUTTON,False},
				{K_COLUMN_BUTTON,False}
					  };

VOCE_MENU jacobiano_sing_righe[] = {
				{K_DISPLAY_VARIABLES,True},
				{K_DISPLAY_BLOCKS,True},
				{K_INFO_BUTTON,True},
				{K_ROW_BUTTON,True},
				{K_COLUMN_BUTTON,False}
					  };

VOCE_MENU jacobiano_sing_col[] = {
				{K_DISPLAY_VARIABLES,True},
				{K_DISPLAY_BLOCKS,True},
				{K_INFO_BUTTON,True},
				{K_ROW_BUTTON,False},
				{K_COLUMN_BUTTON,True}
					  };

/*  altrimenti tutti i bottoni sono abilitati...  */
VOCE_MENU analisi_jacobiano_si[] = {
				{K_DISPLAY_VARIABLES,True},
				{K_DISPLAY_BLOCKS,True},
				{K_INFO_BUTTON,True},
				{K_ROW_BUTTON,True},
				{K_COLUMN_BUTTON,True}
					  };

/* numero di voci analisi_jacobiano  */
short numero_voci_jacobiano = (sizeof analisi_jacobiano_no/
			    sizeof analisi_jacobiano_no[0]);

/*** fine voci_menu.h ***/
