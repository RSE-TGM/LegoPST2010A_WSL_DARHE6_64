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
	SIMANA.INC
        contiene i puntatori degli analogici di diagnostica legati 
        al SSC di un SIMULATORE
	N.B. i valori sotto riportati devono corrispondere ai puntatori
	degli analogici di stato corrispondenti.

        Settembre '92  -  GM.Furlan
*/

/*	       
	diagnostica supervisione simulatore
*/
#define sscnumci         100            // numero di condizione iniziale
#define sscnumbt         101            // numero di foto di backtrack
/*
	definizione locazioni per memorizzare tempo simulatore
*/
#define db_ora_sim       102
#define db_minuti_sim    103 
#define db_secondi_sim   104 
#define db_giorno_sim    105
#define db_mese_sim      106
#define db_anno_sim      107
#define dbtemp_sim       108
