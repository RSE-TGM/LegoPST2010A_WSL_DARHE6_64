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
	parametri definizione per file svincolo FSVAR
	utilizzato da SEPA
*/
#define sp_armadi	12 		// n. max armadi
#define	sp_nump		4096		// n. max punti per armadio
#define sp_ofan		0   		// i primi 2048 sono analogici
#define sp_ofdi		2048	 	// i secondi 2048 sono digitali
/*
	le prime sp-armadi words contengono il numero di punti
	associati all'armadio
	il file viene creato e inizializzato a -1 eccetto l'header
	a zero
*/
#define sp_heasvar	512		// header file

			
