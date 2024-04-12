/**********************************************************************
*
*       C Header:               edi_menu.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:04:36 1996 %
*
**********************************************************************/
/*  EDI_MENU.H		file di definizione strutture per gli stati
			dei vari menu & push button (attivi/disattivi)
			in base alle situazioni che si possono presentare
			nell'applicativo EDICOLE	*/

/* Caso in cui si sta editando una BITMAP ---> non si puo' */
/* fare niente in EDICOLE... */
Voci_menu vm_sospendi_tutto[] = {
			      {K_QUIT_PROGRAM , False}, 
			      {K_MODULE_P , False}, 
			      {K_MODULE_NP, False}, 
			      {K_STD_MODULE_P , False}, 
			      {K_STD_MODULE_NP, False}, 
			      {K_MODIFY , False}, 
			      {K_COPY , False}, 
			      {K_CLEAR , False}, 
			      {K_NEW , False}, 
			      {K_SAVE , False}, 
			      {K_DELETE , False}, 
			      {K_ICON_WIDTH , False}, 
			      {K_ICON_HEIGHT , False}, 
			      {K_FG_MENU , False}, 
			      {K_NEXT_ICON , False}, 
			      {K_PREVIOUS_ICON , False},
			      {K_SYMBOL , False}
			     };

/* editazione dell'icona standard */
Voci_menu vm_edi_icona_std[] = {
			      {K_QUIT_PROGRAM , True}, 
			      {K_MODULE_P , True}, 
			      {K_MODULE_NP, True}, 
			      {K_STD_MODULE_P , True}, 
			      {K_STD_MODULE_NP, True}, 
			      {K_MODIFY , True}, 
			      {K_COPY , True}, 
			      {K_CLEAR , True}, 
			      {K_NEW , True}, 
			      {K_SAVE , True}, 
			      {K_DELETE , True}, 
			      {K_ICON_WIDTH , True}, 
			      {K_ICON_HEIGHT , True}, 
			      {K_FG_MENU , True}, 
			      {K_NEXT_ICON , False}, 
			      {K_PREVIOUS_ICON , False},
			      {K_SYMBOL , True}
			     };

/* All'avviamento del programma */
Voci_menu vm_inizio_programma[] = {
			        {K_QUIT_PROGRAM , True}, 
			        {K_MODULE_P , True}, 
			        {K_MODULE_NP, True}, 
			        {K_STD_MODULE_P , True}, 
			        {K_STD_MODULE_NP, True}, 
			        {K_MODIFY , False}, 
			        {K_COPY , False}, 
			        {K_CLEAR , False}, 
			        {K_NEW , False}, 
			        {K_SAVE , False}, 
			        {K_DELETE , False}, 
			        {K_ICON_WIDTH , True}, 
			        {K_ICON_HEIGHT , True}, 
			        {K_FG_MENU , False}, 
			        {K_NEXT_ICON , False}, 
			        {K_PREVIOUS_ICON , False},
			        {K_SYMBOL , True}
			       };
	
/* Caso in cui si seleziona un modulo di PROCESSO */
Voci_menu vm_moduli_p_ico[] = {
			{K_QUIT_PROGRAM , True}, 
			{K_MODULE_P , True}, 
			{K_MODULE_NP, True}, 
			{K_STD_MODULE_P , True}, 
			{K_STD_MODULE_NP, True}, 
			{K_MODIFY , True}, 
			{K_COPY , True}, 
			{K_CLEAR , True}, 
			{K_NEW , True}, 
			{K_SAVE , True}, 
			{K_DELETE , True}, 
			{K_ICON_WIDTH , True}, 
			{K_ICON_HEIGHT , True}, 
			{K_FG_MENU , True}, 
			{K_NEXT_ICON , True}, 
			{K_PREVIOUS_ICON , True},
			{K_SYMBOL , True}
		       };

Voci_menu vm_nessuna_icona[] = {
			{K_QUIT_PROGRAM , True}, 
			{K_MODULE_P , True}, 
			{K_MODULE_NP, True}, 
			{K_STD_MODULE_P , True}, 
			{K_STD_MODULE_NP, True}, 
			{K_MODIFY , False}, 
			{K_COPY , False}, 
			{K_CLEAR , False}, 
			{K_NEW , True}, 
			{K_SAVE , False}, 
			{K_DELETE , False}, 
			{K_ICON_WIDTH , False}, 
			{K_ICON_HEIGHT , False}, 
			{K_FG_MENU , False}, 
			{K_NEXT_ICON , False}, 
			{K_PREVIOUS_ICON , False},
			{K_SYMBOL , True}
		       };

/* Caso in cui si seleziona un modulo di SCHEMA */
Voci_menu vm_moduli_np[] ={
			{K_QUIT_PROGRAM , True}, 
			{K_MODULE_P , True}, 
			{K_MODULE_NP, True}, 
			{K_STD_MODULE_P , True}, 
			{K_STD_MODULE_NP, True}, 
			{K_MODIFY , False}, 
			{K_COPY , False}, 
			{K_CLEAR , False}, 
			{K_NEW , False}, 
			{K_SAVE , False}, 
			{K_DELETE , False}, 
			{K_ICON_WIDTH , False}, 
			{K_ICON_HEIGHT , False}, 
			{K_FG_MENU , False}, 
			{K_NEXT_ICON , False}, 
			{K_PREVIOUS_ICON , False},
			{K_SYMBOL , True}
		       };

/* Numero di voci dei menu & push button */
short numero_voci = sizeof vm_moduli_p_ico / sizeof vm_moduli_p_ico[0];


/*** FINE FILE edi_menu.h ***/
