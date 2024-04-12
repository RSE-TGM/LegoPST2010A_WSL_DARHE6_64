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
	SepStruct.inc

	Contiene i messaggi e le strutture del protocollo con armadi Sepa 
	non comuni con quelli STAR_SDI

	19 Aprile 1993

*/
#define sp_armadi	12 		// n. max armadi Sepa
#define	sp_nump		4096		// n. max punti per armadio
/*
	n. totale nodi = n. armadi * 2 + nodo_armadi per indirizzamento fisico
*/
#define n_tot_nodi	(sp_armadi*2+nodo_armadi)
/*
	Definizione struttura file Fsvar.rtf
	E' composto da un header di 512 bytes inizializzato a 0
	che contiene la struttura heafsvar. Seguono sp_armadi record
	inizializzati a -1 e dimensionati sp_nump word
*/
#define sp_heasvar	512		// header file
#define l_nome_armadio   10 
typedef struct s_heafsvar {
				short n_punti;		// n. punti installati
				short l_punto;		// indice ultimo punto
				short duale;		// tipo di nodo singolo o duale
				char  nome[l_nome_armadio];	// nome armadio
			  } HEA_FSVAR;			

#define NODO_SING	1	//	nodo singolo
#define NODO_DUALE	0	//	nodo duale
/*
	I record associati a ciascun armadio sono composti da
	sp_nump word che contengono nei 15 bit bassi l'indice
	nel data base logico, il bit piu' alto indica se si
	tratta di digitale o analogico
*/
#define mask_tpun	0x8000		// maschera identificazione tipo
					// di punto (se 1 digitale)
/*
	La struttura sepnodi e' utilizzata per memorizzare lo stato
	dei nodi della rete e selezionare il nodo per la richiesta
	della data
*/
#define n_dignodi	3	//	n. punti diagnostica per nodo
#define n_digretA	0	//	diagn . rete A
#define n_digretB	1	//	diagn. rete B
#define n_digmodF	2	//	diagn. mod. funzionamento

typedef struct s_sepnodi {
	    	  unsigned char stato[n_dignodi];
			   char Fa;		// flag data attendibile
                           char Rce;            // flag Rce in corso
			   char Group;		// gruppo acquisizione di appartenenza
			} S_SEPNODI;

