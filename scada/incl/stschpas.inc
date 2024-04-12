/**********************************************************************
*
*       C Header:               stschpas.inc
*       Subsystem:              1
*       Description:
*       %created_by:    lomgr %
*       %date_created:  Thu Jul  1 17:20:50 2004 %
*
**********************************************************************/
/* File di include contenente la definizione delle strutture */


/* Struttura SCHEDULER  -->  Area dati di lavoro Scheduler PAS */

struct SCHEDULER { 
           char buf_dbl[DIMDBL];	// area data base locale
	   short p_status_word;		// stato coprocessore 8087
	   short p_control_word;	// control word 8087
	   short p_valore;		// valore letto da 8087
	   char  p_fl_sign;		// per memorizzare dati seno
	   char  p_fl_trigon;		// dati funzioni trigonometriche
	   short p_registro;		// appoggio operazioni con 8087
	   char  p_pa;			// pseudo accumulatore logico
	   char  p_spare;		// byte spare di allineamento
	   char *p_scb_pointer;		// pointer SCB corrente
	   char *cur_FP;
	   char *off_buf_dbl;	
	   char *off_inizio_codice;	
           char  buf_pcb[DIMPCB];	// area dati struttura PCB
#if defined OSF1_40 || defined LINUX
           short spare1;
           short spare2;
#endif
	   char  pac_mes[DIMPAC];	// area packet per send
	   char  buf_mes[DIMMES];	// area per messaggi
           short buf_pr[DIM_PR];		// area codice descrittori SCB
					// il suo dimensionamento
					// e' variabile e viene stabilito
					// nei moduli assembler 
           } ;


/* Struttura PCB  -->  PAS Control Block */

struct PCB {
           short stato;        // word stato PAS
           short indice_pas;   // indice PCB associata al PAS
           short begin_scb;    // indirizzo inizio SCB
           short ind_dbl;      // indirizzo inizio DBL
           short num_scb ;     // numero SCB che costituiscono il PAS
           short lun_rtf;      // lunghezza file .dbl + file .rtf
           short per_att;      // periodo di attivazione (multiplo tic att.)
           short spare[3];     // spare per arrivare a 10 word di PCB
           } ;


/* Struttura SCB  -->  Sequence Control Block */

struct SCB {   // struttura del sequence control block
           short st_seq;         // stato della sequenza
           short counter;	       // counter di time out
           short ind_cod;        // indirizzo alla entry relativa alla sequenza
           short begin_stk;      // offset inizio stack sequenza
           short end_stk;        // offset fine stack sequenza
           char ind_seq;        // indice sequenza utente
           char ind_pas;        // indice processo utente
           char *save_entry;     // save ritorno in caso di breakpoint
           char *save_sp;        // save stack pointer sequenza
           char *save_fp;        // save frame pointer sequenza
           char save_pa;       // save pseudo accumulatore
           char f_single_step; // flag di single step
           char f_init_stack;  // flag di inizializzazione stack sequenza
           char f_ritorno;     // codice numerico di terminazione
           short seq_stk[86];    // stack sequenza (la lunghezza deve essere 200 byte)
           } ;

