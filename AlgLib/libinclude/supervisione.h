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
   modulo supervisione.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)supervisione.h	5.1
*/
/* HEADER per tutte le comunicazione fra lo schedulatore e gli eventuali
   processi di supervisione agganciati alla simulazione */

struct header_sv_st {
		int inizio_dati;	/*puntatore alla posizione del
					  primo dato*/
		int lun;		/*lunghezza in byte del campo
					  dati*/
		int tempo;		/*tempo della simulazione*/
		int tempo_rit;		/*ritardo della simulazione*/
		int comando;		/*campo comando*/
		int flag;		/*flag di utilita'*/
		char tipo_dati;  	/*DATI_ANALOGICI DATI_DIGITALI*/
		char indirizzo_dato;	/*TRUE FALSE*/
		char stato_sim;		/*stato della simulazione*/
		char spare;		/*carattere spare*/
                };

typedef struct header_sv_st HEADER_SV;

#define DATI_ANALOGICI		0
#define DATI_DIGITALI		1


/* codici per il campo comando della struttura HEADER_SV */

#define         RICH_DATI_TOPOLOGIA     	1
#define         DATI_TOPOLOGIA          	2
#define         ACK_DATI_TOPOLOGIA      	3
#define         INTERVALLO_AGG          	4
#define         ACK_INTERVALLO_AGG     		5
#define         DATI_LEGOGRAF           	6
#define         TERMINE_SUPERVISIONE           	7
#define		PERTURBAZIONE			8
#define         ACK_TERMINE_SUPERVISIONE      	9
