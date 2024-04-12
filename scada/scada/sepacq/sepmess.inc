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
	SepMess.inc

	Contiene i messaggi e le strutture del protocollo con armadi Sepa 
	non comuni con quelli STAR_SDI

	19 Aprile 1993

*/
#include "rcemess.h"

#define mrdag	28	// richiesta digitali globali
#define POINT_NULL  -1	// puntatore nullo
typedef struct s_mrdag {
			HEASCA hea;
			short  point; } S_MRDAG;

#define mdanas 64        // acquisizione dati analogici
#define max_analogici_sepa 180

typedef struct s_dtaa_sepa {
		short point ;		// contiene indice + flag FH FL CA
		short val ; } S_DTAA_SEPA ;
typedef struct s_mdana_sepa {
		HEASCA hea ;	
		S_DTAA_SEPA  dati[max_analogici_sepa]; } S_DANA_SEPA ;

#define mrtime	29	// richiesta sincronizzazione ora
typedef struct s_mrtime {
			HEASCA hea;
		        } S_MRTIME;

#define mdtime 33	// risposta sincronizzazione data e ora
typedef struct s_mdtime {
		HEASCA hea;
		short valida;
		short giorno;
		short ora;
		char minuti;
		char secondi;
		short milli;
		} S_MDTIME;

typedef struct s_mscao_sep {
		HEASCA hea;
		short  indice; 
		short  valore;	} S_MSCAO_SEP ;


#define mdrce	67	// dati rce


typedef struct s_mrce {
		HEASCA hea;
		S_RCE  m;
		} S_MRCE;
