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
   Gesrep.h

   Il file di include gesrep contiene le strutture dati utilizzate per
   la gestione dei reperibili

*/

// dimensionamenti reperibili:
// n. specialita', n. squadre per specialita', n. di persone per squadra
#define max_specrep  8        // n. massimo specialita' 
#define max_squrep   8        // n. massimo squadre a disposizione di ogni reperibile
#define max_elesqu   8        // n. massimo elementi per squadra

// dimensionamenti n. punti associabili ad una gestione di reperibilita'
#define max_puntirep 4096     // n. massimo punti reperibili
#define max_vfisse   10       // n. massimo voci fisse
#define max_vvaria   10       // n. massimo voci variabili

// Struttura definizione punti associati a reperibilita'
#define lun_tagrep   16       // lunghezza nome reperibili (attualmente utilizzata fino a 10)

typedef struct s_punrep {
         char  tag[lun_tagrep];  // tag reperibile
         short  vfisse[max_vfisse];  // voci fisse
         short  vvaria[max_vvaria];  // voci variabili
         char  severita;            // severita' (ascii '1', '2' ecc..);
         char  specrep;             // specialita' o reperibile associato
               } S_PUNREP;

pub S_PUNREP punrep[max_puntirep];

// definizione svincoli data base - reperibili
pub short *repaa;
pub short *repas;
pub short *repac;
pub short *repad;
pub short *repda;
pub short *repds;
pub short *repdc;
pub short *repdd;
pub short *repor;

// Struttura per gli svincoli dei punti diagnostica dei reperibili
typedef struct s_svrep {
			short interv;
			short nchiam;
			short cod;
			short ntel[max_elesqu];
			short npref[max_elesqu];
				  } S_SVREP;
				  
// Svincolo punti di diagnostica reperibili
pub S_SVREP *svrep;

// Lunghezza massima della linea dei file di configurazione
#define lLine	256

// Pattern di riempimento del buffer dei reperibili segnala campo non utilizzato
#define FILPATT -1

// Formato delle stringhe per la costruzione dei punti di diagnostica dei reperibili
#define szForTel    "SR%02dTEL%02d"
#define szForPref   "SR%02dPREF%02d"
#define szForCod    "SR%02dDTMF"
#define szForChiam  "SR%02dNR"
#define szForInterv "SR%02dIR"
#define szRicTag	  "SRRICTAG"
#define szNonRicTag "SRNRICTAG"
#define szTag       "SRDIATAG"
#define szTel       "SRDIATEL"
#define szPref      "SRDIAPREF"

#define nRicTag    1
#define nNonRicTag 0
#define nTag       0
#define nTel       1
#define nPref      2

// Massima lunghezza del messaggio
#define lBuffer 256

// Struttura del messaggio
typedef struct s_rep
         {
            short count;
            char  mess[lBuffer];
         }S_MGESREP;

// variabile globale : n. massimo di messaggi in coda (default:50)

#define def_max_repall   50      // valore di default

pub   short  max_repall;
pub   short  cont_repall;        // stato attuale accodamenti

// variabile globale :  n. massimo di riaccodamenti permesso (default=infiniti)
pub   short  max_repretry;

// Massimo numero di voci con cui comporre il messaggio telefonico
#define maxVoci  11

// Svincolo punti di diagnostica per segnalazione riconoscimento avvenuto o non avvenuto
pub short svRic[2];

// Svincolo punti di diagnostica per segnalazione telefono e punto in esame
pub short svDia[3];

// Assoiazioni tra tipi di allarmi e voci variabili
#define FA 		0	// Fuori attendibilita'
#define RFA		1	// Rientro da fuori attendibilita'

// Digitali
#define	ST0		2	// Stato 0
#define	ST1		3	// Stato 1

// Analogici
#define FLH		2	// Fuori limite alto
#define	FLHH	3	// Fuori limite altissimo
#define FLL		4	// Fuori limite basso
#define FLLL	5	// Fuori limite bassissimo
#define RFLH    6	// Rientro da fuori limite alto
#define RFLHH	7	// Rientro da fuori limite altissimo
#define RFLL	8	// Rientro da fuori limite basso
#define	RFLLL	9	// Rientro da fuori limite bassissimo

// Organi
#define	CF		2	// Comando Fallito
#define	VS		3	// Variazione spontanea

